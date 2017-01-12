#pragma once

#include "../Utils/PhysicsGameObject.h"


class Box : public PhysicsGameObject {

public:
	Box(Node& parentNode, string nodeName, string animationCsbPath, string colliderSpritePath, bool dynamic, bool gravityEnabled, EventDispatcher* eventDispatcher, unsigned int contactTestBitmask = 0xFFFFFFFF);
	Box(Node& parentNode, const Vec2& localPosition, string animationCsbPath, string colliderSpritePath, bool dynamic, bool gravityEnabled, EventDispatcher* eventDispatcher, unsigned int contactTestBitmask = 0xFFFFFFFF);
	virtual ~Box();
	virtual void explode() = 0;

private:
	Box();									// Unimplemented
	Box(const Box& other);					// Unimplemented
	Box& operator=(const Box& other);		// Unimplemented

};