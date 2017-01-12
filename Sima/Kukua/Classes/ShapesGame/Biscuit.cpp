#include "Biscuit.h"
#include "Gorilla.h"
#include "ShapesGame.h"


const float Biscuit::MIN_SCALE = 0.2f;
const float Biscuit::MAX_SCALE = 1.f;
const float Biscuit::DELTA_SCALE = MAX_SCALE - MIN_SCALE;
const float Biscuit::MOUTH_RADIUS = 100.f;

Biscuit::Biscuit(Node& parentNode, string nodeName, string csbPath, string colliderSpritePath, EventDispatcher* eventDispatcher, Gorilla* gorilla, Shape shape)
	: DraggableGameObject(parentNode, nodeName, csbPath, colliderSpritePath, eventDispatcher),
	gorilla(gorilla),
	shape(shape)
{

	CCLOG("Biscuit");

	shadowNode = static_cast<Node*>(node->getChildByName("RootBone")->getChildByName("ShadowBone")->getChildByName("ShadowSprite"));

	gorillaMouthNode = static_cast<Node*>(gorilla->getNode().getChildByName("RootBone")->getChildByName("Bone_torace")->getChildByName("Bone_NUCA")->getChildByName("MASER_faccia")->getChildByName("MASTER_Bocca")->getChildByName("Bone_boccaperta"));
	startDistanceToMouth = (getPosition() - gorillaMouthNode->getParent()->convertToWorldSpace(gorillaMouthNode->getPosition())).length();

}

Biscuit::Biscuit(Node& parentNode, const Vec2& localPosition, string csbPath, string colliderSpritePath, EventDispatcher* eventDispatcher, Gorilla* gorilla, Shape shape)
: DraggableGameObject(parentNode, localPosition, csbPath, colliderSpritePath, eventDispatcher),
gorilla(gorilla),
shape(shape)
{
    
    CCLOG("Biscuit");
    
    shadowNode = static_cast<Node*>(node->getChildByName("RootBone")->getChildByName("ShadowBone")->getChildByName("ShadowSprite"));
    
    gorillaMouthNode = static_cast<Node*>(gorilla->getNode().getChildByName("RootBone")->getChildByName("Bone_torace")->getChildByName("Bone_NUCA")->getChildByName("MASER_faccia")->getChildByName("MASTER_Bocca")->getChildByName("Bone_boccaperta"));
    startDistanceToMouth = (getPosition() - gorillaMouthNode->getParent()->convertToWorldSpace(gorillaMouthNode->getPosition())).length();
    
}


Biscuit::~Biscuit() {

	CCLOG("~Biscuit");

}

bool Biscuit::onTouchBegan(Touch* touch, Event* event) {

    if (DraggableGameObject::onTouchBegan(touch, event)) {
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect((ShapesGame::PATH + "Audio/tap1.mp3").c_str());
		startDistanceToMouth = (getPosition() - gorillaMouthNode->getParent()->convertToWorldSpace(gorillaMouthNode->getPosition())).length();
		//	node->stopAllActions();
		shadowNode->runAction(FadeOut::create(0.4f));
		return true;
	}

	return false;

}

void Biscuit::onTouchMoved(Touch* touch, Event* event) {

	DraggableGameObject::onTouchMoved(touch, event);

	float distance = (getPosition() - gorillaMouthNode->getParent()->convertToWorldSpace(gorillaMouthNode->getPosition())).length();
	if (distance < MOUTH_RADIUS) {
		node->setScale(MIN_SCALE);
		gorilla->openMouth();
	} else if (distance > startDistanceToMouth) {
		node->setScale(MAX_SCALE);
		gorilla->closeMouth();
	} else {
		node->setScale(MIN_SCALE + DELTA_SCALE * (distance - MOUTH_RADIUS) / (startDistanceToMouth - MOUTH_RADIUS));
		//node->setScale((distance / startDistanceToMouth) * MAX_SCALE);
		gorilla->closeMouth();
	}

}

void Biscuit::onTouchEnded(Touch* touch, Event* event) {

	static const float RETURN_TIME = 0.5f;
	static const float DISAPPER_TIME = 0.3f;

	DraggableGameObject::onTouchEnded(touch, event);

	float distance = (getPosition() - gorillaMouthNode->getParent()->convertToWorldSpace(gorillaMouthNode->getPosition())).length();
	if (distance < MOUTH_RADIUS) {
		//MoveTo* moveToMouth = MoveTo::create(DISAPPER_TIME, grandpaMouthNode->getParent()->convertToWorldSpace(grandpaMouthNode->getPosition()));
		MoveTo* moveToMouth = MoveTo::create(DISAPPER_TIME, node->getParent()->convertToNodeSpace(gorillaMouthNode->getParent()->convertToWorldSpace(gorillaMouthNode->getPosition())));
		ScaleTo* scaleToZero = ScaleTo::create(DISAPPER_TIME, 0.f);
		node->runAction(
			Sequence::create(
				Spawn::createWithTwoActions(moveToMouth, scaleToZero),
				CallFunc::create([=]() { setVisible(false); }),
				nullptr)
			);
		gorilla->eat(shape);
	} else {
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect((ShapesGame::PATH + "Audio/dropCestino.mp3").c_str());
		auto returnToStartPosition = EaseBounceOut::create(MoveTo::create(RETURN_TIME, startLocalPosition));
		auto scaleToMaxScale = EaseBounceOut::create(ScaleTo::create(RETURN_TIME, MAX_SCALE));
		CallFunc* fadeInShadow = CallFunc::create([this]() {
			shadowNode->runAction(FadeIn::create(0.4f));
		});
		node->runAction(Sequence::create(Spawn::createWithTwoActions(returnToStartPosition, scaleToMaxScale), fadeInShadow, nullptr));
		gorilla->closeMouth();
	}

	//EaseBounceOut::create()

}

void Biscuit::reset(Vec2 newLocalPosition) {

	/*startLocalPosition = node->getPosition();
	node->setScale(MAX_SCALE);
	shadowNode->setOpacity(255);*/
	
	/*node->stopAllActions();
	node->getChildByName("RootBone")->getChildByName("Sprite")->stopAllActions();
	node->getChildByName("RootBone")->getChildByName("ShadowBone")->getChildByName("ShadowSprite")->stopAllActions();*/

	//setLocalPosition(newLocalPosition);
	startLocalPosition = newLocalPosition;
	setLocalPosition(startLocalPosition);
	node->setScale(MAX_SCALE);
	setVisible(true);

	/*node->getChildByName("RootBone")->getChildByName("Sprite")->runAction(
		Sequence::create(
				FadeOut::create(0.25f),
				CallFunc::create(
					[&]() {
						setLocalPosition(startLocalPosition);
						node->setScale(MAX_SCALE);
						setVisible(true);
					}),
				FadeIn::create(0.25f),
				nullptr
			)
		);
	node->getChildByName("RootBone")->getChildByName("ShadowBone")->getChildByName("ShadowSprite")->runAction(
		Sequence::create(
				FadeOut::create(0.25f),
				FadeIn::create(0.25f),
				nullptr
			)
		);*/

}

void Biscuit::fadeIn(float seconds) {

	node->getChildByName("RootBone")->getChildByName("Sprite")->runAction(FadeIn::create(seconds));
	node->getChildByName("RootBone")->getChildByName("ShadowBone")->getChildByName("ShadowSprite")->runAction(FadeIn::create(seconds));

}

void Biscuit::fadeOut(float seconds) {

	node->getChildByName("RootBone")->getChildByName("Sprite")->runAction(FadeOut::create(seconds));
	node->getChildByName("RootBone")->getChildByName("ShadowBone")->getChildByName("ShadowSprite")->runAction(FadeOut::create(seconds));

}
