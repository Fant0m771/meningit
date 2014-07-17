<?php
// $Id$

/**
 * @file
 * Responsible for generating, encrypting and sending the file to CEMHUB
 */

/**
 * Handler function to process the submissions
 */
function cemhub_process_submissions() {
  $integrated_webforms = cemhub_get_integrated_activated_webforms_settings();
  if (empty($integrated_webforms)) {
    watchdog('cemhub', 'The file was not generated because there is no form selected to be integrated with CEMHUB');
    return FALSE;
  }

  module_load_include('inc', 'cemhub', 'cemhub.mail');

  $vendor_id = variable_get('cemhub_vendor_id');

  $record_count = 0;
  $total_lines  = 0;
  $file_lines   = '';
  $last_submissions_by_webform = array();

  foreach ($integrated_webforms as $webform) {
    $last_submissions_by_webform[$webform->nid] = cemhub_get_last_webform_submission_id($webform->nid, $webform->last_submission_id);

    // WARNING: $record_count and $total_lines are passed by referece below
    $file_lines .= cemhub_get_file_lines_from_webform_submissions($webform, $vendor_id, $total_lines, $record_count);
  }

  if (!empty($file_lines)) {
    $file_data = cemhub_get_file_contents_with_trailer_records($vendor_id, $total_lines, $record_count, $file_lines);
    $inbound_folder_path = cemhub_get_files_repository_path(TRUE) . '/';
    $file_name = cemhub_get_new_file_name();

    $saved_file = file_save_data($file_data, $inbound_folder_path . $file_name . '.txt', FILE_EXISTS_REPLACE);
    if ($saved_file) {
      watchdog('cemhub', 'The file "' . $file_name . '.txt" was successfully generated in the folder: ' . $inbound_folder_path);
      if (cemhub_send_file($file_name)) {
        cemhub_update_config_with_last_submission_ids($last_submissions_by_webform);
        cemhub_delete_submissions($last_submissions_by_webform);
        cemhub_send_success_job_email();
      }

      // Delete the flat files at the end of the operations
      cemhub_delete_flat_files($file_name);
    }
    else {
      $error_message = 'The file "' . $file_name . '.txt" can not be generated, make sure the permissions and folders are set properly. Folder: ' . $inbound_folder_path;
      watchdog('cemhub', $error_message);
      cemhub_send_failure_job_email($error_message);
    }
  }
  else {
    watchdog('cemhub', 'The file was not generated and sent because does not exist data to integrate.');
    cemhub_send_no_submissions_job_email();
  }
}

/**
 * Given a string containing the records to send to CEMHUB, return it with the
 * trailer records (first and last lines) expected by the CEMHUB parser
 *
 * @param string $vendor_id
 * @param int $total_lines
 * @param int $record_count
 * @param string $file_lines
 *
 * @return string
 */
function cemhub_get_file_contents_with_trailer_records($vendor_id, $total_lines, $record_count, $file_lines) {
  $trailer_record = cemhub_get_trailer_file_record($vendor_id, $total_lines, $record_count);
  $file_content = $trailer_record . $file_lines . $trailer_record;

  return $file_content;
}

/**
 * Builds the trailer record used to wrap the registries sent to CEMHUB
 *
 * @param string $vendor_id
 * @param int $total_lines
 * @param int $record_count
 *
 * @return string
 */
function cemhub_get_trailer_file_record($vendor_id, $total_lines, $record_count) {
  $trailer_record = $vendor_id . "|" . $total_lines . "|" . $record_count . "|" . date('Ymd') . "|" . date('His') . "|\r\n";

  return $trailer_record;
}

/**
 * Returns a string containing the registries to be sent to CEMHUB, based on the
 * webform submissions
 *
 * @param stdClass $webform
 * @param string $vendor_id
 * @param int $total_lines
 * @param int $record_count
 *
 * @return string
 */
function cemhub_get_file_lines_from_webform_submissions($webform, $vendor_id, &$total_lines, &$record_count) {
  $root_uii = variable_get('cemhub_organization_code');

  $file_lines = '';

  $webform_submissions = cemhub_get_webform_submissions_since_last_submission_id($webform->nid, $webform->last_submission_id);
  if (!empty($webform_submissions)) {
    foreach ($webform_submissions as $webform_submission) {
      $submission_fields = cemhub_get_submission_fields($webform->nid, $webform_submission->sid);

      if ($submission_fields) {
        // updated by reference. used outside
        $record_count++;

        $uii = cemhub_get_uii($root_uii, $record_count);

        foreach ($submission_fields as $fields) {
          foreach ($fields as $row) {
            // Can not be sent to an empty answer
            if (!empty($row['data'])) {
              $campaign_src = (!empty($row['campaign'])) ? $row['campaign'] : $webform->campaign_source;

              // updated by reference. used outside
              $total_lines++;

              $file_lines .= cemhub_build_file_line(
                $vendor_id,
                date("Ymd", $webform_submission->submitted),
                trim($campaign_src),
                $uii,
                $webform->survey_id,
                $row['question_code'],
                $row['answer_code'],
                $row['data']
              );
            }
          }
        }
      }
    }
  }

  return $file_lines;
}

/**
 * Returns an array with the submission fields
 *
 * @param int $webform_nid
 * @param int $webform_submission_id
 *
 * @return array $rows
 */
function cemhub_get_submission_fields($webform_nid, $webform_submission_id) {
  $rows = array();

  $submitted_fields_result_set = cemhub_get_webform_submission_fields_as_result_set($webform_nid, $webform_submission_id);
  while ($submitted_field = $submitted_fields_result_set->fetchAssoc()) {
    $answer_details = cemhub_get_answer_details($submitted_field);
    $submitted_field['answer_code'] = $answer_details['code'];
    $submitted_field['data'] = $answer_details['value'];

    $field_key = $submitted_field['form_key'];
    unset($submitted_field['form_key']);
    $rows[$field_key][] = $submitted_field;
  }

  // implements hook_cemhub_data_alter
  foreach (module_implements('cemhub_data_alter') as $module) {
    call_user_func_array($module . '_' . 'cemhub_data_alter', array(&$rows, $webform_nid));
  }

  return $rows;
}

/**
 * Return an array containing the Answer code/Answer value
 *
 * @param array $submitted_field
 *
 * @return array
 */
function cemhub_get_answer_details($submitted_field) {
  $answer_value = '';
  $answer_code  = '';

  $answer_map = list_extract_allowed_values($submitted_field['answer_code'], 'list_text', FALSE);

  $is_select_field = count($answer_map) > 1;
  if ($is_select_field) {
    if (empty($submitted_field['data'])) {
      // define default value if no data submited
      $answer_value = array_keys($answer_map);
      $answer_value = $answer_value[0];
      $answer_code = $answer_map[$answer_value];
    }
    else {
      // set the value selected according to the options webform
      $answer_value = $submitted_field['data'];
      $answer_code = $answer_map[$submitted_field['data']];
    }
  }
  else {
    // answer field type is textfield
    $answer_value = $submitted_field['data'];
    $answer_code = array_shift($answer_map);
  }

  $answer_details = array(
    'code'  => $answer_code,
    'value' => str_replace('|', '', $answer_value),
  );

  return $answer_details;
}

/**
 * Returns the last submission id for the given webform nid
 *
 * @param int $nid
 * @param int $latest_submission
 *
 * @return int
 */
function cemhub_get_last_webform_submission_id($nid, $latest_submission) {
  $limit = cemhub_get_limit_submissions_per_day($nid);

  $query = <<<QUERY
    SELECT COALESCE(MAX(sid), -1) AS last_sid
      FROM (
        SELECT sid
          FROM {webform_submissions}
         WHERE nid = :nid
           AND sid > :sid
         LIMIT $limit
      ) AS total
QUERY;

  $args = array(
    ':nid' => $nid,
    ':sid' => $latest_submission,
  );

  $last_submission = db_query($query, $args)->fetchField();

  if ($last_submission == '-1') {
    $last_submission = $latest_submission;
  }

  return $last_submission;
}

/**
 * Returns the filename to be used when saving the file before sending to CEMHUB
 *
 * @return string
 */
function cemhub_get_new_file_name() {
  $file_sequence = variable_get('cemhub_file_sequence');
  $file_vendor_code = variable_get('cemhub_vendor_id');

  $file_name = CEMHUB_FILE_CLIENT_CODE . '_' . $file_vendor_code . '_' . CEMHUB_FILE_INDICATOR . '_' . date('Ymd') . '_' . $file_sequence;

  return $file_name;
}

/**
 * Returns a formatted file line to be sent to CEMHUB
 *
 * @param string $vendor_id
 * @param int $submission_timestamp Must be a UNIX timestamp converted by the function date("Ymd",$date)
 * @param string $campain_source
 * @param int $uii
 * @param string $survey_id
 * @param string $question_code
 * @param string $answer_code
 * @param string $value
 *
 * @return string
 */
function cemhub_build_file_line($vendor_id, $submission_timestamp, $campain_source,
                                 $uii, $survey_id, $question_code, $answer_code, $value) {
  $line = $vendor_id            . '|' .
          $submission_timestamp . '|' .
          trim($campain_source) . '|' .
          $uii                  . '|' .
          $survey_id            . '|' .
          $question_code        . '|' .
          $answer_code          . '|' .
          $value                . "|\r\n";

  return $line;
}

/**
 * Returns the UII value based on the Root UII, plus the current iteration (when
 * generating the file)
 *
 * @param string $root_uii
 * @param int $record_count
 *
 * @return string
 */
function cemhub_get_uii($root_uii, $record_count) {
  $uii = $root_uii . date('mdYHis') . str_pad($record_count, 4, '0', STR_PAD_LEFT);

  return $uii;
}

/**
 * Encrypt file and send to CEMHUB
 *
 * @param $file_name
 */
function cemhub_send_file($file_name) {
  $is_successful = FALSE;

  $encrypted_file = cemhub_encrypt_file($file_name . '.txt');
  if ($encrypted_file) {
    if (cemhub_sftp_send_file($encrypted_file->filename)) {
      $is_successful = TRUE;
      watchdog('cemhub', 'The encrypted file was successfully sent to CEMHUB: ' . $encrypted_file->filename);
    }
    else {
      module_load_include('inc', 'cemhub', 'cemhub.mail');
      $error_message = 'Failed to connect CEM SFTP';
      watchdog('cemhub', $error_message);
      cemhub_send_failure_job_email($error_message);
    }
  }

  return $is_successful;
}

/**
 * Send file to CEMHUB using a SFTP connection
 *
 * @param string $file_name
 *
 * @return boolean
 */
function cemhub_sftp_send_file($file_name) {
  $is_successful = FALSE;

  $resource = cemhub_ssh2_create_connection();
  if ($resource) {
    $sftp_stream = cemhub_open_sftp_stream($resource, $file_name);

    try {
      cemhub_sftp_write_file($sftp_stream, $file_name);
      $is_successful = TRUE;
    }
    catch (Exception $e) {
      watchdog('cemhub', 'Exception: ' . $e->getMessage());
    }

    cemhub_close_sftp_stream($sftp_stream);
  }


  return $is_successful;
}

/**
 * Write the file in remote sftp server
 *
 * @param session $sftp_stream
 * @param string $file_name
 * @throws Exception
 */
function cemhub_sftp_write_file($sftp_stream, $file_name) {
  $source_file_path = cemhub_get_files_repository_path(TRUE) . '/' . $file_name;

  if (!$sftp_stream) {
    throw new Exception('Could not open remote file.');
  }

  $data_to_send = @file_get_contents($source_file_path);
  if ($data_to_send === FALSE) {
    throw new Exception("Could not open local file: $source_file_path.");
  }

  if (@fwrite($sftp_stream, $data_to_send) === FALSE) {
    throw new Exception("Could not send data from file: $source_file_path.");
  }
}

/**
 * Closes the opened SFTP file pointer
 *
 * @param $stream
 */
function cemhub_close_sftp_stream($stream) {
  @fclose($stream);
}

/**
 * Establish a connection to a remote SSH server.
 *
 * @return resource TRUE on success, or FALSE on error.
 */
function cemhub_ssh2_create_connection() {
  $sucessfully_created = FALSE;

  $sftp_settings = cemhub_get_sftp_settings();
  $resource = @ssh2_connect($sftp_settings['address'], 22);

  if ($resource && !cemhub_ssh2_auth_pubkey_file($resource)) {
    $resource = FALSE;
  }

  return $resource;
}

/**
 * Authenticate using a public key read from a file.
 *
 * @param string $resource
 *
 * @return TRUE on success or FALSE on failure.
 */
function cemhub_ssh2_auth_pubkey_file($resource) {
  $sftp_settings = cemhub_get_sftp_settings();
  $private_path = cemhub_get_private_file_system_path(TRUE);

  return @ssh2_auth_pubkey_file(
    $resource,
    $sftp_settings['user_name'],
    $private_path . '/' . $sftp_settings['public_key'],
    $private_path . '/' . $sftp_settings['private_key'],
    $sftp_settings['passphrase']);
}

/**
 * Request the SFTP subsystem from an already connected SSH2 server.
 *
 * @param $resource
 *   An SSH connection link identifier, obtained from a call to ssh2_connect().
 *   @see cemhub_ssh2_create_connection()
 */
function cemhub_initialize_sftp_subsystem($resource) {
  return @ssh2_sftp($resource);
}

/**
 * Binds a named resource, specified by filename, to a stream.
 *
 * @param $resource
 * @param string $file_name
 */
function cemhub_open_sftp_stream($resource, $file_name) {
  $sftp_settings = cemhub_get_sftp_settings();
  $sftp = cemhub_initialize_sftp_subsystem($resource);

  return @fopen('ssh2.sftp://' . $sftp . '/' . $sftp_settings['folder_destination'] . '/' . $file_name, 'w');
}

/**
 * Updates CEMHUB with the last webform submission ids
 *
 * @param array $last_submissions_by_webform
 */
function cemhub_update_config_with_last_submission_ids($last_submissions_by_webform) {
  foreach ($last_submissions_by_webform as $nid => $last_submission_id) {
    $config = array(
      'nid' => $nid,
      'last_submission_id' => $last_submission_id,
    );
    cemhub_update_webform_config($config);
  }
}

/**
 * Deletes webform submissions in the tables: webform_submissions and webform_submitted_data
 *
 * @param $submissions
 */
function cemhub_delete_submissions($submissions) {
  if (empty($submissions) || !variable_get('cemhub_delete_entries', FALSE)) {
    watchdog('cemhub', 'Submissions were not deleted. Please verify admin interface settings for CEM HUB.');
    return FALSE;
  }

  $tables = array(
    'webform_submitted_data',
    'webform_submissions',
    'cemhub_campaign_source',
  );
  foreach ($submissions as $nid => $last_submission) {
    foreach ($tables as $table) {
      db_delete($table)
        ->condition('sid', $last_submission, '<=')
        ->condition('nid', $nid)
        ->execute();
    }
  }

  watchdog('cemhub', 'The submissions were successfully excluded');
}

/**
 * Deletes flat files with extensions .txt and .txt.pgp.
 *
 * @param $file_name
 *   The file will be removed without extension.
 *
 * @return bool TRUE on success. FALSE otherwise
 */
function cemhub_delete_flat_files($file_name) {
  if (cemhub_is_to_delete_flat_file()) {
    $extensions = array(
      '.txt',
      '.txt.pgp',
    );

    foreach ($extensions as $extension) {
      cemhub_delete_file($file_name . $extension);
    }
  }
  else {
    watchdog('cemhub', 'The flat files were not excluded. Please verify admin interface settings for CEM HUB.');
  }
}

/**
 * Encrypts the given file using PGP.
 *
 * @param $file_name
 *
 * @return File details in case of sucess. FALSE otherwise.
 */
function cemhub_encrypt_file($file_name) {
  $file_path = cemhub_get_files_repository_path(TRUE) . '/' . $file_name;

  $encrypted_content = NULL;
  $gnupg = cemhub_gnupg_create_new_instance();
  if ($gnupg) {
    $encrypted_content = $gnupg->encrypt(file_get_contents($file_path));
  }

  $encrypted_file = NULL;
  if ($encrypted_content) {
    $encrypted_file = file_save_data($encrypted_content, $file_path . '.pgp', FILE_EXISTS_REPLACE);
  }

  if ($encrypted_file) {
    watchdog('cemhub', 'The encrypted file was successfully generated');
  }
  else {
    $error_message = 'Unable to encrypt the file';
    watchdog('cemhub', $error_message);
    cemhub_send_failure_job_email($error_message);
  }

  return $encrypted_file;
}

/**
 * Returns a new pgp instantiated object
 *
 * @return $gnupg
 */
function cemhub_gnupg_create_new_instance() {
  $gnupg = NULL;

  if (extension_loaded(CEMHUB_EXTENSION_GNUPG_NAME)) {
    // Setting environment var for apache user
    $gnupg_home = drupal_get_path('module', 'cemhub') . '/.gnupg';
    putenv("GNUPGHOME={$gnupg_home}");

    // Fix temporary files creation inside module dir
    putenv('GNUPGHOME=' . variable_get('file_temporary_path', '/tmp'));

    $gnupg = new gnupg();

    // Set errormode to PHP WARNING rather than raise an exception
    $gnupg->seterrormode(GNUPG_ERROR_WARNING);

    // Import key at every encryption to not rely on GPG
    $pubkey_info = $gnupg->import(cemhub_get_pgp_public_key_content());
    $gnupg->addencryptkey($pubkey_info['fingerprint']);
    // setarmor=1 will include header information at the content
    $gnupg->setarmor(0);
  }

  return $gnupg;
}

/**
 * Returns the pgp public key content
 *
 * @return string
 */
function cemhub_get_pgp_public_key_content() {
  $public_key = cemhub_get_private_file_system_path() . '/' . variable_get('cemhub_pgp_key_name');

  return file_get_contents($public_key);
}

/**
 * Returns all the webform submissions since the last submission id passed as argument
 *
 * @param int $webform_nid
 * @param int $last_submission_id
 *
 * @return array
 */
function cemhub_get_webform_submissions_since_last_submission_id($webform_nid, $last_submission_id) {
  $limit_per_day = cemhub_get_limit_submissions_per_day($webform_nid);

  $webform_submissions = db_select('webform_submissions', 's')
    ->fields('s', array('nid', 'sid', 'submitted'))
    ->condition('s.sid', $last_submission_id, '>')
    ->condition('s.nid', $webform_nid, '=')
    ->range(0, $limit_per_day)
    ->execute()
    ->fetchAll();

  return $webform_submissions;
}

/**
 * Returns all the data of a webform submission
 *
 * @param int $webform_nid
 * @param int $submission_id
 *
 * @return DatabaseStatementInterface
 */
function cemhub_get_webform_submission_fields_as_result_set($webform_nid, $submission_id) {
  $query = db_select('webform_submitted_data', 'w');
  $query->leftJoin('cemhub_campaign_source', 's', 's.sid = w.sid');
  $query->join('cemhub_fields', 'f', 'f.cid = w.cid');
  $query->join('webform_component', 'c', 'c.cid = w.cid AND c.nid = f.nid');
  $query->fields('w', array('data'))
    ->fields('s', array('campaign'))
    ->fields('f', array('question_code', 'answer_code'))
    ->fields('c', array('form_key'))
    ->condition('f.nid', $webform_nid, '=')
    ->condition('f.active', 1, '=')
    ->condition('w.sid', $submission_id, '=');

  $result_set = $query->execute();

  return $result_set;
}
