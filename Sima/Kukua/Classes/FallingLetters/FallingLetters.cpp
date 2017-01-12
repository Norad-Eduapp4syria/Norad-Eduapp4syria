#include "FallingLetters.h"
#include "FLFruit.h"

#include <time.h>
#include <iterator>
#include "../Utils/StringUtility.h"
#include "../Utils/Data/Logger.h"

template<> const bool kukua::Game<FallingLetters>::USE_PHYSICS = true;										// Enable/disable physics
template<> const bool kukua::Game<FallingLetters>::ENABLE_TOUCH = true;										// Used to disable tutorial on first touch and manage general touch events
template<> string kukua::Game<FallingLetters>::PATH = "FallingLetters/";							// Resources' subfolder path for this game
template<> const string kukua::Game<FallingLetters>::BACKGROUND_MUSIC_FILENAME = "";		// Background music filename
template<> bool kukua::Game<FallingLetters>::SHOWN_TUTORIAL = false;										// Used for showing tutorial on first execution, set to true only if tutorial is not needed
template<> Scene* kukua::Game<FallingLetters>::scene = nullptr;
const int FallingLetters::FRUITS_BASE_TAG = 1000;
template<> const string kukua::Game<FallingLetters>::NAME = "FallingLetters";

FallingLetters::~FallingLetters() {

	CCLOG("~FallingLetters");

	// Delete objects created with new
	delete help;
	delete helpLabel;
	delete helpHand;
	delete sema;
	delete semaTryagain;
	delete flBaloon;
	delete signboardPositive;
	delete signboardNegative;
	delete spiral;

	for (map<int, FLFruit*>::iterator iterator = fruits.begin(); iterator != fruits.end(); ++iterator) {
		delete iterator->second;
	}

	for (int index = 0; index < MAX_LIFES; ++index) {
		delete lifesGameObjects[index];
	}

}

void FallingLetters::initVariables() {

	CCLOG("FallingLetters - Init variables");

	//auto scene = _director->getRunningScene();
	scene->getPhysicsWorld()->setGravity(scene->getPhysicsWorld()->getGravity() * 1.75f);

	srand( static_cast<unsigned int>(time(NULL)));
    string phonemeOk = DataProvider::getInstance()->getCurrentDBKnowledgeBubble()->getPhoneme();
    

    int currentEp = DataProvider::getInstance()->getCurrentEpisode();
    if (currentEp == 3) {
        phonemeOk = phonemeOk.substr(0, phonemeOk.find("#"));
        phonemeOk = phonemeOk + "_i";
    }
    if (currentEp == 2) {
        int random123 = rand() % 3 + 1;
        if (random123 == 1) phonemeOk = phonemeOk + "_initial";
        else if (random123 == 2) phonemeOk = phonemeOk + "_medial";
        else phonemeOk = phonemeOk + "_final";
    }
    
    letterToGet = DataProvider::getInstance()->checkAndCorrectDuplicatePhoneme(phonemeOk);//rand() % 10 + 1;
    
    
    
    CCLOG("............letterToGet %s", letterToGet.c_str());
    
	lifes = MAX_LIFES;
    matchCounter = 0;

    int skin = DataProvider::getInstance()->getSkin();
    static_cast<Sprite*>(rootNode->getChildByName("Background"))->setTexture(PATH+"png/background/background_" +  StringUtility::toString(skin) + ".png");
    
}

void FallingLetters::initAudio() {

	CCLOG("FallingLetters - Init audio");

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

void FallingLetters::initGameObjects() {

	CCLOG("FallingLetters - Init objects");

	// Instantiate gameObjects
    
	help = new GameObject(*rootNode, "Help", PATH + "csd/Help.csb");
	helpLabel = new LabelGameObject(*(help->getNode().getChildByName("RootBone")->getChildByName("NumberParentBone")->getChildByName("NumberBone")), Vec2::ZERO, "common/fonts/Arabic-Regular.ttf", 400, letterToGet, Color3B(47, 109, 182));

	helpHand = new GameObject(*rootNode, "HelpHand", PATH + "csd/HelpHand.csb");
	helpHand->setVisible(false);

	sema = new FLSema(*rootNode, "Sema", PATH + "csd/Sema.csb", "sema_reference", _eventDispatcher, this);
	sema->setVisible(false);
	touchableGameObjects.push_back(sema); // set sema as draggable

	semaTryagain = new GameObject(*rootNode, "Sema_tryagain", PATH + "csd/Sema_tryagain.csb");

	flBaloon = new FLBaloon(*rootNode, "FLBaloon");
	flBaloon->setFactors(letterToGet);
	
	for (int index = 0; index < FRUIT_COUNT; ++index) {
		int tag = FRUITS_BASE_TAG + index;
		FLFruit* fruit = new FLFruit(
			*rootNode,
			Vec2(
				_director->getWinSize().width * (index + 1) / (FRUIT_COUNT + 1),
				_director->getWinSize().height + 200.f),
			_eventDispatcher,
			tag,
			this);
		fruit->setPhysicsActivated(false);
		fruits.insert(
			pair<int, FLFruit*>(
				tag,
				fruit
				)
			);
	}
	//CCLOG("fruit size: %lu", fruits.size());


	signboardPositive = new GameObject(*rootNode, "Signboard_positive", PATH + "csd/Signboard_positive.csb");
	signboardNegative = new GameObject(*rootNode, "Signboard_negative", PATH + "csd/Signboard_negative.csb");

	spiral = new GameObject(*(sema->getNode().getChildByName("Spirale")->getChildByName("Spirale")), Vec2::ZERO, PATH + "csd/Spirale.csb");
	spiral->setVisible(false);
    int skin = DataProvider::getInstance()->getSkin();
	for (int index = 0; index < MAX_LIFES; ++index) {
		lifesGameObjects[index] = new GameObject(
			*(flBaloon->getNode().getChildByName("RootBone")->getChildByName("Life" + StringUtility::toString(index + 1))),
			Vec2::ZERO,
			PATH + "csd/Life.csb");
        
        static_cast<Sprite*>((lifesGameObjects[index])->getChild("RootBone/Sprite"))->setTexture(PATH+"png/life/life_" +  StringUtility::toString(skin) + ".png");
	}
	
}

void FallingLetters::fadeIn() {

	CCLOG("FallingLetters - Fade in");
	
	// Start fade in animations

	help->play("Help", [&]() {
		rootNode->runAction(
			Sequence::create(
				//DelayTime::create(1.f),
				CallFunc::create(
					[&]() {
						sema->setVisible(true);
						simpleAudioEngine->playEffect((PATH + "Audio/SemaSale.wav").c_str());
						sema->play("Sema_start", [&]() {
							sema->play("Sema_standing", nullptr, true);
							simpleAudioEngine->playEffect((PATH + "Audio/cartello_entra.wav").c_str());
							flBaloon->play("baloon_show", [&]() {
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
                                flBaloon->getActionTimeline()->clearLastFrameCallFunc(); // controllare..
							});
                            sema->getActionTimeline()->clearLastFrameCallFunc();
						});
					}),
				nullptr
				)
			);
            help->getActionTimeline()->clearLastFrameCallFunc(); // controllare..
		});
	

}

void FallingLetters::showTutorial() {

	CCLOG("FallingLetters - Show tutorial");
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

void FallingLetters::hideTutorial() {

	CCLOG("FallingLetters - Hide tutorial");

	// End tutorial animation
	helpHand->pause();
	helpHand->setVisible(false);

}

bool FallingLetters::onTouchBegan(Touch* touch, Event* event) {

	return true;

}

void FallingLetters::onTouchMoved(Touch* touch, Event* event) {

}

void FallingLetters::onTouchEnded(Touch* touch, Event* event) {

}

void FallingLetters::endGame() {

	CCLOG("FallingLetters - End game");

	// Manage end game and start fade out animations

	unscheduleUpdate();

	stopSendingFruits();

	sema->setTouchable(false);
	sema->getCollider()->setPhysicsActivated(false);

	flBaloon->play(
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
            flBaloon->getActionTimeline()->clearLastFrameCallFunc();
		});

}

/*bool FallingLetters::onContactBegin(PhysicsContact& contact) {

	CCLOG("FallingLetters - onContactBegin");

	return true;

}*/

void FallingLetters::startSendingFruits() {

	CCLOG("FallingLetters - startSendingFruits");

	sendFruits = RepeatForever::create(
		Sequence::create(
			DelayTime::create(1.f),
			CallFunc::create(
				[&]() {
					CCLOG("SEND_FRUITS");
					map<int, FLFruit*>::iterator iterator;
					FLFruit* fruit;
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
                            fruit->setLetter(letterToGet);
                        } else {
                            //crea numero errato
                            string phonemeKo = DataProvider::getInstance()->getRandomWrongPhoneme(letterToGet);
                            string phonemeKoToShow = DataProvider::getInstance()->checkAndCorrectDuplicatePhoneme(phonemeKo);
                            fruit->setLetter(phonemeKoToShow);
                        }
                        
                        fruit->startFalling();
                        
                    }
				}),
			nullptr
			)
		);
	rootNode->runAction(sendFruits);

	CCLOG("C0");


	/*stopSendingFruits();

	Director::getInstance()->getActionManager()->resumeTarget(rootNode);*/
	
}

void FallingLetters::stopSendingFruits() {
	
	CCLOG("FallingLetters - stopSendingFruits");

	//Director::getInstance()->getActionManager()->pauseTarget(rootNode);
	//if (!sendFruits->isDone()) {
		rootNode->stopAction(sendFruits);
	//}
	for (map<int, FLFruit*>::iterator iterator = fruits.begin(); iterator != fruits.end(); ++iterator) {
		if (iterator->second->isFalling()) {
			iterator->second->stopFalling(false);
		}
	}

}

void FallingLetters::checkFruitLetter(string letter) {

	CCLOG("FallingLetters - checkFruitLetter");

	stopSendingFruits();
	
    CCLOG("letter = %s", letter.c_str());
    CCLOG("letterToGet = %s", letterToGet.c_str());
    
	if (letter == letterToGet) {
        Logger::getInstance()->logEvent(NAME, Logger::CORRECT, "");
		simpleAudioEngine->playEffect((PATH + "Audio/cesto_corretto.wav").c_str());
		sema->play("Sema_OK", [&]() {
			sema->play("Sema_standing", nullptr, true);
            sema->getActionTimeline()->clearLastFrameCallFunc();
		});

		matchCounter++;

		flBaloon->play("baloon_correct", [&]() {
			flBaloon->setFactors(letterToGet);
            flBaloon->getActionTimeline()->clearLastFrameCallFunc();
        });

		if (matchCounter > 5) {
			endGame();
		} else {
			startSendingFruits();
		}

	} else {
        
        if (lifes < 1) return;
        Logger::getInstance()->logEvent(NAME, Logger::WRONG, "");
		lifes--;
 
        //substract score
        scorePercent -= scoreToSubtract;
        CCLOG("lo score ora vale %f", scorePercent);

		simpleAudioEngine->playEffect((PATH + "Audio/cesto_sbagliato.wav").c_str());
		sema->play("Sema_error_A", [&]() {
			flBaloon->play("baloon_error", [&]() {
				simpleAudioEngine->playEffect((PATH + "Audio/error.wav").c_str());
				lifesGameObjects[lifes]->play("life_B", [&]() {
						if (lifes <= 0) {
							endGame();
						} else {
							startSendingFruits();
						}
                        lifesGameObjects[lifes]->getActionTimeline()->clearLastFrameCallFunc();
					});
                flBaloon->getActionTimeline()->clearLastFrameCallFunc();
			});
			sema->play("Sema_error_B", [&]() {
				sema->play("Sema_standing", nullptr, true);
                sema->getActionTimeline()->clearLastFrameCallFunc();
			});
		});

	}

}

void FallingLetters::update(float dt) {

	static const float ACCELERATION_SCALE = 15000.f;
	static const float DUMPING = 0.9f;
	static const float MAX_SPEED = 4000.f;

	// CCLOG("FallingLetters - update");

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
    
    /*
	if (x >= windowWidth / (FallingLetters::FRUIT_COUNT + 1) || x <= windowWidth * FallingLetters::FRUIT_COUNT / (FallingLetters::FRUIT_COUNT + 1)) {
		sema->setVelocity(sema->getVelocity() + sema->getAcceleration() * ACCELERATION_SCALE * dt);
	} else if (x < windowWidth / (FallingLetters::FRUIT_COUNT + 1)) {
		sema->setVelocity(
			sema->getAcceleration().x < 0 ? Vec2(std::abs(sema->getVelocity().x), 0.f) : sema->getVelocity() + sema->getAcceleration() * ACCELERATION_SCALE * dt
			);
	} else if (x > windowWidth * FallingLetters::FRUIT_COUNT / (FallingLetters::FRUIT_COUNT + 1)) {
		sema->setVelocity(
			sema->getAcceleration().x > 0 ? -Vec2(std::abs(sema->getVelocity().x), 0.f) : sema->getVelocity() + sema->getAcceleration() * ACCELERATION_SCALE * dt
			);
	}
	if (std::abs(sema->getVelocity().x) > MAX_SPEED) {
		sema->setVelocity(Vec2((sema->getVelocity().x >= 0.f ? 1.f : -1.f) * MAX_SPEED, 0.f));
	}
	sema->setVelocity(sema->getVelocity() * DUMPING);
	sema->setLocalPosition(sema->getLocalPosition() + sema->getVelocity() * dt);
    */
}

void FallingLetters::homeButtonPressed() {
    Logger::getInstance()->logEvent("FallingLetters", Logger::CLOSE, "");
    if ( TEST_ENABLED ) {
        DataProvider::getInstance()->setGameCompleted("FallingLetters");
        DataProvider::getInstance()->setWatchmanReaction(WatchmanScene::GOOD_REACTION);
    } else {
        DataProvider::getInstance()->setWatchmanReaction(WatchmanScene::BAD_REACTION);
    }
}
