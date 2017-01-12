#include "WatchmanScene.h"
#include "../Utils/StringUtility.h"
#include "../PenaltyKickGame/PenaltyKickGame.h"
#include "../FallingLetters/FallingLetters.h"
#include "../FallingLetters/FallingLettersEp2/FallingLettersEp2.h"
#include "../PlatformGame2/PlatformGame2.h"

#include "../TubGame/TubGame.h"

#include "../LettersGame/LettersGame.h"
//#include "../LettersGame/LettersGamePaint.h"
#include "../Blending1Game/Blending1Game.h"
#include "../MapScene/MapScene.h"
#include "InventoryButton.h"
#include "Portal.h"
#include "../PhotoScene/PhotoScene.h"
#include "../TunnelLoop/TunnelLoop.h"
#include "../AppMacros.h"
#include "WatchmanSceneGrandpa.h"
#include "../RecorderScene/WordReading.h"

#include "../WordDictation/WordDictation.h"
#include "../ListComprehens/ListComprehens.h"
#include "../ShapesGame2/ShapesGame2.h"
#include "../ShapesGame/ShapesGame.h"
#include "../Bodyparts/Bodyparts.h"
#include "../OralPassage/OralPassage.h"

#include "../ShuffledSentence/ShuffledSentence.h"
#include "../WordsProblemGame/WordsProblemGame.h"
#include "../SentenceDictation/SentenceDictation.h"
#include "../HealthGame/HealthGame.h"
#include "../NightrunnerGame_1_4/NightrunnerGame_1_4.h"
#include "../SocialWeal/SocialWeal.h"
#include "../EmotionalGame/EmotionalGame.h"

const string WatchmanScene::PATH = "WatchmanScene/";    // Resources' subfolder path for this scene
const string WatchmanScene::FIRST_TIME = "FIRST_TIME";
const string WatchmanScene::SHOW_1_PORTAL = "SHOW_1_PORTAL";
const string WatchmanScene::SHOW_2_PORTALS = "SHOW_2_PORTALS";
const string WatchmanScene::SHOW_3_PORTALS = "SHOW_3_PORTALS";
const bool WatchmanScene::ENABLE_TOUCH = true; // Used to disable tutorial on first touch and manage general touch events
bool WatchmanScene::NIGHTRUNNER_ACTIVE = false;
int WatchmanScene::NIGHTRUNNER_HEARTS = -1;
const string WatchmanScene::NONE_REACTION = "NONE_REACTION";
const string WatchmanScene::GOOD_REACTION = "GOOD_REACTION";
const string WatchmanScene::BAD_REACTION = "BAD_REACTION";


Scene* WatchmanScene::createScene() {

	// 'scene' is an autorelease object
	Scene* scene = Scene::create();

	// 'layer' is an autorelease object			 
	auto layer = WatchmanScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;

}

WatchmanScene::~WatchmanScene() {

	// Delete objects created with new

    _eventDispatcher->removeEventListener(listenerPlayButtonClicked);
    _eventDispatcher->removeEventListener(moveSemaOnPortalEventHandler);
    
	for (vector<DBKnowledgeBubble*>::iterator iterator = dbKnowledgeBubbles_forKB.begin(); iterator != dbKnowledgeBubbles_forKB.end(); ++iterator) {
		delete (*iterator);
	}
	dbKnowledgeBubbles_forKB.clear();
    
    for (vector<DBKnowledgeBubble*>::iterator iterator = dbUnlockedKnowledgeBubbles.begin(); iterator != dbUnlockedKnowledgeBubbles.end(); ++iterator) {
        delete (*iterator);
    }
    dbUnlockedKnowledgeBubbles.clear();
    
    for (vector<DBGame*>::iterator iterator = vectorGamesPortals.begin(); iterator != vectorGamesPortals.end(); ++iterator) {
        delete (*iterator);
    }
    vectorGamesPortals.clear();
    
    for (vector<DBGame*>::iterator iterator = vectorGamesState.begin(); iterator != vectorGamesState.end(); ++iterator) {
        delete (*iterator);
    }
    vectorGamesState.clear();
    

	for (map<string, vector<DBGame*>>::iterator iterator1 = dbGames_forKB.begin(); iterator1 != dbGames_forKB.end(); ++iterator1) {
		for (vector<DBGame*>::iterator iterator2 = iterator1->second.begin(); iterator2 != iterator1->second.end(); ++iterator2) {
			delete (*iterator2);
		}
	}
	dbGames_forKB.clear();

	delete sema;
    delete stateCalculator;

	for (vector<KnowledgeBubble*>::iterator iterator = knowledgeBubbles.begin(); iterator != knowledgeBubbles.end(); ++iterator) {
		delete (*iterator);
	}

	delete portal1;
	delete portal2;
	delete portal3;
    if (help != nullptr) delete help;

	delete inventory;
	delete inventoryButton;
    delete watchmanObj;
    
    if (letterHelp != nullptr) delete letterHelp;
    
    
    if (nightrunnerObj != nullptr) delete nightrunnerObj;
    
}

bool WatchmanScene::init() {

	if (!Layer::init())
	{
		return false;
	}

	rootNode = CSLoader::createNode(PATH + "MainScene.csb");

	rootNode->setAnchorPoint(Point(0.5, 0.5));
	rootNode->setPosition(Point(_director->getWinSize().width / 2, _director->getWinSize().height / 2));
	addChild(rootNode);

	startGame();

	return true;

}

void WatchmanScene::startGame() {

	Logger::getInstance()->logEvent("Watchman", Logger::OPEN, "");

	initVariables();
	initAudio();
	initGameObjects();
	if (!NIGHTRUNNER_ACTIVE) addHomeButton();
	fadeIn();

}

void WatchmanScene::initVariables() {

    help = nullptr;
    letterHelp = nullptr;
    mustShowHelpNewNumber = false;
    
    step = 0;
	touching = false;
    newPhonemeDiscovered = false;
    
	dataProvider = DataProvider::getInstance();
    dataProvider->inGame = false;
    
}

void WatchmanScene::initAudio() {

	// Preload audio files
	simpleAudioEngine = SimpleAudioEngine::getInstance();
    
    
    simpleAudioEngine->preloadBackgroundMusic("common/audio/bg/WATCHMAN.mp3");
    
    
    
    simpleAudioEngine->preloadEffect((PATH + "Audio/main/back.mp3").c_str());
    simpleAudioEngine->preloadEffect((PATH + "Audio/main/Granpa/man/Feedback_negativi/Granpa_tryagain.mp3").c_str());
    simpleAudioEngine->preloadEffect((PATH + "Audio/main/Granpa/man/Feedback_positivi/Granpa_welldone.mp3").c_str());
    simpleAudioEngine->preloadEffect((PATH + "Audio/main/Granpa/man/Main_scene/Granpa_Choose_the_game.mp3").c_str());
    
    
}

void WatchmanScene::initGameObjects() {
    
    // Instantiate gameObjects
    
    sema = new WatchmanSceneSema(*rootNode, "Sema", PATH + "CSD/Sema.csb", "RootBone/dragSprite","RootBone/hitSprite", _eventDispatcher);
    //leave commented to avoid bug.. sema->setVisible(false);
    touchableGameObjects.push_back(sema);
    
    
    listenerPlayButtonClicked = EventListenerCustom::create("PortalPlayButtonClicked", [=](EventCustom* event){
        CCLOG("PortalPlayButtonClicked");
        openGame();
    });
    _eventDispatcher->addEventListenerWithFixedPriority(listenerPlayButtonClicked, 1);
    
    
    moveSemaOnPortalEventHandler = EventListenerCustom::create("MoveSemaOnPortalEvent", [=](EventCustom* event){
        
        auto portal = static_cast<Portal*>(event->getUserData());
        sema->moveToPortal(portal);
        
        CCLOG("moveSemaOnPortalEventHandler");
    });
    _eventDispatcher->addEventListenerWithFixedPriority(moveSemaOnPortalEventHandler, 1);
    
    
    rootNode->getChildByName("blackBG")->setVisible(false);
    
    
    int currentEpisodeNum = dataProvider->getCurrentEpisode();
    
    if (NIGHTRUNNER_ACTIVE) {
        
        
        
        dataProvider->calculateIntensifier(-1);
        dataProvider->setCurrentDBKnowledgeBubble( dataProvider->getCurrentIntensifier()->getDBKnowledgeBubble()  );
        
        
        nightrunnerObj = new GameObject(*rootNode, "Nightrunner", PATH + "CSD/Watchman_Skin/boss.csb");
        nightrunnerObj->setVisible(true);
        
        setNightRunnerHearts();
        
        portal1 = new Portal(*rootNode, "Portal1", PATH + "CSD/portal.csb", "Sprite", _eventDispatcher);
        portal2 = new Portal(*rootNode, "Portal2", PATH + "CSD/portal.csb", "Sprite", _eventDispatcher);
        portal3 = new Portal(*rootNode, "Portal3", PATH + "CSD/portal.csb", "Sprite", _eventDispatcher);
     
        if (currentEpisodeNum <= 4) {
            
            auto game1_4 = new DBGame( "NightrunnerGame_1_4" , 1 ); // TODO: su questo ci sarebbe da fare il delete
            
            portal2->setLinkedGame( game1_4 );
            portal1->setVisible(false);
            portal3->setVisible(false);
                        
        } else {
            
            string phoneme = dataProvider->getCurrentDBKnowledgeBubble()->getPhoneme();
            if ( (currentEpisodeNum == 2) && (phoneme.find("_") != std::string::npos) ) { // todo syria: controllare questo if
                // phoneme contains _   --> is a writing
                
                portal1->showInClosedState();
                portal2->showInClosedState();
                portal3->showInClosedState();
                
                portal1->setVisible(false);
                portal2->setVisible(false);
                portal3->setVisible(false);
                
                int randomInt = rand() % 1000;
                if (randomInt < 333) {
                    portal1->setLinkedGame( dataProvider->getCurrentIntensifier()->getDBGame() );
                    portal1->setPosition( portal2->getPosition() );
                    portal1->setVisible(true);
                } else if (randomInt < 666) {
                    portal2->setLinkedGame( dataProvider->getCurrentIntensifier()->getDBGame() );
                    portal2->setVisible(true);
                } else {
                    portal3->setLinkedGame( dataProvider->getCurrentIntensifier()->getDBGame() );
                    portal3->setPosition( portal2->getPosition() );
                    portal3->setVisible(true);
                }
                
                
            } else {
                portal2->setLinkedGame( dataProvider->getCurrentIntensifier()->getDBGame() );
                portal1->setVisible(false);
                portal3->setVisible(false);
            }
        }
        
        
        
        
        Sprite* bgSprite = static_cast<Sprite*>(rootNode->getChildByName("fondo") );
        string bgImageName = PATH + "PNG/Background_skin/Ep_"+ StringUtility::toString(currentEpisodeNum) +"/bk_boss.png";
        bgSprite->setTexture(bgImageName);
        
        
        rootNode->getChildByName("InventoryButton")->setVisible(false);
        
        
        inventory = new Inventory(*rootNode, Vec2(640.f, _director->getWinSize().height / 2 + 140.f), PATH + "CSD/Inventories/Inventory_ep"+ StringUtility::toString( currentEpisodeNum ) +".csb", _eventDispatcher, this);
        
        
        simpleAudioEngine->playBackgroundMusic("common/audio/bg/BOSS_NIGHTRUNNER.mp3", true);
        return;
    }
    
    nightrunnerObj = nullptr;
    
    simpleAudioEngine->playBackgroundMusic("common/audio/bg/WATCHMAN.mp3", true);
    
   
    stateCalculator = new WatchmanSceneStateCalculator(*this);
    stateCalculator->calculateState();
  
    
    
    
    
    skin = dataProvider->getCurrentDBWatchman()->getNumber();
    
    setKnowledgeBubbles();
    
    setPortals();
    
    //watchmanObj = new GameObject(*rootNode, "Watchman", PATH + "CSD/nonno_skin_"+ StringUtility::toString(skin) +".csb");
    
    
    Sprite* bgSprite = static_cast<Sprite*>(rootNode->getChildByName("fondo") );
    string bgImageName = PATH + "PNG/Background_skin/Ep_"+ StringUtility::toString(currentEpisodeNum) +"/bk_"+ StringUtility::toString(skin) +".png";
    bgSprite->setTexture(bgImageName);
    
    Node* watchmanPlaceholder = rootNode->getChildByName("WatchmanPlaceholder");
    string watchmanObjCsbPath = PATH + "CSD/Watchman_Skin/Ep_"+ StringUtility::toString(currentEpisodeNum) +"/skin_"+ StringUtility::toString(skin) +".csb";
    watchmanObj = new WatchmanSceneGrandpa(*watchmanPlaceholder, Vec2::ZERO, _eventDispatcher, this, skin, watchmanObjCsbPath);
   
    watchmanObj->play("standing", nullptr, true);
    
	inventory = new Inventory(*rootNode, Vec2(640.f, _director->getWinSize().height / 2 + 140.f), PATH + "CSD/Inventories/Inventory_ep"+ StringUtility::toString( currentEpisodeNum ) +".csb", _eventDispatcher, this);
    inventoryButton = new InventoryButton(*rootNode, "InventoryButton", _eventDispatcher, this, inventory);
    
    inventoryButton->setPosition(Point(inventoryButton->getPosition().x, _director->getWinSize().height - 70));
    
    
    if (dataProvider->isIntensifierGameTurn)  {
        // hide and block the inventory button
        inventoryButton->setVisible(false);
        inventoryButton->setTouchable(false);
    } else {
        
        touchableGameObjects.push_back(inventoryButton);
    }
    
}

void WatchmanScene::setPortals() {
    portal1 = new Portal(*rootNode, "Portal1", PATH + "CSD/portal.csb", "Sprite", _eventDispatcher);
    portal2 = new Portal(*rootNode, "Portal2", PATH + "CSD/portal.csb", "Sprite", _eventDispatcher);
    portal3 = new Portal(*rootNode, "Portal3", PATH + "CSD/portal.csb", "Sprite", _eventDispatcher);
    
    CCLOG("..portal.. currentPhoeme = %s", dataProvider->getCurrentDBKnowledgeBubble()->getPhoneme().c_str());
    
    vectorGamesPortals = dataProvider->getDBGames( *dataProvider->getCurrentDBKnowledgeBubble() );
    int idx = 1;
    for (auto iterator = vectorGamesPortals.begin(); iterator != vectorGamesPortals.end(); ++iterator) {
        DBGame *dbgame = *iterator;
        string gameName = dbgame->getName();
        CCLOG("..........portal game = %s ", dbgame->getName().c_str() );
        // CCLOG("..........portal skin = %d ", dbgame->getSkin() );
        bool justCompleted = false;
        if (  gameName == dataProvider->getLastCompletedGame() ) justCompleted = true;
        if (idx == 1) {
            
            if (dataProvider->isIntensifierGameTurn) {   // gioco rafforzativo
                portal1->setLinkedGame( dataProvider->getCurrentIntensifier()->getDBGame() );
            } else {
                portal1->setLinkedGame(dbgame);
            }
            
            cocos2d::UserDefault *userDef=cocos2d::UserDefault::getInstance();
            if ( (dataProvider->getCurrentEpisode() == 2) && (dbgame->getName()=="WritingLetters") ) {
                if (userDef->getBoolForKey(gameName.append("_completedPortal1").c_str(), false)) {
                    portal1->setLinkedGameIsCompleted(justCompleted);
                }
            } else {
                if (userDef->getBoolForKey(gameName.append("_completed").c_str(), false)) {
                    portal1->setLinkedGameIsCompleted(justCompleted);
                }
            }
            
        }
        else if (idx == 2) {
            portal2->setLinkedGame(dbgame);
            cocos2d::UserDefault *userDef=cocos2d::UserDefault::getInstance();
            if ( (dataProvider->getCurrentEpisode() == 2) && (dbgame->getName()=="WritingLetters") ) {
                if (userDef->getBoolForKey(gameName.append("_completedPortal2").c_str(), false)) {
                    portal2->setLinkedGameIsCompleted(justCompleted);
                }
            } else {
                if (userDef->getBoolForKey(gameName.append("_completed").c_str(), false)) {
                    portal2->setLinkedGameIsCompleted(justCompleted);
                }
            }
        }
        else if (idx == 3) {
            portal3->setLinkedGame(dbgame);
            cocos2d::UserDefault *userDef=cocos2d::UserDefault::getInstance();
            if ( (dataProvider->getCurrentEpisode() == 2) && (dbgame->getName()=="WritingLetters") ) {
                if (userDef->getBoolForKey(gameName.append("_completedPortal3").c_str(), false)) {
                    portal3->setLinkedGameIsCompleted(justCompleted);
                }
            } else {
                if (userDef->getBoolForKey(gameName.append("_completed").c_str(), false)) {
                    portal3->setLinkedGameIsCompleted(justCompleted);
                }
            }
        }
        
        idx++;
    }
}




void WatchmanScene::showPortals() {
    
    if ( state == WatchmanScene::SHOW_3_PORTALS ) {
    
        portal1->showInClosedState();
        portal2->showInClosedState();
        portal3->showInClosedState();
        
    } else if ( state == WatchmanScene::SHOW_2_PORTALS ) {
        
        portal3->setVisible(false);
        portal2->setPosition( portal3->getPosition() );
        
        portal1->setPosition( Vec2( portal1->getPosition().x + 150, portal1->getPosition().y ));
        portal2->setPosition( Vec2( portal2->getPosition().x - 150, portal2->getPosition().y ));
        
        portal1->showInClosedState();
        portal2->showInClosedState();
        
    } else if ( state == WatchmanScene::SHOW_1_PORTAL ) {
        
        
        string phoneme = dataProvider->getCurrentDBKnowledgeBubble()->getPhoneme();
        
        if ( (dataProvider->isIntensifierGameTurn) && (dataProvider->getCurrentEpisode() == 2) && (phoneme.find("_") != std::string::npos) ) {
            
            portal1->showInClosedState();
            portal2->showInClosedState();
            portal3->showInClosedState();
            
            portal1->setVisible(false);
            portal2->setVisible(false);
            portal3->setVisible(false);
            
            int randomInt = rand() % 1000;
            if (randomInt < 333) {
                portal1->setLinkedGame( dataProvider->getCurrentIntensifier()->getDBGame() );
                portal1->setPosition( portal2->getPosition() );
                portal1->setVisible(true);
            } else if (randomInt < 666) {
                portal2->setLinkedGame( dataProvider->getCurrentIntensifier()->getDBGame() );
                portal2->setVisible(true);
            } else {
                portal3->setLinkedGame( dataProvider->getCurrentIntensifier()->getDBGame() );
                portal3->setPosition( portal2->getPosition() );
                portal3->setVisible(true);
            }
            
        } else {
            portal2->setVisible(false);
            portal3->setVisible(false);
            portal1->setPosition( portal2->getPosition() );
            // ? portal1->hideGreenPortal();
            portal1->showInClosedState();
        }
        
   
  
    }
    
}


void WatchmanScene::fadeIn() {

    if (mustShowNightRunnerScene) {
        dataProvider->setNightRunnerUnlockedForEpisode(dataProvider->getCurrentEpisode());
        // WatchmanScene::NIGHTRUNNER_ACTIVE = true;
        watchmanObj->play("talk");
        simpleAudioEngine->playEffect((PATH + "Audio/main/Granpa/man/Main_scene/Granpa_Ohno.mp3").c_str());
        showNightRunnerScene();
        return;
    }
    if (WatchmanScene::NIGHTRUNNER_ACTIVE) {
        enableTouch();
        this->scheduleUpdate();
        sema->setVisible(true);
        sema->walkIn();
        
        portal2->hideGreenPortal();
        portal2->moveIn(0.0f);
        
        if (dataProvider->getWatchmanReaction() == GOOD_REACTION) {
            
            NIGHTRUNNER_HEARTS++;
            simpleAudioEngine->playEffect((PATH + "Audio/nightrunner/Hearth_ko.mp3").c_str());
            
           
            nightrunnerObj->play("talk", [&]() {
                nightrunnerObj->play("talk", [&]() {
                    nightrunnerObj->play("standing", nullptr, true);
                    nightrunnerObj->getActionTimeline()->clearLastFrameCallFunc();
                });
            });
            
            
            if ( NIGHTRUNNER_HEARTS == 1) {
                heart1->play("hit");
                
                simpleAudioEngine->playEffect((PATH + "Audio/nightrunner/WelDone(hearth1_2).mp3").c_str());
            
            } else if ( NIGHTRUNNER_HEARTS == 2) {
                heart2->play("hit");
                
                simpleAudioEngine->playEffect((PATH + "Audio/nightrunner/WelDone(hearth1_2).mp3").c_str());
            
            } else if ( NIGHTRUNNER_HEARTS == 3) {
                heart3->play("hit");
                
                simpleAudioEngine->playEffect((PATH + "Audio/nightrunner/NotBad(hearth3_4).mp3").c_str());
                
            } else if ( NIGHTRUNNER_HEARTS == 4) {
                heart4->play("hit");
                
                simpleAudioEngine->playEffect((PATH + "Audio/nightrunner/NotBad(hearth3_4).mp3").c_str());
            
            } else if ( NIGHTRUNNER_HEARTS == 5) {
                heart5->play("hit");
                
                simpleAudioEngine->playEffect((PATH + "Audio/nightrunner/impossible_(hearth5).mp3").c_str());
                
                CCLOG("-----------------------END!");
                showNightRunnerFinalAnimation();
            }
            
            
        } else {
            
            simpleAudioEngine->playEffect((PATH + "Audio/nightrunner/laugh(beginning).mp3").c_str());
            nightrunnerObj->play("laugh", [&]() {
                nightrunnerObj->play("standing", nullptr, true);
                nightrunnerObj->getActionTimeline()->clearLastFrameCallFunc();
            });
        }
        
        return;
    }
    
    
    string ph = dataProvider->getCurrentDBKnowledgeBubble()->getPhoneme();
   
    if (  (StringUtility::startsWith( ph  , "Photo")) ||  (StringUtility::startsWith( ph  , "Social")) ||  (StringUtility::startsWith( ph  , "Emotional")) ) {
        openGameDirectly( ph );
        return;
    }
    if (StringUtility::startsWith( ph  , "Health")) {
     
        runAction(
            Sequence::createWithTwoActions(
                        DelayTime::create(2*TRANSITION_TIME),
                        CallFunc::create([=]() {
                            simpleAudioEngine->stopBackgroundMusic();
                            simpleAudioEngine->stopAllEffects();
                            Logger::getInstance()->logEvent("Watchman", Logger::CLOSE, "");
                            Director::getInstance()->replaceScene(TransitionSlideInR::create(TRANSITION_TIME, HealthGame::createScene()));
                        })
            )
        );
        
        return;
    }
    
    
    inventory->bringToFront(); // necessary to bring inventory in front to the "back to map" button
    
    if (newPhonemeDiscovered) {
        
        newPhonemeDiscovered = false;
        
        showPortals();
        
        string currentPhoeme = dataProvider->getCurrentDBKnowledgeBubble()->getPhoneme();
        
        if (dataProvider->isNumber(currentPhoeme)) {
            sema->setVisible(true);
            sema->walkIn();
            showNewNumberHelp();
        } else {
            showNewPhoneme_doNextStep();
        }
        
        return;
    }
   
    if (dataProvider->getWatchmanReaction() == GOOD_REACTION) {
        watchmanObj->playGoodReaction();
    } else if (dataProvider->getWatchmanReaction() == BAD_REACTION) {
        watchmanObj->playBadReaction();
    }
    
    
    
    sema->setVisible(true);
    sema->walkIn();
    enableTouch();
    this->scheduleUpdate();
    
    showPortals();

   
}

void WatchmanScene::enableTouch() {

	// CCLOG("WatchmanScene - Enable touch");

	if (ENABLE_TOUCH) {

		touchListener = EventListenerTouchOneByOne::create();

		touchListener->onTouchBegan = CC_CALLBACK_2(WatchmanScene::onTouchBegan, this);
		touchListener->onTouchMoved = CC_CALLBACK_2(WatchmanScene::onTouchMoved, this);
		touchListener->onTouchEnded = CC_CALLBACK_2(WatchmanScene::onTouchEnded, this);

		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, rootNode);

	} else {

		touchListener = nullptr;

	}

	// Enable drag on draggableGameObjects
	for (vector<TouchableGameObject*>::iterator iterator = touchableGameObjects.begin(); iterator != touchableGameObjects.end(); ++iterator) {
		(*iterator)->setTouchable(true);
	}

}

void WatchmanScene::disableTouch() {

	CCLOG("Game - Disable touch");

	if (ENABLE_TOUCH) {

		_eventDispatcher->removeEventListener(touchListener);
		touchListener = nullptr;
	}

	// Disable drag on touchableGameObjects
	for (vector<TouchableGameObject*>::iterator iterator = touchableGameObjects.begin(); iterator != touchableGameObjects.end(); ++iterator) {
		(*iterator)->setTouchable(false);
	}

}

bool WatchmanScene::onTouchBegan(Touch* touch, Event* event) {

	// Manage the start of a touch event
	touching = true;

	return true;

}

void WatchmanScene::onTouchMoved(Touch* touch, Event* event) {

	// Manage a touch event
}

void WatchmanScene::onTouchEnded(Touch* touch, Event* event) {

	// Manage the end of a touch event
	touching = false;

}

void WatchmanScene::endGame(string gameName) {

	CCLOG("WatchmanScene - End game");
    simpleAudioEngine->stopBackgroundMusic();
    simpleAudioEngine->stopAllEffects();
    Logger::getInstance()->logEvent("Watchman", Logger::CLOSE, "");
    
    dataProvider->inGame = true;
    
	if (gameName.compare("PenaltyKick") == 0) {
        TunnelLoop::NEXT_SCENE_CREATE_SCENE = PenaltyKickGame::createScene;
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, TunnelLoop::createScene(), TRANSITION_COLOR));
        
	} else if (gameName.compare("Platform") == 0) {
                
        //TunnelLoop::NEXT_SCENE_CREATE_SCENE = PlatformGame2::createScene;
        TunnelLoop::NEXT_SCENE_CREATE_SCENE = PlatformGame2::createScene;
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, TunnelLoop::createScene(), TRANSITION_COLOR));
    
    } else if (gameName.compare("FallingLetters") == 0) {
        if (dataProvider->getCurrentEpisode() == 2) {
            TunnelLoop::NEXT_SCENE_CREATE_SCENE = FallingLettersEp2::createScene;
        } else {
            TunnelLoop::NEXT_SCENE_CREATE_SCENE = FallingLetters::createScene;
        }
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, TunnelLoop::createScene(), TRANSITION_COLOR));
    } else if (gameName.compare("WritingLetters") == 0) {
        
        TunnelLoop::NEXT_SCENE_CREATE_SCENE = LettersGame::createScene;
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, TunnelLoop::createScene(), TRANSITION_COLOR));
    } else if (gameName.compare("BodyParts") == 0) {
        TunnelLoop::NEXT_SCENE_CREATE_SCENE = Bodyparts::createScene;
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, TunnelLoop::createScene(), TRANSITION_COLOR));
        
    } else if (gameName.compare("TubGame") == 0) {
        TunnelLoop::NEXT_SCENE_CREATE_SCENE = TubGame::createScene;
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, TunnelLoop::createScene(), TRANSITION_COLOR));
        
    } else if (gameName.compare("WordReading") == 0) {
        WordReading::NAME = gameName;
        TunnelLoop::NEXT_SCENE_CREATE_SCENE = WordReading::createScene;
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, TunnelLoop::createScene(), TRANSITION_COLOR));
    
    } else if (gameName.compare("SentenceReading") == 0) {
        WordReading::NAME = gameName;
        TunnelLoop::NEXT_SCENE_CREATE_SCENE = WordReading::createScene;
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, TunnelLoop::createScene(), TRANSITION_COLOR));
        
    } else if (gameName.compare("ListComprehens") == 0) {
        ListComprehens::NAME = gameName;
        TunnelLoop::NEXT_SCENE_CREATE_SCENE = ListComprehens::createScene;
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, TunnelLoop::createScene(), TRANSITION_COLOR));
    } else if (gameName.compare("ReadComprehens") == 0) {
        ListComprehens::NAME = gameName;
        TunnelLoop::NEXT_SCENE_CREATE_SCENE = ListComprehens::createScene;
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, TunnelLoop::createScene(), TRANSITION_COLOR));
    } else if (gameName.compare("OralPassage") == 0) {
        TunnelLoop::NEXT_SCENE_CREATE_SCENE = OralPassage::createScene;
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, TunnelLoop::createScene(), TRANSITION_COLOR));

    } else if (gameName.compare("ShapeNaming") == 0) {
        TunnelLoop::NEXT_SCENE_CREATE_SCENE = ShapesGame::createScene;
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, TunnelLoop::createScene(), TRANSITION_COLOR));
        
    } else if (gameName.compare("ShapeIdentifier") == 0) {
        TunnelLoop::NEXT_SCENE_CREATE_SCENE = ShapesGame2::createScene;
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, TunnelLoop::createScene(), TRANSITION_COLOR));
        
    } else if (gameName.compare("ShuffledSentence") == 0) {
        TunnelLoop::NEXT_SCENE_CREATE_SCENE = ShuffledSentence::createScene;
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, TunnelLoop::createScene(), TRANSITION_COLOR));
        
    } else if (gameName.compare("NightrunnerGame_1_4") == 0) {
        TunnelLoop::NEXT_SCENE_CREATE_SCENE = NightrunnerGame_1_4::createScene;
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, TunnelLoop::createScene(), TRANSITION_COLOR));
        
    } else if (gameName.compare("WordDictation") == 0) {
        WordDictation::NAME = gameName;
        string currentPhoneme =  dataProvider->getCurrentDBKnowledgeBubble()->getPhoneme();
        vector<string> wordsVector = dataProvider->getWordsForGame( currentPhoneme, "wordDictation" );
        
        dataProvider->setVectorWordsForGame( wordsVector);
        for (vector<string>::iterator iterator = wordsVector.begin(); iterator != wordsVector.end(); ++iterator) {
            CCLOG("WD parole = %s", (*iterator).c_str() );
        }
        
        TunnelLoop::NEXT_SCENE_CREATE_SCENE = WordDictation::createScene;
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, TunnelLoop::createScene(), TRANSITION_COLOR));
        
    } else if (gameName.compare("SentenceDictation") == 0) {
        
        SentenceDictation::NAME = gameName;
        string currentPhoneme =  dataProvider->getCurrentDBKnowledgeBubble()->getPhoneme();
        vector<string> wordsVector = dataProvider->getWordsForGame( currentPhoneme, "sentenceDictation" );
        CCLOG("SD currentPhoneme = %s", currentPhoneme.c_str());
        dataProvider->setVectorWordsForGame( wordsVector);
        for (vector<string>::iterator iterator = wordsVector.begin(); iterator != wordsVector.end(); ++iterator) {
            CCLOG("SD parole = %s", (*iterator).c_str() );
        }
        
        TunnelLoop::NEXT_SCENE_CREATE_SCENE = SentenceDictation::createScene;
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, TunnelLoop::createScene(), TRANSITION_COLOR));
        
    } else if (gameName.compare("Blending1") == 0) {
        
        Blending1Game::PATH = "Blending1Game/skin_" + StringUtility::toString( dataProvider->getSkin() ) + "/";
     
        string currentPhoneme =  dataProvider->getCurrentDBKnowledgeBubble()->getPhoneme();
        vector<string> wordsVectorWords = dataProvider->getWordsForGame( currentPhoneme, "blending" );
       
       
        vector<string> wordsVectorOnlyAudio;
        for (vector<string>::iterator iterator = wordsVectorWords.begin(); iterator != wordsVectorWords.end(); ++iterator) {
            string wordOnlyAudio = (*iterator);
            wordOnlyAudio += "ONLYAUDIO";
            wordsVectorOnlyAudio.push_back(wordOnlyAudio);
            //CCLOG("parole = %s", (*iterator).c_str() );
        }
        
        vector<string> wordsVectorComplete;
        
        for (int i = 0; i < wordsVectorWords.size(); i++) {
            wordsVectorComplete.push_back(wordsVectorWords[i]);
            wordsVectorComplete.push_back(wordsVectorOnlyAudio[i]);
        }
        
        // Shuffle wordsVector
        //random_shuffle(wordsVector.begin(), wordsVector.end()); // TODO: controllare se è corretto
        
        reverse(wordsVectorComplete.begin(), wordsVectorComplete.end());
        
        dataProvider->setVectorWordsForGame( wordsVectorComplete);
        Blending1Game::NUM_WORDS = (int)wordsVectorComplete.size();
        
        TunnelLoop::NEXT_SCENE_CREATE_SCENE = Blending1Game::createScene;
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, TunnelLoop::createScene(), TRANSITION_COLOR));
        
    } else {
        CCLOG("Error in WatchmanScene::endGame ! gameName: %s", gameName.c_str() );
    }

}

void WatchmanScene::update(float deltaTime) {

	if ((!touching) && (!sema->isMovingToPortal)) {
        
        Rect semaBoundingBox = sema->getBoundingBox();
        
        Rect portal1BoundingBox = portal1->getBoundingBox();
        Rect portal2BoundingBox = portal2->getBoundingBox();
        Rect portal3BoundingBox = portal3->getBoundingBox();
        
        
        if (sema->isOnPortal == false) {
            // check if sema is intersecting a portal
            
            if (semaBoundingBox.intersectsRect(portal1BoundingBox)) {
                handleSemaIntersectsPortal(portal1);
                return;
            }
            if (semaBoundingBox.intersectsRect(portal2BoundingBox)) {
                handleSemaIntersectsPortal(portal2);
                return;
            }
            if (semaBoundingBox.intersectsRect(portal3BoundingBox)) {
                handleSemaIntersectsPortal(portal3);
                return;
            }
        }
      
	}
    
    
    if (sema->isOnPortal == true) {
        // check if sema is moving out from a portal
        //CCLOG("check if sema is moving out from a portal");
        
        Rect semaBoundingBox = sema->getBoundingBox();
        
        Rect portal1BoundingBox = portal1->getBoundingBox();
        Rect portal2BoundingBox = portal2->getBoundingBox();
        Rect portal3BoundingBox = portal3->getBoundingBox();
        
     
        if (semaBoundingBox.intersectsRect(portal1BoundingBox)) return;
        if (semaBoundingBox.intersectsRect(portal2BoundingBox)) return;
        if (semaBoundingBox.intersectsRect(portal3BoundingBox)) return;
        
        handleSemaMovesOutPortal(sema->getLastPortalWasOn());
    }

}


void WatchmanScene::handleSemaMovesOutPortal(Portal* portal) {
    sema->isOnPortal = false;
    portal->close();
}

void WatchmanScene::handleSemaIntersectsPortal(Portal* portal) {
    if (portal->isVisible() == false) return;
    sema->isOnPortal = true;
    sema->setLastPortalWasOn(portal);
    
    // Game::disableTouch();
    // this->unscheduleUpdate();
    CCLOG("--------handleSemaIntersectsPortal");
    sema->play(
        Sequence::createWithTwoActions(
            MoveTo::create(0.2f, sema->getNode().getParent()->convertToNodeSpace(portal->getPosition())),
                CallFunc::create(
                    [=]() {
                        
                        portal->open();
                        
                        sema->semaFront->play("trans_floating", [=]() {
                            sema->semaFront->play("sema_Float", nullptr, true);
                            sema->semaFront->getActionTimeline()->clearLastFrameCallFunc();
                        });
                       
                    }
                )
            )
    );
}

void WatchmanScene::openGame() {
    CCLOG("Open Game !");
    
    auto scaleDown = ScaleTo::create(0.8, 0.01);
    sema->semaFront->play(scaleDown);
    sema->semaFront->play("salto_portale", [=]() {
        sema->semaFront->setVisible(false);
        // sema->getLastPortalWasOn()->close();
        DBGame *gameToLoad = sema->getLastPortalWasOn()->getLinkedGame();
        CCLOG(">>>> Game to load = %s", gameToLoad->getName().c_str() );
        dataProvider->setSkin( gameToLoad->getSkin() );
        endGame( gameToLoad->getName() );
        
        sema->semaFront->getActionTimeline()->clearLastFrameCallFunc();
    });
    
}


void WatchmanScene::showNewLetterHelp() {
    showNewPhoneme_doNextStep();
    return;
    help = new GameObject(*rootNode, "help_letters", PATH + "CSD/help_letters.csb");
    
    string letter = dataProvider->getCurrentDBKnowledgeBubble()->getPhoneme();
    letter = letter.substr(0, letter.find("_"));
    
    if (dataProvider->getCurrentEpisode() == 3) {
        // letter = StringUtility::toLowerCase(letter);
    }
    if (dataProvider->getCurrentEpisode() == 1) {
        string::size_type idxEp1 = letter.find("#ep1");
        if (idxEp1 != string::npos)
            letter.erase(idxEp1, 4); // 4 is length of "#ep1"
    }
    
    
    // letter / phoneme
    letterHelp = new LabelGameObject(*help->getChild("Striscione_help_sound/Ball_letter"), Vec2::ZERO, "common/fonts/Arabic-Regular.ttf", 300, letter, Color3B(24, 95, 166), true);
    
    // image
    string word = dataProvider->getWordForPhoneme( letter );
    string imageName = "common/images/words/";
    imageName.append( word );
    imageName.append(".png");
    CCLOG("showNewLetterHelp - imageName: %s", imageName.c_str());
    
    Sprite* imgSprite = static_cast<Sprite*>( help->getChild("Striscione_help_sound/Ball_imagine/Ball_letter") );
    imgSprite->setTexture(imageName);
    /////
    rootNode->getChildByName("blackBG")->setOpacity(0);
    rootNode->getChildByName("blackBG")->setVisible(true);
    rootNode->getChildByName("blackBG")->runAction(FadeIn::create(0.5f));
    //
    
    simpleAudioEngine->playEffect((PATH + "Audio/help/Granpa/Granpa_Lets_learn_the_sound.mp3").c_str());
    help->play("help_1", [=]() {
        simpleAudioEngine->playEffect(("common/audio/grandpa/phonemes/" + letter + ".mp3").c_str());
        help->play("help_2", [=]() {
            simpleAudioEngine->playEffect((PATH + "Audio/help/Granpa/Granpa_likein.mp3").c_str());
            help->play("help_3", [=]() {
                simpleAudioEngine->playEffect(("common/audio/grandpa/words/" + word + ".mp3").c_str());
                help->play("help_4", [=]() {
                    simpleAudioEngine->playEffect(("common/audio/grandpa/phonemes/" + letter + ".mp3").c_str());
                    help->play("help_5", [=]() {
                        simpleAudioEngine->playEffect(("common/audio/grandpa/phonemes/" + letter + ".mp3").c_str());
                        help->play("help_6", [=]() {
                            simpleAudioEngine->playEffect(("common/audio/grandpa/words/" + word + ".mp3").c_str());
                            help->play("help_7", [=]() {
                                rootNode->getChildByName("blackBG")->runAction(FadeOut::create(0.5f));
                                help->play("help_8", [=]() {
                                    rootNode->getChildByName("blackBG")->setVisible(false);
                                    showNewPhoneme_doNextStep();
                                    help->getActionTimeline()->clearLastFrameCallFunc();
                                });
                            });
                        });
                    });
                });
            });
        });
    });
    
    
}


void WatchmanScene::showNewNumberHelp() {
    
    help = new GameObject(*rootNode, "Help_Numbers", PATH + "CSD/help_numbers.csb");
    
    string number = dataProvider->getCurrentDBKnowledgeBubble()->getPhoneme();
    
    letterHelp = new LabelGameObject(*help->getChild("Striscione_help_sound/Ball_letter"), Vec2::ZERO, "common/fonts/Arabic-Regular.ttf", 300,  number, Color3B(24, 95, 166), true);
    
    
    simpleAudioEngine->playEffect((PATH + "Audio/help/Granpa/Granpa_Lets_learn_the_number.mp3").c_str());
    help->play("help_1", [=]() {
        simpleAudioEngine->playEffect(("common/audio/sema/phonemes/" + number + ".mp3").c_str());
        help->play("help_2", [=]() {
            simpleAudioEngine->playEffect(("common/audio/sema/phonemes/" + number + ".mp3").c_str());
            help->play("help_3", [=]() {
                help->play("help_4", [=]() {
                    enableTouch();
                    this->scheduleUpdate();
                    help->getActionTimeline()->clearLastFrameCallFunc();
                });
            });
        });
    });
    
    
}



Vec2 WatchmanScene::getBubblePosition(int bubbleNum, int totBubblesNum) {
   
    if (totBubblesNum == 3) {
        if (bubbleNum == 1) return Vec2(398,582);
        if (bubbleNum == 2) return Vec2(635,683);
        if (bubbleNum == 3) return Vec2(866,582);
    } else if (totBubblesNum == 4) {
        if (bubbleNum == 1) return Vec2(395,585);
        if (bubbleNum == 2) return Vec2(558,585);
        if (bubbleNum == 3) return Vec2(722,585);
        if (bubbleNum == 4) return Vec2(885,585);
    } else if (totBubblesNum == 5) {
        if (bubbleNum == 1) return Vec2(477,611);
        if (bubbleNum == 2) return Vec2(640,611);
        if (bubbleNum == 3) return Vec2(804,611);
        if (bubbleNum == 4) return Vec2(558,499);
        if (bubbleNum == 5) return Vec2(721,499);
    } else if (totBubblesNum == 6) {
        
        if (dataProvider->getCurrentEpisode() >= 4) {
            if (bubbleNum == 1) return Vec2(409,537);
            if (bubbleNum == 2) return Vec2(490,611);
            if (bubbleNum == 3) return Vec2(588,658);
            if (bubbleNum == 4) return Vec2(695,658);
            if (bubbleNum == 5) return Vec2(796,611);
            if (bubbleNum == 6) return Vec2(872,537);
        } else {
            if (bubbleNum == 1) return Vec2(480,611);
            if (bubbleNum == 2) return Vec2(642,611);
            if (bubbleNum == 3) return Vec2(806,611);
            if (bubbleNum == 4) return Vec2(480,460);
            if (bubbleNum == 5) return Vec2(642,460);
            if (bubbleNum == 6) return Vec2(806,460);
        }
        
    } else if (totBubblesNum == 7) {
        
        if (dataProvider->getCurrentEpisode() >= 4) {
            if (bubbleNum == 1) return Vec2(351, 529);
            if (bubbleNum == 2) return Vec2(432, 603);
            if (bubbleNum == 3) return Vec2(531, 650);
            if (bubbleNum == 4) return Vec2(639, 666);
            if (bubbleNum == 5) return Vec2(746, 650);
            if (bubbleNum == 6) return Vec2(847, 603);
            if (bubbleNum == 7) return Vec2(928, 529);
        } else {
            if (bubbleNum == 1) return Vec2(395, 611);
            if (bubbleNum == 2) return Vec2(558, 611);
            if (bubbleNum == 3) return Vec2(722, 611);
            if (bubbleNum == 4) return Vec2(885, 611);
            if (bubbleNum == 5) return Vec2(476, 489);
            if (bubbleNum == 6) return Vec2(640, 489);
            if (bubbleNum == 7) return Vec2(804, 489);
        }
        
    }
    return Vec2(0,0);
}


void WatchmanScene::setKnowledgeBubbles() {
    
    dbUnlockedKnowledgeBubbles = dataProvider->getUnlockedDBKnowledgeBubbles(*(dataProvider->getCurrentDBWatchman()));
    dbKnowledgeBubbles_forKB = dataProvider->getDBKnowledgeBubbles(*(dataProvider->getCurrentDBWatchman()));
    
    CCLOG("setKnowledgeBubbles. size: %lu", dbKnowledgeBubbles_forKB.size());
    
    int index = 1;
    for (vector<DBKnowledgeBubble*>::iterator iterator = dbKnowledgeBubbles_forKB.begin(); iterator != dbKnowledgeBubbles_forKB.end(); ++iterator) {
        
        KnowledgeBubble* knowledgeBubble;
        string phonemeValue = (**iterator).getPhoneme();
  
        
        bool indexMustBeDecreased = false;
        if (phonemeValue.find("_") != std::string::npos)  {
            indexMustBeDecreased = true;
        }
        
        phonemeValue = phonemeValue.substr(0, phonemeValue.find("_"));
        
        Vec2 pos =  getBubblePosition(index, (int)dbKnowledgeBubbles_forKB.size() );
        
        if (dataProvider->isNumber( phonemeValue )) {
            knowledgeBubble = new KnowledgeBubble(*rootNode->getChildByName("kbContainer"), "KnowledgeBubble" + StringUtility::toString(index), pos, _eventDispatcher, WatchmanScene::PATH + "CSD/knowledgenumbers.csb", **iterator);
        } else {
            knowledgeBubble = new KnowledgeBubble(*rootNode->getChildByName("kbContainer"), "KnowledgeBubble" + StringUtility::toString(index), pos, _eventDispatcher, WatchmanScene::PATH + "CSD/knowledgeBubble.csb", **iterator);
           // knowledgeBubble->setScale(0.9);
            
            if (dataProvider->getCurrentEpisode() >= 4) {
                indexMustBeDecreased = false;
                string epStr = StringUtility::toString( dataProvider->getCurrentEpisode() );
                knowledgeBubble->setText("");
                knowledgeBubble->setNotCompletedImage(PATH + "PNG/knowledge_spheres/ep"+epStr+"/ball_empty.png");
                knowledgeBubble->setCompletedImage(PATH + "PNG/knowledge_spheres/ep"+epStr+"/ball_full.png");
                knowledgeBubble->setActiveImage(PATH + "PNG/knowledge_spheres/ep"+epStr+"/ball_select.png");
            }
            
        }
        
       
        
        knowledgeBubble->play("Ball_empty");
        
        
        DBKnowledgeBubble *bubble = *iterator;
        
        string bubblePhoneme = bubble->getPhoneme();
        bubblePhoneme = bubblePhoneme.substr(0, bubblePhoneme.find("_"));
        
        string currPhoneme = dataProvider->getCurrentDBKnowledgeBubble()->getPhoneme();
        currPhoneme = currPhoneme.substr(0, currPhoneme.find("_"));
        CCLOG("currPhoneme = %s", currPhoneme.c_str());
            
        if ( (bubble->getPhoneme() == dataProvider->getCurrentDBKnowledgeBubble()->getPhoneme() ) && (dataProvider->isIntensifierGameTurn==false) ) {
            knowledgeBubble->play("ball_active", nullptr, true);
        } else if ( bubblePhoneme == currPhoneme ) {
            knowledgeBubble->play("ball_active", nullptr, true);
        } else {
            
            // check if   bubble->getPhoneme() was previously unlocked
            
            for (vector<DBKnowledgeBubble*>::iterator iterator2 = dbUnlockedKnowledgeBubbles.begin(); iterator2 != dbUnlockedKnowledgeBubbles.end(); ++iterator2) {
               
                string iterator2Phoneme = (*iterator2)->getPhoneme();
                iterator2Phoneme = iterator2Phoneme.substr(0, iterator2Phoneme.find("_"));
                
                
                if ( bubblePhoneme  == iterator2Phoneme ) {
                    knowledgeBubble->play("ball_white_stop");
                }
                
                if ( bubble->getPhoneme()  == (*iterator2)->getPhoneme() ) {
                    knowledgeBubble->play("ball_white_stop");
                }
                
                
            }
            
        }
        
        knowledgeBubbles.push_back(knowledgeBubble);
        //touchableGameObjects.push_back(knowledgeBubble);		// Actually not touchable
        ++index;
        if (indexMustBeDecreased) index--;
    
        
    }
    
}


void WatchmanScene::showNewPhoneme_doNextStep() {
    step++;
    
    switch (step) {
        case 1:
            CCLOG("varie animazioni dell'inventario....");
            inventory->showUnlockedNewKnowledgeBubble( *dataProvider->getCurrentDBKnowledgeBubble(), [=](){ showNewPhoneme_doNextStep(); } );
            break;
        case 2:
            CCLOG("entra sema da sinistra (non draggabile al momento)");
            sema->setVisible(true);
            sema->walkIn();
            showNewPhoneme_doNextStep();
            break;
        case 3:
            // mostro help lettere
            showNewLetterHelp();
            break;
        case 4:
            // CCLOG("step: %d", step);
            watchmanObj->play("talk");
            if ( (dataProvider->getCurrentEpisode()==3)  || (dataProvider->getCurrentEpisode()==9) )  {
                simpleAudioEngine->playEffect((PATH + "Audio/main/Granpa/woman/Main_scene/Granpa_Choose_the_game.mp3").c_str());
            } else {
                simpleAudioEngine->playEffect((PATH + "Audio/main/Granpa/man/Main_scene/Granpa_Choose_the_game.mp3").c_str());
            }            
            showNewPhoneme_doNextStep();
            break;
        case 5:
            enableTouch();
            this->scheduleUpdate();
            break;
    }
    
}

void WatchmanScene::addHomeButton() {
    
    cocos2d::ui::Button *backNode = cocos2d::ui::Button::create("common/homeBtn.png", "common/homeBtn.png", "common/homeBtn.png");
    backNode->setScale(0.9);
    backNode->setName("HomeButton");
    backNode->setAnchorPoint(Vec2(0.5, 0.5));
    
    auto x = 90;
   
    
    float winHeight = cocos2d::Director::getInstance()->getWinSize().height;
    float rootNodeHeight = rootNode->getBoundingBox().size.height;
    
    float y = winHeight;
    if ( winHeight > rootNodeHeight ) { // like iPad
        float delta = (winHeight-rootNodeHeight) / 2;
        y = rootNode->getBoundingBox().size.height + delta - (backNode->getBoundingBox().size.height/2);
    }
    y = y - (backNode->getBoundingBox().size.height /2);
    
    
    backNode->setPosition(Vec2(x, y));
    rootNode->addChild(backNode);
    
    
   
    
    
	backNode->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		switch (type) {
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
            backToMapFromHomeButton();
			break;
		default:
			break;
		}
	});

}

void WatchmanScene::backToMapFromHomeButton() {
    string portalCodeFromHomeButton = string("") + StringUtility::toString( dataProvider->getCurrentDBWatchman()->getEpisode() ) + "-" + StringUtility::toString( dataProvider->getCurrentDBWatchman()->getNumber() ) ;
    CCLOG("portalCodeFromHomeButton = %s", portalCodeFromHomeButton.c_str());
    dataProvider->setSemaInitialPortalCode(portalCodeFromHomeButton);
    
    Logger::getInstance()->logEvent("Watchman", Logger::CLOSE, "");
    simpleAudioEngine->stopAllEffects();
    simpleAudioEngine->stopBackgroundMusic();
    _director->replaceScene(TransitionFade::create(TRANSITION_TIME, MapScene::createScene(), TRANSITION_COLOR));
}

void WatchmanScene::showNightRunnerScene() {
    
    CCLOG("showNightRunnerScene funciton");
    
    runAction(
        Sequence::createWithTwoActions(
             DelayTime::create(2.5f),
             CallFunc::create(
                    [=]() {
                     simpleAudioEngine->stopAllEffects();
                     simpleAudioEngine->stopBackgroundMusic();
                     Logger::getInstance()->logEvent("Watchman", Logger::CLOSE, "");
                     Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, MapScene::createScene(), TRANSITION_COLOR));
             })
        )
    );
}



void WatchmanScene::setNightRunnerHearts() {
    
    heart1 = new GameObject(*rootNode->getChildByName("kbContainer"), Vec2(364,563), PATH + "CSD/boss_life.csb");
   // heart1->setScale(0.9);
    heart2 = new GameObject(*rootNode->getChildByName("kbContainer"), Vec2(500,620), PATH + "CSD/boss_life.csb");
   // heart2->setScale(0.9);
    heart3 = new GameObject(*rootNode->getChildByName("kbContainer"), Vec2(640,653), PATH + "CSD/boss_life.csb");
   // heart3->setScale(0.9);
    heart4 = new GameObject(*rootNode->getChildByName("kbContainer"), Vec2(780,620), PATH + "CSD/boss_life.csb");
   // heart4->setScale(0.9);
    heart5 = new GameObject(*rootNode->getChildByName("kbContainer"), Vec2(916,563), PATH + "CSD/boss_life.csb");
   // heart5->setScale(0.9);
    
    
    if (NIGHTRUNNER_HEARTS == -1) {
        // is the first time
        simpleAudioEngine->playEffect((PATH + "Audio/nightrunner/LetsSee(beginning).mp3").c_str());
        nightrunnerObj->play("talk");
        heart1->play("pop", [=]() {
            heart2->play("pop", [=]() {
                heart3->play("pop", [=]() {
                    heart4->play("pop", [=]() {
                        heart5->play("pop", [=]() {
                            NIGHTRUNNER_HEARTS = 0;
                            heart5->getActionTimeline()->clearLastFrameCallFunc();
                        });
                        heart4->getActionTimeline()->clearLastFrameCallFunc();
                    });
                    heart3->getActionTimeline()->clearLastFrameCallFunc();
                });
                heart2->getActionTimeline()->clearLastFrameCallFunc();
            });
            heart1->getActionTimeline()->clearLastFrameCallFunc();
        });
    } else {
        
        CCLOG("-----------------------NIGHTRUNNER_HEARTS %d", NIGHTRUNNER_HEARTS);
        
        switch (NIGHTRUNNER_HEARTS) {
                
            case 0:
                heart1->getActionTimeline()->gotoFrameAndPause(30);
            case 1:
                heart2->getActionTimeline()->gotoFrameAndPause(30);
            case 2:
                heart3->getActionTimeline()->gotoFrameAndPause(30);
            case 3:
                heart4->getActionTimeline()->gotoFrameAndPause(30);
            case 4:
                heart5->getActionTimeline()->gotoFrameAndPause(30);
                
        }
        
        
    
    }
    

}

void WatchmanScene::showNightRunnerFinalAnimation() {
    CCLOG("------showNightRunnerFinalAnimation");
    /*
    auto fadeOut = FadeOut::create(1.1f);
    spotLight->runAction(fadeOut);
    */
    inventory->showNightrunnerAnimation();
    
    WatchmanScene::NIGHTRUNNER_ACTIVE = false;
    WatchmanScene::NIGHTRUNNER_HEARTS = -1;
}

void WatchmanScene::openGameDirectly(string phonemeOfGame) {
    
    CCLOG("openPhotoScene da WatchmanScene");
    
    simpleAudioEngine->stopBackgroundMusic();
    simpleAudioEngine->playBackgroundMusic("TunnelLoop/audio/loop.mp3", true);
    
    auto frameSize =  rootNode->getBoundingBox().size;
    
    // background
    Node* bg = CSLoader::createNode("TunnelLoop/Passaggio.csb");
    cocostudio::timeline::ActionTimeline* bgTimeline = CSLoader::createTimeline("TunnelLoop/Passaggio.csb");
    bg->setPosition(Vec2(frameSize.width / 2, frameSize.height / 2));
    rootNode->addChild(bg);
    bg->runAction(bgTimeline);
    bgTimeline->play("passaggio_loop", false);
    
    bgTimeline->setLastFrameCallFunc([this, bgTimeline, phonemeOfGame](){
        simpleAudioEngine->stopBackgroundMusic();
        simpleAudioEngine->stopAllEffects();
        Logger::getInstance()->logEvent("Watchman", Logger::CLOSE, "");
        Scene* scene;
        if (StringUtility::startsWith( phonemeOfGame  , "Photo"))  scene = PhotoScene::createScene();
        else if (StringUtility::startsWith( phonemeOfGame  , "Social"))  scene = SocialWeal::createScene();
        else if (StringUtility::startsWith( phonemeOfGame  , "Emotional"))  scene = EmotionalGame::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene, TRANSITION_COLOR));
        bgTimeline->clearLastFrameCallFunc();
    });
    
    // sema
    Node* semaTunnel = CSLoader::createNode("WatchmanScene/CSD/Sema_front.csb");
    cocostudio::timeline::ActionTimeline* semaTunnelTimeline = CSLoader::createTimeline("WatchmanScene/CSD/Sema_front.csb");
    semaTunnel->setPosition(Vec2(640.0f, 200.0f));
    rootNode->addChild(semaTunnel);
    semaTunnel->runAction(semaTunnelTimeline);
    semaTunnelTimeline->play("Sema_Vola", true);
    
}

