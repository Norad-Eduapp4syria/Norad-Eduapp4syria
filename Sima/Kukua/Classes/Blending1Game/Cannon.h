#pragma once

#include "../Utils/TouchableGameObject.h"
#include "../Utils/PhysicsGameObject.h"
#include "SimpleAudioEngine.h"
class CannonAimCollider;
class TatuProjectile;
class Blending1Game;


class Cannon : public TouchableGameObject {

public:
	Cannon(Node& parentNode, string nodeName, EventDispatcher* eventDispatcher, Blending1Game* blending1Game);
	virtual ~Cannon();
	virtual void setTouchable(bool touchable);
	void rotate(float deltaAngle);
	void load(bool enableTouch);
	void shot();
	void setCorrectLetterHit();

protected:
	CocosDenshion::SimpleAudioEngine* simpleAudioEngine;
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);

private:
	float rotation;
	bool correctLetterHit;
	Blending1Game* blending1Game;
	Node* pivotBone;
	GameObject* shotSmoke;
	CannonAimCollider* cannonAimCollider;
	TatuProjectile* tatuProjectile;
	Cannon();									// Unimplemented
	Cannon(const Cannon& other);				// Unimplemented
	Cannon& operator=(const Cannon& other);		// Unimplemented
	
};