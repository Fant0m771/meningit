/**************************** PLUGINS *******************************/
/*
 * Utility Function: split v1.5 - split a string (JS 1.0 compatible)
 */
s.split=new Function("l","d",""
+"var i,x=0,a=new Array;while(l){i=l.indexOf(d);i=i>-1?i:l.length;a[x"
+"++]=l.substring(0,i);l=l.substring(i+d.length);}return a");
/*
* Plugin Utility: apl v1.1
*/
s.apl=new Function("L","v","d","u",""
+"var s=this,m=0;if(!L)L='';if(u){var i,n,a=s.split(L,d);for(i=0;i<a."
+"length;i++){n=a[i];m=m||(u==1?(n==v):(n.toLowerCase()==v.toLowerCas"
+"e()));}}if(!m)L=L?L+d+v:v;return L");
/*
 * Plugin: getTimeParting 3.0 - Set timeparting values based on time zone - valid through 2014
 */
s.getTimeParting=new Function("t","z",""
+"var s=this,d,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T;d=new Date();A"
+"=d.getFullYear();if(A=='2009'){B='08';C='01'}if(A=='2010'){B='14';C"
+"='07'}if(A=='2011'){B='13';C='06'}if(A=='2012'){B='11';C='04'}if(A="
+"='2013'){B='10';C='03'}if(A=='2014'){B='09';C='02'}if(!B||!C){B='08"
+"';C='01'}B='03/'+B+'/'+A;C='11/'+C+'/'+A;D=new Date('1/1/2000');if("
+"D.getDay()!=6||D.getMonth()!=0){return'Data Not Available'}else{z=p"
+"arseFloat(z);E=new Date(B);F=new Date(C);G=F;H=new Date();if(H>E&&H"
+"<G){z=z+1}else{z=z};I=H.getTime()+(H.getTimezoneOffset()*60000);J=n"
+"ew Date(I+(3600000*z));K=['Sunday','Monday','Tuesday','Wednesday','"
+"Thursday','Friday','Saturday'];L=J.getHours();M=J.getMinutes();N=J."
+"getDay();O=K[N];P='AM';Q='Weekday';R='00';if(M>30){R='30'}if(L>=12)"
+"{P='PM';L=L-12};if(L==0){L=12};if(N==6||N==0){Q='Weekend'}T=L+':'+R"
+"+P;if(t=='h'){return T}if(t=='d'){return O}if(t=='w'){return Q}}");
/*
 * Plugin: getQueryParam 2.3
 */
s.getQueryParam=new Function("p","d","u",""
+"var s=this,v='',i,t;d=d?d:'';u=u?u:(s.pageURL?s.pageURL:s.wd.locati"
+"on);if(u=='f')u=s.gtfs().location;while(p){i=p.indexOf(',');i=i<0?p"
+".length:i;t=s.p_gpv(p.substring(0,i),u+'');if(t){t=t.indexOf('#')>-"
+"1?t.substring(0,t.indexOf('#')):t;}if(t)v+=v?d+t:t;p=p.substring(i="
+"=p.length?i:i+1)}return v");
s.p_gpv=new Function("k","u",""
+"var s=this,v='',i=u.indexOf('?'),q;if(k&&i>-1){q=u.substring(i+1);v"
+"=s.pt(q,'&','p_gvf',k)}return v");
s.p_gvf=new Function("t","k",""
+"if(t){var s=this,i=t.indexOf('='),p=i<0?t:t.substring(0,i),v=i<0?'T"
+"rue':t.substring(i+1);if(p.toLowerCase()==k.toLowerCase())return s."
+"epa(v)}return ''");
/*
 * Plugin: getValOnce 0.2
 */
s.getValOnce=new Function("v","c","e",""
+"var s=this,k=s.c_r(c),a=new Date;e=e?e:0;if(v){a.setTime(a.getTime("
+")+e*86400000);s.c_w(c,v,e?a:0);}return v==k?'':v");