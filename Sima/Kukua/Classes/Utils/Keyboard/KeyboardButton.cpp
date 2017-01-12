#include "KeyboardButton.h"
#include "base/ccMacros.h"


KeyboardButton::KeyboardButton(Node& parentNode, string nodeName, string csbPath, EventDispatcher* eventDispatcher)
	: TouchableGameObject(parentNode, nodeName, csbPath, "BoneButton/Button", eventDispatcher),
	touchable(true)
{
	
	assert(colliderSprite != nullptr);

	this->eventDispatcher = eventDispatcher;

	touchListener = nullptr;

	this->setTouchable(true);


	//this->touchListener->setSwallowTouches(true);

	name = "";

}


KeyboardButton::~KeyboardButton() {

	// CCLOG("~KeyboardButton");

}

bool KeyboardButton::onTouchBegan(Touch* touch, Event* event) {
	if (TouchableGameObject::onTouchBegan(touch, event)) {
		//CCLOG("KeyboardButton - onTouchBegan %s", this->name.c_str());
		
		this->play("press",nullptr,false);

		EventCustom event("keyboard_click_button");
		event.setUserData(this);
		eventDispatcher->dispatchEvent(&event);

	}
	return false;
}

void KeyboardButton::onTouchMoved(Touch* touch, Event* event) {

	// CCLOG("KeyboardButton - onTouchMoved");

}

void KeyboardButton::onTouchEnded(Touch* touch, Event* event) {

	//CCLOG("KeyboardButton - onTouchEnded");

}
