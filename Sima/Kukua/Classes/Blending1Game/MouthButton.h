#pragma once

#include "../Utils/TouchableGameObject.h"
#include "SimpleAudioEngine.h"


class MouthButton : public TouchableGameObject {

public:
	MouthButton(Node& parentNode, string nodeName, EventDispatcher* eventDispatcher, const string& word);
	virtual ~MouthButton();
	void playAudio();

protected:
	CocosDenshion::SimpleAudioEngine* simpleAudioEngine;
	virtual bool onTouchBegan(Touch* touch, Event* event);

private:
	string word;
	MouthButton();											// Unimplemented
	MouthButton(const MouthButton& other);					// Unimplemented
	MouthButton& operator=(const MouthButton& other);		// Unimplemented

};