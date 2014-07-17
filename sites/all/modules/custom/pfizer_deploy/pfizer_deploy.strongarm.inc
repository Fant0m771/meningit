<?php
/**
 * @file
 * pfizer_deploy.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function pfizer_deploy_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'deploy_auto_plan_entity_types';
  $strongarm->value = pfizer_deploy_get_entity_type_defaults();
  $export['deploy_auto_plan_entity_types'] = $strongarm;

  return $export;
}
