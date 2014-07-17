<?php

function gmapslivesearch_render_marker($number, $force_mobile_device = false) {
  //Validating data
  $number = intval($number);
  
  if($number == 0) {
    $number = '';
  }

  //Force mobile device if needed
  if($force_mobile_device !== false) {
    $device_type = $force_mobile_device;
  } 
  else {
    $device_type = _gmapslivesearch_return_device_type();
  }
  
  $cache_file_suffix = $device_type == 'mobile'?'_mobile':'';
  $cache_file_name = GMAPSLIVESEARCH_MAP_BULLETS_IMAGE_FOLDER_CACHE . 'bullet_' . $number . $cache_file_suffix . '.png';
  $cache_path = drupal_realpath(file_build_uri($cache_file_name));
  
  if (!file_exists($cache_path)) {
    //Generate cachefile for image, if it doesn't exist
    _gmapslivesearch_generate_marker_image($cache_path, $number, _gmapslivesearch_obtain_bullet_values_for_device($device_type));
  }

  // Output to browser
  header('Content-type: image/png');
  
  $fp = fopen($cache_path, 'rb'); //stream the image directly from the cachefile
  fpassthru($fp);
}

/**
 * Generates the file with the bullet
 * 
 * @param string $cache_file Filename of the generated image
 * @param int $number Number that will be rendered on the bullet
 * @param array $options Marker settings
 */
function _gmapslivesearch_generate_marker_image($cache_file, $number, array $options) {
  $image  = imagecreatefrompng($options['image_path']);

  //enable image alpha
  imagesavealpha($image, true);
  //Text settings
  $rgb = _gmapslivesearch_hex2RGB($options['color']);
  $color  = imagecolorallocate($image, $rgb['R'], $rgb['G'], $rgb['B']);
  $text   = $number;
  $font   = $options['ttf'];
  $size   = $options['font_size'];
  //Obtaining size of the text
  $rect   = imagettfbbox($size, 0, $font, $text);

  //Check if we need to center it on the X axis or use an hardcoded size
  if($options['auto_margin_x'] === 1) {
    $minX = min(array($rect[0], $rect[2], $rect[4], $rect[6])); 
    $maxX = max(array($rect[0], $rect[2], $rect[4], $rect[6]));
    $x    = (imagesx($image) - ($maxX - $minX))/2; //Centering the text
  } else {
    $x    = $options['margin_x'];
  }

  //Check if we need to center it on the Y axis or use an hardcoded size
  if($options['auto_margin_y'] === 1) {
    $minY = min(array($rect[1], $rect[3], $rect[5], $rect[7])); 
    $y    = (imagesy($image) - $minY)/2; //Centering the text 
  } else {
    $y    = $options['margin_y'];
  }

  // Add the text
  imagettftext($image, $size, 0, $x, $y, $color, $font, $text);

  imagepng($image, $cache_file); //store the image to cachefile
  imagedestroy($image); 
}

/**
 * Obtains the bullet values for device
 * return: array
 */
function _gmapslivesearch_obtain_bullet_values_for_device($device_type = FALSE) {
  $options = array();
  
  //Depending on the device type, load vars
  $options['image_path'] = _gmapslivesearch_get_bullet_image($device_type);
  $options['ttf'] = _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BULLETS_TTF, $device_type);
  $options['font_size'] = _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BULLETS_FONT_SIZE, $device_type);
  $options['auto_margin_y'] = _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BULLETS_FONT_AUTO_MARGINY, $device_type);
  $options['auto_margin_x'] = _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BULLETS_FONT_AUTO_MARGINX, $device_type);
  $options['margin_y'] = _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BULLETS_FONT_MARGIN_TOP, $device_type);
  $options['margin_x'] = _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BULLETS_FONT_MARGIN_LEFT, $device_type);
  $options['color'] = _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BULLETS_FONT_COLOR, $device_type);
  
  return $options;
}

/**
 * Obtains the bullet image uri according to a device_type
 * 
 * @param type $device_type
 * @return string 
 */
function _gmapslivesearch_get_bullet_image($device_type) {
  $image_folder = GMAPSLIVESEARCH_MAP_BULLETS_IMAGE_FOLDER;
  $image_filename = _gmapslivesearch_get_value(GMAPSLIVESEARCH_MAP_BULLETS_IMAGE_FILE, $device_type);
  
  $image_uri = file_build_uri($image_folder . $image_filename);
  //There is an image uploaded.
  if ($image_filename && file_exists(drupal_realpath($image_uri))) {
    $image_path = $image_uri;
  }
  else {
    $image_path = drupal_get_path('module', 'gmapslivesearch') . '/images/marker.png';
  }
  
  return $image_path;
}

/**
 * Convert a hexa decimal color code to its RGB equivalent
 *
 * @param string $hexStr (hexadecimal color value)
 * @return array|bool Array with 'R', 'G', and 'B' index, or returns FALSE if invalid hex color value
 */                                                                                                 
function _gmapslivesearch_hex2RGB($hexa) {
  // Gets a proper hexa string  
  $hexStr = preg_replace("/[^0-9A-Fa-f]/", '', $hexa); 

  $rgbArray = array();
  if (strlen($hexStr) == 6) { 
    //If a proper hex code, convert using bitwise operation. No overhead... faster
    $colorVal = hexdec($hexStr);
    $rgbArray['R'] = 0xFF & ($colorVal >> 0x10);
    $rgbArray['G'] = 0xFF & ($colorVal >> 0x8);
    $rgbArray['B'] = 0xFF & $colorVal;
  } elseif (strlen($hexStr) == 3) { 
    //if shorthand notation, need some string manipulations
    $rgbArray['R'] = hexdec(str_repeat(substr($hexStr, 0, 1), 2));
    $rgbArray['G'] = hexdec(str_repeat(substr($hexStr, 1, 1), 2));
    $rgbArray['B'] = hexdec(str_repeat(substr($hexStr, 2, 1), 2));
  } else {
    $rgbArray = FALSE; //Invalid hex color code
  }

  return $rgbArray; 
}

/**
 * Deletes all bullets cache
 */
function _gmapslivesearch_clear_bullets_cache() {
  $cache_dir = drupal_realpath(file_build_uri(GMAPSLIVESEARCH_MAP_BULLETS_IMAGE_FOLDER_CACHE));
  $cache_files = scandir($cache_dir);
  
  foreach ($cache_files as $file) {
    if (!is_dir($cache_dir . DIRECTORY_SEPARATOR . $file) && $file != '.' && $file != '..') {
      unlink($cache_dir . DIRECTORY_SEPARATOR . $file);
    }
  }
}
