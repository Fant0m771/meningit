<?php
/**
 * @file
 * pfizer_deploy.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function pfizer_deploy_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "deploy" && $api == "deploy_endpoints") {
    return array("version" => "1");
  }
  if ($module == "deploy" && $api == "deploy_plans") {
    return array("version" => "1");
  }
  if ($module == "services" && $api == "services") {
    return array("version" => "3");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
