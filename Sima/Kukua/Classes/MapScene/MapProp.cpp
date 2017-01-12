#include "MapProp.h"
#include "../Utils/Data/Logger.h"
#include "../Utils/StringUtility.h"

MapProp::MapProp(Node& parentNode, const Vec2& localPosition, string csbPath, string colliderSpritePath, string partName, EventDispatcher* eventDispatcher)
: TouchableGameObject(parentNode, localPosition, csbPath, colliderSpritePath, eventDispatcher)
{
    name = partName;
    
    
    if ( (name == "windpower_1") || (name == "windpower_2") || (name == "ground") )  {
        setTouchable(false);
        play("standing", nullptr, true);
        return;
    }
    
    setTouchable(true);
    playStanding();
}

    
MapProp::~MapProp() {
    setTouchable(false);
    getNode().stopAllActions();
}

bool MapProp::onTouchBegan(Touch* touch, Event* event) {
	
	if (TouchableGameObject::onTouchBegan(touch, event)) {
		
        CCLOG("Tap on:  %s", name.c_str());
      
        node->stopAction(standingAction);
        
        play("tap", [=]() {
            playStanding();
            getActionTimeline()->clearLastFrameCallFunc();
        });
        
        
        playAudioTap();
        
        
	}

	// Always return false
	return false;

}

string MapProp::getName() {
    return name;
}


float MapProp::getRandomTime() {
    int randomInt = 4000 + rand() % 5000;
    float toRet = (float)randomInt / 1000.0f;
    return toRet;
}

void MapProp::playStanding() {
        
    standingAction = RepeatForever::create(
                                           Sequence::create(
                                                            DelayTime::create( getRandomTime() ),
                                                            CallFunc::create(
                                                                             [&]() {
                                                                                 play("standing");
                                                                             }),
                                                            nullptr
                                                            )
                                           );

    node->runAction(standingAction);
}

void MapProp::playAudioTap() {
    if ( StringUtility::startsWith(name, "chicken") ) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("MapScene/audio/chicken.wav");
    } else {
         CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(("MapScene/audio/" + name + ".wav").c_str());
    }
}

