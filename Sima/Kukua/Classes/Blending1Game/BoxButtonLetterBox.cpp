#include "BoxButtonLetterBox.h"
#include "Blending1Game.h"
#include "../Utils/Data/ArabicHelper.h"

BoxButtonLetterBox::BoxButtonLetterBox(Node& parentNode, const Vec2& localPosition, string phoneme, LetterBox::Color color)
	: GameObject(parentNode, localPosition, Blending1Game::PATH + "BoxButton" + (color == LetterBox::Color::YELLOW ? "Yellow" : (color == LetterBox::Color::RED ? "Red" : "Blue")) + "LetterBox.csb"),
	phoneme(phoneme),
	color(color)
{

	setScale(0.8f);
    
	labelGameObject = new LabelGameObject(*(getChild("RootBone")), Vec2::ZERO, "common/fonts/Arabic-Regular.ttf", 100, phoneme, Color3B::WHITE, false, string(), false);
	char firstChar = phoneme.front();
	if (phoneme.size() > 0 && islower(firstChar) != 0 && (firstChar != 'f' && firstChar != 'h' && firstChar != 'k' && firstChar != 'l' && firstChar != 't')) {
		labelGameObject->setLocalPosition(Vec2(0.f, 10.f));
	}

	simpleAudioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
    
	simpleAudioEngine->preloadEffect(("common/audio/sema/phonemes/" + ArabicHelper::getInstance()->getInLetter(phoneme) + ".mp3").c_str());

}

BoxButtonLetterBox::~BoxButtonLetterBox() {

	delete labelGameObject;

}

void BoxButtonLetterBox::playAudio() {

	simpleAudioEngine->playEffect(("common/audio/sema/phonemes/" + ArabicHelper::getInstance()->getInLetter(phoneme) + ".mp3").c_str());

}
