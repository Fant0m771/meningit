<?php
/**
 * @file
 * meningitis_article.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function meningitis_article_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-mobile-menu.
  $menus['menu-mobile-menu'] = array(
    'menu_name' => 'menu-mobile-menu',
    'title' => 'mobile menu',
    'description' => '',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('mobile menu');


  return $menus;
}
