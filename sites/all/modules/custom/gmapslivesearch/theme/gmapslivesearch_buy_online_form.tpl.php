<div>
  <div class="buy-online-box-wrapper">  
    <h2><?php print _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_NOW_STORE_SEARCH_FIELD_LABEL); ?></h2>
    <?php print drupal_render($form[GMAPSLIVESEARCH_FIELD_STORES_SEARCH_FIND_ONLINE]); ?>
    <?php print _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_NOW_STORE_SEARCH_DESC); ?>
    <?php print drupal_render($form[GMAPSLIVESEARCH_FIELD_GOTO_ONLINE_STORE_BTN_FIND_ONLINE]); ?>
  </div>
</div>
<?php print drupal_render($form['form_build_id']); ?>
<?php print drupal_render($form['form_id']); ?>
