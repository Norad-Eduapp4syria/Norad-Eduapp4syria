#pragma once

#include "../Utils/GameObject.h"
#include "../Utils/TouchableGameObject.h"
#include "../Utils/Data/DataProvider.h"
#include <vector>
#include <map>
#include "MapPortal.h"
#include "MapEpisode.h"
//#include "MapScene.h"

using namespace std;


class MapSema : public GameObject {

public:
	MapSema(Node& parentNode, const Vec2& localPosition, string csbPath, EventDispatcher* eventDispatcher, vector<MapEpisode*>* episodesVector);
	virtual ~MapSema();
    
    void jumpToPortal(MapPortal* portal);
    void jumpToPortalTestFast(MapPortal* portal);
    void placeOnPortal(MapPortal* portal);
    void comeOutFromPortal();
    string portalCodeOn;
    
private:
	DataProvider* dataProvider;
	MapSema();										// Unimplemented
	MapSema(const MapSema& other);					// Unimplemented
	MapSema& operator=(const MapSema& other);		// Unimplemented
    CocosDenshion::SimpleAudioEngine* simpleAudioEngine;
    EventDispatcher* eventDispatcher;
    
    vector<string> passagesVector;
    //vector<MapPortal*> portalPassagesVector;
    void jump();
    
    Vec2 getPortalPosition(string portalCode);
    
    MapPortal* getPortalFromPortalCode(string portalCode);
    vector<MapEpisode*>* episodesVectorRef;
    bool isJumping;
    
    void moveCameraToEpisode(int episodeNum);
};