#include "Bongo.h"
#include "../Utils/Game.h"
#include "WordsProblemGame.h"
#include "../Utils/StringUtility.h"
#include "../Utils/Data/Logger.h"

Bongo::Bongo(Node& parentNode, string nodeName, string csbPath, EventDispatcher* eventDispatcher, WordsProblemGame* wordsProblemGame, string audioFile)
	: TouchableGameObject(parentNode, nodeName, csbPath, "RootBone/Collider", eventDispatcher),
	audioFile(audioFile)
{

	CCLOG("Bongo");

	label = new LabelGameObject(*(node->getChildByName("RootBone")->getChildByName("NumberBone")), Vec2::ZERO, "common/fonts/Arabic-Regular.ttf", 180, "", Color3B(159, 107, 19));

	for (int index = 0; index < PARTICLE_SPRITE_COUNT; ++index) {
		particleSprites[index] = static_cast<Sprite*>(node->getChildByName("Particle" + StringUtility::toString(index + 1))->getChildByName("Sprite"));
	}

	this->wordsProblemGame = wordsProblemGame;

	simpleAudioEngine = CocosDenshion::SimpleAudioEngine::getInstance();

}

Bongo::~Bongo() {

	CCLOG("~Bongo");

	delete label;

}

bool Bongo::onTouchBegan(Touch* touch, Event* event) {

	CCLOG("Bongo - onTouchBegan");

	if (TouchableGameObject::onTouchBegan(touch, event)) {

		wordsProblemGame->Game<WordsProblemGame>::hideTutorial();
		wordsProblemGame->disableTouch();

		if (number == wordsProblemGame->getCorrectSolution()) {
            Logger::getInstance()->logEvent(WordsProblemGame::NAME, Logger::CORRECT, "");
			simpleAudioEngine->playEffect(audioFile.c_str());
			play("Bongo_play", [&]() {
				wordsProblemGame->checkBongosNumber(this);
                getActionTimeline()->clearLastFrameCallFunc();
			});
			for (int index = 0; index < PARTICLE_SPRITE_COUNT; ++index) {
				particleSprites[index]->setOpacity(255);
				particleSprites[index]->runAction(EaseIn::create(FadeOut::create(0.8f), 2.f));
			}
		} else {
            Logger::getInstance()->logEvent(WordsProblemGame::NAME, Logger::WRONG, "");
			simpleAudioEngine->playEffect((wordsProblemGame->PATH + "Audio/FeedNeg5.mp3").c_str());
			play("Bongo_error", [&]() {
				wordsProblemGame->checkBongosNumber(this);
                getActionTimeline()->clearLastFrameCallFunc();
			});
		}
		
	}

	return false;

}

void Bongo::setNumber(int number) {

	this->number = number;


	//CCLOG("_______________________ != nullptr ? %s", label->getNode().getChildByName("Label") != nullptr ? "true" : "false");
	static_cast<Label*>(label->getNode().getChildByName("Label"))->runAction(
		Sequence::create(
			FadeOut::create(0.25f),
			CallFunc::create(
				[&]() {
                    string txt = StringUtility::toString(this->number);
					label->setText(txt);
				}),
			FadeIn::create(0.25f),
			nullptr
			)
		);

}