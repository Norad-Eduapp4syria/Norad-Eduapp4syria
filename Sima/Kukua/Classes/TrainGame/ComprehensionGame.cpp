#include "ComprehensionGame.h"
#include "../Utils/Data/Logger.h"

template<> const bool kukua::Game<ComprehensionGame>::USE_PHYSICS = false;
template<> const bool kukua::Game<ComprehensionGame>::ENABLE_TOUCH = true;
template<> string kukua::Game<ComprehensionGame>::PATH = "Episodio7_comprehension/";
template<> const string kukua::Game<ComprehensionGame>::BACKGROUND_MUSIC_FILENAME = "backgroundMusic.mp3";
template<> bool kukua::Game<ComprehensionGame>::SHOWN_TUTORIAL = false;
template<> Scene* kukua::Game<ComprehensionGame>::scene = nullptr;
template<> const string kukua::Game<ComprehensionGame>::NAME = "Train";

ComprehensionGame::~ComprehensionGame() {

	CCLOG("~ComprehensionGame");
    
	delete help;
	delete train;
    delete leftBush;
    delete rightBush;
    delete cloud1;
    delete cloud2;
    delete cloud3;
    delete cloud4;
    delete cloud5;
    
}

void ComprehensionGame::initVariables() {

	CCLOG("ComprehensionGame - Init variables");

}

void ComprehensionGame::initAudio() {

	CCLOG("ComprehensionGame - Init audio");

	// Preload audio files
	simpleAudioEngine->preloadEffect((kukua::Game<ComprehensionGame>::PATH + "Audio/byee_ok.mp3").c_str());
	simpleAudioEngine->preloadEffect((kukua::Game<ComprehensionGame>::PATH + "Audio/CarroSale.wav").c_str());
	simpleAudioEngine->preloadEffect((kukua::Game<ComprehensionGame>::PATH + "Audio/dropCarro.wav").c_str());
	simpleAudioEngine->preloadEffect((kukua::Game<ComprehensionGame>::PATH + "Audio/feed_NEG5.wav").c_str());
	simpleAudioEngine->preloadEffect((kukua::Game<ComprehensionGame>::PATH + "Audio/feedPos4.wav").c_str());
	simpleAudioEngine->preloadEffect((kukua::Game<ComprehensionGame>::PATH + "Audio/popEnri1.wav").c_str());
	simpleAudioEngine->preloadEffect((kukua::Game<ComprehensionGame>::PATH + "Audio/popEnri2.wav").c_str());
	simpleAudioEngine->preloadEffect((kukua::Game<ComprehensionGame>::PATH + "Audio/popEnri3.wav").c_str());
	simpleAudioEngine->preloadEffect((kukua::Game<ComprehensionGame>::PATH + "Audio/TRAIN.wav").c_str());
	simpleAudioEngine->preloadEffect((kukua::Game<ComprehensionGame>::PATH + "Audio/TRAIN_riparte.wav").c_str());
    
    simpleAudioEngine->preloadEffect((kukua::Game<ComprehensionGame>::PATH + "Audio/help/help_1.mp3").c_str());
    simpleAudioEngine->preloadEffect((kukua::Game<ComprehensionGame>::PATH + "Audio/help/help_2.mp3").c_str());
    simpleAudioEngine->preloadEffect((kukua::Game<ComprehensionGame>::PATH + "Audio/help/help_3.mp3").c_str());
    simpleAudioEngine->preloadEffect((kukua::Game<ComprehensionGame>::PATH + "Audio/help/help_4.mp3").c_str());
    simpleAudioEngine->preloadEffect((kukua::Game<ComprehensionGame>::PATH + "Audio/help/help_5.mp3").c_str());
    simpleAudioEngine->preloadEffect((kukua::Game<ComprehensionGame>::PATH + "Audio/help/help_6.mp3").c_str());
    simpleAudioEngine->preloadEffect((kukua::Game<ComprehensionGame>::PATH + "Audio/help/help_7.mp3").c_str());
    simpleAudioEngine->preloadEffect((kukua::Game<ComprehensionGame>::PATH + "Audio/help/help_8.mp3").c_str());
    simpleAudioEngine->preloadEffect((kukua::Game<ComprehensionGame>::PATH + "Audio/help/help_voice.mp3").c_str());
	
    simpleAudioEngine->preloadBackgroundMusic("common/audio/bg/GAME_2.mp3");
    simpleAudioEngine->playBackgroundMusic("common/audio/bg/GAME_2.mp3", true);
}

void ComprehensionGame::initGameObjects() {

	CCLOG("ComprehensionGame - Init objects");

	Node* wagonsPlaceholder = rootNode->getChildByName("WagonsPlaceholder");

	help = new GameObject(*rootNode, "Help", ComprehensionGame::PATH + "Help.csb");
	// train = new Train(*rootNode, rootNode->getChildByName("TrainPlaceholder")->getPosition(), ComprehensionGame::PATH, _eventDispatcher, *this, wagonsPlaceholder);
	
    
    CCLOG("---------------pos = %f %f", rootNode->getChildByName("TrainPlaceholder")->getPosition().x, rootNode->getChildByName("TrainPlaceholder")->getPosition().y);
    
    train = new Train(*rootNode, rootNode->getChildByName("TrainPlaceholder")->getPosition(), ComprehensionGame::PATH, _eventDispatcher, *this, wagonsPlaceholder);
    
    
    leftBush = new GameObject(*rootNode, "LeftBush", ComprehensionGame::PATH + "Bush.csb");
	rightBush = new GameObject(*rootNode, "RightBush", ComprehensionGame::PATH + "Bush.csb");
	cloud1 = new GameObject(*rootNode, "Cloud1", ComprehensionGame::PATH + "cloud_1.csb");
	cloud2 = new GameObject(*rootNode, "Cloud2", ComprehensionGame::PATH + "cloud_2.csb");
	cloud3 = new GameObject(*rootNode, "Cloud3", ComprehensionGame::PATH + "cloud_1.csb");
	cloud4 = new GameObject(*rootNode, "Cloud4", ComprehensionGame::PATH + "cloud_2.csb");
	cloud5 = new GameObject(*rootNode, "Cloud5", ComprehensionGame::PATH + "cloud_1.csb");
 
}

void ComprehensionGame::fadeIn() {

	CCLOG("ComprehensionGame - Fade in");

	leftBush->play("animation0", nullptr, true);
	rightBush->play("animation0", nullptr, true);

	/*auto scaleUp = EaseBounceIn::create(ScaleTo::create(7.5f, 1.15f, 1.1f));
	auto scaleDown = EaseBounceIn::create(ScaleTo::create(7.5f, 1.f, 1.f));
	auto scaleCycle = RepeatForever::create(Sequence::create(scaleUp, scaleDown, nullptr));
	cloud1->getNode().runAction(scaleCycle->clone());
	cloud2->getNode().runAction(scaleCycle->clone());
	cloud3->getNode().runAction(scaleCycle->clone());
	cloud4->getNode().runAction(scaleCycle->clone());
	cloud5->getNode().runAction(scaleCycle->clone());*/
	auto move = Repeat::create(
		Sequence::create(
			MoveBy::create(30.f, Vec2(1500.f, 0.f)),
			MoveBy::create(0.f, Vec2(-1500.f, 0.f)),
			nullptr),
		-1
		);
	cloud1->getNode().runAction(
		Sequence::create(
			DelayTime::create(0.f),
			move->clone(),
			nullptr)
		);
	cloud2->getNode().runAction(
		Sequence::create(
			DelayTime::create(2.5f),
			move->clone(),
			nullptr)
		);
	cloud3->getNode().runAction(
		Sequence::create(
			DelayTime::create(17.5f),
			move->clone(),
			nullptr)
		);
	cloud4->getNode().runAction(
		Sequence::create(
			DelayTime::create(10.f),
			move->clone(),
			nullptr)
		);
	cloud5->getNode().runAction(
		Sequence::create(
			DelayTime::create(20.f),
			move->clone(),
			nullptr)
		);
	
	rootNode->runAction(
		Sequence::create(
			DelayTime::create(1.f),
			CallFunc::create([&]() {
            
            if (!SHOWN_TUTORIAL) {
                
            
            
                simpleAudioEngine->playEffect((kukua::Game<ComprehensionGame>::PATH + "Audio/help/help_1.mp3").c_str());
                help->play("help_1", [=]() {
                    simpleAudioEngine->playEffect((kukua::Game<ComprehensionGame>::PATH + "Audio/help/help_2.mp3").c_str());
                    help->play("help_2", [=]() {
                        simpleAudioEngine->playEffect((kukua::Game<ComprehensionGame>::PATH + "Audio/help/help_voice.mp3").c_str());
                        simpleAudioEngine->playEffect((kukua::Game<ComprehensionGame>::PATH + "Audio/help/help_3.mp3").c_str());
                        help->play("help_3", [=]() {
                            simpleAudioEngine->playEffect((kukua::Game<ComprehensionGame>::PATH + "Audio/help/help_4.mp3").c_str());
                            help->play("help_4", [=]() {
                                simpleAudioEngine->playEffect((kukua::Game<ComprehensionGame>::PATH + "Audio/help/help_5.mp3").c_str());
                                help->play("help_5", [=]() {
                                    simpleAudioEngine->playEffect((kukua::Game<ComprehensionGame>::PATH + "Audio/help/help_6.mp3").c_str());
                                    help->play("help_6", [=]() {
                                        simpleAudioEngine->playEffect((kukua::Game<ComprehensionGame>::PATH + "Audio/help/help_7.mp3").c_str());
                                        help->play("help_7", [=]() {
                                            simpleAudioEngine->playEffect((kukua::Game<ComprehensionGame>::PATH + "Audio/help/help_8.mp3").c_str());
                                            help->play("help_8", [=]() {
                                                simpleAudioEngine->playEffect((kukua::Game< ComprehensionGame>::PATH + "Audio/help/  help_1.mp3").c_str());
                                                help->play("help_9", [=]() {
                                                    train->fadeIn([&]() {
                                                        Game::enableTouch();
                                                        train->startSendingWagons();
                                                        Game::showTutorial();
                                                        train->getActionTimeline()->clearLastFrameCallFunc();
                                                    });
                                                    help->getActionTimeline()->clearLastFrameCallFunc();
                                                });
                                            });
                                        });
                                    });
                                });
                            });
                        });
                    });
                });
            }
            else {
                train->fadeIn([&]() {
                    Game::enableTouch();
                    train->startSendingWagons();
                });
            }
            
			}),
			nullptr
		)
        
	);

}





void ComprehensionGame::showTutorial() {

	CCLOG("ComprehensionGame - Show tutorial");

	// Start tutorial animation
    train->showTutorial();
}

void ComprehensionGame::hideTutorial() {

	CCLOG("ComprehensionGame - Hide tutorial");

	// End tutorial animation
    train->hideTutorial();
}

bool ComprehensionGame::onTouchBegan(Touch* touch, Event* event) {

	CCLOG("ComprehensionGame - Touch began");

	// Manage the start of a touch event

	return true;

}

void ComprehensionGame::onTouchMoved(Touch* touch, Event* event) {

	CCLOG("ComprehensionGame - Touch moved");

	// Manage a touch event

}

void ComprehensionGame::onTouchEnded(Touch* touch, Event* event) {

	CCLOG("ComprehensionGame - Touch ended");

	// Manage the end of a touch event

}

void ComprehensionGame::endGame(bool gameOver) {

	CCLOG("ComprehensionGame - End game");
    Logger::getInstance()->logEvent(NAME, Logger::WIN, "");
	//train->play("Train_B");
	train->fadeOut([&]() {
        simpleAudioEngine->stopBackgroundMusic();
        Logger::getInstance()->logEvent(NAME, Logger::CLOSE, "");
		_director->replaceScene(TransitionFade::create(0.8, ComprehensionGame::createScene(), Color3B(255, 255, 255)));
	});

}
void ComprehensionGame::homeButtonPressed() {
}
