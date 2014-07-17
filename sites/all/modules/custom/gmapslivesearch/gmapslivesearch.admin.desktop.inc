<?php
/**
 * @file gmapslivesearch.admin.forms.inc
 * Forms for admin pages
 */

// Include helpers
module_load_include('inc', 'gmapslivesearch', 'gmapslivesearch.admin.common');

/**
 * Setting options for desktop site
 */
function gmapslivesearch_desktop_config() {
  $form = array();

  $form[GMAPSLIVESEARCH_FIELDSET_DEFAULT_RESULT] = array(
    '#type'           => 'fieldset',
    '#title'          => t('Where to buy results'),
    '#description'    => t('Settings related with the Where to buy form result.'),
    '#collapsible'    => TRUE,
    '#collapsed'      => TRUE,
  );

  $form[GMAPSLIVESEARCH_FIELDSET_DEFAULT_RESULT][GMAPSLIVESEARCH_FIELDSET_DEFAULT_MILE_RADIUS] = array(
    '#type'           => 'textfield',
    '#title'          => t('Results Maxium Radius'),
    '#description'    => t('Maxium distance between the searching point and the farthest item. The default value for this is 1.'),
    '#size'           => 50,
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELDSET_DEFAULT_MILE_RADIUS, 'desktop'),
  );
  
  $form[GMAPSLIVESEARCH_FIELDSET_DEFAULT_RESULT][GMAPSLIVESEARCH_FIELDSET_MAPS_GREAT_DISTANCE_MESSAGE] = array(
    '#type'           =>  'textfield',
    '#title'          =>  t('No results Found Warning Message'),
    '#description'    =>  t('This message will be shown when all stores located are further away than the "Results Maxium Radius" setting above. You can use the #distance# placeholder to be replaced with the max allowed mileage.'),  
    '#size'           =>  110,
    '#default_value'  =>  _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELDSET_MAPS_GREAT_DISTANCE_MESSAGE , 'desktop'),
  );
  
  $form[GMAPSLIVESEARCH_FIELDSET_DEFAULT_RESULT][GMAPSLIVESEARCH_FIELD_ENABLE_DEFAULT_RESULT] = array(
    '#type'           => 'checkbox',
    '#title'          => t('Enable default result'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_ENABLE_DEFAULT_RESULT, 'desktop'),
  );

  $form[GMAPSLIVESEARCH_FIELDSET_DEFAULT_RESULT][GMAPSLIVESEARCH_FIELD_MAX_RESULT] = array(
    '#type'           => 'textfield',
    '#title'          => t('Maxium results'),
    '#size'           => 5,
    '#description'    => t('Set the maximum amount of results.'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_MAX_RESULT, 'desktop'),
  );

  $form[GMAPSLIVESEARCH_FIELDSET_DEFAULT_RESULT][GMAPSLIVESEARCH_FIELD_DEFAULT_MAP_RESULT_LATITUDE] = array(
    '#type'           => 'textfield',
    '#title'          => t('Starting latitude'),
    '#size'           => 10,
    '#description'    => t('Set the default Latitude address to the Map. Ex.: -34.397.'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_DEFAULT_MAP_RESULT_LATITUDE, 'desktop'),
  );

  $form[GMAPSLIVESEARCH_FIELDSET_DEFAULT_RESULT][GMAPSLIVESEARCH_FIELD_DEFAULT_MAP_RESULT_LONGITUDE] = array(
    '#type'           => 'textfield',
    '#title'          => t('Starting longitude'),
    '#size'           => 10,
    '#description'    => t('Set the default Longitude address to the Map. Ex.: 150.644.'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_DEFAULT_MAP_RESULT_LONGITUDE, 'desktop'),
  );

  $form[GMAPSLIVESEARCH_FIELDSET_DEFAULT_RESULT][GMAPSLIVESEARCH_FIELD_DEFAULT_MAP_RESULT_ZOOM] = array(
    '#type'           => 'textfield',
    '#title'          => t('Map Zoom'),
    '#size'           => 5,
    '#description'    => t('Set the Zoom distance for the Map. The default value is "4".'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_DEFAULT_MAP_RESULT_ZOOM, 'desktop'),
  );


  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_SELECT] = array(
    '#type'           => 'fieldset',
    '#title'          => t('Default fields label'),
    '#collapsed'      => TRUE,
    '#collapsible'    => TRUE,  
  );

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_SELECT][GMAPSLIVESEARCH_FIELD_BUY_NOW_ADDRESS_SEARCH_LABEL] = array(
    '#type'           => 'textfield',
    '#title'          => t('TextBox address label'),
    '#description'    => t('Label for field address search on buy online'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_NOW_ADDRESS_SEARCH_LABEL, 'desktop'),
  );

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_SELECT][GMAPSLIVESEARCH_FIELD_BUY_NOW_STORE_SEARCH_LABEL] = array(
    '#type'           => 'textfield',
    '#title'          => t('Select stores label'),
    '#description'    => t('Label for field store on buy online'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_NOW_STORE_SEARCH_LABEL, 'desktop'),
  );

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_SELECT][GMAPSLIVESEARCH_FIELD_FIND_STORE_BTN] = array(
    '#type'           => 'textfield',
    '#title'          => t('Find a Store: \'Search\' button text and title'),
    '#description'    => t('\'Search\' button text and title for the Find a Store box'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_FIND_STORE_BTN, 'desktop'),
  );  

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_BLOCK] = array(
    '#type'           => 'fieldset',
    '#title'          => t('Where to buy BLOCK'),
    '#collapsed'      => TRUE,
    '#collapsible'    => TRUE,  
  );

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_BLOCK][GMAPSLIVESEARCH_FIELD_BUY_NOW_ADDRESS_SEARCH_DESC] = array(
    '#type'           =>  'textfield',
    '#title'          => t('Buy online address description'),
    '#description'    => t('Description for field address on buy online box'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_NOW_ADDRESS_SEARCH_DESC, 'desktop'),
  );

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_BLOCK][GMAPSLIVESEARCH_FIELD_BUY_NOW_STORE_SEARCH_DESC] = array(
    '#type'           =>  'textfield',
    '#title'          => t('Buy online store description'),
    '#description'    => t('Description for field store on buy online box'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_NOW_STORE_SEARCH_DESC, 'desktop'),
  );

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_BLOCK][GMAPSLIVESEARCH_FIELD_BUY_NOW_STORE_ADDRESS_FIELD_LABEL] = array(
    '#type'           =>  'textfield',
    '#title'          => t('Buy online address field label'),
    '#description'    => t('Label for address field on buy online box.'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_NOW_STORE_ADDRESS_FIELD_LABEL, 'desktop'),
  );

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_BLOCK][GMAPSLIVESEARCH_FIELD_BUY_NOW_STORE_SEARCH_FIELD_LABEL] = array(
    '#type'           =>  'textfield',
    '#title'          => t('Buy online store field label'),
    '#description'    => t('Label for store field on buy online box.'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_NOW_STORE_SEARCH_FIELD_LABEL, 'desktop'),
  );

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_BLOCK][GMAPSLIVESEARCH_FIELD_BUY_ONLINE_BTN] = array(
    '#type'           => 'textfield',
    '#title'          => t('Buy Online: \'Go\' button text and title'),
    '#description'    => t('\'Go\' button text and title for the Buy Online box'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_ONLINE_BTN, 'desktop'),
  );

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_PAGE] = array(
    '#type'           => 'fieldset',
    '#title'          => t('Where to buy PAGE'),
    '#collapsed'      => TRUE,
    '#collapsible'    => TRUE,  
  );

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_PAGE][GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_TITLE] = array(
    '#type'           => 'textfield',
    '#title'          => t('Gmaps live search page title'),
    '#description'    => t('Set the title for Gmaps live search page'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_TITLE, 'desktop'),
  );

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_PAGE][GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_PATH] = array(
    '#type'           => 'textfield',
    '#title'          => t('Path to Gmaps live search page'),
    '#description'    => t('Set the url for Gmaps live search page'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_PATH, 'desktop'),
  );

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_PAGE][GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_ADDRESS_SEARCH_DESC] = array(
    '#type'           =>  'textfield',
    '#title'          => t('Where to buy page address description'),
    '#description'    => t('Description for field address on where to buy page'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_ADDRESS_SEARCH_DESC, 'desktop'),
  );

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_PAGE][GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_STORE_SEARCH_DESC] = array(
    '#type'           =>  'textfield',
    '#title'          => t('Where to buy page store description'),
    '#description'    => t('Description for field store on where to buy page'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_STORE_SEARCH_DESC, 'desktop'),
  );

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_PAGE][GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_TITLE_TEXT] = array(
    '#type'           =>  'textfield',
    '#title'          => t('Where to buy page title'),
    '#description'    => t('Page title for where to buy section'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_TITLE_TEXT, 'desktop'),
  );

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_PAGE][GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_SUBTITLE_TEXT] = array(
    '#type'           =>  'textfield',
    '#title'          => t('Where to buy page subtitle'),
    '#description'    => t('Page subtitle for where to buy section'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_SUBTITLE_TEXT, 'desktop'),
  );

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_PAGE][GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_ADDRESS_FIELD_LABEL] = array(
    '#type'           =>  'textfield',
    '#title'          => t('Where to buy address field label'),
    '#description'    => t('Label for address field on Where to buy page.'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_ADDRESS_FIELD_LABEL, 'desktop'),
  );

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_PAGE][GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_STORE_FIELD_LABEL] = array(
    '#type'           =>  'textfield',
    '#title'          => t('Where to buy store field label'),
    '#description'    => t('Label for store field on Where to buy page.'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_STORE_FIELD_LABEL, 'desktop'),
  );

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_PAGE][GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_RESULTS_SCROLL_JS_DRAG_HEIGHT] = array(
    '#type'           =>  'textfield',
    '#title'          => t('Where to buy results scroll jsDrag height'),
    '#description'    => t('Store results list jsDrag scroll height in pixels. Do NOT include "px" in its value, it expects only an integer.'),  
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_RESULTS_SCROLL_JS_DRAG_HEIGHT, 'desktop'),
  );

  $form[GMAPSLIVESEARCH_FIELDSET_BUY_ONLINE_PAGE][GMAPSLIVESEARCH_FIELD_BUY_ONLINE_BTN_PAGE] = array(
    '#type'           => 'textfield',
    '#title'          => t('Buy Online: \'Go\' button text and title'),
    '#description'    => t('\'Go\' button text and title for the Buy Online box'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_ONLINE_BTN_PAGE, 'desktop'),
  );

  $form[GMAPSLIVESEARCH_ERROR_MESSAGES] = array(
    '#type'           => 'fieldset',
    '#title'          => t('Validation Messages'),
    '#collapsible'    => TRUE,
    '#collapsed'      => TRUE,
  );

  $form[GMAPSLIVESEARCH_ERROR_MESSAGES][GMAPSLIVESEARCH_ERROR_MESSAGE_ADDRESS_FIELD] = array(
    '#type'           => 'textfield',
    '#title'          => t('Address Error Message'),
    '#description'    => t('Error message for the address field.'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_ERROR_MESSAGE_ADDRESS_FIELD, 'desktop'), 
  );
  
  $form[GMAPSLIVESEARCH_FIELDSET_MAPS_BULLETS] = array(
    '#type'           => 'fieldset',
    '#title'          => t('Maps bullets'),
    '#description'    => t('Bullets used on google maps results.'),
    '#collapsible'    => TRUE,
    '#collapsed'      => TRUE,
  );
  
  $form[GMAPSLIVESEARCH_FIELDSET_MAPS_BULLETS][GMAPSLIVESEARCH_FIELD_BULLETS_TTF] = array(
    '#type' => 'select',
    '#title'          => t('Font type'),
    '#description'    => t('Select a font to generate the marker.'),
    '#options'        => _gmapslivesearch_get_default_fonts(),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BULLETS_TTF, 'desktop'),
  );
  
  $form[GMAPSLIVESEARCH_FIELDSET_MAPS_BULLETS][GMAPSLIVESEARCH_FIELD_BULLETS_TTF_FILE] = array(
    '#type'           => 'file',
    '#title'          => t('Upload a font'),
    '#description'    => t('The font must be a TTF.'),
    '#states' => array(
      'visible' => array(
        ':input[name="' . GMAPSLIVESEARCH_FIELD_BULLETS_TTF . '"]' => array('value' => 'upload'),
      ),
    ),
    '#element_validate' => array('_gmapslivesearch_ttf_file_validate'),
    '#file_name' => 'ttf_file.ttf',
  );
  
  $form[GMAPSLIVESEARCH_FIELDSET_MAPS_BULLETS][GMAPSLIVESEARCH_FIELD_BULLETS_TTF_FILE_UPLOADED] = array(
    '#type'   => 'item',
    '#markup' => '<b>' . t('Uploaded TTF file') . ': </b>' . _gmapslivesearch_get_ttf_file_uploaded(),
    '#states' => array(
      'visible' => array(
        ':input[name="' . GMAPSLIVESEARCH_FIELD_BULLETS_TTF . '"]' => array('value' => 'upload'),
      ),
    ),
  );
  
  $form[GMAPSLIVESEARCH_FIELDSET_MAPS_BULLETS][GMAPSLIVESEARCH_FIELD_BULLETS_FONT_SIZE] = array(
    '#type' => 'select',
    '#title'          => t('Font size'),
    '#description'    => t('Select a font size to generate the marker.'),
    '#options'        => _gmapslivesearch_get_font_sizes(),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BULLETS_FONT_SIZE, 'desktop'),
  );
  
  $form[GMAPSLIVESEARCH_FIELDSET_MAPS_BULLETS][GMAPSLIVESEARCH_FIELD_BULLETS_FONT_COLOR] = array(
    '#type'           => 'textfield',
    '#title'          => t('Font color'),
    '#description'    => t('Use hexadecimal.'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BULLETS_FONT_COLOR, 'desktop'),
  );
  
  $form[GMAPSLIVESEARCH_FIELDSET_MAPS_BULLETS][GMAPSLIVESEARCH_FIELD_BULLETS_FONT_AUTO_MARGINY] = array(
    '#type'           => 'checkbox',
    '#title'          => t('Vertical align'),
    '#description'    => t('If this option is selected, the text will be centered vertically.'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BULLETS_FONT_AUTO_MARGINY, 'desktop'),  
  );
  
  $form[GMAPSLIVESEARCH_FIELDSET_MAPS_BULLETS][GMAPSLIVESEARCH_FIELD_BULLETS_FONT_MARGIN_TOP] = array(
    '#type'           => 'textfield',
    '#size'           => 5,
    '#title'          => t('Font margin top'),
    '#description'    => t('Select margin top (in pixels) to generate the text in the marker.'),
    '#states' => array(
      'visible' => array(
        ':input[name="' . GMAPSLIVESEARCH_FIELD_BULLETS_FONT_AUTO_MARGINY . '"]' => array('checked' => FALSE),
      ),
    ),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BULLETS_FONT_MARGIN_TOP, 'desktop'),
  );
  
  $form[GMAPSLIVESEARCH_FIELDSET_MAPS_BULLETS][GMAPSLIVESEARCH_FIELD_BULLETS_FONT_AUTO_MARGINX] = array(
    '#type'           => 'checkbox',
    '#title'          => t('Centered text'),
    '#description'    => t('If this option is selected, the text will be centered horizontally.'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BULLETS_FONT_AUTO_MARGINX, 'desktop'),  
  );
  
  $form[GMAPSLIVESEARCH_FIELDSET_MAPS_BULLETS][GMAPSLIVESEARCH_FIELD_BULLETS_FONT_MARGIN_LEFT] = array(
    '#type'           => 'textfield',
    '#size'           => 5,
    '#title'          => t('Font margin left'),
    '#description'    => t('Select margin left (in pixels) to generate the text in the marker.'),
    '#states' => array(
      'visible' => array(
        ':input[name="' . GMAPSLIVESEARCH_FIELD_BULLETS_FONT_AUTO_MARGINX . '"]' => array('checked' => FALSE),
      ),
    ),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BULLETS_FONT_MARGIN_LEFT, 'desktop'),
  );
  
  $form[GMAPSLIVESEARCH_FIELDSET_MAPS_BULLETS][GMAPSLIVESEARCH_MAP_BULLETS_IMAGE] = array(
    '#type'           => 'file',
    '#title'          => t('Bullet image'),
    '#description'    => t('The image must be a png.'),
    '#element_validate' => array('_gmapslivesearch_map_bullet_validate'),
    '#file_name' => 'bullet_background.png',
  );
  
  $form[GMAPSLIVESEARCH_FIELDSET_MAPS_BULLETS][GMAPSLIVESEARCH_MAP_BULLETS_SUBMIT_PREVIEW] = array(
    '#type' => 'button',
    '#value' => t('Preview'),
    '#ajax'=> array(
        'callback'=>'_gmapslivesearch_get_image_preview',
        'wrapper'=> 'bullet-preview',
        'method'=> 'replace',
        'effect'=> 'fade',
     ),
  );
  
  $form[GMAPSLIVESEARCH_FIELDSET_MAPS_BULLETS][GMAPSLIVESEARCH_MAP_BULLETS_ITEM_PREVIEW] = array(
	'#type'   => 'item',
	'#prefix'  => '<div id="bullet-preview">',
    '#suffix'  => '</div>',
  );
  
  $form[GMAPSLIVESEARCH_FIELDSET_MAPS_BULLETS][GMAPSLIVESEARCH_MAP_BULLETS_IMAGE_PREVIEW] = array(
    '#type'   => 'item',
    '#markup' => '<b>' . t('Uploaded Image') . ': </b>' . _gmapslivesearch_get_image_file_uploaded(),
  );
  
  $form[GMAPSLIVESEARCH_FIELD_REMOVE_BUY_NOW_BUTTON] = array(
    '#type'           => 'checkbox',
    '#prefix'         => t('<b>Remove Search Button</b>'),
    '#title'          => t('Remove the Button in Buy Now select field'),
    '#description'    => t('If this option is selected, removes the "GO" Button in Buy now field, leaving the automatic redirection to link when selecting a store.'),
    '#default_value'  => _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_REMOVE_BUY_NOW_BUTTON, 'desktop'),  
  );
  
  $form[GMAPSLIVESEARCH_JQTRANSFORM_OPTION] = array(
    '#type'            => 'checkbox',
    '#prefix'          => t('<b>Apply jqTransform</b>'),
    '#title'           => t('Enable this field to apply jqTranform plugin to form fields.'),
    '#default_value'   => _gmapslivesearch_get_value(GMAPSLIVESEARCH_JQTRANSFORM_OPTION, 'desktop'),
  );
  
  $form['#attributes'] = array('enctype' => "multipart/form-data");
  $form['#submit'][] = 'gmapslivesearch_admin_config_submit';
  
  return system_settings_form($form);
}
