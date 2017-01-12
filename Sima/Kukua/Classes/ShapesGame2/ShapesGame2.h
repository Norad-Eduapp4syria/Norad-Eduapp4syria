#pragma once

#include "../Utils/Game.h"
#include "../Utils/GameObject.h"
#include "../Utils/TouchableGameObject.h"
#include "SimpleAudioEngine.h"
#include "Bug.h"



/* Example class, to use as a template for other Game classes. Do not modify */
class ShapesGame2 : public kukua::Game<ShapesGame2> {

public:
	// Public variables
	
	// implement the "static create()" method manually
	CREATE_FUNC(ShapesGame2);

	virtual ~ShapesGame2();

	void initVariables();
	void initAudio();
	void initGameObjects();
	void fadeIn();
	void showTutorial();
	void hideTutorial();
	bool onTouchBegan(Touch* touch, Event* event);		// Optional, needed if ExampleGame::ENABLE_TOUCH is set to true
	void onTouchMoved(Touch* touch, Event* event);		// Optional, needed if ExampleGame::ENABLE_TOUCH is set to true
	void onTouchEnded(Touch* touch, Event* event);		// Optional, needed if ExampleGame::ENABLE_TOUCH is set to true
	void endGame(bool gameOver = false);
	void gotoPauseOut();
	
	int validSimbol;
	bool gameFinished;
	bool gamePaused;

	void homeButtonPressed();

private:
	// Private variables
    
	bool test;


	vector < Bug* > arrayBug;
    vector < Bug* > arrayBugToDelete;
	vector < GameObject* > arrayCounter;

	GameObject* help;
	GameObject* tatu;
	GameObject* tree;
	GameObject* leafs;
	GameObject* form;

	GameObject* semaTry;
	GameObject* semaWell;

	GameObject* formCounter1;
	GameObject* formCounter2;
	GameObject* formCounter3;
	GameObject* formCounter4;
	GameObject* formCounter5;

	
	EventListenerCustom *clickBug;
	EventListenerCustom *deleteBug;

	void startAnimStartGame();
	void createBug();
	void openLeafs();
	void closeLeafs();
	void finishGame(bool _win);
	void touchBugOK();
	void touchBugKO();
	void returnTongue(bool _correctBug, Bug* _target);

    float scorePercent = 100.0f;
    float scoreToSubtract = 25.0f;

	int nLedOn;
	
    void closeGame(bool isWinning);
}; 
