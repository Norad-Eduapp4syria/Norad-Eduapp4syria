#include "Cannon.h"
#include "Blending1Game.h"
#include "CannonAimCollider.h"
#include "TatuProjectile.h"
#include <algorithm>
using namespace std;


Cannon::Cannon(Node& parentNode, string nodeName, EventDispatcher* eventDispatcher, Blending1Game* blending1Game)
	: TouchableGameObject(parentNode, nodeName, Blending1Game::PATH + "Cannon.csb", "RootBone/PivotBone/ShotCollider", eventDispatcher),
	correctLetterHit(false)
{

	rotation = 0.f;

	this->blending1Game = blending1Game;

	pivotBone = getChild("RootBone/PivotBone");

	shotSmoke = new GameObject(*pivotBone, Vec2(140.f, 0.f), Blending1Game::PATH + "ShotSmoke.csb");
	shotSmoke->setScale(0.9f);

	cannonAimCollider = new CannonAimCollider(*getChild("RootBone"), "PivotBone", eventDispatcher, blending1Game, this);
    
	tatuProjectile = new TatuProjectile(*pivotBone, Vec2(50.f, 20.f), eventDispatcher);

	simpleAudioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
	simpleAudioEngine->preloadEffect((Blending1Game::PATH_AUDIO + "Audio/cannonLoad.mp3").c_str());
	simpleAudioEngine->preloadEffect((Blending1Game::PATH_AUDIO + "Audio/shot.mp3").c_str());
	simpleAudioEngine->preloadEffect((Blending1Game::PATH_AUDIO + "Audio/tatuYahoo.mp3").c_str());

}

Cannon::~Cannon() {

	delete shotSmoke;
	delete cannonAimCollider;
	delete tatuProjectile;

}

void Cannon::setTouchable(bool touchable) {

	TouchableGameObject::setTouchable(touchable);
	cannonAimCollider->setTouchable(touchable);

}

bool Cannon::onTouchBegan(Touch* touch, Event* event) {

	if (TouchableGameObject::onTouchBegan(touch, event)) {

		blending1Game->hideAimTutorial();
		blending1Game->hideShotTutorial();

		shot();

	}

	return false;

}

void Cannon::onTouchMoved(Touch* touch, Event* event) {

}

void Cannon::onTouchEnded(Touch* touch, Event* event) {

}

void Cannon::rotate(float deltaAngle) {

	static const float MAX_ROTATION_ANGLE = 0.f;
	static const float MIN_ROTATION_ANGLE = -60.f;

	float rotationAngle = min(MAX_ROTATION_ANGLE, max(MIN_ROTATION_ANGLE, pivotBone->getRotation() + deltaAngle));
	pivotBone->setRotation(rotationAngle);

}

void Cannon::load(bool enableTouch) {
    
	correctLetterHit = false;

	tatuProjectile->load();

	pivotBone->runAction(
		Sequence::create(
			RotateTo::create(0.5f, 0.f),
			CallFunc::create(
				[=]() {
					simpleAudioEngine->playEffect((Blending1Game::PATH_AUDIO + "Audio/cannonLoad.mp3").c_str());
					play("load", [=]() {
						play("idle", nullptr, true);
					
                        if (enableTouch == true) {
                            blending1Game->enableTouch();
                        }
                        
						getActionTimeline()->clearLastFrameCallFunc();
					});
				}),
			nullptr
			)
		);

}

void Cannon::shot() {

	setTouchable(false);

	simpleAudioEngine->playEffect((Blending1Game::PATH_AUDIO + "Audio/shot.mp3").c_str());
	
	play("shotA", [&]() {
		
		play("shotB");
		
		shotSmoke->play("shotSmoke");

		simpleAudioEngine->playEffect((Blending1Game::PATH_AUDIO + "Audio/tatuYahoo.mp3").c_str());
		Vec2 impulse(1000.f, 0.f);
		impulse.rotate(Vec2::ZERO, CC_DEGREES_TO_RADIANS(-pivotBone->getRotation()));
		tatuProjectile->shot(impulse);
		
		tatuProjectile->play(
			Sequence::create(
				DelayTime::create(3.5f),
				CallFunc::create(
					[&]() {
						//load();
						tatuProjectile->fadeOut(1.f);
					}),
				DelayTime::create(1.f),
				CallFunc::create(
					[&]() {
						tatuProjectile->load();
                        CCLOG("update box shot cannon");
						blending1Game->updateBoxes(correctLetterHit, true);
					}),
				nullptr
				)
			);

		getActionTimeline()->clearLastFrameCallFunc();

	});

}
void Cannon::setCorrectLetterHit() {

	correctLetterHit = true;

}