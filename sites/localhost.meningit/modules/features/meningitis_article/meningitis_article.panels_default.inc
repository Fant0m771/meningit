<?php
/**
 * @file
 * meningitis_article.panels_default.inc
 */

/**
 * Implements hook_default_panels_mini().
 */
function meningitis_article_default_panels_mini() {
  $export = array();

  $mini = new stdClass();
  $mini->disabled = FALSE; /* Edit this to true to make a default mini disabled initially */
  $mini->api_version = 1;
  $mini->name = 'footer_panel';
  $mini->category = '';
  $mini->admin_title = 'Footer panel';
  $mini->admin_description = '';
  $mini->requiredcontexts = array();
  $mini->contexts = array();
  $mini->relationships = array();
  $display = new panels_display();
  $display->layout = 'one';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'one_main' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '450493bd-81a3-476d-9ae3-27db81651bca';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-a22525ea-45ee-4fa3-a9ef-d6cf5505ad1e';
    $pane->panel = 'one_main';
    $pane->type = 'block';
    $pane->subtype = 'block-7';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '<none>',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'a22525ea-45ee-4fa3-a9ef-d6cf5505ad1e';
    $display->content['new-a22525ea-45ee-4fa3-a9ef-d6cf5505ad1e'] = $pane;
    $display->panels['one_main'][0] = 'new-a22525ea-45ee-4fa3-a9ef-d6cf5505ad1e';
    $pane = new stdClass();
    $pane->pid = 'new-86d0e97c-accb-4e91-a749-c5078766c851';
    $pane->panel = 'one_main';
    $pane->type = 'block';
    $pane->subtype = 'block-8';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '<none>',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '86d0e97c-accb-4e91-a749-c5078766c851';
    $display->content['new-86d0e97c-accb-4e91-a749-c5078766c851'] = $pane;
    $display->panels['one_main'][1] = 'new-86d0e97c-accb-4e91-a749-c5078766c851';
    $pane = new stdClass();
    $pane->pid = 'new-498b99d4-257e-4b7d-b804-cc480ccd7cf9';
    $pane->panel = 'one_main';
    $pane->type = 'block';
    $pane->subtype = 'block-9';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '<none>',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '498b99d4-257e-4b7d-b804-cc480ccd7cf9';
    $display->content['new-498b99d4-257e-4b7d-b804-cc480ccd7cf9'] = $pane;
    $display->panels['one_main'][2] = 'new-498b99d4-257e-4b7d-b804-cc480ccd7cf9';
    $pane = new stdClass();
    $pane->pid = 'new-db86fd4b-de4f-483f-a966-b5ae45bb3e49';
    $pane->panel = 'one_main';
    $pane->type = 'block';
    $pane->subtype = 'block-10';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '<none>',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = 'db86fd4b-de4f-483f-a966-b5ae45bb3e49';
    $display->content['new-db86fd4b-de4f-483f-a966-b5ae45bb3e49'] = $pane;
    $display->panels['one_main'][3] = 'new-db86fd4b-de4f-483f-a966-b5ae45bb3e49';
    $pane = new stdClass();
    $pane->pid = 'new-c11946b8-f645-46e3-8820-ec5eb0f2cbfd';
    $pane->panel = 'one_main';
    $pane->type = 'block';
    $pane->subtype = 'menu-menu-footer-menu';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 4;
    $pane->locks = array();
    $pane->uuid = 'c11946b8-f645-46e3-8820-ec5eb0f2cbfd';
    $display->content['new-c11946b8-f645-46e3-8820-ec5eb0f2cbfd'] = $pane;
    $display->panels['one_main'][4] = 'new-c11946b8-f645-46e3-8820-ec5eb0f2cbfd';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-86d0e97c-accb-4e91-a749-c5078766c851';
  $mini->display = $display;
  $export['footer_panel'] = $mini;

  $mini = new stdClass();
  $mini->disabled = FALSE; /* Edit this to true to make a default mini disabled initially */
  $mini->api_version = 1;
  $mini->name = 'header_panel';
  $mini->category = '';
  $mini->admin_title = 'Header panel';
  $mini->admin_description = '';
  $mini->requiredcontexts = array();
  $mini->contexts = array();
  $mini->relationships = array();
  $display = new panels_display();
  $display->layout = 'one';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'one_main' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '1dfd3c46-b642-42af-9da4-cb91272121ce';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-1c6d22d2-fc46-4de0-aad3-37a6e689932e';
    $pane->panel = 'one_main';
    $pane->type = 'block';
    $pane->subtype = 'block-5';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '<none>',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '1c6d22d2-fc46-4de0-aad3-37a6e689932e';
    $display->content['new-1c6d22d2-fc46-4de0-aad3-37a6e689932e'] = $pane;
    $display->panels['one_main'][0] = 'new-1c6d22d2-fc46-4de0-aad3-37a6e689932e';
    $pane = new stdClass();
    $pane->pid = 'new-3e7eeed2-7e67-4cb6-959e-9b1409625ade';
    $pane->panel = 'one_main';
    $pane->type = 'block';
    $pane->subtype = 'block-6';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '<none>',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '3e7eeed2-7e67-4cb6-959e-9b1409625ade';
    $display->content['new-3e7eeed2-7e67-4cb6-959e-9b1409625ade'] = $pane;
    $display->panels['one_main'][1] = 'new-3e7eeed2-7e67-4cb6-959e-9b1409625ade';
    $pane = new stdClass();
    $pane->pid = 'new-dc1d642f-8cb4-49e3-b3a7-9436e406be08';
    $pane->panel = 'one_main';
    $pane->type = 'block';
    $pane->subtype = 'block-1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '<none>',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = 'dc1d642f-8cb4-49e3-b3a7-9436e406be08';
    $display->content['new-dc1d642f-8cb4-49e3-b3a7-9436e406be08'] = $pane;
    $display->panels['one_main'][2] = 'new-dc1d642f-8cb4-49e3-b3a7-9436e406be08';
    $pane = new stdClass();
    $pane->pid = 'new-a6ad1e68-e0f0-4662-bf00-856bfe8efd68';
    $pane->panel = 'one_main';
    $pane->type = 'block';
    $pane->subtype = 'system-main-menu';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = 'a6ad1e68-e0f0-4662-bf00-856bfe8efd68';
    $display->content['new-a6ad1e68-e0f0-4662-bf00-856bfe8efd68'] = $pane;
    $display->panels['one_main'][3] = 'new-a6ad1e68-e0f0-4662-bf00-856bfe8efd68';
    $pane = new stdClass();
    $pane->pid = 'new-42529edf-7d15-409f-a56c-0df5287ea3c0';
    $pane->panel = 'one_main';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => 'Mobile menu button',
      'title' => '',
      'body' => '<div id=\'open-mobile-menu\' class=\'open-mobile-menu\'>open menu</div>',
      'format' => 'full_html',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 4;
    $pane->locks = array();
    $pane->uuid = '42529edf-7d15-409f-a56c-0df5287ea3c0';
    $display->content['new-42529edf-7d15-409f-a56c-0df5287ea3c0'] = $pane;
    $display->panels['one_main'][4] = 'new-42529edf-7d15-409f-a56c-0df5287ea3c0';
    $pane = new stdClass();
    $pane->pid = 'new-a4181802-904d-43af-b98a-d2fd705dba8c';
    $pane->panel = 'one_main';
    $pane->type = 'block';
    $pane->subtype = 'menu-menu-mobile-menu';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 5;
    $pane->locks = array();
    $pane->uuid = 'a4181802-904d-43af-b98a-d2fd705dba8c';
    $display->content['new-a4181802-904d-43af-b98a-d2fd705dba8c'] = $pane;
    $display->panels['one_main'][5] = 'new-a4181802-904d-43af-b98a-d2fd705dba8c';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-a6ad1e68-e0f0-4662-bf00-856bfe8efd68';
  $mini->display = $display;
  $export['header_panel'] = $mini;

  $mini = new stdClass();
  $mini->disabled = FALSE; /* Edit this to true to make a default mini disabled initially */
  $mini->api_version = 1;
  $mini->name = 'page_banner';
  $mini->category = '';
  $mini->admin_title = 'Page banner';
  $mini->admin_description = '';
  $mini->requiredcontexts = array();
  $mini->contexts = array();
  $mini->relationships = array();
  $display = new panels_display();
  $display->layout = 'one';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'one_main' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = 'ed121ba7-7bfc-43d2-ab8f-8111f4f3d820';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-32f9fd7a-1b1a-49ca-9a4b-91b6bff06922';
    $pane->panel = 'one_main';
    $pane->type = 'block';
    $pane->subtype = 'views-page_banner_image-block';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '32f9fd7a-1b1a-49ca-9a4b-91b6bff06922';
    $display->content['new-32f9fd7a-1b1a-49ca-9a4b-91b6bff06922'] = $pane;
    $display->panels['one_main'][0] = 'new-32f9fd7a-1b1a-49ca-9a4b-91b6bff06922';
    $pane = new stdClass();
    $pane->pid = 'new-f24a6b34-d8c2-4fbe-9b90-6a4212036b95';
    $pane->panel = 'one_main';
    $pane->type = 'block';
    $pane->subtype = 'block-3';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '<none>',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'f24a6b34-d8c2-4fbe-9b90-6a4212036b95';
    $display->content['new-f24a6b34-d8c2-4fbe-9b90-6a4212036b95'] = $pane;
    $display->panels['one_main'][1] = 'new-f24a6b34-d8c2-4fbe-9b90-6a4212036b95';
    $pane = new stdClass();
    $pane->pid = 'new-67b01b87-b6c5-4eb4-875c-6ee8412e06ac';
    $pane->panel = 'one_main';
    $pane->type = 'block';
    $pane->subtype = 'block-4';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '<none>',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '67b01b87-b6c5-4eb4-875c-6ee8412e06ac';
    $display->content['new-67b01b87-b6c5-4eb4-875c-6ee8412e06ac'] = $pane;
    $display->panels['one_main'][2] = 'new-67b01b87-b6c5-4eb4-875c-6ee8412e06ac';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-32f9fd7a-1b1a-49ca-9a4b-91b6bff06922';
  $mini->display = $display;
  $export['page_banner'] = $mini;

  return $export;
}
