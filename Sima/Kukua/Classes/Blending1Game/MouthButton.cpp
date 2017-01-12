#include "MouthButton.h"
#include "Blending1Game.h"


MouthButton::MouthButton(Node& parentNode, string nodeName, EventDispatcher* eventDispatcher, const string& word)
	: TouchableGameObject(parentNode, nodeName, Blending1Game::PATH + "MouthButton.csb", "RootBone/Sprite", eventDispatcher),
	word(word)
{

	CCLOG("MouthButton()");

	simpleAudioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
	simpleAudioEngine->preloadEffect(("common/audio/sema/words/" + word + ".mp3").c_str());

}

MouthButton::~MouthButton() {

	CCLOG("~MouthButton()");

}

bool MouthButton::onTouchBegan(Touch* touch, Event* event) {

	CCLOG("MouthButton - onTouchBegan");
	
	if (TouchableGameObject::onTouchBegan(touch, event)) {
		
		playAudio();

		play("tap", [&]() {
			//play("standing", nullptr, true);
			actionTimeline->clearLastFrameCallFunc();
		});

	}

	return false;

}

void MouthButton::playAudio() {

	simpleAudioEngine->playEffect(("common/audio/sema/words/" + word + ".mp3").c_str());

}