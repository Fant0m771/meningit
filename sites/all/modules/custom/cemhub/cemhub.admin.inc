<?php
/**
 * @file
 * Forms to manage settings on the CEMHUB administration
 */

/**
 * Form constructor for the CEM HUB registration.
 *
 * @param array $form
 * @param array $form_state
 */
function cemhub_vendor_registration($form, &$form_state) {
  cemhub_check_required_environment_settings();

  $file_private_path = cemhub_get_private_file_system_path();
  if ($file_private_path) {
    // Vendor settings
    $form['vendor_settings'] = array(
      '#type' => 'fieldset',
      '#title' => t('Vendor Detail'),
      '#collapsible' => TRUE,
    );

    $form['vendor_settings']['cemhub_vendor_id'] = array(
      '#type' => 'textfield',
      '#title' => t('Vendor Code'),
      '#maxlength' => 3,
      '#size' => 3,
      '#default_value' => variable_get('cemhub_vendor_id'),
      '#description' => t('An alpha code provided by HUB team.'),
      '#required' => TRUE,
    );

    $form['vendor_settings']['cemhub_organization_code'] = array(
      '#type' => 'textfield',
      '#title' => t('UII Root'),
      '#maxlength' => 6,
      '#size' => 6,
      '#default_value' => variable_get('cemhub_organization_code'),
      '#description' => t('This number is used to build the 24-digit "UII".'),
      '#required' => TRUE,
    );

    // Campaign tracking
    $form['campaign_tracking'] = array(
      '#type' => 'fieldset',
      '#title' => t('Campaign Tracking'),
      '#collapsible' => TRUE,
    );

    $form['campaign_tracking']['cemhub_cookies_enabled'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use cookie instead of session.'),
      '#default_value' => variable_get('cemhub_cookies_enabled'),
      '#description' => t('By default, the campaign is tracked by session verification, but some environments may present some instability to set SESSION. Keep this box checked if you do not sure about it.'),
      '#collapsible' => TRUE,
    );

    $form['campaign_tracking']['cemhub_cookie_time'] = array(
      '#title' => t('Cookie expire time'),
      '#description' => t('The time the cookie expires, in minutes. <strong>Recommended: If set to 0 (zero), the cookie will expire at the end of the session (when the browser closes</strong>).'),
      '#type' => 'textfield',
      '#maxlength' => 3,
      '#size' => 3,
      '#default_value' => variable_get('cemhub_cookie_time', 0),
    );

    $form['campaign_tracking']['cemhub_external_campaign_parameters'] = array(
      '#type' => 'textarea',
      '#title' => t('Possible external campaign parameter names'),
      '#description' => t('Set one value per row.<br/>
                          The value of the campaign Source ID may be given externally, passing the value by GET method, example: www.website.com?source=CENW10025942'),
      '#default_value' => variable_get('cemhub_external_campaign_parameters'),
    );

    // File settings
    $form['file_settings'] = array(
      '#type' => 'fieldset',
      '#title' => t('File'),
      '#collapsible' => TRUE,
    );

    $form['file_settings']['cemhub_file_sequence'] = array(
      '#type' => 'textfield',
      '#title' => t('File Sequence Number'),
      '#description' => t('Fix the file sequence number to avoid conflict between files sent for different sites in the same day.'),
      '#field_prefix' => CEMHUB_FILE_CLIENT_CODE . '_' . variable_get('cemhub_vendor_id', 'XYZ') . '_' . CEMHUB_FILE_INDICATOR . '_' . date('Ymd') . '_',
      '#default_value' => variable_get('cemhub_file_sequence'),
      '#field_suffix' => '.txt.pgp',
      '#maxlength' => 3,
      '#size' => 3,
      '#required' => TRUE,
    );

    $form['file_settings']['cemhub_repository_files'] = array(
      '#type' => 'textfield',
      '#title' => t('Temporary repository Files'),
      '#field_prefix' => $file_private_path ? $file_private_path . '/' : '',
      '#description' => t('Folder where the .txt and the encrypted files will be generated in Drupal Private file system path. Ex.: cemhub/files'),
      '#default_value' => variable_get('cemhub_repository_files'),
      '#maxlength' => 100,
      '#required' => TRUE,
    );

    // SFTP settings
    $sftp_settings = cemhub_get_sftp_settings();
    $form['sftp_settings'] = array(
      '#type' => 'fieldset',
      '#title' => t('SFTP'),
      '#collapsible' => TRUE,
    );

    $form['sftp_settings']['cemhub_sftp_address'] = array(
      '#type' => 'textfield',
      '#title' => t('SFTP Address'),
      '#description' => t('The address of the SFTP server that will receive the files.'),
      '#default_value' => $sftp_settings['address'],
      '#maxlength' => 100,
      '#required' => TRUE,
    );

    $form['sftp_settings']['cemhub_destination_repository_files'] = array(
      '#type' => 'textfield',
      '#title' => t('File destination repository'),
      '#description' => t('Folder in SFTP server where the encrypted files will be transferred. Ex.: home/pfizvendor/Inbound'),
      '#default_value' => $sftp_settings['folder_destination'],
      '#maxlength' => 100,
      '#required' => TRUE,
    );

    $form['sftp_settings']['cemhub_sftp_userid'] = array(
      '#type' => 'textfield',
      '#title' => t('SFTP User name'),
      '#default_value' => $sftp_settings['user_name'],
      '#maxlength' => 50,
      '#size' => 7,
      '#required' => TRUE,
    );

    $form['sftp_settings']['cemhub_sftp_pass_ppk'] = array(
      '#type' => 'textfield',
      '#title' => t('SFTP Passphrase'),
      '#default_value' => $sftp_settings['passphrase'],
      '#maxlength' => 50,
      '#size' => 20,
      '#required' => TRUE,
    );

    $form['sftp_settings']['cemhub_sftp_public_key'] = array(
      '#type' => 'textfield',
      '#title' => t('SFTP Public Key Path'),
      '#field_prefix' => $file_private_path ? $file_private_path . '/' : '',
      '#default_value' => $sftp_settings['public_key'],
      '#description' => t('The location of the Public key from Drupal Private file system path. <br/> Notice: The public key, MUST be in OpenSSH authorized_keys file format.<br>Ex. path: cemhub/publickey.pub'),
      '#required' => TRUE,
    );

    $form['sftp_settings']['cemhub_sftp_private_key'] = array(
      '#type' => 'textfield',
      '#title' => t('SFTP Private Key Path'),
      '#field_prefix' => $file_private_path ? $file_private_path . '/' : '',
      '#default_value' => $sftp_settings['private_key'],
      '#description' => t('The location of the PPK Key from Drupal Private file system path.<br/> Notice: The public key, MUST be in OpenSSH format.<br> Ex. path: cemhub/privatekey.ppk'),
      '#required' => TRUE,
    );

    // PGP settings
    $form['pgp_settings'] = array(
      '#type' => 'fieldset',
      '#title' => t('PGP Encryption'),
      '#collapsible' => TRUE,
    );

    $form['pgp_settings']['cemhub_pgp_key_name'] = array(
      '#type' => 'textfield',
      '#title' => t('PGP CEM Public Key Name'),
      '#field_prefix' => $file_private_path ? $file_private_path . '/' : '',
      '#default_value' => variable_get('cemhub_pgp_key_name'),
      '#description' => t('The location of the CEM Key from Drupal Private file system path<br>Ex. path: cemhub/pgpkey.ppk'),
      '#required' => TRUE,
    );

    $form['#validate'][] = 'cemhub_vendor_registration_form_validate';
    $form['#submit'][] = 'cemhub_vendor_registration_treats_requirements';

    return system_settings_form($form);
  }
}

/**
 * Helper function Validator for Admin form
 *
 * @param array $form
 * @param array $form_state
 */
function cemhub_vendor_registration_form_validate($form, &$form_state){
  if ((bool)$form_state['values']['cemhub_cookies_enabled']) {
    $cookie_time = $form_state['values']['cemhub_cookie_time'];

    if (!preg_match('/^[0-9]+$/', $cookie_time)) {
      form_set_error('cemhub_cookie_time', t('Cookie time needs to be a number.'));
    }
  }
}

/**
 * Additional Form submit to treats the environment requirements
 *
 * @param array $form
 * @param array $form_state
 */
function cemhub_vendor_registration_treats_requirements($form, $form_state) {
  // If the directory does not exist, it is created
  cemhub_get_files_repository_path();
}

/**
 * Form constructor for the Email notification
 *
 * @param array $form
 * @param array $form_state
 */
function cemhub_form_email_alerts($form, &$form_state) {
  cemhub_check_required_environment_settings();

  $form['email_integration'] = array(
    '#type' => 'fieldset',
    '#title' => t('Integration'),
    '#collapsible' => TRUE,
  );

  $form['email_case'] = array(
    '#type' => 'fieldset',
    '#title' => t('Send E-mail in case'),
    '#description' => t('Check each case of job result you want to get e-mail.'),
    '#collapsible' => TRUE,
  );

  $form['email_configuration'] = array(
    '#type' => 'fieldset',
    '#title' => t('E-mail Configuration'),
    '#collapsible' => TRUE,
  );

  $form['email_configuration']['email_configuration_success'] = array(
    '#type' => 'fieldset',
    '#title' => t('Success'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['email_configuration']['email_configuration_failure'] = array(
    '#type' => 'fieldset',
    '#title' => t('Failure'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['email_configuration']['email_configuration_no_submissions'] = array(
    '#type' => 'fieldset',
    '#title' => t('No Submissions'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['email_integration']['cemhub_email_integration_cron_job'] = array(
    '#type' => 'checkbox',
    '#title' => t('Cron Job'),
    '#default_value' => variable_get('cemhub_email_integration_cron_job'),
    '#description' => t('Send e-mails for Cem Hub Jobs performed by system Cron'),
  );

  $form['email_case']['cemhub_email_case_success'] = array(
    '#type' => 'checkbox',
    '#title' => t('Success'),
    '#default_value' => variable_get('cemhub_email_case_success', FALSE),
    '#description' => t('When the file is successfully sent'),
  );

  $form['email_case']['cemhub_email_case_failure'] = array(
    '#type' => 'checkbox',
    '#title' => t('Failure'),
    '#default_value' => variable_get('cemhub_email_case_failure', FALSE),
    '#description' => t('When it was not possible to send the file. Errors are described in the e-mail'),
  );

  $form['email_case']['cemhub_email_case_no_submissions'] = array(
    '#type' => 'checkbox',
    '#title' => t('No submissions to send'),
    '#default_value' => variable_get('cemhub_email_case_no_submissions', FALSE),
    '#description' => t('When no submissions to be sent'),
  );

  $form['email_configuration']['cemhub_email_from'] = array(
    '#type' => 'textfield',
    '#title' => t('Name From'),
    '#default_value' => variable_get('cemhub_email_from'),
    '#description' => t('The e-mail address to which the message should be sent'),
    '#weight' => -1,
  );

  $form['email_configuration']['cemhub_email_recipient'] = array(
    '#type' => 'textfield',
    '#title' => t('Recipient'),
    '#default_value' => variable_get('cemhub_email_recipient'),
    '#description' => t('The e-mail address to which the message should be sent'),
    '#weight' => -2,
  );

  $form['email_configuration']['email_configuration_success']['cemhub_email_subject_success'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject'),
    '#default_value' => variable_get('cemhub_email_subject_success'),
    '#description' => t('The subject of the message. You can use the tokens:<br/>
                        [sitename] - Display the site name<br/>
                        [siteurl]  - Display the site Url'),
  );

  $form['email_configuration']['email_configuration_success']['cemhub_email_message_success'] = array(
    '#type' => 'textarea',
    '#title' => t('Success Message e-mail body'),
    '#default_value' => variable_get('cemhub_email_message_success'),
    '#description' => t('The default message to be displayed in the e-mail body in case of success. <br>You can use the tokens:<br/>
                        [sitename] - Display the site name<br/>
                        [siteurl]  - Display the site Url'),
  );

  $form['email_configuration']['email_configuration_failure']['cemhub_email_subject_failure'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject'),
    '#default_value' => variable_get('cemhub_email_subject_failure'),
    '#description' => t('The subject of the message. You can use the tokens:<br/>
                        [sitename] - Display the site name<br/>
                        [siteurl]  - Display the site Url'),
  );

  $form['email_configuration']['email_configuration_failure']['cemhub_email_message_failure'] = array(
    '#type' => 'textarea',
    '#title' => t('Failure Message e-mail body'),
    '#default_value' => variable_get('cemhub_email_message_failure'),
    '#description' => t('The default message to be displayed in the e-mail body in case of Failure. <br/>
                        You can use the tokens:<br/>
                        [sitename] - Display the site name<br/>
                        [siteurl]  - Display the site Url<br/>
                        [errorlog] - Display the log of the error'),
  );

  $form['email_configuration']['email_configuration_no_submissions']['cemhub_email_subject_no_submissions'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject'),
    '#default_value' => variable_get('cemhub_email_subject_no_submissions'),
    '#description' => t('The subject of the message. You can use the tokens:<br/>
                        [sitename] - Display the site name<br/>
                        [siteurl]  - Display the site Url'),
  );

  $form['email_configuration']['email_configuration_no_submissions']['cemhub_email_message_no_submissions'] = array(
    '#type' => 'textarea',
    '#title' => t('No Submissions Message e-mail body'),
    '#default_value' => variable_get('cemhub_email_message_no_submissions'),
    '#description' => t('The default message to be displayed in the e-mail body in case of no submissions. <br/>
                        You can use the tokens:<br/>
                        [sitename] - Display the site name<br/>
                        [siteurl]  - Display the site Url'),
  );

  return system_settings_form($form);
}

/**
 * Form constructor for the CEM HUB Integration Settings.
 *
 * @param array $form
 * @param array $form_state
 *
 * @return array
 */
function cemhub_integration_settings_form($form, &$form_state){
  cemhub_check_required_environment_settings();

  if (cemhub_get_private_file_system_path()) {
    $form['integration_settings'] = array(
      '#type' => 'fieldset',
      '#title' => t('Integration Settings'),
    );

    $form['integration_settings']['cemhub_batch_run_time'] = array(
      '#type' => 'select',
      '#title' => t('Run the Daily Batch Process as:'),
      '#options' => cemhub_get_batch_run_time_options(),
      '#default_value' => variable_get('cemhub_batch_run_time', '04'),
      '#description' => t('Time is allowed to run the batch process to generate and send the file to CEM HUB during the Drupal Cron.<br/>
                          Notifying that the hour to send the file for vendors must occur 4AM EST.<br/>
                          You must configure the CRONTAB on the Web Server to call the cron.php file in the Drupal folder at the same time that is selected here.'),
      '#required' => TRUE,
    );

    $form['integration_settings']['cemhub_integration_enabled'] = array(
      '#type' => 'checkbox',
      '#prefix' => t('<b>Integration with HUB</b>'),
      '#title' => t('Enable Integration with HUB to generate the file and submit it through the SFTP channel.'),
      '#default_value' => variable_get('cemhub_integration_enabled', FALSE),
      '#description' => t('Very careful with this configuration. Only enable it if you are sure that the integration with HUB and all the configuration fields above are correctly working.'),
    );

    $form['integration_settings']['cemhub_delete_flatfile'] = array(
      '#type' => 'checkbox',
      '#prefix' => t('<strong>Flat files</strong>'),
      '#title' => t('Delete the flat files (.txt, .txt.pgp) after the process is completed.'),
      '#default_value' => cemhub_is_to_delete_flat_file(),
      '#description' => t('Leave unchecked if you want to persist the files in the %repository folder.', array('%repository' => variable_get('cemhub_repository_files'))),
    );

    $form['integration_settings']['cemhub_delete_entries'] = array(
      '#type' => 'checkbox',
      '#prefix' => t('<b>Database entries</b>'),
      '#title' => t('Delete the entries at the database after generating the flat file.'),
      '#default_value' => variable_get('cemhub_delete_entries', FALSE),
    );

    $form['integration_settings']['cemhub_last_cron_run'] = array(
      '#type' => 'textfield',
      '#title' => t('Last integration by Cron'),
      '#description' => t('Timestamp of the last successful integration performed by Cron. Format: YYYYMMDD.<br>Leave blank if you want to reset.'),
      '#default_value' => variable_get('cemhub_last_cron_run'),
      '#maxlength' => 8,
      '#size' => 20,
    );

    return system_settings_form($form);
  }
}

/**
 * Form constructor for the webforms Settings.
 * This form define which webforms will be integrated with CEM HUB
 *
 * @param array $form
 * @param array $form_state
 *
 * @return array
 */
function cemhub_forms_settings_form($form, &$form_state){
  cemhub_check_required_environment_settings();

  if (cemhub_get_private_file_system_path()) {
    $available_webforms = cemhub_get_available_webforms();

    $webforms_to_update = array();
    foreach ($available_webforms as $webform) {
      $nid = $webform->nid;
      $webfom_title = 'Webform: ' . $webform->title . ' (nid ' . $nid . ')';
      $webforms_to_update[] = $nid;

      $integrated_webforms = cemhub_get_integrated_webform_settings_by_node_id($nid);
      $webform_config = !empty($integrated_webforms) ? get_object_vars($integrated_webforms) : NULL;

      $form['form_nid' . $nid . '_fieldset'] = array(
        '#type' => 'fieldset',
        '#title' => check_plain($webfom_title),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );

      $form['form_nid' . $nid . '_fieldset']['campaign'] = array(
        '#type' => 'fieldset',
        '#title' => 'Campaign',
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
      );

      $form['form_nid' . $nid . '_fieldset']['integration'] = array(
        '#type' => 'fieldset',
        '#title' => 'Integration',
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
      );

      $form['form_nid' . $nid . '_fieldset']['campaign']['cemhub_form_nid' . $nid . '_campaign_source'] = array(
        '#type' => 'textfield',
        '#title' => t('Default Campaign Source ID'),
        '#size' => 25,
        '#maxlength' => 25,
        '#default_value' => isset($webform_config['campaign_source']) ? $webform_config['campaign_source'] : '',
        '#description' => t('The CEM Campaign ID that is related to this Webform'),
      );

      $form['form_nid' . $nid . '_fieldset']['campaign']['cemhub_form_nid' . $nid . '_external_campaign_source'] = array(
        '#type' => 'textarea',
        '#title' => t('Allowed External Campaign Source ID'),
        '#default_value' =>  isset($webform_config['external_campaign_source']) ? $webform_config['external_campaign_source'] : '',
        '#description' => t('Enter the possible values ​​for the external campaign source ID, one per row. <br/>
                            The value of the campaign Source ID may be given externally,
                            passing the value by GET method, example: www.website.com?source=CENW10025942<br/>
                            You can view the possible names to the GET parameter, access the <strong>"General settings" tab</strong>'),
      );

      $form['form_nid' . $nid . '_fieldset']['campaign']['cemhub_form_nid' . $nid . '_survey_id'] = array(
        '#type' => 'textfield',
        '#title' => t('Survey ID'),
        '#size' => 6,
        '#maxlength' => 6,
        '#default_value' => isset($webform_config['survey_id']) ? $webform_config['survey_id'] : '',
        '#description' => t('The CEM Survey ID that is related to this Webform'),
      );

      $form['form_nid' . $nid . '_fieldset']['integration']['cemhub_form_nid' . $nid . '_last_submission_id'] = array(
        '#type' => 'textfield',
        '#title' => t('Last webform entry that was submitted'),
        '#default_value' => empty($webform_config['last_submission_id']) ? '-1' : $webform_config['last_submission_id'],
        '#size' => 10,
        '#description' => t('You can reset that value to -1 if you want to submit all entries again to the HUB, but this flag is the tracking about what was already sent.'),
      );

      $form['form_nid' . $nid . '_fieldset']['integration']['cemhub_form_nid' . $nid . '_limit_submissions'] = array(
        '#type' => 'textfield',
        '#title' => t('Limit of UII Submissions per day'),
        '#description' => t('Limit of submissions per day. The default value is 9999.<br/>
                            Care to change this field: If the records exceed the expected limit, all the records starting from the limit number will be rejected.'),
        '#default_value' => cemhub_get_limit_submissions_per_day($nid),
        '#maxlength' => 10,
        '#size' => 10,
      );

      $form['form_nid' . $nid . '_fieldset']['integration']['cemhub_form_nid' . $nid . '_active'] = array(
        '#type' => 'checkbox',
        '#prefix' => '<b>Integration</b>',
        '#title' => t('Enable Integration with HUB'),
        '#default_value' => isset($webform_config['active']) ? $webform_config['active'] : 0,
        '#description' => t('All Submissions of this form will be sent to the CEM HUB'),
      );
    }

    $form['cemhub_update_nid_list'] = array(
      '#type' => 'hidden',
      '#value' => $webforms_to_update,
    );

    $form['actions']['submit'] = array(
      '#type'  => 'submit',
      '#value' => t('Save Settings'),
    );

    return $form;
  }
}

/**
 * Form Submit for the webforms Settings.
 *
 * @param array $form
 * @param array $form_state
 */
function cemhub_forms_settings_form_submit($form, &$form_state){
  form_state_values_clean($form_state);

  $webforms_to_update = $form_state['values']['cemhub_update_nid_list'];
  foreach ($webforms_to_update as $nid) {
    $integrate_data = cemhub_forms_settings_formats_data_to_database_integration($form_state, $nid);

    $webform_already_exists = cemhub_get_integrated_webform_settings_by_node_id($nid);
    if ($webform_already_exists) {
      // Update existing
      cemhub_update_webform_config($integrate_data);
    }
    else {
      // Create new entry in table
      cemhub_insert_new_entry_of_webform_config($integrate_data);
    }
  }

  drupal_set_message(t('Fields have been successfully saved'));
}

/**
 * Form constructor to CEMHUB Jobs
 * Force to Run a Job or view the generated flat files.
 *
 * @param array $form
 * @param array $form_state
 */
function cemhub_form_jobs($form, &$form_state){
  // Run Job Now
  $form['run_job'] = array(
    '#type' => 'fieldset',
    '#title' => t('Run Job'),
    '#collapsible' => TRUE,
    '#description' => t('Use this button to executes a Job Instantly.'),
  );

  $form['run_job']['run_now'] = array(
    '#type' => 'button',
    '#value' => t('Run Job Now'),
    '#name' => 'run_job_now',
    '#executes_submit_callback' => TRUE,
    '#disabled' => cemhub_check_required_environment_settings() ? FALSE : TRUE,
  );

  // Generated Files
  $form['generated_files'] = array(
    '#type' => 'fieldset',
    '#title' => t('Flat files'),
    '#collapsible' => TRUE,
  );

  $generated_files = cemhub_get_generated_flat_files();
  $table_rows = array();
  foreach ($generated_files as $file_path => $file_details) {
    $table_rows['cemhub_files_' . $file_details->name] = array(
      'mark_to_delete' => array(
        'data' => array(
          '#type' => 'checkbox',
          '#name'  => $file_details->filename,
          '#checked' => FALSE,
        ),
      ),
      'file_name' => l($file_details->filename, CEMHUB_MENU_CALLBACK_DOWNLOAD_FLAT_FILE . '/' . $file_details->filename),
      'file_size' => number_format(filesize($file_path) / 1024, 2) . ' KB',
      'file_date' => date('F d, Y', filemtime($file_path)),
    );
  }

  $form['generated_files']['cemhub_fields'] = array(
    '#theme' => 'table',
    '#header' => array(
      'mark_to_delete' => '#',
      'file_name' => t('File Name'),
      'file_size' => t('Size'),
      'file_date' => t('Date'),
    ),
    '#rows' => $table_rows,
    '#empty' => t('No files available.'),
  );

  if (!empty($generated_files)) {
    $form['generated_files']['delete_files'] = array(
      '#type' => 'button',
      '#value' => t('Delete'),
      '#name' => 'delete_files',
      '#executes_submit_callback' => TRUE,
    );
  }

  return $form;
}

/**
 * Form submit handler
 *
 * @see cemhub_form_jobs()
 *
 * @param array $form
 * @param array $form_state
 */
function cemhub_form_jobs_submit($form, &$form_state) {
  $button_clicked = $form_state['triggering_element']['#name'];
  switch ($button_clicked) {
    case 'run_job_now':
      // Process a new submission
      module_load_include('inc', 'cemhub', 'cemhub.submission');
      cemhub_process_submissions();
      drupal_set_message(t('The Job was executed successfully. To more details, check the watchdog.'));
      break;

    case 'delete_files':
      cemhub_delete_flat_files_selected_for_deletion($form_state);
      break;
  }
}

/**
 * Deletes selected flat files by form
 *
 * @param array $form_state
 */
function cemhub_delete_flat_files_selected_for_deletion($form_state) {
  $deleted_files = cemhub_get_flat_files_selected_for_deletion($form_state);
  foreach ($deleted_files as $file_path => $file_details) {
    cemhub_delete_file($file_details->filename);
  }

  drupal_set_message(t('The selected files were deleted.'));
}

/**
 * Returns an array with the selected files for deletion
 *
 * @param array $form_state
 */
function cemhub_get_flat_files_selected_for_deletion($form_state) {
  $generated_files = cemhub_get_generated_flat_files();

  $deleted_files = array();
  foreach ($generated_files as $file_path => $file_details) {
    if(array_key_exists(str_replace('.', '_', $file_details->filename), $form_state['input'])) {
      $deleted_files[$file_path] = $file_details;
    }
  }

  return $deleted_files;
}

/**
 * Form for listing the webform fields for mapping the fields of CEMHUB
 */
function cemhub_mapping_fields() {
  cemhub_check_required_environment_settings();

  if (cemhub_get_private_file_system_path()) {
    $webforms_to_update = array();

    $enabled_webforms = cemhub_get_integrated_activated_webforms_settings();
    if (!empty($enabled_webforms)) {
      foreach ($enabled_webforms as $webform) {
        $webform = node_load($webform->nid);
        $webforms_to_update[] = $webform->nid;

        cemhub_sync_tables($webform->nid);

        $form['fields_table_nid' . $webform->nid] = array(
          '#type' => 'fieldset',
          '#description' => t('Defines the <strong>question codes</strong> and the <strong>answers codes</strong> of the fields that will be sent to CEMHUB.'),
          '#title' => t('Webform: %webform_title (NID %webform_nid)', array('%webform_title' => $webform->title, '%webform_nid' => $webform->nid)),
          '#collapsible' => TRUE,
          '#collapsed'   => TRUE,
        );

        $cemhub_fields = cemhub_get_mapped_webform_fields_by_nid($webform->nid);

        $table_rows = array();
        foreach ($cemhub_fields as $field) {
          $field_properties =  cemhub_get_webform_field_properties($webform->nid, $field->cid);

          $table_rows['cemhub_fields_cid' . $field->cid . 'nid_' . $webform->nid] = array(
            'user_field' => $field_properties['form_key'],
            'question_code' =>  array(
              'data' => array(
                '#type' => 'textfield',
                '#name'  => 'cid_' . $field->cid . '_nid' . $webform->nid . '_question',
                '#value' => $field->question_code,
                '#size' => 6,
                '#maxlength' => 6,
              ),
            ),
            'answer_code' =>  array(
              'data' => array(
                '#type' => ($field_properties['type'] == 'select') ? 'textarea' : 'textfield',
                '#name'  => 'cid_' . $field->cid . '_nid' . $webform->nid . '_answer',
                '#value' => $field->answer_code,
                '#description' => ($field_properties['type'] == 'select') ? t('The default value in case of multiple values is the first row. Ex.: default_value|answer') : '',
                '#size' => 6,
                '#maxlength' => 6,
              ),
            ),
            'status' => array(
              'data' => array(
                '#type' => 'checkbox',
                '#name'  => 'cid_' . $field->cid . '_nid' . $webform->nid . '_status',
                '#checked' => $field->active ? TRUE : FALSE,
              ),
            ),
          );
        }

        // Table header
        $form['fields_table_nid' . $webform->nid]['cemhub_fields'] = array(
          '#theme' => 'table',
          '#header' => array(
            'user_field'    => t('Webform Field Key'),
            'question_code' => t('Question Code'),
            'answer_code'   => t('Answer Code'),
            'status'        => t('Status'),
          ),
          '#rows' => $table_rows,
          '#empty' => t('No content available.'),
          '#weight' => 7,
        );
      }

      $form['cemhub_webforms_to_update'] = array(
        '#type' => 'hidden',
        '#value' => $webforms_to_update,
      );

      $form['actions']['submit'] = array(
        '#type'  => 'submit',
        '#value' => t('Save Table'),
      );

      return $form;

    }
    else {
      drupal_set_message(t('No webform has been integrated. Access the tab: "FORMS SETTINGS"'), 'warning');
    }
  }
}

/**
 * Form Submit for cemhub_mapping_fields
 *
 * @see cemhub_mapping_fields()
 *
 * @param array $form
 * @param array $form_state
 */
function cemhub_mapping_fields_submit($form, &$form_state) {
  form_state_values_clean($form_state);

  $webforms_to_update = $form_state['values']['cemhub_webforms_to_update'];

  foreach ($webforms_to_update as $nid) {
    $cemhub_fields = cemhub_get_mapped_webform_fields_by_nid($nid);

    if (!empty($cemhub_fields)) {
      foreach ($cemhub_fields as $field) {
        $question_code = $form_state['input']['cid_' . $field->cid . '_nid' . $nid . '_question'];
        $answer_code   = $form_state['input']['cid_' . $field->cid . '_nid' . $nid . '_answer'];
        $active        = isset($form_state['input']['cid_' . $field->cid . '_nid' . $nid . '_status']) ? 1 : 0;

        cemhub_update_webform_fields_mapping(
          $field->cid,
          $nid,
          $question_code,
          $answer_code,
          $active
        );
      }
    }
  }

  drupal_set_message(t('Fields have been successfully saved'));
}
