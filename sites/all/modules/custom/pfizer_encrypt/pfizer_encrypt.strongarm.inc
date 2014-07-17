<?php
/**
 * @file
 * pfizer_encrypt.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function pfizer_encrypt_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'encrypt_default_method';
  $strongarm->value = 'pfizer_encrypt';
  $export['encrypt_default_method'] = $strongarm;

  return $export;
}
