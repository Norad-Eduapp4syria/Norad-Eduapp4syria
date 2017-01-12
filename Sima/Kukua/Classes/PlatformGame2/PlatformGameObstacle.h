#pragma once


#include "../Utils/GameObject.h"
#include <vector>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"


using namespace std;


class PlatformGameObstacle : public Node {

public:
	PlatformGameObstacle(string pngPath);	// For nodes to be instantiated from a csb or new nodes
	virtual ~PlatformGameObstacle();

	Sprite* sprite;
	string name;
	bool correct;
protected:

private:


};