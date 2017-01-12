#include "MapScene.h"
#include "../Utils/Data/DataProvider.h"
#include "../Utils/Data/Logger.h"
#include "../Utils/CocosCamera/CocosCamera.h"
#include "../AppMacros.h"
#include "MapEpisode.h"
#include "MapPortal.h"
#include "MapPortalPlay.h"
#include "../WatchmanScene/WatchmanScene.h"
#include "../Utils/StringUtility.h"
#include "../VideoScene/VideoScene.h"

const bool MapScene::ENABLE_TOUCH = true;								// Used to disable tutorial on first touch and manage general touch events
const string MapScene::PATH = "MapScene/";								// Resources' subfolder path for this game

Scene* MapScene::createScene() {

	// 'scene' is an autorelease object
	Scene* scene = Scene::create();

	// 'layer' is an autorelease object			 
	auto layer = MapScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;

}

MapScene::~MapScene() {

	// CCLOG("~MapScene");
    
    this->unscheduleUpdate();
    
    _eventDispatcher->removeEventListener(moveMapEventHandler);
    _eventDispatcher->removeEventListener(portalTouchedEventHandler);
    _eventDispatcher->removeEventListener(portalPlayTouchedEventHandler);

  
    for (vector<MapEpisode*>::iterator iterator = episodesVector.begin(); iterator != episodesVector.end(); ++iterator) {
        delete (*iterator);
    }
    episodesVector.clear();
    
    // lastTappedPortal must not be deleted !!
    
   
}

bool MapScene::init() {

	if (!Layer::init())
	{
		return false;
	}
	
	rootNode = CSLoader::createNode(PATH + "MainScene.csb");

	rootNode->setAnchorPoint(Point(0.5, 0.5));
	rootNode->setPosition(Point(_director->getWinSize().width / 2, _director->getWinSize().height / 2));
	addChild(rootNode);
    
    //////
    
	startGame();

	return true;

}



void MapScene::startGame() {

	Logger::getInstance()->logEvent("MapScene", Logger::OPEN, "");
    

	initVariables();
	initAudio();
	initGameObjects();
	fadeIn();
    
 
}

void MapScene::initVariables() {
    
	dataProvider = DataProvider::getInstance();
    
    scrollContainer = rootNode->getChildByName("scrollContainer");
    
    canSwipe = false;
    gameTime = 0;
    hasTocalculateTime =false;
    scrollIndex = 1;
    currentMapPosition = 1;
    
    
    WatchmanScene::NIGHTRUNNER_ACTIVE = false;
    WatchmanScene::NIGHTRUNNER_HEARTS = -1;
    
    lastTappedPortal = nullptr;

    episodesVector.push_back(nullptr);
    episodesVector.push_back(nullptr);
    episodesVector.push_back(nullptr);
    episodesVector.push_back(nullptr);
    episodesVector.push_back(nullptr);
    episodesVector.push_back(nullptr);
    episodesVector.push_back(nullptr);
    episodesVector.push_back(nullptr);
    episodesVector.push_back(nullptr);
    episodesVector.push_back(nullptr);
    
    
    //
    
    moveMapEventHandler = EventListenerCustom::create("MoveMapToEpisodeEvent", [=](EventCustom* event){
        
        string portalNumToGo = "";
        char* buf = static_cast<char*>(event->getUserData());
        portalNumToGo += buf;
        
        // CCLOG("MoveMapToEpisodeEventHandler... %s", portalNumToGo.c_str());
        moveMapToEpisode( StringUtility::stringToNumber<int>(portalNumToGo) );
        
    });
    _eventDispatcher->addEventListenerWithFixedPriority(moveMapEventHandler, 1);
    //
    
    portalTouchedEventHandler = EventListenerCustom::create("PortalTouchedEvent", [=](EventCustom* event){
        
        auto portal = static_cast<MapPortal*>(event->getUserData());
        
        CCLOG("portalTouchedEventHandler");
        portal->play("portal_tap");
        if (lastTappedPortal != nullptr) {
            lastTappedPortal->hidePlayButton();
        }
        lastTappedPortal = portal;
        sema->jumpToPortal(portal);
        
    });
    _eventDispatcher->addEventListenerWithFixedPriority(portalTouchedEventHandler, 1);
    
    
    portalPlayTouchedEventHandler = EventListenerCustom::create("PortalPlayTouchedEvent", [=](EventCustom* event){
        
        dataProvider->resetGamesCompleted();

        
        string portalCodeToOpen = lastTappedPortal->getPortalCode();
        CCLOG("portalCodeToOpen = %s", portalCodeToOpen.c_str());
        vector<string> portalCodeSplitted = StringUtility::split(portalCodeToOpen, '-');
        string episodeNumStr = portalCodeSplitted.at(0);
        string watchmanNumStr = portalCodeSplitted.at(1);
        int episodeNumInt = StringUtility::stringToNumber<int>(episodeNumStr);
        int watchmanNumInt = StringUtility::stringToNumber<int>(watchmanNumStr);
        
        dataProvider->setSemaInitialPortalCode(portalCodeToOpen);
        
        dataProvider->setCurrentDBWatchman(new DBWatchman( StringUtility::stringToNumber<int>(episodeNumStr) , StringUtility::stringToNumber<int>(watchmanNumStr) )); // todo: su questo new andrebbe fatto un delete
      
        
        lastTappedPortal->play("portal_jump_inside");
      
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("MapScene/audio/PortaljumpInside.wav");
        sema->play("minisema_jump_inside", [=]() {
            
            dataProvider->setWatchmanReaction(WatchmanScene::NONE_REACTION);
            Logger::getInstance()->logEvent("MapScene", Logger::CLOSE, "");
            simpleAudioEngine->stopBackgroundMusic();
            
            if ( lastTappedPortal->isVideo() ) {
            
                
                dataProvider->setCurrentDBKnowledgeBubble(new DBKnowledgeBubble("Video"+  episodeNumStr, true) ); // todo: su questo new andrebbe fatto un delete
                
                
                VideoScene::VIDEO_PATH = "Videos/video"+  episodeNumStr + ".mp4";
                VideoScene::NEXT_SCENE_CREATE_SCENE = MapScene::createScene;
                Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, VideoScene::createScene(), TRANSITION_COLOR));

                if (dataProvider->nextPhonemeIsLocked() ) {
                    dataProvider->setMustUnlockNewPortalMap(true);
                }                
                dataProvider->updateCurrentStatusToNext();
             
            } else if ( lastTappedPortal->isNightrunner() ) {
                
                WatchmanScene::NIGHTRUNNER_ACTIVE = true;
                
                Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, WatchmanScene::createScene(), TRANSITION_COLOR));
                
            } else {
                
                int lastUnlockedEpisode = dataProvider->getLastUnlockedEpisodeNum();
                int lastUnlockedWatchman = dataProvider->getLastUnlockedWatchmanNum();
                
                if ( (lastUnlockedEpisode == episodeNumInt)  && (lastUnlockedWatchman == watchmanNumInt) ){
                    
                    dataProvider->setStatusFromLatestUnlockedPhoneme();
                    
                } else {
                    
                    string phoneme = dataProvider->getPhonemeForPortalCode(portalCodeToOpen);
                    dataProvider->setCurrentDBKnowledgeBubble(new DBKnowledgeBubble(phoneme, true) ); // todo: su questo new andrebbe fatto un delete
                    
                }
                
               
                Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, WatchmanScene::createScene(), TRANSITION_COLOR));
                
               
                
            }
            
             sema->clearLastFrameCallFunc(); // todo: controllare che sia corretto
           
        });
      
    });
    _eventDispatcher->addEventListenerWithFixedPriority(portalPlayTouchedEventHandler, 1);
    
    
}

void MapScene::initAudio() {

	simpleAudioEngine = SimpleAudioEngine::getInstance();
   
    simpleAudioEngine->preloadBackgroundMusic("common/audio/bg/MAP.mp3");
    
    simpleAudioEngine->playBackgroundMusic("common/audio/bg/MAP.mp3", true);
}

void MapScene::initGameObjects() {
    
    
    dataProvider->resetGamesCompleted();
    dataProvider->isIntensifierGameTurn = false;
    dataProvider->lastIntensifierGameNum = -1;
    
    
    string semaInitialPortalCode = dataProvider->getSemaInitialPortalCode();
    CCLOG("MAP - semaInitialPortalCode = %s", semaInitialPortalCode.c_str());
    
    vector<string> portalCodeSplitted = StringUtility::split(semaInitialPortalCode, '-');
    int semaInitialEpisode = StringUtility::stringToNumber<int>( portalCodeSplitted.at(0) );
    
    int index = 0;
    startEpisode = semaInitialEpisode - 1;
    CCLOG("...startEpisode = %d", startEpisode);
    if (startEpisode < 1 ) startEpisode = 1;

    int endEpisode = semaInitialEpisode + 1;
  
    if (endEpisode >= (totNumEpisodes +1) ) endEpisode = totNumEpisodes;
    
    // load episode from   semaInitialEpisode-1   to  semaInitialEpisode+1
    for (index = startEpisode; index <= endEpisode; ++index) {
        
        
        auto ep = loadEpisode(index);
        episodesVector.at(index) = ep;// .push_back(ep);
        
    }
    printEpisodesVector();
    sema = new MapSema(*rootNode->getChildByName("scrollContainer"), Vec2(104.f, 421.f), PATH + "csd/chars/mini_sema.csb", _eventDispatcher, &episodesVector);
    sema->setVisible(false);
    
    
    //CCLOG("2episodesVector soze  = %lu", episodesVector.size());
}





void MapScene::fadeIn() {
    
    string semaInitialPortalCode = dataProvider->getSemaInitialPortalCode();
    CCLOG("fade in semaInitialPortalCode = %s", semaInitialPortalCode.c_str());
    sema->placeOnPortal(  getPortalFromPortalCode( semaInitialPortalCode )  );
   
    string episodeInitial =  (StringUtility::split(semaInitialPortalCode, '-')).at(0);

    moveMapToEpisode( StringUtility::stringToNumber<int>(episodeInitial), 0 );
    
    string semaInitialAction = dataProvider->getSemaInitialAction();
    
    if (semaInitialAction == "stand") {
        dataProvider->setSemaInitialAction("comeOut");
        sema->setVisible(true);
        if (lastTappedPortal != nullptr) lastTappedPortal->hidePlayButton();
        lastTappedPortal = getPortalFromPortalCode( semaInitialPortalCode );
        getPortalFromPortalCode( semaInitialPortalCode )->showPlayButton();
        
    } else {
        // come out
        CallFunc *runCallback = CallFunc::create(CC_CALLBACK_0(MapScene::runSemaInitialAnimation, this));
        this->runAction(Sequence::create(DelayTime::create(1.0), runCallback, nullptr));
    }
    
    
    startDetectingSwipe();
    canSwipe = true;
    
    
}

void MapScene::runSemaInitialAnimation() {
    
    string semaInitialPortalCode = dataProvider->getSemaInitialPortalCode();
    
    sema->setVisible(true);
    sema->comeOutFromPortal();
    auto portal = getPortalFromPortalCode( semaInitialPortalCode );
    portal->play("portal_jump_outside", [=]() {
        if (lastTappedPortal != nullptr) lastTappedPortal->hidePlayButton();
        lastTappedPortal = portal;
        portal->showPlayButton();
        portal->getActionTimeline()->clearLastFrameCallFunc();
    });
    
    
    
   
    bool mustUnlockNewPortal = dataProvider->getMustUnlockNewPortalMap();
    if (mustUnlockNewPortal) {
        // TODO 
        dataProvider->setMustUnlockNewPortalMap(false);
    }
}


MapPortal* MapScene::getPortalFromPortalCode(string portalCode) {
    CCLOG(">>>> getPortalFromPortalCode  - portalCode: %s", portalCode.c_str());
    vector<string> portalCodeSplitted = StringUtility::split(portalCode, '-');
    string episodeNumStr = portalCodeSplitted.at(0);
    string portalNumStr = portalCodeSplitted.at(1);
    int episodeNumInt = StringUtility::stringToNumber<int>(episodeNumStr);
    int portalNumInt = StringUtility::stringToNumber<int>(portalNumStr);
    return episodesVector.at(episodeNumInt)->getPortal(portalNumInt);
}



/// swipe part

void MapScene::startDetectingSwipe()
{
    CCLOG("startDetectingSwipe");
    auto listener = EventListenerTouchOneByOne::create();
    // listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(MapScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(MapScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(MapScene::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(MapScene::onTouchCancelled, this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    isTouchDown = false;
    
    initialTouchPos[0] = 0;
    initialTouchPos[1] = 0;
    
    this->scheduleUpdate();
}


void MapScene::update(float dt)
{
    if (!canSwipe) return;
    
    if (hasTocalculateTime) gameTime += dt;
   
}

bool MapScene::onTouchBegan(Touch *touch, Event *event)
{
    //CCLOG("-------onTouchBegan");
    //if (touchIsOnBall(touch) == false) return false;
    
    if (!canSwipe) return false;
    
    initialTouchPos[0] = touch->getLocation().x;
    initialTouchPos[1] = touch->getLocation().y;
    currentTouchPos[0] = touch->getLocation().x;
    currentTouchPos[1] = touch->getLocation().y;
    
    isTouchDown = true;
    moveLeftGestureDone = false;
    moveRightGestureDone = false;
    gameTime = 0;
    hasTocalculateTime = true;
    startX = touch->getLocation().x;
    startY = touch->getLocation().y;
    
    //   CCLOG("onTouchBegan ID: %d, X: %f, Y: %f", touch->getID(), touch->getLocation().x, touch->getLocation().y);
    
    return true;
}



void MapScene::onTouchMoved(Touch *touch, Event *event)
{
    /*if (!canSwipe) return;
    currentTouchPos[0] = touch->getLocation().x;
    currentTouchPos[1] = touch->getLocation().y;*/
}

void MapScene::onTouchEnded(Touch *touch, Event *event)
{
    if (!canSwipe) return;

    hasTocalculateTime = false;
    //CCLOG("gameTime = %f", gameTime);
    
 
    if (true == isTouchDown)
    {
        
        currentTouchPos[0] = touch->getLocation().x;
        currentTouchPos[1] = touch->getLocation().y;
        
        float threshold = 250; // - visibleSize.width * 0.1
        

        CCLOG("TOUCH DOWN");
        CCLOG("Touch swipe is %f while threshold is %f", initialTouchPos[0] - currentTouchPos[0], threshold);
       

        if (initialTouchPos[0] - currentTouchPos[0] > threshold)
        {
            CCLOG("SWIPED LEFT");
            moveLeftGestureDone = true;
            isTouchDown = false;
            
        }
        if (initialTouchPos[0] - currentTouchPos[0] < -threshold )
        {
            CCLOG("SWIPED RIGHT");
            moveRightGestureDone = true;
            isTouchDown = false;
            
        }
        if (initialTouchPos[1] - currentTouchPos[1] > visibleSize.width * 0.05)
        {
            //CCLOG("SWIPED DOWN");
            isTouchDown = false;
            
        }
        if (initialTouchPos[1] - currentTouchPos[1] < - visibleSize.width * 0.05)
        {
            //CCLOG("SWIPED UP");
            isTouchDown = false;
        }
        
    }

     isTouchDown = false;
    

    Vec2 direction = Vec2( Vec2(startX,startY), Vec2(touch->getLocation().x, touch->getLocation().y) );
    
    direction.normalize();
    
    
    
    if ((moveLeftGestureDone) && (gameTime<0.5)) {
        //CCLOG("ok moveLeftGestureDone!!");
        if (scrollIndex < totNumEpisodes) {
            scrollIndex++;
            moveMapToEpisode(scrollIndex);
        }
    } else if ((moveRightGestureDone) && (gameTime<0.5)) {
        //CCLOG("ok moveRightGestureDone!!");
        if (scrollIndex > 1) {
            scrollIndex--;
            moveMapToEpisode(scrollIndex);
            
        }
        
    }
    
    
}

void MapScene::onTouchCancelled(Touch *touch, Event *event)
{
    onTouchEnded(touch, event);
}

// end swipe part



MapEpisode* MapScene::loadEpisode(int numEpisodeToLoad) {
    //CCLOG("start loading episode %d", numEpisodeToLoad);
    string indexStr = StringUtility::toString( numEpisodeToLoad );
    
    int lastUnlockedEpisode = dataProvider->getLastUnlockedEpisodeNum();
    int lastUnlockedWatchman = dataProvider->getLastUnlockedWatchmanNum();
    
    int lastUlockedPortal;
    if (numEpisodeToLoad == lastUnlockedEpisode) lastUlockedPortal = lastUnlockedWatchman;
    else if (numEpisodeToLoad > lastUnlockedEpisode) lastUlockedPortal = -1; // none
    else if (numEpisodeToLoad < lastUnlockedEpisode) lastUlockedPortal = 100; // all
    
    MapEpisode* ep;
    bool test = false;
    if (test) {
        if (indexStr>"4") {
            ep = new MapEpisode(*rootNode->getChildByName("scrollContainer"), rootNode->getChildByName("scrollContainer")->getChildByName("placeholder_ep"+indexStr)->getPosition(), PATH + "csd/lands/land_ep1.csb", 1, lastUlockedPortal, _eventDispatcher);
            
        } else {
            ep = new MapEpisode(*rootNode->getChildByName("scrollContainer"), rootNode->getChildByName("scrollContainer")->getChildByName("placeholder_ep"+indexStr)->getPosition(), PATH + "csd/lands/land_ep"+indexStr+".csb", numEpisodeToLoad, lastUlockedPortal, _eventDispatcher);
        }
    } else {
        ep = new MapEpisode(*rootNode->getChildByName("scrollContainer"), rootNode->getChildByName("scrollContainer")->getChildByName("placeholder_ep"+indexStr)->getPosition(), PATH + "csd/lands/land_ep"+indexStr+".csb", numEpisodeToLoad, lastUlockedPortal, _eventDispatcher);
    }
    return ep;
}

void MapScene::moveMapToEpisode(int episodeNum, float transitionTime) {

    
    if (transitionTime == 0)  moveMapToEpisodeSingle(episodeNum, episodeNum, transitionTime);
   
    if (currentMapPosition == episodeNum) {
        CCLOG(">>>>> arrivato! fine!");
        return;
    }
    
    CCLOG(">>>>> moveMapToEpisode - from %d  to %d", currentMapPosition, episodeNum);
    
    if (currentMapPosition > episodeNum) {
        // go back
        int stepEpisodeToGo = currentMapPosition - 1;
        moveMapToEpisodeSingle(stepEpisodeToGo, episodeNum, transitionTime);
    } else if (currentMapPosition < episodeNum) {
        // go forward
        int stepEpisodeToGo = currentMapPosition + 1;
        moveMapToEpisodeSingle(stepEpisodeToGo, episodeNum, transitionTime);
    }
}

void MapScene::moveMapToEpisodeSingle(int episodeNum, int episodeNumToReach, float transitionTime) {
    
    CCLOG(">>>>> moveMapToEpisodeSingle - from %d  to %d", currentMapPosition, episodeNum);
   
    
    if (currentMapPosition == episodeNum) {
        canSwipe = true;
        return;
    }
       
  
    printEpisodesVector();
    scrollIndex = episodeNum;
    
    float yPos = scrollContainer->getPositionY();
    Vec2 finalPos;
    
    if (episodeNum == 1) {
        finalPos = Vec2(0,yPos);
    } else if (episodeNum > 1) {
        float xPos = -750 - (900*(episodeNum-2));
        if (episodeNum == totNumEpisodes) xPos += 230;
        finalPos = Vec2(xPos,yPos);
    }
    if (transitionTime == 0) {
        scrollContainer->setPosition(finalPos);
        currentMapPosition = episodeNum;
    } else {
        
        int div = (episodeNumToReach - episodeNum);
        if (div < 0) div = -div;
        div++;
        transitionTime = transitionTime / div ;
        CCLOG("transitionTime = %f", transitionTime);
        int direction = 0;
        if (currentMapPosition > episodeNum) direction = -1;
        if (currentMapPosition < episodeNum) direction = 1;
        
        int indexEpisodeToLoad;
        if (direction < 0) {
            indexEpisodeToLoad = episodeNum - 1;
            if (indexEpisodeToLoad > 0) {
                if (episodesVector.at(indexEpisodeToLoad) == nullptr) {
                    auto ep = loadEpisode(indexEpisodeToLoad);
                    episodesVector.at(indexEpisodeToLoad) = ep;
                    //CCLOG(">>caricato episodio prec  %d", indexEpisodeToLoad);
                }
            }
            
        } else {
            indexEpisodeToLoad = episodeNum + 1;
            if (indexEpisodeToLoad <= totNumEpisodes) {
                if (episodesVector.at(indexEpisodeToLoad) == nullptr) {
                    auto ep = loadEpisode(indexEpisodeToLoad);
                    episodesVector.at(indexEpisodeToLoad) = ep;// .push_back(ep);
                    //CCLOG(">>caricato episodio succ  %d", indexEpisodeToLoad);
                }
            }
            
        }
        
        
        printEpisodesVector();
        
        
        canSwipe = false;
        MoveTo *move = MoveTo::create(transitionTime, finalPos);
        scrollContainer->runAction(Sequence::create(move,
                                                    CallFunc::create([=]() {
            
                                                            if (direction < 0) {
                                                                int indexEpisodeToDelete = episodeNum + 2;
                                                                if (indexEpisodeToDelete <= totNumEpisodes) {
                                                                   //CCLOG("<<cancello episodio molto succ %d", indexEpisodeToDelete);
                                                                   /* if (episodesVector.at(indexEpisodeToDelete) != nullptr) {
                                                                        delete episodesVector.at(indexEpisodeToDelete);
                                                                        episodesVector.at(indexEpisodeToDelete) = nullptr;
                                                                    } */
                                                                   printEpisodesVector();
                                                                }
                                                                
                                                            } else {
                                                                int indexEpisodeToDelete = episodeNum - 2;
                                                                if (indexEpisodeToDelete  >= 1) {
                                                                    //CCLOG("<<cancello episodio molto prec %d", indexEpisodeToDelete);
                                                                    /* if (episodesVector.at(indexEpisodeToDelete) != nullptr) {
                                                                        delete episodesVector.at(indexEpisodeToDelete);
                                                                        episodesVector.at(indexEpisodeToDelete) = nullptr;
                                                                    } */
                                                                    printEpisodesVector();
                                                                    
                                                                }
                                                            }
                                                            currentMapPosition = episodeNum;
                                                            CCLOG("qui fine single!  currentMapPosition  %d", currentMapPosition);
                                                            canSwipe = true;
            
                                                            moveMapToEpisode(episodeNumToReach, transitionTime);
            
                                                            }),
                                                    nullptr
                                    ));
    }

    //CCLOG("fine moveMapToEpisode");
}


void MapScene::printEpisodesVector() {
    string toPrint = "";
    for (vector<MapEpisode*>::iterator iterator = episodesVector.begin(); iterator != episodesVector.end(); ++iterator) {
        toPrint += " ";
        if ( (*iterator) != nullptr ) {
            toPrint += StringUtility::toString((*iterator)->episodeNum);
        } else {
            toPrint += "*";
        }
    }
     CCLOG("EpisodesVector:  %s ", toPrint.c_str());
}

