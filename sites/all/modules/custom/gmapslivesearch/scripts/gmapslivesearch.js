(function($){ 
  var buyNowFormObj, submitObj, inputBuyNowObj, errorContainerObj;
  
  $(document).ready(function(){
    //Global vars (used to improve performance avoiding multiple searches on the DOM)
    buyNowFormObj = $('form#gmapslivesearch-buy-now-form');
    submitObj = $('input.form-submit', buyNowFormObj);
    inputBuyNowObj = $('input.gmapslivesearch-field-address-to-search', buyNowFormObj);
    errorContainerObj = $('div.error', buyNowFormObj);

    initialize();
    initjScrollPane();
    setDefaultValueOnSearchInput();
    toggleDisableButton();
    buyNowFormValidation();
    applyJqTransform();    
    mobileButtonsBehavior();
    buyOnlineBehavior();
  });
  
  
  
  function initialize() {
    if($('div#gmapslivesearch-map').length) {
      //Setting default options
      var myOptions = {
        zoom: parseInt(Drupal.settings.gmapslivesearch.default_result_zoom),
        center: new google.maps.LatLng(Drupal.settings.gmapslivesearch.default_result_latitude, Drupal.settings.gmapslivesearch.default_result_longitude),
        mapTypeId: google.maps.MapTypeId.ROADMAP
      };
      
      //If we are showing results... set opts
      if(typeof Drupal.settings.gmapslivesearch.search_position != 'undefined' && Drupal.settings.gmapslivesearch.no_results_found !== false) {
        $.extend(myOptions, {
          zoom: parseInt(Drupal.settings.gmapslivesearch.zoom),
          center: new google.maps.LatLng(Drupal.settings.gmapslivesearch.search_position.lat, Drupal.settings.gmapslivesearch.search_position.lng)
        });
      }
      
      //Instantiate map
      var map = new google.maps.Map(document.getElementById("gmapslivesearch-map"), myOptions);

      //Obtain markers
      var markers = Drupal.settings.gmapslivesearch.results_list;
      if(typeof markers != 'undefined' && markers.length > 0) {
        //create bounds file to center the map acording to markers
        var bounds = new google.maps.LatLngBounds ();
        //Create info Window
        var infoWindow = new google.maps.InfoWindow();

        for (var i in markers) {
          var markerPos = new google.maps.LatLng(markers[i].location.lat, markers[i].location.lng);
          createMarker(
            map, 
            markerPos, 
            infoWindow, 
            i, 
            markers[i].name, 
            $('li:eq(' + parseInt(i) + ') div.GMap_Info', 'div#gmapslivesearch-stores').clone()[0]
          );
            
          // increase the bounds to take this point
          bounds.extend(markerPos);
        }
        // Fit these bounds to the map
        map.fitBounds(bounds);
        
        //setting maxium zoom after fitBounds
        var listener = google.maps.event.addListener(map, "idle", function() { 
          if (map.getZoom() > 16) map.setZoom(16); 
          google.maps.event.removeListener(listener); 
        });
        
        map.setCenter(bounds.getCenter());
      }
    }
  }
  
  //Creates the markers and its info windows
  function createMarker(map, latlng, infoWindow, id, title, description) {          
    var markerImage = new google.maps.MarkerImage('gmapslivesearch/marker/' + (parseInt(id)+1));
    
    var marker = new google.maps.Marker({
      position: latlng,
      map: map,
      title: title,
      icon: markerImage
    });
    
    //Attach Drupal behaviours
    Drupal.attachBehaviors($(description));
    
    google.maps.event.addListener(marker, 'click', function() {
      marker.setZIndex(9999);
      infoWindow.setContent(description);
      infoWindow.open(map, marker);
      map.setCenter(marker.position);
    });
    
    //Link the marker on results list to the map
    $('li a.centerMap[rel=!rel_number]'.replace('!rel_number', parseInt(id)+1), 'div#gmapslivesearch-stores').click(function() {
      google.maps.event.trigger(marker, 'click');
    });
  }

  //jScrollPane implementation. Used for the scrollbar on results
  function initjScrollPane() {
    if(!_isMobile() && Drupal.settings.gmapslivesearch.use_jscrollpane === true) {
      if ($.browser.msie) {
        $("#gmapslivesearch-stores").jScrollPane({
          verticalDragMinHeight: 0,
          verticalDragMaxHeight: 0
        });
        Drupal.attachBehaviors($('#gmapslivesearch-map-results'));
        $('div.jspTrack').css('height', '440px');
      }
      else {
        $("#gmapslivesearch-stores").jScrollPane({
          verticalDragMinHeight: Drupal.settings.gmapslivesearch.results_scroll_js_drag_height,
          verticalDragMaxHeight: Drupal.settings.gmapslivesearch.results_scroll_js_drag_height
        });
        Drupal.attachBehaviors($('#gmapslivesearch-map-results'));
      }
    }
  }
  
  //Helper to check if the device is mobile
  function _isMobile() {
    if ( typeof Drupal.settings.mobileDevice != "undefined" ) {
      return Drupal.settings.mobileDevice.type == 'mobile';
    }
    return false;
  }
  
  function setDefaultValueOnSearchInput() {
    //Behavior for search fields. Set the default text and remove it when field is on focus in case
    //user don't type anything get the default value and print on the field otherwise leave the input value.
    inputBuyNowObj.each(function(index, element){
      defaultValueFieldAddressToSearch($(element));
      $(element).focus(function() {
    	  clearValueFieldAddressToSearch($(element));
      });
      
      $(element).focusout(function() {
    	  defaultValueFieldAddressToSearch($(element));
      });
    });
    
    
    function defaultValueFieldAddressToSearch(element) {
      if (!_isValidTextInput(element)) {
        element.attr('value', Drupal.settings.gmapslivesearch.field_address_default_label);
        element.css("font-style", "italic");
      }
    }
    function clearValueFieldAddressToSearch(element) {
      if (!_isValidTextInput(element)) {
        element.attr('value', '');
        $(element).css("font-style", "normal");
      }
    }
  }
  
  //toggle disable class for the button
  function toggleDisableButton() {
    var input = inputBuyNowObj.bind('change keyup', function() {
      toggleEnableDisable($(this), submitObj);
    });

    toggleEnableDisable(input, submitObj);

    function toggleEnableDisable(element, submit) {
      if(_isValidTextInput(element)) {
        submit.removeClass('disabled');
      }
      else {
        submit.addClass('disabled');
      }
    }
  }
  
  //Checks if the text input of the find a store form is valid
  function _isValidTextInput(element) {
    return (element.attr('value') != '' && element.attr('value') != Drupal.settings.gmapslivesearch.field_address_default_label);
  }
  
  function buyNowFormValidation() {
    buyNowFormObj.submit(function() {     
      var elemVal = inputBuyNowObj.val();
      var validZipCode = /^[0-9]{5}$/.test(elemVal);
      var validCityState = /^[A-Za-z]+(\s[A-Za-z]+)?\s*,\s*[A-Za-z]+(\s[A-Za-z]+)?\s*$/.test(elemVal);
      
      var passValidation = _isValidTextInput(inputBuyNowObj) //Non default value, non empty
              && (validZipCode || validCityState); //Is an zipcode or city, state value
    
      if(!passValidation) {
        errorContainerObj.text(Drupal.settings.gmapslivesearch.error_msg)
                          .show();
      }
    
      return passValidation;
    });
  }
  
  function applyJqTransform() {
    if(Drupal.settings.gmapslivesearch.apply_jqtransform) {
      $("form#gmapslivesearch-buy-now-form, form.gmapslivesearch-find-online-form").jqTransform();
    }
  }
  
  function mobileButtonsBehavior() {
    if(_isMobile()) {      
      $('#gmapslivesearch-btn-map').click(function(){
        _gmapslivesearchShowMap();
      });
      
      $('#gmapslivesearch-btn-list').click(function(){
        _gmapslivesearchShowList();
      });
      
      $('#gmapslivesearch-stores a.centerMap').click(function() {
        _gmapslivesearchShowMap();
      });
      
      function _gmapslivesearchShowMap() {
        $('#gmapslivesearch-btn-map').hide();
        $('#gmapslivesearch-stores').hide();
        $('#gmapslivesearch-map').show();
        $('#gmapslivesearch-btn-list').show();
      }
      
      function _gmapslivesearchShowList() {
        $('#gmapslivesearch-loader').hide();
        $('#gmapslivesearch-btn-list').hide();
        $('#gmapslivesearch-map').hide();
        $('#gmapslivesearch-stores').show();
        $('#gmapslivesearch-btn-map').show();
      }
    }
  }
  
  function buyOnlineBehavior() {
    var find_online_form = $('form.gmapslivesearch-find-online-form');
    var find_online_select = $('select', find_online_form);
    var find_online_submit = $('a.gmapslivesearch-goto-online-store', find_online_form);

    handleGoToStoreLink(find_online_submit, find_online_select);

    find_online_select.change(function() {
      var box_wrapper = $(this).closest('div.buy-online-box-wrapper');
      var find_online_submit = $('a.gmapslivesearch-goto-online-store', box_wrapper);
      handleGoToStoreLink(find_online_submit, this);
    });

     
    function handleGoToStoreLink(link, store_selected) {
      link.attr('href', $(':selected', store_selected).val());
      link.unbind('click');
     
      if ($(':selected', store_selected).val() == Drupal.settings.basePath || $(':selected', store_selected).val() == '') {
        link.click(function(){
          if (!Drupal.settings.gmapslivesearch_remove_buy_now_button){
            alert(Drupal.t('Please select a retailer.'));
          }
          return false;
        });
      }
      else {
        Drupal.attachBehaviors(link.parent());
      }
    }
  }
})(jQuery);
