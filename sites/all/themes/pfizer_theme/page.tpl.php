<div id="wrapper-page">
  <div id="page">
    <!-- Header -->
    <header id="header" role="banner">
      <div class="section clearfix">
        <!-- Header Region -->
        <?php if(!empty($page['header'])): ?>
        <div class="section" id="header-region">
          <?php print render($page['header']); ?>
        </div>
        <?php endif;?>
        <!-- END Header Region -->
        
        <!-- Page Top Region -->
        <div class="section" id="page-top">
          <!-- Logo Image -->
          <?php if ($logo): ?>
            <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo">
              <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
            </a>
          <?php endif; ?>
          <!-- END Logo Image -->
          <?php if(!empty($page['top'])): ?>  
            <?php print render($page['top']); ?>
          <?php endif;?>
        </div> 
        <!-- END Page Top Region -->
      </div>
    </header>
    <!-- END Header -->
    
    <!-- Navigation -->
    <?php if(!empty($page['navigation']) ): ?>
    <nav id="main-navigation">
      <?php print render($page['navigation']); ?>
    </nav>
    <?php endif; ?>
    <!-- END Navigation -->
    <!-- Content -->
    <section id="main-wrapper">    
      <div id="content" class="column" role="main">
        <?php print $messages; ?>

        <?php if ($tabs): ?>
          <div class="tabs"><?php print drupal_render($tabs); ?></div>
        <?php endif; ?>

        <?php print render($page['content']); ?>
      </div>
    </section>
    <!-- END Content -->
    <!-- Footer -->
    <?php if(!empty($page['footer'])): ?>
    <footer id="footer" role="contentinfo">
      <div class="section" >
        <?php print render($page['footer']); ?>
      </div>  
    </footer>
    <?php endif; ?>
    <!-- END Footer -->
    <div id="overlay-mask"></div>
  </div>
</div>
<!-- Bottom Content -->
<?php if(!empty($page['bottom'])): ?>
<section id="isi" class="section fixed">
  <?php print render($page['bottom']); ?>
</section>
<?php endif; ?>
<!-- END Bottom Content -->
<!-- Overlay Content -->
<div id="overlay-content-wrapper">
  <div id="overlay-content"></div>
  <div id="close-overlay-content" class="general-sprite">[X]</div>
</div>
<!-- END Overlay Content -->