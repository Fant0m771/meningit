<?php
/**
 * @file
 * pfizer_deploy.deploy_endpoints.inc
 */

/**
 * Implements hook_deploy_endpoints_default().
 */
function pfizer_deploy_deploy_endpoints_default() {
  $export = array();

  $endpoint = new DeployEndpoint();
  $endpoint->disabled = FALSE; /* Edit this to true to make a default endpoint disabled initially */
  $endpoint->api_version = 1;
  $endpoint->name = 'next';
  $endpoint->title = 'Next';
  $endpoint->description = 'Generic endpoint that will be overwritten by a script when WF Tools creates the site in the environment.';
  $endpoint->debug = variable_get('pfizer_deploy_debug', 0);
  $endpoint->authenticator_plugin = 'DeployAuthenticatorSession';
  $endpoint->authenticator_config = array(
    'username' => variable_get('pfizer_deploy_next_user', NULL),
    'password' => variable_get('pfizer_deploy_next_pass', NULL),
  );
  $endpoint->service_plugin = 'DeployServiceRestJSON';
  $endpoint->service_config = array(
    'url' => variable_get('pfizer_deploy_next_url', NULL),
  );
  $export['next'] = $endpoint;

  return $export;
}
