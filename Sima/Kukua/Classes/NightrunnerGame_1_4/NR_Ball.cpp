#include "NR_Ball.h"
#include "../Utils/Data/ArabicHelper.h"

NR_Ball::NR_Ball(Node& parentNode, string nodeName, EventDispatcher* eventDispatcher, string ballNumber)
	: TouchableGameObject(parentNode, nodeName, "NightrunnerGame_1_4/csd/Ball.csb", "Master_ball/ball/ball", eventDispatcher)
{
    
    numBall = ballNumber;
    
    setTouchable(true);

    label = ArabicHelper::getInstance()->createLabel("", 90);
    label->setTextColor(Color4B(47,109,182,255));
    getNode().getChildByName("Master_ball")->getChildByName("labelRef")->addChild(label);
    
}

NR_Ball::~NR_Ball() {

}


void NR_Ball::setValue(string value, int epispdeNum) {
   
    if ( (epispdeNum == 1) || (epispdeNum == 2) ) {
       
        
        if (epispdeNum == 1) {
            label->setPosition(Vec2(0,0));
            label->setSystemFontSize(90.0);
        } else {
            label->setPosition(Vec2(0,-20));
            label->setSystemFontSize(60.0);
        }
        
        label->setString( ArabicHelper::getInstance()->getInArabic(value) );
        
        
    } else if ( (epispdeNum == 3) || (epispdeNum == 4) ) {
        label->setPosition(Vec2(0,-26));
        label->setSystemFontSize(50.0);
        CCLOG("setValue: %s", value.c_str());
        label->setString( value );
        
    }

}

bool NR_Ball::onTouchBegan(Touch* touch, Event* event) {

	

	if (TouchableGameObject::onTouchBegan(touch, event)) {

        CCLOG("NR_Ball - onTouchBegan");
        play("tap");
        
        string numBallStr = numBall;
        char *buf = &numBallStr[0u];
        EventCustom event("TouchBallEvent");
        event.setUserData(buf);
        eventDispatcher->dispatchEvent(&event);
        
        
		// playAudio();
        /*
		play("tap", [&]() {
			if (blending1Game->getCurrentNR_Ball() == this) {
				play("standing", nullptr, true);
			}
			actionTimeline->clearLastFrameCallFunc();
		});
        */

	}

	return false;

}

void NR_Ball::playAudio() {

	// simpleAudioEngine->playEffect(("common/audio/sema/phonemes/" + ArabicHelper::getInstance()->getInLetter(phoneme) + ".mp3").c_str());

}
