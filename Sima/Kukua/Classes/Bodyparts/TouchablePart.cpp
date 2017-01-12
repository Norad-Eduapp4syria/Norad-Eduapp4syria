#include "TouchablePart.h"
#include "../Utils/Data/Logger.h"

TouchablePart::TouchablePart(Node& parentNode, const Vec2& localPosition, string csbPath, string colliderSpritePath, string partName, EventDispatcher* eventDispatcher)
: TouchableGameObject(parentNode, localPosition, csbPath, colliderSpritePath, eventDispatcher)
{
    name = partName;
    
    float hitScaleX;
    float hitScaleY;
    
    if (partName == "wrong") {
        hitScaleX = parentNode.getChildByName("body_master")->getChildByName("head_master")->getChildByName("wrong")->getChildByName(partName)->getScaleX();
        hitScaleY = parentNode.getChildByName("body_master")->getChildByName("head_master")->getChildByName("wrong")->getChildByName(partName)->getScaleY();
        
    } else {
        hitScaleX = parentNode.getChildByName("body_master")->getChildByName("head_master")->getChildByName("placeholders")->getChildByName(partName)->getScaleX();
        hitScaleY = parentNode.getChildByName("body_master")->getChildByName("head_master")->getChildByName("placeholders")->getChildByName(partName)->getScaleY();
        
    }
    
    node->getChildByName("hitSprite")->setScale(hitScaleX, hitScaleY);
    node->setOpacity(0);
}

    
TouchablePart::~TouchablePart() {
}

bool TouchablePart::onTouchBegan(Touch* touch, Event* event) {
	
	//CCLOG("TouchablePart - onTouchBegan");

	if (TouchableGameObject::onTouchBegan(touch, event)) {
		//setTouchable(false);
        CCLOG("Tap on:  %s", name.c_str());
      
        EventCustom event("BodyPartTouchedEvent");
        event.setUserData(this);
        eventDispatcher->dispatchEvent(&event);
        
        
        Node* touchEffect = CSLoader::createNode("Bodyparts/csd/tap.csb");
          node->getParent()->getParent()->addChild(touchEffect);
        touchEffect->setPosition(node->getParent()->getParent()->convertToWorldSpace(touch->getLocation()));
        
        touchEffect->setPosition( touchEffect->getPositionX(), touchEffect->getPositionY() + 72 );
        
        cocostudio::timeline::ActionTimeline* touchEffectTimeline = CSLoader::createTimeline("Bodyparts/csd/tap.csb");
        touchEffect->runAction(touchEffectTimeline);
        
        touchEffect->setScale(1.5f);
        
        touchEffectTimeline->play("tap", false);
        
        
        touchEffect->getChildByName("circle")->getChildByName("circle")->runAction(FadeOut::create(0.8f));
        touchEffect->getChildByName("circle_2")->getChildByName("circle")->runAction(FadeOut::create(0.8f));
        touchEffect->getChildByName("star_master_1")->getChildByName("star_1")->runAction(FadeOut::create(1.0f));
        touchEffect->getChildByName("star_master_2")->getChildByName("star_1")->runAction(FadeOut::create(1.0f));
        
        /*
        touchEffectTimeline->setLastFrameCallFunc([=](){
            touchEffect->setVisible(false);
            touchEffectTimeline->clearLastFrameCallFunc();
        });
        */
	}

	// Always return false
	return false;

}

string TouchablePart::getName() {
    return name;
}

void TouchablePart::enableTouch() {
    setTouchable(true);
    touchListener->setSwallowTouches(true);
}
void TouchablePart::disableTouch() {
    setTouchable(false);
}
