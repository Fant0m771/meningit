<?php

/**
 * @file
 * Tokens functions for Pfizer Connect Authentication module.
 */

/**
 * Implements hook_token_info().
 */
function pfizer_connect_token_info() {
  $types['pfizer-user'] = array(
    'name' => 'Pfizer User Info',
    'description' => t('User info provided by Pfizer Connect.'),
  );

  $tokens['profile'] = array(
    'name' => t('Profile data'),
    'description' => t('Profile data. The dynamic parameter corresponds to the field name.'),
    'dynamic' => TRUE,
  );

  return array(
    'types' => $types,
    'tokens' => array('pfizer-user' => $tokens),
  );
}


/**
 * Implements hook_tokens().
 */
function pfizer_connect_tokens($type, $tokens, array $data = array(), array $options = array()) {
  global $user;
  $replacements = array();

  if ($type == 'pfizer-user' && user_is_logged_in()) {

    $account = user_load($user->uid);
    if (isset($account->pfizer_profile['und'][0]['value'])) {

      // Get parameters from profile data
      $rpx_data_raw = $account->pfizer_profile['und'][0]['value'];
      parse_str($rpx_data_raw, $rpx_data);
      $profile_tokens = token_find_with_prefix($tokens, 'profile');

      foreach ($profile_tokens as $name => $original) {
        if (isset($rpx_data[$name])) {
          // Replace token
          $replacements[$original] = check_plain($rpx_data[$name]);
        }
        else {
          // Remove token if value is not found
          $replacements[$original] = '';
        }
      }
    }

  }

  return $replacements;
}
