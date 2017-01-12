#include "TouchableGameObject.h"
#include "base/ccMacros.h"


TouchableGameObject::TouchableGameObject(Node& parentNode, string nodeName, string csbPath, string colliderSpritePath, EventDispatcher* eventDispatcher)
	: GameObject(parentNode, nodeName, csbPath, colliderSpritePath),
	touchable(false)
{

	// CCLOG("TouchableGameObject");

	assert(colliderSprite != nullptr);

	this->eventDispatcher = eventDispatcher;

	touchListener = nullptr;

}

TouchableGameObject::TouchableGameObject(Node& parentNode, const Vec2& localPosition, string csbPath, string colliderSpritePath, EventDispatcher* eventDispatcher)
	: GameObject(parentNode, localPosition, csbPath, colliderSpritePath),
	touchable(false)
{

	// CCLOG("TouchableGameObject");

	assert(colliderSprite != nullptr);

	this->eventDispatcher = eventDispatcher;

	touchListener = nullptr;

}

TouchableGameObject::~TouchableGameObject() {

	// CCLOG("~TouchableGameObject");

}

void TouchableGameObject::setTouchable(bool touchable) {

	this->touchable = touchable;

	if (touchable) {

		touchListener = EventListenerTouchOneByOne::create();
		touchListener->onTouchBegan = CC_CALLBACK_2(TouchableGameObject::onTouchBegan, this);
		touchListener->onTouchMoved = CC_CALLBACK_2(TouchableGameObject::onTouchMoved, this);
		touchListener->onTouchEnded = CC_CALLBACK_2(TouchableGameObject::onTouchEnded, this);
		eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, node);

	} else if (touchListener != nullptr) {

		eventDispatcher->removeEventListener(touchListener);
        touchListener = nullptr;
	}

}

bool TouchableGameObject::onTouchBegan(Touch* touch, Event* event) {

	// CCLOG("TouchableGameObject - onTouchBegan");

	return (touchable && intersectsPoint(*touch));

}

void TouchableGameObject::onTouchMoved(Touch* touch, Event* event) {

	// CCLOG("TouchableGameObject - onTouchMoved");

}

void TouchableGameObject::onTouchEnded(Touch* touch, Event* event) {

	CCLOG("TouchableGameObject - onTouchEnded");

}