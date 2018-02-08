var gameHeight;
var gameWidth
var hasWebGL;
var isMobile;
var isSupport;

calcAppSize();

try {
	hasWebGL = UnityLoader.SystemInfo.hasWebGL;
	isMobile = UnityLoader.SystemInfo.mobile;
} catch (error) {
	
}
isSupport = checkAppSupported();

updateAppContent();

window.addEventListener("load", fixAppSize);	

function calcAppSize()
{
	var w = window.innerWidth;
	var h = window.innerHeight;
	
	gameHeight = parseInt(h * 0.90);
	gameHeight = (gameHeight > 500) ? gameHeight : 500;
	gameWidth = (parseInt((gameHeight / 16) * 9) - 1);
}

function fixAppSize() {
	document.getElementById("gameContainer").style.height = gameHeight + "px";
	document.getElementById("gameContainer").style.width =  gameWidth + "px";
	
	document.getElementById("gameParent").style.height = gameHeight + "px";
	document.getElementById("gameParent").style.width =  gameWidth + "px";
}
	
function checkAppSupported () {
	if(isMobile) {
		return false;
	} else {
		if(!hasWebGL) {
			return false;
		} else if(["Firefox","Chrome","Safari"].indexOf(UnityLoader.SystemInfo.browser) == -1) {
			return false;
		}
	}
	return true;
}
var gameInstance;
function updateAppContent() {
	if(isSupport) {

		gameInstance = UnityLoader.instantiate("gameContainer", UNITY_WEBGL_BUILD_URL, {
//			onProgress: MyProgressFunction,
			Module: {
				keyboardListeningElement: document.getElementById('rootMountElement'),
				dataUrl: "FTM.data.unityweb?ver=" + GAME_VER_ID,
				asmCodeUrl: "FTM.asm.code.unityweb?ver=" + GAME_VER_ID,
				asmMemoryUrl: "FTM.asm.memory.unityweb?ver=" + GAME_VER_ID,
				asmFrameworkUrl: "FTM.asm.framework.unityweb?ver=" + GAME_VER_ID
			},
		});

//		gameInstance = UnityLoader.instantiate("gameContainer", UNITY_WEBGL_BUILD_URL);
	} else {
		if(isMobile) {
			window.addEventListener("load", addMobileError);	
		} else {
			window.addEventListener("load", addBrwserError);	
		}
	}
}

function addMobileError()
{
	var elem = getImageElement();
	elem.setAttribute("src", "TemplateData/Kesem_oops_mobile_v01.jpg");
	
	fixMapCoords("planetmap_ios");
	fixMapCoords("planetmap_android");
	
	elem.setAttribute("useMap", "#planetmap");
}
function addBrwserError()
{
	var elem = getImageElement();
	elem.setAttribute("src", "TemplateData/Kesem_oops_v01.jpg");
}

function getImageElement()
{
	var elem = document.createElement("img");

	elem.setAttribute("height", gameHeight);
	elem.setAttribute("width", gameWidth);
	elem.setAttribute("alt", "Not Supported");
	elem.setAttribute("id", "NotSupported");

	document.getElementById("gameContainer").appendChild(elem);
	return elem;
}

function fixMapCoords(elementName)
{
	var elm;
	var vector;
	var vArr;
	var ratio;
	
	ratio = ((100 / 1920) * gameHeight) / 100;
	
	elm = document.getElementById(elementName);
	vector = elm.getAttribute("coords");
	vArr = vector.split(",");
	vector =  parseInt(vArr[0] * ratio) + ",";
	vector += parseInt(vArr[1] * ratio) + ",";
	vector += parseInt(vArr[2] * ratio) + ",";
	vector += parseInt(vArr[3] * ratio)
	
	elm.setAttribute("coords", vector);
}

function MyProgressFunction(gameInstance, progress) {
	if (!gameInstance.Module)
    return;
  if (!gameInstance.logo) {
    gameInstance.logo = document.createElement("div");
    gameInstance.logo.className = "logo " + gameInstance.Module.splashScreenStyle;
    gameInstance.container.appendChild(gameInstance.logo);
  }
  if (!gameInstance.progress) {    
    gameInstance.progress = document.createElement("div");
    gameInstance.progress.className = "progress " + gameInstance.Module.splashScreenStyle;
    gameInstance.progress.empty = document.createElement("div");
    gameInstance.progress.empty.className = "empty";
    gameInstance.progress.appendChild(gameInstance.progress.empty);
    gameInstance.progress.full = document.createElement("div");
    gameInstance.progress.full.className = "full";
    gameInstance.progress.appendChild(gameInstance.progress.full);
    gameInstance.container.appendChild(gameInstance.progress);
  }
  gameInstance.progress.full.style.width = (100 * progress) + "%";
  gameInstance.progress.empty.style.width = (100 * (1 - progress)) + "%";
  if (progress == 1)
    gameInstance.logo.style.display = gameInstance.progress.style.display = "none";
}
