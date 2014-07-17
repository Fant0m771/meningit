(function ($) {
  $(document).ready(function() {
    $('#open-mobile-menu').bind('click', function () {
      $(this).toggleClass('opened');
      $(".pane-menu-menu-mobile-menu").slideToggle();
    });
  });

})(jQuery);