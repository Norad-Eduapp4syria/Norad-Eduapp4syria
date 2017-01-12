#include "FLSemaColliderPhysicsGameObject.h"
#include "FLFruit.h"
#include "FallingLetters.h"


FLSemaColliderPhysicsGameObject::FLSemaColliderPhysicsGameObject(Node& parentNode, string nodeName, EventDispatcher* eventDispatcher, FallingLetters* fallingLetters)
	: PhysicsGameObject(parentNode, nodeName, string(), "Collider", false, false, eventDispatcher)
{

	CCLOG("FLSemaColliderPhysicsGameObject");

	this->fallingLetters = fallingLetters;

	physicsBody->setTag(TAG);

}

FLSemaColliderPhysicsGameObject::~FLSemaColliderPhysicsGameObject() {

	CCLOG("~FLSemaColliderPhysicsGameObject");

}

bool FLSemaColliderPhysicsGameObject::onContactBegin(PhysicsContact& contact) {

	PhysicsGameObject::onContactBegin(contact);

	CCLOG("FLSemaColliderPhysicsGameObject - onContactBegin");

	map<int, FLFruit*>& fruits = fallingLetters->getFruits();

	map<int, FLFruit*>::iterator fruitIterator = fruits.find(contact.getShapeA()->getBody()->getTag());
	CCLOG("Tag %d", contact.getShapeA()->getBody()->getTag());
	if (fruitIterator == fruits.end()) {
		fruitIterator = fruits.find(contact.getShapeB()->getBody()->getTag());
		CCLOG("Tag %d", contact.getShapeB()->getBody()->getTag());
	}

	if (fruitIterator != fruits.end()) {
		FLFruit* fruit = fruitIterator->second;
		//fruit->setPhysicsActivated(false);

		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect((FallingLetters::PATH + "Audio/fruttoappenapreso.wav").c_str());
		fruit->stopFalling(fruit->getLetter() != fallingLetters->getLetterToGet() );

		/*fruit->setParent(*node);
		fruit->play(MoveTo::create(0.5f, Vec2::ZERO));*/
		fruit->setParent(*node);
		fruit->getNode().getChildByName("RootBone")->getChildByName("Sprite")->setScale(1);
		//fruit->getNode().setPosition(Vec2(0.f, -400.f));
		//fruit->getNode().getChildByName("RootBone")->setPosition(Vec2(100.f, 0.f));
		fruit->getNode().getChildByName("RootBone")->runAction(
	
			JumpTo::create(
				0.25f,
				fruit->getNode().convertToNodeSpace(node->convertToWorldSpace(node->getChildByName("Collider")->getPosition() + Vec2(0.f, 50.f))),
				25.f,
				1
				)
			);

		fallingLetters->checkFruitLetter(fruit->getLetter());

	}

	return false;

}
