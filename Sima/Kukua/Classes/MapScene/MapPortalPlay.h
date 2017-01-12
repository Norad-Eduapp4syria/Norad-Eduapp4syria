#pragma once

#include "../Utils/TouchableGameObject.h"
#include "SimpleAudioEngine.h"


class MapPortalPlay : public TouchableGameObject {

public:
	MapPortalPlay(Node& parentNode, EventDispatcher* eventDispatcher);
	virtual ~MapPortalPlay();
    int loopOpenSoundEffect;

protected:
	virtual bool onTouchBegan(Touch* touch, Event* event);
    CocosDenshion::SimpleAudioEngine* simpleAudioEngine;

private:
	bool interacting;
	MapPortalPlay();												// Unimplemented
	MapPortalPlay(const MapPortalPlay& otherMapPortalPlay);					// Unimplemented
	MapPortalPlay& operator=(const MapPortalPlay& otherMapPortalPlay);		// Unimplemented

};