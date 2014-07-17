<?php
/**
 * @file
 * Common functions used by CEMHUB module
 */

/**
 * Returns an array containing the configuration of integrated webforms.
 *
 * @return array $webforms
 */
function cemhub_get_integrated_webforms_settings() {
  $webforms = cemhub_retrieve_integrated_webforms_settings();

  return $webforms;
}

/**
 * Returns an array containing the configuration of all activated integrated webforms.
 *
 * @return array $active_webforms
 */
function cemhub_get_integrated_activated_webforms_settings() {
  $webforms_settings = cemhub_retrieve_integrated_webforms_settings();

  $active_webforms = array();
  foreach ($webforms_settings as $webform) {
    if (!empty($webform->active)) {
      $active_webforms[$webform->nid] = $webform;
    }
  }

  return $active_webforms ? $active_webforms : NULL;
}

/**
 * Returns the settings of a integrated webform.
 *
 * @param int $node_id
 * @return Ambigous <NULL, array>
 */
function cemhub_get_integrated_webform_settings_by_node_id($node_id) {
  $webforms = cemhub_get_integrated_webforms_settings();

  return isset($webforms[$node_id]) ? $webforms[$node_id] : NULL;
}

/**
 * Retrive configuration of integrated webforms from static cache or from database.
 *
 * @return array $webforms
 */
function cemhub_retrieve_integrated_webforms_settings() {
  $cache = &drupal_static(__FUNCTION__);

  if ($cache) {
    $webforms = $cache;
  }
  else {
    // For the first call, get all results and set in cache.
    $db_select = db_select('cemhub_forms_config', 'cf')->fields('cf');
    $webforms = $db_select->execute()->fetchAll();

    // Places the index of the array as webform nid.
    $webforms_rows_by_nid = array();
    foreach ($webforms as $webform) {
      $webforms_rows_by_nid[$webform->nid] = $webform;
    }
    $webforms = $webforms_rows_by_nid;

    if (!empty($webforms)) {
      // set cache
      $cache = $webforms;
    }
  }

  return $webforms;
}

/**
 * Returns TRUE if the given webform is integrated with CEMHUB, FALSE otherwise.
 *
 * @param int $nid
 * @return boolean
 */
function cemhub_is_webform_integrated($nid) {
  $webform_settings = cemhub_get_integrated_webform_settings_by_node_id($nid);

  return !empty($webform_settings->active) ? TRUE : FALSE;
}

/**
 * Returns whether or not the CEMHUB integration is enabled.
 * @return bool
 */
function cemhub_is_integration_enabled() {
  return (bool)variable_get('cemhub_integration_enabled', FALSE);
}

/**
 * Returns whether or not the set cookie for caimpaing value is enabled.
 * @return bool
 */
function cemhub_campaign_tracking_use_cookie_instead_session() {
  return (bool)variable_get('cemhub_cookies_enabled');
}

/**
 * Updates the CEMHUB configuration table.
 *
 * @param array $webform_config
 */
function cemhub_update_webform_config($webform_config) {
  db_update('cemhub_forms_config')
    ->fields($webform_config)
    ->condition('nid', $webform_config['nid'], '=')
    ->execute();
}

/**
 * Return the limit of submissions per day expected by the CEM HUB by webform.
 *
 * @param int $webform_nid
 * @return integer $limit
 */
function cemhub_get_limit_submissions_per_day($webform_nid) {
  $webforms_settings = cemhub_get_integrated_webform_settings_by_node_id($webform_nid);
  $limit = isset($webforms_settings->limit_submissions) ? $webforms_settings->limit_submissions : CEMHUB_DEFAULT_LIMIT_SUBMISSION;

  return $limit;
}

/**
 * Saves information of integrated webform in config database table.
 *
 * @param array $webform_config
 */
function cemhub_insert_new_entry_of_webform_config($webform_config) {
  db_insert('cemhub_forms_config')
    ->fields($webform_config)
    ->execute();
}

/**
 * Checks all the required environment settings.
 *
 * @param boolean $set_message
 *   Set to TRUE if want to return a warning message in case of errors on validation
 * @param boolean $log_error
 *
 * @return boolean $return
 *   return TRUE if ALL settings are configured correctly, FALSE otherwise
 */
function cemhub_check_required_environment_settings($set_message = TRUE, $log_error = FALSE, $send_email = FALSE) {
  // Clear all error messages
  drupal_get_messages('warning');

  $return = FALSE;

  if (cemhub_get_private_file_system_path()) {

    $checked_values = array(
      cemhub_check_temporary_repository_files($set_message),
      cemhub_check_sftp_keys($set_message),
      cemhub_check_pgp_public_key($set_message),
      cemhub_check_required_php_extensions($set_message),
      cemhub_check_htaccess_in_private_system_path(),
    );

    $return = in_array(FALSE, $checked_values) ? FALSE : TRUE;
  }
  elseif ($set_message) {
    drupal_set_message(t('This module Requires Drupal Private file system path where private files will be stored. <br/> Set on: Configuration > Media > File system.'), 'error');
  }

  if (empty($return)) {
    $error_message = 'Error on integration! Some environment settings are not configured correctly. Access the module configuration page and check the environment errors.';

    if ($log_error) {
      watchdog('cemhub', $error_message);
    }

    if ($send_email) {
      module_load_include('inc', 'cemhub', 'cemhub.mail');
      cemhub_send_failure_job_email($error_message);
    }
  }

  return $return;
}

/**
 * Checks if the .htaccess file exist for private system folder.
 *
 * @return boolean
 */
function cemhub_check_htaccess_in_private_system_path($set_message = TRUE) {
  $is_created = FALSE;

  $file_private_path = variable_get('file_private_path', FALSE);
  if ($file_private_path) {
    file_create_htaccess('private://', TRUE);

    if (file_exists($file_private_path . '/.htaccess')) {
      $is_created = TRUE;
    }
    elseif ($set_message) {
      drupal_set_message(t("Security warning: Couldn't write .htaccess file."), 'warning');
    }
  }

  return $is_created;
}

/**
 * Checks if required PHP extensions are loaded.
 * If not, print warnings to the screen
 *
 * @param boolean $set_message
 *   If the parameter is TRUE and the validation fail, returns a warning message
 *
 * @param array $extensions_list
 *   An array with the required extensions
 *
 * @return array $return
 */
function cemhub_check_required_php_extensions($set_message = TRUE, $extensions_list = array(CEMHUB_EXTENSION_SSH_NAME, CEMHUB_EXTENSION_GNUPG_NAME)) {
  $return = FALSE;
  $return_extensions_status = array();

  foreach ($extensions_list as $extension) {
    $extension_loaded = extension_loaded($extension);
    $return_extensions_status[$extension] = $extension_loaded;

    if (empty($extension_loaded) && $set_message) {
      drupal_set_message(t('The extension "%extension" must be installed and enabled on the server.', array('%extension' => $extension)), 'warning');
    }
  }

  // Check results
  if (!empty($return_extensions_status)) {
    $return = in_array(FALSE, $return_extensions_status) ? FALSE : TRUE;
  }

  return $return;
}

/**
 * Checks if PGP public key exist and is readable.
 *
 * @param boolean $set_message
 *  If the parameter is TRUE and the validation fail, returns a warning message
 *
 * @return boolean $is_readable
 */
function cemhub_check_pgp_public_key($set_message = TRUE) {
  $key_location = 'private://' . variable_get('cemhub_pgp_key_name');
  $is_readable = is_readable($key_location);

  if (empty($is_readable) && $set_message) {
    drupal_set_message(t('The PGP Public Key "%key_location" does not exist or is not readable, please fix this.', array('%key_location' => $key_location)), 'warning');
  }

  return $is_readable;
}

/**
 * Checks if temporary repository files exist and is writable.
 *
 * @param boolean $set_message
 *  If the parameter is TRUE and the validation fail, returns a warning message
 *
 *  @return boolean $checked_temporary_repository
 */
function cemhub_check_temporary_repository_files($set_message = TRUE) {
  $temp_files_path = cemhub_get_files_repository_path(TRUE);
  $checked_temporary_repository = file_prepare_directory($temp_files_path);

  if (empty($checked_temporary_repository) && $set_message) {
    $message = t('Temporary repository files @path does not exist or is not writable, please fix this.',
      array('@path' => $temp_files_path));
    drupal_set_message($message, 'warning');
  }

  return $checked_temporary_repository;
}

/**
 * Checks if the SFTP keys are in their location.
 *
 * @param boolean $set_message
 * @param array $keys
 *  If the parameter is TRUE and the validation fail, returns a warning message
 *
 * @return boolean $return
 */
function cemhub_check_sftp_keys($set_message = TRUE, $keys = array('public', 'private')) {
  $return = FALSE;
  $return_key_status = array();

  foreach ($keys as $key_type) {
    $retrieved_stored_key = variable_get('cemhub_sftp_' . $key_type . '_key');
    $key_exists = $retrieved_stored_key ? file_exists('private://' . $retrieved_stored_key) : 'No variable to stored key';

    $return_key_status[$key_type] = $key_exists;

    if (empty($key_exists) && $set_message) {
      drupal_set_message(t('SFTP %key_type Key does not exist in "%retrieved_stored_key", provide the key in the correct location.', array('%key_type' => $key_type, '%retrieved_stored_key' => $retrieved_stored_key)), 'warning');
    }
  }

  // Check results
  if (!empty($return_key_status)) {
    $return = in_array(FALSE, $return_key_status) ? FALSE : TRUE;
  }

  return $return;
}

/**
 * Returns relative Drupal's private file path for the site.
 * If the first parameter is TRUE, return the absolute path.
 *
 * @param boolean $absolute_path
 *
 * @return string $return_path
 */
function cemhub_get_private_file_system_path($absolute_path = FALSE) {
  $stored_path = variable_get('file_private_path', FALSE);

  $return_path = $stored_path;

  if ($stored_path && $absolute_path) {
    $return_path = getcwd() . '/' . $stored_path;
  }

  return $return_path;
}

/**
 * Returns the local CEMHUB files repository path.
 *
 * @param boolean $drupal_internal_path
 * @return string $files_repository_path
 */
function cemhub_get_files_repository_path($drupal_internal_path = FALSE) {
  $private_files_path = cemhub_get_private_file_system_path(TRUE);
  $stored_path = variable_get('cemhub_repository_files');

  $files_repository_path = $private_files_path . '/' . $stored_path;

  // If the directory does not exist, it is created
  cemhub_create_directory($files_repository_path);

  if ($drupal_internal_path) {
    $files_repository_path = 'private://' . $stored_path;
  }

  return $files_repository_path;
}

/**
 * Returns an array with all the webforms available in the system.
 *
 * @return array $available_webforms
 */
function cemhub_get_available_webforms() {
  $available_webforms = db_select('node', 'nd')
    ->fields('nd', array('title', 'nid'))
    ->condition('type', 'webform')
    ->execute()
    ->fetchAll();

  return $available_webforms;
}

/**
 * Returns an array with the form data formatted in the format expected by functions of database
 * integration.
 *
 * @see cemhub_insert_new_entry_of_webform_config
 * @see cemhub_update_webform_config
 *
 * @param array $form_state
 * @param array $nid
 *
 * @return array $formated_data
 */
function cemhub_forms_settings_formats_data_to_database_integration($form_state, $nid) {
  $fields_names = cemhub_get_integrated_webforms_names_fields_settings();

  $formated_data = array();
  foreach ($fields_names as $key => $column) {
    if ($column != 'id' && $column != 'nid') {
      $formated_data[$column] = $form_state['values']['cemhub_form_nid' . $nid . '_' . $column];
    }
  }
  $formated_data['nid'] = $nid;

  return $formated_data;
}

/**
 * Get the name of the columns of the table form config.
 *
 * @see cemhub_forms_settings_formats_data_to_database_integration
 */
function cemhub_get_integrated_webforms_names_fields_settings() {
  $cache = &drupal_static(__FUNCTION__);

  if ($cache) {
    $fields_names = $cache;
  }
  else {
    $fields_names = db_query('SHOW COLUMNS FROM {cemhub_forms_config}')->fetchCol();

    if (!empty($fields_names)) {
      // set cache
      $cache = $fields_names;
    }
  }

  return $fields_names;
}

/**
 * Returns an array containing the 'title' and 'type' properties of the given field id (identified
 * by $component_id).
 *
 * @param int $nid The fields's parent webform nid
 * @param int $component_id Webform field component id
 * @return array
 */
function cemhub_get_webform_field_properties($nid, $component_id) {
  $field_properties = db_select('webform_component', 'wc')
    ->fields('wc', array('form_key', 'type'))
    ->condition('wc.nid', $nid, '=')
    ->condition('wc.cid', $component_id, '=')
    ->execute()
    ->fetchAssoc();

  return $field_properties;
}

/**
 * Returns the mapped webform mapped identified by CEMHUB module.
 *
 * @param int $nid webform nid
 * @return array
 */
function cemhub_get_mapped_webform_fields_by_nid($nid) {
  $fields = db_select('cemhub_fields', 'cf')
    ->fields('cf', array('cid', 'nid', 'question_code', 'answer_code', 'active'))
    ->condition('cf.nid', $nid, '=')
    ->execute();

  return $fields;
}

/**
 * Returns an array containing the options (hours) available for scheduling
 * the cron job execution time.
 *
 * @return array
 */
function cemhub_get_batch_run_time_options() {
  $hours = array();

  for ($hour = 0; $hour <= 23; $hour++) {
    $formatted_hour = str_pad($hour, 2, '0', STR_PAD_LEFT);
    $hours[$formatted_hour] = $formatted_hour . ' hr';

    if ($hour > 1) {
      $hours[$formatted_hour] .= 's';
    }
  }

  return $hours;
}

/**
 * Creates a CEMHUB mapping for the given field.
 *
 * @param int $field_cid
 * @param int $webform_nid
 * @param string $question_code
 * @param string $answer_code
 * @param int $active
 */
function cemhub_create_webform_fields_mapping($field_cid, $webform_nid, $question_code, $answer_code, $active) {
  db_insert('cemhub_fields')
    ->fields(
      array(
        'cid'           => $field_cid,
        'nid'           => $webform_nid,
        'question_code' => $question_code,
        'answer_code'   => $answer_code,
        'active'        => $active,
      )
    )
    ->execute();
}

/**
 * Updates a CEMHUB mapping for the given field
 *
 * @param int $field_cid
 * @param int $webform_nid
 * @param string $question_code
 * @param string $answer_code
 * @param int $active
 */
function cemhub_update_webform_fields_mapping($field_cid, $webform_nid, $question_code, $answer_code, $active) {
  db_update('cemhub_fields')
    ->fields(
      array(
        'question_code' => $question_code,
        'answer_code'   => $answer_code,
        'active'        => $active,
      )
    )
    ->condition('cid', $field_cid, '=')
    ->condition('nid', $webform_nid, '=')
    ->execute();
}

/**
 * Deletes the CEMHUB mapping for the given field.
 *
 * @param int $cid
 * @param int $nid
 */
function cemhub_delete_webform_field_mapping($cid, $nid) {
  db_delete('cemhub_fields')
    ->condition('cid', $cid)
    ->condition('nid', $nid)
    ->execute();
}

/**
 * Compare the two tables ({webform_component} and {cemhub_fields}) and synchronize them.
 *
 * @param webform id to compare
 */
function cemhub_sync_tables($webform_nid) {
  if (!empty($webform_nid)) {
    $webform_fields_cids = cemhub_get_webform_field_ids($webform_nid);
    $cemhub_mapped_fields_cids = cemhub_get_mapped_field_ids($webform_nid);

    $fields_to_insert = array_diff($webform_fields_cids, $cemhub_mapped_fields_cids);
    $fields_to_delete = array_diff($cemhub_mapped_fields_cids, $webform_fields_cids);

    if (!empty($fields_to_insert)) {
      foreach ($fields_to_insert as $cid_to_insert) {
        $question_code = '';
        $answer_code   = '';
        $active        = 0;

        cemhub_create_webform_fields_mapping(
          $cid_to_insert,
          $webform_nid,
          $question_code,
          $answer_code,
          $active
        );
      }
    }

    if (!empty($fields_to_delete)) {
      foreach ($fields_to_delete as $cid_to_delete) {
        cemhub_delete_webform_field_mapping($cid_to_delete, $webform_nid);
      }
    }
  }
}

/**
 * Returns the IDs of the fields that remain to the given webform.
 *
 * @param int $webform_nid
 * @return array $webform_fields_cids
 */
function cemhub_get_webform_field_ids($webform_nid) {
  $webform_fields_cids = db_select('webform_component', 'wc')
    ->fields('wc', array('cid'))
    ->condition('nid', $webform_nid, '=')
    ->execute()
    ->fetchCol();

  return $webform_fields_cids;
}

/**
 * Returns the IDs of the fields mapped by CEMHUB module.
 *
 * @param int $webform_nid
 * @return array $cemhub_mapped_fields_cids
 */
function cemhub_get_mapped_field_ids($webform_nid) {
  $cemhub_mapped_fields_cids = db_select('cemhub_fields', 'cf')
    ->fields('cf', array('cid'))
    ->condition('nid', $webform_nid, '=')
    ->execute()
    ->fetchCol();

  return $cemhub_mapped_fields_cids;
}

/**
 * Deletes all webform references from CEMHUB.
 *
 * @param int $nid
 */
function cemhub_cleanup_webform_references($nid) {
  $tables = array(
    'cemhub_forms_config',
    'cemhub_fields',
    'cemhub_campaign_source',
  );

  foreach ($tables as $table) {
    db_delete($table)->condition('nid', $nid)->execute();
  }
}

/**
 * Checks if the current time is in the same hour range specified in admin form
 * and if the integration by cron has not ran today.
 *
 * @return boolean $should_perform_job
 *  True if the integration must be performed, False otherwise
 */
function cemhub_cron_should_perform_job() {
  $last_cron_run_day = variable_get('cemhub_last_cron_run', date('Ymd', strtotime("yesterday")));
  $current_day = date('Ymd');

  $is_in_scheduled_hour_range = (variable_get('cemhub_batch_run_time') == date('H', REQUEST_TIME));
  $hasnt_ran_today = ($last_cron_run_day < $current_day);

  $should_perform_job = ($is_in_scheduled_hour_range && $hasnt_ran_today);

  return $should_perform_job;
}

/**
 * If the given directory does not exist, it is created.
 *
 * @param string $directory
 * @return boolean $return
 *   TRUE if the directory was successfully created, FALSE otherwise
 */
function cemhub_create_directory($directory) {
  $return = FALSE;

  if (!is_dir($directory)) {
    if (!mkdir($directory, 0777, TRUE)) {
      watchdog('cemhub', 'Could not create directory: {$directory}');
    }
    else {
      $return = TRUE;
    }
  }

  return $return;
}

/**
 * Returns a array with all allowed campaign source parameters.
 *
 * @return array
 */
function cemhub_get_allowed_external_campaign_parameters() {
  $possible_parameters = variable_get('cemhub_external_campaign_parameters');

  return explode("\n", $possible_parameters);
}

/**
 * Gets external Campaign source code ID by GET method
 *
 * @return string $campaign_source_id
 */
function cemhub_get_incoming_campaign_source_code_id() {
  $campaign_source_id = NULL;

  $allowed_parameters = cemhub_get_allowed_external_campaign_parameters();
  foreach ($allowed_parameters as $parameter) {
    if (array_key_exists(trim($parameter), $_GET)) {
      $campaign_source_id = $_GET[trim($parameter)];
    }
  }

  return $campaign_source_id;
}

/**
 * Gets campaign source code session value.
 *
 * @return $campaign_source
 */
function cemhub_get_campaign_source_code_session_value() {
  $campaign_source = NULL;

  if (isset($_SESSION[CEMHUB_CAMPAIGN_SOURCE_SESSION])) {
    $campaign_source = $_SESSION[CEMHUB_CAMPAIGN_SOURCE_SESSION];
  }

  return $campaign_source;
}

/**
 * Gets campaign source code cookie value.
 *
 * @return $campaign_source
 */
function cemhub_get_campaign_source_code_cookie_value() {
  $campaign_source = NULL;

  if (isset($_COOKIE[CEMHUB_CAMPAIGN_SOURCE_COOKIES])) {
    $campaign_source = $_COOKIE[CEMHUB_CAMPAIGN_SOURCE_COOKIES];
  }

  return $campaign_source;
}

/**
 * Creates cookie to store campaing ID value.
 *
 * @return bool
 */
function cemhub_campaign_tracking_generate_cookie($campaign_id) {
  $cookie_time = variable_get('cemhub_cookie_time', 0);
  if (!empty($cookie_time)) {
    $cookie_time = time() + ($cookie_time * 60);
  }

  return setcookie(CEMHUB_CAMPAIGN_SOURCE_COOKIES, $campaign_id, $cookie_time, '/');
}

/**
 * Stores the incoming campaign source code id.
 * Can be stored in a cookie or in a session, depends on the admin settings.
 */
function cemhub_store_incoming_campaign_source_code_id() {
  $campaign_source_id = cemhub_get_incoming_campaign_source_code_id();
  if ($campaign_source_id) {
    if (cemhub_campaign_tracking_use_cookie_instead_session()) {
      // Store on cookie
      cemhub_campaign_tracking_generate_cookie($campaign_source_id);
    }
    else {
      // Store on session
      cemhub_campaign_tracking_generate_session($campaign_source_id);
    }
  }
}

/**
 * Creates a session to store campaing ID value.
 *
 * @param string $campaign_source_id
 */
function cemhub_campaign_tracking_generate_session($campaign_source_id){
  $_SESSION[CEMHUB_CAMPAIGN_SOURCE_SESSION] = $campaign_source_id;
}

/**
 * Retrieves the incoming campaign source code id.
 *
 * @return NULL or string
 *   returns the cookie value or session value, NULL otherwise
 */
function cemhub_retrieve_incoming_campaign_source_code_id() {
  $cookie_value = cemhub_get_campaign_source_code_cookie_value();

  return $cookie_value ? $cookie_value : cemhub_get_campaign_source_code_session_value();
}

/**
 * Checks if the given campaign source ID is allowed to the related webform.
 *
 * @return boolean
 */
function cemhub_is_an_allowed_external_campaign_source_id($campaing_source_id, $webform_node_id) {
  $webform_settings = cemhub_get_integrated_webform_settings_by_node_id($webform_node_id);
  $allowed_external_campaign_sources = list_extract_allowed_values($webform_settings->external_campaign_source, 'list_text', FALSE);

  return in_array($campaing_source_id, $allowed_external_campaign_sources);
}

/**
 * Insert new entry for the external campaign source ID.
 *
 * @param int $node_id
 * @param int $submission_id
 * @param string $campaign_source_id
 */
function cemhub_insert_campaign_source_id_entry($node_id, $submission_id, $campaign_source_id) {
  db_insert('cemhub_campaign_source')
    ->fields(array(
      'sid' => $submission_id,
      'nid' => $node_id,
      'campaign' => $campaign_source_id,
    ))
    ->execute();
}

/**
 * Returns an array with the information of the generated files.
 *
 * @return array
 */
function cemhub_get_generated_flat_files() {
  return file_scan_directory(cemhub_get_files_repository_path(TRUE), '/.*\.txt|.pgp$/');
}

/**
 * Checks if is to delete the flat files.
 *
 * @return TRUE if is to delete, FALSE otherwise
 */
function cemhub_is_to_delete_flat_file() {
  return variable_get('cemhub_delete_flatfile', FALSE);
}

/**
 * Deletes file from Drupal's file_managed table (if exists) and the file itself.
 *
 * @param string $file_name
 *   The file that will be removed
 *
 * @return bool TRUE on success. FALSE otherwise
 */
function cemhub_delete_file($file_name) {
  $successfully_deleted = FALSE;

  $file_details = cemhub_retrieve_file_details($file_name);
  if (!empty($file_details)) {
    $successfully_deleted = file_delete($file_details, TRUE);
  }
  else {
    $repository_path = cemhub_get_files_repository_path(TRUE);
    $successfully_deleted = file_unmanaged_delete($repository_path . '/' . $file_name);
  }

  if ($successfully_deleted) {
    watchdog('cemhub', 'The file "' . $file_name . '" was deleted successfully.');
  }
  else {
    watchdog('cemhub', 'It was not possible to delete file "' . $file_name . '", checks the Drupal file log to view more details.');
  }

  return $successfully_deleted;
}

/**
 * Retrieves file details by making a request in database.
 *
 * @param string $filename
 * @return object
 */
function cemhub_retrieve_file_details($filename) {
  $file_info = db_select('file_managed', 'f')
    ->fields('f', array('fid'))
    ->condition('filename', $filename, '=')
    ->execute()
    ->fetchAssoc();

  $file = NULL;
  if (!empty($file_info['fid'])) {
    $file = file_load($file_info['fid']);
  }

  return $file;
}

/**
 * Force to download a flat file.
 *
 * @param string $file_name
 */
function cemhub_download_flat_file($file_name) {
  $file_details = cemhub_retrieve_file_details($file_name);

  if ($file_details) {
    drupal_add_http_header('Content-type', 'octet/stream');
    drupal_add_http_header('Content-disposition', "attachment; filename=" . $file_details->filename . ";");
    drupal_add_http_header('Cache-Control', 'private');
    drupal_add_http_header('Content-Length', filesize($file_details->uri));
    readfile($file_details->uri);
    drupal_exit();
  }
}

/**
 * Returns an array with the SFTP settings.
 *
 * @return array $settings
 */
function cemhub_get_sftp_settings() {
  return array(
    'address' => variable_get('cemhub_sftp_address'),
    'user_name' => variable_get('cemhub_sftp_userid'),
    'passphrase' => variable_get('cemhub_sftp_pass_ppk'),
    'public_key' => variable_get('cemhub_sftp_public_key'),
    'private_key' => variable_get('cemhub_sftp_private_key'),
    'folder_destination' => variable_get('cemhub_destination_repository_files'),
  );
}
