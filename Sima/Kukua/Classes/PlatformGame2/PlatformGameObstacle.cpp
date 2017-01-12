#include "PlatformGameObstacle.h"
#include "../Utils/StringUtility.h"





PlatformGameObstacle::PlatformGameObstacle(string pngPath)
{
	sprite = Sprite::create(pngPath);
	this->addChild(sprite);
	name = "letter";
	correct = false;
}

PlatformGameObstacle::~PlatformGameObstacle() {

}


