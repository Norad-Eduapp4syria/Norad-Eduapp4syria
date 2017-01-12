#pragma once

#include "../Utils/TouchableGameObject.h"
#include "SimpleAudioEngine.h"
class Blending1Game;
class Cannon;


class CannonAimCollider : public TouchableGameObject {

public:
	CannonAimCollider(Node& parentNode, string nodeName, EventDispatcher* eventDispatcher, Blending1Game* blending1Game, Cannon* cannon);
	CannonAimCollider(Node& parentNode, const Vec2& localPosition, EventDispatcher* eventDispatcher, Cannon* cannon);
	virtual ~CannonAimCollider();

protected:
	CocosDenshion::SimpleAudioEngine* simpleAudioEngine;
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);

private:
	Blending1Game* blending1Game;
	unsigned int aimAudioId;
	Cannon* cannon;
	CannonAimCollider();												// Unimplemented
	CannonAimCollider(const CannonAimCollider& other);					// Unimplemented
	CannonAimCollider& operator=(const CannonAimCollider& other);		// Unimplemented

};