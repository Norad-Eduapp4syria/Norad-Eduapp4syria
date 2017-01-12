#include "PortalPlay.h"
#include "WatchmanScene.h"

PortalPlay::PortalPlay(Node& parentNode, EventDispatcher* eventDispatcher)
: TouchableGameObject(parentNode, Vec2::ZERO, WatchmanScene::PATH + "CSD/portal_play_btn.csb", "RootBone/colliderSprite", eventDispatcher),
	interacting(false)
{

	// CCLOG("PortalPlay");
    
    simpleAudioEngine = SimpleAudioEngine::getInstance();
    simpleAudioEngine->preloadEffect((WatchmanScene::PATH + "Audio/portal/portal_play_tap.mp3").c_str());
}

PortalPlay::~PortalPlay() {

	// CCLOG("~PortalPlay");

}

bool PortalPlay::onTouchBegan(Touch* touch, Event* event) {

	// CCLOG("PortalPlay - onTouchBegan");

	if (TouchableGameObject::onTouchBegan(touch, event)) {

		if (!interacting) {
            
			interacting = true;
            
            simpleAudioEngine->stopEffect(loopOpenSoundEffect);
           
            EventCustom event("PortalPlayButtonClicked");
            //event.setUserData(buf);
            
            eventDispatcher->dispatchEvent(&event);
            simpleAudioEngine->playEffect((WatchmanScene::PATH + "Audio/portal/portal_play_tap.mp3").c_str());
            
            DataProvider::getInstance()->setLastPortalOpened(portalName);
            
			play("Play_press", [&]() {
				interacting = false;
				//play("standing", nullptr, true);
                
                getActionTimeline()->clearLastFrameCallFunc();
			});
            

		}

	}

	return false;

}