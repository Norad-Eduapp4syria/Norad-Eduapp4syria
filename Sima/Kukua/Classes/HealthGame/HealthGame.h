#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"


using namespace CocosDenshion;

class DataProvider;

class HealthGame : public cocos2d::Layer {

public:

	// Public variables
	static const bool ENABLE_TOUCH;							// Used to disable tutorial on first touch and manage general touch events
	static const std::string PATH;								// Resources' subfolder path for this game
																
	// implement the "static create()" method manually
	CREATE_FUNC(HealthGame);

	static cocos2d::Scene* createScene();
	virtual ~HealthGame();

	bool init();
	void startGame();

	void initVariables();
	void initAudio();
	void initGameObjects();
	void fadeIn();

    
protected:
	SimpleAudioEngine* simpleAudioEngine;
	Node* rootNode;

private:
	DataProvider* dataProvider;
    void addBackToHomeButton();
    Node *slideNode;
    std::string getSlideNum();
    void closeGame();
    void playAudioInstructions();
};
