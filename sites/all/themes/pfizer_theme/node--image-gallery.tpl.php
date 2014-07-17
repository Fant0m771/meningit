<div id="image-gallery-wrapper">
  <?php if(!empty($node->body[$node->language])): ?>
    <div id="image-gallery-top-text">
      <?php print $node->body[$node->language][0]['value']; ?>
    </div>
  <?php endif; ?>
  <div id="image-gallery-images-wrapper">
    <div id="image-gallery-images">
      <?php
      
      $has_single_image = count($node->field_image_gallery_image[$node->language]) == 1;
	  
      foreach ($node->field_image_gallery_image[$node->language] as $key => $image):
        $image['path'] = $image['uri'];	
			
        $classes = "";	
        $image_title = t('other image');
      
        if($key == 0) {
          $classes = "first";
          
          if (!$has_single_image) {
            $image_title = $node->field_image_gallery_image[$node->language][$key + 1]['alt'];
          }
          
        } else if ($key == count($node->field_image_gallery_image[$node->language])-1){
          $classes = "last";
          
          $image_title = $node->field_image_gallery_image[$node->language][$key - 1]['alt'];
        }
      ?>     
       <div class="image-gallery-image <?php print $classes; ?>">
       
			 <?php	print t('<h3>@title</h3>', array('@title' => $image['alt'])); ?>
       
       <p class="swipe-image-text">    
       <?php 			 
          if(theme_get_setting('open_gallery_in_overlay')){
            print t('Tap to expand or swipe to see<br /><span style="text-transform: lowercase">@image_title</span>.', array('@image_title' => $image_title)); 
          }
		 else if  (empty($node->field_image_description_field[$node->language][$key])){
            print t('Swipe or click to see<br /><span style="text-transform: lowercase">@image_title</span>.', array('@image_title' => $image_title)); 
		  }
		  else{
			print $node->field_image_description_field[$node->language][$key]['value'] ."<br />". $image_title;
		  }
        ?>
       </p>
          <?php
            $variables = array(
              'path' => $image['path'],
              'attributes' => array('class' => 'image-gallery'),
            );
          ?>
          <figure>
            <?php print theme('image', $variables); ?>
          </figure>
          
          <div class="image-gallery-big-image">
            <?php print theme('image', $image); ?>
          </div>
        </div>
        
      <?php endforeach; ?>
    </div>
    <div id="image-gallery-indicator-wrapper">
      <ul id="image-gallery-indicator"></ul>
    </div>
  </div>
  <?php if(!empty($node->field_image_gallery_bottom_text[$node->language])): ?>
    <div id="image-gallery-bottom-text">
      <?php print $node->field_image_gallery_bottom_text[$node->language][0]['value']; ?>
    </div>
  <?php endif; ?>
</div>

