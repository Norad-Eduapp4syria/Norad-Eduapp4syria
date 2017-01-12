#pragma once
/*
#include "../Utils/GameObject.h"
#include "../Utils/TouchableGameObject.h"
*/
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "../Utils/GameObject.h"

using namespace CocosDenshion;

class DataProvider;

class SocialWeal : public cocos2d::Layer {

public:

	// Public variables
	static const bool ENABLE_TOUCH;							// Used to disable tutorial on first touch and manage general touch events
	static const std::string PATH;								// Resources' subfolder path for this game

	// implement the "static create()" method manually
	CREATE_FUNC(SocialWeal);

	static cocos2d::Scene* createScene();
	virtual ~SocialWeal();

	bool init();
	void startGame();
	

	void initVariables();
	void initAudio();
	void initGameObjects();
	void fadeIn();


	void createButton(int _id);
	void createAnimation(int _character, int _id);
	void activeClickCharacter();
	void clickCharacter(int _id);
	void clickButton(int _id);
	void stopTalk();
	void activeNext();
	void clickNext();

	Node* bgNode;
	Node* samirNode;
	Node* simaNode;

	Node* button1Node;
	Node* button2Node;
	Node* button3Node;
	Node* button4Node;
	Node* button5Node;
	Node* button6Node;

	GameObject* samir;
	GameObject* sima;

	GameObject* hand;
	GameObject* emotes;

	GameObject* next;

	vector < GameObject* > arrayButton;
	vector < float > timeAudioIntro;
	vector < float > timeAudioSima;
	vector < float > timeAudioSamir;
	bool firstClick;
	bool activeClick;
	bool activedNext;
	int selected;
	int inTalk;
    
    int SKIN;

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

protected:
	CocosDenshion::SimpleAudioEngine *audioEngine;
	Node* rootNode;

private:

	
    void addBackToMapButton();

	void closeGame();
};
