#include "WRLetter.h"
#include "../Utils/Data/ArabicHelper.h"

WRLetter::WRLetter(Node& parentNode, const Vec2& localPosition, EventDispatcher* eventDispatcher, string letter)
	: TouchableGameObject(parentNode, localPosition, "WordReading/Csd/letter_box.csb", "letter_master/letter_box/hit", eventDispatcher)
{
	
    txt = letter;
    
    auto labelArab = ArabicHelper::getInstance()->createLabel(txt, 100, false);
    labelArab->setColor(Color3B(249, 142, 28));
    getChild("letter_master/letter_box/Text")->addChild(labelArab);
    
    cocos2d::ui::Text *label = static_cast<cocos2d::ui::Text *>( getChild("letter_master/letter_box/Text") );
    label->setString("");
    //label->setString(txt);
    
    
	simpleAudioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
    CCLOG("---------.-AUDIO txt %s",  ArabicHelper::getInstance()->getInLetter(txt).c_str());
    simpleAudioEngine->preloadEffect(("common/audio/sema/phonemes/" + ArabicHelper::getInstance()->getInLetter(txt) + ".mp3").c_str());

    setTouchable(true);
}

WRLetter::~WRLetter() {


}

bool WRLetter::onTouchBegan(Touch* touch, Event* event) {

	// CCLOG("WRLetter - onTouchBegan");

	if (TouchableGameObject::onTouchBegan(touch, event)) {

        CCLOG("tapped letter: %s", txt.c_str());
        
		playAudio();


	}

	return false;

}

void WRLetter::playAudio() {

	getParent()->runAction(
		Sequence::create(
		CallFunc::create(
		[=]() {
            string txtAudio = ArabicHelper::getInstance()->getInLetter(txt);

		simpleAudioEngine->playEffect(("common/audio/sema/phonemes/" + txtAudio + ".mp3").c_str());
		// set color
		// getChild("letter_master/letter_box/letter_box")->setColor(Color3B(200, 200, 0));

		// play animation
		play("press_letter");
	}),
		/*
		DelayTime::create(0.75f),
		CallFunc::create(
		[=]() {

		// set color
		// getChild("letter_master/letter_box/letter_box")->setColor(Color3B(255, 255, 255));
	}),*/
		nullptr
		)
		);

	//simpleAudioEngine->playEffect(("common/audio/sema/phonemes/" + txt + ".mp3").c_str());
	//simpleAudioEngine->playEffect(("phonemes/" + txt + ".mp3").c_str());
}
