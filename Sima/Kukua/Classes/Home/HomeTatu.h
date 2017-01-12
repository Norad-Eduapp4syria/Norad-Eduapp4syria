#pragma once

#include "../Utils/TouchableGameObject.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

class HomeTatu : public TouchableGameObject {

public:
	HomeTatu(Node& parentNode, EventDispatcher* eventDispatcher);
	virtual ~HomeTatu();

protected:
	virtual bool onTouchBegan(Touch* touch, Event* event);
	SimpleAudioEngine* simpleAudioEngine;
private:
	bool interacting;
	HomeTatu();											// Unimplemented
	HomeTatu(const HomeTatu& otherHomeTatu);				// Unimplemented
	HomeTatu& operator=(const HomeTatu& otherHomeTatu);		// Unimplemented

};