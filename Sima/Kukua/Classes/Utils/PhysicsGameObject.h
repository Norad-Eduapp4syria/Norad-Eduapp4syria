#pragma once

#include "GameObject.h"


class PhysicsGameObject : public GameObject {

public:
	PhysicsGameObject(Node& parentNode, string nodeName, string animationCsbPath, string colliderSpritePath, bool dynamic, bool gravityEnabled, EventDispatcher* eventDispatcher, unsigned int contactTestBitmask = 0xFFFFFFFF, const PhysicsMaterial& material = cocos2d::PHYSICSBODY_MATERIAL_DEFAULT, PhysicsShape::Type shape = PhysicsShape::Type::BOX);				// For existing nodes in scene
	PhysicsGameObject(Node& parentNode, const Vec2& localPosition, string animationCsbPath, string colliderSpritePath, bool dynamic, bool gravityEnabled, EventDispatcher* eventDispatcher, unsigned int contactTestBitmask = 0xFFFFFFFF, const PhysicsMaterial& material = cocos2d::PHYSICSBODY_MATERIAL_DEFAULT, PhysicsShape::Type shape = PhysicsShape::Type::BOX);		// For nodes to be instantiated from a csb or new nodes
	virtual ~PhysicsGameObject();
	bool isPhysicsActivated() const;
	void setPhysicsActivated(bool activated);
	void setGravityEnabled(bool enabled);
	PhysicsBody& getPhysicsBody() const;
	int getTag() const;

protected:
	static int LAST_TAG;
	const int tag;
	bool physicsActivated;
	bool gravityEnabled;
	EventDispatcher* eventDispatcher;
	EventListenerPhysicsContact* contactListener;
	PhysicsBody* physicsBody;
	virtual bool onContactBegin(PhysicsContact& contact);

private:
	PhysicsGameObject();				// Unimplemented

};

inline bool PhysicsGameObject::isPhysicsActivated() const {

	return physicsActivated;

}

inline PhysicsBody& PhysicsGameObject::getPhysicsBody() const {

	return *physicsBody;

}

inline int PhysicsGameObject::getTag() const {

	return tag;

}