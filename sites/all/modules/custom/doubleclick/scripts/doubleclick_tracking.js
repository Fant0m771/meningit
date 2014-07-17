function trackDoubleClick(trackVars, redirectUrl){

  var axel = Math.random() + "";
  var a = axel * 10000000000000;
  var trackString = "";
  
  if (typeof trackVars.cat !== "undefined" && trackVars.cat.length) {
    trackString += "cat="+ trackVars.cat +";";
  }
  
  if (typeof trackVars.strType !== "undefined" && trackVars.strType.length) {
    trackString += trackVars.strType +"="+ trackVars.trackValue+ ";";
  }
  
  if (typeof trackVars.ord !== "undefined" && trackVars.ord.length) {
    trackString += "ord="+ trackVars.ord +";num="+ a;
  } else {
    trackString += "ord="+ a;
  }
  
  var trackImg = jQuery('<iframe />')
    .attr('width','1')
    .attr('height','1')
    .attr('src', trackVars.clientUrl + ";src="+ trackVars.clientCode +";type="+ trackVars.clientStrCode +";"+ trackString +"?");

  if (redirectUrl != undefined) {
    trackImg.load(function () {
      window.location = redirectUrl;
    });
  }
  
  trackImg.appendTo('body');
  
}