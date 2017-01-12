#pragma once

#include "../Utils/Game.h"
#include "../Utils/GameObject.h"
#include "../Utils/TouchableGameObject.h"
#include "SimpleAudioEngine.h"
#include "../Utils/Keyboard/Keyboard.h"



/* Example class, to use as a template for other Game classes. Do not modify */
class SentenceDictation : public kukua::Game<SentenceDictation> {

public:
	// Public variables
	
	// implement the "static create()" method manually
	CREATE_FUNC(SentenceDictation);
   
    static std::string NAME;
	virtual ~SentenceDictation();

	void initVariables();
	void initAudio();
	void initGameObjects();
	void fadeIn();
	void showTutorial();
	void hideTutorial();
	bool onTouchBegan(Touch* touch, Event* event);		// Optional, needed if ExampleGame::ENABLE_TOUCH is set to true
	void onTouchMoved(Touch* touch, Event* event);		// Optional, needed if ExampleGame::ENABLE_TOUCH is set to true
	void onTouchEnded(Touch* touch, Event* event);		// Optional, needed if ExampleGame::ENABLE_TOUCH is set to true
	
	EventListenerCustom *clickButton;
	void homeButtonPressed();

	bool lowercase;

private:
	// Private variables
	//CocosDenshion::SimpleAudioEngine* audio;

	
	GameObject* tatu;
	void toFront(Node* _child, Node* _parent);

    int line;
    int spaceCounter;

	//PART 1
	vector < GameObject* > arrayCharBox;
	GameObject* leterBox;
	GameObject* backGround;
	Keyboard* keyboard;
	// string word;
    vector<string> wordArray;

	int charActive;
    // int remWidthRef;
    int xPosIndex;
    
	bool inPauseInsert;
	bool test;

	void createWord();
	void createChar(int _id, string _char);
	void setChar(int _id, string _char);
	void checkChar();
	void startGame();
	void selectBox(int _id);
	void finishFase1();

	//PART 2

	string pathLetters;


	int typeSymbol;

	GameObject* letter;
	GameObject* hand;
	GameObject* point;
	GameObject* marker;
	GameObject* help;
	GameObject* handTutorial;
	int step;
	int actualStep;
	int actualShape;
	int stateInteraction; // 0=ready 1=progress 2=cancellation 3=changestep or finish
	int letterID;
	int progreLetter;
	void changeLevel();
	void restartGame();
	void showHand();
	void setPositionHand(int _i);
	void playAutomatic();
	void playLetters(string _path);
	string phoneme;

	
	void finisGame();

    bool useCapitalLetters;

    void addListenButton();
    void playAudioWord();
    
    float score;
    
	CocosDenshion::SimpleAudioEngine *audioEngine;

	virtual void update(float delta);
    
    string wordToRead;

}; 
