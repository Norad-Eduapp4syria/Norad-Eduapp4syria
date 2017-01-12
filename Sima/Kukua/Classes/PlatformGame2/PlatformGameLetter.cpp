#include "PlatformGameLetter.h"
#include "../Utils/StringUtility.h"



PlatformGameLetter::PlatformGameLetter(Node& parentNode, string nodeName, string animationCsbPath, string colliderSpritePath)
	: GameObject(parentNode, nodeName, animationCsbPath, colliderSpritePath)
{
	name = "letter";
	correct = false;
	took = false;
}

PlatformGameLetter::PlatformGameLetter(Node& parentNode, const Vec2& localPosition, string csbPath, string colliderSpritePath)
	: GameObject(parentNode, localPosition, csbPath, colliderSpritePath)
{
	name = "letter";
	correct = false;
	took = false;
}

PlatformGameLetter::~PlatformGameLetter() {
}


