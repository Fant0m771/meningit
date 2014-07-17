<?php
/**
 * @file
 * meningitis_article.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function meningitis_article_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view_panel_context';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'article' => 'article',
            ),
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
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
  $display->title = '%node:title';
  $display->uuid = '094c609e-e7c6-4b8c-9423-fde0e05e38db';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-85ac992a-40fc-4667-ba06-23b4bac0e86d';
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
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '85ac992a-40fc-4667-ba06-23b4bac0e86d';
    $display->content['new-85ac992a-40fc-4667-ba06-23b4bac0e86d'] = $pane;
    $display->panels['one_main'][0] = 'new-85ac992a-40fc-4667-ba06-23b4bac0e86d';
    $pane = new stdClass();
    $pane->pid = 'new-b5b9898f-4986-435a-b525-0e988bd4e91c';
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
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'b5b9898f-4986-435a-b525-0e988bd4e91c';
    $display->content['new-b5b9898f-4986-435a-b525-0e988bd4e91c'] = $pane;
    $display->panels['one_main'][1] = 'new-b5b9898f-4986-435a-b525-0e988bd4e91c';
    $pane = new stdClass();
    $pane->pid = 'new-a76ecc29-97e3-42d2-aee5-f3ee92b50b72';
    $pane->panel = 'one_main';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:body';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'text_default',
      'delta_limit' => '0',
      'delta_offset' => '0',
      'delta_reversed' => 0,
      'formatter_settings' => array(),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = 'a76ecc29-97e3-42d2-aee5-f3ee92b50b72';
    $display->content['new-a76ecc29-97e3-42d2-aee5-f3ee92b50b72'] = $pane;
    $display->panels['one_main'][2] = 'new-a76ecc29-97e3-42d2-aee5-f3ee92b50b72';
    $pane = new stdClass();
    $pane->pid = 'new-fc7c93b1-2441-4da2-923d-2a9782016dc2';
    $pane->panel = 'one_main';
    $pane->type = 'panels_mini';
    $pane->subtype = 'footer_panel';
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
    $pane->uuid = 'fc7c93b1-2441-4da2-923d-2a9782016dc2';
    $display->content['new-fc7c93b1-2441-4da2-923d-2a9782016dc2'] = $pane;
    $display->panels['one_main'][3] = 'new-fc7c93b1-2441-4da2-923d-2a9782016dc2';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-85ac992a-40fc-4667-ba06-23b4bac0e86d';
  $handler->conf['display'] = $display;
  $export['node_view_panel_context'] = $handler;

  return $export;
}
