#include "ShapesGame.h"
#include <algorithm>    // std::random_shuffle
#include "../Utils/StringUtility.h"
#include "../Utils/Data/Logger.h"
#include "../Utils/Data/DataProvider.h"
#include "../WatchmanScene/WatchmanScene.h"
#include "../AppMacros.h"

template<> const bool kukua::Game<ShapesGame>::USE_PHYSICS = false;										// Enable/disable physics
template<> const bool kukua::Game<ShapesGame>::ENABLE_TOUCH = true;										// Used to disable tutorial on first touch and manage general touch events
template<> string kukua::Game<ShapesGame>::PATH = "ShapesGame/";									// Resources' subfolder path for this game
template<> const string kukua::Game<ShapesGame>::BACKGROUND_MUSIC_FILENAME = "backgroundMusic.wav";		// Background music filename
template<> bool kukua::Game<ShapesGame>::SHOWN_TUTORIAL = false;										// Used for showing tutorial on first execution, set to true only if tutorial is not needed
template<> Scene* kukua::Game<ShapesGame>::scene = nullptr;
template<> const string kukua::Game<ShapesGame>::NAME = "ShapeNaming";

ShapesGame::~ShapesGame() {

	CCLOG("~ShapesGame");

	// Delete objects created with new
	delete help;
	delete helpHand;
	delete hill;
	delete palm;
	delete gorilla;
	for (vector<Biscuit*>::iterator iterator = biscuits.begin(); iterator != biscuits.end(); ++iterator) {
		delete (*iterator);
	}
	delete spiral;
	delete semaWellDone;
	delete semaTryAgain;
	for (vector<GameObject*>::iterator iterator = backDrops.begin(); iterator != backDrops.end(); ++iterator) {
		delete (*iterator);
	}
	for (vector<GameObject*>::iterator iterator = frontDrops.begin(); iterator != frontDrops.end(); ++iterator) {
		delete (*iterator);
	}
	for (vector<GameObject*>::iterator iterator = hungryIcons.begin(); iterator != hungryIcons.end(); ++iterator) {
		delete (*iterator);
	}
	
}

void ShapesGame::initVariables() {

	CCLOG("ShapesGame - Init variables");

    score = 100;
    
    dataProvider = DataProvider::getInstance();
    string currentPhoneme = dataProvider->getCurrentDBKnowledgeBubble()->getPhoneme();
    vector<string> wordsVector = dataProvider->getWordsForGame( currentPhoneme, "shapeNaming" );
    requestedSymbol =  wordsVector.at(0);
    
    
    
    if (requestedSymbol == "circle")        requestedShape = Biscuit::Shape::CIRCLE;
    else if (requestedSymbol == "triangle") requestedShape = Biscuit::Shape::TRIANGLE;
    else if (requestedSymbol == "square")   requestedShape = Biscuit::Shape::SQUARE;
    else if (requestedSymbol == "rectangle") requestedShape = Biscuit::Shape::RECTAGLE;
    else if (requestedSymbol == "trapezoid") requestedShape = Biscuit::Shape::TRAPEZE;
    else if (requestedSymbol == "rhombus")   requestedShape = Biscuit::Shape::RHOMBUS;
    else if (requestedSymbol == "pentagon") requestedShape = Biscuit::Shape::PENTA;
    else if (requestedSymbol == "hexagon")  requestedShape = Biscuit::Shape::HEXAGON;
    else if (requestedSymbol == "octagon")  requestedShape = Biscuit::Shape::HEXAGON;
    else if (requestedSymbol == "oval")         requestedShape = Biscuit::Shape::OVAL;
    else if (requestedSymbol == "parallelogram") requestedShape = Biscuit::Shape::PARALL;
    
    else  {
        requestedShape = Biscuit::Shape::CIRCLE;
    }
    
	CCLOG("requestedShape = %d", requestedShape);

	previousEatenBiscuits = 0;

	lifes = 3;

}

void ShapesGame::initAudio() {

	CCLOG("ShapesGame - Init audio");

	// Preload audio files
    simpleAudioEngine->preloadBackgroundMusic("common/audio/bg/GAME_5.mp3");
    simpleAudioEngine->playBackgroundMusic("common/audio/bg/GAME_5.mp3", true);
}

void ShapesGame::initGameObjects() {

	CCLOG("ShapesGame - Init objects");

	// Instantiate gameObjects

	help = new GameObject(*rootNode, "Help", PATH + "Help.csb");
	helpHand = new GameObject(*rootNode, "HelpHand", PATH + "HelpHand.csb");
	helpHand->setVisible(false);

    skin = dataProvider->getSkin();
    string skinStr = StringUtility::toString( skin );
    
    static_cast<Sprite*>(rootNode->getChildByName("Background"))->setTexture(PATH+"PNG/FONDALE/FONDALE_"+ skinStr +"/background_" + skinStr + ".jpg");
    
	hill = new GameObject(*rootNode, rootNode->getChildByName("HillRef")->getPosition(), PATH + "Hill_"+skinStr+".csb");
	hill->setVisible(false);

	palm = new GameObject(*rootNode, "Palm", PATH + "Palm.csb");
	palm->setVisible(false);

	gorilla = new Gorilla(*rootNode, rootNode->getChildByName("GorillaRef")->getPosition(), PATH + "Gorilla_"+skinStr+".csb", _eventDispatcher, this);
	touchableGameObjects.push_back(gorilla);
	gorilla->setVisible(false);

    
    createBiscuits();
    
	spiral = new GameObject(*rootNode, "Spiral", PATH + "Spiral.csb");
	spiral->setVisible(false);
	semaWellDone = new GameObject(*rootNode, "SemaWellDone", PATH + "SemaWellDone.csb");
	semaTryAgain = new GameObject(*rootNode, "SemaTryAgain", PATH + "SemaTryAgain.csb");

	Node* node;
    if (skin == 1) {
        // add drops
        for (int index = 0; (node = rootNode->getChildByName("BackDrop" + StringUtility::toString(index))) != nullptr; ++index) {
            backDrops.push_back(new GameObject(*rootNode, "BackDrop" + StringUtility::toString(index), PATH + "Drop.csb"));
        }
        for (int index = 0; (node = rootNode->getChildByName("FrontDrop" + StringUtility::toString(index))) != nullptr; ++index) {
            frontDrops.push_back(new GameObject(*rootNode, "FrontDrop" + StringUtility::toString(index), PATH + "Drop.csb"));
        }
    }
    
	for (int index = 0; (node = rootNode->getChildByName("HungryIcon" + StringUtility::toString(index))) != nullptr; ++index) {
		GameObject* hungryIcon = new GameObject(*rootNode, "HungryIcon" + StringUtility::toString(index), PATH + "HungryIcon.csb");
		hungryIcon->setVisible(true);
		hungryIcons.push_back(hungryIcon);
	}	

    //
   
    std::random_shuffle(biscuits.begin(), biscuits.end());
    
    float x = _director->getWinSize().width / 2 - 2 * 170.f;
    
    for (vector<Biscuit*>::iterator iterator = biscuits.begin(); iterator != biscuits.end(); ++iterator) {
        (*iterator)->reset(Vec2(x, 140.f));
        (*iterator)->setVisible(false);
        x += 170.f;
    }
    
    helpHand->bringToFront();
}

void ShapesGame::createBiscuits() {
    // forme disponibili
    
    vector<string> availableForms;
    availableForms.push_back("circle");
    availableForms.push_back("triangle");
    availableForms.push_back("square");
    availableForms.push_back("rectangle");
    availableForms.push_back("trapezoid");
    availableForms.push_back("rhombus");
    availableForms.push_back("pentagon");
    availableForms.push_back("hexagon");
    availableForms.push_back("octagon");
    availableForms.push_back("oval");
    availableForms.push_back("parallelogram");
    
    std::random_shuffle(availableForms.begin(), availableForms.end());
    
    createBiscuit(requestedSymbol, "BiscuitPos1");
    availableForms.erase(std::remove(availableForms.begin(), availableForms.end(), requestedSymbol), availableForms.end());
    
    createBiscuit(availableForms.back(), "BiscuitPos2");
    availableForms.pop_back();
    
    createBiscuit(availableForms.back(), "BiscuitPos3");
    availableForms.pop_back();
    
    createBiscuit(availableForms.back(), "BiscuitPos4");
    availableForms.pop_back();
    
    createBiscuit(availableForms.back(), "BiscuitPos5");
    availableForms.pop_back();
}

void ShapesGame::createBiscuit(string shape, string refPos) {
    
    string csbName = "CircleBiscuit";
    Biscuit::Shape biscuitShape = Biscuit::Shape::CIRCLE;
   
    if (shape == "circle")          csbName = "CircleBiscuit";
    else if (shape == "triangle")   csbName = "TriangleBiscuit";
    else if (shape == "square")     csbName = "SquareBiscuit";
    else if (shape == "rectangle")  csbName = "RectangleBiscuit";
    else if (shape == "trapezoid")  csbName = "TrapezeBiscuit";
    else if (shape == "rhombus")    csbName = "RomboBiscuit";
    else if (shape == "pentagon")   csbName = "PentaBiscuit";
    else if (shape == "hexagon")    csbName = "HexagonBiscuit";
    else if (shape == "octagon")    csbName = "OctagonBiscuit";
    else if (shape == "oval")       csbName = "OvalBiscuit";
    else if (shape == "parallelogram")  csbName = "ParalleloBiscuit";
    
    
    if (shape == "circle")          biscuitShape = Biscuit::Shape::CIRCLE;
    else if (shape == "triangle")   biscuitShape = Biscuit::Shape::TRIANGLE;
    else if (shape == "square")     biscuitShape = Biscuit::Shape::SQUARE;
    else if (shape == "rectangle")  biscuitShape = Biscuit::Shape::RECTAGLE;
    else if (shape == "trapezoid")  biscuitShape = Biscuit::Shape::TRAPEZE;
    else if (shape == "rhombus")    biscuitShape = Biscuit::Shape::RHOMBUS;
    else if (shape == "pentagon")   biscuitShape = Biscuit::Shape::PENTA;
    else if (shape == "hexagon")    biscuitShape = Biscuit::Shape::HEXAGON;
    else if (shape == "octagon")    biscuitShape = Biscuit::Shape::HEXAGON;
    else if (shape == "oval")       biscuitShape = Biscuit::Shape::OVAL;
    else if (shape == "parallelogram") biscuitShape = Biscuit::Shape::PARALL;
    
    
    
    Biscuit* biscuit = new Biscuit(*rootNode,  (rootNode->getChildByName(refPos))->getPosition() , PATH + csbName + ".csb", "RootBone/Sprite", _eventDispatcher, gorilla, biscuitShape);

    touchableGameObjects.push_back(biscuit);
    biscuit->setVisible(false);
    biscuits.push_back(biscuit);
    
}

void ShapesGame::fadeIn() {

	CCLOG("ShapesGame - Fade in");

	// Start fade in animations
	
	static const float FALL_TIME = 2.f;

	srand( static_cast<unsigned int>(time(NULL)));
	for (vector<GameObject*>::iterator iterator = backDrops.begin(); iterator != backDrops.end(); ++iterator) {
		float phase = rand() % 10;
		(*iterator)->play(
			RepeatForever::create(
				Sequence::create(
					DelayTime::create(FALL_TIME * phase / 10.f),
					MoveBy::create(FALL_TIME, Vec2(0.f, -1200.f)),
					//DelayTime::create(FALL_TIME * (10.f - phase) / 10.f),
					MoveBy::create(0.f, Vec2(0.f, 1200.f)),
					nullptr
					)
				)
			);
	}
	for (vector<GameObject*>::iterator iterator = frontDrops.begin(); iterator != frontDrops.end(); ++iterator) {
		float phase = rand() % 10;
		(*iterator)->play(
			RepeatForever::create(
				Sequence::create(
					DelayTime::create(FALL_TIME * phase / 10.f),
					MoveBy::create(FALL_TIME, Vec2(0.f, -1200.f)),
					//DelayTime::create(FALL_TIME * (10.f - phase) / 10.f),
					MoveBy::create(0.f, Vec2(0.f, 1200.f)),
					nullptr
					)
				)
			);
	}

	if (!SHOWN_TUTORIAL) {

		help->play("show", [&]() {
			hill->setVisible(true);
			hill->play("show", [&]() {
				hill->play("idle", nullptr, true);
                hill->getActionTimeline()->clearLastFrameCallFunc();
			});
            if (skin == 1) palm->setVisible(true);
			palm->play("show", [&]() {
				palm->play(
					RepeatForever::create(
						Sequence::create(
							CallFunc::create(
								[&]() {
									palm->play("idle", nullptr, true);
								}),
							DelayTime::create(6.f),
							CallFunc::create(
								[&]() {
									palm->play("drop", nullptr, true);
								}),
							DelayTime::create(1.f),
							nullptr
						)
					)
				);

				gorilla->setVisible(true);
				gorilla->play("Gorilla_arrivo", [&]() {
					gorilla->play("Gorilla_Idle", nullptr, true);
					runAction(
						Sequence::create(
							CallFunc::create(
								[&]() {
						biscuits[0]->setVisible(true);
						biscuits[0]->play("show");
					}),
							DelayTime::create(0.2f),
						CallFunc::create(
							[&]() {
						biscuits[1]->setVisible(true);
						biscuits[1]->play("show");
					}),
						DelayTime::create(0.2f),
						CallFunc::create(
							[&]() {
						biscuits[2]->setVisible(true);
						biscuits[2]->play("show");
					}),
						DelayTime::create(0.2f),
						CallFunc::create(
							[&]() {
						biscuits[3]->setVisible(true);
						biscuits[3]->play("show");
					}),
						DelayTime::create(0.2f),
						CallFunc::create(
							[&]() {
						biscuits[4]->setVisible(true);
						biscuits[4]->play("show");
					}),
						DelayTime::create(1.f), CallFunc::create(
							[&]() {
						hungryIcons[0]->setVisible(true);
						hungryIcons[0]->play("show");
					}),
						DelayTime::create(0.2f),
						CallFunc::create(
							[&]() {
						hungryIcons[1]->setVisible(true);
						hungryIcons[1]->play("show");
					}),
						DelayTime::create(0.2f),
						CallFunc::create(
							[&]() {
						hungryIcons[2]->setVisible(true);
						hungryIcons[2]->play("show");
					}),
						DelayTime::create(0.2f),
						CallFunc::create(
							[&]() {
						hungryIcons[3]->setVisible(true);
						hungryIcons[3]->play("show");
					}),
						DelayTime::create(0.2f),
						CallFunc::create(
							[&]() {
						hungryIcons[4]->setVisible(true);
						hungryIcons[4]->play("show");
					}),
						DelayTime::create(2.f),
						CallFunc::create(
							[&]() {
						gorilla->askBiscuit();
					}),
						DelayTime::create(2.f),
						CallFunc::create(
							[&]() {
						Game::showTutorial();
					}),
						nullptr
						)
						);
                    gorilla->getActionTimeline()->clearLastFrameCallFunc(); // controllare
                });
                palm->getActionTimeline()->clearLastFrameCallFunc(); // controllare
			});
            help->getActionTimeline()->clearLastFrameCallFunc();
		});
        
	} else {
	
		hill->setVisible(true);
			hill->play("show", [&]() {
				hill->play("idle", nullptr, true);
                hill->getActionTimeline()->clearLastFrameCallFunc();
			});
			if (skin == 1) palm->setVisible(true);
			palm->play("show", [&]() {
				palm->play(
					RepeatForever::create(
						Sequence::create(
							CallFunc::create(
								[&]() {
									palm->play("idle", nullptr, true);
								}),
							DelayTime::create(6.f),
							CallFunc::create(
								[&]() {
									palm->play("drop", nullptr, true);
								}),
							DelayTime::create(1.f),
							nullptr
							)
						)
					);

				gorilla->setVisible(true);
				gorilla->play("Gorilla_arrivo", [&]() {
					gorilla->play("Gorilla_Idle", nullptr, true);
					runAction(
						Sequence::create(
							CallFunc::create(
								[&]() {
						biscuits[0]->setVisible(true);
						biscuits[0]->play("show");
					}),
							DelayTime::create(0.2f),
						CallFunc::create(
							[&]() {
						biscuits[1]->setVisible(true);
						biscuits[1]->play("show");
					}),
						DelayTime::create(0.2f),
						CallFunc::create(
							[&]() {
						biscuits[2]->setVisible(true);
						biscuits[2]->play("show");
					}),
						DelayTime::create(0.2f),
						CallFunc::create(
							[&]() {
						biscuits[3]->setVisible(true);
						biscuits[3]->play("show");
					}),
						DelayTime::create(0.2f),
						CallFunc::create(
							[&]() {
						biscuits[4]->setVisible(true);
						biscuits[4]->play("show");
					}),
						DelayTime::create(1.f), CallFunc::create(
							[&]() {
						hungryIcons[0]->setVisible(true);
						hungryIcons[0]->play("show");
					}),
						DelayTime::create(0.2f),
						CallFunc::create(
							[&]() {
						hungryIcons[1]->setVisible(true);
						hungryIcons[1]->play("show");
					}),
						DelayTime::create(0.2f),
						CallFunc::create(
							[&]() {
						hungryIcons[2]->setVisible(true);
						hungryIcons[2]->play("show");
					}),
						DelayTime::create(0.2f),
						CallFunc::create(
							[&]() {
						hungryIcons[3]->setVisible(true);
						hungryIcons[3]->play("show");
					}),
						DelayTime::create(0.2f),
						CallFunc::create(
							[&]() {
						hungryIcons[4]->setVisible(true);
						hungryIcons[4]->play("show");
					}),
						DelayTime::create(2.f),
						CallFunc::create(
							[&]() {
						gorilla->askBiscuit();
					}),
						nullptr
						)
						);
                    gorilla->getActionTimeline()->clearLastFrameCallFunc();
				});
                palm->getActionTimeline()->clearLastFrameCallFunc();
			});
	}

}

void ShapesGame::showTutorial() {

	CCLOG("ShapesGame - Show tutorial");

	// Start tutorial animation
	helpHand->setVisible(true);
	helpHand->play("manina", nullptr, true);
	helpHand->getNode().getChildByName("RootBone")->getChildByName("Sprite")->runAction(FadeIn::create(0.25f));

}

void ShapesGame::hideTutorial() {

	CCLOG("ShapesGame - Hide tutorial");

	// End tutorial animation
	helpHand->getNode().getChildByName("RootBone")->getChildByName("Sprite")->runAction(
		Sequence::createWithTwoActions(
			FadeOut::create(0.25f),
			CallFunc::create(
				[&]() {
					helpHand->setVisible(false);	
				})
			)
		);

}

bool ShapesGame::onTouchBegan(Touch* touch, Event* event) {

	return true;

}

void ShapesGame::onTouchMoved(Touch* touch, Event* event) {

}

void ShapesGame::onTouchEnded(Touch* touch, Event* event) {

}

void ShapesGame::endGame(bool gameOver) {

	CCLOG("ShapesGame - End game");

	// Manage end game and start fade out animations

	disableTouch();

	for (vector<Biscuit*>::iterator iterator = biscuits.begin(); iterator != biscuits.end(); ++iterator) {
		(*iterator)->fadeOut(0.25f);
	}

	if (!gameOver) {
        
        Logger::getInstance()->logEvent(NAME, Logger::WIN, "");
        
		hungryIcons[4]->play("on");

		gorilla->play("Goril_FeedOK", nullptr, true);

		spiral->setVisible(true);
		spiral->play("show", [&]() {
			spiral->play("loop", nullptr, true);
			spiral->getActionTimeline()->clearLastFrameCallFunc();
		});

		runAction(
			Sequence::create(
				DelayTime::create(1.f),
				CallFunc::create(
					[&]() {
						semaWellDone->play("Well_Apparizione");
					}),
				DelayTime::create(2.f),
				CallFunc::create(
					[&]() {
						semaWellDone->play("Well_Sparizione", [&]() {
                            simpleAudioEngine->stopBackgroundMusic();
                            Logger::getInstance()->logEvent(NAME, Logger::CLOSE, "");
                            dataProvider->setGameCompleted(NAME, score);
                            dataProvider->setWatchmanReaction(WatchmanScene::GOOD_REACTION);
                            _director->replaceScene(TransitionFade::create(TRANSITION_TIME, WatchmanScene::createScene(), TRANSITION_COLOR));
                            semaWellDone->getActionTimeline()->clearLastFrameCallFunc();
						});
					}),
				/*DelayTime::create(2.f),
				CallFunc::create(
					[&]() {
						
					}),*/
				nullptr
				)
			);

	} else {
		
        Logger::getInstance()->logEvent(NAME, Logger::LOSE, "");
        
		runAction(
			Sequence::create(
				DelayTime::create(1.f),
				CallFunc::create(
					[&]() {
						semaTryAgain->play("Try_Apparizione");
					}),
				DelayTime::create(2.f),
				CallFunc::create(
					[&]() {
						semaTryAgain->play("Try_Sparizione", [&]() {
                            simpleAudioEngine->stopBackgroundMusic();
                            Logger::getInstance()->logEvent(NAME, Logger::CLOSE, "");
                            dataProvider->setWatchmanReaction(WatchmanScene::BAD_REACTION);
                            _director->replaceScene(TransitionFade::create(TRANSITION_TIME, WatchmanScene::createScene(), TRANSITION_COLOR));
                            semaTryAgain->getActionTimeline()->clearLastFrameCallFunc();
						});
					}),
				nullptr
			)
		);
		

	}
	
}

void ShapesGame::resetBiscuits() {

	static const float X_OFFSET = 170.f;
	static const float Y = 140.f;

	std::random_shuffle(biscuits.begin(), biscuits.end());

	float x = _director->getWinSize().width / 2 - 2 * X_OFFSET;
	
	if (gorilla->getEatenBiscuits() == 0) {
		--lifes;
		runAction(
			Sequence::create(
				CallFunc::create(
					[&]() {
						if (previousEatenBiscuits > 4) {
							hungryIcons[4]->play("off");
						}
					}),
				DelayTime::create(0.2f),
				CallFunc::create(
					[&]() {
						if (previousEatenBiscuits > 3) {
							hungryIcons[3]->play("off");
						}
					}),
				DelayTime::create(0.2f),
				CallFunc::create(
					[&]() {
						if (previousEatenBiscuits > 2) {
							hungryIcons[2]->play("off");
						}
					}),
				DelayTime::create(0.2f),
				CallFunc::create(
					[&]() {
						if (previousEatenBiscuits > 1) {
							hungryIcons[1]->play("off");
						}
					}),
				DelayTime::create(0.2f),
				CallFunc::create(
					[&]() {
						if (previousEatenBiscuits > 0) {
							hungryIcons[0]->play("off");
						}
						previousEatenBiscuits = gorilla->getEatenBiscuits();
					}),
				nullptr
				)
			);
		if (lifes >= 0) {
			for (vector<Biscuit*>::iterator iterator = biscuits.begin(); iterator != biscuits.end(); ++iterator) {
				(*iterator)->reset(Vec2(x, Y));
				x += X_OFFSET;
			}
			runAction(
				Sequence::create(
					DelayTime::create(2.f),
					CallFunc::create(
						[&]() {
							//enableTouch();
							gorilla->askBiscuit();
						}),
					DelayTime::create(1.5f),
					CallFunc::create(
						[&]() {
							for (vector<Biscuit*>::iterator iterator = biscuits.begin(); iterator != biscuits.end(); ++iterator) {
								(*iterator)->fadeIn(0.25f);
							}
						}),
					nullptr
					)
				);
		} else {
			Game::endGame(true);
		}
	} else {
		for (vector<Biscuit*>::iterator iterator = biscuits.begin(); iterator != biscuits.end(); ++iterator) {
			(*iterator)->reset(Vec2(x, Y));
			x += X_OFFSET;
		}
		hungryIcons[gorilla->getEatenBiscuits() - 1]->play("on");
		previousEatenBiscuits = gorilla->getEatenBiscuits();
		runAction(
			Sequence::create(
				DelayTime::create(2.f),
				CallFunc::create(
					[&]() {
						//enableTouch();
						gorilla->askBiscuit();
					}),
				DelayTime::create(1.5f),
				CallFunc::create(
					[&]() {
						for (vector<Biscuit*>::iterator iterator = biscuits.begin(); iterator != biscuits.end(); ++iterator) {
							(*iterator)->fadeIn(0.25f);
						}
					}),				
				nullptr
				)
			);
	}

}

void ShapesGame::homeButtonPressed() {
    
    Logger::getInstance()->logEvent(NAME, Logger::CLOSE, "");
    if ( TEST_ENABLED ) {
        dataProvider->setGameCompleted(NAME);
        dataProvider->setWatchmanReaction(WatchmanScene::GOOD_REACTION);
    } else {
        dataProvider->setWatchmanReaction(WatchmanScene::BAD_REACTION);
    }
    _director->replaceScene(TransitionFade::create(TRANSITION_TIME, WatchmanScene::createScene(), TRANSITION_COLOR));
}
