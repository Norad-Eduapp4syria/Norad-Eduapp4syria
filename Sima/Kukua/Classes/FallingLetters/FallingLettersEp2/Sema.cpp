#include "Sema.h"
#include "FallingLettersEp2.h"


Sema::Sema(Node& parentNode, string nodeName, string csbPath, string colliderSpritePath, EventDispatcher* eventDispatcher, FallingLettersEp2* multiplicationGame)
	: DraggableGameObject(parentNode, nodeName, csbPath, colliderSpritePath, eventDispatcher)
{

	CCLOG("Sema");
	
	collider = new SemaColliderPhysicsGameObject(*(node->getChildByName("RootBone")->getChildByName("HeadBone")), "BasketBone", eventDispatcher, multiplicationGame);
	
	acceleration = Vec2::ZERO;
	velocity = Vec2::ZERO;

	Device::setAccelerometerEnabled(true);
	auto listener = EventListenerAcceleration::create(
		CC_CALLBACK_2(Sema::onAcceleration, this)
		);
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener, node);

}

Sema::~Sema() {

	delete collider;

}

void Sema::onTouchMoved(Touch* touch, Event* event) {
    
	float windowWidth = Director::getInstance()->getWinSize().width;
	float x = node->getParent()->convertToNodeSpace(touch->getLocation()).x;

	if (x > windowWidth / (FallingLettersEp2::FRUIT_COUNT + 1) && x < windowWidth * FallingLettersEp2::FRUIT_COUNT / (FallingLettersEp2::FRUIT_COUNT + 1)) {

		node->setPosition(
			Vec2(
				node->getParent()->convertToNodeSpace(touch->getLocation()).x,
				node->getPosition().y)
			);

	}

}

void Sema::onAcceleration(Acceleration* acc, Event* event) {

	acceleration = Vec2(1.f, 0.f) * acc->x;
}

void Sema::setAcceleration(Vec2 acceleration) {

	this->acceleration = acceleration;

}

void Sema::setVelocity(Vec2 velocity) {

	this->velocity = velocity;

}
