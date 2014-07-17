<?php

/**
 * @file
 * Contains theme override functions and preprocess functions for the Boron theme.
 */

function pfizer_mobile_preprocess_page(&$vars) {
  pfizer_mobile_css_alter($vars);
  drupal_add_js(array('themePath' => path_to_theme()), 'setting');
}

function pfizer_mobile_css_alter(&$vars) {
  if (!user_is_logged_in()) {
    unset($vars[drupal_get_path('module', 'webform') . '/css/webform.css']);
    unset($vars[drupal_get_path('module', 'system') . '/system.menus.css']);
    unset($vars[drupal_get_path('module', 'system') . '/system.menus.css']);
    unset($vars[drupal_get_path('module', 'system') . '/system.menus.css']);
    unset($vars[drupal_get_path('module', 'system') . '/system.base.css']);
    unset($vars[drupal_get_path('module', 'system') . '/system.messages.css']);
    unset($vars[drupal_get_path('module', 'system') . '/system.theme.css']);
    unset($vars[drupal_get_path('module', 'field_group') . '/field_group.css']);
    unset($vars[drupal_get_path('module', 'views') . '/css/views.css']);
    unset($vars[drupal_get_path('module', 'ctools') . '/css/ctools.css']);
    unset($vars[drupal_get_path('module', 'ckeditor') . '/ckeditor.css']);
    unset($vars[drupal_get_path('module', 'field') . '/theme/field.css']);
    unset($vars[drupal_get_path('module', 'node') . '/node.css']);
    unset($vars[drupal_get_path('module', 'search') . '/search.css']);
    unset($vars[drupal_get_path('module', 'user') . '/user.css']);
    unset($vars[drupal_get_path('module', 'system') . '/system.menus.css']);
  }
}

// Changes the default meta content-type tag to the shorter HTML5 version
function pfizer_mobile_html_head_alter(&$head_elements) {
  $head_elements['system_meta_content_type']['#attributes'] = array(
    'charset' => 'utf-8',
  );
    
  $head_elements['ios_web_app'] = array (
	'#type' => 'html_tag',
	'#tag' => 'meta',
	'#attributes' => array (
	  'name' => 'apple-mobile-web-app-capable',
	  'content' => 'yes',
     ),
  );

  $head_elements['viewport'] = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'name' => 'viewport',
      'content' => 'width=device-width; initial-scale=1; maximum-scale=1, user-scalable=no',
    ),
  );
  
  $head_elements['telephone_number_detection'] = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'name' => 'format-detection',
      'content' => 'telephone=no',
    ),
  );
}

/**
 * Uses RDFa attributes if the RDF module is enabled
 * Lifted from Adaptivetheme for D7, full credit to Jeff Burnz
 * ref: http://drupal.org/node/887600
 */
function pfizer_mobile_preprocess_html(&$vars) {
  
  $vars["head_title"] = drupal_get_title();

  if (module_exists('rdf')) {
    $vars['doctype'] = '<!DOCTYPE html PUBLIC "-//W3C//DTD HTML+RDFa 1.1//EN">' . "\n";
    $vars['rdf']->version = 'version="HTML+RDFa 1.1"';
    $vars['rdf']->namespaces = $vars['rdf_namespaces'];
    $vars['rdf']->profile = ' profile="' . $vars['grddl_profile'] . '"';
  } else {
    $vars['doctype'] = '<!DOCTYPE html PUBLIC "-//WAPFORUM//DTD XHTML Mobile 1.2//EN" "http://www.openmobilealliance.org/tech/DTD/xhtml-mobile12.dtd">' . "\n";
    $vars['rdf']->version = '';
    $vars['rdf']->namespaces = '';
    $vars['rdf']->profile = '';
  }
  
  if(theme_get_setting('open_gallery_in_overlay') == 1) {
    $images_in_an_overlay = TRUE;
  }
  else {
    $images_in_an_overlay = FALSE;
  }
  
  drupal_add_js(array('imagesInAnOverlay' => $images_in_an_overlay), 'setting');
  
}

function pfizer_mobile_menu_link__main_menu(array $variables) {
  $element = $variables['element'];
  $sub_menu = '';

  // If the link have any class, get it and add it to the li
  if( isset( $element['#original_link']['options']['attributes']['class'] )  ){
    $original_link_class = ' ' . implode($element['#original_link']['options']['attributes']['class'], ' ');
    $element['#attributes']['class'][] = $original_link_class;
  }
  
  // If the menu item has sublinks remove original link.
  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
    $element['#localized_options']['attributes']['class'][] = "no-link";    
  }
  
  $element['#localized_options']['html'] = TRUE;
  $output = l(
    $element['#title'] . '<span class="general-sprite"></span>', 
    $element['#href'],
    $element['#localized_options']
  );
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}