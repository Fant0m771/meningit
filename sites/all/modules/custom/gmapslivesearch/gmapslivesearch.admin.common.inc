<?php
/**
 * @file gmapslivesearch.admin.common.inc
 * Common helpers for admin forms
 */

/**
 * Get a default descript used in many fields
 */
function _gmapslivesearch_get_miles_to_search_description() {
  $description = '<p>' . 
      t('The possible values this field can contain. Enter one value per line, in the format key|label.');
  $description .= '<br/>' . 
      t('The key is the stored value, and must be numeric. The label will be used in displayed values and edit forms.');
  $description .= '<br/>' . 
      t('The label is optional: if a line contains a single number, it will be used as key and label.');
  $description .= '<br/>' . t('Lists of labels are also accepted (one label per line), only if the field does not ' . 
          'hold any values yet. Numeric keys will be automatically generated from the positions in the list.');
  return $description;
}

/**
 * Helper function
 * Get default fonts
 */
function _gmapslivesearch_get_default_fonts() {
  $fonts = array(
    drupal_get_path('module', 'gmapslivesearch') . '/ttf/Amble-Regular.ttf' => 'Amble Regular',
    drupal_get_path('module', 'gmapslivesearch') . '/ttf/Cantarell-Regular.ttf' => 'Cantarell Regular',
    drupal_get_path('module', 'gmapslivesearch') . '/ttf/DroidSans.ttf' => 'DroidSans',
    drupal_get_path('module', 'gmapslivesearch') . '/ttf/new_athena_unicode.ttf' => 'New Athena Unicode',
    drupal_get_path('module', 'gmapslivesearch') . '/ttf/OpenSans-Regular.ttf' => 'Open Sans Regular',
    'upload' => 'Upload a TTF file',
  );
  return $fonts;
}

/**
 * Helper function
 * Get font sizes
 */
function _gmapslivesearch_get_font_sizes() {
  $font_sizes = array();
  for ($i = 5; $i < 25; $i++) {
    $font_sizes[$i] = $i;
  }
  return $font_sizes;
}

/**
 * Helper function
 * Validator for background file field.
 */
function _gmapslivesearch_map_bullet_validate($element, &$form_state) {
  $form_key = implode('_', $element['#parents']);

  if(empty($_FILES['files']['name'][$form_key]) || form_get_error($element)) {
    return;
  }
  
  $file = file_save_upload($form_key, array(
    'file_validate_is_image' => array(),
    'file_validate_extensions' => array('png'),
  ));
  
  if($file) {
    $file->filename = $element['#file_name'];      
    if ($file = file_move($file, 'temporary://')) {
      $form_state['values'][$form_key] = $file;
    }
    else {
      drupal_set_message(t('The uploaded file %filename was unable to be saved. The destination directory may not be writable.', array('%filename' => $file->filename)), 'error');
    }
  }
  else {
    form_set_error($form_key, t('No file was uploaded.'));
  }
}

/**
 * Helper function
 * Validator for ttf file field.
 */
function _gmapslivesearch_ttf_file_validate($element, &$form_state) {
  
  $form_key = implode('_', $element['#parents']);
  
  $mobile = ($form_state['build_info']['form_id'] == 'gmapslivesearch_mobile_config') ? true : false;
  
  $constant_value_parent = ($mobile === false) ? GMAPSLIVESEARCH_FIELD_BULLETS_TTF : GMAPSLIVESEARCH_FIELD_BULLETS_TTF_MOBILE;

  if($form_state['values'][$constant_value_parent] != 'upload') {    
    return;
  }
  
  if(empty($_FILES['files']['name'][$form_key]) || form_get_error($element)) {
    return;
  }
  
  $file = file_save_upload($form_key, array(
    'file_validate_extensions' => array('ttf'),
  ));
  
  if($file) {
    $file->filename = $element['#file_name'];      
    if ($file = file_move($file, 'temporary://')) {
      $form_state['values'][$form_key] = $file;
    }
    else {
      drupal_set_message(t('The uploaded file %filename was unable to be saved. The destination directory may not be writable.', array('%filename' => $file->filename)), 'error');
    }
  }
  else {
    form_set_error($form_key, t('No file was uploaded.'));
  }
}

/**
 * Helper function
 * Return TTF file uploaded.
 */
function _gmapslivesearch_get_ttf_file_uploaded($mobile = false) {
  $device_type = ($mobile === false) ? false : 'mobile';
  $ttf = _gmapslivesearch_get_value(GMAPSLIVESEARCH_MAP_BULLETS_TTF_FILE, $device_type);
  if(strlen($ttf) > 4) {
    return substr($ttf, strripos($ttf, "/"));
  }
  return t('No TTF file uploaded.');
}

/**
 * Helper function
 * Return image file uploaded.
 */
function _gmapslivesearch_get_image_file_uploaded($mobile = false) {
  if($mobile === true) {
    $file = 'admin/config/gmapslivesearch/marker/preview/mobile';
  } else {
    $file = 'admin/config/gmapslivesearch/marker/preview/desktop';
  }
  return theme('image', array('path' => $file, 'alt'   => 'Bullet', 'title' => 'Bullet'));
}

/**
 * Helper function
 * Return the bullet preview
 */
function _gmapslivesearch_get_image_preview($form, $form_state) {
  
  module_load_include('inc', 'gmapslivesearch', 'gmapslivesearch.markers');
  
  // Detect form
  $mobile = ($form['form_id']['#value'] == 'gmapslivesearch_mobile_config') ? TRUE : FALSE;
  
  // Set suffix
  $suffix = $mobile ? GMAPSLIVESEARCH_SUFFIX_MOBILE : GMAPSLIVESEARCH_SUFFIX_DESKTOP;
  
  // init values
  $preview_bullet = array(
    'image_path'    => _gmapslivesearch_get_bullet_image($mobile?'mobile':'desktop'),
    'ttf'           => $form_state['values'][GMAPSLIVESEARCH_FIELD_BULLETS_TTF . $suffix],
    'auto_margin_y' => $form_state['values'][GMAPSLIVESEARCH_FIELD_BULLETS_FONT_AUTO_MARGINY . $suffix],
    'auto_margin_x' => $form_state['values'][GMAPSLIVESEARCH_FIELD_BULLETS_FONT_AUTO_MARGINX . $suffix],
    'margin_y'      => $form_state['values'][GMAPSLIVESEARCH_FIELD_BULLETS_FONT_MARGIN_TOP . $suffix],
    'margin_x'      => $form_state['values'][GMAPSLIVESEARCH_FIELD_BULLETS_FONT_MARGIN_LEFT . $suffix],
    'font_size'     => $form_state['values'][GMAPSLIVESEARCH_FIELD_BULLETS_FONT_SIZE . $suffix],
    'color'         => $form_state['values'][GMAPSLIVESEARCH_FIELD_BULLETS_FONT_COLOR . $suffix],
  );
  // Upload background bullet
  if(!empty($form_state['values'][GMAPSLIVESEARCH_MAP_BULLETS_IMAGE . $suffix])) {
    $file_background = $form_state['values'][GMAPSLIVESEARCH_MAP_BULLETS_IMAGE . $suffix];
    
    if($file_background) {
      $preview_bullet['image_path'] = $file_background->uri;
    }
    else {
      // TO DO
      // Display error
    }
  }
  
  // Upload ttf file
  if($form_state['values'][GMAPSLIVESEARCH_FIELD_BULLETS_TTF . $suffix] == 'upload') {
    $file_ttf = $form_state['values'][GMAPSLIVESEARCH_FIELD_BULLETS_TTF_FILE . $suffix];
    
    if($file_ttf) {
      $preview_bullet['ttf'] = drupal_realpath($file_ttf->uri);
    }
    else {
      // TO DO
      // Display error
    }
  } 
  else {
    $preview_bullet['ttf'] = drupal_realpath($form_state['values'][GMAPSLIVESEARCH_FIELD_BULLETS_TTF . $suffix]);
  }
  
  //Generating the preview file
  $preview_file = drupal_realpath(file_build_uri(GMAPSLIVESEARCH_MAP_BULLETS_IMAGE_FOLDER . 'preview.png'));
  _gmapslivesearch_generate_marker_image($preview_file, '10', $preview_bullet);
  $image_base64 = base64_encode(file_get_contents($preview_file, true));
  //delete it because is not needed any more
  unlink($preview_file);
  
  $form[GMAPSLIVESEARCH_FIELDSET_MAPS_BULLETS . $suffix][GMAPSLIVESEARCH_MAP_BULLETS_ITEM_PREVIEW] = array (
	'#type'   => 'item',
    '#title'   => t('Preview:'),
    '#prefix'  => '<div id="bullet-preview">',
    '#markup'  => '<img src="data:image/png;base64,' . $image_base64 . '" />',
    '#suffix'  => '</div>',
  );
  
  return $form[GMAPSLIVESEARCH_FIELDSET_MAPS_BULLETS . $suffix][GMAPSLIVESEARCH_MAP_BULLETS_ITEM_PREVIEW];
}

/**
 * Submit function for desktop and mobile config
 */
function gmapslivesearch_admin_config_submit($form, $form_state) {
  // Detect form
  $mobile = ($form['form_id']['#value'] == 'gmapslivesearch_mobile_config') ? true : false;
  // Set suffix
  $suffix = $mobile ? GMAPSLIVESEARCH_SUFFIX_MOBILE : GMAPSLIVESEARCH_SUFFIX_DESKTOP;
  // Move the background image
  $file = $form_state['values'][GMAPSLIVESEARCH_MAP_BULLETS_IMAGE . $suffix];
  if(is_object($file)) {
    unset($form_state['values'][GMAPSLIVESEARCH_MAP_BULLETS_IMAGE . $suffix]);
    $folder = constant('GMAPSLIVESEARCH_MAP_BULLETS_IMAGE_FOLDER' . strtoupper($suffix));
    $destination = file_build_uri($folder) . '/' . $file->filename;
    $file = file_move($file, $destination, FILE_EXISTS_REPLACE);
    $file->status = FILE_STATUS_PERMANENT;
    file_save($file);
    variable_set('gmapslivesearch_map_bullet_image_file'.$suffix, $file->filename);    
  }
  // Move ttf file
  $constant_value_parent = ($mobile === false) ? GMAPSLIVESEARCH_FIELD_BULLETS_TTF : GMAPSLIVESEARCH_FIELD_BULLETS_TTF_MOBILE;
  $file = $form_state['values'][GMAPSLIVESEARCH_FIELD_BULLETS_TTF_FILE . $suffix];
  if(is_object($file) && $form_state['values'][$constant_value_parent] == 'upload') {
    unset($form_state['values'][GMAPSLIVESEARCH_FIELD_BULLETS_TTF_FILE . $suffix]);
    $folder = constant('GMAPSLIVESEARCH_MAP_BULLETS_TTF_FOLDER' . strtoupper($suffix));
    $destination = file_build_uri($folder) . '/' . $file->filename;
    $file = file_move($file, $destination, FILE_EXISTS_REPLACE);
    $file->status = FILE_STATUS_PERMANENT;
    file_save($file);
    variable_set('gmapslivesearch_field_bullets_ttf_file'.$suffix, $file->filename);
  }
  //Clear bullets cache
  module_load_include('inc', 'gmapslivesearch', 'gmapslivesearch.markers');
  _gmapslivesearch_clear_bullets_cache();
}
