<?php
/**
 * Draw doubleclick settings page
 * @param type $form_state
 * @param type $node
 * @return type 
 */
function doubleclick_admin_form($form_state, $node) {
  $form['doubleclick'] = array(
    '#type' => 'fieldset',
    '#title' => t('DoubleClick Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['doubleclick'][DOUBLECLICK_PREFIX.'tracking_src'] = array(
  '#type' => 'textfield',
	'#title' => t('Tracking Id'),
	'#default_value' => variable_get(DOUBLECLICK_PREFIX.'tracking_src'),
	'#description' => t('DoubleClick Tracking Id'),
	'#required' => TRUE
  );

  $form['doubleclick'][DOUBLECLICK_PREFIX.'tracking_type'] = array(
  '#type' => 'textfield',
	'#title' => t('Tracking Mode'),
	'#default_value' => variable_get(DOUBLECLICK_PREFIX.'tracking_type'),
	'#description' => t('DoubleClick Tracking Mode'),
	'#required' => TRUE
  );
  
  $form['doubleclick'][DOUBLECLICK_PREFIX.'tracking_url'] = array(
  	'#type' => 'textfield',
	  '#title' => t('Tracking URL'),
	  '#default_value' => variable_get(DOUBLECLICK_PREFIX.'tracking_url'),
	  '#description' => t('DoubleClick Tracking URL. Ex: https://fls.doubleclick.net/activityi'),
	  '#required' => TRUE
  );
  
  $form['#submit'][] = 'doubleclick_admin_form';
  return system_settings_form($form);
  
}
/**
 * Draw doubleclick javascript general page function
 * @param type $form_state
 * @param type $node
 * @return type 
 */
function doubleclick_javascript_form($form_state, $node) {

  $form['javascript_onload_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('JS Onload Events'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['javascript_onload_settings'][DOUBLECLICK_PREFIX.'onload_javascript'] = array(
  '#type' => 'textarea',
	'#title' => t('Javascript For Onload Event'),
	'#default_value' => variable_get(DOUBLECLICK_PREFIX.'onload_javascript'),
	'#description' => t('Javascript to track onload events'),
	'#required' => TRUE,
  );

  $form['javascript_onclick_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('JS Onclick Events'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  
  $form['javascript_onclick_settings'][DOUBLECLICK_PREFIX.'selectors_javascript'] = array(
  '#type' => 'textarea',
	'#title' => t('Javascript For Onclick Events'),
	'#default_value' => variable_get(DOUBLECLICK_PREFIX.'selectors_javascript'),
	'#description' => t('Javascript to track onclick events'),
	'#required' => FALSE,
  );
  
  $form['#submit'][] = 'doubleclick_javascript_form';
  return system_settings_form($form);
}

/**
 * Draw doubleclick by page function  
 * @param type $form_state
 * @return string 
 */
function doubleclick_by_page_form($form_state) {
  
  $form['pages'] = array('#tree' => TRUE);
  
  $query = db_select('doubleclick_tracking_by_page', 'dc')->fields('dc');
  
  $custom_config_paths = $query->execute();
  
  foreach ($custom_config_paths as $page) {
    $form['pages'][$page->dcid] = array(
      '#type' => 'fieldset',
      '#title' => $page->url,
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#tree' => TRUE,
    );
    
    $form['pages'][$page->dcid]['tracking_value'] = array(
      '#type' => 'textfield',
      '#title' => $page->url,
      '#description' => t('Insert your tracking value here.'),
      '#default_value' => $page->value,
    );
    
    $form['pages'][$page->dcid]['delete'] = array(
      '#type' => 'checkbox',
      '#title' => t('Delete'),
      '#description' => t('Select this checkbox to delete this configuration'),
      '#default_value' => 0,
    );
  } 
  
  $new_page_description = t('Enter a new page url to define its specific configuration. DO NOT include the base_path here.<br />
    Valid entries:<br />
    1. normal path         (e.g. node/5)<br />
    2. path alias          (e.g. products/product-name-1)<br />
    3. menu router path    (e.g. products/%)<br />
  ');
  
  $form['new_page'] = array(
    '#type' => 'textfield',
    '#title' => t('New page'),
    '#description' => $new_page_description,
    '#attributes' => array('style' => 'font-family: monospace;'),
  );
  
  $form['submit'] = array(
    '#type'  => 'submit',
    '#value' => t('Save')  
  );
  
  return $form;
}

/**
 * Add, update or delete doubleclick tracking value for each page
 * @param type $form
 * @param type $form_state 
 */
function doubleclick_by_page_form_submit($form, $form_state) {
  
  if (!empty($form_state['values']['new_page'])) {
    
    $insert = db_insert('doubleclick_tracking_by_page');
    $insert->fields(array('url' => $form_state['values']['new_page']));
    $insert->execute();
    
  }  
  
  if (isset($form_state['values']['pages'])) {
    
    foreach ( $form_state['values']['pages'] as $dcid => $page ) {

      if ($page['delete']) {
        $delete = db_delete('doubleclick_tracking_by_page');
        $delete->condition('dcid', $dcid);
        $delete->execute();
      }
      else {
        $update = db_update('doubleclick_tracking_by_page');
        $update->fields(array('value' => $page['tracking_value']));
        $update->condition('dcid', $dcid);
        $update->execute(); 
      }
    }
  }
}

