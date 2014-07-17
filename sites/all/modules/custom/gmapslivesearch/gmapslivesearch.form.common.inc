<?php

/**
 * Send vars to JS
 * 
 * @param array $var Key is the var name
 */
function _gmapslivesearch_send_to_js(array $var) {
  drupal_add_js(array('gmapslivesearch' => $var), 'setting');
}
