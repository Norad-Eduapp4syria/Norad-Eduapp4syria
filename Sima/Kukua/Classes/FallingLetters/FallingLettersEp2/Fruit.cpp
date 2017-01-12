#include "Fruit.h"
#include "FallingLettersEp2.h"
#include "../../Utils/StringUtility.h"

Fruit::Fruit(Node& parentNode, const Vec2& localPosition, EventDispatcher* eventDispatcher, int tag, FallingLettersEp2* multiplicationGame)
	: PhysicsGameObject(parentNode, localPosition, kukua::Game<FallingLettersEp2>::PATH + "csd/Fruit.csb", "RootBone/Sprite", true, true, eventDispatcher, 1 << (tag - FallingLettersEp2::FRUITS_BASE_TAG)),
	tag(tag),
	falling(false),
	startLocalPosition(node->getPosition())
{

	//CCLOG("Fruit");

    int skin = DataProvider::getInstance()->getSkin();
    static_cast<Sprite*>(node->getChildByName("RootBone")->getChildByName("Sprite"))->setTexture(kukua::Game<FallingLettersEp2>::PATH+"png/fruits/fruit_"+  StringUtility::toString(skin) + ".png");
    
	node->setName(StringUtility::toString(tag - FallingLettersEp2::FRUITS_BASE_TAG));

	this->multiplicationGame = multiplicationGame;

    labelImg = Sprite::create("common/images/letters/small_white/void.png");
    node->getChildByName("RootBone")->addChild(labelImg);
    labelImg->setPosition( Vec2(-2.f, -17.f) );

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

Fruit::~Fruit() {

}

void Fruit::setNumber(int number) {

	//CCLOG("Fruit - setNumber - Number %d", number);

	this->number = number;
    //string txt = StringUtility::toString(number);

    
    string phoneme = DataProvider::getInstance()->getCurrentDBKnowledgeBubble()->getPhoneme();
    
    // i numeri corretti sono solo: 0, 1, 2
    if (number == 0) labelImg->setTexture("common/images/letters/small_white/"+phoneme+"_initial.png");
    else if (number == 1) labelImg->setTexture("common/images/letters/small_white/"+phoneme+"_medial.png");
    else if (number == 2) labelImg->setTexture("common/images/letters/small_white/"+phoneme+"_final.png");
    
    else if (number == 3) labelImg->setTexture("common/images/letters/small_white/"+phoneme+"_initial.png");
    else if (number == 4) labelImg->setTexture("common/images/letters/small_white/"+phoneme+"_medial.png");
    else if (number == 5) labelImg->setTexture("common/images/letters/small_white/"+phoneme+"_final.png");
    
    else {
        // wrong random phoneme
        
        string wrong = DataProvider::getInstance()->getRandomWrongPhoneme(phoneme);
        wrong = wrong.substr(0, wrong.find("_"));
        
        while (wrong == phoneme) {
            wrong = DataProvider::getInstance()->getRandomWrongPhoneme(phoneme);
            wrong = wrong.substr(0, wrong.find("_"));
        }
        // NB questo non è del tutto corretto perchè così facendo posso andare a pescare fonemi che ancora non ho scoperto
        int pos = rand() % 3;
        if (pos == 0) labelImg->setTexture("common/images/letters/small_white/"+wrong+"_initial.png");
        else if (pos == 0) labelImg->setTexture("common/images/letters/small_white/"+wrong+"_medial.png");
        else if (pos == 0) labelImg->setTexture("common/images/letters/small_white/"+wrong+"_final.png");
        else labelImg->setTexture("common/images/letters/small_white/"+wrong+".png");
        
        CCLOG("--------------wrong = %s", wrong.c_str());
        
    }
 
}

void Fruit::startFalling() {

	// CCLOG("Fruit - startFalling - Number %d", number);

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


	node->getChildByName("RootBone")->getChildByName("Sprite")->runAction(FadeIn::create(1.f));
	labelImg->runAction( FadeIn::create(1.f) );
    
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

void Fruit::stopFalling(bool jumpAway) {

	CCLOG("Fruit - stopFalling - Number %d", number);

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
						labelImg->runAction( FadeOut::create(1.f) );
					}),
				nullptr
				)
			);

	} else {
		CCLOG("_|-|_|-|_|-|_|-|_ Jumping Number %d", number);
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

bool Fruit::onContactBegin(PhysicsContact& contact) {

	return false;
	
	CCLOG("Fruit - onContactBegin");
	CCLOG("Number %d", number);

	if (falling && (contact.getShapeA()->getBody()->getTag() == SemaColliderPhysicsGameObject::TAG || contact.getShapeB()->getBody()->getTag() == SemaColliderPhysicsGameObject::TAG)) {

		PhysicsGameObject::onContactBegin(contact);

		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect((FallingLettersEp2::PATH + "Audio/fruttoappenapreso.wav").c_str());
		stopFalling(number != multiplicationGame->getMultiplier());

		//return true;

	}

	return false;

}
