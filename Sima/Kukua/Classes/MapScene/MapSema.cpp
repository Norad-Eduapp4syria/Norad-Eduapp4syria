#include "MapSema.h"
#include "../Utils/Data/Logger.h"
#include "../AppMacros.h"
#include "../Utils/StringUtility.h"

MapSema::MapSema(Node& parentNode, const Vec2& localPosition, string csbPath, EventDispatcher* _eventDispatcher, vector<MapEpisode*>* episodesVector)
	: GameObject(parentNode, localPosition, csbPath)
{
   
    setScale(0.35);
   
    episodesVectorRef = episodesVector;
    
    
    // CCLOG("1episodesVector soze  = %lu", episodesVector->size());
    // CCLOG("1episodesVectorRef soze  = %lu", episodesVectorRef->size());
    
    simpleAudioEngine = CocosDenshion::SimpleAudioEngine::getInstance();

    eventDispatcher = _eventDispatcher;

	dataProvider = DataProvider::getInstance();
    
    portalCodeOn = "1-0";
    
    isJumping = false;
    
    play("minisema_stand", nullptr, true);
 
}

MapSema::~MapSema() {
  
}



void MapSema::moveCameraToEpisode(int episodeNum) {
    string episodeOnStr = StringUtility::toString(episodeNum);
    char *buf1 = &episodeOnStr[0u];
    EventCustom event("MoveMapToEpisodeEvent");
    event.setUserData(buf1);
    eventDispatcher->dispatchEvent(&event);
}

void MapSema::jumpToPortal(MapPortal* portal) {
    
    if (isJumping) return;
    
    CCLOG("---jump to portal!");
    
    string portalCodeToGo = portal->getPortalCode();
    string direction = "stay";
    
    int episodeOn = StringUtility::stringToNumber<int>( (StringUtility::split(portalCodeOn, '-')).at(0) );
    int episodeToGo =  StringUtility::stringToNumber<int>( (StringUtility::split(portalCodeToGo, '-')).at(0) );
    
    int watchmanOn =  StringUtility::stringToNumber<int>( (StringUtility::split(portalCodeOn, '-')).at(1) );
    int watchmanToGo =  StringUtility::stringToNumber<int>( (StringUtility::split(portalCodeToGo, '-')).at(1) );
    
    bool isLongJump = false;
    
    if (episodeOn == episodeToGo) {
        
        if (watchmanOn > watchmanToGo) {
            direction = "back";
        } else if (watchmanOn < watchmanToGo) {
            direction = "forward";
        } else {
            direction = "stay";
        }
        
    } else if (episodeOn > episodeToGo) {
        isLongJump = true;
        direction = "back";
    } else if (episodeOn < episodeToGo) {
        isLongJump = true;
        direction = "forward";
    }
    
    if ( episodeToGo == (episodeOn+1) ) {
        if ( (watchmanToGo == 0) && (watchmanOn == episodesVectorRef->at(episodeOn)->getPortalsVectorSize()-1 ) ) isLongJump = false;
    }
    if ( episodeToGo == (episodeOn-1) ) {
        if ( (watchmanOn == 0) && (watchmanToGo == episodesVectorRef->at(episodeToGo)->getPortalsVectorSize()-1 ) ) isLongJump = false;
    }

    
    
    if (direction == "stay") return;

    
    
    if (isLongJump) {
        isJumping = true;
        
        // move "camera" to current position
        moveCameraToEpisode(episodeOn);
        
        getNode().runAction(Sequence::create(DelayTime::create(0.6f), CallFunc::create([=](){
        
            
            getPortalFromPortalCode(portalCodeOn)->play("portal_jump_inside");
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("MapScene/audio/PortaljumpInside.wav");
            
            play("minisema_jump_inside", [=]() {
                //CCLOG("qui fine salta dentro");
                moveCameraToEpisode(episodeToGo);
                
                getNode().runAction(Sequence::create(DelayTime::create(0.6f), CallFunc::create([=](){
                
                    //CCLOG("qui salta fuori... portalCodeToGo = %s ", portalCodeToGo.c_str() );
                    
                    placeOnPortal( portal );
                  
                    portal->play("portal_jump_outside", [=]() {
                        portal->showPlayButton();
                        CCLOG("...................si può saltare!!");
                        portal->getActionTimeline()->clearLastFrameCallFunc();
                    });
                    
                    comeOutFromPortal();
                    
                }),  nullptr));
                
               
                
            });
            
            
        }),  nullptr));
        
        
        return;
    }
    
    
    string element = "";
    int eIdx = episodeOn;
    int wIdx = watchmanOn;
    while (element != portalCodeToGo) {
        
        element =  StringUtility::toString( eIdx ) + "-" + StringUtility::toString( wIdx );
        passagesVector.push_back(element);
        // CCLOG("element = %s", element.c_str());
        
        
        if (direction == "back") {
            wIdx--;
            if (wIdx==-1) {
                eIdx--;
                if (eIdx > 0) wIdx = episodesVectorRef->at(eIdx)->getPortalsVectorSize() -1;
            }
        }
        
        
        if (direction == "forward") {
            wIdx++;
            if (wIdx == (episodesVectorRef->at(eIdx)->getPortalsVectorSize() )) {
                eIdx++;
                wIdx = 0;
            }
        }
        
    }
    
    passagesVector.erase(passagesVector.begin()); // remove first element
    
    getPortalFromPortalCode(portalCodeOn)->hidePlayButton();
    
    isJumping = true;
    jump();
}

void MapSema::jumpToPortalTestFast(MapPortal* portal) {
    
    
    
    Vec2 finalPos =  node->getParent()->convertToNodeSpace( portal->getPosition() );
    
    finalPos = Vec2(finalPos.x, finalPos.y + 76);

    /////
    string episodeOn =  (StringUtility::split(portalCodeOn, '-')).at(0);
    string episodeToGo =  (StringUtility::split(portal->getPortalCode(), '-')).at(0);
    if (episodeOn != episodeToGo) {
        // move map to episodeToGo
   
        char *buf = &episodeToGo[0u];
        
        EventCustom event("MoveMapToEpisodeEvent");
        event.setUserData(buf);
        eventDispatcher->dispatchEvent(&event);
    }
    ////
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("MapScene/audio/sema_jumpOutside.wav");
    play("minisema_jump_A", [=]() {
        
        play(
             Sequence::createWithTwoActions(
                                            JumpTo::create(0.7f, finalPos, 100, 1),
                                            CallFunc::create(
                                                             [=]() {
                                                                 CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("MapScene/audio/sema_jumpInside.wav");
                                                                 portal->showPlayButton();
                                                                 play("minisema_jump_C", [=]() {
                                                                     portalCodeOn = portal->getPortalCode();
                                                                     play("minisema_stand", nullptr, true);
                                                                     getActionTimeline()->clearLastFrameCallFunc();
                                                                 });
                                                                 
                                                             }
                                                             )
                                            )
             );
        
    });
    
}



Vec2 MapSema::getPortalPosition(string portalCode) {
    
    return getPortalFromPortalCode( portalCode )->getPosition();
    
}


MapPortal* MapSema::getPortalFromPortalCode(string portalCode) {
    vector<string> portalCodeSplitted = StringUtility::split(portalCode, '-');
    string episodeNumStr = portalCodeSplitted.at(0);
    string portalNumStr = portalCodeSplitted.at(1);
    int episodeNumInt = StringUtility::stringToNumber<int>(episodeNumStr);
    int portalNumInt = StringUtility::stringToNumber<int>(portalNumStr);
    return episodesVectorRef->at(episodeNumInt)->getPortal(portalNumInt);
}


void MapSema::jump() {
    CCLOG("jump---------");
    string portalCode = passagesVector.at(0);
    passagesVector.erase(passagesVector.begin()); // remove first element
    //
    CCLOG("jump- portalCode = %s", portalCode.c_str());
    
    Vec2 finalPos =  node->getParent()->convertToNodeSpace( getPortalPosition(portalCode) );
    
    finalPos = Vec2(finalPos.x, finalPos.y + 76);
    
    //
    
    
    /////
    string episodeOn =  (StringUtility::split(portalCodeOn, '-')).at(0);
    string episodeToGo =  (StringUtility::split(portalCode, '-')).at(0);
    if (episodeOn != episodeToGo) {
        // move map to episodeToGo
        
        char *buf = &episodeToGo[0u];
        
        EventCustom event("MoveMapToEpisodeEvent");
        event.setUserData(buf);
        eventDispatcher->dispatchEvent(&event);
    }
    ////
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("MapScene/audio/sema_jumpOutside.wav");
    play("minisema_jump_A", [=]() {
        
        play(
             Sequence::createWithTwoActions(
                                            JumpTo::create(0.7f, finalPos, 100, 1),
                                            CallFunc::create(
                                                             [=]() {
                                                                 CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("MapScene/audio/sema_jumpInside.wav");
                                                                 play("minisema_jump_C", [=]() {
                                                                        portalCodeOn = portalCode;
                                                                     
                                                                        if (passagesVector.size() == 0) {
                                                                            getPortalFromPortalCode(portalCode)->showPlayButton();
                                                                            // TO_FIX   portal->showPlayButton();
                                                                            isJumping = false;
                                                                            play("minisema_stand", nullptr, true);
                                                                            getActionTimeline()->clearLastFrameCallFunc();
                                                                        } else {
                                                                            jump();
                                                                        }
                                                                     
                                                                });
                                                               
                                                             })
                                            )
             );
        
    });

    
}


void MapSema::placeOnPortal(MapPortal* portal) {
    CCLOG("place sema on portal ..code: %s", portal->getPortalCode().c_str());
    Vec2 finalPos = node->getParent()->convertToNodeSpace( portal->getPosition() );
    finalPos = Vec2(finalPos.x, finalPos.y + 76);
    CCLOG("pos sema = %f %f", finalPos.x, finalPos.y);
    portalCodeOn =  portal->getPortalCode();
    getNode().setPosition(finalPos);
}

void MapSema::comeOutFromPortal() {
   // node->stopAllActions();
    isJumping = true;
    this->bringToFront();
    play("minisema_jump_outside", [=]() {
        play("minisema_stand", nullptr, true);
        CCLOG("sema out and in stand");
        isJumping = false;
        getActionTimeline()->clearLastFrameCallFunc();
    });
}
