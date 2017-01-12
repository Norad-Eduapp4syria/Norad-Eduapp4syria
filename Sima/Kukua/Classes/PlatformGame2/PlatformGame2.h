#pragma once

#include "../Utils/Game.h"
#include "../Utils/GameObject.h"
#include "PlatformGameLetter.h"
#include "PlatformGameSema.h"
#include "PlatformGameObstacle.h"
#include "PlatformGameObstacleMove.h"
#include "../Utils/TouchableGameObject.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "GUI/CCScrollView/CCScrollView.h"

/* Example class, to use as a template for other Game classes. Do not modify */
class PlatformGame2 : public kukua::Game<PlatformGame2> {
	

public:
	// Public variables
	
	// implement the "static create()" method manually
	CREATE_FUNC(PlatformGame2);

	virtual ~PlatformGame2();

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
	// Private variables
	//CocosDenshion::SimpleAudioEngine* audio;
	bool test;

	void toFront(Sprite* _child);
	void toFront(Node* _child);

	CocosDenshion::SimpleAudioEngine *audioEngine;

	virtual void update(float delta);

	float scorePercent = 100.0f;

	void createBg(int _type, bool _first);
	void jumpStart();
	void jumpFinish();
	void flyStart();
	void flyFinish();
	void setBar(int _val);
	void createLetter(bool _inRainbow = false, float _x = NULL);
	void createPotion();
	void createSpeed();
	void createRainbow();
	void closeGame();
	bool colliderWithSema(float _x, float _y, float _radiusX, float _radiusY);
	void playAudioHelp();

	void createObstacle();
	void loseLife();
	void endGame(bool _win);

	Sprite* buttonTunnel;

	float levelDelayFactor;
	int middleY;
	int potionCount;
	int level;
	bool isFinishStandBy;
	bool isFinish;
	bool isStoped;
	bool inJump;
	bool inFly;
	bool inPotion;
	bool slideEnabled;
	bool inSlide;
	int whereGoingY;
	int ySemaOrigin;
	int energy;
	float velocity;
	int lifes;
	bool invincible;
	int audio1;
	bool inCrack;

	vector < Sprite* > arrayBg1;
	vector < Sprite* > arrayBg2;
	vector < PlatformGameLetter* > arrayLetters;
	vector < PlatformGameObstacle* > arrayObstacle;
	vector < PlatformGameObstacleMove* > arrayObstacleMove;
	vector < Sprite* > arrayRainbow;

	int oldValBar;
	vector < GameObject* > arrayBar;
	GameObject* help;
	GameObject* life1;
	GameObject* life2;
	GameObject* life3;
	GameObject* sema;
	GameObject* sema_positive;
	GameObject* sema_negative;
	GameObject* slider;
	GameObject* scoreBar;
	Node* backGround;
	Node* secondPlane;
	Node* firstPlane;
	Node* letters;
	Node* player;
	PlatformGameLetter* potion;
	Node* obstacle;
	Node* rainbow;
	string letterOk;
	string letterKo;

	vector<Sprite*> semaSprites;
	void collectSpritesInHierarchy(Node* node, vector<Sprite*>& spriteVector);

	float deltaTime;
	
	//GameObject* button3;

}; 