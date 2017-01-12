#include "CannonAimCollider.h"
#include "Blending1Game.h"
#include "Cannon.h"


CannonAimCollider::CannonAimCollider(Node& parentNode, string nodeName, EventDispatcher* eventDispatcher, Blending1Game* blending1Game, Cannon* cannon)
	: TouchableGameObject(parentNode, nodeName, "", "AimCollider", eventDispatcher)
{

	this->blending1Game = blending1Game;

	this->cannon = cannon;

	simpleAudioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
	simpleAudioEngine->preloadEffect((Blending1Game::PATH_AUDIO + "Audio/aim.mp3").c_str());

}

CannonAimCollider::CannonAimCollider(Node& parentNode, const Vec2& localPosition, EventDispatcher* eventDispatcher, Cannon* cannon)
	: TouchableGameObject(parentNode, localPosition, Blending1Game::PATH + "CannonRotationCollider.csb", "RootBone/Collider", eventDispatcher)
{

	this->cannon = cannon;

	simpleAudioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
	simpleAudioEngine->preloadEffect((Blending1Game::PATH_AUDIO + "Audio/aim.mp3").c_str());

}

CannonAimCollider::~CannonAimCollider() {

}

bool CannonAimCollider::onTouchBegan(Touch* touch, Event* event) {

	if (TouchableGameObject::onTouchBegan(touch, event)) {
        CCLOG("---CannonAimCollider::onTouchBegan");
		blending1Game->hideAimTutorial();

		aimAudioId = simpleAudioEngine->playEffect((Blending1Game::PATH_AUDIO + "Audio/aim.mp3").c_str(), true);

		return true;

	}

	return false;
	//return TouchableGameObject::onTouchBegan(touch, event);

}

void CannonAimCollider::onTouchMoved(Touch* touch, Event* event) {

	static const float ROTATION_SCALE = 0.2f;

	cannon->rotate(touch->getDelta().y * ROTATION_SCALE);

	/*Vec2 touchLocalPosition = colliderSprite->getParent()->convertTouchToNodeSpace(touch);

	cannon->rotate(-CC_RADIANS_TO_DEGREES(atan2f(touchLocalPosition.y, touchLocalPosition.x)));*/

}

void CannonAimCollider::onTouchEnded(Touch* touch, Event* event) {

	blending1Game->showShotTutorial();

	simpleAudioEngine->stopEffect(aimAudioId);

}