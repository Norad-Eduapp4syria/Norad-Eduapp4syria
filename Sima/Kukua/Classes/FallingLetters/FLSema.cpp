#include "FLSema.h"
#include "FallingLetters.h"


FLSema::FLSema(Node& parentNode, string nodeName, string csbPath, string colliderSpritePath, EventDispatcher* eventDispatcher, FallingLetters* fallingLetters)
	: DraggableGameObject(parentNode, nodeName, csbPath, colliderSpritePath, eventDispatcher)
{

	CCLOG("FLSema");
	
	collider = new FLSemaColliderPhysicsGameObject(*(node->getChildByName("RootBone")->getChildByName("HeadBone")), "BasketBone", eventDispatcher, fallingLetters);
	
	acceleration = Vec2::ZERO;
	velocity = Vec2::ZERO;

	Device::setAccelerometerEnabled(true);
	auto listener = EventListenerAcceleration::create(
		CC_CALLBACK_2(FLSema::onAcceleration, this)
		);
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener, node);

}

FLSema::~FLSema() {

	CCLOG("~FLSema");

	delete collider;

}

void FLSema::onTouchMoved(Touch* touch, Event* event) {

	float windowWidth = Director::getInstance()->getWinSize().width;
	float x = node->getParent()->convertToNodeSpace(touch->getLocation()).x;

	if (x > windowWidth / (FallingLetters::FRUIT_COUNT + 1) && x < windowWidth * FallingLetters::FRUIT_COUNT / (FallingLetters::FRUIT_COUNT + 1)) {

		node->setPosition(
			Vec2(
				node->getParent()->convertToNodeSpace(touch->getLocation()).x,
				node->getPosition().y)
			);

	}

}

void FLSema::onAcceleration(Acceleration* acc, Event* event) {

	acceleration = Vec2(1.f, 0.f) * acc->x;
}

void FLSema::setAcceleration(Vec2 acceleration) {

	this->acceleration = acceleration;

}

void FLSema::setVelocity(Vec2 velocity) {

	this->velocity = velocity;

}
