#include "FLFruit.h"
#include "FallingLetters.h"
#include "../Utils/StringUtility.h"
#include "../Utils/Data/DataProvider.h"

FLFruit::FLFruit(Node& parentNode, const Vec2& localPosition, EventDispatcher* eventDispatcher, int tag, FallingLetters* fallingLetters)
	: PhysicsGameObject(parentNode, localPosition, kukua::Game<FallingLetters>::PATH + "csd/Fruit.csb", "RootBone/Sprite", true, true, eventDispatcher, 1 << (tag - FallingLetters::FRUITS_BASE_TAG)),
	tag(tag),
	falling(false),
	startLocalPosition(node->getPosition())
{

	CCLOG("FLFruit");
    
    int skin = DataProvider::getInstance()->getSkin();
    static_cast<Sprite*>(node->getChildByName("RootBone")->getChildByName("Sprite"))->setTexture(kukua::Game<FallingLetters>::PATH+"png/fruits/fruit_"+  StringUtility::toString(skin) + ".png");

	node->setName(StringUtility::toString(tag - FallingLetters::FRUITS_BASE_TAG));

	this->fallingLetters = fallingLetters;

	label = new LabelGameObject(*(node->getChildByName("RootBone")), Vec2(-2.f, -17.f), "common/fonts/Arabic-Regular.ttf", 80, "0");

	physicsBody->setTag(tag);
    
	physicsBody->setRotationEnable(false);

	setVisible(false);

	startParentNode = &parentNode;

	fallEndAction = Sequence::create(
		DelayTime::create(5.f),
		CallFunc::create([&]() {
			setPhysicsActivated(false);
			falling = false;
			setVisible(false);
			node->setPosition(startLocalPosition);
		}),
		nullptr
		);

}

FLFruit::~FLFruit() {

    delete label;
}

void FLFruit::setLetter(string letter) {

	CCLOG("FLFruit - setNumber - Number %s", letter.c_str());
    
	this->letter = letter;
	label->setText(letter);
	label->getLabel().setSystemFontSize(90);

}

void FLFruit::startFalling() {

	CCLOG("FLFruit - startFalling - letter %s", letter.c_str());

	node->stopAllActions();

	setParent(*startParentNode);
	node->setPosition(startLocalPosition);
	node->getChildByName("RootBone")->setPosition(Vec2::ZERO);

	falling = true;
	setPhysicsActivated(true);
	setVisible(true);
	node->setRotation(0.f);
	physicsBody->setRotationOffset(0.f);

	node->getChildByName("RootBone")->stopAllActions();
	node->getChildByName("RootBone")->setScale(1.f);
	node->getChildByName("RootBone")->setPosition(Vec2::ZERO);

	// CocosDenshion::SimpleAudioEngine::getInstance()->playEffect((FallingLetters::PATH + "Audio/frutti_caduta.wav").c_str());

	node->getChildByName("RootBone")->getChildByName("Sprite")->runAction(FadeIn::create(1.f));
	label->getLabel().runAction(FadeIn::create(1.f));

	fallEndAction = Sequence::create(
		DelayTime::create(5.f),
		CallFunc::create([&]() {
			if (isPhysicsActivated()) {
				setPhysicsActivated(false);
			}
			falling = false;
			setVisible(false);
			setParent(*startParentNode);
			node->setPosition(startLocalPosition);
			node->getChildByName("RootBone")->setPosition(Vec2::ZERO);
		}),
		nullptr
		);
	node->runAction(fallEndAction);

}

void FLFruit::stopFalling(bool jumpAway) {

	CCLOG("FLFruit - stopFalling - letter %s", letter.c_str());

	if (!falling) {
		return;
	}

	falling = false;
	
	setPhysicsActivated(false);



	if (!jumpAway) {
		node->runAction(
			Sequence::create(
				CallFunc::create([&]() {
						node->getChildByName("RootBone")->getChildByName("Sprite")->runAction(FadeOut::create(1.f));
						label->getLabel().runAction(FadeOut::create(1.f));
					}),
				nullptr
				)
			);

	} else {
		node->getChildByName("RootBone")->runAction(
			Sequence::create(
				DelayTime::create(0.5f),
				Spawn::createWithTwoActions(
					JumpBy::create(0.75f, Vec2(-200.f, 50.f), 100.f, 1),
					ScaleTo::create(0.75f, 0.f)
					),
				nullptr
				)
			);
	}

}

bool FLFruit::onContactBegin(PhysicsContact& contact) {

	return false;
	
}
