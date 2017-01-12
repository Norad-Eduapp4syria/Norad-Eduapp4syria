#pragma once

#include "../Utils/GameObject.h"
#include "../Utils/TouchableGameObject.h"
#include "../Utils/Data/DBGame.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

class DataProvider;

class TunnelLoop : public cocos2d::Layer {

public:
    static cocos2d::Scene* (*NEXT_SCENE_CREATE_SCENE)();
	// Public variables
	static const bool ENABLE_TOUCH;							// Used to disable tutorial on first touch and manage general touch events
	static const string PATH;								// Resources' subfolder path for this game
																
	// implement the "static create()" method manually
	CREATE_FUNC(TunnelLoop);

	static Scene* createScene();
	virtual ~TunnelLoop();

	bool init();
	void startGame();

	void initVariables();
	void initAudio();
	void initGameObjects();
	void fadeIn();


protected:
	SimpleAudioEngine* simpleAudioEngine;
	Node* rootNode;
	EventListenerTouchOneByOne* touchListener;
	vector<TouchableGameObject*> touchableGameObjects;

private:
	DataProvider* dataProvider;

	void closePage();

	GameObject* sema;
    GameObject* bg;

};