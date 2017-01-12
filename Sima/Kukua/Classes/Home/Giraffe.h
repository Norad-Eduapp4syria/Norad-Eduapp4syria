#pragma once

#include "../Utils/TouchableGameObject.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

class Giraffe : public TouchableGameObject {

public:
	Giraffe(Node& parentNode, string nodeName, EventDispatcher* eventDispatcher);
	virtual ~Giraffe();

protected:
	virtual bool onTouchBegan(Touch* touch, Event* event);
	SimpleAudioEngine* simpleAudioEngine;
private:
	bool interacting;
	Giraffe();												// Unimplemented
	Giraffe(const Giraffe& otherGiraffe);					// Unimplemented
	Giraffe& operator=(const Giraffe& otherGiraffe);		// Unimplemented

};