<?php

/**
 * @file
 * Admin settings for Pfizer Connect Authentication module.
 */

function pfizer_connect_admin_settings($form, $form_state) {

  $form['#tree'] = FALSE;

  // Configure SiteID and Language Code for each country
  $form['pfizer_connect_country_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Country settings'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t('Parameters sent in the authentication request.'),
    '#theme' => 'pfizer_connect_country_settings',
  );

  $languages = language_list();
  $country_settings = variable_get('pfizer_connect_country_settings', array());
  foreach ($languages as $language_code => $language) {
    if (!$language->enabled) continue;
    $form['pfizer_connect_country_settings'][$language_code] = array(
      '#type' => 'fieldset',
      '#title' => $language->name,
    );
    $form['pfizer_connect_country_settings'][$language_code]['site_id'] = array(
      '#type' => 'textfield',
      '#title' => t('Site ID'),
      '#default_value' => isset($country_settings[$language_code]['site_id']) ? $country_settings[$language_code]['site_id'] : '',
      '#size' => 10,
    );
    $form['pfizer_connect_country_settings'][$language_code]['language_code'] = array(
      '#type' => 'textfield',
      '#title' => t('Language Code'),
      '#default_value' => isset($country_settings[$language_code]['language_code']) ? $country_settings[$language_code]['language_code'] : '',
      '#size' => 10,
    );
    $form['pfizer_connect_country_settings'][$language_code]['segment'] = array(
      '#type' => 'textfield',
      '#title' => t('Segment'),
      '#default_value' => isset($country_settings[$language_code]['segment']) ? $country_settings[$language_code]['segment'] : '',
      '#size' => 30,
    );
  }

  // Configure external JavaScript URLs
  $form['external_javascripts'] = array(
    '#type' => 'fieldset',
    '#title' => t('External Javascripts settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t('Configure external JavaScript URLs.'),
  );

  $form['external_javascripts']['pfizer_connect_js_url_sso'] = array(
    '#type' => 'textfield',
    '#title' => t('Janrain Federate SSO (sso.js)'),
    '#required' => TRUE,
    '#default_value' => variable_get('pfizer_connect_js_url_sso', NULL),
  );

  $form['external_javascripts']['pfizer_connect_js_url_xd_receiver'] = array(
    '#type' => 'textfield',
    '#title' => t('Cross Domain Receiver (xd_receiver.js)'),
    '#required' => TRUE,
    '#default_value' => variable_get('pfizer_connect_js_url_xd_receiver', NULL),
  );

  $form['external_javascripts']['pfizer_connect_js_url_engage_main'] = array(
    '#type' => 'textfield',
    '#title' => t('Engage Main script (engage-mc.js)'),
    '#required' => TRUE,
    '#default_value' => variable_get('pfizer_connect_js_url_engage_main', NULL),
  );

  $form['external_javascripts']['pfizer_connect_js_url_engage_sso'] = array(
    '#type' => 'textfield',
    '#title' => t('Engage SSO script (sso-mc.js)'),
    '#default_value' => variable_get('pfizer_connect_js_url_engage_sso', NULL),
    '#attributes' => array('placeholder' => t('Leave blank to use default file.')),
    '#description' => t('Leave blank to use default file.'),
  );

  $form['external_javascripts']['pfizer_connect_sso_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Single Sign On'),
    '#default_value' => variable_get('pfizer_connect_sso_enabled', FALSE),
    '#description' => t('SSO allows users to log into multiple applications entering their credentials just once.'),
  );

  return system_settings_form($form);
}


/**
 * Returns HTML for the Country Configuration form.
 *
 * @param $variables
 *   An associative array containing:
 *   - form: A render element representing the form.
 *
 * @ingroup themeable
 */
function theme_pfizer_connect_country_settings($variables) {
  $form = $variables['form'];
  $header = array(
    t('Market'),
    t('Site ID'),
    t('Language Code'),
    t('Segment'),
  );

  foreach (element_children($form) as $key) {
    $form[$key]['site_id']['#title_display'] = 'invisible';
    $form[$key]['language_code']['#title_display'] = 'invisible';
    $form[$key]['segment']['#title_display'] = 'invisible';

    $rows[] = array(
      $form[$key]['#title'],
      array('data' => drupal_render($form[$key]['site_id'])),
      array('data' => drupal_render($form[$key]['language_code'])),
      array('data' => drupal_render($form[$key]['segment'])),
    );
  }

  $output = theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'pfizer-connect-country-settings')));
  return $output;
}

