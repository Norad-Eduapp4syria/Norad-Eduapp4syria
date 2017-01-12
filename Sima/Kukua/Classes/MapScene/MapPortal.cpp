#include "MapPortal.h"
#include "MapScene.h"
#include "../Utils/StringUtility.h"

MapPortal::MapPortal(Node& parentNode, Vec2 localPosition, string animationCsbPath, string colliderSpritePath, EventDispatcher* eventDispatcher, string _typePortal, string _state, int episodeNum, int watchmanNum)
: TouchableGameObject(parentNode, localPosition, animationCsbPath, colliderSpritePath, eventDispatcher)
{    
    state = _state;
    typePortal = _typePortal;
    lockIcon = Sprite::create("MapScene/png/Portal/portal_lock.png");
   
    portalCode = string(  StringUtility::toString( episodeNum )  ) + "-" + StringUtility::toString( watchmanNum ) ;
    
    
    
    if (typePortal == "nightrunner") {
        nightrunnerMask = new GameObject(*(node->getChildByName("portal_master")->getChildByName("mask_boss")->getChildByName("Node")), Vec2::ZERO, "MapScene/csd/chars/mask_boss.csb");
        nightrunnerMask->play("mask_boss_loop", nullptr, true);
        nightrunnerMask->setVisible(false);
    } else nightrunnerMask = nullptr;
  
    if (typePortal != "video") {
        static_cast<Sprite*>( getChild("portal_master/portal_color/portal_base/portal_base_ep1") )->setTexture("MapScene/png/Portal_color/portal_base_ep" +  StringUtility::toString(episodeNum) + ".png");
        static_cast<Sprite*>( getChild("portal_master/portal_color/portal_close/portal_close_ep1") )->setTexture("MapScene/png/Portal_color/portal_close_ep" +  StringUtility::toString(episodeNum) + ".png");
    }
   
    setStatus(state);
}

MapPortal::~MapPortal() {
    setTouchable(false);
    if (playButton != nullptr) delete playButton;
    if (nightrunnerMask != nullptr) {
        //nightrunnerMask->getNode().stopAllActions();
        delete nightrunnerMask;
    }
    
}


void MapPortal::setStatus(string status) {
    state = status;
    if (status == "locked") {
        playButton = nullptr;
        this->getChild("portal_master/portal_color")->setVisible(false);
        this->getChild("portal_master/portal_play/Node")->addChild(lockIcon);
        if (typePortal == "nightrunner") nightrunnerMask->setVisible(false);
        setTouchable(false);
    } else {
        lockIcon->removeFromParent();
        this->getChild("portal_master/portal_color")->setVisible(true);
        playButton = new MapPortalPlay(*(this->getChild("portal_master/portal_play/Node")), eventDispatcher);
        playButton->setVisible(false);
        if (typePortal == "nightrunner") nightrunnerMask->setVisible(true);
        setTouchable(true);
    }
}

void MapPortal::showPlayButton() {
    if (playButton != nullptr) {
        playButton->setVisible(true);
        playButton->play("portal_play_pop");
    }
    
}
void MapPortal::hidePlayButton() {
    if (playButton != nullptr) {
        playButton->setVisible(false);
    }
}

string MapPortal::getPortalCode() {
    return portalCode;
}
bool MapPortal::isVideo() {
    if (typePortal == "video") return true;
    return false;
    /*
    vector<string> portalCodeSplitted = StringUtility::split(portalCode, '-');
    if (portalCodeSplitted.at(1) == "0") return true;
    return false;
    */
}
bool MapPortal::isNightrunner() {
    if (typePortal == "nightrunner") return true;
    return false;
}

 

bool MapPortal::onTouchBegan(Touch* touch, Event* event) {
    
    if (TouchableGameObject::onTouchBegan(touch, event)) {
        CCLOG("tocco portale");
    
        if (playButton != nullptr) {
            if (playButton->isVisible()) return false;
        }
        
        // setTouchable(false);
        EventCustom event("PortalTouchedEvent");
        event.setUserData(this);
        eventDispatcher->dispatchEvent(&event);
        
    }
    
    return false;
    
}
