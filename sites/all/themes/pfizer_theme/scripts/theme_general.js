//PUT ALL THE JS FUNCTIONS, AND CODES INSIDE THE (function ($) {* INSIDE HERE *})(jQuery);
(function ($) {
  var device = getUserAgent(); 
  $(document).ready(function() {
    addFakeActiveClass();
    hideUrlBar();
    playVideo();
    addDeviceClass();
    openISIBlock();
    hideMainMenuNavigation();
    treatMenuNavigationBehaviors();
    treatExpandedMenuBehaviors();
    checkIScroll();
    treatBackToTopClick();
    // Fire the functions that deal every time the window is resized or the orientation change.
    if ( window.orientation != undefined ) {
      window.onorientationchange = orientationChangeFunctions;
    }
    else {
      $(window).resize( orientationChangeFunctions );
    }
  });
  
  // Add fake active class to the links beacuse pseudo class active don't work in Android.
  function addFakeActiveClass(){
    $("nav#main-navigation a,header#header a")
    .bind("mouseup", function () {
        $(this).removeClass("fake-active");
    })
    .bind("mousedown", function () {
        $(this).addClass("fake-active");
    })
    .bind("touchstart", function () {
        $(this).addClass("fake-active");
    })
   .bind("touchend", function() {
        $(this).removeClass("fake-active");
    })
    .bind("touchcancel", function() {
        // sometimes Android fires a touchcancel event rather than a touchend. Handle this too.
        $(this).removeClass("fake-active");
    });
  }
  
  /* Apply iScrool only if the page isn't /user or user isn't logged in */
  function checkIScroll(){
    if($("body").hasClass("page-user") || $("body").hasClass("logged-in")) {
      $("body").addClass('no-iscroll');
    }
    else {
      iScrollEvents();
    }
  }
  function treatBackToTopClick() {
    $(".back-top").click(function() {
      myScroll.scrollTo(0, 0, 500);
    });
  }
  
  function treatExpandedMenuBehaviors() {
    $("#main-navigation li.expanded ul a").addClass("child");	
    $("#main-navigation a.no-link").attr('href', 'javascript:void(0);');

    $("#main-navigation li.expanded a").click(function() {    
      $(this).parent('li').toggleClass("opened");
      $(this).next('ul').slideToggle();
      myScroll.refresh();
    });
  }
  
  function treatMenuNavigationBehaviors() {
    $(".open-menu").click(function() {
      $(this).toggleClass("opened");
      $("div#overlay-mask").toggle();
      
      $("#main-navigation").toggleClass('opening');
      
      openActiveTrailSubmenu();
      
      $("#main-navigation li:not(.active-trail).expanded ul").hide();
      setMenuNavigationPosition();
      $("#main-navigation").slideToggle('fast',function(){
        $("#main-navigation li:not(.active-trail).expanded").removeClass('opened');
      });
      myScroll.refresh();
    });
    
    $('div#overlay-mask').click(function(){
      $(".open-menu").click();
    });
  }
  
  function openActiveTrailSubmenu() {
    var isActiveTrailOpened = $("#main-navigation li.active-trail.expanded").hasClass('opened');
    var isMainMenuOpening = $("#main-navigation").hasClass('opening');
    var shouldOpenActiveTrail = (!isActiveTrailOpened && isMainMenuOpening);
    
    if (shouldOpenActiveTrail) {
      $("#main-navigation li.active-trail.expanded").addClass('opened');
      $("#main-navigation li.active-trail.expanded ul").show();
    }
  }
  
  function setMenuNavigationPosition() {
    var headerHeight = $("header#header").height();
    var pageTopHeight = $("div#page-top").height();
    var openMenuButtonHeight = $(".open-menu").height();
    var menu_position = headerHeight - ( pageTopHeight / 2 ) + openMenuButtonHeight - 1;
    $("#main-navigation").css('top',menu_position);
  }
  
  function openISIBlock() {
    var isiSign = $('<span />').addClass('sign');
    $(".block-isi > h2").append(isiSign);

    $(".block-isi").click(function() {
            
      $(this).toggleClass("opened");

      clearInterval(resize);
      
      if($(this).hasClass("opened")){
        var isiExpandedHeight;
        if(device == "ios"){
      	  isiExpandedHeight = window.innerHeight;  
        }
        else {
          isiExpandedHeight = "100%";
        }
          $(this).animate({"height":isiExpandedHeight}, 500, function(){
            $("#wrapper-page").toggle();	
            $(this).css("height","100%");
            $(this).css("position","static");
          });	        
        
        
        $("#isi .region .opened").bind('touchmove',function(e) {
          e.stopPropagation();
        })
      } 
      else {
        $(this).css("position","absolute");  
        $("#wrapper-page").toggle();	
        window.scrollTo(0, 1);
        var isiHeight = window.innerHeight / 3;  
        $('.content', this).hide();
        
        $(this).animate({"height":isiHeight}, 500,function(){
          $(".block-isi").unbind('touchmove');
          if (typeof myScroll == 'object' && typeof myScroll.enabled != 'undefined') {
            myScroll.refresh();
          }
          reSetISIResizeInterval();
        });  
        $('.content', this).show();
      }
    });
  }
  
   /*if the current page is the front page, the right menu navigation should not appear*/
  function hideMainMenuNavigation() {
    if(!$("body").hasClass("front")) {
      $("#main-navigation").hide();
    }
  }
  
  function addDeviceClass() {
    $('body,html').addClass(device);
  }
  

  // Apply iScroll to an image gallery
  function applyGalleryCarousel() {    
    if ($('#image-gallery-images-wrapper').length > 0) {
      var indicator = $('#image-gallery-indicator');
      var galleryItens = $('#image-gallery-images .image-gallery-image');
      var gallery = $('#image-gallery-images');
      var galleryDimensions = getGalleryDimensions(galleryItens);
      
      addGalleryIndicator(galleryItens, indicator);

      $(gallery).height(galleryDimensions['height']);
      $(gallery).width(galleryDimensions['width']);
      $(gallery).css("visibility","visible");

      var previousPageX = 0;
      
      iCarouselGallery = new iScroll('image-gallery-images-wrapper', {
        snap: true,
        momentum: false,
        hScrollbar: false,
        onScrollEnd: function () {
          $('li.active',indicator).removeClass('active');
          $('li:nth-child(' + (this.currPageX+1) + ')', indicator).addClass('active');

          //treat only if the page has changed
          if (previousPageX != this.currPageX) {
            if(typeof window.trackSwipeOmniture == 'function') {
              // function exists, so we can now call it
              trackSwipeOmniture(this.currPageX);
            }
          }
          previousPageX = this.currPageX;
        },
        onScrollMove: function() {
          $(galleryItens).bind('click', function(e) {
            e.preventDefault();
          });
        }
      });
   
      myScroll.refresh();
      ImageGalleryClicked();
    }
  }

  // Get the width of the gallery itens to apply iScroll
  function getGalleryDimensions(gallery) {
    var dimensions = new Array();
    dimensions['width'] = 0;
    dimensions['height'] = 0;
    $(gallery).each(function(i) {
      dimensions['width'] += this.offsetWidth;
      dimensions['height'] = this.offsetHeight;
    });

    return dimensions;
  }

  // Add indicators itens bellow the gallery
  function addGalleryIndicator(galleryItens,indicator) {
    $(galleryItens).each(function(i) {
      $(indicator).append('<li/>');
    });
    $('li:first-child',indicator).addClass('active');
  }

  // Open the gallery image inside an overlay
  function ImageGalleryClicked() {
    var galleryOverlay = $('div#overlay-content-wrapper');
    $('div.image-gallery-image').bind("click", function () {
    
    
      if(Drupal.settings.imagesInAnOverlay) {
        var biggerImage = $('div.image-gallery-big-image', this).html();
        openOverlay(biggerImage);
      }
      else {
        if($(this).next().length > 0){
          iCarouselGallery.scrollToPage('next', 0);
        }
        else {
          iCarouselGallery.scrollToPage('prev', 0);
        }
      }
    
    });  
  }

  // Open any content inside the overlay
  function openOverlay(content){
    var overlay = $('div#overlay-content-wrapper');
    var overlayContent = $('div#overlay-content');
    $(overlayContent).html(content);
    $(overlay).addClass('opened');
    if(device == "ios"){
      $(overlay).height(window.innerHeight);
    }

    $(overlay).click(function() {
      if(device == "ios"){
        $(overlay).height(window.innerHeight - 60);
      }
      $(overlay).removeClass('opened');
      $(overlayContent).html('');
      hideUrlBar();
    });

    if($(overlay).hasClass("opened")){
      $(overlay).bind('touchmove', function(e) {
        e.stopPropagation();				  
      })
    }
    else {
      $(overlay).unbind('touchmove')
    }
    hideUrlBar();
  }

  function applyIScroll () {
    setTimeout(function() {
       myScroll = new iScroll('wrapper-page');
       applyGalleryCarousel();	
    }, 300);
  }

  function iScrollEvents() {
    document.addEventListener('touchmove', function(e) {
      var event = e.preventDefault();
    }, false);
    window.addEventListener('load', applyIScroll, false);
  }
 
 
 function playVideo() {
  $('#play-movie').click(function(){
    if(device == 'android') {
      document.getElementById('video-player').play();
    }
    else {
      var videoURL = $('#video-player source').attr('src');
      window.location = videoURL;
    }
    $("#video-player").bind("ended", function() {
       window.location = document.URL;
    });
  });
 }
 
 function getUserAgent(){
    // Get User Agent
    var user_agent = navigator.userAgent;
    var device; 
    
    switch(true) {
      case /iphone/i.test(user_agent) || /ipod/i.test(user_agent):
        device = 'ios';
        break;

      case /android/i.test(user_agent):
        device = 'android';
        break;
      default:
        device = 'desktop';
    }
    
    return device;
 }

  window.addEventListener('load', hideUrlBar, false);
  window.addEventListener('load', reSetISIResizeInterval, false);

  // Check to avoid misplacement of menu items block on Android when rotating the device 
  if(device == 'android'){
    setInterval(setMenuNavigationPosition, 20);
  }
  // Fired when user rotate the screen or chage the screen size
  function orientationChangeFunctions() {
    hideUrlBar();
    resizeISI();
    updateOverlaySize();
    setMenuNavigationPosition();
    reSetISIResizeInterval();
  }
  
  function updateOverlaySize(){
    if(device == "ios"){
      $('div#overlay-content-wrapper').height(window.innerHeight);
    }
  }
  
  function hideUrlBar() {
    window.scrollTo(0, 1);
  }
  
  function resizeISI() {
    if(!$(".block-isi").hasClass('opened')) {
      if(device == 'ios'){
        var isiHeight = window.innerHeight / 3;
        $('section#isi div.block-isi').height(isiHeight);
        $('div#wrapper-page').css('bottom',isiHeight);
      }
      if (typeof myScroll == 'object' && typeof myScroll.enabled != 'undefined') {
        myScroll.refresh();
      }
    }
  }
  
  var resize = setInterval(resizeISI, 500);
  function reSetISIResizeInterval() {
    resize = setInterval(resizeISI, 500);
  }
  
  
  // Menu Moving Up Feature //
  
    $(document).ready(function() {
		$('.no-link').bind("click.scroll", function(){
			if($(this).parent().hasClass('opened'))
	 			{ myScroll.scrollToElement(this); } 
	 		else { myScroll.scrollToElement('#main-navigation');}
	 	});
	});
  
  // End Menu Moving Up Feature //
  
})(jQuery);