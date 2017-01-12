#include "Train.h"
#include "ComprehensionGame.h"

#include <time.h>
#include "../Utils/StringUtility.h"


const Color3B Train::YELLOW_COLOR(179, 150, 16);
const Color3B Train::GREEN_COLOR(76, 125, 14);
const Color3B Train::ORANGE_COLOR(173, 92, 0);
const Color3B Train::VIOLET_COLOR(94, 84, 197);
const int Train::MIN_YELLOW_WAGON_NUMBER = 0;
const int Train::MAX_YELLOW_WAGON_NUMBER = 7;
//const int Train::SEND_CORRECT_WAGON_PROBABILITY = 25;	// %
const int Train::SEND_WAGON_PROBABILITY = 15;	//50;			// %
const float Train::SEND_WAGON_RATE = 8.f;	//2.5f;

Train::Train(Node& rootNode, const Vec2& localPosition, string csbFolderPath, EventDispatcher* eventDispatcher, ComprehensionGame& comprehensionGame, Node* wagonsPlaceholder)
	: GameObject(rootNode, localPosition, csbFolderPath + "Train.csb")//,
	//sendWagons(false)
{

	CCLOG("Train");

	this->comprehensionGame = &comprehensionGame;

	simpleAudioEngine = CocosDenshion::SimpleAudioEngine::getInstance();

	srand( static_cast<unsigned int>(time(NULL)));
	yellowWagonNumber = MIN_YELLOW_WAGON_NUMBER + rand() % (MAX_YELLOW_WAGON_NUMBER + 1 - MIN_YELLOW_WAGON_NUMBER);

	Node* rootBone = static_cast<Node*>(node->getChildByName("RootBone"));
	
	locomotiveGameObject = new GameObject(*(rootBone->getChildByName("LocomotiveNode")), Vec2::ZERO, csbFolderPath + "locomotive.csb");

	GameObject* wagonGameObject;

	// Yellow wagon
	wagonGameObject = new GameObject(*(rootBone->getChildByName("YellowWagonNode")), Vec2::ZERO, csbFolderPath + "YellowWagon.csb"/*, "BaloonBone/Sprite", eventDispatcher*/);
	yellowWagonLabelGameObject = new LabelGameObject(*(wagonGameObject->getNode().getChildByName("WagonBone")), Vec2(0.f, -5.f), "common/fonts/Arabic-Regular.ttf", 90, StringUtility::toString(yellowWagonNumber), YELLOW_COLOR);
	idleWagonsGameObjects.push_back(wagonGameObject);

	// Green wagons
	wagonGameObject = new GameObject(*(rootBone->getChildByName("GreenWagonNode")), Vec2::ZERO, csbFolderPath + "AlphaWagon.csb");
	idleWagonsGameObjects.push_back(wagonGameObject);
	/*wagons[&GREEN_COLOR].push_back(
		new Wagon(*(wagonGameObject->getNode().getChildByName("WagonBone")), Vec2(0.f, -350.f), csbFolderPath, "GreenWagon.csb", "BaloonBone/Sprite", eventDispatcher, &GREEN_COLOR, yellowWagonNumber + 1, *this)
		);
	wagons[&GREEN_COLOR].push_back(
		new Wagon(*(wagonGameObject->getNode().getChildByName("WagonBone")), Vec2(0.f, -350.f), csbFolderPath, "GreenWagon.csb", "BaloonBone/Sprite", eventDispatcher, &GREEN_COLOR, yellowWagonNumber + 1, *this)
		);*/
	wagons[&GREEN_COLOR].push_back(
			new Wagon(*wagonsPlaceholder, wagonsPlaceholder->convertToNodeSpace(wagonGameObject->getNode().getParent()->convertToWorldSpace(wagonGameObject->getNode().getChildByName("WagonBone")->getPosition() + Vec2(0.f, -350.f))), csbFolderPath, "GreenWagon.csb", "BaloonBone/Baloon/Sprite", eventDispatcher, &GREEN_COLOR, yellowWagonNumber + 1, *this, wagonGameObject->getNode().getChildByName("WagonBone"))
			);
	/*wagons[&GREEN_COLOR].push_back(
		new Wagon(*wagonsPlaceholder, wagonsPlaceholder->convertToNodeSpace(wagonGameObject->getNode().getParent()->convertToWorldSpace(wagonGameObject->getNode().getChildByName("WagonBone")->getPosition() + Vec2(0.f, -350.f))), csbFolderPath, "GreenWagon.csb", "BaloonBone/Sprite", eventDispatcher, &GREEN_COLOR, yellowWagonNumber + 1, *this, wagonGameObject->getNode().getChildByName("WagonBone"))
		);*/

	// Orange wagons
	wagonGameObject = new GameObject(*(rootBone->getChildByName("OrangeWagonNode")), Vec2::ZERO, csbFolderPath + "AlphaWagon.csb");
	idleWagonsGameObjects.push_back(wagonGameObject);
	/*wagons[&ORANGE_COLOR].push_back(
		new Wagon(*(wagonGameObject->getNode().getChildByName("WagonBone")), Vec2(0.f, -350.f), csbFolderPath, "OrangeWagon.csb", "BaloonBone/Sprite", eventDispatcher, &ORANGE_COLOR, yellowWagonNumber + 2, *this, &wagonGameObject->getNode())
		);
	wagons[&ORANGE_COLOR].push_back(
		new Wagon(*(wagonGameObject->getNode().getChildByName("WagonBone")), Vec2(0.f, -350.f), csbFolderPath, "OrangeWagon.csb", "BaloonBone/Sprite", eventDispatcher, &ORANGE_COLOR, yellowWagonNumber + 2, *this, &wagonGameObject->getNode())
		);*/
	wagons[&ORANGE_COLOR].push_back(
		new Wagon(*wagonsPlaceholder, wagonsPlaceholder->convertToNodeSpace(wagonGameObject->getNode().getParent()->convertToWorldSpace(wagonGameObject->getNode().getChildByName("WagonBone")->getPosition() + Vec2(0.f, -350.f))), csbFolderPath, "OrangeWagon.csb", "BaloonBone/Baloon/Sprite", eventDispatcher, &ORANGE_COLOR, yellowWagonNumber + 2, *this, wagonGameObject->getNode().getChildByName("WagonBone"))
		);
	/*wagons[&ORANGE_COLOR].push_back(
		new Wagon(*wagonsPlaceholder, wagonsPlaceholder->convertToNodeSpace(wagonGameObject->getNode().getParent()->convertToWorldSpace(wagonGameObject->getNode().getChildByName("WagonBone")->getPosition() + Vec2(0.f, -350.f))), csbFolderPath, "OrangeWagon.csb", "BaloonBone/Sprite", eventDispatcher, &ORANGE_COLOR, yellowWagonNumber + 2, *this, wagonGameObject->getNode().getChildByName("WagonBone"))
		);*/

	// Violet wagons
	wagonGameObject = new GameObject(*(rootBone->getChildByName("VioletWagonNode")), Vec2::ZERO, csbFolderPath + "AlphaWagon.csb");
	idleWagonsGameObjects.push_back(wagonGameObject);
	/*wagons[&VIOLET_COLOR].push_back(
		new Wagon(*(wagonGameObject->getNode().getChildByName("WagonBone")), Vec2(0.f, -350.f), csbFolderPath, "VioletWagon.csb", "BaloonBone/Sprite", eventDispatcher, &VIOLET_COLOR, yellowWagonNumber + 3, *this, &wagonGameObject->getNode())
		);
	wagons[&VIOLET_COLOR].push_back(
		new Wagon(*(wagonGameObject->getNode().getChildByName("WagonBone")), Vec2(0.f, -350.f), csbFolderPath, "VioletWagon.csb", "BaloonBone/Sprite", eventDispatcher, &VIOLET_COLOR, yellowWagonNumber + 3, *this, &wagonGameObject->getNode())
		);*/
	wagons[&VIOLET_COLOR].push_back(
		new Wagon(*wagonsPlaceholder, wagonsPlaceholder->convertToNodeSpace(wagonGameObject->getNode().getParent()->convertToWorldSpace(wagonGameObject->getNode().getChildByName("WagonBone")->getPosition() + Vec2(0.f, -350.f))), csbFolderPath, "VioletWagon.csb", "BaloonBone/Baloon/Sprite", eventDispatcher, &VIOLET_COLOR, yellowWagonNumber + 3, *this, wagonGameObject->getNode().getChildByName("WagonBone"))
		);
	/*wagons[&VIOLET_COLOR].push_back(
		new Wagon(*wagonsPlaceholder, wagonsPlaceholder->convertToNodeSpace(wagonGameObject->getNode().getParent()->convertToWorldSpace(wagonGameObject->getNode().getChildByName("WagonBone")->getPosition() + Vec2(0.f, -350.f))), csbFolderPath, "VioletWagon.csb", "BaloonBone/Sprite", eventDispatcher, &VIOLET_COLOR, yellowWagonNumber + 3, *this, wagonGameObject->getNode().getChildByName("WagonBone"))
		);*/

	// End wagon
	endWagonGameObject = new GameObject(*(rootBone->getChildByName("EndWagonNode")), Vec2::ZERO, csbFolderPath + "EndWagon.csb");
	endWagonBaloonGameObject = new GameObject(*(endWagonGameObject->getNode().getChildByName("WagonBone")->getChildByName("BaloonBone")), Vec2::ZERO, csbFolderPath + "Baloon_bye.csb");
	//endWagonBaloonGameObject->play("sema_baloon_A");
	endWagonBaloonGameObject->setVisible(false);
	
	/*sendGreenWagonsAction = RepeatForever::create(
			Sequence::create(
				CallFunc::create(
					[&]() {
						if (rand() % 100 < SEND_WAGON_PROBABILITY) {
							Wagon* wagon = wagons[&GREEN_COLOR][rand() % 2];
							if (!wagon->isSent()) {
								wagon->send();
							}
						}
					}
				),
				DelayTime::create(Wagon::SEND_TIME / SEND_WAGON_RATE),
				nullptr
				)
			);
	sendOrangeWagonsAction = RepeatForever::create(
			Sequence::create(
				DelayTime::create(Wagon::SEND_TIME / (3 * SEND_WAGON_RATE)),
				CallFunc::create(
					[&]() {
						if (rand() % 100 < SEND_WAGON_PROBABILITY) {
							Wagon* wagon = wagons[&ORANGE_COLOR][rand() % 2];
							if (!wagon->isSent()) {
								wagon->send();
							}
						}
					}
				),
				DelayTime::create((2 * Wagon::SEND_TIME) / (3 * SEND_WAGON_RATE)),
				nullptr
				)
			);
	sendVioletWagonsAction = RepeatForever::create(
			Sequence::create(
				DelayTime::create((2 * Wagon::SEND_TIME) / (3 * SEND_WAGON_RATE)),
				CallFunc::create(
					[&]() {
						if (rand() % 100 < SEND_WAGON_PROBABILITY) {
							Wagon* wagon = wagons[&VIOLET_COLOR][rand() % 2];
							if (!wagon->isSent()) {
								wagon->send();
							}
						}
					}
				),
				DelayTime::create(Wagon::SEND_TIME / (3 * SEND_WAGON_RATE)),
				nullptr
				)
			);
	node->runAction(sendGreenWagonsAction);
	node->runAction(sendOrangeWagonsAction);
	node->runAction(sendVioletWagonsAction);
	node->pause();*/

	sendGreenWagons = false;
	sendOrangeWagons = false;
	sendVioletWagons = false;

    hand = new GameObject( *(wagons[&VIOLET_COLOR][0]->getNode().getChildByName("BaloonBone")) , Vec2::ZERO, csbFolderPath + "Help_hand.csb" );
	hand->getNode().getChildByName("mano")->getChildByName("Manina")->getChildByName("Manina")->setVisible(false);
    
    node->setVisible(false);
	
}

Train::~Train() {

	CCLOG("~Train");

	locomotiveGameObject->getNode().removeFromParent();
	delete locomotiveGameObject;
	for (vector<GameObject*>::iterator iterator = idleWagonsGameObjects.begin(); iterator != idleWagonsGameObjects.end(); ++iterator) {
		delete (*iterator);
	}
	delete endWagonGameObject;
	delete yellowWagonLabelGameObject;

	for (vector<Wagon*>::iterator iterator = wagons[&GREEN_COLOR].begin(); iterator != wagons[&GREEN_COLOR].end(); ++iterator) {
		delete (*iterator);
	}
	for (vector<Wagon*>::iterator iterator = wagons[&ORANGE_COLOR].begin(); iterator != wagons[&ORANGE_COLOR].end(); ++iterator) {
		delete (*iterator);
	}
	for (vector<Wagon*>::iterator iterator = wagons[&VIOLET_COLOR].begin(); iterator != wagons[&VIOLET_COLOR].end(); ++iterator) {
		delete (*iterator);
	}

    delete hand;
    
}

void Train::fadeIn(std::function<void()> callback) {

	CCLOG("Train - fadeIn");

	/*if (callback != nullptr) {
		//CCLOG("callback");
		actionTimeline->setLastFrameCallFunc(callback);
	} else {
		//CCLOG("no callback");
		actionTimeline->clearLastFrameCallFunc();
	}

	actionTimeline->play(animationName, looping);*/

	simpleAudioEngine->playEffect((kukua::Game<ComprehensionGame>::PATH + "Audio/TRAIN.wav").c_str());

	node->setVisible(true);

	locomotiveGameObject->play("travel", nullptr, true);

	bool addPhase = false;
	for (vector<GameObject*>::iterator iterator = idleWagonsGameObjects.begin(); iterator != idleWagonsGameObjects.end(); ++iterator) {
		if (addPhase) {
			/*Node& wagonNode = (*iterator)->getNode();
			wagonNode.runAction(
				Sequence::create(
					DelayTime::create(0.5f),
					CallFunc::create([=]() {
							(*iterator)->play("travel", nullptr, true);
						}),
					nullptr));*/
			//(*iterator)->play("travel", nullptr, true, 0.5f);
			(*iterator)->play("travel", nullptr, true, 0.f, 22);
		} else {
			(*iterator)->play("travel", nullptr, true);
		}
		addPhase = !addPhase;
	}

	endWagonGameObject->play("travel", nullptr, true, 0.f, 22);

	/*play(
		"Train_A",
		[=]() {
			
			locomotiveGameObject->stop();

			for (vector<GameObject*>::iterator iterator = wagonsGameObjects.begin(); iterator != wagonsGameObjects.end(); ++iterator) {
				(*iterator)->stop();
			}

			if (callback != nullptr) {
				callback();
			}

		},
		false);*/

	Vec2 endPosition = node->getPosition();
	//node->setPosition(endPosition + Vec2(100.f, 0.f));
	node->setPosition(endPosition - Vec2(1280.f, 0.f));
	node->runAction(
		Sequence::create(
			EaseOut::create(MoveTo::create(3.f, endPosition), 2.f),
			CallFunc::create([&]() {
				locomotiveGameObject->pause();
				for (vector<GameObject*>::iterator iterator = idleWagonsGameObjects.begin(); iterator != idleWagonsGameObjects.end(); ++iterator) {
					(*iterator)->pause();
				}
				endWagonGameObject->pause();
			}),
			CallFunc::create(callback),
			nullptr
			)
		);

}

void Train::fadeOut(std::function<void()> callback) {

	CCLOG("Train - fadeOut");

	simpleAudioEngine->playEffect((kukua::Game<ComprehensionGame>::PATH + "Audio/TRAIN_riparte.wav").c_str());

	locomotiveGameObject->resume();

	for (vector<GameObject*>::iterator iterator = idleWagonsGameObjects.begin(); iterator != idleWagonsGameObjects.end(); ++iterator) {
		(*iterator)->resume();
	}

	endWagonGameObject->resume();

	Vec2 endPosition = node->getPosition();
	node->runAction(
		Sequence::create(
			Spawn::createWithTwoActions(
				EaseIn::create(MoveTo::create(4.5f, endPosition + Vec2(1920.f, 0.f)), 2.f),
				Sequence::create(
					DelayTime::create(2.f),
					CallFunc::create(
						[&]() {
							endWagonBaloonGameObject->setVisible(true);
							simpleAudioEngine->playEffect((kukua::Game<ComprehensionGame>::PATH + "Audio/byee_ok.mp3").c_str());
							endWagonBaloonGameObject->play("sema_baloon_A", [&]() {
								endWagonBaloonGameObject->play("animation0");                                
                                endWagonBaloonGameObject->getActionTimeline()->clearLastFrameCallFunc();
							});
						}),
					nullptr
					)
				),
			/*CallFunc::create([&]() {
				locomotiveGameObject->pause();
				for (vector<GameObject*>::iterator iterator = idleWagonsGameObjects.begin(); iterator != idleWagonsGameObjects.end(); ++iterator) {
					(*iterator)->pause();
				}
				endWagonGameObject->pause();
			}),*/
			CallFunc::create(callback),
			nullptr
		)
	);

}

/*void Train::update() {



}*/

/*bool Train::attachWagon(Wagon& wagon) {
	
	CCLOG("Train - attachWagon");
	
	return false;

}*/

void Train::startSendingWagons() {

	CCLOG("Train - startSendingWagons");

	sendGreenWagons = true;
	sendOrangeWagons = true;
	sendVioletWagons = true;

	/*sendGreenWagonsAction = RepeatForever::create(
			Sequence::create(
				CallFunc::create(
					[&]() {
						if (rand() % 100 < SEND_WAGON_PROBABILITY) {
							Wagon* wagon = wagons[&GREEN_COLOR][rand() % 2];
							if (!wagon->isSent()) {
								wagon->send();
							}
						}
					}
				),
				DelayTime::create(Wagon::SEND_TIME / SEND_WAGON_RATE),
				nullptr
				)
			);
	node->runAction(sendGreenWagonsAction);

	sendOrangeWagonsAction = RepeatForever::create(
			Sequence::create(
				DelayTime::create(Wagon::SEND_TIME / (3 * SEND_WAGON_RATE)),
				CallFunc::create(
					[&]() {
						if (rand() % 100 < SEND_WAGON_PROBABILITY) {
							Wagon* wagon = wagons[&ORANGE_COLOR][rand() % 2];
							if (!wagon->isSent()) {
								wagon->send();
							}
						}
					}
				),
				DelayTime::create((2 * Wagon::SEND_TIME) / (3 * SEND_WAGON_RATE)),
				nullptr
				)
			);
	node->runAction(sendOrangeWagonsAction);

	sendVioletWagonsAction = RepeatForever::create(
			Sequence::create(
				DelayTime::create((2 * Wagon::SEND_TIME) / (3 * SEND_WAGON_RATE)),
				CallFunc::create(
					[&]() {
						if (rand() % 100 < SEND_WAGON_PROBABILITY) {
							Wagon* wagon = wagons[&VIOLET_COLOR][rand() % 2];
							if (!wagon->isSent()) {
								wagon->send();
							}
						}
					}
				),
				DelayTime::create(Wagon::SEND_TIME / (3 * SEND_WAGON_RATE)),
				nullptr
				)
			);
	node->runAction(sendVioletWagonsAction);*/
	/*node->resume();*/

	sendWagonsAction = RepeatForever::create(
		Sequence::create(
			CallFunc::create(
				[&]() {
					
					float multiplyer = 1 + (3 - (sendGreenWagons ? 1 : 0) + (sendOrangeWagons ? 1 : 0) + (sendVioletWagons ? 1 : 0)) * 2.f/*(3.f / 2.f)*/;
					int randomNumber = rand() % 100;
					//CCLOG("----- randomNumber %d < %d -----", randomNumber, SEND_WAGON_PROBABILITY);
					if (randomNumber < SEND_WAGON_PROBABILITY * multiplyer) {
						Wagon* wagon;
						int wagonIndex = rand() % 3;
						switch (wagonIndex) {
						case 0:
							wagon = wagons[&GREEN_COLOR][0];
							if (sendGreenWagons && !wagon->isSent()) {
								//CCLOG("----- SEND GREEN -----");
								break;
							}
						case 1:
							wagon = wagons[&ORANGE_COLOR][0];
							if (sendOrangeWagons && !wagon->isSent()) {
								//CCLOG("----- SEND ORANGE -----");
								break;
							}
						case 2:
							wagon = wagons[&VIOLET_COLOR][0];
							if (sendVioletWagons && !wagon->isSent()) {
								//CCLOG("----- SEND VIOLET -----");
								break;
							}
						}
						wagon->send();
					}
				}
			),
			DelayTime::create(Wagon::SEND_TIME / SEND_WAGON_RATE),
		nullptr
		)
		);
	node->runAction(sendWagonsAction);

}

void Train::stopSendingWagons(const Color3B* color) {

	CCLOG("Train - stopSendingWagons");
	
	if (color == &GREEN_COLOR) {
		//node->stopAction(sendGreenWagonsAction);
		sendGreenWagons = false;
	} else if (color == &ORANGE_COLOR) {
		//node->stopAction(sendOrangeWagonsAction);
		sendOrangeWagons = false;
	} else if (color == &VIOLET_COLOR) {
		//node->stopAction(sendVioletWagonsAction);
		sendVioletWagons = false;
	}

	if (!sendGreenWagons && !sendOrangeWagons && !sendVioletWagons) {
		node->stopAction(sendWagonsAction);
		comprehensionGame->endGame();
	}

}

void Train::showTutorial() {
    hand->getNode().getChildByName("mano")->getChildByName("Manina")->getChildByName("Manina")->setVisible(true);
    hand->play("help_hand", nullptr, true);
}
void Train::hideTutorial() {
    hand->getNode().getChildByName("mano")->getChildByName("Manina")->getChildByName("Manina")->setVisible(false);
    hand->pause();
    CCLOG("Train - hideTutorial");
}