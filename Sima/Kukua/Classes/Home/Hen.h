#pragma once

#include "../Utils/TouchableGameObject.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

class Hen : public TouchableGameObject {

public:
	Hen(Node& parentNode, string nodeName, EventDispatcher* eventDispatcher);
	virtual ~Hen();

protected:
	virtual bool onTouchBegan(Touch* touch, Event* event);
	SimpleAudioEngine* simpleAudioEngine;

private:
	
	static const int STANDING_LOOP;
	static int LAST_STANDING_OFFSET;
	int standingOffset;
	bool interacting;
	Action* standingAction;
	//Action* runningAction;
	Hen();										// Unimplemented
	Hen(const Hen& otherHen);					// Unimplemented
	Hen& operator=(const Hen& otherHen);		// Unimplemented

};