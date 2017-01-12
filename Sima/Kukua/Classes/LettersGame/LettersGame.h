#pragma once

#include "../Utils/Game.h"
#include "../Utils/GameObject.h"



/* Example class, to use as a template for other Game classes. Do not modify */
class LettersGame : public kukua::Game<LettersGame> {

public:
	// Public variables
	
	// implement the "static create()" method manually
	CREATE_FUNC(LettersGame);

	virtual ~LettersGame();

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

	void homeButtonPressed();

private:
	// Private variables
	//CocosDenshion::SimpleAudioEngine* audio;
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
	int level;
	void changeLevel();
	void restartGame();
	void startGame();
	void showHand();
	void setPositionHand(int _i);
	void playAutomatic();
	void playLetters(string _path);
	string phoneme;

    float hiatusTimer = 30.0f;          // tempo oltre il quale parte a detrarre punteggio
    float singleInterval = 0.5f;        // intervallo di sottrazione punteggio
    float scorePercent = 100.0f;        // punteggio in % del gioco
    float unitScoreToSubtract = 1.0f;   // quanto togliere ongi singleInterval
    
    void subtractScore(float useless);  // pare che senza argomento float non si può schedulare una function
    
    
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
	void toFront(Node* _child, Node* _parent = nullptr);
	bool sortFc(GameObject* i, GameObject* j);
	void createAnimal();
	
	virtual void update(float delta);
    int typeSymbol;
    
    bool showHelp;
    bool showMiddlePhase;
    
    
    void assignLetterID(string phonemeVal);
    void populateArrayConfigLetter();
    void showInitialHelp();
    
    int phonemesToPlay;
    void reinitGameObjects();
    
    bool canPaint;
    void cleanVariables();
    void addPaint();
    cocos2d::RenderTexture* canvas;
    cocos2d::Sprite* brush;
};
