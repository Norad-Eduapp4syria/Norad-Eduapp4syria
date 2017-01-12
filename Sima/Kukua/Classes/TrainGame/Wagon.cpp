#include "Wagon.h"
#include "Train.h"
//#include "Utils/Game.h"
#include "ComprehensionGame.h"
#include "../Utils/StringUtility.h"
#include "../Utils/Data/Logger.h"

const float Wagon::SEND_TIME = 5.f;
const Vec2 Wagon::SEND_OFFSET = Vec2(0.f, 1100.f);
const int Wagon::MIN_NUMBER = 0;
const int Wagon::MAX_NUMBER = 10;
const int Wagon::CORRECT_NUMBER_PROBABILITY = 33;


Wagon::Wagon(Node& parentNode, const Vec2& localPosition, string csbFolderPath, string csbFileName, string colliderSpritePath, EventDispatcher* eventDispatcher, const Color3B* color, int correctNumber, Train& train, Node* trainWagonNode)
	: TouchableGameObject(parentNode, localPosition, csbFolderPath + csbFileName, colliderSpritePath, eventDispatcher),
	color(color),
	correctNumber(correctNumber),
	startLocalPosition(localPosition),
	sent(false)
{

	CCLOG("Wagon");

	//node->retain();
	/*node->removeFromParent();
	wagonsPlaceholder->addChild(node);
	node->setPosition(wagonsPlaceholder->convertToNodeSpace(getPosition()));*/
	//node->removeFromParent();

	//startLocalPosition = wagonsPlaceholder->convertToNodeSpace(getPosition()/*node->getParent()->convertToNodeSpace(startLocalPosition)*/);
	
	/*node->retain();
	node->removeFromParent();
	wagonsPlaceholder->addChild(node);
	node->setGlobalZOrder(0);
	node->release();
	CCLOG("Wagon parent node: %s", node->getParent()->getName().c_str());*/

	//node->setPosition(wagonsPlaceholder->convertToNodeSpace(getPosition()));
	//node->release();

	this->train = &train;

	labelGameObject = new LabelGameObject(*(node->getChildByName("WagonBone")), Vec2::ZERO, "common/fonts/Arabic-Regular.ttf", 90, "", *color);
	
	this->wagonsPlaceholder = &parentNode;
	this->trainWagonNode = trainWagonNode;

	setVisible(false);

}

Wagon::~Wagon() {

	CCLOG("~Wagon");

	delete labelGameObject;

}

bool Wagon::onTouchBegan(Touch* touch, Event* event) {
	
	CCLOG("Wagon - onTouchBegan");

	if (TouchableGameObject::onTouchBegan(touch, event)) {
		setTouchable(false);
		node->stopAction(sendAction);


		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect((kukua::Game<ComprehensionGame>::PATH + "Audio/popEnri" + StringUtility::toString(rand() % 3 + 1) + ".wav").c_str());
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect((kukua::Game<ComprehensionGame>::PATH + "Audio/dropCarro.wav").c_str());

		node->retain();
		Vec2 newPosition = trainWagonNode->convertToNodeSpace(getPosition());
		wagonsPlaceholder->removeChild(node, false);
		trainWagonNode->addChild(node);
		node->setPosition(newPosition);
		node->release();
		//CCLOG("Wagon parent node: %s", node->getParent()->getName().c_str());

		Node* baloonBoneNode = node->getChildByName("BaloonBone");
		play("Wagon_tap_baloon", [=]() {
			baloonBoneNode->retain();
			//newPosition = node->convertToNodeSpace(node->getParent()->convertToWorldSpace(baloonBoneNode->getPosition()));
			node->getParent()->removeChild(baloonBoneNode, false);
			node->addChild(baloonBoneNode);
			baloonBoneNode->setPosition(Vec2::ZERO);
			baloonBoneNode->release();
            getActionTimeline()->clearLastFrameCallFunc();
		});
		baloonBoneNode->retain();
		newPosition = node->getParent()->convertToNodeSpace(node->convertToWorldSpace(baloonBoneNode->getPosition()));
		node->removeChild(baloonBoneNode, false);
		node->getParent()->addChild(baloonBoneNode);
		baloonBoneNode->setPosition(newPosition);
		baloonBoneNode->release();

		//play("Wagon_tap_baloon", [=]() {
			//actionTimeline->gotoFrameAndPause(0);
			node->runAction(
				Sequence::create(
					EaseBounceOut::create(
						MoveTo::create(
							1.f,
							Vec2::ZERO//node->getParent()->convertToWorldSpace(Vec2::ZERO)
							)
					),
					CallFunc::create(
							[&]() {
								if (number == correctNumber) {
                                    Logger::getInstance()->logEvent(ComprehensionGame::NAME, Logger::CORRECT, "");
									CocosDenshion::SimpleAudioEngine::getInstance()->playEffect((kukua::Game<ComprehensionGame>::PATH + "Audio/feedPos4.wav").c_str());
									trainWagonNode->getChildByName("Sprite")->runAction(FadeOut::create(1.f));
									play("Wagon_feedpos", [=]() {
										train->stopSendingWagons(color);
                                        getActionTimeline()->clearLastFrameCallFunc();
									});
								} else {
                                    Logger::getInstance()->logEvent(ComprehensionGame::NAME, Logger::WRONG, "");
									CocosDenshion::SimpleAudioEngine::getInstance()->playEffect((kukua::Game<ComprehensionGame>::PATH + "Audio/feed_NEG5.wav").c_str());

    //
                                    train->scorePercent -= train->scoreToSubtract;
CCLOG("score ora vale %f", train->scorePercent);
                                
									play("Wagon_error", [=]() {
										node->runAction(
											Sequence::create(
												//EaseElasticInOut::create(MoveBy::create(1.f, Vec2::ZERO)),
												Spawn::createWithTwoActions(
													JumpBy::create(SEND_TIME / 10, Vec2(-150.f, 50.f), 100.f, 1),
													ScaleTo::create(SEND_TIME / 10, 0.f)
													),
												CallFunc::create(
													[&]() {
														node->retain();
														trainWagonNode->removeChild(node, false);
														wagonsPlaceholder->addChild(node);
														node->release();
														
														actionTimeline->gotoFrameAndPause(0);
														node->setScale(1.f);
														node->setPosition(startLocalPosition);
														setTouchable(false);
														sent = false;

														setVisible(false);
													}),
												nullptr
											)
										);
                                        getActionTimeline()->clearLastFrameCallFunc();
									});
									
								}
							}
						),
					nullptr
				)
			);
		//});
	}

	// Always return false
	return false;

}

void Wagon::setNumber(int number) {

	//CCLOG("Wagon - setNumber");

	this->number = number;

	string numberString = StringUtility::toString(number);

	labelGameObject->setText(numberString);

}

void Wagon::send() {
	
	//CCLOG("Wagon - send");

	const auto SEND = Sequence::create(
			CallFunc::create(
				[&]() {
					actionTimeline->gotoFrameAndPause(0);
					node->setScale(1.f);
					node->setPosition(startLocalPosition);
					setTouchable(false);
					setVisible(true);
				}
			),
			Spawn::createWithTwoActions(
				MoveBy::create(SEND_TIME, SEND_OFFSET),
				Sequence::create(
					DelayTime::create(SEND_TIME / 2.25),
					CallFunc::create(
						[&]() {
							setTouchable(true);
						}),
					nullptr
					)
				),
			CallFunc::create(
				[&]() {
					actionTimeline->gotoFrameAndPause(0);
					node->setScale(1.f);
					node->setPosition(startLocalPosition);
					setTouchable(false);
					sent = false;
					setVisible(false);
				}
			),
			nullptr
		);

	if (sent) {
		return;
	}

	sent = true;

	/*node->removeFromParent();
	wagonsPlaceholder->addChild(node);
	startLocalPosition = wagonsPlaceholder->convertToNodeSpace(getPosition());
	node->setPosition(startLocalPosition);*/


	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect((kukua::Game<ComprehensionGame>::PATH + "Audio/CarroSale.wav").c_str());

	int newNumber;
	if (rand() % 100 < CORRECT_NUMBER_PROBABILITY) {
		newNumber = correctNumber;
	} else {
		do {
			newNumber = MIN_NUMBER + rand() % (MAX_NUMBER - MIN_NUMBER);
		} while (newNumber == correctNumber);
	}
	setNumber(newNumber);

	//auto send = MoveBy::create(SEND_TIME, SEND_OFFSET);
	sendAction = SEND->clone();
	node->runAction(
		sendAction
	);

}