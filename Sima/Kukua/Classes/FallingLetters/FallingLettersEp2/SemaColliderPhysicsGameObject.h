#pragma once

#include "../../Utils/PhysicsGameObject.h"
class FallingLettersEp2;


class SemaColliderPhysicsGameObject : public PhysicsGameObject {

public:
	static const int TAG = 500;
	SemaColliderPhysicsGameObject(Node& parentNode, string nodeName, EventDispatcher* eventDispatcher, FallingLettersEp2* multiplicationGame);
	virtual ~SemaColliderPhysicsGameObject();

protected:
	virtual bool onContactBegin(PhysicsContact& contact);

private:
	FallingLettersEp2* multiplicationGame;
	SemaColliderPhysicsGameObject();				// Unimplemented

};
