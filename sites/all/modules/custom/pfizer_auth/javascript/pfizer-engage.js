(function() {
    if (typeof window.janrain !== 'object') window.janrain = {};
    if (typeof window.janrain.settings !== 'object') window.janrain.settings = {};

    // Token url
    janrain.settings.tokenUrl = window.location.protocol + '//' + window.location.hostname + '/rpx/token_handler';

    // Custom SAML
    janrain.settings.custom = true;
    janrain.settings.customSAML = true;
    janrain.settings.providers = Drupal.settings.pfizerAuthentication.SAMLProviders;
    janrain.settings.customSAMLProviderId = Drupal.settings.pfizerAuthentication.SAMLProviders;
    
    if (Drupal.settings.pfizerAuthentication.loginFormInterface == 'modal' && PfizerAuthentication.isModalCompatible()) {
      // Set iframe redirect behavior
      janrain.settings.popup = false;
      janrain.settings.customProviderInIFrame = true;
    }
    else {
      // Set popup size
      janrain.settings.customSAMLModalWidth = 285;
      janrain.settings.customSAMLModalHeight = 290;
    }

    function isReady() { janrain.ready = true; };
    if (document.addEventListener) {
      document.addEventListener('DOMContentLoaded', isReady, false);
    } else {
      window.attachEvent('onload', isReady);
    }

    var e = document.createElement('script');
    e.type = 'text/javascript';
    e.id = 'janrainAuthWidget';

    if (document.location.protocol === 'https:') {
      e.src = 'https://rpxnow.com/js/lib/dm-sso.pfizer.com/engage.js';
    } else {
      e.src = 'http://widget-cdn.rpxnow.com/js/lib/dm-sso.pfizer.com/engage.js';
    }

    var s = document.getElementsByTagName('script')[0];
    s.parentNode.insertBefore(e, s);
})();