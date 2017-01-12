#pragma once

#include "../Utils/TouchableGameObject.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

class Gazelle : public TouchableGameObject {

public:
	Gazelle(Node& parentNode, string nodeName, EventDispatcher* eventDispatcher);
	virtual ~Gazelle();

protected:
	virtual bool onTouchBegan(Touch* touch, Event* event);
	SimpleAudioEngine* simpleAudioEngine;
private:
	bool interacting;
	Gazelle();												// Unimplemented
	Gazelle(const Gazelle& otherGazelle);					// Unimplemented
	Gazelle& operator=(const Gazelle& otherGazelle);		// Unimplemented

};