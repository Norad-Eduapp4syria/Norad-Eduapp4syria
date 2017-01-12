#pragma once

#include "../TouchableGameObject.h"
#include <vector>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"


class KeyboardButton : public TouchableGameObject {

public:
	KeyboardButton(Node& parentNode, string nodeName, string csbPath, EventDispatcher* eventDispatcher);
	virtual ~KeyboardButton();
	bool isTouchable() const;
	string name;
	string editText;
protected:
	bool touchable;
	EventDispatcher* eventDispatcher;
	EventListenerTouchOneByOne* touchListener;
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);

};

inline bool KeyboardButton::isTouchable() const {

	return touchable;

}