var UserId = "";
var UserToken = "";
var UserDispalyName = "";
var isLoginInited = false;
var loginCallBackGameObject = null;
var loginCallBackFunction = null;


/*
if (window.addEventListener) {
    window.addEventListener('message', ssoMessagesReceiver, false);
} else {
    window.attachEvent('onmessage', ssoMessagesReceiver);
}
*/
 function ssoMessagesReceiver(e) {
	if (e.data.sender === 'CetSSO' && e.data.action) {
		switch (e.data.action) {
			case 'ready':
				break;
			case 'cookieChanged':
				break;
			case 'ssoLogout':
//				deleteCookie('ebagUData');
				break;
			case 'ssoSetSchool':
				break;
			case 'ssoLogin':
				break;
			case 'ssoSessionInfo':
				break;
		}
	}
 }

function isCetLogin()
{
	if(cet.uiServices.authentication.isLoggedIn()) {
		var user = cet.uiServices.authentication.userLogged();
		
		UserId = user.userID;
		UserToken = user.token;
		UserDispalyName = user.displayName;
		
		return JSON.stringify(user);
	}
	return "{}";
}

function doCetLogin(callBackGameObject, callBackFunction, userName, userPassword)
{
	CetSso.login(userName, userPassword,
		function (data, user) {
			if(data == true) {
				UserId = user.userID;
				UserToken = user.token;
				UserDispalyName = user.displayName;
				gameInstance.SendMessage(callBackGameObject, callBackFunction, JSON.stringify(user));
			} else {
				gameInstance.SendMessage(callBackGameObject, callBackFunction, "{}");
			}
		}
	);
}

function doCetLogout()
{
	cet.uiServices.login.logout();
	//CetSso.logout();
}

function getCetUser(callBackGameObject, callBackFunction) {
	var userJson = isCetLogin();
	gameInstance.SendMessage(callBackGameObject, callBackFunction, userJson);
}

function getCetUserId()
{
	if(cet.uiServices.authentication.isLoggedIn()) {		
		var user = cet.uiServices.authentication.userLogged();
		return user.userID;
	}
	return null;
}

function refreshSession()
{
	cet.uiServices.login.refreshsession();
//	CetSso.refreshsession();
}

function CetShowForgetPasswordPopup()
{
	if(isLoginInited == true) {
		cet.uiServices.login.passwordRecovery.show(false);
	}
}

function CetShowLoginPopup(callBackGameObject, callBackFunction)
{
	if(isLoginInited == true) {
		if(cet.uiServices.authentication.isLoggedIn()) {		
			var user = cet.uiServices.authentication.userLogged();
			
			UserId = user.userID;
			UserToken = user.token;
			UserDispalyName = user.displayName;
						
			gameInstance.SendMessage(callBackGameObject, callBackFunction, JSON.stringify(user));
		} else {
			deleteCookie('ebagUData');
			loginCallBackGameObject = callBackGameObject;
			loginCallBackFunction = callBackFunction;

			cet.uiServices.login.show();			
		}
	}
}

function getCetUserData(userId)
{
	return "{}";
}

function setCetUserData(userId, jsonData)
{	
//	alert(jsonData);
}





function isSubscription(callBackGameObject, callBackFunction)
{
//	var token = getCookie('CetSession');
	var isTrueSet = false;
	if(UserToken) {
		var environment = getEnvironment();
//		url = 'http://ebag' + environment + '.cet.ac.il/api/subscription/userhasmonsters';
		url = 'http://ebag' + environment + '.cet.ac.il/api/subscription/userHasProduct?productId=0b374cc3-5a89-4f85-a86a-ede4e0c85010';
//		url = 'http://ebag.testing.cet.ac.il/api/subscription/userhasmonsters';
		
		url += "&token=" + UserToken;
		
		xhttp('GET', url, "", function (data) {
			isTrueSet = (data.toLowerCase() === 'true');
			var res = "{\"ok\":" + ((isTrueSet) ? "true": "false") + "}";
			gameInstance.SendMessage(callBackGameObject, callBackFunction, res);
		}, function (jqXHR, textStatus, errorThrown) {
			var res = "{\"ok\":false}";
			gameInstance.SendMessage(callBackGameObject, callBackFunction, res);
		});
	}
}

function initLoginModule(language, idmEnabled, mountElement) {
	if(typeof cet === 'undefined' || typeof cet.uiServices === 'undefined' || typeof cet.uiServices.login === 'undefined') {
		setTimeout(
			function () {
				initLoginModule(language, idmEnabled, mountElement);
			}
		, 100);
	} else {
		setTimeout(
			function () {
				cet.uiServices.login.initModule({
					language: language
					,hasIdm: idmEnabled
					,siteKey: 'ebag'
					,siteName: 'lo.cet.ac.il'
					,url: window.location.href
					,container: $(mountElement)
					,setSSLiframeFromEbag: true 

					,onLogin: onLogin
					,onLogout: onLogout
					,onLoginProcessEnd: onLoginProcessEnd
					,onschoolupdate: onSchoolUpdate
					,onLoginReady: onLoginReady
					,onLogoutReady: onLogoutReady
				});
				isLoginInited = true;
			}
		, 300);
	}
}

initLoginModule("ar", true, document.getElementById('rootMountElement'));

function onLogin() {
//	alert("onLogin");
}

function onLogout() {
//	alert("onLogout");
}

function onLoginProcessEnd() {
	if(loginCallBackGameObject != null && loginCallBackFunction != null) {
		if(cet.uiServices.authentication.isLoggedIn()) {
			var user = cet.uiServices.authentication.userLogged();

			UserId = user.userID;
			UserToken = user.token;
			UserDispalyName = user.displayName;

			userJson = JSON.stringify(user);
			
			gameInstance.SendMessage(loginCallBackGameObject, loginCallBackFunction, userJson);
			loginCallBackGameObject = null;
			loginCallBackFunction = null;	
		}
	}
//	alert("onLoginProcessEnd");
}

function onLoginReady() {
//	alert("onLoginReady");
}

function onSchoolUpdate() {
//	alert("onSchoolUpdate");
}

function onLogoutReady() {
//	alert("onLogoutReady");
}

function xhttp(method, url, data, success, error) {
	var xhr = new XMLHttpRequest();
	method = method.toUpperCase();
	if (method === 'GET' && data) {
		if (data != undefined && data != null && data !== '') {
			if (typeof (data) == 'object') {
				var buffer = [];
				for (var key in data) {
					buffer.push(encodeURIComponent(key) + '=' + encodeURIComponent(data[key]));
				}
				data = buffer.join('&');
			}
			url = url + '?' + data;
		}
		data = '';
	} else {
		data = (typeof (data) === 'object' ? JSON.stringify(data) : data);
	}
	url = url.replace(/^http:/i, window.location.protocol);
	xhr.open(method, url);
//	xhr.responseType = 'text';
	xhr.setRequestHeader('Accept', 'application/json');
	xhr.setRequestHeader('Content-Type', 'application/json');
//	xhr.withCredentials = true;
	
	xhr.onreadystatechange = function (e) {
		if (xhr.readyState === 4) {
			var responseData = (/^[\{\[]/.test(xhr.responseText)) ? JSON.parse(xhr.responseText) : xhr.responseText;
			if (xhr.status >= 200 && xhr.status < 300) {
				success(responseData);
			} else {
				error(responseData);
			}
		}
	};
	try {
		if (data) {
			xhr.send(data);
		} else {
			xhr.send();
		}
	}
	catch (e) {
		error('' + e + '\n' + xhr.responseText);
	}
}



function getQuerystring(name) {
	var url = window.location.href;
	name = name.replace(/[\[\]]/g, "\\$&");
	var regex = new RegExp("[?&]" + name + "(=([^&#]*)|&|#|$)"),
	results = regex.exec(url);
	if (!results) return null;
	if (!results[2]) return '';
	return decodeURIComponent(results[2].replace(/\+/g, " "));
}
 
function getCookie(key) {
	return decodeURIComponent(document.cookie.replace(new RegExp("(?:(?:^|.*;)\\s*" + encodeURIComponent(key).replace(/[\-\.\+\*]/g, "\\$&") + "\\s*\\=\\s*([^;]*).*$)|^.*$"), "$1")) || '';
}

function setCookie(key, value) {
	document.cookie = encodeURIComponent(key) + "=" + encodeURIComponent(value) + '; domain=.cet.ac.il; path=/';
}

function deleteCookie(key) {
	document.cookie = encodeURIComponent(key) + "=; expires=Thu, 01 Jan 1970 00:00:00 GMT" + '; domain=.cet.ac.il; path=/';
}






