#include "HomeGame.h"
#include "../AppMacros.h"
#include "../UserScene/UserSelectScene.h"
#include "../Utils/Data/DataProvider.h"
#include "../Utils/StringUtility.h"
#include "../WatchmanScene/WatchmanScene.h"

template<> const bool kukua::Game<HomeGame>::USE_PHYSICS = false;										// Enable/disable physics
template<> const bool kukua::Game<HomeGame>::ENABLE_TOUCH = true;										// Used to disable tutorial on first touch and manage general touch events
template<> string kukua::Game<HomeGame>::PATH = "Home/";											// Resources' subfolder path for this game
template<> const string kukua::Game<HomeGame>::BACKGROUND_MUSIC_FILENAME = "";		// Background music filename
template<> bool kukua::Game<HomeGame>::SHOWN_TUTORIAL = false;											// Used for showing tutorial on first execution, set to true only if tutorial is not needed
template<> Scene* kukua::Game<HomeGame>::scene = nullptr;
template<> const string kukua::Game<HomeGame>::NAME = "Home";

HomeGame::~HomeGame() {

	// Delete objects created with new
	delete logo;
	delete sema;
	delete hill1;
	delete hill2;
	delete tatu;
	delete playButton;
	delete hen1;
	delete hen2;
	delete hen3;

}

void HomeGame::initVariables() {
  
    
    dataProvider = DataProvider::getInstance();
    
    dataProvider->initUser();
    
    WatchmanScene::NIGHTRUNNER_ACTIVE = false;
    WatchmanScene::NIGHTRUNNER_HEARTS = -1;
    
    dataProvider->resetGamesCompleted();
    dataProvider->isIntensifierGameTurn = false;
    dataProvider->lastIntensifierGameNum = -1;
    
    dataProvider->setStatusFromLatestUnlockedPhoneme();
    int lastUnlockedEpisode = dataProvider->getCurrentEpisode();
    int lastUnlockedWatchman = dataProvider->getCurrentDBWatchman()->getNumber();
    
    string initialPortalCode = string(  StringUtility::toString( lastUnlockedEpisode )  ) + "-" + StringUtility::toString( lastUnlockedWatchman ) ;
    CCLOG("Home - initialPortalCode: %s", initialPortalCode.c_str());
    dataProvider->setSemaInitialPortalCode(initialPortalCode);
    dataProvider->setSemaInitialPortalCode("1-0"); // TODO: Togliere!
    dataProvider->setSemaInitialAction("stand");
    dataProvider->setMustUnlockNewPortalMap(false);
  
}

void HomeGame::initAudio() {

	// Preload audio files
	simpleAudioEngine->preloadEffect("Home/audio/altalena.mp3");
	simpleAudioEngine->preloadEffect("Home/audio/LetsPlay.mp3");
	simpleAudioEngine->preloadEffect("Home/audio/Logo.mp3");
	simpleAudioEngine->preloadEffect("Home/audio/playAppar.mp3");


    simpleAudioEngine->preloadBackgroundMusic("common/audio/bg/MAIN_THEME.mp3");
    simpleAudioEngine->playBackgroundMusic("common/audio/bg/MAIN_THEME.mp3", true);
	//simpleAudioEngine->playEffect("Home/audio/gallina.mp3");
}

void HomeGame::initGameObjects() {

	// Instantiate gameObjects
	logo = new GameObject(*rootNode, "Logo", PATH + "Logo.csb");

	hill1 = new GameObject(*rootNode, "Hill1", PATH + "Hill1.csb");
	hill2 = new GameObject(*rootNode, "Hill2", PATH + "Hill2.csb");

    sema = new HomeSema(*(hill1->getChild("master_hill/sima/Node")), Vec2::ZERO, _eventDispatcher);
    touchableGameObjects.push_back(sema);
    
	tatu = new HomeTatu(*(hill2->getChild("RootBone/TatuNode")), _eventDispatcher);
	tatu->setScale(0.7f);
	touchableGameObjects.push_back(tatu);

	playButton = new PlayButton(*rootNode, "PlayButton", _eventDispatcher, this);
	touchableGameObjects.push_back(playButton);

	hen1 = new Hen(*rootNode, "Hen1", _eventDispatcher);
	touchableGameObjects.push_back(hen1);

	hen2 = new Hen(*rootNode, "Hen2", _eventDispatcher);
	touchableGameObjects.push_back(hen2);

	hen3 = new Hen(*rootNode, "Hen3", _eventDispatcher);
	touchableGameObjects.push_back(hen3);

	cloud1 = new GameObject(*rootNode, "Cloud1", PATH + "Cloud_1.csb");
	cloud2 = new GameObject(*rootNode, "Cloud2", PATH + "Cloud_2.csb");
	cloud3 = new GameObject(*rootNode, "Cloud3", PATH + "Cloud_1.csb");
	cloud4 = new GameObject(*rootNode, "Cloud4", PATH + "Cloud_2.csb");
    
    // addSettingsButton();
    
    addLogoutButton();

}

void HomeGame::fadeIn() {
	
	// Disable HomeButton
	rootNode->getChildByName("HomeButton")->setVisible(false);

	// Start fade in animations

	/*hen1->play("standing", nullptr, true);
	hen2->play("standing", nullptr, true);
	hen3->play("standing", nullptr, true);*/
    
	hill1->play("shown");
	hill2->play("shown");
	tatu->play("Tatu_standing", nullptr, true);
	sema->play("sima_loop", nullptr, true);
	auto move = Repeat::create(
		Sequence::create(
			MoveBy::create(30.f, Vec2(1500.f, 0.f)),
			MoveBy::create(0.f, Vec2(-1500.f, 0.f)),
			nullptr),
		-1
		);
	cloud1->play(
		Sequence::create(
			DelayTime::create(0.f),
			move->clone(),
			nullptr)
		);
	cloud2->play(
		Sequence::create(
			DelayTime::create(2.5f),
			move->clone(),
			nullptr)
		);
	cloud3->play(
		Sequence::create(
			DelayTime::create(17.5f),
			move->clone(),
			nullptr)
		);
	cloud4->play(
		Sequence::create(
			DelayTime::create(10.f),
			move->clone(),
			nullptr)
		);

	runAction(
		Sequence::create(
			CallFunc::create(
			[=]() {
					simpleAudioEngine->playEffect("Home/audio/Logo.mp3");
					logo->play("Logo_A", [=]() {
						simpleAudioEngine->playEffect("Home/audio/LetsPlay.mp3");
						logo->play("Logo_B", nullptr, true);
                        logo->getActionTimeline()->clearLastFrameCallFunc();
					});
				}),
			DelayTime::create(0.4f),
			CallFunc::create(
				[&]() {
					simpleAudioEngine->playEffect("Home/audio/playAppar.mp3");
					playButton->play("Play_A");
				}),
			DelayTime::create(0.4f),
			CallFunc::create(
				[&]() {
					Game::enableTouch();
				}),
			nullptr
			)
		);
}

void HomeGame::showTutorial() {

	// Start tutorial animation

}

void HomeGame::hideTutorial() {

	// End tutorial animation

}

bool HomeGame::onTouchBegan(Touch* touch, Event* event) {

	// Manage the start of a touch event

	return true;

}

void HomeGame::onTouchMoved(Touch* touch, Event* event) {

	// Manage a touch event
}

void HomeGame::onTouchEnded(Touch* touch, Event* event) {

	// Manage the end of a touch event

}

void HomeGame::endGame(bool gameOver) {

	// Manage end game and start fade out animations

}

void HomeGame::homeButtonPressed() {
}


void HomeGame::addSettingsButton() {
    /*
    cornerTapCounter = 0;
    
    cocos2d::ui::Button *backNode = cocos2d::ui::Button::create("common/images/void.png", "common/images/void.png", "common/images/void.png");
    
    backNode->setPosition(Vec2(50, 50 ));
    
    rootNode->addChild(backNode);
    
    backNode->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                cornerTapCounter++;
                if (cornerTapCounter == 5) {
                    Logger::getInstance()->logEvent("Home", Logger::CLOSE, "");
                    _director->replaceScene(TransitionFade::create(TRANSITION_TIME, Settings::createScene(), TRANSITION_COLOR));
                }
                break;
            default:
                break;
        }
    });
    */
}



void HomeGame::addLogoutButton() {
    
    cocos2d::ui::Button *backNode = cocos2d::ui::Button::create("Home/png/logOut.png", "Home/png/logOut.png", "Home/png/logOut.png");
    
    backNode->setAnchorPoint(Vec2(0.5, 0.5));
    
    auto frameSize =  rootNode->getBoundingBox().size; //cocos2d::Director::getInstance()->getWinSize();
    auto x = 90;
  
    float winHeight = cocos2d::Director::getInstance()->getWinSize().height;
    float rootHieght = rootNode->getBoundingBox().size.height;
    
    float y = 0;
    
    if ( winHeight < rootHieght ) {
        //CCLOG("like iphone");
        y = winHeight;
        
    } else {
        //   CCLOG("like ipad");
        float delta = (winHeight-rootHieght) / 2;
        y = rootHieght + delta;
        y -= 10;
    }
    
    
    y = y - (backNode->getBoundingBox().size.height /2);

    backNode->setPosition(Vec2(x, y));
    
    rootNode->addChild(backNode, 10);
    
    backNode->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                Logger::getInstance()->logEvent("Home", Logger::CLOSE, "");
                simpleAudioEngine->stopBackgroundMusic();
                _director->replaceScene(TransitionFade::create(TRANSITION_TIME, UserSelectScene::createScene(), TRANSITION_COLOR));
                
                break;
            default:
                break;
        }
    });
    
}

