<?php
/**
 * @file gmapslivesearch.admin.forms.inc
 * Forms for admin pages
 */
 
// Include helpers
module_load_include('inc', 'gmapslivesearch', 'gmapslivesearch.admin.common');

/**
 * Setting the available stores
 */
function gmapslivesearch_stores_config() {
  $form = array();
  
  $form[GMAPSLIVESEARCH_FIELD_STORES_SEARCH] = array(
    '#type'           => 'textarea',
    '#title'          => t('Stores to search'),
    '#description'    => _gmapslivesearch_get_miles_to_search_description(),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_STORES_SEARCH, 'all'),
  );
  
  $form[GMAPSLIVESEARCH_FIELD_SEARCHSTRING] = array(
    '#type'           => 'textarea',
    '#title'          => t('Search string'),  
    '#description'    => t('Search string used to get store results. Enter one value per line.'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_SEARCHSTRING, 'all'),
  );
  
  $form[GMAPSLIVESEARCH_MAPS_STORES_BY_CONTENT] = array(
    '#type'           => 'fieldset',
    '#title'          => t('Stores by content'),
    '#description'    => t('Content type specific stores configuration.'),
    '#collapsible'    => TRUE,
    '#collapsed'      => FALSE,
  );
  
  $types = node_type_get_types();
  foreach($types as $node_type) {
    $options[$node_type->type] = $node_type->name;
  }
  array_unshift($options, 'none');
  $form[GMAPSLIVESEARCH_MAPS_STORES_BY_CONTENT][GMAPSLIVESEARCH_FIELD_STORES_CONTENT_TYPE] = array(
    '#type'           => 'select',
    '#title'          => t('Stores by content'),
    '#description'    => t('Select a content type to make specific stores configuration by content. It will load a new field for that type of content and display a new configuration based on the stores entered in "Search string" field.'),
    '#options'        => $options,
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_STORES_CONTENT_TYPE, 'all'),
    '#collapsible'    => TRUE,
    '#collapsed'      => FALSE,
  );
  
  $form['#validate'][] = 'gmapslivesearch_stores_config_validate';
  $form['#submit'][] = 'gmapslivesearch_stores_config_submit';
  
  return system_settings_form($form);
}

/**
 * Form validations
 */
function gmapslivesearch_stores_config_validate($form, &$form_state) {
  $field = field_info_field('gmapslivesearch_stores_options');
  $has_data = field_has_data($field);
  $element = $form[GMAPSLIVESEARCH_FIELD_SEARCHSTRING];

  $values = list_extract_allowed_values($form_state['values'][GMAPSLIVESEARCH_FIELD_SEARCHSTRING], 'list_text', FALSE);

  if (!is_array($values)) {
    form_error($element, t('Allowed values list: invalid input.'));
  }
  else {
    // Prevent removing values currently in use.
    if ($has_data) {
      $lost_keys = array_diff(array_keys($field['settings']['allowed_values']), array_keys($values));
      
      if (_list_values_in_use($field, $lost_keys)) {
        form_error($element, t('Allowed values list: some values are being removed while currently in use: :lost_keys.', array(':lost_keys' => implode(', ', $lost_keys))));
      }
    }

  }
}

/**
* Process Stores options for gmapslivesearch stores settings submission.
*/
function gmapslivesearch_stores_config_submit($form, &$form_state) {
  $types = node_type_get_types();
  foreach($types as $node_type) {
    $options[$node_type->type] = $node_type->name;
  }

  // Loop through each defined content type
  foreach ($types as $key => $value) {
    $instance = field_info_instance('node', 'gmapslivesearch_stores_options', $key);
    
    if ($key !== $form_state['values'][GMAPSLIVESEARCH_FIELD_STORES_CONTENT_TYPE]) {
    
      if (!empty($instance)) {
        $delete_field_if_last_instance = FALSE;
        field_delete_instance($instance, $delete_field_if_last_instance);
        watchdog("Gmapslivesearch", 'Deleted gmapslivesearch_stores_options field from content type: %key', array('%key' => $key));
      }
    }
    else {
    
      // If the check box for a content type is checked, look to see whether
      // the field is associated with that content type. If not then add the
      // stores selection field to the content type.
      if (empty($instance)) {
      
        $instance = array(
          'field_name' => 'gmapslivesearch_stores_options',
          'entity_type' => 'node',
          'bundle' => $key,
          'label' => 'Selected Stores',
          'widget' => array(
            'type' => 'options_buttons',
            'weight' => 5,
          ),
        );
        
        $instance = field_create_instance($instance);
        watchdog('Gmapslivesearch', 'Added gmapslivesearch_stores_options field to content type: %key', array('%key' => $key));
      }
      
      // update field allowed values
      $field = field_info_field('gmapslivesearch_stores_options');
      $field['settings']['allowed_values'] = list_extract_allowed_values($form_state['values'][GMAPSLIVESEARCH_FIELD_SEARCHSTRING], 'list_text', FALSE);
      field_update_field($field);
    }
  } // End foreach loop.
}
