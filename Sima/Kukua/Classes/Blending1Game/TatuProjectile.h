#pragma once

#include "../Utils/PhysicsGameObject.h"


class TatuProjectile : public PhysicsGameObject {

public:
	TatuProjectile(Node& parentNode, const Vec2& localPosition, EventDispatcher* eventDispatcher);
	virtual ~TatuProjectile();
	void load();
	void shot(Vec2 impulse);
	void fadeOut(float time);

private:
	Vec2 startLocalPosition;
	Sprite* sprite;
	TatuProjectile();											// Unimplemented
	TatuProjectile(const TatuProjectile& other);				// Unimplemented
	TatuProjectile& operator=(const TatuProjectile& other);		// Unimplemented

};
