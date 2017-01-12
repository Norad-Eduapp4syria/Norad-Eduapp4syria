
#pragma once

#include "../Utils/GameObject.h"
#include "../Utils/TouchableGameObject.h"
//#include "../Utils/DraggableGameObject.h"
#include "../Utils/Data/DataProvider.h"
#include "SimpleAudioEngine.h"
#include "KnowledgeBubble.h"
#include "WatchmanSceneSema.h"
#include "Inventory.h"
#include "Portal.h"
#include "WatchmanSceneGrandpa.h"
#include "WatchmanSceneStateCalculator.h"

class InventoryButton;
class WatchmanSceneStateCalculator;

using namespace CocosDenshion;



class WatchmanScene : public cocos2d::Layer {

public:
	// Public variables
	static const bool ENABLE_TOUCH;							// Used to disable tutorial on first touch and manage general touch events
	static const string PATH;								// Resources' subfolder path for this game

	// implement the "static create()" method manually
	CREATE_FUNC(WatchmanScene);

	static Scene* createScene();
	virtual ~WatchmanScene();

	bool init();
	void startGame();

	void initVariables();
	void initAudio();
	void initGameObjects();
	void fadeIn();
	//void showTutorial();
	//void hideTutorial();
	void enableTouch();
	void disableTouch();
	bool onTouchBegan(Touch* touch, Event* event);		// Optional, needed if ExampleGame::ENABLE_TOUCH is set to true
	void onTouchMoved(Touch* touch, Event* event);		// Optional, needed if ExampleGame::ENABLE_TOUCH is set to true
	void onTouchEnded(Touch* touch, Event* event);		// Optional, needed if ExampleGame::ENABLE_TOUCH is set to true
	//void endGame(bool gameOver = false);				// Unused
	void endGame(string gameName);
	void update(float deltaTime);
    void openGame();
    
    string state;
    bool newPhonemeDiscovered;
    bool mustShowNightRunnerScene;
        
    static bool NIGHTRUNNER_ACTIVE;
    static int NIGHTRUNNER_HEARTS;
    static const string FIRST_TIME;
    static const string SHOW_1_PORTAL;
    static const string SHOW_2_PORTALS;
    static const string SHOW_3_PORTALS;
    
    static const string NONE_REACTION;
    static const string GOOD_REACTION;
    static const string BAD_REACTION;

protected:
	SimpleAudioEngine* simpleAudioEngine;
	Node* rootNode;
	EventListenerTouchOneByOne* touchListener;
	vector<TouchableGameObject*> touchableGameObjects;

private:
	bool touching;
	DataProvider* dataProvider;
	vector<DBKnowledgeBubble*> dbKnowledgeBubbles_forKB;
    vector<DBKnowledgeBubble*> dbUnlockedKnowledgeBubbles;
    vector<DBGame*> vectorGamesPortals;
    vector<DBGame*> vectorGamesState;
    WatchmanSceneSema* sema;
    map<string, vector<DBGame*>> dbGames_forKB;
	vector<KnowledgeBubble*> knowledgeBubbles;
	Portal* portal1;
	Portal* portal2;
	Portal* portal3;
    WatchmanSceneGrandpa *watchmanObj;
	Inventory* inventory;
	InventoryButton* inventoryButton;
    EventListenerCustom *listenerPlayButtonClicked;
    EventListenerCustom *moveSemaOnPortalEventHandler;
    GameObject *help;
    WatchmanSceneStateCalculator *stateCalculator;
    int step;
    
    void handleSemaMovesOutPortal(Portal* portal);
    void handleSemaIntersectsPortal(Portal* portal);
    void showNewLetterHelp();
    void showNewNumberHelp();
    void setKnowledgeBubbles();
    void showNewPhoneme_doNextStep();
    void setPortals();
    void showNightRunnerScene();
    void openGameDirectly(string phonemeOfGame);

	void addHomeButton();
    
    LabelGameObject *letterHelp;
    
    int skin;
    
    bool mustShowHelpNewNumber;

    // night runner
    GameObject *nightrunnerObj;
    void setNightRunnerHearts();
    GameObject *heart1;
    GameObject *heart2;
    GameObject *heart3;
    GameObject *heart4;
    GameObject *heart5;
    void showNightRunnerFinalAnimation();
    cocos2d::Sprite* spotLight;
    
    void showPortals();
    void backToMapFromHomeButton();
    Vec2 getBubblePosition(int bubbleNum, int totBubblesNum);
};
