<div id="gmapslivesearch-wrapper">
  <div id="gmapslivesearch-loader"></div>
  <div id="gmapslivesearch-header">
    <h3><?php print t('Stores Near You'); ?></h3>
    <a href="http://maps.google.com/maps?pw=2&q=" id="gmapslivesearch-printresults" class="print-btn">
      <?php print t('Print');?>
    </a>
  </div>
  <div id="gmapslivesearch-map-results">
    <div id="searcher"></div>
    <div id="gmapslivesearch-map" class="gmapslivesearch-map"></div>
    <div id="gmapslivesearch-stores">
      <ul>
       <?php if(is_array($stores)) : $count = 1;?>
          <?php foreach($stores as $store): ?>
            <li>
              <div class="GMap_Info">
                <div class="GMap_Title">Family Dollar #8731</div>  
                <div class="GMap_Address">35-27 31st St</div>  
                <div class="GMap_City_And_Region">Astoria, NY</div>  
                <div class="LocationFooter list-link">
                  <a href="<?php print $store['goto_link']; ?>" class="Links mapDirections" rel="0" target="_blank"><?php print t('Map & Directions'); ?></a>
                </div> 
                <div class="Links map-link">
                  <a href="<?php print $store['goto_link'];?>" class="Links mapDirections" rel="<?php print $count; ?>"><?php print t('Get Directions');?></a>
                </div>
              </div>
              <a href="javascript:void(0);" class="centerMap" rel="<?php print $count; ?>"><img src="/gmapslivesearch/marker/<?php print $count; ?>" border="0" class="imgnumber" /></a>
            </li>
            <?php $count++; ?>
          <?php endforeach;?>
        <?php endif; ?>
      </ul>
    </div>
    <div class="clear_both"></div>
  </div>
</div>