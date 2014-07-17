var closeBtnImage = 'data:image/png;base64,' +
  'iVBORw0KGgoAAAANSUhEUgAAABkAAAAZCAYAAADE6YVjAAAAGXRFWHRTb2Z0d2FyZQBBZG9iZSBJbWFnZVJlYWR5ccllPAAAAyJpVFh' +
  '0WE1MOmNvbS5hZG9iZS54bXAAAAAAADw/eHBhY2tldCBiZWdpbj0i77u/IiBpZD0iVzVNME1wQ2VoaUh6cmVTek5UY3prYzlkIj8+ID' +
  'x4OnhtcG1ldGEgeG1sbnM6eD0iYWRvYmU6bnM6bWV0YS8iIHg6eG1wdGs9IkFkb2JlIFhNUCBDb3JlIDUuMC1jMDYwIDYxLjEzNDc3N' +
  'ywgMjAxMC8wMi8xMi0xNzozMjowMCAgICAgICAgIj4gPHJkZjpSREYgeG1sbnM6cmRmPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5LzAy' +
  'LzIyLXJkZi1zeW50YXgtbnMjIj4gPHJkZjpEZXNjcmlwdGlvbiByZGY6YWJvdXQ9IiIgeG1sbnM6eG1wPSJodHRwOi8vbnMuYWRvYmU' +
  'uY29tL3hhcC8xLjAvIiB4bWxuczp4bXBNTT0iaHR0cDovL25zLmFkb2JlLmNvbS94YXAvMS4wL21tLyIgeG1sbnM6c3RSZWY9Imh0dH' +
  'A6Ly9ucy5hZG9iZS5jb20veGFwLzEuMC9zVHlwZS9SZXNvdXJjZVJlZiMiIHhtcDpDcmVhdG9yVG9vbD0iQWRvYmUgUGhvdG9zaG9wI' +
  'ENTNSBNYWNpbnRvc2giIHhtcE1NOkluc3RhbmNlSUQ9InhtcC5paWQ6NDlENzlEREIxOTQ5MTFFMUI4MDNFMUVCMEFFRUIwMTQiIHht' +
  'cE1NOkRvY3VtZW50SUQ9InhtcC5kaWQ6NDlENzlEREMxOTQ5MTFFMUI4MDNFMUVCMEFFRUIwMTQiPiA8eG1wTU06RGVyaXZlZEZyb20' +
  'gc3RSZWY6aW5zdGFuY2VJRD0ieG1wLmlpZDo0OUQ3OUREOTE5NDkxMUUxQjgwM0UxRUIwQUVFQjAxNCIgc3RSZWY6ZG9jdW1lbnRJRD' +
  '0ieG1wLmRpZDo0OUQ3OUREQTE5NDkxMUUxQjgwM0UxRUIwQUVFQjAxNCIvPiA8L3JkZjpEZXNjcmlwdGlvbj4gPC9yZGY6UkRGPiA8L' +
  '3g6eG1wbWV0YT4gPD94cGFja2V0IGVuZD0iciI/PtljwdcAAATjSURBVHjajFZpTFRXFP5YhqWEYRAQhqFFQlJ+IFBsWUSqtdL+aZyW' +
  'KKZAYzWCtQKtYBXFEC2VRRYLYkzTNNEuJhTSsETbCrSxUkG2FvijJA0UKAOEJUVhhv31nMvMOAMFOeSD9+67937nnvOdc7GQJAnrmJz' +
  'gR/hhnTlVhALCwFoTLNYh2UK4SHiDsHlmZgY6nW75C62xtpbBUe4o3ggaQgzhIeHfjZKcJBTyQ1dnF1pamvHgfiP+7uuDtLQkdnWSyx' +
  'EQGIDQ8O3YEbkDzs7OPL2D8Jae9KkxyQqkESSNRiNlnDkrBflvlTbJnSSVu4fk7amSvFVeAs8rPSU3502Sl4dSilarpdo7dyS9tRPcT' +
  'PdceZJThPz2tjacy8hAxx9/QiaTwdbWds2ELNHJtNPTcFI4I+FoIj45fQoWFhYctnDCY9NwyQgnmIA3PnTwIMbHx2FjY8MLsBFbmJ+H' +
  'jvL2YdJxZJ4/Dysrqy4ajib0WOrn8N/8kZERcYKxsTHhPROwpwsLC1hcXFwVZh5n8LM1ndjBwQFfX7+BivJynhJISDRszjL9il++uHY' +
  'Nba2txvDwYqVSiVdCQuDr62uMMRPynMCgILwUHCw2Z2csLS3F96L8AvT29PAWsUzGJC+zTLu7u1FTVW0WIvZSpVLhxrffoKyiHC/6+U' +
  'Gr1Yrxc5mZqKypRvx78ZimnBhyS2ECiQY3v7vJr96EV5mEz+beRBLt7+83SzIvaGlpoRBch6ubGy5kZVF9WGN/TAzejYvFPwMDKL78u' +
  'SDluSLJegd/b7iHqakpfrzKJDqe1Eqb2dnZmcWdj8+huXqlFA+amhAWHkZEnyIpJVlsejb9DHp7e8XpTY0dGR4eRmdnhzHhmCdl9FGh' +
  'GbwxNT7Z5OQkci5mY3BwEEcSE7HFxweX8nLx2927sLe3x8qCZueePH6CYc3wUxJDktcyTuz9hgY0NTaKd1ZhdWXVcqFtQOKWG6kBju3' +
  'uPa8jKipKvLMYklI+EoW6lnMGJRpJOEwKZ4WQ4Uqbm52Fu7u7UJOC+lNRQSHa29qFqqL37QM3zv8j4PzK5XIjiYITFxoSumoBky7Rgu' +
  'PJyQjetg0/3r6N3OxslJYUC0WdTk8XstaRrE3Dxt9cXV3gH+BvJCkhjEdERkLu6Gh2GlbWXrUaR499gJHhEeTn5olE19fWicr2VHniw' +
  'mdZ1LcUQjymtjUgkMLqxY9l1vTrEuFtatsuO3e/hlvVNZA7ORnrhON+ubAIrc3NRrmyI6UlJUKmLFcXFxdML9eE+Mahio2PM/AVc4Pk' +
  '0/gQ/uKWknD4CDXHMbOi5OPzYiY07QY8xo4wkSHJ3BESSOZZ2Xzf4UtCMhMs6S+ZX7lHpZ5MW86FPmy8mDda2ZF5YyY19Cs2rqew7eF' +
  'IOfExv84SfuIyNEiY79W9PPj+4UNCSdxVWVmmrWLVtUrjDM6dTqvDzl27UFJaCjdqQWRq/f2/6tJ6jlBJeLOuthZ5OTnoftSNxYVFyG' +
  'xkZh2Br+E5fbIdSaqxcXFITUtlEbBn7xB+ftYdX0/YMzo6iorvy/FLfR00gxpMTEwYQ8PJ9VB6CBXtPxCDiIgIQ0QOEG5t5B8J7pTJh' +
  'GME37m5OXQ/fIShoaHlSqYfbjV+VCObqVD1lke4p88DnvWPhCleIKgJ2nVQRghbb5//BBgA0xWoovfeMJMAAAAASUVORK5CYII=';
var PfizerAuthSettings = Drupal.settings.pfizerAuthentication;
var PfizerAuthentication = new (function () {

  // Default options
  var options = {
    // modal width (not applicable for popup window)
    width : 290,
    // modal height (not applicable for popup window)
    height : 290,
    // keep modal hidden after calling triggerFlow
    hideModal : false,
    // redirect user to this url after login (empty = use Drupal's default destination)
    destination : ''
  };

  var providers = {
    'pfizer-pac' : {
      options : {
        hideModal : false
      }
    },
    'pfizer-emp' : {
      options : {
        hideModal : true
      },
      getJanrain : function () {
        return window.janrain;
      }
    }
  };

  var currentProvider;

  /**
   * Trigger login action.
   * @param provider
   * @param (optional) (arguments[1]) options 
   */
  this.login = function (provider) {
    // Validate required arguments.
    if (!isset(provider)) {
      throw('PfizerAuthentication: provider is not defined.');
    }
    if (jQuery.inArray(provider, PfizerAuthSettings.SAMLProviders) == -1) {
      throw('PfizerAuthentication: invalid provider.');
    }

    currentProvider = provider;

    // Extend options.
    options = jQuery.extend({}, options, providers[currentProvider].options);
    if (isset(arguments[1])) {
      options = jQuery.extend({}, options, arguments[1]);
    }

    // Setup.
    getJanrain().settings.tokenUrl = generateTokenUrl();
    if (PfizerAuthSettings.loginFormInterface == 'modal' && PfizerAuthentication.isModalCompatible()) {
      var iframe = getRedirectIframe();
      // Set modal size.
      iframe.css('width', options.width);
      iframe.css('height', options.height);
      iframe.dialog('option', 'width', options.width);
      iframe.dialog('option', 'height', options.height);
    }
    if (isset(providers[currentProvider].setup)) providers[currentProvider].setup();

    // Connect.
    getJanrain().engage.signin.triggerFlow(currentProvider);
    if (PfizerAuthSettings.loginFormInterface == 'modal' && PfizerAuthentication.isModalCompatible() && !options.hideModal) {
      // Open modal with iframe.
      getRedirectIframe().dialog('open');
    }
  }

  /**
   * SSO Logout from Pfizer Authentication
   */
  this.logout = function () {
    if (typeof doLogout != 'undefined') {
      doLogout();
    }
    else {
      window.location.href = window.location.protocol + '//' + window.location.hostname + '/user/logout';
    }
  }

  /**
   * Check modal compatibility for Pfizer Authentication
   * Due to privacy limitations in stack browsers (Safari and IE),
   * modal overlay (iframe) feature is not compatible.
   * These browsers will use the default window popup.
   * @return boolean
   */
  this.isModalCompatible = function () {
    var isSafari = (jQuery.browser.safari && !/chrome/i.test(navigator.userAgent));
    var isIExplorer = jQuery.browser.msie;
    return (isSafari || isIExplorer) ? false : true;
  }

  var getJanrain = function () {
    if (isset(providers[currentProvider].getJanrain)) {
      return providers[currentProvider].getJanrain();
    }
    var frame = window.frames['pfizer-auth-form-frame'];
    if (isset(frame)) {
      return frame.janrain;
    }
    else {
      return window.janrain;
    }
  }

  var generateTokenUrl = function () {
    var destination = options.destination ? options.destination : getQueryParameterByName('destination');
    return url = window.location.protocol + '//' + window.location.hostname + '/rpx/token_handler' + '?destination=' + destination;
  }

  var isRedirectPage = function () {
    return /pfizer-auth\/redirect$/i.test(window.location.pathname);
  }

  var preloadLoginBox = function () {
    var iframe = getRedirectIframe();
    var width = options.width;
    var height = options.height;
    iframe.dialog({
      modal: true,
      width: width,
      height: height,
      resizable: false,
      draggable: false,
      create: function () {
        var dialog = jQuery(this).closest(".ui-dialog");
        var closeBtn = jQuery('<div class="pfizer-auth-close-icon"></div>');
        closeBtn.css({
          'background' : 'url(' + closeBtnImage + ') no-repeat',
          'cursor' : 'pointer',
          'width' : 25,
          'height' : 25,
          'z-index' : 2000,
          'position' : 'absolute'
        });
        closeBtn.click(function () {
          iframe.dialog("close");
        });
        dialog.after(closeBtn);
      },
      open: function () {
        var dialog = jQuery(this).closest(".ui-dialog");
        dialog.find(".ui-dialog-titlebar:first").hide();
        dialog.find(".ui-dialog-content:first").css('padding', 0);
        jQuery("div.pfizer-auth-close-icon").css({
          'top' : parseFloat(dialog.css('top')) - 12,
          'left' : parseFloat(dialog.css('left')) + width
        }).show();
      },
      beforeClose: function () {
        jQuery("div.pfizer-auth-close-icon").hide();
      }
    });
    iframe.dialog("close");
    iframe.bind('dialogbeforeclose', function () {
      iframe.attr('src', '/pfizer-auth/redirect');
    });
  }

  var getRedirectIframe = function () {
    return jQuery('#pfizer-auth-form-frame').length
      ? jQuery('#pfizer-auth-form-frame')
      : jQuery('<iframe></iframe>')
      .attr('id', 'pfizer-auth-form-frame')
      .attr('name', 'pfizer-auth-form-frame')
      .attr('src', '/pfizer-auth/redirect')
      .attr('scrolling', 'no')
      .attr('frameborder', '0')
      .load(function (event) {
        jQuery(this).css('overflow', 'hidden');
      });
  }

  jQuery(document).ready(function () {
    // Preload login box.
    if (!PfizerAuthSettings.userIsLoggedIn) {
      if (PfizerAuthSettings.loginFormInterface == 'modal' && PfizerAuthentication.isModalCompatible() && !isRedirectPage()) {
        preloadLoginBox();
      }
    }
  });

})();

// Validate if variable is set.
function isset(variable) {
  return typeof variable != 'undefined';
}

// Get query string parameter.
function getQueryParameterByName(name) {
  name = name.replace(/[\[]/, "\\\[").replace(/[\]]/, "\\\]");
  var regexS = "[\\?&]" + name + "=([^&#]*)";
  var regex = new RegExp(regexS);
  var results = regex.exec(window.location.search);
  if (results == null) return '';
  else return decodeURIComponent(results[1].replace(/\+/g, ' '));
}
