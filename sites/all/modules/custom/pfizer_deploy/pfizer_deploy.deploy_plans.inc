<?php
/**
 * @file
 * pfizer_deploy.deploy_plans.inc
 */

/**
 * Implements hook_deploy_plans_default().
 */
function pfizer_deploy_deploy_plans_default() {
  $export = array();

  $plan = new DeployPlan();
  $plan->disabled = FALSE; /* Edit this to true to make a default plan disabled initially */
  $plan->api_version = 1;
  $plan->name = 'push_to_next';
  $plan->title = 'Push to Next';
  $plan->description = 'This is an example plan called "Push to Next".  WF Tools will actually create the deployment plan needed for the job.';
  $plan->debug = variable_get('pfizer_deploy_debug', 0);
  $plan->aggregator_plugin = 'DeployAggregatorManaged';
  $plan->aggregator_config = array(
    'delete_post_deploy' => 0,
  );
  $plan->fetch_only = 0;
  $plan->processor_plugin = 'DeployProcessorMemory';
  $plan->processor_config = array();
  $plan->endpoints = array(
    'next' => 'next',
  );
  $export['push_to_next'] = $plan;

  return $export;
}
