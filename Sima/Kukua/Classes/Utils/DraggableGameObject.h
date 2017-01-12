#pragma once

#include "TouchableGameObject.h"


class DraggableGameObject : public TouchableGameObject {

public:
	DraggableGameObject(Node& parentNode, string nodeName, string csbPath, string colliderSpritePath, EventDispatcher* eventDispatcher);
	DraggableGameObject(Node& parentNode, const Vec2& localPosition, string csbPath, string colliderSpritePath, EventDispatcher* eventDispatcher);
	virtual ~DraggableGameObject();

protected:
	Vec2 startLocalPosition;
	//virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	//virtual void onTouchEnded(Touch* touch, Event* event);

};