#include "MapPortalPlay.h"
#include "MapScene.h"
#include "../AppMacros.h"
#include "../Utils/Data/Logger.h"

MapPortalPlay::MapPortalPlay(Node& parentNode, EventDispatcher* eventDispatcher)
: TouchableGameObject(parentNode, Vec2::ZERO, "MapScene/csd/portals/portal_play.csb", "portal_play/colliderSprite", eventDispatcher),
	interacting(false)
{

    
    simpleAudioEngine = SimpleAudioEngine::getInstance();
    //simpleAudioEngine->preloadEffect((MapScene::PATH + "Audio/MapPortal/MapPortal_play_tap.mp3").c_str());
    
    setTouchable(true);
}

MapPortalPlay::~MapPortalPlay() {
     setTouchable(false);
	// CCLOG("~MapPortalPlay");

}

bool MapPortalPlay::onTouchBegan(Touch* touch, Event* event) {

	// CCLOG("MapPortalPlay - onTouchBegan");

	if (TouchableGameObject::onTouchBegan(touch, event)) {

		if (!interacting) {
            
            if (isVisible() == false) return false;
            
			// interacting = true;
           // CCLOG("cliccato MapPortalPlay! lo rendo non più cliccabile.");
            
            play("portal_play_tap");
            
            EventCustom event("PortalPlayTouchedEvent");
            //event.setUserData(this);
            eventDispatcher->dispatchEvent(&event);
            
		}

	}

	return false;

}
