<?php

/**
 * class gmapslivesearchRollingCurl
 * Send multiple curl to google
 */
class gmapslivesearchRollingCurl {
  // private vars
  private $_rolling_window = 5;
  private $_urls = array();
  private $_stores = array();
  private $_search_location = null;
  private $_device_type;
  
  /**
   * method construct
   * params:
   *  $search_string: string
   */
  function __construct($search_string, $stores) {
    //get device type
    $this->_device_type = _gmapslivesearch_return_device_type();
    //get search location
    $this->_search_location = $this->getLatLong($search_string);
    //set urls for google place
    $this->setUrlsForGooglePlace($stores);    
    //init multiple curl requests
    $this->runRequests();
  }
  
  
  /**
   * method setUrlsForGooglePlace
   * description: Set urls to webservices of Google Place
   */
  private function setUrlsForGooglePlace($stores) {
    $radius = _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELDSET_DEFAULT_MILE_RADIUS);
    $radius_in_miles = round($radius*1609.344);
    $base_url = "https://maps.googleapis.com/maps/api/place/search/json?location=".$this->_search_location->lat.",".$this->_search_location->lng."&radius=".$radius_in_miles."&name=[name]&sensor=false&key="._gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_GOOGLEAPIKEY, 'all');
    
    $urls = array();
    foreach($stores as $store) {
      if(strlen($store) > 1){
        $urls[] = str_replace("[name]", trim($store), $base_url);
      }
    }
    
    $this->_urls = $urls;
  }
  
  private function runRequests($options = null) {
    $master = curl_multi_init();
    $curl_arr = array();

    // add additional curl options here
    $std_options = array(
      CURLOPT_RETURNTRANSFER => true,
      CURLOPT_FOLLOWLOCATION => true,
      CURLOPT_MAXREDIRS => 5,
      CURLOPT_SSL_VERIFYPEER => false
    );
    
    $custom_options = array();
    
    $options = ($custom_options) ? ($std_options + $custom_options) : $std_options;

    // start the first batch of requests
    for ($i = 0; $i < $this->_rolling_window; $i++) {
      $ch = curl_init();
      $options[CURLOPT_URL] = $this->_urls[$i];
      curl_setopt_array($ch,$options);
      curl_multi_add_handle($master, $ch);
    }
    
    do {
      while(($execrun = curl_multi_exec($master, $running)) == CURLM_CALL_MULTI_PERFORM);
      if($execrun != CURLM_OK)
        break;
      // a request was just completed -- find out which one
      while($done = curl_multi_info_read($master)) {
        $info = curl_getinfo($done['handle']);
        if ($info['http_code'] == 200) {
          $output = curl_multi_getcontent($done['handle']);

          // request successful.  process output using the callback function.
          $this->processRequest($output);

          // start a new request (it's important to do this before removing the old one)
          $ch = curl_init();
          $options[CURLOPT_URL] = $this->_urls[$i++];  // increment i
          curl_setopt_array($ch,$options);
          curl_multi_add_handle($master, $ch);

          // remove the curl handle that just completed
          curl_multi_remove_handle($master, $done['handle']);
        } else {
          // request failed.  add error handling.
        }
      }
    } while ($running);

    curl_multi_close($master);
  }
  
  /**
   * method processRequest
   * description: parse json
   */
  private function processRequest($output) {
    $stores = json_decode($output);
    if($stores->status == 'OK') {
      foreach($stores->results as $store) {
        $result = array(
          'name' => $store->name,
          'location' => $store->geometry->location,
          'address' => '',
          'city' => $store->vicinity,
          'distance' => $this->getDistance($store->geometry->location->lat, $store->geometry->location->lng),
          'goto_link' => $this->generateGoToLink($store)
        );
        
        //Splitting address and city
        $commaPos = strpos($store->vicinity, ',');
        if($commaPos!==FALSE) {
          $splitted_address = explode(',', $store->vicinity);
          $result['address'] = $splitted_address[0];
          $result['city'] = $splitted_address[1];
        }
        
        array_push($this->_stores, $result);
      }
    }
  }

  private function generateGoToLink($store) {
    $url = 'https://www.google.com/maps?source=uds&daddr=[code]&iwstate1=dir:to';
    $code = str_replace(' ', '+', $store->vicinity . ' ' . '(' . $store->name . ') %40' . $store->geometry->location->lat . ',' . $store->geometry->location->lng);
    
    return str_replace('[code]', $code, $url);
  }
  
  /**
   * method getDistance
   * description: obtain the distance for the search address and the store
   */
  private function getDistance($lat, $long) {
    //$earth = 6371; //km change accordingly
    $earth = 3960; //miles

    //Point 1 cords
    $lat1 = deg2rad($lat);
    $long1= deg2rad($long);
    //Point 2 cords
    $lat2 = deg2rad($this->_search_location->lat);
    $long2= deg2rad($this->_search_location->lng);

    //Haversine Formula
    $dlong=$long2-$long1;
    $dlat=$lat2-$lat1;

    $sinlat=sin($dlat/2);
    $sinlong=sin($dlong/2);

    $a=($sinlat*$sinlat)+cos($lat1)*cos($lat2)*($sinlong*$sinlong);

    $c=2*asin(min(1,sqrt($a)));

    $d=$earth*$c;

    return $d;
  }
  
  /**
   * method getLatLong
   * description: obtain latitude and longitude of the search address
   */
  public function getLatLong($search_string = '') {
    if(strlen($search_string) > 2) {
      $base_url = "http://maps.google.com/maps/api/geocode/json?address=[search]&sensor=false";
      $url = str_replace("[search]", urlencode(trim($search_string)), $base_url);
      $ch = curl_init($url);
      $options[CURLOPT_URL] = $url;
      $options[CURLOPT_RETURNTRANSFER] = true;
      curl_setopt_array($ch,$options);
      $json = curl_exec($ch);
      curl_close($ch);
      
      $data = json_decode($json);
      
      if($data->status == 'OK') {
        return $data->results[0]->geometry->location;
      }
    }
    return null;
  }
  
  /**
   * method orderStores
   * description: sort stores for distance
   */
  private function orderStores() {
    $position = array();  
    $newRow = array();  
    foreach ($this->_stores as $key => $row) {  
      $position[$key] = $row['distance'];  
      $newRow[$key] = $row;  
    }
    
    asort($position);
    
    $returnArray = array();  
    foreach ($position as $key => $pos) {
      $newRow[$key]['distance'] = round($newRow[$key]['distance'], 1);
      $returnArray[] = $newRow[$key];
    }
    $this->_stores = $returnArray;  
  }
  
  /**
   * method limitResult
   * description: limits the number of results returned
   */
  private function limitResult() {
    $max_results = _gmapslivesearch_get_value(GMAPSLIVESEARCH_FIELD_MAX_RESULT);
    if(count($this->_stores) > $max_results) {
      $this->_stores = array_slice($this->_stores, 0, $max_results);
    }
  }
  
  /**
   * method getStores
   * return the stores
   */
  public function getStores() {
    $this->orderStores();
    $this->limitResult();
    return $this->_stores;
  }
}
