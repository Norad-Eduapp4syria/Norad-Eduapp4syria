#pragma once

#include "../Utils/GameObject.h"
#include "../Utils/TouchableGameObject.h"
#include "../Utils/Data/DBGame.h"
#include "SimpleAudioEngine.h"
#include "PhotoCharacter.h"

using namespace CocosDenshion;

class DataProvider;

class PhotoScene : public cocos2d::Layer {

public:

	// Public variables
	static const bool ENABLE_TOUCH;							// Used to disable tutorial on first touch and manage general touch events
	static const string PATH;								// Resources' subfolder path for this game
																
	// implement the "static create()" method manually
	CREATE_FUNC(PhotoScene);

	static Scene* createScene();
	virtual ~PhotoScene();

	bool init();
	void startGame();

	void initVariables();
	void initAudio();
	void initGameObjects();
	void fadeIn();

    void captureCallback(cocos2d::Ref* pSender);
    void openCamera();
    void cameraResponse(bool isError, std::string imagePath);
    
    
protected:
	SimpleAudioEngine* simpleAudioEngine;
	Node* rootNode;
	EventListenerTouchOneByOne* touchListener;
	vector<TouchableGameObject*> touchableGameObjects;

private:
	DataProvider* dataProvider;

    void addButtons();
    void addHomeButton();
    void afterCaptured(bool succeed, const std::string& outputFile);
    void addCharacters();
    void runConfirmAnimation();
    PhotoCharacter* character1;
    PhotoCharacter* character2;
    PhotoCharacter* character3;
    PhotoCharacter* character4;
    Node *confirmNode;
    Node *handPhoto;
    Node *handDrag;
    cocos2d::ui::Button *char1Btn;
    cocos2d::ui::Button *char2Btn;
    cocos2d::ui::Button *char3Btn;
    cocos2d::ui::Button *char4Btn;
    cocos2d::ui::Button *backBtn;
    cocos2d::ui::Button *shootBtn;
    cocos2d::ui::Button *saveBtn;
    void setUIVisibility(bool visibility);
};