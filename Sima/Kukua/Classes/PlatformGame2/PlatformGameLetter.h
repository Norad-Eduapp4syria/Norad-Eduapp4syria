#pragma once


#include "../Utils/GameObject.h"
#include <vector>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"


using namespace std;


class PlatformGameLetter : public GameObject {

public:
	PlatformGameLetter(Node& parentNode, const Vec2& localPosition, string csbPath = string(), string colliderSpritePath = string());
	PlatformGameLetter(Node& parentNode, string nodeName, string animationCsbPath, string colliderSpritePath = string());	// For nodes to be instantiated from a csb or new nodes
	virtual ~PlatformGameLetter();

	string name;
	bool took;
	bool correct;
protected:

private:


};