#pragma once


#include "../Utils/GameObject.h"
#include <vector>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"


using namespace std;


class PlatformGameObstacleMove : public GameObject {

public:
	PlatformGameObstacleMove(Node& parentNode, const Vec2& localPosition, string csbPath = string(), string colliderSpritePath = string());
	virtual ~PlatformGameObstacleMove();

	string name;
	bool correct;
protected:

private:


};