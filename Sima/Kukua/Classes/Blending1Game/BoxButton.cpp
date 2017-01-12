#include "BoxButton.h"
#include "Blending1Game.h"
#include "BoxButtonLetterBox.h"
#include "../Utils/Data/ArabicHelper.h"

/*BoxButton::BoxButton(Node& parentNode, string nodeName, EventDispatcher* eventDispatcher)
	: TouchableGameObject(parentNode, nodeName, Blending1Game::PATH + "BoxButton.csb", "RootBone/Sprite", eventDispatcher)
{

	CCLOG("BoxButton()");

}*/

BoxButton::BoxButton(Node& parentNode, const Vec2& localPosition, EventDispatcher* eventDispatcher, Blending1Game* blending1Game, string phoneme, LetterBox::Color color)
	: TouchableGameObject(parentNode, localPosition, Blending1Game::PATH + "BoxButton.csb", "RootBone/Sprite", eventDispatcher),
	phoneme(phoneme)
{
	
	this->blending1Game = blending1Game;

	boxButtonLetterBox = new BoxButtonLetterBox(*node, Vec2::ZERO, phoneme, color);

	simpleAudioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
    
	simpleAudioEngine->preloadEffect(("common/audio/sema/phonemes/" + ArabicHelper::getInstance()->getInLetter(phoneme) + ".mp3").c_str());

}

BoxButton::~BoxButton() {

	delete boxButtonLetterBox;

}

bool BoxButton::onTouchBegan(Touch* touch, Event* event) {

	// CCLOG("BoxButton - onTouchBegan");

	if (TouchableGameObject::onTouchBegan(touch, event)) {

		playAudio();

		play("tap", [&]() {
			if (blending1Game->getCurrentBoxButton() == this) {
				play("standing", nullptr, true);
			}
			actionTimeline->clearLastFrameCallFunc();
		});

	}

	return false;

}

void BoxButton::playAudio() {

	simpleAudioEngine->playEffect(("common/audio/sema/phonemes/" + ArabicHelper::getInstance()->getInLetter(phoneme) + ".mp3").c_str());

}
