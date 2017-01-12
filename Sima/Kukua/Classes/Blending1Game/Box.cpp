#include "Box.h"


Box::Box(Node& parentNode, string nodeName, string animationCsbPath, string colliderSpritePath, bool dynamic, bool gravityEnabled, EventDispatcher* eventDispatcher, unsigned int contactTestBitmask)
	: PhysicsGameObject(parentNode, nodeName, animationCsbPath, colliderSpritePath, dynamic, gravityEnabled, eventDispatcher, contactTestBitmask)
{

	setScale(0.8f);

}

Box::Box(Node& parentNode, const Vec2& localPosition, string animationCsbPath, string colliderSpritePath, bool dynamic, bool gravityEnabled, EventDispatcher* eventDispatcher, unsigned int contactTestBitmask)
	: PhysicsGameObject(parentNode, localPosition, animationCsbPath, colliderSpritePath, dynamic, gravityEnabled, eventDispatcher, contactTestBitmask)
{

	setScale(0.8f);

}

Box::~Box() {

}