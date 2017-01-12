#pragma once

#include "../../Utils/DraggableGameObject.h"
#include "SemaColliderPhysicsGameObject.h"
class FallingLettersEp2;


class Sema : public DraggableGameObject {

public:
	Sema(Node& parentNode, string nodeName, string csbPath, string colliderSpritePath, EventDispatcher* eventDispatcher, FallingLettersEp2* multiplicationGame);
	virtual ~Sema();
	SemaColliderPhysicsGameObject* getCollider() const;
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
	SemaColliderPhysicsGameObject* collider;
	Sema();										// Unimplemented
	Sema(const Sema& otherSema);				// Unimplemented
	Sema& operator=(const Sema& otherSema);		// Unimplemented

};

inline Vec2 Sema::getAcceleration() const {

	return acceleration;

}

inline Vec2 Sema::getVelocity() const {

	return velocity;

}

inline SemaColliderPhysicsGameObject* Sema::getCollider() const {

	return collider;

}
