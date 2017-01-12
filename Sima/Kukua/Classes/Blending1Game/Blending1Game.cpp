#include "Blending1Game.h"
#include "MouthButton.h"
#include "BoxButton.h"
#include "Cannon.h"
#include "Box.h"
#include "WoodenBox.h"
#include "FeedbackSignboard.h"
#include "../Utils/Data/ArabicHelper.h"
#include "../Utils/StringUtility.h"
#include "../Utils/Data/DataProvider.h"
#include "../AppMacros.h"
#include <utility>
#include <algorithm>
using namespace std;


template<> const bool kukua::Game<Blending1Game>::USE_PHYSICS = true;										// Enable/disable physics
template<> const bool kukua::Game<Blending1Game>::ENABLE_TOUCH = true;										// Used to disable tutorial on first touch and manage general touch events
//template<> string kukua::Game<Blending1Game>::PATH = "Blending1Game/";								// Resources' subfolder path for this game
template<> string kukua::Game<Blending1Game>::PATH = "Blending1Game/skin_" + StringUtility::toString( DataProvider::getInstance()->getSkin() ) + "/";
const string Blending1Game::PATH_AUDIO = "Blending1Game/";

template<> const string kukua::Game<Blending1Game>::BACKGROUND_MUSIC_FILENAME = "";				// Background music filename
template<> bool kukua::Game<Blending1Game>::SHOWN_TUTORIAL = false;											// Used for showing tutorial on first execution, set to true only if tutorial is not needed
bool Blending1Game::SHOWN_AIM_TUTORIAL = false;
bool Blending1Game::SHOWN_SHOT_TUTORIAL = false;
template<> Scene* kukua::Game<Blending1Game>::scene = nullptr;
template<> const string kukua::Game<Blending1Game>::NAME = "Blending1Game";
int Blending1Game::NUM_WORDS;

Blending1Game::~Blending1Game() {

	CCLOG("~Blending1Game");

	// Delete objects created with new
	delete help;

	//delete mouthButton;

	/*delete boxButton1;
	delete boxButton2;
	delete boxButton3;*/
	for (vector<BoxButton*>::iterator iterator = boxButtons.begin(); iterator != boxButtons.end(); ++iterator) {
		delete (*iterator);
	}

	delete cannon;

	delete leftHill;
	delete rightHill;

	delete aimHelpHand;
	delete shotHelpHand;
	
	/*delete woodenBox;
	delete yellowLetterBox;
	delete redLetterBox;
	delete blueLetterBox;*/

	for (vector<WoodenBox*>::iterator iterator = woodenBoxes.begin(); iterator != woodenBoxes.end(); ++iterator) {
		delete (*iterator);
	}
	for (vector<LetterBox*>::iterator iterator = yellowLetterBoxes.begin(); iterator != yellowLetterBoxes.end(); ++iterator) {
		delete (*iterator);
	}
	for (vector<LetterBox*>::iterator iterator = redLetterBoxes.begin(); iterator != redLetterBoxes.end(); ++iterator) {
		delete (*iterator);
	}
	for (vector<LetterBox*>::iterator iterator = blueLetterBoxes.begin(); iterator != blueLetterBoxes.end(); ++iterator) {
		delete (*iterator);
	}

	for (vector<GameObject*>::iterator iterator = lifeGameObjects.begin(); iterator != lifeGameObjects.end(); ++iterator) {
		delete (*iterator);
	}

	delete tatuTryAgain;

	delete feedbackSignboard;

}

vector<string> Blending1Game::split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

void Blending1Game::initVariables() {

	CCLOG("Blending1Game - Init variables");
	scene->getPhysicsWorld()->setGravity(Vec2(0.f, -300.f));

	showingAimTutorial = false;
	showingShotTutorial = false;
	
    /////////
	
    vector<string> wordsVector = DataProvider::getInstance()->getVectorWordsForGame();
    /*
    for (vector<string>::iterator iterator = wordsVector.begin(); iterator != wordsVector.end(); ++iterator) {
        //    (*iterator)
        CCLOG("parole = %s", (*iterator).c_str() );
    }
    */
    if ( wordsVector.empty() ) {
        CCLOG("ho finito...devo tornare al watchman.. non dovrebbe mai succedere");
        return;
    }
    string wordToSplit = wordsVector.back(); // get the last word
    
    // controllo se wordToSplit contiene ONLYAUDIO
    justAudio = false;
    string::size_type justAudioStrCheck = wordToSplit.find("ONLYAUDIO");
    if (justAudioStrCheck != string::npos) {
        justAudio = true;
        wordToSplit.erase(justAudioStrCheck, 9); // 9 is length of "ONLYAUDIO"
    }
        
    CCLOG("Start - wordToSplit = %s", wordToSplit.c_str());
    
    
    wordToSplit = ArabicHelper::getInstance()->getInArabic(wordToSplit);
  
    CCLOG("wordToSplit = %s", wordToSplit.c_str());
    
    vector<string> wordsVectorSplitted = split(wordToSplit, '#');
    
    word = "";
    int idx;
    
   
    
    for (idx = 0; idx< wordsVectorSplitted.size(); idx++ ) { // sarebbe meglio usare un iterator
        word.append( wordsVectorSplitted.at(idx) );
        correctPhonemes.push_back( wordsVectorSplitted.at(idx) );
    }
    CCLOG("word = %s", word.c_str());
    
    
    wordAudioFilename = ArabicHelper::getInstance()->getFilenameInEnglish( word );
    CCLOG("================== wordAudioFilename =================== %s", wordAudioFilename.c_str());

  // originalmente....
	/*word = "cat";
    
	correctPhonemes.push_back("c");
	correctPhonemes.push_back("a");
	correctPhonemes.push_back("t");*/
    
    
    
    
	// Choose random colors for each correct phoneme
	srand( static_cast<unsigned int>(time(NULL)));
	for (int index = 0; index < correctPhonemes.size(); ++index) {
	
        LetterBox::Color color;

		switch (index % 3) {
		case 1:
			do {
				color = static_cast<LetterBox::Color>(rand() % 3);
			} while (color == correctPhonemesColors.at(index - 1));
			break;
		case 2:
			do {
				color = static_cast<LetterBox::Color>(rand() % 3);
			} while (color == correctPhonemesColors.at(index - 1) || color == correctPhonemesColors.at(index - 2));
			break;
		case 0:
		default:
			color = static_cast<LetterBox::Color>(rand() % 3);
			break;
		}

		correctPhonemesColors.push_back(color);
	}

    /*
     wrongPhonemes.push_back("x");
     wrongPhonemes.push_back("y");
     wrongPhonemes.push_back("z");
     */
    
    
    int onlyFromEpisode = -1;
    if ( DataProvider::getInstance()->getCurrentEpisode() >= 4) onlyFromEpisode = 1;
    
    string wrong1 = DataProvider::getInstance()->getRandomWrongPhoneme(word, false, onlyFromEpisode);
    wrong1 = wrong1.substr(0, wrong1.find("_"));
    
    
    string wrong2 = DataProvider::getInstance()->getRandomWrongPhoneme(word, false, onlyFromEpisode);
    while (wrong2 == wrong1) {
        wrong2 = DataProvider::getInstance()->getRandomWrongPhoneme(word, false, onlyFromEpisode);
    }
    string wrong3 = DataProvider::getInstance()->getRandomWrongPhoneme(word, false, onlyFromEpisode);
    while ((wrong3 == wrong1) || (wrong3 == wrong2) ) {
        wrong3 = DataProvider::getInstance()->getRandomWrongPhoneme(word, false, onlyFromEpisode);
    }
    
    
    wrongPhonemes.push_back( ArabicHelper::getInstance()->getInArabic( wrong1 ) );
    wrongPhonemes.push_back( ArabicHelper::getInstance()->getInArabic( wrong2 ) );
    wrongPhonemes.push_back( ArabicHelper::getInstance()->getInArabic( wrong3 ) );
    
    currentPhonemeIndex = -1;

	lifes = START_LIFES;

}

void Blending1Game::initAudio() {

	// Preload audio files

	simpleAudioEngine->preloadEffect((PATH_AUDIO + "Audio/Help.mp3").c_str());

	/*simpleAudioEngine->preloadEffect((PATH_AUDIO + "Audio/" + word + ".mp3").c_str());

	for (auto iterator = correctPhonemes.begin(); iterator != correctPhonemes.end(); ++iterator) {
		simpleAudioEngine->preloadEffect((PATH_AUDIO + "Audio/" + (*iterator) + ".mp3").c_str());
	}*/

    simpleAudioEngine->preloadBackgroundMusic("common/audio/bg/GAME_1.mp3");
	simpleAudioEngine->preloadEffect((PATH_AUDIO + "Audio/signboardHide.mp3").c_str());
	simpleAudioEngine->preloadEffect((PATH_AUDIO + "Audio/signboardShow.mp3").c_str());
	//simpleAudioEngine->preloadEffect((PATH_AUDIO + "Audio/Help_" + word + ".mp3").c_str());
	simpleAudioEngine->preloadEffect((PATH_AUDIO + "Audio/hillShow.mp3").c_str());
	simpleAudioEngine->preloadEffect((PATH_AUDIO + "Audio/boxFall1.mp3").c_str());
	simpleAudioEngine->preloadEffect((PATH_AUDIO + "Audio/boxFall2.mp3").c_str());
	simpleAudioEngine->preloadEffect((PATH_AUDIO + "Audio/boxFall3.mp3").c_str());
	simpleAudioEngine->preloadEffect((PATH_AUDIO + "Audio/lifeShow.mp3").c_str());
	simpleAudioEngine->preloadEffect((PATH_AUDIO + "Audio/lifeHide.mp3").c_str());
	simpleAudioEngine->preloadEffect((PATH_AUDIO + "Audio/feedbackPositive.mp3").c_str());
	simpleAudioEngine->preloadEffect((PATH_AUDIO + "Audio/semaTryagain.mp3").c_str());

    
    
   simpleAudioEngine->playBackgroundMusic("common/audio/bg/GAME_1.mp3", true);
    
}

void Blending1Game::initGameObjects() {

	// Instantiate gameObjects
	help = new GameObject(*rootNode, "Help", PATH + "Help.csb");

	/*mouthButton = new MouthButton(*rootNode, "MouthButton", _eventDispatcher, word);
	touchableGameObjects.push_back(mouthButton);*/

	/*boxButton1 = new BoxButton(*rootNode, "BoxButton1", _eventDispatcher);
	touchableGameObjects.push_back(boxButton1);
	boxButton2 = new BoxButton(*rootNode, "BoxButton2", _eventDispatcher);
	touchableGameObjects.push_back(boxButton2);
	boxButton3 = new BoxButton(*rootNode, "BoxButton3", _eventDispatcher);
	touchableGameObjects.push_back(boxButton3);*/
	Node* boxButtonReference = rootNode->getChildByName("BoxButtonReference");
    if (  cocos2d::Director::getInstance()->getWinSize().height > rootNode->getBoundingBox().size.height ) { // like iPad
        boxButtonReference->setPosition(Point(boxButtonReference->getPosition().x, _director->getWinSize().height - 150));
    }
    
    
    int indexPos = (int)correctPhonemes.size();
    for (int index = 0; index < correctPhonemes.size(); ++index) {
	//for (int index = correctPhonemes.size() - 1; index >= 0; --index) {
        indexPos--;
		BoxButton* boxButton = new BoxButton(*boxButtonReference, Vec2(120.f * indexPos, 0.f), _eventDispatcher, this, correctPhonemes.at(index), correctPhonemesColors.at(index));
		boxButton->setVisible(false);
		boxButton->getBoxButtonLetterBox().play("reset");
		touchableGameObjects.push_back(boxButton);
		boxButtons.push_back(boxButton);
	}
	//reverse(boxButtons.begin(), boxButtons.end());

	cannon = new Cannon(*rootNode, "Cannon", _eventDispatcher, this);
	touchableGameObjects.push_back(cannon);

	//leftHill = new PhysicsGameObject(*rootNode, "LeftHill", PATH + "LeftHill.csb", "RootBone/Collider", false, false, _eventDispatcher);
	leftHill = new GameObject(*(rootNode->getChildByName("LeftHill")), "RootBone", PATH + "LeftHill.csb", "Collider"/*, false, false, _eventDispatcher*/);
	//rightHill = new PhysicsGameObject(*rootNode, "RightHill", PATH + "RightHill.csb", "RootBone/Collider", false, false, _eventDispatcher);
	rightHill = new PhysicsGameObject(*(rootNode->getChildByName("RightHill")), "RootBone", PATH + "RightHill.csb", "Collider", false, false, _eventDispatcher);

	aimHelpHand = new GameObject(*rootNode, "AimHelpHand", PATH + "AimHelpHand.csb");
	shotHelpHand = new GameObject(*rootNode, "ShotHelpHand", PATH + "ShotHelpHand.csb");
	aimHelpHand->setVisible(false);
	shotHelpHand->setVisible(false);

	/*woodenBox = new WoodenBox(*rootNode, "WoodenBox", _eventDispatcher);
	activeBoxes.push_back(woodenBox);
	yellowLetterBox = new LetterBox(*rootNode, "YellowLetterBox", PATH + "YellowLetterBox.csb", _eventDispatcher, "C", this);
	activeBoxes.push_back(yellowLetterBox);
	redLetterBox = new LetterBox(*rootNode, "RedLetterBox", PATH + "RedLetterBox.csb", _eventDispatcher, "A", this);
	activeBoxes.push_back(redLetterBox);
	blueLetterBox = new LetterBox(*rootNode, "BlueLetterBox", PATH + "BlueLetterBox.csb", _eventDispatcher, "T", this);
	activeBoxes.push_back(blueLetterBox);*/

	for (int index = 0; index < 6; ++index) {
		WoodenBox* box = new WoodenBox(*rootNode, Vec2::ZERO, _eventDispatcher);
		box->setVisible(false);
		box->setPhysicsActivated(false);
		woodenBoxes.push_back(box);
	}
	for (int index = 0; index < 2; ++index) {
		LetterBox* box = new LetterBox(*rootNode, Vec2::ZERO, /*PATH + "YellowLetterBox.csb"*/LetterBox::Color::YELLOW, _eventDispatcher, "", this, cannon);
		box->setVisible(false);
		box->setPhysicsActivated(false);
		yellowLetterBoxes.push_back(box);
	}
	for (int index = 0; index < 2; ++index) {
		LetterBox* box = new LetterBox(*rootNode, Vec2::ZERO, /*PATH + "RedLetterBox.csb"*/ LetterBox::Color::RED, _eventDispatcher, "", this, cannon);
		box->setVisible(false);
		box->setPhysicsActivated(false);
		redLetterBoxes.push_back(box);
	}
	for (int index = 0; index < 2; ++index) {
		LetterBox* box = new LetterBox(*rootNode, Vec2::ZERO, /*PATH + "BlueLetterBox.csb"*/ LetterBox::Color::BLUE, _eventDispatcher, "", this, cannon);
		box->setVisible(false);
		box->setPhysicsActivated(false);
		blueLetterBoxes.push_back(box);
	}

	for (int index = 1; index <= START_LIFES; ++index) {
		lifeGameObjects.push_back(new GameObject(*rootNode, "Life" + StringUtility::toString(index), PATH + "Life.csb"));
	}

	tatuTryAgain = new GameObject(*rootNode, "TatuTryAgain", PATH + "TatuTryAgain.csb");

	feedbackSignboard = new FeedbackSignboard(*rootNode, "FeedbackSignboard", word, correctPhonemes, correctPhonemesColors, word + ".png", justAudio);

    feedbackSignboard->wordAudioFilename = wordAudioFilename;
    
	initBoxConfigurations();

}

void Blending1Game::fadeIn() {
    
    // CCLOG("Blending1Game - Fade in");
    
    composeGame();
    
    runAction(
        Sequence::createWithTwoActions(
            DelayTime::create(8.5f), // time for game composition
            CallFunc::create([=]() {
                showHelp();
            })
        )
    );
    
    
}

void Blending1Game::showHelp() {
	
//SHOWN_TUTORIAL = false;
    if( SHOWN_TUTORIAL == false) {
        SHOWN_TUTORIAL = true;
        
        
        simpleAudioEngine->playEffect((PATH_AUDIO + "Audio/Help.mp3").c_str());
        runAction(
            Sequence::createWithTwoActions(
                DelayTime::create(2.9f),
                      CallFunc::create([=]() {
                CCLOG("----------play audio word.... %s", wordAudioFilename.c_str());
                        simpleAudioEngine->playEffect(("common/audio/sema/words/" + wordAudioFilename + ".mp3").c_str());
                })
            )
        );
        
        runAction(
            Sequence::createWithTwoActions(
                 DelayTime::create(4.0f),
                      CallFunc::create([=]() {
                        showIntroHelp();
                  })
            )
        );
        

    } else {
        showIntroHelp();
    }
} // close fadeIn

void Blending1Game::composeGame() {
    
    disableTouch();
    
    const float stepDelay = 0.2f;
    float totalDelay = stepDelay;
    

    switch (NUM_WORDS)
    {
        case 1:
            scoreToSubtract = 100.0f / 3.0f;
            break;
            
        case 2:
            scoreToSubtract = 100.0f / 6.0f;
            break;
            
        case 3:
            scoreToSubtract = 100.0f / 9.0f;
            break;
    }
    

    runAction(   // runAction1
              Sequence::create(  // seq1
                               DelayTime::create(totalDelay),
                               CallFunc::create([&]() {
                  simpleAudioEngine->playEffect((PATH_AUDIO + "Audio/hillShow.mp3").c_str());
                  cannon->play("show");
                  leftHill->play("show", [=]() {
                      simpleAudioEngine->playEffect((PATH_AUDIO + "Audio/hillShow.mp3").c_str());
                      rightHill->play("show", [=]() {
                          const float stepDelay = 0.15f;
                          float totalDelay = 0.f;
                          for (vector<GameObject*>::iterator iterator = lifeGameObjects.begin(); iterator != lifeGameObjects.end(); ++iterator) {
                              GameObject* life = (*iterator);
                              life->play(
                                         Sequence::createWithTwoActions(
                                                                        DelayTime::create(totalDelay),
                                                                        CallFunc::create([=]() {
                                             simpleAudioEngine->playEffect((PATH_AUDIO + "Audio/lifeShow.mp3").c_str());
                                             life->play("show");
                                         })
                                                                        )
                                         );
                              totalDelay += stepDelay;
                          }
                          runAction(
                                    Sequence::createWithTwoActions(
                                            DelayTime::create(totalDelay + stepDelay),
                                            CallFunc::create([&]() {
                                                updateBoxes(true, false);
                                            })
                                    )
                            );
                          rightHill->getActionTimeline()->clearLastFrameCallFunc();
                      });
                      leftHill->getActionTimeline()->clearLastFrameCallFunc();
                  });
              }),
                               nullptr
                               ) // close seq1
              ); // close runAction1
    
}

void Blending1Game::showIntroHelp() {

    disableTouch();
    
    feedbackSignboard->bringToFront();
    feedbackSignboard->showStartGame([=]() {
        
        const float stepDelay = 0.2f;
        float totalDelay = stepDelay;
        
        for (vector<BoxButton*>::reverse_iterator iterator = boxButtons.rbegin(); iterator != boxButtons.rend(); ++iterator ) {
        // for (vector<BoxButton*>::iterator iterator = boxButtons.begin(); iterator != boxButtons.end(); ++iterator) {
            BoxButton* boxButton = (*iterator);
            boxButton->play(
                    Sequence::createWithTwoActions(
                                    DelayTime::create(totalDelay),
                                    CallFunc::create( [=]() {
                                        boxButton->setVisible(true);
                                        boxButton->play("show");
                        
                                    })
                   )
            );
            totalDelay += stepDelay;
        }
        
        
        
        showAimTutorial();
        enableTouch();
        animateCurrentBoxButton();
 
        
    });
}


void Blending1Game::showTutorial() {}

void Blending1Game::hideTutorial() {}

void Blending1Game::showAimTutorial() {

	if (showingAimTutorial || SHOWN_AIM_TUTORIAL) {
		return;
	}

	/*if (SHOWN_AIM_TUTORIAL) {
		showingTutorial = false;
		return;
	}*/

	showingAimTutorial = true;
	SHOWN_AIM_TUTORIAL = true;

	// Start tutorial animation
	aimHelpHand->setVisible(true);
	Node* aimHelpHandSprite = aimHelpHand->getChild("RootBone/Sprite");
	aimHelpHandSprite->setOpacity(0);
	aimHelpHandSprite->runAction(
		Sequence::createWithTwoActions(
			FadeIn::create(0.5f),
			CallFunc::create(
				[=]() {
					aimHelpHand->play("drag", nullptr, true);
				})
			)
		);

}

void Blending1Game::showShotTutorial() {

	if (showingShotTutorial || SHOWN_SHOT_TUTORIAL) {
		return;
	}

	showingShotTutorial = true;
	SHOWN_SHOT_TUTORIAL = true;

	/*if (SHOWN_SHOT_TUTORIAL) {
		showingTutorial = false;
		return;
	}*/
	
	// Start tutorial animation
	shotHelpHand->setVisible(true);
	Node* shotHelpHandSprite = shotHelpHand->getChild("RootBone/Sprite");
	shotHelpHandSprite->setOpacity(0);
	shotHelpHandSprite->runAction(
		Sequence::createWithTwoActions(
			FadeIn::create(0.5f),
			CallFunc::create(
				[=]() {
					shotHelpHand->play("tap", nullptr, true);
				})
			)
		);

}

void Blending1Game::hideAimTutorial() {
	
	SHOWN_AIM_TUTORIAL = true;

	if (!showingAimTutorial) {
		return;
	}

	showingAimTutorial = false;

	// End tutorial animation
	Node* aimHelpHandSprite = aimHelpHand->getChild("RootBone/Sprite");
	aimHelpHandSprite->runAction(
		Sequence::createWithTwoActions(
			FadeOut::create(0.5f),
			CallFunc::create(
				[&]() {
					aimHelpHand->setVisible(false);
				})
			)
		);

}

void Blending1Game::hideShotTutorial() {
	
	SHOWN_SHOT_TUTORIAL = true;

	if (!showingShotTutorial) {
		return;
	}

	showingShotTutorial = false;

	// End tutorial animation
	Node* shotHelpHandSprite = shotHelpHand->getChild("RootBone/Sprite");
	shotHelpHandSprite->runAction(
		Sequence::createWithTwoActions(
			FadeOut::create(0.5f),
			CallFunc::create(
				[&]() {
					shotHelpHand->setVisible(false);
				})
			)
		);

}

bool Blending1Game::onTouchBegan(Touch* touch, Event* event) {

	// CCLOG("Blending1Game - Touch began");

	// Manage the start of a touch event

	return true;

}

void Blending1Game::onTouchMoved(Touch* touch, Event* event) {

	// CCLOG("Blending1Game - Touch moved");

	// Manage a touch event
}

void Blending1Game::onTouchEnded(Touch* touch, Event* event) {

	// CCLOG("Blending1Game - Touch ended");

	// Manage the end of a touch event

}

void Blending1Game::closeGame() {
    
    vector<string> wordsVector = DataProvider::getInstance()->getVectorWordsForGame();
    wordsVector.pop_back();
    if ( wordsVector.empty() ) {
        DataProvider::getInstance()->setGameCompleted("Blending1");
        DataProvider::getInstance()->setWatchmanReaction(WatchmanScene::GOOD_REACTION);
        Logger::getInstance()->logEvent(NAME, Logger::CORRECT, "");
        Logger::getInstance()->logEvent(NAME, Logger::WIN, "");
        Logger::getInstance()->logEvent(NAME, Logger::CLOSE, "");
        _director->replaceScene(TransitionFade::create(TRANSITION_TIME, WatchmanScene::createScene(), TRANSITION_COLOR));
    } else {
        DataProvider::getInstance()->setVectorWordsForGame(wordsVector);
        Logger::getInstance()->logEvent(NAME, Logger::CORRECT, "");
        Logger::getInstance()->logEvent(NAME, Logger::CLOSE, "");
        _director->replaceScene(TransitionFade::create(TRANSITION_TIME, Blending1Game::createScene(), TRANSITION_COLOR));
    }
}

void Blending1Game::endGame(bool gameOver) {

	CCLOG("Blending1Game - End game");

	// Manage end game and start fade out animations

	disableTouch();
    
	if (!gameOver) {
        
		feedbackSignboard->showEndGame([=]() {
            closeGame();
            feedbackSignboard->clearLastFrameCallFunc();
		});

		
	} else {

		tatuTryAgain->play("show", [&]() {
			simpleAudioEngine->playEffect((PATH_AUDIO + "Audio/semaTryagain.mp3").c_str());
			tatuTryAgain->play(
				Sequence::createWithTwoActions(
					FadeOut::create(1.f),
					CallFunc::create(
						[&]() {
							tatuTryAgain->play("hide", [&]() {
                                Logger::getInstance()->logEvent(NAME, Logger::LOSE, "");
                                Logger::getInstance()->logEvent(NAME, Logger::CLOSE, "");
                                _director->replaceScene(TransitionFade::create(TRANSITION_TIME, WatchmanScene::createScene(), TRANSITION_COLOR));
								tatuTryAgain->clearLastFrameCallFunc();
							});
						})
					)
				);
			tatuTryAgain->clearLastFrameCallFunc();
		});

	}

}

void Blending1Game::initBoxConfigurations() {

	vector<pair<Vec2, Box*>> configuration;

	configuration.push_back(make_pair(Vec2(56.f, 56.f), woodenBoxes.at(0)));
	configuration.push_back(make_pair(Vec2(168.f, 56.f), yellowLetterBoxes.at(0)));
	configuration.push_back(make_pair(Vec2(280.f, 56.f), woodenBoxes.at(1)));
	configuration.push_back(make_pair(Vec2(130.f, 168.f), woodenBoxes.at(2)));
	configuration.push_back(make_pair(Vec2(242.f, 168.f), blueLetterBoxes.at(0)));
	configuration.push_back(make_pair(Vec2(94.f, 280.f), woodenBoxes.at(3)));
	configuration.push_back(make_pair(Vec2(206.f, 280.f), woodenBoxes.at(4)));
	configuration.push_back(make_pair(Vec2(130.f, 392.f), redLetterBoxes.at(0)));
	boxConfigurations.push_back(configuration);

	configuration.clear();
	configuration.push_back(make_pair(Vec2(56.f, 56.f), woodenBoxes.at(0)));
	configuration.push_back(make_pair(Vec2(168.f, 56.f), redLetterBoxes.at(0)));
	configuration.push_back(make_pair(Vec2(280.f, 56.f), woodenBoxes.at(1)));
	configuration.push_back(make_pair(Vec2(18.f, 168.f), woodenBoxes.at(2)));
	configuration.push_back(make_pair(Vec2(130.f, 168.f), blueLetterBoxes.at(0)));
	configuration.push_back(make_pair(Vec2(242.f, 168.f), woodenBoxes.at(3)));
	configuration.push_back(make_pair(Vec2(94.f, 280.f), woodenBoxes.at(4)));
	configuration.push_back(make_pair(Vec2(130.f, 392.f), yellowLetterBoxes.at(0)));
	boxConfigurations.push_back(configuration);

	configuration.clear();
	configuration.push_back(make_pair(Vec2(56.f, 56.f), woodenBoxes.at(0)));
	configuration.push_back(make_pair(Vec2(168.f, 56.f), woodenBoxes.at(1)));
	configuration.push_back(make_pair(Vec2(280.f, 56.f), yellowLetterBoxes.at(0)));
	configuration.push_back(make_pair(Vec2(130.f, 168.f), woodenBoxes.at(2)));
	configuration.push_back(make_pair(Vec2(242.f, 168.f), redLetterBoxes.at(0)));
	configuration.push_back(make_pair(Vec2(150.f, 280.f), blueLetterBoxes.at(0)));
	configuration.push_back(make_pair(Vec2(262.f, 280.f), woodenBoxes.at(3)));
	configuration.push_back(make_pair(Vec2(130.f, 392.f), yellowLetterBoxes.at(1)));
	boxConfigurations.push_back(configuration);

	configuration.clear();
	configuration.push_back(make_pair(Vec2(56.f, 56.f), redLetterBoxes.at(0)));
	configuration.push_back(make_pair(Vec2(168.f, 56.f), woodenBoxes.at(0)));
	configuration.push_back(make_pair(Vec2(280.f, 56.f), woodenBoxes.at(1)));
	configuration.push_back(make_pair(Vec2(206.f, 168.f), yellowLetterBoxes.at(0)));
	configuration.push_back(make_pair(Vec2(318.f, 168.f), woodenBoxes.at(2)));
	configuration.push_back(make_pair(Vec2(168.f, 280.f), woodenBoxes.at(3)));
	configuration.push_back(make_pair(Vec2(206.f, 392.f), blueLetterBoxes.at(0)));
	configuration.push_back(make_pair(Vec2(168.f, 504.f), woodenBoxes.at(4)));
	boxConfigurations.push_back(configuration);

	configuration.clear();
	configuration.push_back(make_pair(Vec2(56.f, 56.f), blueLetterBoxes.at(0)));
	configuration.push_back(make_pair(Vec2(168.f, 56.f), woodenBoxes.at(0)));
	configuration.push_back(make_pair(Vec2(280.f, 56.f), woodenBoxes.at(1)));
	configuration.push_back(make_pair(Vec2(130.f, 168.f), woodenBoxes.at(2)));
	configuration.push_back(make_pair(Vec2(242.f, 168.f), yellowLetterBoxes.at(0)));
	configuration.push_back(make_pair(Vec2(168.f, 280.f), woodenBoxes.at(3)));
	configuration.push_back(make_pair(Vec2(280.f, 280.f), redLetterBoxes.at(0)));
	configuration.push_back(make_pair(Vec2(130.f, 392.f), woodenBoxes.at(4)));
	configuration.push_back(make_pair(Vec2(242.f, 392.f), woodenBoxes.at(5)));
	configuration.push_back(make_pair(Vec2(94.f, 504.f), blueLetterBoxes.at(1)));
	boxConfigurations.push_back(configuration);

	configuration.clear();
	configuration.push_back(make_pair(Vec2(56.f, 56.f), woodenBoxes.at(0)));
	configuration.push_back(make_pair(Vec2(168.f, 56.f), yellowLetterBoxes.at(0)));
	configuration.push_back(make_pair(Vec2(280.f, 56.f), woodenBoxes.at(1)));
	configuration.push_back(make_pair(Vec2(130.f, 168.f), woodenBoxes.at(2)));
	configuration.push_back(make_pair(Vec2(242.f, 168.f), redLetterBoxes.at(0)));
	configuration.push_back(make_pair(Vec2(150.f, 280.f), blueLetterBoxes.at(0)));
	configuration.push_back(make_pair(Vec2(262.f, 280.f), woodenBoxes.at(3)));
	configuration.push_back(make_pair(Vec2(168.f, 392.f), yellowLetterBoxes.at(1)));
	boxConfigurations.push_back(configuration);

	configuration.clear();
	configuration.push_back(make_pair(Vec2(56.f, 56.f), woodenBoxes.at(0)));
	configuration.push_back(make_pair(Vec2(168.f, 56.f), blueLetterBoxes.at(0)));
	configuration.push_back(make_pair(Vec2(280.f, 56.f), woodenBoxes.at(1)));
	configuration.push_back(make_pair(Vec2(94.f, 168.f), yellowLetterBoxes.at(0)));
	configuration.push_back(make_pair(Vec2(206.f, 168.f), woodenBoxes.at(2)));
	configuration.push_back(make_pair(Vec2(142.f, 280.f), woodenBoxes.at(3)));
	configuration.push_back(make_pair(Vec2(252.f, 280.f), redLetterBoxes.at(0)));
	configuration.push_back(make_pair(Vec2(168.f, 392.f), woodenBoxes.at(4)));
	configuration.push_back(make_pair(Vec2(214.f, 504.f), yellowLetterBoxes.at(1)));
	boxConfigurations.push_back(configuration);

	configuration.clear();
	configuration.push_back(make_pair(Vec2(56.f, 56.f), woodenBoxes.at(0)));
	configuration.push_back(make_pair(Vec2(168.f, 56.f), woodenBoxes.at(1)));
	configuration.push_back(make_pair(Vec2(280.f, 56.f), yellowLetterBoxes.at(0)));
	configuration.push_back(make_pair(Vec2(18.f, 168.f), woodenBoxes.at(2)));
	configuration.push_back(make_pair(Vec2(130.f, 168.f), woodenBoxes.at(3)));
	configuration.push_back(make_pair(Vec2(242.f, 168.f), blueLetterBoxes.at(0)));
	configuration.push_back(make_pair(Vec2(188.f, 280.f), yellowLetterBoxes.at(1)));
	configuration.push_back(make_pair(Vec2(130.f, 392.f), woodenBoxes.at(4)));
	configuration.push_back(make_pair(Vec2(242.f, 392.f), redLetterBoxes.at(0)));
	boxConfigurations.push_back(configuration);

	configuration.clear();
	configuration.push_back(make_pair(Vec2(56.f, 56.f), woodenBoxes.at(0)));
	configuration.push_back(make_pair(Vec2(168.f, 56.f), redLetterBoxes.at(0)));
	configuration.push_back(make_pair(Vec2(280.f, 56.f), woodenBoxes.at(1)));
	configuration.push_back(make_pair(Vec2(130.f, 168.f), woodenBoxes.at(2)));
	configuration.push_back(make_pair(Vec2(242.f, 168.f), yellowLetterBoxes.at(0)));
	configuration.push_back(make_pair(Vec2(168.f, 280.f), blueLetterBoxes.at(0)));
	configuration.push_back(make_pair(Vec2(280.f, 280.f), woodenBoxes.at(3)));
	configuration.push_back(make_pair(Vec2(204.f, 392.f), yellowLetterBoxes.at(1)));
	boxConfigurations.push_back(configuration);

	configuration.clear();
	configuration.push_back(make_pair(Vec2(56.f, 56.f), redLetterBoxes.at(0)));
	configuration.push_back(make_pair(Vec2(168.f, 56.f), woodenBoxes.at(0)));
	configuration.push_back(make_pair(Vec2(280.f, 56.f), woodenBoxes.at(1)));
	configuration.push_back(make_pair(Vec2(18.f, 168.f), woodenBoxes.at(2)));
	configuration.push_back(make_pair(Vec2(130.f, 168.f), blueLetterBoxes.at(0)));
	configuration.push_back(make_pair(Vec2(242.f, 168.f), woodenBoxes.at(3)));
	configuration.push_back(make_pair(Vec2(94.f, 280.f), woodenBoxes.at(4)));
	configuration.push_back(make_pair(Vec2(208.f, 280.f), redLetterBoxes.at(1)));
	configuration.push_back(make_pair(Vec2(76.f, 392.f), woodenBoxes.at(5)));
	configuration.push_back(make_pair(Vec2(188.f, 392.f), yellowLetterBoxes.at(0)));
	boxConfigurations.push_back(configuration);

}

void Blending1Game::updateBoxes(bool sendNewConfiguration, bool enableCannonTouch) {

	if (lifes <= 0) {
		endGame(true);
		return;
	}

    if (enableCannonTouch == false) CCLOG("enableCannonTouch è false");
    
	if (!sendNewConfiguration) {
		for (vector<Box*>::iterator iterator = activeBoxes.begin(); iterator != activeBoxes.end(); ++iterator) {
			(*iterator)->setPhysicsActivated(true);
		}
        
		cannon->load(enableCannonTouch);
		return;
	}

	//BoxButton* currentBoxButton;

	++currentPhonemeIndex;

	if (currentPhonemeIndex >= correctPhonemes.size()) {
		endGame();
		return;
	}

	/*currentBoxButton = boxButtons.at(currentPhonemeIndex);
	currentBoxButton->play("standing", nullptr, true);*/

	//Node* boxConfigurationsReference = rootNode->getChildByName("BoxConfigurationsReference");getChild("RootBone/BoxConfigurationsReference")
	Node* boxConfigurationsReference = rightHill->getNode().getChildByName("BoxConfigurationsReference");

	// Choose a box configuration
	srand( static_cast<unsigned int>(time(NULL)));
	int configurationIndex = rand() % boxConfigurations.size();
	
	vector<pair<Vec2, Box*>>& configuration = boxConfigurations.at(configurationIndex);

	// Disable previously enabled boxes
	for (vector<Box*>::iterator iterator = activeBoxes.begin(); iterator != activeBoxes.end(); ++iterator) {
		(*iterator)->setVisible(false);
		(*iterator)->setPhysicsActivated(false);
	}
	activeBoxes.clear();

	// Enable current configuration boxes
	vector<LetterBox*> letterBoxes;
	//int globalZOrder = 1;
	for (vector<pair<Vec2, Box*>>::iterator iterator = configuration.begin(); iterator != configuration.end(); ++iterator) {

		Box* box = (*iterator).second;
		//box->getNode().setPositionZ(globalZOrder++);
		box->setPosition(boxConfigurationsReference->getParent()->convertToWorldSpace(boxConfigurationsReference->getPosition()) + (*iterator).first + Vec2(0.f, 1000.f));
		box->setVisible(true);
		box->setPhysicsActivated(true);
		box->play("reset");
		activeBoxes.push_back(box);

		if (dynamic_cast<LetterBox*>(box) != nullptr) {
			letterBoxes.push_back(dynamic_cast<LetterBox*>(box));
		}

	}

	// Choose random phonemes from correct and wrong phonemes except the current correct phoneme
	set<string> phonemes;
	phonemes.insert(correctPhonemes[currentPhonemeIndex]);
	while (phonemes.size() < letterBoxes.size()) {
		if (rand() % 2 == 0) {
			phonemes.insert(correctPhonemes.at(rand() % correctPhonemes.size()));
		} else {
			phonemes.insert(wrongPhonemes.at(rand() % wrongPhonemes.size()));
		}
	}
	phonemes.erase(correctPhonemes[currentPhonemeIndex]);

	// Shuffle letterbox vector
	random_shuffle(letterBoxes.begin(), letterBoxes.end());

	// Assign correct phoneme to a letterbox of the correct color
	vector<LetterBox*>::iterator correctColorLetterBoxIterator = std::find_if(letterBoxes.begin(), letterBoxes.end(), [&](const LetterBox* letterBox) {
		return letterBox->getColor() == correctPhonemesColors[currentPhonemeIndex];
	});
	assert(correctColorLetterBoxIterator != letterBoxes.end());
	(*correctColorLetterBoxIterator)->setPhoneme(correctPhonemes[currentPhonemeIndex]);
	letterBoxes.erase(correctColorLetterBoxIterator);

	// Assign other phonemes to the other letterboxes
	int letterBoxIndex = 0;
	for (set<string>::iterator iterator = phonemes.begin(); iterator != phonemes.end(); ++iterator) {
		letterBoxes.at(letterBoxIndex++)->setPhoneme((*iterator));
	}

	const float stepDelay = 0.2f;
	float totalDelay = 0.f;
	for (vector<Box*>::iterator iterator = activeBoxes.begin(); iterator != activeBoxes.end(); ++iterator) {
		(*iterator)->play(
			Sequence::create(
				DelayTime::create(totalDelay),
				EaseOut::create(MoveBy::create(stepDelay * 2, Vec2(0.f, -1000.f)), 2.f),
				CallFunc::create(
					[=]() {
						simpleAudioEngine->playEffect((PATH_AUDIO + "Audio/boxFall" + StringUtility::toString(rand() % 3 + 1) + ".mp3").c_str());
					}),
				nullptr
				)
			);
		totalDelay += stepDelay;
	}
	runAction(
		Sequence::createWithTwoActions(
			DelayTime::create(totalDelay + stepDelay),
			CallFunc::create(
				[=]() {
					cannon->load(enableCannonTouch);
				})
			)
		);

}

void Blending1Game::animateCorrectLetter(const Vec2& startWorldPosition) {

	BoxButton* boxButton = boxButtons.at(currentPhonemeIndex);
	boxButton->setTouchable(false);
	touchableGameObjects.erase(find(touchableGameObjects.begin(), touchableGameObjects.end(), boxButton));

	BoxButtonLetterBox* boxButtonLetterBox = &(boxButton->getBoxButtonLetterBox());
	boxButtonLetterBox->setPosition(startWorldPosition);
	boxButtonLetterBox->play("spiral", [=]() {
		boxButton->play("reset");
		boxButtonLetterBox->play(EaseInOut::create(MoveTo::create(0.5f, Vec2::ZERO), 2.f));
		boxButtonLetterBox->clearLastFrameCallFunc();
	});

}

void Blending1Game::decreaseLifes() {

	assert(lifes > 0);
	
	simpleAudioEngine->playEffect((PATH_AUDIO + "Audio/lifeHide.mp3").c_str());
	
	lifeGameObjects.at(lifes - 1)->play("hide");
	--lifes;

        scorePercent -= scoreToSubtract;
}

void Blending1Game::animateCurrentBoxButton() {

	BoxButton* currentBoxButton = boxButtons.at(currentPhonemeIndex);
	currentBoxButton->play("standing", nullptr, true);

}



void Blending1Game::homeButtonPressed() {
    if ( TEST_ENABLED ) {
      //////  DataProvider::getInstance()->updateCurrentStatusToNext();
        DataProvider::getInstance()->setGameCompleted("Blending1");
        DataProvider::getInstance()->setWatchmanReaction(WatchmanScene::GOOD_REACTION);
    } else {
       DataProvider::getInstance()->setWatchmanReaction(WatchmanScene::BAD_REACTION);
    }
    
}
