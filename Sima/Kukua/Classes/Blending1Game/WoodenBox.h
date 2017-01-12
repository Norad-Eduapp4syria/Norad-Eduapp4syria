#pragma once

#include "Box.h"
#include "SimpleAudioEngine.h"


class WoodenBox : public Box {

public:
	WoodenBox(Node& parentNode, string nodeName, EventDispatcher* eventDispatcher);
	WoodenBox(Node& parentNode, const Vec2& localPosition, EventDispatcher* eventDispatcher);
	virtual ~WoodenBox();
	virtual void explode();

protected:
	//CocosDenshion::SimpleAudioEngine* simpleAudioEngine;
	virtual bool onContactBegin(PhysicsContact& contact);

private:
	bool hit;
	WoodenBox();										// Unimplemented
	WoodenBox(const WoodenBox& other);					// Unimplemented
	WoodenBox& operator=(const WoodenBox& other);		// Unimplemented

};