#pragma once

#include "../Utils/GameObject.h"
#include "../Utils/Data/DataProvider.h"
#include <vector>
#include <map>
#include "MapPortalPlay.h"
#include "SimpleAudioEngine.h"

using namespace std;


class MapPortal : public TouchableGameObject {

public:    
    MapPortal(Node& parentNode, Vec2 localPosition, string animationCsbPath, string colliderSpritePath = string(), EventDispatcher* eventDispatcher = nullptr, string typePortal = "normal", string state = "locked", int episodeNum=0, int watchmanNum=0);
	virtual ~MapPortal();

    MapPortalPlay *playButton;
    void showPlayButton();
    void hidePlayButton();
    string getPortalCode();
    bool isVideo();
    bool isNightrunner();
    void setStatus(string status);
    
protected:
    CocosDenshion::SimpleAudioEngine* simpleAudioEngine;
    virtual bool onTouchBegan(Touch* touch, Event* event);
    
private:
	MapPortal();										// Unimplemented
	MapPortal(const MapPortal& other);					// Unimplemented
	MapPortal& operator=(const MapPortal& other);		// Unimplemented
    string state;
    string portalCode;
    Sprite* lockIcon;
    string typePortal;
    GameObject* nightrunnerMask;
};