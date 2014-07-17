<?php

// Include helpers
module_load_include('inc', 'gmapslivesearch', 'gmapslivesearch.form.common');

/**
 * @file
 * Buy now functionality.
 */

/**
 * Build buy now page.
 */
function gmapslivesearch_buy_now_page() {
  //Load JS files
  _gmapslivesearch_load_js();
  _gmapslivesearch_find_store_load_js();

  //Obtain buy now form
  $buy_now_form = drupal_get_form('gmapslivesearch_buy_now_form');

  return theme('gmapslivesearch_find_store_page', array('search_box'  => drupal_render($buy_now_form)));
}

/**
 * Prepares the map
 *
 * @param DrupalForm $buy_now_form The buy now form
 */
function _gmapslivesearch_prepare_buy_now_map($buy_now_form, $results = false) {
  $enabled_default_result   = _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_ENABLE_DEFAULT_RESULT);
  $default_result_latitude  = _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_DEFAULT_MAP_RESULT_LATITUDE);
  $default_result_longitude = _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_DEFAULT_MAP_RESULT_LONGITUDE);
  $default_result_zoom      = _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_DEFAULT_MAP_RESULT_ZOOM);

  _gmapslivesearch_send_to_js(array('no_results_found' => FALSE));
  $map = null;
  //if the user request a search
  if ($results !== false) {
    //check if there are results
    if($results != array()) {
      $_SESSION['gmapslivesearch_has_results'] = TRUE;
      _gmapslivesearch_send_to_js(array('results_list' => $results));
      _gmapslivesearch_send_to_js(array('zoom' => (int)($default_result_zoom)));

      $map = theme('gmapslivesearch_map_block', array('stores' => $results));
      _gmapslivesearch_send_to_js(array('no_results_found' => TRUE));
    }
  } elseif (!empty($enabled_default_result) && !empty($default_result_latitude) && !empty($default_result_longitude)) {
    //Sending default values to JS
    _gmapslivesearch_send_to_js(array(
      'enabled_default_result' => $enabled_default_result,
      'default_result_latitude' => $default_result_latitude,
      'default_result_longitude' => $default_result_longitude,
      'default_result_zoom' => $default_result_zoom
    ));

    $map = theme('gmapslivesearch_map_block');
  }

  return $map;
}

/**
 * Generate form for search stores feature, based on the given $form_type.
 */
function gmapslivesearch_buy_now_form($form, &$form_state) {
  $address_search_label = _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_NOW_ADDRESS_SEARCH_LABEL);
  $gmapslivesearch_error_message_address_field = _gmapslivesearch_get_value(GMAPSLIVESEARCH_ERROR_MESSAGE_ADDRESS_FIELD);

  _gmapslivesearch_send_to_js(array(
    'field_address_default_label' => $address_search_label,
    'error_msg' => $gmapslivesearch_error_message_address_field
  ));

  //Input to search
  $form[GMAPSLIVESEARCH_FIELD_ADDRESS_TO_SEARCH] = array(
    '#type'   => 'textfield',
    '#default_value' => isset($form_state['input'][GMAPSLIVESEARCH_FIELD_ADDRESS_TO_SEARCH]) ? $form_state['input'][GMAPSLIVESEARCH_FIELD_ADDRESS_TO_SEARCH] : '',
    '#attributes' => array('class' => array('gmapslivesearch-field-address-to-search')),
  );

  if (_gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_STORES_CONTENT_TYPE, 'all') !== '0') {
    $stores = _gmapslivesearch_fetch_stores_by_content();
    if (!empty($stores)) {
      $form[GMAPSLIVESEARCH_FIELD_STORES_CONTENT_TYPE] = array(
        '#type'	   => 'select',
        '#title'   => t('Content with stores'),
        '#options' => $stores
      );
      if(isset($_GET['content'])) {
        $form[GMAPSLIVESEARCH_FIELD_STORES_CONTENT_TYPE]['#value'] = $_GET['content'];
      }
    }
  }

  $find_store_btn_label = _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_FIND_STORE_BTN);
  $form['submit'] = array(
    '#type'           => 'submit',
    '#value'          => $find_store_btn_label,
    '#attributes'     => array('title' => $find_store_btn_label),
  );

  //In case this become accessible for logged users this might need some fix.
  if (user_is_logged_in()) {
    //Please check form.inc line 958 for explanation of this. As this is a search form we don't need tokens.
    $form['#token'] = FALSE;
  }

  //Show map if needed
  $form['#suffix'] = _gmapslivesearch_prepare_buy_now_map($form);
  //Hardcode action
  $form['#action'] = url(_gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_PATH));
  $form['#pre_render']= array('gmapslivesearch_buy_now_form_pre_render');
  $form['#theme'] = 'gmapslivesearch_find_store_form';
  $form['#id'] = 'gmapslivesearch-buy-now-form';

  return $form;
}


/**
 * Handle validation of a search over the stores.
 */
function gmapslivesearch_buy_now_form_validate(&$form, &$form_state) {
  //if data is valid
  if (!gmapslivesearch_is_valid_address_input($form_state['input'][GMAPSLIVESEARCH_FIELD_ADDRESS_TO_SEARCH])) {
    //Sending error message
    $error_message_address_field = _gmapslivesearch_get_value(GMAPSLIVESEARCH_ERROR_MESSAGE_ADDRESS_FIELD);
    form_error($form[GMAPSLIVESEARCH_FIELD_ADDRESS_TO_SEARCH], filter_xss($error_message_address_field));
  }
}

/**
 * Handle submission of a search over the stores, returning the available stores for
 * the filters seleceted.
 */
function gmapslivesearch_buy_now_form_submit(&$form, &$form_state) {
  $form_state['redirect'] = FALSE;

  //Apend results list
  $results = _gmapslivesearch_get_stores_location($form_state['input'][GMAPSLIVESEARCH_FIELD_ADDRESS_TO_SEARCH]);
  $form['#suffix'] = _gmapslivesearch_prepare_buy_now_map($form, $results);

  if(count($results)==0) {
    $no_results_found_msg = _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELDSET_MAPS_GREAT_DISTANCE_MESSAGE);
    $miles_search = _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELDSET_DEFAULT_MILE_RADIUS);

    $form['no_results_found'] = array(
      '#markup' => str_replace('#distance#', $miles_search, $no_results_found_msg)
    );
  }
  else {
    $form['#attributes']['class'] = 'has-results';
  }
}

/**
 * Pre render used to send error to the cutomized field
 */
function gmapslivesearch_buy_now_form_pre_render($form) {
  $errors = _gmapslivesearch_get_form_errors();

  if($errors) {
    //We made this on this way in order to customize the error location
    $form['errors'] = array(
      '#markup' => $errors
    );
  }

  return $form;
}

/**
 * Works with the google api and request all the vendors
 *
 * @var string address to search
 */
function _gmapslivesearch_get_stores_location($address) {
  module_load_include('inc', 'gmapslivesearch', 'gmapslivesearch.class');
  $stores_to_search = _gmapslivesearch_get_stores_to_search();
  $stores = new gmapslivesearchRollingCurl($address, $stores_to_search);
  $stores_list = $stores->getStores();
  $position = $stores->getLatLong($address);

  _gmapslivesearch_send_to_js(array('search_position' => $position));

  return $stores_list;
}

/**
 * Get form errors stylized and ready to be outputed
 */
function _gmapslivesearch_get_form_errors() {
  $errors_list = drupal_get_messages('error', TRUE);
  if(count($errors_list) > 0) {
    $errors = array(
      'items'       => $errors_list,
      'type'        => 'ul',
      'attributes'  => array('class' => 'error error-inline error-messages-find-store messages')
    );

    return theme('item_list', $errors);
  }

  return FALSE;
}

/**
 * Loads map JS and jQtransform if needed
 */
function _gmapslivesearch_find_store_load_js() {
  //Adding google library
  drupal_add_js('https://maps.google.com/maps/api/js?sensor=false');

  $device_type = _gmapslivesearch_return_device_type();

  if($device_type != 'mobile') {
    $apply_jqTransform = _gmapslivesearch_get_value(GMAPSLIVESEARCH_JQTRANSFORM_OPTION, 'desktop');
    _gmapslivesearch_send_to_js(array('apply_jqtransform' => $apply_jqTransform));

    if($apply_jqTransform == 1) {
      drupal_add_js($module_path . '/scripts/jquery.jqtransform.js');
    }

    _gmapslivesearch_send_to_js(array('use_jscrollpane' => true));
    drupal_add_js(drupal_get_path('module', 'gmapslivesearch') . '/scripts/jquery.jscrollpane.min.js');
  }
}

/**
 * Return the correct stores to be searched by Google Search API for the current content.
 * Check from where the current content is being passed, getting the current content of the posted form or from the $_GET parameter, so it works for both the buy-now page and the buy-now block.
 *
 * @return
 * Return all stores defined in the current content.
 * If the current content is not defined or have its stores empty, return all the defined stores in the administration form.
 */
function _gmapslivesearch_get_stores_to_search() {
  $stores_to_search = array();
  $current_content_id = NULL;

  if (!empty($_POST)) {
    $current_content_id = isset($_POST[GMAPSLIVESEARCH_FIELD_STORES_CONTENT_TYPE]) ? $_POST[GMAPSLIVESEARCH_FIELD_STORES_CONTENT_TYPE] : NULL;
  }
  else {
    $current_content_id = isset($_GET['content']) ? $_GET['content'] : NULL;
  }

  $current_content = _gmapslivesearch_get_valid_content($current_content_id);
  if ($current_content && !empty($current_content->gmapslivesearch_stores_options['und'])) {
    $stores = $current_content->gmapslivesearch_stores_options['und'];
    foreach ($stores as $id => $store_name) {
      $stores_to_search[] = $store_name['value'];
    }
  }
  else {
    $stores_to_search = list_extract_allowed_values(_gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_SEARCHSTRING, 'all'), 'list_text', FALSE);
  }

  return $stores_to_search;
}

/**
 * Return valid content object defined by $nid, FALSE if it is not valid.
 *
 * @param $nid
 * Node id to be checked and loaded.
 *
 * @return
 * Loaded object for a valid $nid of a content for the correct content type. FALSE otherwise.
 */
function _gmapslivesearch_get_valid_content($nid) {
  $valid_content = FALSE;
  $node = node_load(intval($nid));

  if ($node && $node->type === _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_STORES_CONTENT_TYPE, 'all')) {
    $valid_content = $node;
  }

  return $valid_content;
}


/**
 *
 * Obtain the list of content which has relation with the stores
 * @return array
 */
function _gmapslivesearch_fetch_stores_by_content() {
  $select= db_select('field_data_gmapslivesearch_stores_options', 'f');
  $select->join('node', 'n', 'n.nid = f.entity_id');
  $select->fields('n', array('nid','title'))->condition('f.deleted', 0, '=');
  $result = $select->execute();

  $items = array();

  foreach ($result as $row) {
    $items[$row->nid] = $row->title;
  }

  return $items;
}


/**
 * Check whether the input string is valid or not against the zipcode pattern 12345.
 * @param type $zip_code
 * @return boolean True if valid otherwise return false;
 */
function _gmapslivesearch_is_valid_zipcode($zip_code) {
  return preg_match('/^[0-9]{5}$/', $zip_code);
}

/**
 * Check whether the input string is valid or not against the pattern City,State.
 * @param type $city_state Parsed string
 * @return boolean True if valid otherwise return false;
 */
function _gmapslivesearch_is_valid_city_state($city_state) {
  return preg_match('/^[A-Za-z]+(\s[A-Za-z]+)?\s*,\s*[A-Za-z]+(\s[A-Za-z]+)?\s*$/', $city_state);
}

/**
 * Validate whether the input address is in valid format.
 */
function gmapslivesearch_is_valid_address_input($address_input) {
  return _gmapslivesearch_is_valid_zipcode($address_input) || _gmapslivesearch_is_valid_city_state($address_input);
}
