<?php
/**
 * @file gmapslivesearch.admin.forms.inc
 * Forms for admin pages
 */
 
// Include helpers
module_load_include('inc', 'gmapslivesearch', 'gmapslivesearch.admin.common');

/**
* Setting options for mobile site
*/
function gmapslivesearch_mobile_config() {
  $form = array();

  $form[GMAPSLIVESEARCH_FIELDSET_DEFAULT_RESULT_MOBILE] = array(
    '#type'           => 'fieldset',
    '#title'          => t('Where to buy results'),
    '#description'    => t('Settings related with the Where to buy form result.'),
    '#collapsible'    => TRUE,
    '#collapsed'      => TRUE,
  );

  $form[GMAPSLIVESEARCH_FIELDSET_DEFAULT_RESULT_MOBILE][GMAPSLIVESEARCH_FIELDSET_DEFAULT_MILE_RADIUS_MOBILE] = array(
    '#type'           => 'textfield',
    '#title'          => t('Results Maxium Radius'),
    '#description'    => t('Maxium distance (miles) between the searching point and the farthest item. The default value for this is 1.'),
    '#size'           =>  50,
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELDSET_DEFAULT_MILE_RADIUS, 'mobile'),
  );

  $form[GMAPSLIVESEARCH_FIELDSET_DEFAULT_RESULT_MOBILE][GMAPSLIVESEARCH_FIELDSET_MAPS_GREAT_DISTANCE_MESSAGE_MOBILE] = array(
    '#type'           =>  'textfield',
    '#title'          =>  t('No results Found Warning Message'),
    '#description'    =>  t('This message will be shown when all stores located are further away than the "Results Maxium Radius" setting above. You can use the #distance# placeholder to be replaced with the max allowed mileage.'),  
    '#size'           =>  110,
    '#default_value'  =>  _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELDSET_MAPS_GREAT_DISTANCE_MESSAGE, 'mobile'),
  );
  
  $form[GMAPSLIVESEARCH_FIELDSET_DEFAULT_RESULT_MOBILE][GMAPSLIVESEARCH_FIELD_ENABLE_DEFAULT_RESULT_MOBILE] = array(
    '#type'           => 'checkbox',
    '#title'          => t('Enable default result'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_ENABLE_DEFAULT_RESULT, 'mobile'),
  );

  $form[GMAPSLIVESEARCH_FIELDSET_DEFAULT_RESULT_MOBILE][GMAPSLIVESEARCH_FIELD_MAX_RESULT_MOBILE] = array(
    '#type'           => 'textfield',
    '#title'          => t('Max results returned'),
    '#size'           => 5,
    '#description'    => t('Set the maximum amount of results.'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_MAX_RESULT, 'mobile'),
  );

  $form[GMAPSLIVESEARCH_FIELDSET_DEFAULT_RESULT_MOBILE][GMAPSLIVESEARCH_FIELD_DEFAULT_MAP_RESULT_LATITUDE_MOBILE] = array(
    '#type'           => 'textfield',
    '#title'          => t('Latitude'),
    '#size'           => 10,
    '#description'    => t('Set the default Latitude address to the Map. Ex.: -34.397.'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_DEFAULT_MAP_RESULT_LATITUDE, 'mobile'),
  );

  $form[GMAPSLIVESEARCH_FIELDSET_DEFAULT_RESULT_MOBILE][GMAPSLIVESEARCH_FIELD_DEFAULT_MAP_RESULT_LONGITUDE_MOBILE] = array(
    '#type'           => 'textfield',
    '#title'          => t('Longitude'),
    '#size'           => 10,
    '#description'    => t('Set the default Longitude address to the Map. Ex.: 150.644.'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_DEFAULT_MAP_RESULT_LONGITUDE, 'mobile'),
  );

  $form[GMAPSLIVESEARCH_FIELDSET_DEFAULT_RESULT_MOBILE][GMAPSLIVESEARCH_FIELD_DEFAULT_MAP_RESULT_ZOOM_MOBILE] = array(
    '#type'           => 'textfield',
    '#title'          => t('Map Zoom'),
    '#size'           => 5,
    '#description'    => t('Set the Zoom distance for the Map. The default value is "4".'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_DEFAULT_MAP_RESULT_ZOOM, 'mobile'),
  );

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_SELECT_MOBILE] = array(
    '#type'           => 'fieldset',
    '#title'          => t('Default fields label'),
    '#collapsed'      => TRUE,
    '#collapsible'    => TRUE,  
  );

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_SELECT_MOBILE][GMAPSLIVESEARCH_FIELD_BUY_NOW_ADDRESS_SEARCH_LABEL_MOBILE] = array(
    '#type'           => 'textfield',
    '#title'          => t('TextBox address label'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_NOW_ADDRESS_SEARCH_LABEL, 'mobile'),
    '#description'    => t('Label for field address search on buy online'),  
  );

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_SELECT_MOBILE][GMAPSLIVESEARCH_FIELD_BUY_NOW_STORE_SEARCH_LABEL_MOBILE] = array(
    '#type'           => 'textfield',
    '#title'          => t('Select stores label'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_NOW_STORE_SEARCH_LABEL, 'mobile'),
    '#description'    => t('Label for field store on buy online'),  
  );

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_SELECT_MOBILE][GMAPSLIVESEARCH_FIELD_FIND_STORE_BTN_MOBILE] = array(
    '#type'           => 'textfield',
    '#title'          => t('Find a Store: \'Search\' button text and title'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_FIND_STORE_BTN, 'mobile'),
    '#description'    => t('\'Search\' button text and title for the Find a Store box'),  
  );
  
  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_SELECT_MOBILE][GMAPSLIVESEARCH_FIELD_BUY_ONLINE_BTN_MAP_MOBILE] = array(
    '#type'           => 'textfield',
    '#title'          => t('Buy Online: \'Show map\' button text and title'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_ONLINE_BTN_MAP, 'mobile'),
    '#description'    => t('\'Show map\' button text and title for the Buy Online box'),  
  );
  
  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_SELECT_MOBILE][GMAPSLIVESEARCH_FIELD_BUY_ONLINE_BTN_LIST_MOBILE] = array(
    '#type'           => 'textfield',
    '#title'          => t('Buy Online: \'Show list\' button text and title'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_ONLINE_BTN_LIST, 'mobile'),
    '#description'    => t('\'Show list\' button text and title for the Buy Online box'),  
  );

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_BLOCK_MOBILE] = array(
    '#type'           => 'fieldset',
    '#title'          => t('Where to buy BLOCK'),
    '#collapsed'      => TRUE,
    '#collapsible'    => TRUE,  
  );

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_BLOCK_MOBILE][GMAPSLIVESEARCH_FIELD_BUY_NOW_ADDRESS_SEARCH_DESC_MOBILE] = array(
    '#type'           =>  'textfield',
    '#title'          => t('Buy online address description'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_NOW_ADDRESS_SEARCH_DESC. 'mobile'),
    '#description'    => t('Description for field address on buy online box'),  
  );

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_BLOCK_MOBILE][GMAPSLIVESEARCH_FIELD_BUY_NOW_STORE_SEARCH_DESC_MOBILE] = array(
    '#type'           =>  'textfield',
    '#title'          => t('Buy online store description'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_NOW_STORE_SEARCH_DESC, 'mobile'),
    '#description'    => t('Description for field store on buy online box'),  
  );

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_BLOCK_MOBILE][GMAPSLIVESEARCH_FIELD_BUY_NOW_STORE_ADDRESS_FIELD_LABEL_MOBILE] = array(
    '#type'           =>  'textfield',
    '#title'          => t('Buy online address field label'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_NOW_STORE_ADDRESS_FIELD_LABEL, 'mobile'),
    '#description'    => t('Label for address field on buy online box.'),  
  );

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_BLOCK_MOBILE][GMAPSLIVESEARCH_FIELD_BUY_NOW_STORE_SEARCH_FIELD_LABEL_MOBILE] = array(
    '#type'           =>  'textfield',
    '#title'          => t('Buy online store field label'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_NOW_STORE_SEARCH_FIELD_LABEL, 'mobile'),
    '#description'    => t('Label for store field on buy online box.'),  
  );

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_BLOCK_MOBILE][GMAPSLIVESEARCH_FIELD_BUY_ONLINE_BTN_MOBILE] = array(
    '#type'           => 'textfield',
    '#title'          => t('Buy Online: \'Go\' button text and title'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_ONLINE_BTN, 'mobile'),
    '#description'    => t('\'Go\' button text and title for the Buy Online box'),  
  );

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_PAGE_MOBILE] = array(
    '#type'           => 'fieldset',
    '#title'          => t('Where to buy PAGE'),
    '#collapsed'      => TRUE,
    '#collapsible'    => TRUE,  
  );

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_PAGE_MOBILE][GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_TITLE_MOBILE] = array(
    '#type'           => 'textfield',
    '#title'          => t('Gmaps live search page title'),
    '#description'    => t('Set the title for Gmaps live search page'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_TITLE, 'mobile'),
  );

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_PAGE_MOBILE][GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_PATH_MOBILE] = array(
    '#type'           => 'textfield',
    '#title'          => t('Path to Gmaps live search page'),
    '#description'    => t('Set the url for Gmaps live search page'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_PATH, 'mobile'),
  );

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_PAGE_MOBILE][GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_ADDRESS_SEARCH_DESC_MOBILE] = array(
    '#type'           =>  'textfield',
    '#title'          => t('Where to buy page address description'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_ADDRESS_SEARCH_DESC, 'mobile'),
    '#description'    => t('Description for field address on where to buy page'),  
  );

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_PAGE_MOBILE][GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_STORE_SEARCH_DESC_MOBILE] = array(
    '#type'           =>  'textfield',
    '#title'          => t('Where to buy page store description'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_STORE_SEARCH_DESC, 'mobile'),
    '#description'    => t('Description for field store on where to buy page'),  
  );

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_PAGE_MOBILE][GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_TITLE_TEXT_MOBILE] = array(
    '#type'           =>  'textfield',
    '#title'          => t('Where to buy page title'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_TITLE_TEXT, 'mobile'),
    '#description'    => t('Page title for where to buy section'),  
  );

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_PAGE_MOBILE][GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_SUBTITLE_TEXT_MOBILE] = array(
    '#type'           =>  'textfield',
    '#title'          => t('Where to buy page subtitle'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_SUBTITLE_TEXT, 'mobile'),
    '#description'    => t('Page subtitle for where to buy section'),  
  );

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_PAGE_MOBILE][GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_ADDRESS_FIELD_LABEL_MOBILE] = array(
    '#type'           =>  'textfield',
    '#title'          => t('Where to buy address field label'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_ADDRESS_FIELD_LABEL, 'mobile'),
    '#description'    => t('Label for address field on Where to buy page.'),  
  );

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_PAGE_MOBILE][GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_STORE_FIELD_LABEL_MOBILE] = array(
    '#type'           =>  'textfield',
    '#title'          => t('Where to buy store field label'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_STORE_FIELD_LABEL, 'mobile'),
    '#description'    => t('Label for store field on Where to buy page.'),  
  );

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_PAGE_MOBILE][GMAPSLIVESEARCH_FIELD_BUY_ONLINE_BTN_PAGE_MOBILE] = array(
    '#type'           => 'textfield',
    '#title'          => t('Buy Online: \'Go\' button text and title'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_ONLINE_BTN_PAGE, 'mobile'),
    '#description'    => t('\'Go\' button text and title for the Buy Online box'),  
  );

  $form[GMAPSLIVESEARCH_ERROR_MESSAGES_MOBILE] = array(
    '#type'           => 'fieldset',
    '#title'          => t('Validation Messages'),
    '#collapsible'    => TRUE,
    '#collapsed'      => TRUE,
  );

  $form[GMAPSLIVESEARCH_ERROR_MESSAGES_MOBILE][GMAPSLIVESEARCH_ERROR_MESSAGE_ADDRESS_FIELD_MOBILE] = array(
    '#type'           => 'textfield',
    '#title'          => t('Address Error Message'),
    '#description'    => t('Error message for the address field.'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_ERROR_MESSAGE_ADDRESS_FIELD, 'mobile'), 
  );
  
  $form[GMAPSLIVESEARCH_FIELDSET_MAPS_BULLETS_MOBILE] = array(
    '#type'           => 'fieldset',
    '#title'          => t('Maps bullets'),
    '#description'    => t('Bullets used on google maps results.'),
    '#collapsible'    => TRUE,
    '#collapsed'      => TRUE,
  );
  
  $form[GMAPSLIVESEARCH_FIELDSET_MAPS_BULLETS_MOBILE][GMAPSLIVESEARCH_FIELD_BULLETS_TTF_MOBILE] = array(
    '#type' => 'select',
    '#title'          => t('Font type'),
    '#description'    => t('Select a font to generate the marker.'),
    '#options'        => _gmapslivesearch_get_default_fonts(),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BULLETS_TTF, 'mobile'),
  );
  
  $form[GMAPSLIVESEARCH_FIELDSET_MAPS_BULLETS_MOBILE][GMAPSLIVESEARCH_FIELD_BULLETS_TTF_FILE_MOBILE] = array(
    '#type'           => 'file',
    '#title'          => t('Upload a font'),
    '#description'    => t('The font must be a TTF.'),
    '#states' => array(
      'visible' => array(
        ':input[name="' . GMAPSLIVESEARCH_FIELD_BULLETS_TTF_MOBILE . '"]' => array('value' => 'upload'),
      ),
    ),
    '#element_validate' => array('_gmapslivesearch_ttf_file_validate'),
    '#file_name' => 'ttf_file_mobile.ttf',
  );
  
  $form[GMAPSLIVESEARCH_FIELDSET_MAPS_BULLETS_MOBILE][GMAPSLIVESEARCH_FIELD_BULLETS_TTF_FILE_UPLOADED_MOBILE] = array(
    '#type'   => 'item',
    '#markup' => '<b>' . t('Uploaded TTF file') . ': </b>' . _gmapslivesearch_get_ttf_file_uploaded(true),
    '#states' => array(
      'visible' => array(
        ':input[name="'.GMAPSLIVESEARCH_FIELD_BULLETS_TTF_MOBILE.'"]' => array('value' => 'upload'),
      ),
    ),
  );
  
  $form[GMAPSLIVESEARCH_FIELDSET_MAPS_BULLETS_MOBILE][GMAPSLIVESEARCH_FIELD_BULLETS_FONT_SIZE_MOBILE] = array(
    '#type' => 'select',
    '#title'          => t('Font size'),
    '#description'    => t('Select a font size to generate the marker.'),
    '#options'        => _gmapslivesearch_get_font_sizes(),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BULLETS_FONT_SIZE, 'mobile'),
  );
  
  $form[GMAPSLIVESEARCH_FIELDSET_MAPS_BULLETS_MOBILE][GMAPSLIVESEARCH_FIELD_BULLETS_FONT_COLOR_MOBILE] = array(
    '#type'           => 'textfield',
    '#title'          => t('Font color'),
    '#description'    => t('Use hexadecimal.'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BULLETS_FONT_COLOR, 'mobile'),
  );
  
  $form[GMAPSLIVESEARCH_FIELDSET_MAPS_BULLETS_MOBILE][GMAPSLIVESEARCH_FIELD_BULLETS_FONT_AUTO_MARGINY_MOBILE] = array(
    '#type'           => 'checkbox',
    '#title'          => t('Vertical align'),
    '#description'    => t('If this option is selected, the text will be centered vertically.'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BULLETS_FONT_AUTO_MARGINY, 'mobile'),  
  );
  
  $form[GMAPSLIVESEARCH_FIELDSET_MAPS_BULLETS_MOBILE][GMAPSLIVESEARCH_FIELD_BULLETS_FONT_MARGIN_TOP_MOBILE] = array(
    '#type'           => 'textfield',
    '#size'           => 5,
    '#title'          => t('Font margin top'),
    '#description'    => t('Select margin top (in pixels) to generate the text in the marker.'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BULLETS_FONT_MARGIN_TOP, 'mobile'),
    '#states' => array(
      'visible' => array(
        ':input[name="' . GMAPSLIVESEARCH_FIELD_BULLETS_FONT_AUTO_MARGINY_MOBILE . '"]' => array('checked' => false),
      ),
    ),
  );
  
  $form[GMAPSLIVESEARCH_FIELDSET_MAPS_BULLETS_MOBILE][GMAPSLIVESEARCH_FIELD_BULLETS_FONT_AUTO_MARGINX_MOBILE] = array(
    '#type'           => 'checkbox',
    '#title'          => t('Centered text'),
    '#description'    => t('If this option is selected, the text will be centered horizontally.'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BULLETS_FONT_AUTO_MARGINX, 'mobile'),  
  );
  
  $form[GMAPSLIVESEARCH_FIELDSET_MAPS_BULLETS_MOBILE][GMAPSLIVESEARCH_FIELD_BULLETS_FONT_MARGIN_LEFT_MOBILE] = array(
    '#type'           => 'textfield',
    '#size'           => 5,
    '#title'          => t('Font margin left'),
    '#description'    => t('Select margin left (in pixels) to generate the text in the marker.'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BULLETS_FONT_MARGIN_LEFT, 'mobile'),
    '#states' => array(
      'visible' => array(
        ':input[name="' . GMAPSLIVESEARCH_FIELD_BULLETS_FONT_AUTO_MARGINX_MOBILE . '"]' => array('checked' => false),
      ),
    ),
  );
  
  $form[GMAPSLIVESEARCH_FIELDSET_MAPS_BULLETS_MOBILE][GMAPSLIVESEARCH_MAP_BULLETS_IMAGE_MOBILE] = array(
    '#type'           => 'file',
    '#title'          => t('Background image for bullet'),
    '#description'    => t('The image must be a png.'),
    '#element_validate' => array('_gmapslivesearch_map_bullet_validate'),
    '#file_name' => 'bullet_background_mobile.png',
  );
  
  $form[GMAPSLIVESEARCH_FIELDSET_MAPS_BULLETS_MOBILE][GMAPSLIVESEARCH_MAP_BULLETS_SUBMIT_PREVIEW] = array(
    '#type' => 'button',
    '#value' => t('Preview'),
    '#ajax'=> array(
        'callback'=>'_gmapslivesearch_get_image_preview',
        'wrapper'=> 'bullet-preview',
        'method'=> 'replace',
        'effect'=> 'fade',
     ),
  );
  
  $form[GMAPSLIVESEARCH_FIELDSET_MAPS_BULLETS_MOBILE][GMAPSLIVESEARCH_MAP_BULLETS_ITEM_PREVIEW] = array(
	  '#type'   => 'item',
	  '#prefix'  => '<div id="bullet-preview">',
    '#suffix'  => '</div>',
  );
  
  $form[GMAPSLIVESEARCH_FIELDSET_MAPS_BULLETS_MOBILE][GMAPSLIVESEARCH_MAP_BULLETS_IMAGE_PREVIEW_MOBILE] = array(
    '#type'   => 'item',
    '#markup' => '<b>' . t('Uploaded Image') . ': </b>' . _gmapslivesearch_get_image_file_uploaded(true),
  );
  
  $form[GMAPSLIVESEARCH_FIELD_REMOVE_BUY_NOW_BUTTON_MOBILE] = array(
    '#type'           => 'checkbox',
    '#prefix'         => t('<b>Remove Search Button</b>'),
    '#title'          => t('Remove the Button in Buy Now select field'),
    '#description'    => t('If this option is selected, removes the "GO" Button in Buy now field, leaving the automatic redirection to link when selecting a store.'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_REMOVE_BUY_NOW_BUTTON, 'mobile'),  
  );

  $form['#attributes'] = array('enctype' => "multipart/form-data");
  $form['#submit'][] = 'gmapslivesearch_admin_config_submit';
 
  return system_settings_form($form);
}
