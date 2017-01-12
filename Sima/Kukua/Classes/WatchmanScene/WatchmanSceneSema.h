#pragma once

#include "../Utils/DraggableGameObject.h"
#include "Portal.h"

class WatchmanSceneSema : public DraggableGameObject {

public:
	WatchmanSceneSema(Node& parentNode, string nodeName, string csbPath, string dragSpritePath,  string colliderSpritePath, EventDispatcher* eventDispatcher);
	virtual ~WatchmanSceneSema();
    cocos2d::Rect getBoundingBox();
    
    
    bool isOnPortal;
    bool isMovingToPortal;
    void setLastPortalWasOn(Portal *portal);
    Portal* getLastPortalWasOn();
    void moveToPortal(Portal *portal);
    GameObject *semaFront;
    GameObject *semaSide;
    void jumpIntoPortal();
    void walkIn();
    void walkIn2();

protected:
	Vec2 touchOffset;
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);

private:
	static const float MAX_Y;
	bool touchValid;
	WatchmanSceneSema();												// Unimplemented
	WatchmanSceneSema(const WatchmanSceneSema& other);					// Unimplemented
	WatchmanSceneSema& operator=(const WatchmanSceneSema& other);		// Unimplemented
    Portal *portalWasOn;
    float lastX;
    
    
    
    string colliderSpritePath;
};