#pragma once


#include "../Utils/TouchableGameObject.h"
#include <vector>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"


using namespace std;


class Bug : public TouchableGameObject {

public:
	Bug(Node& _parentNode, const Vec2& _localPosition, string _csbPath, int _typeBug, EventDispatcher* _eventDispatcher);	// For nodes to be instantiated from a csb or new nodes
	virtual ~Bug();

	GameObject* shadow;
	void destroy();
	void flyOutCall();
	void flyOut();
	bool clicked;
	string name;
	int typeBug;
	int status; //1=entry 2=stand 3=exit
protected:
	
	virtual bool onTouchBegan(Touch* touch, Event* event);

private:
	CocosDenshion::SimpleAudioEngine *audioEngine;

	Vec2 localPosition;
	EventDispatcher* eventDispatcher;
	
	

	void flyIn();
	
	void stop();
	void scaleMore();
	void scaleLess();

	
	float angleIn;
	float angleOut;

	void update();

};