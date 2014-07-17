<?php
/**
 * @file
 * Field functions for Pfizer Authentication module.
 */

/**
 * Implements hook_field_info().
 */
function pfizer_auth_field_info() {

  $fields = array();

  // Create mapping fields.
  $mapping_fields = _pfizer_auth_get_mapping_fields();
  foreach ($mapping_fields as $field) {
    $fields[$field['name']] = array(
      'label' => t($field['label']),
      'description' => t('Information provided by Pfizer Authentication'),
      'settings' => array(),
      'instance_settings' => array('text_processing' => 0),
      'default_widget' => 'text_textfield',
      'default_formatter' => 'text_default',
      'no_ui' => TRUE,
    );
  }

  return $fields;
}

/**
 * Get mapping fields.
 */
function _pfizer_auth_get_mapping_fields() {
  return array(
    array(
      'name'  => 'field_pfizer_auth_first_name',
      'label' => 'Pfizer Profile - First Name',
      'path'  => "['merged_poco']['name']['givenName']",
    ),
    array(
      'name'  => 'field_pfizer_auth_last_name',
      'label' => 'Pfizer Profile - Last Name',
      'path'  => "['merged_poco']['name']['familyName']",
    ),
    array(
      'name'  => 'field_pfizer_auth_email',
      'label' => 'Pfizer Profile - Email',
      'path'  => "['merged_poco']['emails']['0']['value']",
    ),
    array(
      'name'  => 'field_pfizer_auth_created',
      'label' => 'Pfizer Profile - Created',
      'path'  => "['merged_poco']['created']",
    ),
    array(
      'name'  => 'field_pfizer_auth_postal_address',
      'label' => 'Pfizer Profile - Postal Address',
      'path'  => "['merged_poco']['addresses']['0']['streetAddress']",
    ),
    array(
      'name'  => 'field_pfizer_auth_postal_code',
      'label' => 'Pfizer Profile - Postal Code',
      'path'  => "['merged_poco']['addresses']['0']['postalCode']",
    ),
    array(
      'name'  => 'field_pfizer_auth_phone_number',
      'label' => 'Pfizer Profile - Phone Number',
      'path'  => "['merged_poco']['phoneNumbers']['0']['value']",
    ),
    array(
      'name'  => 'field_pfizer_auth_pref_username',
      'label' => 'Pfizer Profile - Preferred Username',
      'path'  => "['merged_poco']['preferredUsername']",
    ),
    array(
      'name'  => 'field_pfizer_auth_subject',
      'label' => 'Pfizer Profile - Subject',
      'path'  => "['provider']['pfizer']['subject']",
    ),
    array(
      'name'  => 'field_pfizer_auth_pfp_zip',
      'label' => 'Pfizer Profile - PFPZip',
      'path'  => "['provider']['pfizer']['pfpZip']",
    ),
    array(
      'name'  => 'field_pfizer_auth_party_id',
      'label' => 'Pfizer Profile - Party ID',
      'path'  => "['provider']['pfizer']['partyId']",
    ),
    array(
      'name'  => 'field_pfizer_auth_groups',
      'label' => 'Pfizer Profile - Groups',
      'path'  => "['provider']['pfizer']['groups']",
    ),
    array(
      'name'  => 'field_pfizer_auth_categories',
      'label' => 'Pfizer Profile - Categories',
      'path'  => "['provider']['pfizer']['categories']",
    ),
    array(
      'name'  => 'field_pfizer_auth_uid',
      'label' => 'Pfizer Profile - UID',
      'path'  => "['provider']['pfizer']['uid']",
    ),
    array(
      'name'  => 'field_pfizer_auth_emp_group',
      'label' => 'Pfizer Profile - Employee Group',
      'path'  => "['provider']['pfizer']['group']",
    ),
  );
}



