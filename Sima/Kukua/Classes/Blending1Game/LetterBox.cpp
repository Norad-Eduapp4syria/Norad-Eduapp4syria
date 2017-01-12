#include "LetterBox.h"
#include "Blending1Game.h"
#include "Cannon.h"
#include "../Utils//StringUtility.h"
#include <algorithm>


LetterBox::LetterBox(Node& parentNode, string nodeName, Color color, EventDispatcher* eventDispatcher, string phoneme, Blending1Game* blending1Game, Cannon* cannon)
	: Box(parentNode, nodeName, Blending1Game::PATH + (color == Color::YELLOW ? "Yellow" : (color == Color::RED ? "Red" : "Blue")) + "LetterBox.csb", "RootBone/BoxBone/Sprite", false, false, eventDispatcher),
	phoneme(phoneme),
	color(color)
{

	this->blending1Game = blending1Game;
	this->cannon = cannon;
    
	labelGameObject = new LabelGameObject(*(getChild("RootBone/BoxBone")), Vec2::ZERO, "common/fonts/Arabic-Regular.ttf", 100, phoneme, Color3B::WHITE, false, string(), false);

	simpleAudioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
	simpleAudioEngine->preloadEffect((Blending1Game::PATH_AUDIO + "Audio/correctLetterBoxHit.mp3").c_str());
	simpleAudioEngine->preloadEffect((Blending1Game::PATH_AUDIO + "Audio/wrongLetterBoxHit.mp3").c_str());

}

LetterBox::LetterBox(Node& parentNode, const Vec2& localPosition, Color color, EventDispatcher* eventDispatcher, string phoneme, Blending1Game* blending1Game, Cannon* cannon)
	: Box(parentNode, localPosition, Blending1Game::PATH + (color == Color::YELLOW ? "Yellow" : (color == Color::RED ? "Red" : "Blue")) + "LetterBox.csb", "RootBone/BoxBone/Sprite", false, false, eventDispatcher),
	phoneme(phoneme),
	color(color)
{
    
	this->blending1Game = blending1Game;
	this->cannon = cannon;

	labelGameObject = new LabelGameObject(*(getChild("RootBone/BoxBone")), Vec2::ZERO, "common/fonts/Arabic-Regular.ttf", 100, phoneme, Color3B::WHITE, false, string(), false);
	char firstChar = phoneme.front();
	if (phoneme.size() > 0 && islower(firstChar) != 0 && (firstChar != 'f' && firstChar != 'h' && firstChar != 'k' && firstChar != 'l' && firstChar != 't')) {
		labelGameObject->setLocalPosition(Vec2(0.f, 10.f));
	}

	simpleAudioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
	simpleAudioEngine->preloadEffect((Blending1Game::PATH_AUDIO + "Audio/correctLetterBoxHit.mp3").c_str());
	simpleAudioEngine->preloadEffect((Blending1Game::PATH_AUDIO + "Audio/wrongLetterBoxHit.mp3").c_str());
	simpleAudioEngine->preloadEffect((Blending1Game::PATH_AUDIO + "Audio/explosion1.mp3").c_str());
	simpleAudioEngine->preloadEffect((Blending1Game::PATH_AUDIO + "Audio/explosion2.mp3").c_str());
	simpleAudioEngine->preloadEffect((Blending1Game::PATH_AUDIO + "Audio/explosion3.mp3").c_str());

}

LetterBox::~LetterBox() {

	delete labelGameObject;

}

bool LetterBox::onContactBegin(PhysicsContact& contact) {

	// CCLOG("LetterBox - onContactBegin");

	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA && nodeB && (nodeA->getTag() == tag || nodeB->getTag() == tag)) {
		
		vector<Box*> boxes = blending1Game->getActiveBoxes();
		for (vector<Box*>::iterator iterator = boxes.begin(); iterator != boxes.end(); ++iterator) {
			(*iterator)->setPhysicsActivated(false);
		}

		if (phoneme == blending1Game->getCurrentPhoneme()) {
			
			simpleAudioEngine->playEffect((Blending1Game::PATH_AUDIO + "Audio/correctLetterBoxHit.mp3").c_str());

			cannon->setCorrectLetterHit();

			explode();

			vector<Box*> activeBoxes = blending1Game->getActiveBoxes();
			
			random_shuffle(activeBoxes.begin(), activeBoxes.end());
			
			const float stepDelay = 0.05f;
			float totalDelay = stepDelay;
			for (vector<Box*>::iterator iterator = activeBoxes.begin(); iterator != activeBoxes.end(); ++iterator) {
				Box* box = *iterator;
				if (box != this) {
					box->play(
						Sequence::createWithTwoActions(
							DelayTime::create(totalDelay),
							CallFunc::create(
								[=]() {
									simpleAudioEngine->playEffect((Blending1Game::PATH_AUDIO + "Audio/explosion" + StringUtility::toString(rand() % 3 + 1) + ".mp3").c_str());
									box->explode();
								})
							)
						);
					totalDelay += stepDelay;
				}
			}
			play(
				Sequence::createWithTwoActions(
					DelayTime::create(totalDelay / 2),
					CallFunc::create(
						[&]() {
							blending1Game->animateCorrectLetter(getPosition());
						})
					)
				);
			actionTimeline->clearLastFrameCallFunc();

		} else {

			simpleAudioEngine->playEffect((Blending1Game::PATH_AUDIO + "Audio/wrongLetterBoxHit.mp3").c_str());

			blending1Game->decreaseLifes();

			play("hit", [&]() {
				actionTimeline->clearLastFrameCallFunc();
			});
			
		}

	}

	return false;

}

void LetterBox::explode() {

	play("explode");

}
