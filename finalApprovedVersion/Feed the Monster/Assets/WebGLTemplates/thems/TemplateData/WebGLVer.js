var AppVer;

checkVerDate();


function checkVerDate() {
	try {
		var urlParams = new URLSearchParams(window.location.search);
		var isHave = urlParams.has('ver'); // true
		if(!isHave) {
			var newUrl = window.location.toString();
			var n = newUrl.indexOf("?");
			if(n == -1) {
				newUrl += "?"
			}
			newUrl += "&ver=" + new Date().getTime();
			window.location.replace(newUrl);
		} else {
			var target = 1000 * 60 * 60;
			
			var old = parseInt(urlParams.get('ver'));
			var diff = new Date().getTime() - old;
			
			if(isNaN(diff) || diff > target) {
				var newUrl = window.location.toString();
				AppVer = new Date().getTime();

				if(newUrl.indexOf("ver=") != -1) {
					
					if(isNaN(diff)) {
						newUrl = newUrl.replace("ver=", "ver=" + AppVer);	
					} else {
						newUrl = newUrl.replace("ver=" + old, "ver=" + AppVer);	
					}
				} else if(newUrl.indexOf("ver") != -1){
					newUrl = newUrl.replace("ver", "ver=" + AppVer);
				}
				window.location.replace(newUrl);
			} else {
				AppVer = old;
				
			}
		}
    } catch(e) {

	}
}

function addNewScript(src) {
//  	var s = document.createElement( 'script' );
//	s.setAttribute( 'src', src );
//	document.head.appendChild( s );
	document.write('<scr'+'ipt type="text/javascript" src="' + src +'"></sc'+'ript>');
}	
	
function getEnvironment() {
	var url = window.location.host;
	var environment = '';
	if (url.indexOf('.dev.') > -1) {
		environment = '.dev';
	} else if (url.indexOf('.testing.') > -1) {
		environment = '.testing';
	} else if (url.indexOf('.staging.') > -1) {
		environment = '.staging';
	} else if (url.indexOf('.preprod.') > -1) {
		environment = '.preprod';
	}
	return environment;
}

function isTestEnvironment() {
	var url = window.location.host;

	if (url.indexOf('.dev.') > -1) {
		return true;
	} else if (url.indexOf('.testing.') > -1) {
		return true;
	} else if (url.indexOf('.staging.') > -1) {
		return true;
	} else if (url.indexOf('.preprod.') > -1) {
		return false;
	}
	return false;;
}


