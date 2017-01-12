#include "DraggableGameObject.h"
#include "base/ccMacros.h"


DraggableGameObject::DraggableGameObject(Node& parentNode, string nodeName, string csbPath, string colliderSpritePath, EventDispatcher* eventDispatcher)
	: TouchableGameObject(parentNode, nodeName, csbPath, colliderSpritePath, eventDispatcher),
	startLocalPosition(node->getPosition())
{

	assert(colliderSprite != nullptr);

	this->eventDispatcher = eventDispatcher;

	touchListener = nullptr;

}

DraggableGameObject::DraggableGameObject(Node& parentNode, const Vec2& localPosition, string csbPath, string colliderSpritePath, EventDispatcher* eventDispatcher)
	: TouchableGameObject(parentNode, localPosition, csbPath, colliderSpritePath, eventDispatcher),
	//startPosition(node->getParent()->convertToWorldSpace(node->getPosition()))
	startLocalPosition(node->getPosition())
{

	assert(colliderSprite != nullptr);

	this->eventDispatcher = eventDispatcher;

	touchListener = nullptr;

}

DraggableGameObject::~DraggableGameObject() {

}

/*bool DraggableGameObject::touchBegan(Touch* touch, Event* event) {

	CCLOG("DraggableGameObject - touchBegan");

	return (intersectsPoint(*touch) && onTouchBegan(touch, event));

}

void DraggableGameObject::touchMoved(Touch* touch, Event* event) {

	CCLOG("DraggableGameObject - touchMoved");

	return onTouchMoved(touch, event);

}

void DraggableGameObject::touchEnded(Touch* touch, Event* event) {

	CCLOG("DraggableGameObject - touchEnded");

	return onTouchEnded(touch, event);

}

bool DraggableGameObject::onTouchBegan(Touch* touch, Event* event) {

	CCLOG("DraggableGameObject - onTouchBegan");

	return (intersectsPoint(*touch));

}*/

void DraggableGameObject::onTouchMoved(Touch* touch, Event* event) {

	node->setPosition(node->getParent()->convertToNodeSpace(touch->getLocation()));

}

/*void DraggableGameObject::onTouchEnded(Touch* touch, Event* event) {

	CCLOG("DraggableGameObject - onTouchEnded");

}*/