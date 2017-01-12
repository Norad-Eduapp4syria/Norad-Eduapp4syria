#pragma once

#include "../Utils/GameObject.h"
#include "../Utils/TouchableGameObject.h"
#include "../Utils/Data/DBGame.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

class DataProvider;

class UserCreateScene : public cocos2d::Layer {

public:

	// Public variables
	static const bool ENABLE_TOUCH;							// Used to disable tutorial on first touch and manage general touch events
	static const string PATH;								// Resources' subfolder path for this game
																
	// implement the "static create()" method manually
	CREATE_FUNC(UserCreateScene);

	static Scene* createScene();
	virtual ~UserCreateScene();

	bool init();
	void startGame();

	void initVariables();
	void initAudio();
	void initGameObjects();
	void fadeIn();

    //void captureCallback(cocos2d::Ref* pSender);
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
    void afterCaptured(bool succeed, const std::string& outputFile);

    cocos2d::ui::Button *shootBtn1;
    cocos2d::ui::Button *shootBtn2;
    cocos2d::ui::Button *goOnBtn;
    string photoPath;
    string generateId();
    string currentId;
    bool disableClicks;
};