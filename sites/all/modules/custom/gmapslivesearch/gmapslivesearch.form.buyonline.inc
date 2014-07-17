<?php

// Include helpers
module_load_include('inc', 'gmapslivesearch', 'gmapslivesearch.form.common');

/**
 * @file
 * Buy online functionality.
 */

/**
 * Generate form for FIND ONLINE block.
 */
function gmapslivesearch_find_online_form($form, &$form_state) {
  
  $gmapslivesearch_buy_now_store_search_label = _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_NOW_STORE_SEARCH_LABEL);  
  $stores_to_search = array('' => $gmapslivesearch_buy_now_store_search_label) + list_extract_allowed_values(_gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_STORES_SEARCH), 'list_text', FALSE);
  
  $form[GMAPSLIVESEARCH_FIELD_STORES_SEARCH_FIND_ONLINE] = array(
    '#type'           => 'select',
    '#options'        => $stores_to_search,
    '#default_value'  => isset($form_state['input'][GMAPSLIVESEARCH_FIELD_STORES_SEARCH_FIND_ONLINE]) ? $form_state['input'][GMAPSLIVESEARCH_FIELD_STORES_SEARCH_FIND_ONLINE] : '',
    '#attributes' => array('class' => array('gmapslivesearch-field-stores-search')),    
  );
  
  $form[GMAPSLIVESEARCH_FIELD_GOTO_ONLINE_STORE_BTN_FIND_ONLINE] = array(
    '#type'           => 'link',
    '#title'          => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_ONLINE_BTN),
    '#href'           => gmapslivesearch_get_default_store_to_search($form, $stores_to_search, GMAPSLIVESEARCH_FIELD_STORES_SEARCH_FIND_ONLINE),
    '#attributes'     => array('class' => 'gmapslivesearch-goto-online-store', 'title' => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_ONLINE_BTN)),
  );

  $form['#theme'] = 'gmapslivesearch_buy_online_form';

  $form['#attributes']['class'] = array('gmapslivesearch-find-online-form');

  return $form;
}

/**
 * Handle validation of FIND ONLINE block.
 */
function gmapslivesearch_find_online_form_validate($form, &$form_state) {

  if (_gmapslivesearch_get_value(GMAPSLIVESEARCH_SHOW_ERROR_INLINE_FIND_ONLINE_BLOCK, 'all')) {
    if (!gmapslivesearch_is_valid_address_input($form_state['input'][GMAPSLIVESEARCH_FIELD_ADDRESS_TO_SEARCH_FIND_ONLINE])) {
      form_error($form[GMAPSLIVESEARCH_FIELD_ADDRESS_TO_SEARCH_FIND_ONLINE], _gmapslivesearch_get_value(GMAPSLIVESEARCH_ERROR_MESSAGE_ADDRESS_FIELD));
    }
  }
}

/**
 * Handle submission of FIND ONLINE block.
 */
function gmapslivesearch_find_online_form_submit($form, &$form_state) {
  $query = array(
    'address' => $form_state['input'][GMAPSLIVESEARCH_FIELD_ADDRESS_TO_SEARCH_FIND_ONLINE],
  );

  if (isset($form_state['input'][GMAPSLIVESEARCH_FIELD_STORES_CONTENT_TYPE])) {
    $query['content'] = $form_state['input'][GMAPSLIVESEARCH_FIELD_STORES_CONTENT_TYPE];
  }
  
  drupal_goto(_gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_PATH), array('query' => $query));
}

/**
 * Obtains the stores list according the content type or the general list
 * 
 * @param array $form
 * @param array $stores_to_search
 * @param string $field_name
 * @return array List of stores 
 */
function gmapslivesearch_get_default_store_to_search($form, $stores_to_search, $field_name) {
    
  //In case the form has been submitted the value selected should be assigned to GO button.
  if (!empty($form[$field_name]['#default_value']) && array_key_exists($form[$field_name]['#default_value'],
          $form[$field_name]['#options'])) {
    $stores_to_search = check_plain($form[$field_name]['#default_value']);
  }
  else {
    //Get the first stores on the list of 'stores to search' and assign to GO button button href.
    $stores_to_search = array_keys($stores_to_search);
    $stores_to_search = $stores_to_search[0];
  }
  
  return $stores_to_search;
}
