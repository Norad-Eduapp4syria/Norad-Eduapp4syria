#pragma once

#include "../Utils/PhysicsGameObject.h"
class FallingLetters;


class FLSemaColliderPhysicsGameObject : public PhysicsGameObject {

public:
	static const int TAG = 500;
	FLSemaColliderPhysicsGameObject(Node& parentNode, string nodeName, EventDispatcher* eventDispatcher, FallingLetters* fallingLetters);
	virtual ~FLSemaColliderPhysicsGameObject();

protected:
	virtual bool onContactBegin(PhysicsContact& contact);

private:
	FallingLetters* fallingLetters;
	FLSemaColliderPhysicsGameObject();				// Unimplemented

};