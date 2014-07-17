<div id="video-wrapper">
  <div id="video-top-text">
    <?php print $node->body[$node->language][0]['value']; ?>
  </div>
  
  <div id="play-movie-wrapper">
    <div id="play-movie">
      <div id="video-play-button" class="general-sprite"></div>
      <?php 
        $image = $node->field_video_poster[$node->language][0];
        $image['path'] = $image['uri'];

        print theme('image_style', array('style_name' => 'video_poster', 'path' => $image['path']));
      ?>
    </div>
  </div>
  
  <video id="video-player" autobuffer poster="<?php print image_style_url('video_poster',$image['path'])?>">
    <source src="<?php print file_create_url($node->field_video_video[$node->language][0]['uri']);?>" />
  </video>
  
  <div id="video-bottom-text">
    <?php print $node->field_video_bottom_text[$node->language][0]['value']; ?>
  </div>
</div>
