#pragma once


#include "../Utils/PhysicsGameObject.h"
#include <vector>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"


using namespace std;


class PlatformGameSema : public PhysicsGameObject {

public:

	PlatformGameSema(Node& _parentNode, const Vec2& _localPosition, string animationCsbPath, string _colliderSpritePath, bool _dynamic, bool _gravityEnabled, EventDispatcher* _eventDispatcher, unsigned int _contactTestBitmask = 0xFFFFFFFF, const PhysicsMaterial& _material = cocos2d::PHYSICSBODY_MATERIAL_DEFAULT, PhysicsShape::Type _shape = PhysicsShape::Type::BOX);	// For nodes to be instantiated from a csb or new nodes
	virtual ~PlatformGameSema();

	GameObject* shadow;
	void destroy();
	bool clicked;
	string name;
	int typePlatformGameSema;
	int status; //
protected:
	
	virtual bool onContactBegin(PhysicsContact& contact);
	virtual bool onTouchBegan(Touch* touch, Event* event);

private:
	CocosDenshion::SimpleAudioEngine *audioEngine;

	Vec2 localPosition;
	EventDispatcher* eventDispatcher;
	
	
	
	float angleIn;
	float angleOut;

	void update();

};