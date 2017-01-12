#pragma once

#include "../Utils/Game.h"
#include "Body.h"
#include "../Utils/Data/DataProvider.h"

/* Example class, to use as a template for other Game classes. Do not modify */
class Bodyparts : public kukua::Game<Bodyparts> {

public:

    Body* body;
    GameObject* board;
    string bodyPartToTap;
    
    // implement the "static create()" method manually
	CREATE_FUNC(Bodyparts);

	virtual ~Bodyparts();

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
    DataProvider *dataProvider;
    EventListenerCustom *bodyPartTouchedEventHandler;
    void endRound(bool positiveEnd);
    void startNewRound();
    string getRandomBodyPart();
    bool isCorrectMatch(string touchName);
    vector<string> bodyPartsToTapVector;
    Label*  boardTextUi2;
    
    float scorePercent = 100.0f;
    float scoreToSubtract = 25.0f;
};
