<?php
/**
 * @file
 * Admin settings for Pfizer Authentication module.
 */

/**
 * Form constructor for the module settings form.
 *
 * @see user_login_form_validate()
 * @see pfizer_auth_pac_error_list_validate()
 * @ingroup forms
 */
function pfizer_auth_admin_settings($form, $form_state) {

  $form['#tree'] = FALSE;

  // Configure SP settings.
  $form['pfizer_auth_sp_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Janrain Service Provider'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['pfizer_auth_sp_settings']['pfizer_auth_saml_providers'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Enabled SAML Providers'),
    '#default_value' => variable_get('pfizer_auth_saml_providers', array()),
    '#options' => array(
      'pfizer-pac' => 'Pfizer PAC',
      'pfizer-emp' => 'Pfizer EMP',
    ),
  );

  $form['pfizer_auth_sp_settings']['pfizer_auth_login_form_interface'] = array(
    '#type' => 'radios',
    '#title' => t('Login form interface'),
    '#options' => array(
      'modal' => t('Modal overlay'),
      'popup' => t('Popup window'),
    ),
    '#default_value' => variable_get('pfizer_auth_login_form_interface', 'modal'),
  );

  // Configure IDP initiated settings.
  $form['pfizer_auth_idp_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Identity Provider Initiated'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $pac_login_form_block = block_load('pfizer_auth', 'pfizer-auth-pac-login-form');
  $form['pfizer_auth_idp_settings']['idp_initiated_block_status'] = array(
    '#type' => 'item',
    '#title' => t('PAC Login form status'),
    '#markup' => $pac_login_form_block->status
      ? t('Login form is enabled. <a href="@blocks-url" title="Block settings">Configure</a>.', array('@blocks-url' => url('admin/structure/block')))
      : t('Login form is disabled. <a href="@blocks-url" title="Block settings">Configure</a>.', array('@blocks-url' => url('admin/structure/block'))),
  );

  if ($pac_login_form_block->status) {
    $form['pfizer_auth_idp_settings']['pfizer_auth_pac_default_form_style'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use default form style'),
      '#default_value' => variable_get('pfizer_auth_pac_default_form_style', FALSE),
    );

    $form['pfizer_auth_idp_settings']['pfizer_auth_pac_login_url'] = array(
      '#type' => 'textfield',
      '#title' => t('Login action URL'),
      '#default_value' => variable_get('pfizer_auth_pac_login_url', NULL),
      '#maxlength' => 500,
    );

    $form['pfizer_auth_idp_settings']['pfizer_auth_pac_login_success_url'] = array(
      '#type' => 'textfield',
      '#title' => t('Login success URL'),
      '#default_value' => variable_get('pfizer_auth_pac_login_success_url', NULL),
      '#maxlength' => 500,
      '#description' => t('Available token: [pfizer-auth:token-handler-url] Token validation callback URL.'),
    );

    $form['pfizer_auth_idp_settings']['pfizer_auth_pac_logout_url'] = array(
      '#type' => 'textfield',
      '#title' => t('Logout URL'),
      '#default_value' => variable_get('pfizer_auth_pac_logout_url', NULL),
      '#maxlength' => 500,
    );

    $form['pfizer_auth_idp_settings']['pfizer_auth_pac_register_url'] = array(
      '#type' => 'textfield',
      '#title' => t('Register URL'),
      '#default_value' => variable_get('pfizer_auth_pac_register_url', NULL),
      '#maxlength' => 500,
      '#description' => t('Available token: [pfizer-auth:token-handler-url:encoded] Token validation callback URL (encoded).'),
    );

    $error_list = variable_get('pfizer_auth_pac_error_list', array());
    $form['pfizer_auth_idp_settings']['pfizer_auth_pac_error_list'] = array(
      '#type' => 'textarea',
      '#title' => t('Error list'),
      '#default_value' => list_allowed_values_string($error_list),
      '#description' => t('Insert each error by line in the format ErrorCode|ErrorMessage.'),
      '#element_validate' => array('pfizer_auth_pac_error_list_validate'),
    );

    $form['pfizer_auth_idp_settings']['pfizer_auth_pac_error_weight'] = array(
      '#type' => 'select',
      '#title' => t('Error Element Weight'),
      '#default_value' => variable_get('pfizer_auth_pac_error_weight', 0),
      '#options' => array_combine(range(1, 5), range(1, 5)),
      '#description' => t('Set the position of error message in the login form.'),
    );

    $form['pfizer_auth_idp_settings']['pfizer_auth_whitelisted_domains'] = array(
      '#type' => 'textarea',
      '#title' => t('Error page whitelisted domains'),
      '#default_value' => variable_get('pfizer_auth_whitelisted_domains', ''),
      '#cols' => 40,
      '#rows' => 5,
      '#description' => t("Enter one domain per line. Ex: <em>pfizer.com</em>."),
    );
  }

  // Configure external URLs.
  $form['external_urls'] = array(
    '#type' => 'fieldset',
    '#title' => t('External URLs settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['external_urls']['pfizer_auth_js_url_pfizer_engage'] = array(
    '#type' => 'textfield',
    '#title' => t('Pfizer Engage script (pfizer-engage.js)'),
    '#default_value' => variable_get('pfizer_auth_js_url_pfizer_engage', NULL),
    '#attributes' => array('placeholder' => t('Leave blank to use default file.')),
    '#description' => t('Leave blank to use default file.'),
  );

  $form['external_urls']['pfizer_auth_sso_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Single Sign On'),
    '#default_value' => variable_get('pfizer_auth_sso_enabled', FALSE),
    '#description' => t('SSO allows users to log into multiple applications entering their credentials just once.'),
  );

  $states_sso_enabled = array(
    // Show the settings if SSO is enabled.
    'visible' => array(':input[name="pfizer_auth_sso_enabled"]' => array('checked' => TRUE)),
  );

  $form['external_urls']['pfizer_auth_js_url_pfizer_sso'] = array(
    '#type' => 'textfield',
    '#title' => t('Pfizer SSO script (pfizer-sso.js)'),
    '#default_value' => variable_get('pfizer_auth_js_url_pfizer_sso', NULL),
    '#attributes' => array('placeholder' => t('Leave blank to use default file.')),
    '#description' => t('Leave blank to use default file.'),
    '#states' => $states_sso_enabled,
  );

  $form['external_urls']['pfizer_auth_sso_server'] = array(
    '#type' => 'textfield',
    '#title' => t('JanRain SSO Server'),
    '#default_value' => variable_get('pfizer_auth_sso_server', 'https://dm-federate.pfizer.com'),
    '#maxlength' => 100,
  );

  $form['external_urls']['pfizer_auth_js_url_sso'] = array(
    '#type' => 'textfield',
    '#title' => t('Janrain Federate SSO (sso.js)'),
    '#default_value' => variable_get('pfizer_auth_js_url_sso', NULL),
    '#states' => $states_sso_enabled,
  );

  $form['external_urls']['pfizer_auth_js_url_xd_receiver'] = array(
    '#type' => 'textfield',
    '#title' => t('Cross Domain Receiver (xd_receiver.js)'),
    '#default_value' => variable_get('pfizer_auth_js_url_xd_receiver', NULL),
    '#states' => $states_sso_enabled,
  );

  // Drupal account settings.
  $form['drupal_account_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Drupal Account Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('To change these settings, open the <a href="@url-account" title="Account settings" target="_blank">Account settings</a>.', array('@url-account' => url('admin/config/people/accounts/settings'))),
  );

  $user_register_setting = variable_get('user_register', USER_REGISTER_VISITORS_ADMINISTRATIVE_APPROVAL);
  $user_register_options = array(
    USER_REGISTER_ADMINISTRATORS_ONLY => t('Administrators only'),
    USER_REGISTER_VISITORS => t('Visitors'),
    USER_REGISTER_VISITORS_ADMINISTRATIVE_APPROVAL => t('Visitors, but administrator approval is required'),
  );
  $form['drupal_account_settings']['user_register'] = array(
    '#type' => 'item',
    '#title' => t('Who can register accounts?'),
    '#markup' => $user_register_options[$user_register_setting],
  );

  $form['drupal_account_settings']['user_email_verification'] = array(
    '#type' => 'item',
    '#title' => t('Require e-mail verification when a visitor creates an account.'),
    '#markup' => variable_get('user_email_verification', TRUE) ? t('Yes') : t('No'),
  );

  $form['drupal_account_settings']['user_mail_register_no_approval_required_notify'] = array(
    '#type' => 'item',
    '#title' => t('Send welcome e-mail to new users.'),
    '#markup' => variable_get('user_mail_register_no_approval_required_notify', TRUE) ? t('Yes') : t('No'),
  );

  // Janrain settings.
  $form['janrain_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Janrain Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('To change these settings, open the <a href="@url-janrain" title="Janrain settings" target="_blank">Janrain settings</a>.', array('@url-janrain' => url('admin/config/people/rpx'))),
  );

  $form['janrain_settings']['pfizer_auth_segment'] = array(
    '#type' => 'textfield',
    '#title' => t('Segment'),
    '#default_value' => variable_get('pfizer_auth_segment', 'Pfizer_com_idp_pfizer_auth'),
    '#maxlength' => 100,
  );

  $form['janrain_settings']['rpx_apikey'] = array(
    '#type' => 'item',
    '#title' => t('API Key'),
    '#markup' => variable_get('rpx_apikey', ''),
  );

  $form['janrain_settings']['rpx_attach_login_form'] = array(
    '#type' => 'item',
    '#title' => t('Enable Janrain Engage sign-in on login forms'),
    '#markup' => variable_get('rpx_attach_login_form', 0) ? t('Yes') : t('No'),
  );

  $form['janrain_settings']['rpx_extended_authinfo'] = array(
    '#type' => 'item',
    '#title' => t('Request extended profile data.'),
    '#markup' => variable_get('rpx_extended_authinfo', 0) ? t('Yes') : t('No'),
  );

  $form['janrain_settings']['rpx_bypass_email_verification'] = array(
    '#type' => 'item',
    '#title' => t('Bypass email verification for Engage registration'),
    '#markup' => variable_get('rpx_bypass_email_verification', 0) ? t('Yes') : t('No'),
  );

  return system_settings_form($form);
}

/**
 * Form element validation handler for elememt "pfizer_auth_pac_error_list".
 */
function pfizer_auth_pac_error_list_validate($element, &$form_state) {
  // Transform list from text to array.
  module_load_include('module', 'list');
  $values = list_extract_allowed_values($element['#value'], 'list_text', FALSE);

  // Set element value.
  form_set_value($element, $values, $form_state);
}

/**
 * Form validation handler for pfizer_auth_admin_settings().
 */
function pfizer_auth_admin_settings_validate($form, &$form_state) {
  // Validate required SSO URLs.
  if ($form_state['values']['pfizer_auth_sso_enabled']) {
    if (empty($form_state['values']['pfizer_auth_js_url_sso'])) {
      form_set_error('pfizer_auth_js_url_sso', t('Janrain Federate SSO URL is required'));
    }
    if (empty($form_state['values']['pfizer_auth_js_url_xd_receiver'])) {
      form_set_error('pfizer_auth_js_url_xd_receiver', t('Cross Domain Receiver URL is required'));
    }
  }
}
