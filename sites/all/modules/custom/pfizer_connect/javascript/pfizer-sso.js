var _getUrlLanguagePrefix = function() {
  var path = location.pathname.split('/');
  if (typeof path[1] != 'undefined') {
    var countrySettings = Drupal.settings.pfizerConnect.countrySettings;
    for (code in countrySettings) {
      if (countrySettings[code].prefix == path[1]) {
        return '/' + countrySettings[code].prefix;
      }
    }
    return '';
  }
}

var langPrefix = _getUrlLanguagePrefix();
var tokenUrl = window.location.protocol + "//" + window.location.hostname + langPrefix + "/rpx/token_handler";
var logoutUrl = window.location.protocol + "//" + window.location.hostname + langPrefix + "/user/logout";
var xdReceiverUrl = 'https://' + window.location.hostname + '/sites/default/files/xdreceiver.html';
var segment = PfizerConnect.getSegment();

JANRAIN.SSO.ENGAGE.check_login ({
  sso_server: 'https://dm-federate.pfizer.com',
  token_uri: tokenUrl,
  xd_receiver: xdReceiverUrl,
  logout_uri: logoutUrl,
  segment: segment
});

function doLogout() {
  JANRAIN.SSO.ENGAGE.logout({
    sso_server: 'https://dm-federate.pfizer.com/',
    logout_uri: logoutUrl
  });
};

function setSegment(language) {
  var altLangPrefix = PfizerConnect.getLanguagePrefix(language);
  var altTokenUrl = window.location.protocol + "//" + window.location.hostname + Drupal.settings.basePath + altLangPrefix + "/rpx/token_handler";
  var altXdReceiverUrl = 'https://' + window.location.hostname + Drupal.settings.basePath + 'sites/default/files/xdreceiver.html';
  var altLogoutUrl = window.location.protocol + "//" + window.location.hostname + Drupal.settings.basePath + altLangPrefix + "/user/logout";
  var altSegment = PfizerConnect.getAltSegment(language);
  
  JANRAIN.SSO.ENGAGE.check_login ({
    sso_server: 'https://dm-federate.pfizer.com',
    token_uri: altTokenUrl,
    xd_receiver: altXdReceiverUrl,
    logout_uri: altLogoutUrl,
    segment: altSegment
  });
  return true;
}