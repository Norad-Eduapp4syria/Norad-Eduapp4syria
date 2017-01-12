#pragma once

#include "../Utils/Game.h"
#include "../Utils/GameObject.h"
#include "../Utils/TouchableGameObject.h"
#include "SimpleAudioEngine.h"
#include "../Utils/Keyboard/Keyboard.h"
#include "cocos2d.h"
#include "GUI/CCScrollView/CCScrollView.h"
#include "OPTextProvider.h"

/* Example class, to use as a template for other Game classes. Do not modify */
class OralPassage : public kukua::Game<OralPassage> {
	

public:
	// Public variables
	
	// implement the "static create()" method manually
	CREATE_FUNC(OralPassage);

	virtual ~OralPassage();

	void initVariables();
	void initAudio();
	void initGameObjects();
	void fadeIn();
	void showTutorial();
	void hideTutorial();
	bool onTouchBegan(Touch* touch, Event* event);		// Optional, needed if ExampleGame::ENABLE_TOUCH is set to true
	void onTouchMoved(Touch* touch, Event* event);		// Optional, needed if ExampleGame::ENABLE_TOUCH is set to true
	void onTouchEnded(Touch* touch, Event* event);		// Optional, needed if ExampleGame::ENABLE_TOUCH is set to true
	
	void homeButtonPressed();

	


private:
	    
    OPTextProvider *textProvider;

	CocosDenshion::SimpleAudioEngine *audioEngine;

	virtual void update(float delta);


	void openText();
	void closeText();
	void openQuest();
	void closeQuest(bool _new);
	void initText();
	void climbUp();
	void fall();
	void stopSema();
	void loseLife();
	void checkResult(int _id);

	void finishGame(bool _win);

	int questCorrect;
	int lifes;
	int quest;
	bool helpIsOpen;
	float velocityButterfly;
	float rotationButterfly;
	bool clikEnabled;
		
	vector<string> orderAns;

	string textAnswer1;
    
    float scorePercent;
    float scoreToSubtract;

	GameObject* help;
	GameObject* story;
	GameObject* sema;
	GameObject* tree;
	GameObject* questPanel;
	GameObject* tryagain;
	GameObject* welldone;
	GameObject* butterfly;
	GameObject* hand;
	GameObject* life1;
	GameObject* life2;
	GameObject* life3;

	GameObject* button1;
	GameObject* button2;
	GameObject* button3;

    EventListenerTouchOneByOne* touchListener;
    
    void closeGame(bool goodEnd);
    
    Label *longTextLabel;
    Label *questLabel;
    Label *answer1Label;
    Label *answer2Label;
    Label *answer3Label;
}; 
