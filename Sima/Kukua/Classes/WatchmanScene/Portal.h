#pragma once

#include "../Utils/GameObject.h"
#include "../Utils/Data/DataProvider.h"
#include <vector>
#include <map>
#include "PortalPlay.h"
#include "SimpleAudioEngine.h"

using namespace std;


class Portal : public TouchableGameObject {

public:    
    Portal(Node& parentNode, string nodeName, string animationCsbPath, string colliderSpritePath = string(), EventDispatcher* eventDispatcher = nullptr);
	virtual ~Portal();

    void moveIn(float delay);
    cocos2d::Rect getBoundingBox();
    
    PortalPlay *playButton;
    
    void open();
    void close();
    void showInClosedState();
    void setLinkedGameIsCompleted(bool justCompleted);
    void hideGreenPortal();
    void setLinkedGame(DBGame *linkedGame);
    DBGame* getLinkedGame();
    bool semaIsOnPortal;
    
protected:
    CocosDenshion::SimpleAudioEngine* simpleAudioEngine;
    virtual bool onTouchBegan(Touch* touch, Event* event);
    
private:
	Portal();										// Unimplemented
	Portal(const Portal& other);					// Unimplemented
	Portal& operator=(const Portal& other);		// Unimplemented
    GameObject *greenPortal;
    int loopOpenSoundEffect;
    DBGame *_linkedGame;
};