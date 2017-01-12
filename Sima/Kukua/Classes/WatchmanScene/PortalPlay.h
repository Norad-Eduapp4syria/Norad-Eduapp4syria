#pragma once

#include "../Utils/TouchableGameObject.h"
#include "SimpleAudioEngine.h"


class PortalPlay : public TouchableGameObject {

public:
	PortalPlay(Node& parentNode, EventDispatcher* eventDispatcher);
	virtual ~PortalPlay();
    int loopOpenSoundEffect;
    string portalName;

protected:
	virtual bool onTouchBegan(Touch* touch, Event* event);
    CocosDenshion::SimpleAudioEngine* simpleAudioEngine;

private:
	bool interacting;
	PortalPlay();												// Unimplemented
	PortalPlay(const PortalPlay& otherPortalPlay);					// Unimplemented
	PortalPlay& operator=(const PortalPlay& otherPortalPlay);		// Unimplemented

};