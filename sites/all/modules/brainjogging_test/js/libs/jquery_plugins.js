/**
 * The jQuery Chrono plugin, @version 1.0
 * Copyright (c) 2011 Arthur Klepchukov
 * Licensed under the 3-clause BSD license
 */
var jQueryChrono;(function(a){function c(){var d=jQueryChrono.create_timer.apply(this,arguments);return setTimeout(d.callback,d.when)}function b(){var d=jQueryChrono.create_timer.apply(this,arguments);return setInterval(d.callback,d.when)}a.extend({after:c,every:b})}(jQuery));jQueryChrono=(function(){var c={delay:4,units:"milliseconds"},b=1,f=b*1000,d=f*60,i=d*60,h=i*24;var j={millisecond:b,milliseconds:b,ms:b,second:f,seconds:f,sec:f,secs:f,s:f,minute:d,minutes:d,min:d,mins:d,m:d,hour:i,hours:i,hr:i,hrs:i,h:i,day:h,days:h,d:h};function e(k,l){if(typeof l[0]==="string"){k.delay=parseFloat(l[0],10)}else{k.delay=l[0]}if(typeof k.delay!=="number"||isNaN(k.delay)){$.error("$.after and $.every - Require a numerical delay as the 1st argument")}return k}function g(k,l){if(typeof l[0]==="string"&&k.delay!==null){k.units=l[0].replace(k.delay,"")||null}if(typeof l[1]==="string"){k.units=l[1]}if(k.units===null&&l.length===2){k.units=c.units}if(typeof j[k.units]!=="number"){$.error("$.after and $.every - Require a valid unit of time as the 2nd argument")}return k}function a(k,l){k.callback=l[l.length-1];if(!$.isFunction(k.callback)){$.error("$.after and $.every - Require a callback as the last argument")}return k}return{defaults:c,valid_units:j,create_timer:function(){var k={delay:null,units:null,when:null,callback:null};if(arguments.length<2||arguments.length>3){$.error("$.after and $.every - Accept only 2 or 3 arguments")}k=e(k,arguments);k=g(k,arguments);k=a(k,arguments);if(k.delay<c.delay&&k.units===c.units){k.delay=c.delay}if(k.delay<0){k.delay=c.delay;k.units=c.units}k.when=k.delay*j[k.units];return k}}}());

(function($){var escapeable=/["\\\x00-\x1f\x7f-\x9f]/g,meta={'\b':'\\b','\t':'\\t','\n':'\\n','\f':'\\f','\r':'\\r','"':'\\"','\\':'\\\\'};$.toJSON=typeof JSON==='object'&&JSON.stringify?JSON.stringify:function(o){if(o===null){return'null';}
var type=typeof o;if(type==='undefined'){return undefined;}
if(type==='number'||type==='boolean'){return''+o;}
if(type==='string'){return $.quoteString(o);}
if(type==='object'){if(typeof o.toJSON==='function'){return $.toJSON(o.toJSON());}
if(o.constructor===Date){var month=o.getUTCMonth()+1,day=o.getUTCDate(),year=o.getUTCFullYear(),hours=o.getUTCHours(),minutes=o.getUTCMinutes(),seconds=o.getUTCSeconds(),milli=o.getUTCMilliseconds();if(month<10){month='0'+month;}
if(day<10){day='0'+day;}
if(hours<10){hours='0'+hours;}
if(minutes<10){minutes='0'+minutes;}
if(seconds<10){seconds='0'+seconds;}
if(milli<100){milli='0'+milli;}
if(milli<10){milli='0'+milli;}
return'"'+year+'-'+month+'-'+day+'T'+
hours+':'+minutes+':'+seconds+'.'+milli+'Z"';}
if(o.constructor===Array){var ret=[];for(var i=0;i<o.length;i++){ret.push($.toJSON(o[i])||'null');}
return'['+ret.join(',')+']';}
var name,val,pairs=[];for(var k in o){type=typeof k;if(type==='number'){name='"'+k+'"';}else if(type==='string'){name=$.quoteString(k);}else{continue;}
type=typeof o[k];if(type==='function'||type==='undefined'){continue;}
val=$.toJSON(o[k]);pairs.push(name+':'+val);}
return'{'+pairs.join(',')+'}';}};$.evalJSON=typeof JSON==='object'&&JSON.parse?JSON.parse:function(src){return eval('('+src+')');};$.secureEvalJSON=typeof JSON==='object'&&JSON.parse?JSON.parse:function(src){var filtered=src.replace(/\\["\\\/bfnrtu]/g,'@').replace(/"[^"\\\n\r]*"|true|false|null|-?\d+(?:\.\d*)?(?:[eE][+\-]?\d+)?/g,']').replace(/(?:^|:|,)(?:\s*\[)+/g,'');if(/^[\],:{}\s]*$/.test(filtered)){return eval('('+src+')');}else{throw new SyntaxError('Error parsing JSON, source is not valid.');}};$.quoteString=function(string){if(string.match(escapeable)){return'"'+string.replace(escapeable,function(a){var c=meta[a];if(typeof c==='string'){return c;}
c=a.charCodeAt();return'\\u00'+Math.floor(c/16).toString(16)+(c%16).toString(16);})+'"';}
return'"'+string+'"';};})(jQuery);