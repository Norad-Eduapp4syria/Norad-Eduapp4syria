#pragma once


#include "KeyboardButton.h"
#include <vector>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include <string>
#include <locale> 

using namespace std;
using namespace cocos2d;
using namespace cocostudio::timeline;


class Keyboard{

public:
	Keyboard(Node& _parentNode, const Vec2& _localPosition, bool __lowercase, EventDispatcher* eventDispatcher);
	virtual ~Keyboard();

	bool isOpen = false;

	Node* node;
	ActionTimeline* actionTimeline;

	void play(string animationName, std::function<void()> callback = nullptr, bool looping = false, float delay = 0.f, int startFrameOffset = 0);
	void play(Action* action);

	int type;
protected:
	
//	virtual bool onTouchBegan(Touch* touch, Event* event);

private:
	CocosDenshion::SimpleAudioEngine *audioEngine;

    vector<KeyboardButton*> keyboardButtonsVec;
	
	//EventDispatcher* eventDispatcher;
	


};
