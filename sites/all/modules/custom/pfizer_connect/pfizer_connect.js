var PfizerConnect = {

  // Setup for Janrain and triggers Pfizer Connect popup
  setupAndConnect: function(siteId, langCode, destination, langPrefix) {
    if (typeof siteId == 'undefined' || typeof langCode == 'undefined') {
      throw 'PfizerConnect: siteId and languageCode not defined.';
    }

    this._setup(siteId, langCode, destination, langPrefix);
    this._connect();
  },

  // Logout from Pfizer Connect
  logout: function() {
    if (typeof doLogout == 'undefined') {
      window.location = '/user/logout';
    }
    else {
      doLogout();
    }
  },

  // Get SiteID for a specific language
  getSiteId: function(langCode) {
    if (typeof Drupal.settings.pfizerConnect.countrySettings[langCode] == 'undefined') {
      throw 'PfizerConnect: langCode is invalid.';
    }
    return Drupal.settings.pfizerConnect.countrySettings[langCode].site_id;
  },

  // Get LanguageCode for a specific language
  getLanguageCode: function(langCode) {
    if (typeof Drupal.settings.pfizerConnect.countrySettings[langCode] == 'undefined') {
      throw 'PfizerConnect: langCode is invalid.';
    }
    return Drupal.settings.pfizerConnect.countrySettings[langCode].language_code;
  },

  // Get Prefix for a specific language
  getLanguagePrefix: function(langCode) {
    if (typeof Drupal.settings.pfizerConnect.countrySettings[langCode] == 'undefined') {
      throw 'PfizerConnect: langCode is invalid.';
    }
    return Drupal.settings.pfizerConnect.countrySettings[langCode].prefix;
  },

  // Get Segment for current language
  getSegment: function() {
    var langCode = Drupal.settings.pfizerConnect.currentLanguage;

    if (typeof Drupal.settings.pfizerConnect.countrySettings[langCode] == 'undefined') {
      throw 'PfizerConnect: langCode is invalid.';
    }
    return Drupal.settings.pfizerConnect.countrySettings[langCode].segment;
  },

  // Get Segment for alternate language
  getAltSegment: function(langCode) {
    if (typeof Drupal.settings.pfizerConnect.countrySettings[langCode] == 'undefined') {
      throw 'PfizerConnect: langCode is invalid.';
    }
    return Drupal.settings.pfizerConnect.countrySettings[langCode].segment;
  },

  // Settings for Janrain
  _setup: function(siteId, langCode, destination, langPrefix) {
    if (typeof janrain != 'undefined') {
      janrain.settings.customOpenidOpxblob = this._getOpenidOpxblobOptions(siteId, langCode);
      janrain.settings.tokenUrl = this._getTokenUrl(destination, langPrefix);
    }
  },

  // Triggers Pfizer Connect popup
  _connect: function() {
    if (typeof janrain != 'undefined') {
      janrain.engage.signin.triggerFlow('customopenid');
    }
  },

  // Settings for opxblobOptions
  _getOpenidOpxblobOptions: function(siteId, langCode) {
    return '{' +
      '"site_id" : "' + siteId + '",' +
      '"site_lang" : "' + langCode + '"' +
    '}';
  },

  // Get token url
  _getTokenUrl: function(destination, langPrefix) {
    var destination = destination ? destination : getQueryParameterByName('destination');
    var callbackUrl = this._getTokenUrlLangPrefix(langPrefix) + '/rpx/token_handler';
    var tokenUrl = window.location.protocol + "//" + window.location.hostname + callbackUrl;
    return tokenUrl + '?destination=' + destination;
  },

  _getTokenUrlLangPrefix: function(langPrefix) {
    // reset tokenUrl in order to force a language if needed
    if (typeof langPrefix != 'undefined' && langPrefix) {
      if (langPrefix[0] != '/') {
        langPrefix = '/' + langPrefix;
      }
    }
    else {
      langPrefix = '';
    }
    return langPrefix;
  }
}

// Get query string parameter
function getQueryParameterByName(name) {
  name = name.replace(/[\[]/, "\\\[").replace(/[\]]/, "\\\]");
  var regexS = "[\\?&]" + name + "=([^&#]*)";
  var regex = new RegExp(regexS);
  var results = regex.exec(window.location.search);
  if (results == null) return "";
  else return decodeURIComponent(results[1].replace(/\+/g, " "));
}
