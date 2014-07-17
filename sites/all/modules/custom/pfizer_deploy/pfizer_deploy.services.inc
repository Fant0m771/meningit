<?php
/**
 * @file
 * pfizer_deploy.services.inc
 */

/**
 * Implements hook_default_services_endpoint().
 */
function pfizer_deploy_default_services_endpoint() {
  $export = array();

  $endpoint = new stdClass();
  $endpoint->disabled = FALSE; /* Edit this to true to make a default endpoint disabled initially */
  $endpoint->api_version = 3;
  $endpoint->name = 'wf_diff';
  $endpoint->server = 'rest_server';
  $endpoint->path = 'wf-diff';
  $endpoint->authentication = array(
    'services_basic_auth' => 'services_basic_auth',
  );
  $endpoint->server_settings = array(
    'formatters' => array(
      'json' => TRUE,
      'bencode' => FALSE,
      'jsonp' => FALSE,
      'php' => FALSE,
      'xml' => FALSE,
    ),
    'parsers' => array(
      'application/json' => TRUE,
      'application/vnd.php.serialized' => FALSE,
      'application/x-www-form-urlencoded' => FALSE,
      'application/xml' => FALSE,
      'multipart/form-data' => FALSE,
      'text/xml' => FALSE,
    ),
  );
  $endpoint->resources = array(
    'deploy' => array(
      'targeted_actions' => array(
        'diff' => array(
          'enabled' => '1',
        ),
      ),
    ),
  );
  $endpoint->debug = 0;
  $export['wf_diff'] = $endpoint;

  return $export;
}
