#pragma once

#include "../Utils/GameObject.h"
#include "../Utils/TouchableGameObject.h"
#include "../Utils/Data/DBGame.h"
#include "SimpleAudioEngine.h"
#include "MapSema.h"
#include "MapPortal.h"
#include "MapEpisode.h"

using namespace CocosDenshion;

class DataProvider;

class MapScene : public cocos2d::Layer {

public:

	// Public variables
	static const bool ENABLE_TOUCH;							// Used to disable tutorial on first touch and manage general touch events
	static const string PATH;								// Resources' subfolder path for this game
																
	// implement the "static create()" method manually
	CREATE_FUNC(MapScene);

	static Scene* createScene();
	virtual ~MapScene();

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
    EventListenerCustom *moveMapEventHandler;
    EventListenerCustom *portalTouchedEventHandler;
    EventListenerCustom *portalPlayTouchedEventHandler;    
    MapSema* sema;
    MapPortal* lastTappedPortal;
    vector<MapEpisode*> episodesVector;
    MapPortal* getPortalFromPortalCode(string portalCode);
    void runSemaInitialAnimation();
    
    // for swipe - methods
    void startDetectingSwipe();
    void update(float dt);
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);
    
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
    
    void moveMapToEpisodeSingle(int episodeNum, int episodeNumToReach, float transitionTime=0.5);
    void moveMapToEpisode(int episodeNum, float transitionTime=0.5);
    int mapOnEpisodeIndex;
    int currentMapPosition;
    int startEpisode;
    MapEpisode* loadEpisode(int numEpisodeToLoad);
    int const totNumEpisodes = 9; //set to 9
    
    void printEpisodesVector();
};
