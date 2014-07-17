<?php

/**
 * @file
 * Draw the User Guide Tab
 * @return type 
 */
function omniture_by_content_guide_form() {
    
  $new_page_description = t('To set the load page tracking string value:<br>
    1. Go to content.<br />
    2. Select only a basic page and click on edit.<br />
    3. Into the basic page you can find a field "Omniture Page Name Tracking Value".<br />
    4. Set in the tracking value field. The string to send in the onload event.<br />
  ');
  
  $form['omniture_by_content_guide'] = array(
    '#type' => 'fieldset',
    '#title' => t('Omniture Pfizer Mobile Guide'),
    '#description' => check_plain($new_page_description),
    '#attributes' => array('style' => 'font-family: calibri;'),
  );
 
  return $form;
}

/**
 * Draw the JS Settings Tab
 * @return type 
 */
function omniture_by_content_js_form() {
  $form[OMNITURE_PREFIX . '_javascript_onload_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('JS Onload Events'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  
  $form[OMNITURE_PREFIX . '_javascript_onload_settings'][OMNITURE_PREFIX . '_selectors_javascript'] = array(
  '#type' => 'textarea',
    '#title' => t('Javascript For Onclick Events'),
    '#default_value' => variable_get(OMNITURE_PREFIX . '_selectors_javascript'),
    '#description' => t('Javascript to track onload events'),
    '#required' => FALSE,
  );
  
  return system_settings_form($form);
}