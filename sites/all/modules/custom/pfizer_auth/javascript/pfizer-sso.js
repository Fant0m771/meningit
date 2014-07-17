var logoutUrl = window.location.protocol + '//' + window.location.hostname + '/user/logout';
var tokenUrl = window.location.protocol + '//' + window.location.hostname + '/rpx/token_handler';

jQuery(document).ready(function() {
  var xdReceiverUrl = 'https://' + window.location.hostname + '/xdreceiver';
  var segment = Drupal.settings.pfizerAuthentication.segment;
  var ssoServer = Drupal.settings.pfizerAuthentication.ssoServer;

  JANRAIN.SSO.ENGAGE.check_login({
    sso_server: ssoServer,
    token_uri: tokenUrl,
    xd_receiver: xdReceiverUrl,
    logout_uri: logoutUrl,
    segment: segment
  });
});

function doLogout() {
  var federateLogout = function() {
    JANRAIN.SSO.ENGAGE.logout({
      sso_server: Drupal.settings.pfizerAuthentication.ssoServer,
      logout_uri: logoutUrl
    });
  };

  // Load the PAC logout URL and pass the federate logout as a callback
  if (jQuery.inArray('pfizer-pac', Drupal.settings.pfizerAuthentication.SAMLProviders) > -1) {
    JANRAIN.SSO._loadUrls([Drupal.settings.pfizerAuthentication.PACLogoutUrl], federateLogout);
  }
};
