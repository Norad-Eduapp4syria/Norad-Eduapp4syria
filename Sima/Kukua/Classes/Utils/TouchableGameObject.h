#pragma once

#include "GameObject.h"


class TouchableGameObject : public GameObject {

public:
	TouchableGameObject(Node& parentNode, string nodeName, string csbPath, string colliderSpritePath, EventDispatcher* eventDispatcher);
	TouchableGameObject(Node& parentNode, const Vec2& localPosition, string csbPath, string colliderSpritePath, EventDispatcher* eventDispatcher);
	virtual ~TouchableGameObject();
	bool isTouchable() const;
	virtual void setTouchable(bool touchable);

protected:
	bool touchable;
	EventDispatcher* eventDispatcher;
	EventListenerTouchOneByOne* touchListener;
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);

};

inline bool TouchableGameObject::isTouchable() const {

	return touchable;

}