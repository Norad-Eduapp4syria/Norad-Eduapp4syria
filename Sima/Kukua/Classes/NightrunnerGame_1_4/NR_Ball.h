#pragma once
#include "../Utils/TouchableGameObject.h"
#include "SimpleAudioEngine.h"


class NR_Ball : public TouchableGameObject {

public:
	NR_Ball(Node& parentNode, string nodeName, EventDispatcher* eventDispatcher, string ballNumber);
	virtual ~NR_Ball();
	void playAudio();
    string numBall;
    void setValue(string value, int epispdeNum);
    Label*  label;

protected:
	CocosDenshion::SimpleAudioEngine* simpleAudioEngine;
	virtual bool onTouchBegan(Touch* touch, Event* event);

private:
	NR_Ball();										// Unimplemented
	NR_Ball(const NR_Ball& other);					// Unimplemented
	NR_Ball& operator=(const NR_Ball& other);		// Unimplemented
    
};
