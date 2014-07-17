<div id="gmapslivesearch-box-wrapper">
  <div class="gmapslivesearch-box find-store">
    <h3><?php print _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_ADDRESS_FIELD_LABEL); ?></h3>
    <?php print drupal_render($form[GMAPSLIVESEARCH_FIELD_ADDRESS_TO_SEARCH]); ?>
    <?php 
    //Error message container. It is used for the client and server side validation. 
    //So don't delete it. Relocate if needed. ?>
    <div class="error inline-error">
      <?php if($form['errors']) { print drupal_render($form['errors']); } ?>
    </div>
    <?php print _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_ADDRESS_SEARCH_DESC); ?>
    <?php if (isset($form[GMAPSLIVESEARCH_FIELD_STORES_CONTENT_TYPE])): ?>
      <?php print drupal_render($form[GMAPSLIVESEARCH_FIELD_STORES_CONTENT_TYPE]); ?>
    <?php endif; ?>
    <?php print drupal_render($form['submit']); ?>
    <a href="javascript:void(0);" id="gmapslivesearch-btn-map" class="map-btn">
      <?php print _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_ONLINE_BTN_MAP, 'mobile');?>
    </a>
    <a href="javascript:void(0);" id="gmapslivesearch-btn-list" class="list-btn">
      <?php print _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_ONLINE_BTN_LIST, 'mobile');?>
    </a>
  </div>
  <div class="clear_both "></div>
</div>
<?php if(isset($form['no_results_found'])): ?>
  <h3 class="no-results-found"><?php print drupal_render($form['no_results_found']); ?></h3>
<?php endif; ?>
<?php print drupal_render($form['form_build_id']); ?>
<?php print drupal_render($form['form_id']); ?>
