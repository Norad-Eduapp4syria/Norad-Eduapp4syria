#include "PhysicsGameObject.h"
#include "base/ccMacros.h"


int PhysicsGameObject::LAST_TAG(0);

PhysicsGameObject::PhysicsGameObject(Node& parentNode, string nodeName, string animationCsbPath, string colliderSpritePath, bool dynamic, bool gravityEnabled, EventDispatcher* eventDispatcher, unsigned int contactTestBitmask, const PhysicsMaterial& material, PhysicsShape::Type shape)
	: GameObject(parentNode, nodeName, animationCsbPath, colliderSpritePath),
	physicsActivated(false),
	gravityEnabled(gravityEnabled),
	tag(PhysicsGameObject::LAST_TAG++)
{

	this->eventDispatcher = eventDispatcher;

	// Calculate rotation and scale offset
	float rotationOffset = 0.f;
	float scaleOffset = 1.f;
	Node* tempNode = colliderSprite;
	while (tempNode != node) {
		rotationOffset += tempNode->getRotation();
		scaleOffset *= tempNode->getScale();
		tempNode = tempNode->getParent();
	}
	
	switch (shape) {
	case PhysicsShape::Type::BOX:
		physicsBody = PhysicsBody::createBox(colliderSprite->getBoundingBox().size * scaleOffset, material);
		break;
	case PhysicsShape::Type::CIRCLE:
		{ float radius = colliderSprite->getBoundingBox().size.width > colliderSprite->getBoundingBox().size.height ? colliderSprite->getBoundingBox().size.width : colliderSprite->getBoundingBox().size.height;
		physicsBody = PhysicsBody::createCircle(radius * scaleOffset, material); }
		break;
	default:
		CCLOG("Shape not yet implemented!");
		assert(false);
		break;
	}
	physicsBody->setDynamic(dynamic);
	physicsBody->setGravityEnable(gravityEnabled);
	physicsBody->setContactTestBitmask(contactTestBitmask);
	node->addComponent(physicsBody);
	physicsBody->setRotationOffset(rotationOffset);
	physicsBody->setPositionOffset(node->convertToNodeSpace(colliderSprite->getParent()->convertToWorldSpace(colliderSprite->getPosition())));

	setPhysicsActivated(true);

	node->setTag(tag);
	
}

PhysicsGameObject::PhysicsGameObject(Node& parentNode, const Vec2& localPosition, string animationCsbPath, string colliderSpritePath, bool dynamic, bool gravityEnabled, EventDispatcher* eventDispatcher, unsigned int contactTestBitmask, const PhysicsMaterial& material, PhysicsShape::Type shape)
	: GameObject(parentNode, localPosition, animationCsbPath, colliderSpritePath),
	physicsActivated(false),
	gravityEnabled(gravityEnabled),
	tag(PhysicsGameObject::LAST_TAG++)
{

	this->eventDispatcher = eventDispatcher;
	
	// Calculate rotation and scale offset
	float rotationOffset = 0.f;
	float scaleOffset = 1.f;
	Node* tempNode = colliderSprite;
	while (tempNode != node) {
		rotationOffset += tempNode->getRotation();
		scaleOffset *= tempNode->getScale();
		tempNode = tempNode->getParent();
	}

	switch (shape) {
	case PhysicsShape::Type::BOX:
		physicsBody = PhysicsBody::createBox(colliderSprite->getBoundingBox().size * scaleOffset, material);
		break;
	case PhysicsShape::Type::CIRCLE:
		{ float radius = colliderSprite->getBoundingBox().size.width > colliderSprite->getBoundingBox().size.height ? colliderSprite->getBoundingBox().size.width : colliderSprite->getBoundingBox().size.height;
		physicsBody = PhysicsBody::createCircle(radius * scaleOffset, material); }
		break;
	default:
		CCLOG("Shape not yet implemented!");
		assert(false);
		break;
	}
	physicsBody->setDynamic(dynamic);
	physicsBody->setGravityEnable(gravityEnabled);
	physicsBody->setContactTestBitmask(contactTestBitmask);
	node->addComponent(physicsBody);
	physicsBody->setRotationOffset(rotationOffset);
	physicsBody->setPositionOffset(node->convertToNodeSpace(colliderSprite->getParent()->convertToWorldSpace(colliderSprite->getPosition())));
	node->getPhysicsBody()->removeFromWorld();

	setPhysicsActivated(true);

	node->setTag(tag);

}

PhysicsGameObject::~PhysicsGameObject() {

	// CCLOG("~PhysicsGameObject");

}

void PhysicsGameObject::setPhysicsActivated(bool activated) {

	// CCLOG("PhysicsGameObject - setPhysicsActivated");

	if (this->physicsActivated == activated) {
		return;
	}

	this->physicsActivated = activated;

	if (physicsActivated) {
		
		/*// Calculate rotation offset
		float rotationOffset = 0.f;
		Node* tempNode = colliderSprite;
		while (tempNode != node) {
			rotationOffset += tempNode->getRotation();
			tempNode = tempNode->getParent();
		}

		node->addComponent(physicsBody);
		physicsBody->setRotationOffset(rotationOffset);
		physicsBody->setPositionOffset(node->convertToNodeSpace(colliderSprite->getParent()->convertToWorldSpace(colliderSprite->getPosition())));*/

		//node->setPhysicsBody(physicsBody);
		//node->getPhysicsBody()->removeFromWorld();

		physicsBody->setEnabled(true);
		physicsBody->setVelocity(Vec2::ZERO);
		physicsBody->setGravityEnable(gravityEnabled);
		
		// Add contact event listener
		contactListener = EventListenerPhysicsContact::create();
		contactListener->onContactBegin = CC_CALLBACK_1(PhysicsGameObject::onContactBegin, this);
		eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, node);

	} else {
		/*
		//node->removeComponent(physicsBody);

		node->getPhysicsBody()->removeFromWorld();

		// Remove contact event listener
		eventDispatcher->removeEventListener(contactListener);

		//
		*/
		
		physicsBody->setGravityEnable(false);
		physicsBody->setVelocity(Vec2::ZERO);
		physicsBody->setEnabled(false);
		//physicsBody->removeFromWorld();

		eventDispatcher->removeEventListener(contactListener);

	}

}

bool PhysicsGameObject::onContactBegin(PhysicsContact& contact) {

	// CCLOG("PhysicsGameObject - onContactBegin");

	//CCLOG("Contact %s %s", contact.getShapeA()->getBody()->getNode()->getName().c_str(), contact.getShapeB()->getBody()->getNode()->getName().c_str());

	return true;

}

void PhysicsGameObject::setGravityEnabled(bool enabled) {

	physicsBody->setGravityEnable(enabled);

}