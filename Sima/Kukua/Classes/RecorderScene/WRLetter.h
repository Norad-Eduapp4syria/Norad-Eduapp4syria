#pragma once

#include "../Utils/TouchableGameObject.h"
#include "SimpleAudioEngine.h"


class WRLetter : public TouchableGameObject {

public:
	//WRLetter(Node& parentNode, string nodeName, EventDispatcher* eventDispatcher);
	WRLetter(Node& parentNode, const Vec2& localPosition, EventDispatcher* eventDispatcher, string letter);
	WRLetter& operator=(const WRLetter& other);		// Unimplemented
	virtual ~WRLetter();
	void playAudio();

protected:
	CocosDenshion::SimpleAudioEngine* simpleAudioEngine;
	virtual bool onTouchBegan(Touch* touch, Event* event);

private:
	string txt;
	WRLetter();										// Unimplemented
	//WRLetter(const WRLetter& other);				// Unimplemented
	//WRLetter& operator=(const WRLetter& other);		// Unimplemented

};
