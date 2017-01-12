#include "FallingLettersEp2.h"
#include "Fruit.h"

#include <time.h>
#include <iterator>
#include "../../Utils/StringUtility.h"
#include "../../Utils/Data/Logger.h"
#include "../../WatchmanScene/WatchmanScene.h"
#include "../../AppMacros.h"

template<> const bool kukua::Game<FallingLettersEp2>::USE_PHYSICS = true;										// Enable/disable physics
template<> const bool kukua::Game<FallingLettersEp2>::ENABLE_TOUCH = true;										// Used to disable tutorial on first touch and manage general touch events
template<> string kukua::Game<FallingLettersEp2>::PATH = "FallingLetters/";							// Resources' subfolder path for this game
template<> const string kukua::Game<FallingLettersEp2>::BACKGROUND_MUSIC_FILENAME = "";		// Background music filename
template<> bool kukua::Game<FallingLettersEp2>::SHOWN_TUTORIAL = false;										// Used for showing tutorial on first execution, set to true only if tutorial is not needed
template<> Scene* kukua::Game<FallingLettersEp2>::scene = nullptr;
const int FallingLettersEp2::FRUITS_BASE_TAG = 1000;
template<> const string kukua::Game<FallingLettersEp2>::NAME = "FallingLetters";

FallingLettersEp2::~FallingLettersEp2() {

	// Delete objects created with new
	delete help;
	delete helpHand;
	delete sema;
	delete semaTryagain;
	delete multiplicationBaloon;
	delete signboardPositive;
	delete signboardNegative;
	delete spiral;

	for (map<int, Fruit*>::iterator iterator = fruits.begin(); iterator != fruits.end(); ++iterator) {
		delete iterator->second;
	}

	for (int index = 0; index < MAX_LIFES; ++index) {
		delete lifesGameObjects[index];
	}

}

void FallingLettersEp2::initVariables() {

	CCLOG("FallingLettersEp2 - Init variables");

	//auto scene = _director->getRunningScene();
	scene->getPhysicsWorld()->setGravity(scene->getPhysicsWorld()->getGravity() * 1.75f);

	srand( static_cast<unsigned int>(time(NULL)));
   // multiplicand = 1; //rand() % 10 + 1;
	multiplier = rand() % 6;
     CCLOG("------------------1-RAND multiplier = %d", multiplier);
    phonemesToCollect = 5;
	lifes = MAX_LIFES;

}

void FallingLettersEp2::initAudio() {

	CCLOG("FallingLettersEp2 - Init audio");

	// Preload audio files
	simpleAudioEngine->preloadEffect((PATH + "Audio/cartello_entra.wav").c_str());
	simpleAudioEngine->preloadEffect((PATH + "Audio/cesto_corretto.wav").c_str());
	simpleAudioEngine->preloadEffect((PATH + "Audio/cesto_sbagliato.wav").c_str());
	simpleAudioEngine->preloadEffect((PATH + "Audio/error.wav").c_str());
	simpleAudioEngine->preloadEffect((PATH + "Audio/feedPosSalsaChildren.wav").c_str());
	simpleAudioEngine->preloadEffect((PATH + "Audio/frutti_caduta.wav").c_str());
	simpleAudioEngine->preloadEffect((PATH + "Audio/fruttini_vite.wav").c_str());
	simpleAudioEngine->preloadEffect((PATH + "Audio/fruttoappenapreso.wav").c_str());
	simpleAudioEngine->preloadEffect((PATH + "Audio/SemaSale.wav").c_str());
	simpleAudioEngine->preloadEffect((PATH + "Audio/SemaScende.wav").c_str());
	simpleAudioEngine->preloadEffect((PATH + "Audio/tryagaing.mp3").c_str());
	simpleAudioEngine->preloadEffect((PATH + "Audio/welldone.mp3").c_str());
    
    simpleAudioEngine->preloadBackgroundMusic("common/audio/bg/GAME_4.mp3");
    simpleAudioEngine->playBackgroundMusic("common/audio/bg/GAME_4.mp3", true);

}

void FallingLettersEp2::initGameObjects() {

	CCLOG("FallingLettersEp2 - Init objects");

    CCLOG("-----FallingLettersEp2, currentPhoneme = %s", DataProvider::getInstance()->getCurrentDBKnowledgeBubble()->getPhoneme().c_str() );
    /*
     if (DataProvider::getInstance()->getCurrentEpisode()==2) {
     phoneme = phoneme.substr(0, phoneme.find("_"));
     }
     */
    
    int skin = DataProvider::getInstance()->getSkin();
    
    static_cast<Sprite*>(rootNode->getChildByName("Background"))->setTexture(PATH+"png/background/background_" +  StringUtility::toString(skin) + ".png");
    
    
	// Instantiate gameObjects

	help = new GameObject(*rootNode, "Help_ep2", PATH + "csd/Help_ep2.csb");
    help->setVisible(true);
    string basePhoneme = DataProvider::getInstance()->getCurrentDBKnowledgeBubble()->getPhoneme().c_str();
    
    
    auto basePhonemeImg = Sprite::create("common/images/letters/big_blue/"+basePhoneme+".png");
    help->getNode().getChildByName("Striscione_help_sound")->getChildByName("Ball_letter")->addChild(basePhonemeImg);
    
    auto initialPhonemeImg = Sprite::create("common/images/letters/big_blue/"+basePhoneme+"_initial.png");
    help->getNode().getChildByName("Striscione_help_sound")->getChildByName("Ball_initial")->addChild(initialPhonemeImg);
    
    auto medialPhonemeImg = Sprite::create("common/images/letters/big_blue/"+basePhoneme+"_medial.png");
    help->getNode().getChildByName("Striscione_help_sound")->getChildByName("Ball_medial")->addChild(medialPhonemeImg);
    
    auto finalPhonemeImg = Sprite::create("common/images/letters/big_blue/"+basePhoneme+"_final.png");
    help->getNode().getChildByName("Striscione_help_sound")->getChildByName("Ball_final")->addChild(finalPhonemeImg);
    
    
    
    
    
	helpHand = new GameObject(*rootNode, "HelpHand", PATH + "csd/HelpHand.csb");
	helpHand->setVisible(false);

	sema = new Sema(*rootNode, "Sema", PATH + "csd/Sema.csb", "sema_reference", _eventDispatcher, this);
	sema->setVisible(false);
    touchableGameObjects.push_back(sema); // commentare o meno questa linea per abilitare o meno il drag di sema !!!!
    

	semaTryagain = new GameObject(*rootNode, "Sema_tryagain", PATH + "csd/Sema_tryagain.csb");

	multiplicationBaloon = new MultiplicationBaloon(*rootNode, "FLBaloon");
    // set position for multiplicationBaloon
    
    float winHeight = cocos2d::Director::getInstance()->getWinSize().height;
    float rootHieght = rootNode->getBoundingBox().size.height;
    float y = 0;
    if ( winHeight < rootHieght ) {
        // CCLOG("like iphone");
        y = winHeight;
        y += 10;
    } else {
        // CCLOG("like ipad");
        float delta = (winHeight-rootHieght) / 2;
        y = rootHieght + delta;
        y -= 10;
    }
    y = y - (multiplicationBaloon->getNode().getBoundingBox().size.height /2);
    multiplicationBaloon->getNode().setPosition(Vec2(multiplicationBaloon->getNode().getPosition().x, y));
    
    ///---
	multiplicationBaloon->setFactors(multiplier);
	
	for (int index = 0; index < FRUIT_COUNT; ++index) {
		int tag = FRUITS_BASE_TAG + index;
		Fruit* fruit = new Fruit(
			*rootNode,
			Vec2(
				//_director->getWinSize().width / 2 - _director->getWinSize().width / 4 + index * _director->getWinSize().width / 4,
				//_director->getWinSize().width / 2 - (FRUIT_COUNT % 2 == 0 ? _director->getWinSize().width * (2.f * (FRUIT_COUNT + 1)),
				_director->getWinSize().width * (index + 1) / (FRUIT_COUNT + 1),
				_director->getWinSize().height + 200.f),
			_eventDispatcher,
			tag,
			this);
		fruit->setPhysicsActivated(false);
		fruits.insert(
			pair<int, Fruit*>(
				tag,
				fruit
				)
			);
	}
	//CCLOG("fruit size: %d", fruits.size());
	//assert(fruits.size() == 1);

	signboardPositive = new GameObject(*rootNode, "Signboard_positive", PATH + "csd/Signboard_positive.csb");
	signboardNegative = new GameObject(*rootNode, "Signboard_negative", PATH + "csd/Signboard_negative.csb");

	spiral = new GameObject(*(sema->getNode().getChildByName("Spirale")->getChildByName("Spirale")), Vec2::ZERO, PATH + "csd/Spirale.csb");
	spiral->setVisible(false);

    // int skin = DataProvider::getInstance()->getSkin();
	for (int index = 0; index < MAX_LIFES; ++index) {
		lifesGameObjects[index] = new GameObject(
			*(multiplicationBaloon->getNode().getChildByName("RootBone")->getChildByName("Life" + StringUtility::toString(index + 1))),
			Vec2::ZERO,
			PATH + "csd/Life.csb");
        static_cast<Sprite*>((lifesGameObjects[index])->getChild("RootBone/Sprite"))->setTexture(PATH+"png/life/life_" +  StringUtility::toString(skin) + ".png");
	}
	
}

void FallingLettersEp2::fadeIn() {

	CCLOG("FallingLettersEp2 - Fade in");
	
    
	// Start fade in animations
    simpleAudioEngine->playEffect((PATH + "Audio/help_this_is_the_letter.mp3").c_str());
	help->play("help_1", [&]() {
        string basePhoneme = DataProvider::getInstance()->getCurrentDBKnowledgeBubble()->getPhoneme().c_str();
        simpleAudioEngine->playEffect(("common/audio/grandpa/phonemes/" + basePhoneme + ".mp3").c_str());
    help->play("help_2", [&]() {
        simpleAudioEngine->playEffect((PATH + "Audio/help_written_in_three.mp3").c_str());
    help->play("help_3", [&]() {
        
		rootNode->runAction(
			Sequence::create(
				DelayTime::create(1.f),
				CallFunc::create(
					[&]() {
						sema->setVisible(true);
                        simpleAudioEngine->playEffect((PATH + "Audio/help_collect_only_the_letter.mp3").c_str());
						simpleAudioEngine->playEffect((PATH + "Audio/SemaSale.wav").c_str());
						sema->play("Sema_start", [&]() {
							sema->play("Sema_standing", nullptr, true);
							simpleAudioEngine->playEffect((PATH + "Audio/cartello_entra.wav").c_str());
							multiplicationBaloon->play("baloon_show", [&]() {
								runAction(
									Sequence::create(
										CallFunc::create(
											[&]() {
												simpleAudioEngine->playEffect((PATH + "Audio/fruttini_vite.wav").c_str());
												lifesGameObjects[0]->play("life_A");
											}),
										DelayTime::create(0.25f),
										CallFunc::create(
											[&]() {
												simpleAudioEngine->playEffect((PATH + "Audio/fruttini_vite.wav").c_str());
												lifesGameObjects[1]->play("life_A");
											}),
										DelayTime::create(0.25f),
										CallFunc::create(
											[&]() {
												simpleAudioEngine->playEffect((PATH + "Audio/fruttini_vite.wav").c_str());
												lifesGameObjects[2]->play("life_A");
											}),
										DelayTime::create(0.25f),
										CallFunc::create(
											[&]() {
												simpleAudioEngine->playEffect((PATH + "Audio/fruttini_vite.wav").c_str());
												lifesGameObjects[3]->play("life_A");
											}),
										DelayTime::create(0.25f),
										CallFunc::create(
											[&]() {
												simpleAudioEngine->playEffect((PATH + "Audio/fruttini_vite.wav").c_str());
												lifesGameObjects[4]->play("life_A", [&]() {
													Game::enableTouch();
													scheduleUpdate();
													Game::showTutorial();
													startSendingFruits();
                                                    lifesGameObjects[4]->getActionTimeline()->clearLastFrameCallFunc();
												});
											}),
										nullptr
										)
									);
                                multiplicationBaloon->getActionTimeline()->clearLastFrameCallFunc(); // controllare..
							});
                            sema->getActionTimeline()->clearLastFrameCallFunc();
						});
					}),
				nullptr
				)
			);
            help->getActionTimeline()->clearLastFrameCallFunc(); // controllare..
		});
        });
        });
	

}

void FallingLettersEp2::showTutorial() {

	CCLOG("FallingLettersEp2 - Show tutorial");
	Game::enableTouch();

	// Start tutorial animation
	helpHand->setVisible(true);
	helpHand->play("hand_help_2", nullptr, true);
	helpHand->getNode().getChildByName("help_master")->getChildByName("Help_acc")->getChildByName("Help_acc_2")->runAction(FadeIn::create(0.5f));
    helpHand->getNode().getChildByName("help_master")->getChildByName("Help_acc_1")->getChildByName("Help_acc_1")->runAction(FadeIn::create(0.5f));

 
    runAction(Sequence::create(DelayTime::create(4.f), CallFunc::create([&](){
        
        helpHand->getNode().getChildByName("help_master")->getChildByName("Help_acc")->getChildByName("Help_acc_2")->runAction(FadeOut::create(0.5f));
        helpHand->getNode().getChildByName("help_master")->getChildByName("Help_acc_1")->getChildByName("Help_acc_1")->runAction(FadeOut::create(0.5f));

        runAction(Sequence::create(DelayTime::create(0.5f), CallFunc::create([&](){
            Game::hideTutorial();
        }),  NULL));
                                                                            
                                                                            
    }),  NULL));
    
}

void FallingLettersEp2::hideTutorial() {

	CCLOG("FallingLettersEp2 - Hide tutorial");

	// End tutorial animation
	helpHand->pause();
	helpHand->setVisible(false);

}

bool FallingLettersEp2::onTouchBegan(Touch* touch, Event* event) {

    // Manage the start of a touch event

	return true;

}

void FallingLettersEp2::onTouchMoved(Touch* touch, Event* event) {

	// Manage a touch event
}

void FallingLettersEp2::onTouchEnded(Touch* touch, Event* event) {

	// Manage the end of a touch event

}

void FallingLettersEp2::endGame() {

	CCLOG("FallingLettersEp2 - End game");

	// Manage end game and start fade out animations

	unscheduleUpdate();

	stopSendingFruits();

	sema->setTouchable(false);
	sema->getCollider()->setPhysicsActivated(false);
    //auto  dataProvider = DataProvider::getInstance();
	multiplicationBaloon->play(
		"baloon_gameover",
		[&]() {
			if (lifes > 0) {
                Logger::getInstance()->logEvent(NAME, Logger::WIN, "");
				signboardPositive->play("show", [&]() {
					sema->play("Sema_Happy");
					spiral->setVisible(true);
					simpleAudioEngine->playEffect((PATH + "Audio/feedPosSalsaChildren.wav").c_str());
					spiral->play("animation0", [&]() {
						simpleAudioEngine->playEffect((PATH + "Audio/welldone.mp3").c_str());
                        Logger::getInstance()->logEvent(NAME, Logger::CLOSE, "");
                        DataProvider::getInstance()->setGameCompleted("FallingLetters");
                        DataProvider::getInstance()->setWatchmanReaction(WatchmanScene::GOOD_REACTION);
						_director->replaceScene(TransitionFade::create(0.8, WatchmanScene::createScene(), Color3B(255, 255, 255)));
                        spiral->getActionTimeline()->clearLastFrameCallFunc();
					});
                    signboardPositive->getActionTimeline()->clearLastFrameCallFunc();
				});
			} else {
                Logger::getInstance()->logEvent(NAME, Logger::LOSE, "");
				simpleAudioEngine->playEffect((PATH + "Audio/SemaScende.wav").c_str());
				sema->play("Sema_gameover", [&]() {
					signboardNegative->play("show", [&]() {
						semaTryagain->play("Sema_tryagain", [&]() {
							simpleAudioEngine->playEffect((PATH + "Audio/tryagaing.mp3").c_str());
                            Logger::getInstance()->logEvent(NAME, Logger::CLOSE, "");
                            DataProvider::getInstance()->setWatchmanReaction(WatchmanScene::BAD_REACTION);
							_director->replaceScene(TransitionFade::create(0.8, WatchmanScene::createScene(), Color3B(255, 255, 255)));
                            semaTryagain->getActionTimeline()->clearLastFrameCallFunc();
                        });
                        signboardNegative->getActionTimeline()->clearLastFrameCallFunc();
                    });
                    sema->getActionTimeline()->clearLastFrameCallFunc();
                });
			}
            multiplicationBaloon->getActionTimeline()->clearLastFrameCallFunc();
		});

}

/*bool FallingLettersEp2::onContactBegin(PhysicsContact& contact) {

	CCLOG("FallingLettersEp2 - onContactBegin");

	//CCLOG("Contact %s", node->getName());

	return true;

}*/

void FallingLettersEp2::startSendingFruits() {

	CCLOG("FallingLettersEp2 - startSendingFruits");

	sendFruits = RepeatForever::create(
		Sequence::create(
			DelayTime::create(1.f),
			CallFunc::create(
				[&]() {
					map<int, Fruit*>::iterator iterator;
					Fruit* fruit;
					int iterations = 0;
					do {
						iterator = fruits.begin();
						std::advance(iterator, rand() % fruits.size());
						fruit = iterator->second;
						++iterations;
					} while (iterations < FRUIT_COUNT && fruit->isFalling());
					if (!fruit->isFalling()) {
						if (rand() % 3 == 0) {
                            // crea numero corretto
                            fruit->setNumber(multiplier);
						} else {
                            //crea numero errato
                            fruit->setNumber(-1);
						}
						
						fruit->startFalling();

					}
				}),
			nullptr
			)
		);
	rootNode->runAction(sendFruits);


	
}

void FallingLettersEp2::stopSendingFruits() {
	
	CCLOG("FallingLettersEp2 - stopSendingFruits");

	//Director::getInstance()->getActionManager()->pauseTarget(rootNode);
	//if (!sendFruits->isDone()) {
		rootNode->stopAction(sendFruits);
	//}
	for (map<int, Fruit*>::iterator iterator = fruits.begin(); iterator != fruits.end(); ++iterator) {
		//CCLOG("----------------------- Number: %d, falling: %d", (iterator->second->getNumber(), iterator->second->isFalling() ? "true" : "false"));
		if (iterator->second->isFalling()) {
			iterator->second->stopFalling(false);
		}
	}

}

void FallingLettersEp2::checkFruitNumber(int number) {

	CCLOG("FallingLettersEp2 - checkFruitNumber");
    

	stopSendingFruits();
	
    int numToGet = multiplier;
    
    CCLOG("-----qui controllo se ho preso il numero giusto!!   numero da prendere= %d    ..numero preso=  %d", numToGet, number);

    
	if (number == numToGet) {
        Logger::getInstance()->logEvent(NAME, Logger::CORRECT, "");
		simpleAudioEngine->playEffect((PATH + "Audio/cesto_corretto.wav").c_str());
		sema->play("Sema_OK", [&]() {
			sema->play("Sema_standing", nullptr, true);
            sema->getActionTimeline()->clearLastFrameCallFunc();
		});

		//++multiplier;
        multiplier = rand() % 6;
        CCLOG("------------------2-RAND multiplier = %d", multiplier);

		multiplicationBaloon->play("baloon_correct", [&]() {
			multiplicationBaloon->setFactors(multiplier);
            multiplicationBaloon->getActionTimeline()->clearLastFrameCallFunc();
        });
        phonemesToCollect--;
		if (phonemesToCollect < 1) { // prima c'era 10
			endGame();
		} else {
			startSendingFruits();
		}

	} else {
        
        if (lifes < 1) return;
        Logger::getInstance()->logEvent(NAME, Logger::WRONG, "");

		--lifes;
	
		simpleAudioEngine->playEffect((PATH + "Audio/cesto_sbagliato.wav").c_str());
		sema->play("Sema_error_A", [&]() {
			multiplicationBaloon->play("baloon_error", [&]() {
				simpleAudioEngine->playEffect((PATH + "Audio/error.wav").c_str());
				lifesGameObjects[lifes]->play("life_B", [&]() {
						if (lifes <= 0) {
							endGame();
						} else {
							startSendingFruits();
						}
                        lifesGameObjects[lifes]->getActionTimeline()->clearLastFrameCallFunc();
					});
                multiplicationBaloon->getActionTimeline()->clearLastFrameCallFunc();
			});
			sema->play("Sema_error_B", [&]() {
				sema->play("Sema_standing", nullptr, true);
                sema->getActionTimeline()->clearLastFrameCallFunc();
			});
		});

	}

}

void FallingLettersEp2::update(float dt) {

	static const float ACCELERATION_SCALE = 15000.f;
	static const float DUMPING = 0.9f;
	static const float MAX_SPEED = 4000.f;

	// CCLOG("FallingLettersEp2 - update");

	//float windowWidth = Director::getInstance()->getWinSize().width;
	float x = sema->getLocalPosition().x;
    
    int semaWidth = static_cast<Sprite*>( sema->getNode().getChildByName("sema_reference") )->getBoundingBox().size.width;
    float minX = semaWidth/2;
    float maxX = Director::getInstance()->getWinSize().width - semaWidth/2;
    
    
    if ( (x >= minX) &&  (x <= maxX) ) {
        
        sema->setVelocity(sema->getVelocity() + sema->getAcceleration() * ACCELERATION_SCALE * dt);
        
        if (std::abs(sema->getVelocity().x) > MAX_SPEED) {
            sema->setVelocity(Vec2((sema->getVelocity().x >= 0.f ? 1.f : -1.f) * MAX_SPEED, 0.f));
        }
        sema->setVelocity(sema->getVelocity() * DUMPING);
        sema->setLocalPosition(sema->getLocalPosition() + sema->getVelocity() * dt);
    }else {
        sema->setVelocity(Vec2::ZERO);
        if (x >= maxX)  {
            sema->setLocalPosition(Vec2(maxX, 0));
        }
        if (x <= minX)  {
            sema->setLocalPosition(Vec2(minX, 0));
        }
        
    }
    
}

void FallingLettersEp2::homeButtonPressed() {
    Logger::getInstance()->logEvent("FallingLetters", Logger::CLOSE, "");
    auto  dataProvider = DataProvider::getInstance();
    
    if ( TEST_ENABLED ) {
        DataProvider::getInstance()->setGameCompleted("FallingLetters");
        DataProvider::getInstance()->setWatchmanReaction(WatchmanScene::GOOD_REACTION);
    } else {
        DataProvider::getInstance()->setWatchmanReaction(WatchmanScene::BAD_REACTION);
    }
}
