#include "PlatformGameObstacleMove.h"
#include "../Utils/StringUtility.h"





PlatformGameObstacleMove::PlatformGameObstacleMove(Node& parentNode, const Vec2& localPosition, string csbPath, string colliderSpritePath)
	: GameObject(parentNode, localPosition, csbPath, colliderSpritePath)
{
	name = "letter";
	correct = false;
}


PlatformGameObstacleMove::~PlatformGameObstacleMove() {

}


