#pragma once

#include "../Utils/GameObject.h"
#include "../Utils/TouchableGameObject.h"
#include "../Utils/Data/DataProvider.h"
#include <vector>
#include <map>
class WatchmanScene;

using namespace std;


class WatchmanSceneGrandpa : public GameObject {

public:
	WatchmanSceneGrandpa(Node& parentNode, const Vec2& localPosition, EventDispatcher* eventDispatcher, WatchmanScene* watchmanScene, int skin, string csbPath);
	virtual ~WatchmanSceneGrandpa();
    
    void playGoodReaction();
    void playBadReaction();

private:
	WatchmanSceneGrandpa();										// Unimplemented
	WatchmanSceneGrandpa(const WatchmanSceneGrandpa& other);					// Unimplemented
	WatchmanSceneGrandpa& operator=(const WatchmanSceneGrandpa& other);		// Unimplemented
    
    CocosDenshion::SimpleAudioEngine* simpleAudioEngine;
};