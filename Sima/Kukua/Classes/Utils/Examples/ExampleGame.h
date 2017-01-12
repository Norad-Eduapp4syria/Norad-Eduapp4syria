#pragma once

#include "../Game.h"


/* Example class, to use as a template for other Game classes. Do not modify */
class ExampleGame : public kukua::Game<ExampleGame> {

public:
	// Public variables

	// implement the "static create()" method manually
	CREATE_FUNC(ExampleGame);

	virtual ~ExampleGame();

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
    void homeButtonPressed(); // called when home button is pressed. Used to set parameters if leave game from home button

private:
	// Private variables
	
};