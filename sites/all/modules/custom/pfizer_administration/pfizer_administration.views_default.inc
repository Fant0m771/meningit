<?php
/**
 * @file
 * pfizer_administration.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function pfizer_administration_views_default_views() {
  $export = array();
  
  $view = new view();
  $view->name = 'dashboard_content';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Dashboard Content';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  
  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Recently Updated Content';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '15';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'status' => 'status',
    'timestamp' => 'timestamp',
    'title' => 'title',
    'log' => 'title',
    'type' => 'type',
    'changed' => 'changed',
    'name' => 'name',
    'edit_node' => 'edit_node',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'status' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'timestamp' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'log' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'type' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'changed' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['required'] = TRUE;
  /* Field: Content: Published */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Field: Content: Has new content */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'history';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['label'] = '';
  $handler->display->display_options['fields']['timestamp']['exclude'] = TRUE;
  $handler->display->display_options['fields']['timestamp']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '[title] [timestamp] <br />';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content revision: Log message */
  $handler->display->display_options['fields']['log']['id'] = 'log';
  $handler->display->display_options['fields']['log']['table'] = 'node_revision';
  $handler->display->display_options['fields']['log']['field'] = 'log';
  $handler->display->display_options['fields']['log']['label'] = '';
  $handler->display->display_options['fields']['log']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['log']['alter']['text'] = '<i>Log: "[log]"</i>';
  $handler->display->display_options['fields']['log']['element_label_colon'] = FALSE;
  /* Field: Content: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'node';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  /* Field: Content: Updated date */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'Last Updated';
  $handler->display->display_options['fields']['changed']['date_format'] = 'short';
  $handler->display->display_options['fields']['changed']['custom_date_format'] = '2';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'Author';
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Edit';
  /* Sort criterion: Content: Updated date */
  $handler->display->display_options['sorts']['changed']['id'] = 'changed';
  $handler->display->display_options['sorts']['changed']['table'] = 'node';
  $handler->display->display_options['sorts']['changed']['field'] = 'changed';
  $handler->display->display_options['sorts']['changed']['order'] = 'DESC';
  
  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $export['dashboard_content'] = $view;

	$view = new view;
	$view->name = 'dashboard_users';
	$view->description = '';
	$view->tag = 'default';
	$view->base_table = 'users';
	$view->human_name = 'Dashboard Users';
	$view->core = 7;
	$view->api_version = '3.0';
	$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

	/* Display: Master */
	$handler = $view->new_display('default', 'Master', 'default');
	$handler->display->display_options['title'] = 'Active Users';
	$handler->display->display_options['use_more'] = TRUE;
	$handler->display->display_options['use_more_always'] = TRUE;
	$handler->display->display_options['use_more_text'] = 'Click here to see a complete list of users';
	$handler->display->display_options['access']['type'] = 'perm';
	$handler->display->display_options['access']['perm'] = 'access user profiles';
	$handler->display->display_options['cache']['type'] = 'none';
	$handler->display->display_options['query']['type'] = 'views_query';
	$handler->display->display_options['query']['options']['query_comment'] = FALSE;
	$handler->display->display_options['exposed_form']['type'] = 'basic';
	$handler->display->display_options['pager']['type'] = 'some';
	$handler->display->display_options['pager']['options']['items_per_page'] = '10';
	$handler->display->display_options['style_plugin'] = 'table';
	$handler->display->display_options['style_options']['columns'] = array(
		'name' => 'name',
		'mail' => 'mail',
		'rid' => 'rid',
		'access' => 'access',
		'edit_node' => 'edit_node',
	);
	$handler->display->display_options['style_options']['default'] = 'name';
	$handler->display->display_options['style_options']['info'] = array(
		'name' => array(
			'sortable' => 1,
			'default_sort_order' => 'asc',
			'align' => '',
			'separator' => '',
			'empty_column' => 0,
		),
		'mail' => array(
			'sortable' => 1,
			'default_sort_order' => 'asc',
			'align' => '',
			'separator' => '',
			'empty_column' => 0,
		),
		'rid' => array(
			'align' => '',
			'separator' => '',
			'empty_column' => 0,
		),
		'access' => array(
			'sortable' => 1,
			'default_sort_order' => 'asc',
			'align' => '',
			'separator' => '',
			'empty_column' => 0,
		),
		'edit_node' => array(
			'align' => '',
			'separator' => '',
			'empty_column' => 0,
		),
	);
	$handler->display->display_options['style_options']['override'] = 1;
	$handler->display->display_options['style_options']['sticky'] = 0;
	$handler->display->display_options['style_options']['empty_table'] = 0;
	/* Field: User: Name */
	$handler->display->display_options['fields']['name']['id'] = 'name';
	$handler->display->display_options['fields']['name']['table'] = 'users';
	$handler->display->display_options['fields']['name']['field'] = 'name';
	$handler->display->display_options['fields']['name']['label'] = 'Username';
	$handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
	$handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
	$handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
	$handler->display->display_options['fields']['name']['alter']['external'] = 0;
	$handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
	$handler->display->display_options['fields']['name']['alter']['trim_whitespace'] = 0;
	$handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
	$handler->display->display_options['fields']['name']['alter']['word_boundary'] = 0;
	$handler->display->display_options['fields']['name']['alter']['ellipsis'] = 0;
	$handler->display->display_options['fields']['name']['alter']['more_link'] = 0;
	$handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
	$handler->display->display_options['fields']['name']['alter']['trim'] = 0;
	$handler->display->display_options['fields']['name']['alter']['html'] = 0;
	$handler->display->display_options['fields']['name']['element_label_colon'] = 1;
	$handler->display->display_options['fields']['name']['element_default_classes'] = 1;
	$handler->display->display_options['fields']['name']['hide_empty'] = 0;
	$handler->display->display_options['fields']['name']['empty_zero'] = 0;
	$handler->display->display_options['fields']['name']['hide_alter_empty'] = 1;
	$handler->display->display_options['fields']['name']['link_to_user'] = 1;
	$handler->display->display_options['fields']['name']['overwrite_anonymous'] = 0;
	$handler->display->display_options['fields']['name']['format_username'] = 1;
	/* Field: User: E-mail */
	$handler->display->display_options['fields']['mail']['id'] = 'mail';
	$handler->display->display_options['fields']['mail']['table'] = 'users';
	$handler->display->display_options['fields']['mail']['field'] = 'mail';
	$handler->display->display_options['fields']['mail']['alter']['alter_text'] = 0;
	$handler->display->display_options['fields']['mail']['alter']['make_link'] = 0;
	$handler->display->display_options['fields']['mail']['alter']['absolute'] = 0;
	$handler->display->display_options['fields']['mail']['alter']['external'] = 0;
	$handler->display->display_options['fields']['mail']['alter']['replace_spaces'] = 0;
	$handler->display->display_options['fields']['mail']['alter']['trim_whitespace'] = 0;
	$handler->display->display_options['fields']['mail']['alter']['nl2br'] = 0;
	$handler->display->display_options['fields']['mail']['alter']['word_boundary'] = 1;
	$handler->display->display_options['fields']['mail']['alter']['ellipsis'] = 1;
	$handler->display->display_options['fields']['mail']['alter']['more_link'] = 0;
	$handler->display->display_options['fields']['mail']['alter']['strip_tags'] = 0;
	$handler->display->display_options['fields']['mail']['alter']['trim'] = 0;
	$handler->display->display_options['fields']['mail']['alter']['html'] = 0;
	$handler->display->display_options['fields']['mail']['element_label_colon'] = 1;
	$handler->display->display_options['fields']['mail']['element_default_classes'] = 1;
	$handler->display->display_options['fields']['mail']['hide_empty'] = 0;
	$handler->display->display_options['fields']['mail']['empty_zero'] = 0;
	$handler->display->display_options['fields']['mail']['hide_alter_empty'] = 1;
	/* Field: User: Roles */
	$handler->display->display_options['fields']['rid']['id'] = 'rid';
	$handler->display->display_options['fields']['rid']['table'] = 'users_roles';
	$handler->display->display_options['fields']['rid']['field'] = 'rid';
	$handler->display->display_options['fields']['rid']['alter']['alter_text'] = 0;
	$handler->display->display_options['fields']['rid']['alter']['make_link'] = 0;
	$handler->display->display_options['fields']['rid']['alter']['absolute'] = 0;
	$handler->display->display_options['fields']['rid']['alter']['external'] = 0;
	$handler->display->display_options['fields']['rid']['alter']['replace_spaces'] = 0;
	$handler->display->display_options['fields']['rid']['alter']['trim_whitespace'] = 0;
	$handler->display->display_options['fields']['rid']['alter']['nl2br'] = 0;
	$handler->display->display_options['fields']['rid']['alter']['word_boundary'] = 1;
	$handler->display->display_options['fields']['rid']['alter']['ellipsis'] = 1;
	$handler->display->display_options['fields']['rid']['alter']['more_link'] = 0;
	$handler->display->display_options['fields']['rid']['alter']['strip_tags'] = 0;
	$handler->display->display_options['fields']['rid']['alter']['trim'] = 0;
	$handler->display->display_options['fields']['rid']['alter']['html'] = 0;
	$handler->display->display_options['fields']['rid']['element_label_colon'] = 1;
	$handler->display->display_options['fields']['rid']['element_default_classes'] = 1;
	$handler->display->display_options['fields']['rid']['hide_empty'] = 0;
	$handler->display->display_options['fields']['rid']['empty_zero'] = 0;
	$handler->display->display_options['fields']['rid']['hide_alter_empty'] = 1;
	/* Field: User: Last access */
	$handler->display->display_options['fields']['access']['id'] = 'access';
	$handler->display->display_options['fields']['access']['table'] = 'users';
	$handler->display->display_options['fields']['access']['field'] = 'access';
	$handler->display->display_options['fields']['access']['date_format'] = 'long';
	/* Field: User: Edit link */
	$handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
	$handler->display->display_options['fields']['edit_node']['table'] = 'users';
	$handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
	$handler->display->display_options['fields']['edit_node']['alter']['alter_text'] = 0;
	$handler->display->display_options['fields']['edit_node']['alter']['make_link'] = 0;
	$handler->display->display_options['fields']['edit_node']['alter']['absolute'] = 0;
	$handler->display->display_options['fields']['edit_node']['alter']['external'] = 0;
	$handler->display->display_options['fields']['edit_node']['alter']['replace_spaces'] = 0;
	$handler->display->display_options['fields']['edit_node']['alter']['trim_whitespace'] = 0;
	$handler->display->display_options['fields']['edit_node']['alter']['nl2br'] = 0;
	$handler->display->display_options['fields']['edit_node']['alter']['word_boundary'] = 1;
	$handler->display->display_options['fields']['edit_node']['alter']['ellipsis'] = 1;
	$handler->display->display_options['fields']['edit_node']['alter']['more_link'] = 0;
	$handler->display->display_options['fields']['edit_node']['alter']['strip_tags'] = 0;
	$handler->display->display_options['fields']['edit_node']['alter']['trim'] = 0;
	$handler->display->display_options['fields']['edit_node']['alter']['html'] = 0;
	$handler->display->display_options['fields']['edit_node']['element_label_colon'] = 1;
	$handler->display->display_options['fields']['edit_node']['element_default_classes'] = 1;
	$handler->display->display_options['fields']['edit_node']['hide_empty'] = 0;
	$handler->display->display_options['fields']['edit_node']['empty_zero'] = 0;
	$handler->display->display_options['fields']['edit_node']['hide_alter_empty'] = 1;
	/* Sort criterion: User: Last access */
	$handler->display->display_options['sorts']['access']['id'] = 'access';
	$handler->display->display_options['sorts']['access']['table'] = 'users';
	$handler->display->display_options['sorts']['access']['field'] = 'access';
	$handler->display->display_options['sorts']['access']['order'] = 'DESC';
	/* Filter criterion: User: Active */
	$handler->display->display_options['filters']['status']['id'] = 'status';
	$handler->display->display_options['filters']['status']['table'] = 'users';
	$handler->display->display_options['filters']['status']['field'] = 'status';
	$handler->display->display_options['filters']['status']['value'] = '1';
	$handler->display->display_options['filters']['status']['group'] = 1;
	$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
	/* Filter criterion: User: Name (raw) */
	$handler->display->display_options['filters']['name']['id'] = 'name';
	$handler->display->display_options['filters']['name']['table'] = 'users';
	$handler->display->display_options['filters']['name']['field'] = 'name';
	$handler->display->display_options['filters']['name']['operator'] = 'contains';
	$handler->display->display_options['filters']['name']['exposed'] = TRUE;
	$handler->display->display_options['filters']['name']['expose']['operator_id'] = 'name_op';
	$handler->display->display_options['filters']['name']['expose']['label'] = 'Username';
	$handler->display->display_options['filters']['name']['expose']['operator'] = 'name_op';
	$handler->display->display_options['filters']['name']['expose']['identifier'] = 'name';
	$handler->display->display_options['filters']['name']['expose']['required'] = 0;
	$handler->display->display_options['filters']['name']['expose']['multiple'] = FALSE;
	/* Filter criterion: User: E-mail */
	$handler->display->display_options['filters']['mail']['id'] = 'mail';
	$handler->display->display_options['filters']['mail']['table'] = 'users';
	$handler->display->display_options['filters']['mail']['field'] = 'mail';
	$handler->display->display_options['filters']['mail']['operator'] = 'contains';
	$handler->display->display_options['filters']['mail']['exposed'] = TRUE;
	$handler->display->display_options['filters']['mail']['expose']['operator_id'] = 'mail_op';
	$handler->display->display_options['filters']['mail']['expose']['label'] = 'E-mail';
	$handler->display->display_options['filters']['mail']['expose']['operator'] = 'mail_op';
	$handler->display->display_options['filters']['mail']['expose']['identifier'] = 'mail';
	$handler->display->display_options['filters']['mail']['expose']['required'] = 0;
	$handler->display->display_options['filters']['mail']['expose']['multiple'] = FALSE;
	/* Filter criterion: User: Roles */
	$handler->display->display_options['filters']['rid']['id'] = 'rid';
	$handler->display->display_options['filters']['rid']['table'] = 'users_roles';
	$handler->display->display_options['filters']['rid']['field'] = 'rid';
	$handler->display->display_options['filters']['rid']['exposed'] = TRUE;
	$handler->display->display_options['filters']['rid']['expose']['operator_id'] = 'rid_op';
	$handler->display->display_options['filters']['rid']['expose']['label'] = 'Roles';
	$handler->display->display_options['filters']['rid']['expose']['operator'] = 'rid_op';
	$handler->display->display_options['filters']['rid']['expose']['identifier'] = 'rid';
	$handler->display->display_options['filters']['rid']['expose']['reduce'] = 0;
	$handler->display->display_options['filters']['rid']['reduce_duplicates'] = 0;

	/* Display: Block */
	$handler = $view->new_display('block', 'Block', 'block');
	$handler->display->display_options['defaults']['title'] = FALSE;
	$handler->display->display_options['title'] = 'Recently Active Users';
	$handler->display->display_options['defaults']['style_plugin'] = FALSE;
	$handler->display->display_options['style_plugin'] = 'table';
	$handler->display->display_options['style_options']['columns'] = array(
		'name' => 'name',
		'access' => 'access',
	);
	$handler->display->display_options['style_options']['default'] = '-1';
	$handler->display->display_options['style_options']['info'] = array(
		'name' => array(
			'sortable' => 0,
			'default_sort_order' => 'asc',
			'align' => '',
			'separator' => '',
			'empty_column' => 0,
		),
		'access' => array(
			'sortable' => 0,
			'default_sort_order' => 'asc',
			'align' => '',
			'separator' => '',
			'empty_column' => 0,
		),
	);
	$handler->display->display_options['style_options']['override'] = 1;
	$handler->display->display_options['style_options']['sticky'] = 0;
	$handler->display->display_options['style_options']['empty_table'] = 0;
	$handler->display->display_options['defaults']['style_options'] = FALSE;
	$handler->display->display_options['defaults']['row_plugin'] = FALSE;
	$handler->display->display_options['defaults']['row_options'] = FALSE;
	$handler->display->display_options['defaults']['fields'] = FALSE;
	/* Field: User: Name */
	$handler->display->display_options['fields']['name']['id'] = 'name';
	$handler->display->display_options['fields']['name']['table'] = 'users';
	$handler->display->display_options['fields']['name']['field'] = 'name';
	$handler->display->display_options['fields']['name']['label'] = 'Username';
	$handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
	$handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
	$handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
	$handler->display->display_options['fields']['name']['alter']['external'] = 0;
	$handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
	$handler->display->display_options['fields']['name']['alter']['trim_whitespace'] = 0;
	$handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
	$handler->display->display_options['fields']['name']['alter']['word_boundary'] = 0;
	$handler->display->display_options['fields']['name']['alter']['ellipsis'] = 0;
	$handler->display->display_options['fields']['name']['alter']['more_link'] = 0;
	$handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
	$handler->display->display_options['fields']['name']['alter']['trim'] = 0;
	$handler->display->display_options['fields']['name']['alter']['html'] = 0;
	$handler->display->display_options['fields']['name']['element_label_colon'] = 1;
	$handler->display->display_options['fields']['name']['element_default_classes'] = 1;
	$handler->display->display_options['fields']['name']['hide_empty'] = 0;
	$handler->display->display_options['fields']['name']['empty_zero'] = 0;
	$handler->display->display_options['fields']['name']['hide_alter_empty'] = 1;
	$handler->display->display_options['fields']['name']['link_to_user'] = 1;
	$handler->display->display_options['fields']['name']['overwrite_anonymous'] = 0;
	$handler->display->display_options['fields']['name']['format_username'] = 1;
	/* Field: User: Last access */
	$handler->display->display_options['fields']['access']['id'] = 'access';
	$handler->display->display_options['fields']['access']['table'] = 'users';
	$handler->display->display_options['fields']['access']['field'] = 'access';
	$handler->display->display_options['fields']['access']['date_format'] = 'long';
	$handler->display->display_options['defaults']['filters'] = FALSE;
	/* Filter criterion: User: Active */
	$handler->display->display_options['filters']['status']['id'] = 'status';
	$handler->display->display_options['filters']['status']['table'] = 'users';
	$handler->display->display_options['filters']['status']['field'] = 'status';
	$handler->display->display_options['filters']['status']['value'] = '1';
	$handler->display->display_options['filters']['status']['group'] = 1;
	$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

	/* Display: Page */
	$handler = $view->new_display('page', 'Page', 'page_1');
	$handler->display->display_options['defaults']['use_more'] = FALSE;
	$handler->display->display_options['use_more_always'] = TRUE;
	$handler->display->display_options['path'] = 'admin/dashboard-users-list';
  $export['dashboard_users'] = $view;

  return $export;
}
