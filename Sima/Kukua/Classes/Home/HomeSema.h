#pragma once

#include "../Utils/TouchableGameObject.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

class HomeSema : public TouchableGameObject {

public:
	HomeSema(Node& parentNode, Vec2 pos, EventDispatcher* eventDispatcher);
	virtual ~HomeSema();

protected:
	virtual bool onTouchBegan(Touch* touch, Event* event);
	SimpleAudioEngine* simpleAudioEngine;
private:
	bool interacting;
	GameObject* mouth;
	GameObject* baloon;
	HomeSema();										// Unimplemented
	HomeSema(const HomeSema& otherSema);				// Unimplemented
	HomeSema& operator=(const HomeSema& otherSema);		// Unimplemented

};
