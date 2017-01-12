#pragma once

#include "../Utils/Game.h"
#include "Train.h"


/* Example class, to use as a template for other Game classes. Do not modify */
class ComprehensionGame : public kukua::Game<ComprehensionGame> {

public:
	GameObject* help;
	Train* train;
	GameObject* leftBush;
	GameObject* rightBush;
	GameObject* cloud1;
	GameObject* cloud2;
	GameObject* cloud3;
	GameObject* cloud4;
	GameObject* cloud5;
    

	// implement the "static create()" method manually
	CREATE_FUNC(ComprehensionGame);

	virtual ~ComprehensionGame();

	void initVariables();
	void initAudio();
	void initGameObjects();
	void fadeIn();
	void showTutorial();
	void hideTutorial();
    void homeButtonPressed();
	bool onTouchBegan(Touch* touch, Event* event);		// Optional, needed if ExampleGame::ENABLE_TOUCH is set to true
	void onTouchMoved(Touch* touch, Event* event);		// Optional, needed if ExampleGame::ENABLE_TOUCH is set to true
	void onTouchEnded(Touch* touch, Event* event);		// Optional, needed if ExampleGame::ENABLE_TOUCH is set to true
	void endGame(bool gameOver = false);

private:
	// Private variables

};