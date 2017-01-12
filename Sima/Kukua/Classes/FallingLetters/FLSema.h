#pragma once

#include "../Utils/DraggableGameObject.h"
#include "FLSemaColliderPhysicsGameObject.h"
class FallingLetters;


class FLSema : public DraggableGameObject {

public:
	FLSema(Node& parentNode, string nodeName, string csbPath, string colliderSpritePath, EventDispatcher* eventDispatcher, FallingLetters* fallingLetters);
	virtual ~FLSema();
	FLSemaColliderPhysicsGameObject* getCollider() const;
	Vec2 getAcceleration() const;
	void setAcceleration(Vec2 acceleration);
	Vec2 getVelocity() const;
	void setVelocity(Vec2 velocity);

protected:
	virtual void onTouchMoved(Touch* touch, Event* event);
	void onAcceleration(Acceleration* acc, Event* event);

private:
	Vec2 acceleration;
	Vec2 velocity;
	FLSemaColliderPhysicsGameObject* collider;
	FLSema();										// Unimplemented
	FLSema(const FLSema& otherSema);				// Unimplemented
	FLSema& operator=(const FLSema& otherSema);		// Unimplemented

};

inline Vec2 FLSema::getAcceleration() const {

	return acceleration;

}

inline Vec2 FLSema::getVelocity() const {

	return velocity;

}

inline FLSemaColliderPhysicsGameObject* FLSema::getCollider() const {

	return collider;

}