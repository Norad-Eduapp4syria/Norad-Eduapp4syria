#pragma once

#include "../Utils/TouchableGameObject.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

class HomeElephant : public TouchableGameObject {

public:
	HomeElephant(Node& parentNode, string nodeName, EventDispatcher* eventDispatcher);
	virtual ~HomeElephant();

protected:
	virtual bool onTouchBegan(Touch* touch, Event* event);
	SimpleAudioEngine* simpleAudioEngine;
private:
	bool interacting;
	HomeElephant();														// Unimplemented
	HomeElephant(const HomeElephant& otherHomeElephant);				// Unimplemented
	HomeElephant& operator=(const HomeElephant& otheHomeElephant);		// Unimplemented

};