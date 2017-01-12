#pragma once

#include "../Utils/GameObject.h"
#include "../Utils/Data/DataProvider.h"
#include "MapPortal.h"
#include "MapProp.h"
#include <vector>
#include <map>
using namespace std;


class MapEpisode : public GameObject {

public:
	MapEpisode(Node& parentNode, const Vec2& localPosition, string csbPath, int episodeNum, int lastUnlockedPortalNum, EventDispatcher* eventDispatcher);
	virtual ~MapEpisode();
    MapPortal* getPortal(int numPortal);
    int getPortalsVectorSize();
    int episodeNum;
private:
	DataProvider* dataProvider;
	MapEpisode();										// Unimplemented
	MapEpisode(const MapEpisode& other);					// Unimplemented
	MapEpisode& operator=(const MapEpisode& other);		// Unimplemented
    CocosDenshion::SimpleAudioEngine* simpleAudioEngine;
    EventDispatcher* eventDispatcher;
    void addPortals(int lastUnlockedPortalNum);
    
    vector<MapPortal*> portalsVector;
    int getNumPortals(int episodeNum);
    GameObject* house;
    void addHouse();
    void addProps();
    void addProp(string name, string csbName, bool flip = false);
    vector<MapProp*> propsVector;
};
