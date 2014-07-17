(function ($) {

  Drupal.behaviors.desktopSite = {
    attach: function (context, settings) {
      $('a.desktop-site', context).click(function() {
        var result = true;
        if (!confirm(settings.desktopWarning)) {
          result = false;
        }
        return result;
      });
    }
  };

}(jQuery));
