<?php

function pfizer_mobile_form_system_theme_settings_alter(&$form, &$form_state) {
  $form['gallery_options_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Gallery Page Configuration'),
    '#collapsed' => FALSE,
    '#collapsible' => FALSE,
  );

  $form['gallery_options_fieldset']['open_gallery_in_overlay'] = array(    
    '#type' => 'checkbox', 
    '#title' => t('Show images in an overlay.'), 
    '#default_value' => theme_get_setting('open_gallery_in_overlay'), 
    '#description' => t('<p>Select this option if you want to that the images from the image gallery will be shown in an overlay when clicked.</p> <strong>If disabled</strong>, when the user clicks in the image, will slide to the next image. '),
  );
}