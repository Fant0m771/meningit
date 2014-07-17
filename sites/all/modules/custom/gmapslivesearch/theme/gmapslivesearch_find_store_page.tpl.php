<div id="buy-now-page">
  <div id="buy-now-page-header">
    <h1><?php print _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_TITLE_TEXT); ?></h1>
    <h3><?php print _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_BUY_NOW_PAGE_SUBTITLE_TEXT); ?></h3>
  </div>
  <div id="buy-now-content">
    <!-- Search box container -->
    <?php print $search_box; ?>
    <!-- Results box container -->
    <?php print $results_box; ?>
  </div>
</div>
