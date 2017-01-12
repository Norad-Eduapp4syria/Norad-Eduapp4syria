#pragma once

#include "../Utils/TouchableGameObject.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
class HomeGame;


class PlayButton : public TouchableGameObject {

public:
	PlayButton(Node& parentNode, string nodeName, EventDispatcher* eventDispatcher, HomeGame* homeGame);
	virtual ~PlayButton();

protected:
	virtual bool onTouchBegan(Touch* touch, Event* event);
	SimpleAudioEngine* simpleAudioEngine;
private:
	HomeGame* homeGame;
	bool interacting;
	PlayButton();													// Unimplemented
	PlayButton(const PlayButton& otherPlayButton);					// Unimplemented
	PlayButton& operator=(const PlayButton& otherPlayButton);		// Unimplemented

};