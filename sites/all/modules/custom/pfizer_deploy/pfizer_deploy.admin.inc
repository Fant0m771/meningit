<?php

/**
 * @file
 * Administration functions for the Pfizer Deploy module.
 */

/**
 * Menu callback: options for Pfizer Deploy.
 */
function pfizer_deploy_admin_form() {
  $form = array();

  $form['configuration'] = array(
    '#type' => 'fieldset',
    '#title' => t('Configuration'),
  );

  $form['configuration']['pfizer_deploy_next_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Next Endpoint URL'),
    '#default_value' => variable_get('pfizer_deploy_next_url', NULL),
  );

  $form['configuration']['pfizer_deploy_next_user'] = array(
    '#type' => 'textfield',
    '#title' => t('Next Endpoint Username'),
    '#default_value' => variable_get('pfizer_deploy_next_user', NULL),
  );

  $form['configuration']['pfizer_deploy_next_pass'] = array(
    '#type' => 'password',
    '#title' => t('Next Endpoint Pass'),
    '#default_value' => variable_get('pfizer_deploy_next_pass', NULL),
  );

  $form['configuration']['pfizer_deploy_debug'] = array(
    '#type' => 'checkbox',
    '#title' => t('Debug'),
    '#default_value' => variable_get('pfizer_deploy_debug', 0),
  );

  return system_settings_form($form);
}
