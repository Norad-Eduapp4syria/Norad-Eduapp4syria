#include "SemaColliderPhysicsGameObject.h"
#include "Fruit.h"
#include "FallingLettersEp2.h"


SemaColliderPhysicsGameObject::SemaColliderPhysicsGameObject(Node& parentNode, string nodeName, EventDispatcher* eventDispatcher, FallingLettersEp2* multiplicationGame)
	: PhysicsGameObject(parentNode, nodeName, string(), "Collider", false, false, eventDispatcher)
{

	CCLOG("SemaColliderPhysicsGameObject");

	this->multiplicationGame = multiplicationGame;

	physicsBody->setTag(TAG);

}

SemaColliderPhysicsGameObject::~SemaColliderPhysicsGameObject() {

}

bool SemaColliderPhysicsGameObject::onContactBegin(PhysicsContact& contact) {

	PhysicsGameObject::onContactBegin(contact);

	CCLOG("SemaColliderPhysicsGameObject - onContactBegin");

	map<int, Fruit*>& fruits = multiplicationGame->getFruits();

	map<int, Fruit*>::iterator fruitIterator = fruits.find(contact.getShapeA()->getBody()->getTag());
	CCLOG("Tag %d", contact.getShapeA()->getBody()->getTag());
	if (fruitIterator == fruits.end()) {
		fruitIterator = fruits.find(contact.getShapeB()->getBody()->getTag());
		CCLOG("Tag %d", contact.getShapeB()->getBody()->getTag());
	}

	if (fruitIterator != fruits.end()) {
		Fruit* fruit = fruitIterator->second;

		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect((FallingLettersEp2::PATH + "Audio/fruttoappenapreso.wav").c_str());
		fruit->stopFalling(fruit->getNumber() != multiplicationGame->getMultiplier());

		fruit->setParent(*node);
		fruit->getNode().getChildByName("RootBone")->getChildByName("Sprite")->setScale(1);

		fruit->getNode().getChildByName("RootBone")->runAction(
		
			JumpTo::create(
				0.25f,
				fruit->getNode().convertToNodeSpace(node->convertToWorldSpace(node->getChildByName("Collider")->getPosition() + Vec2(0.f, 50.f))),
				25.f,
				1
				)
			);

		multiplicationGame->checkFruitNumber(fruit->getNumber());

	}

	return false;

}
