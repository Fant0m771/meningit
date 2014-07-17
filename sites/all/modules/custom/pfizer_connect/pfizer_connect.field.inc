<?php

/**
 * @file
 * Field functions for Pfizer Connect Authentication module.
 */

/**
 * Implements hook_field_info().
 */
function pfizer_connect_field_info(){

  // Pfizer profile info field
  $fields['pfizer_profile'] = array(
    'label' => t('Pfizer profile info'),
    'description' => t('Information provided by Pfizer Connect'),
    'settings' => array(),
    'instance_settings' => array('text_processing' => 0),
    'default_widget' => 'text_textfield',
    'default_formatter' => 'text_default',
    'no_ui' => TRUE,
  );

  return $fields;
}