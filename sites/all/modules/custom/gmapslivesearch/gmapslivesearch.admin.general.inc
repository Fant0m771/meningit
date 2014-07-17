<?php 

/**
 * 
 * 
 * @file gmapslivesearch.admin.forms.inc
 * 
 * Forms for admin pages
 */

// Include helpers
module_load_include('inc', 'gmapslivesearch', 'gmapslivesearch.admin.common');

/**
 * Setting the API configurations
 */
function gmapslivesearch_general_config() {
  $form = array();  

  $form[GMAPSLIVESEARCH_FIELDSET_GOOGLEAPIKEY] = array(
    '#type'           => 'fieldset',
    '#title'          => t('Google Search API'),
    '#collapsible'    => TRUE,
    '#collapsed'      => FALSE,
  );

  $form[GMAPSLIVESEARCH_FIELDSET_GOOGLEAPIKEY][GMAPSLIVESEARCH_FIELD_GOOGLEAPIKEY] = array(
    '#type'           => 'textfield',
    '#title'          => t('Google Search API key'),
    '#description'    => t('Google Search API key. To generate it go to http://code.google.com/intl/en/apis/loader/signup.html'),  
    '#size'           => 110,  
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_GOOGLEAPIKEY, 'all'),
  );

  $form[GMAPSLIVESEARCH_SHOW_ERROR_INLINE_FIND_ONLINE_BLOCK] = array(
    '#type'            => 'checkbox',
    '#title'           => t('Show error inline find online'),
    '#description'     => t('Whether or not to show validation form error on find online block at the current page otherwise redirects to where yo buy page'),
    '#default_value'   => _gmapslivesearch_get_value(GMAPSLIVESEARCH_SHOW_ERROR_INLINE_FIND_ONLINE_BLOCK, 'all'),
  );
  
  return system_settings_form($form);
}
