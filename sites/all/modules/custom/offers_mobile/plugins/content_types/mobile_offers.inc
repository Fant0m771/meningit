<?php

$plugin = array(
  'single'       => TRUE,
  'title'        => t('Offers Mobile'),
  'description'  => t('Coupons by email mobile'),
  'category'     => t('Pfizer')
);

function  mobile_offers_mobile_offers_content_type_render($subtype, $conf, $args, $context) {
  module_load_include('inc', 'mobile_offers', 'inc/mobile_offers.forms');
  $block = new stdClass();
  $block->title = variable_get(MOBILE_OFFERS_PREFIX . 'page_title', 'Offers');
  $block->content = drupal_get_form('mobile_offers_form');
  return $block;
}