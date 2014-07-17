<?php

if(!defined('DOUBLECLICK_PREFIX')) {
  define('DOUBLECLICK_PREFIX', "doubleclick_");
}

/**
 * add js script and  doubleclick_tracking_value on Drupal object
 */
function _doubleclick_include_onload_javascript() {

  if (_doubleclick_validate_config_data()) {
    $js_content = variable_get(DOUBLECLICK_PREFIX.'onload_javascript');
    $output = _doubleclick_replace_javascript($js_content);
  
    drupal_add_js($output, array('type' => 'inline', 'scope' => 'footer', 'weight' => 5000));
    drupal_add_js(array('doubleclick_tracking_value' => _doubleclick_get_value()), 'setting');
  }

}

function _doubleclick_include_onclick_javascript() {

  if (_doubleclick_validate_config_data()) {
  
    $js_content = variable_get(DOUBLECLICK_PREFIX.'selectors_javascript');
    $output = _doubleclick_replace_javascript($js_content);

    drupal_add_js($output, array('type' => 'inline', 'scope' => 'footer', 'weight' => 5000));
  }
  
}

function _doubleclick_include_core_javascript() {
  if (_doubleclick_validate_config_data()) {

    $js_function = file_get_contents(drupal_get_path('module', 'doubleclick') . '/scripts/doubleclick_tracking.js', 'r');
    $output = _doubleclick_replace_javascript($js_function);
  
    drupal_add_js($output, array('type' => 'inline', 'scope' => 'header', 'weight' => 5000));
  }
  
}

function _doubleclick_validate_config_data() {
  if (variable_get(DOUBLECLICK_PREFIX.'tracking_src') && variable_get(DOUBLECLICK_PREFIX.'tracking_type')
      && variable_get(DOUBLECLICK_PREFIX.'tracking_url')) {
    return true;
  }
  return false;
}

function _doubleclick_replace_javascript($js_content) {

  $patterns = array(
    '//@CLIENTID_PLACEHOLDER@',
    '//@TRACKING_TYPE_PLACEHOLDER@',
    '//@TRACKING_URL_PLACEHOLDER@',
  );
  
  $replaces = array(
    variable_get(DOUBLECLICK_PREFIX.'tracking_src'),
    variable_get(DOUBLECLICK_PREFIX.'tracking_type'),
    variable_get(DOUBLECLICK_PREFIX.'tracking_url'),
  );
  
  
  $output = str_replace($patterns, $replaces, $js_content);
  
  return $output;
  
}
/**
 * Get doubleclick configurable value foreach page through content type or data base
 *
 * @return boolean 
 */
function _doubleclick_get_value() {
    
  $doubleclick_tracking_value_object = menu_get_object();
    
  if ($doubleclick_tracking_value_object && $doubleclick_tracking_value_object->type=='webform' && array_key_exists($doubleclick_tracking_value_object->language, $doubleclick_tracking_value_object->field_doubleclick_webform_value)) {
    $doubleclick_tracking_value = $doubleclick_tracking_value_object->field_doubleclick_webform_value[$doubleclick_tracking_value_object->language][0]['value'];    
  }
  elseif ($doubleclick_tracking_value_object && $doubleclick_tracking_value_object->type=='page' && array_key_exists($doubleclick_tracking_value_object->language, $doubleclick_tracking_value_object->field_doubleclick_value)) {
    $doubleclick_tracking_value = $doubleclick_tracking_value_object->field_doubleclick_value[$doubleclick_tracking_value_object->language][0]['value'];
  } else {

    $select = db_select('doubleclick_tracking_by_page', 'dc');
    $select->condition('url',$_GET['q']);
    $select->fields('dc');
    $select_result = $select->execute();     
    $result_fields = $select_result->fetchObject();

    if ($result_fields) {
      $doubleclick_tracking_value = $result_fields->value;
    } 
    else {
      $doubleclick_tracking_value = false;
    }
  }
  return $doubleclick_tracking_value;
}