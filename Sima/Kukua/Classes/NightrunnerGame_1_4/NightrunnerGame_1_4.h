#pragma once

#include "../Utils/GameObject.h"
#include "SimpleAudioEngine.h"
#include "NR_Ball.h"
#include "NR_Counter.h"

using namespace CocosDenshion;

class DataProvider;

class NightrunnerGame_1_4 : public cocos2d::Layer {

public:

	// Public variables
	static const bool ENABLE_TOUCH;							// Used to disable tutorial on first touch and manage general touch events
	static const std::string PATH;								// Resources' subfolder path for this game
																
	// implement the "static create()" method manually
	CREATE_FUNC(NightrunnerGame_1_4);

	static cocos2d::Scene* createScene();
	virtual ~NightrunnerGame_1_4();

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
    NR_Ball* ball1;
    NR_Ball* ball2;
    NR_Ball* ball3;
    EventListenerCustom *touchBallEventHandler;
    EventListenerCustom *timeFinishedHandler;
    void handleBallTouched(string ballTouchedNum);
    string correctBallNum;
    GameObject* bossPos;
    GameObject* bossNeg;
    NR_Counter* counter;
    void startMatch();
    void updateScore();
    int score;
    int wrongAnserCounter;
    void handleFinishTime();
    string addRandomSuffixEp2(string phoneme);
    int currentEpisode;
    string getCompleteWord(string word);
};
