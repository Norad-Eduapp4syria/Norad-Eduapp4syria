#pragma once

#include "../Utils/Game.h"
#include "../Utils/GameObject.h"
#include "../Utils/TouchableGameObject.h"
#include "SimpleAudioEngine.h"
#include "../Utils/Keyboard/Keyboard.h"



/* Example class, to use as a template for other Game classes. Do not modify */
class WordDictation : public kukua::Game<WordDictation> {

public:
	// Public variables
	
	// implement the "static create()" method manually
	CREATE_FUNC(WordDictation);
   
    static std::string NAME;
	virtual ~WordDictation();

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
	
	GameObject* tatu;
	void toFront(Node* _child, Node* _parent);


	//PART 1
	vector < GameObject* > arrayCharBox;
	GameObject* wordBox;
	GameObject* leterBox;
	GameObject* backGround;
	Keyboard* keyboard;
	//string word;
    vector<string> wordArray;

	int charActive;
	int remainingWidth;
	bool inPauseInsert;
	bool test;

	void createWord();
	void createChar(int _id, string _char);
	void setChar(int _id, string _char);
	void checkChar();
	void startGame();
	void selectBox(int _id);
	void finishFase1();
	void playGameLetter();
	void replayDesk();

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


	vector< vector< vector< int > > > arrayConfigLetter;
	vector < GameObject* > arrayMarker;
	vector < GameObject* > arrayPoint;
	vector < GameObject* > arrayAllShape;
	vector < GameObject* > arrayAnt;
	vector < int > arrayAntRotation;
	vector < float > arrayAntVelocity;
	void setObjectStep();
	void regressPoint();
	void flyPoint();
	void playStartMarker(int _i, int _m);
	void playStartPoint(int _i);
	bool sortFc(GameObject* i, GameObject* j);
	void createAnt();
	void selectLetter();
	void createLetterGame();
	void finisGame();

    bool useCapitalLetters;
    
    void addListenButton();
    void playAudioWord();
    
    float score;
    
    string wordInArabic;
    
	virtual void update(float delta);
    string englishImageName;

}; 
