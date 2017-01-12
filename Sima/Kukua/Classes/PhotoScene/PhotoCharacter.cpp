#include "PhotoCharacter.h"


PhotoCharacter::PhotoCharacter(Node& parentNode, string nodeName, string csbPath, string dragSpritePath, string colliderSpritePath, EventDispatcher* eventDispatcher)
	: DraggableGameObject(parentNode, nodeName, csbPath, dragSpritePath, eventDispatcher),
	touchOffset(Vec2::ZERO), colliderSpritePath(colliderSpritePath)
{

}

PhotoCharacter::~PhotoCharacter() {
}

bool PhotoCharacter::onTouchBegan(Touch* touch, Event* event) {

	if (TouchableGameObject::onTouchBegan(touch, event)) {

       // touchOffset = node->getParent()->convertToNodeSpace(touch->getLocation() - getLocalPosition());
        
		return true;

	}

	return false;

}

void PhotoCharacter::onTouchMoved(Touch* touch, Event* event) {
    DraggableGameObject::onTouchMoved(touch, event);
}

void PhotoCharacter::onTouchEnded(Touch* touch, Event* event) {
    
}


void PhotoCharacter::activate() {
    setPosition(Vec2(640,400));
    setVisible(true);
    setTouchable(true);
    touchListener->setSwallowTouches(true);
}
void PhotoCharacter::deactivate() {
    setVisible(false);
    setTouchable(false);
    
}


