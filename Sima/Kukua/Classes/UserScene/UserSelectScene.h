#pragma once

#include "../Utils/GameObject.h"
#include "../Utils/TouchableGameObject.h"
#include "../Utils/Data/DBGame.h"
#include "SimpleAudioEngine.h"
#include "UserPhotoFrame.h"

using namespace CocosDenshion;

class DataProvider;

class UserSelectScene : public cocos2d::Layer {

public:

	// Public variables
	static const bool ENABLE_TOUCH;							// Used to disable tutorial on first touch and manage general touch events
	static const string PATH;								// Resources' subfolder path for this game
																
	// implement the "static create()" method manually
	CREATE_FUNC(UserSelectScene);

	static Scene* createScene();
	virtual ~UserSelectScene();

	bool init();
	void startGame();

	void initVariables();
	void initAudio();
	void initGameObjects();
	void fadeIn();

    
protected:
	SimpleAudioEngine* simpleAudioEngine;
	Node* rootNode;
	EventListenerTouchOneByOne* touchListener;
	vector<TouchableGameObject*> touchableGameObjects;

private:
	DataProvider* dataProvider;

    void addButtons();

    cocos2d::ui::Button *createNewBtn;
    string lastUserId;
    
    void hideAllPlayButtons();
    
    vector<UserPhotoFrame*> framesVector;
    EventListenerCustom *frameTouchedListener;
    
    
    // for swipe - methods
    void startDetectingSwipe();
    void update(float dt);
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);
    
    Vec2 getFramePosition(int index);
    
    Node* scrollContainer;
    
    // for swipe - variables
    bool isTouchDown;
    bool canSwipe;
    float gameTime;
    bool hasTocalculateTime;
    float initialTouchPos[2];
    float currentTouchPos[2];
    cocos2d::Size visibleSize;
    float startX;
    float startY;
    
    bool moveLeftGestureDone;
    bool moveRightGestureDone;
    int scrollIndex;
    
    vector<string> idsVector;
    void loadPhotoFramesForPage(int pageNum);
    void deletePhotoFramesForPage(int pageNum);
    
    //bool test = true;
    int previousPageElementsCounter;
    int currentPageElementsCounter;
    int totPages;
};
