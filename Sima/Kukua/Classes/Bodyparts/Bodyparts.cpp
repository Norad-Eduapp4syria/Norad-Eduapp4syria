#include "Bodyparts.h"
#include "../Utils/Data/Logger.h"
#include "../Utils/Data/DataProvider.h"
#include "../Utils/Data/ArabicHelper.h"
#include "../Utils/Data/ArabicHelperForGames.h"
#include "../WatchmanScene/WatchmanScene.h"
#include "../AppMacros.h"

template<> const bool kukua::Game<Bodyparts>::USE_PHYSICS = false;
template<> const bool kukua::Game<Bodyparts>::ENABLE_TOUCH = true;
template<> string kukua::Game<Bodyparts>::PATH = "Bodyparts/";
template<> const string kukua::Game<Bodyparts>::BACKGROUND_MUSIC_FILENAME = "backgroundMusic.mp3";
template<> bool kukua::Game<Bodyparts>::SHOWN_TUTORIAL = false;
template<> Scene* kukua::Game<Bodyparts>::scene = nullptr;
template<> const string kukua::Game<Bodyparts>::NAME = "BodyParts";

Bodyparts::~Bodyparts() {

	CCLOG("~Bodyparts");
    delete body;
    delete board;
    _eventDispatcher->removeEventListener(bodyPartTouchedEventHandler);
    
}

void Bodyparts::initVariables() {

	CCLOG("Bodyparts - Init variables");
    
    boardTextUi2 = ArabicHelper::getInstance()->createLabel("", 90);
    boardTextUi2->setTextColor(Color4B(0, 0, 0, 255));
    rootNode->getChildByName("board")->getChildByName("master_board")->getChildByName("text")->addChild(boardTextUi2);
    
    scorePercent = 100.0f;
    scoreToSubtract = 25.0f;
}

void Bodyparts::initAudio() {

	CCLOG("Bodyparts - Init audio");

    simpleAudioEngine->preloadBackgroundMusic("common/audio/bg/GAME_4.mp3");
    simpleAudioEngine->playBackgroundMusic("common/audio/bg/GAME_4.mp3", true);
    
}

void Bodyparts::initGameObjects() {

	CCLOG("Bodyparts - Init objects");
    
     dataProvider = DataProvider::getInstance();

    int skin = dataProvider->getSkin();
    
    if (skin == 1) body = new Body(*rootNode, rootNode->getChildByName("sema")->getPosition(), Bodyparts::PATH+"csd/sema.csb", "sema", _eventDispatcher, *this);
    else  body = new Body(*rootNode, rootNode->getChildByName("paul")->getPosition(), Bodyparts::PATH+"csd/paul.csb", "paul", _eventDispatcher, *this);
    
    
    string currentPhoneme = dataProvider->getCurrentDBKnowledgeBubble()->getPhoneme();
    bodyPartsToTapVector = dataProvider->getWordsForGame( currentPhoneme, "bodyParts" );
    
    board = new GameObject(*rootNode, "board", Bodyparts::PATH + "csd/board.csb");
 
    
    bodyPartTouchedEventHandler = EventListenerCustom::create("BodyPartTouchedEvent", [=](EventCustom* event){
        auto part = static_cast<TouchablePart*>(event->getUserData());
        string partName = part->getName();
        CCLOG("bodyPartTouchedEventHandler %s", part->getName().c_str());
        
        /*
        auto touchEffect = static_cast<Node*>(rootNode->getChildByName("touch"));
        touchEffect->setPosition(convertToWorldSpace(part->getPosition()));
        cocostudio::timeline::ActionTimeline* touchEffectTimeline = CSLoader::createTimeline(Bodyparts::PATH + "csd/tap.csb");
        touchEffect->runAction(touchEffectTimeline);
        touchEffectTimeline->play("tap", false);
        */
        
        
        body->disableTouchOnParts();
        
        endRound( isCorrectMatch(partName)  );
        
    });
    _eventDispatcher->addEventListenerWithFixedPriority(bodyPartTouchedEventHandler, 1);
    
}

void Bodyparts::fadeIn() {

	CCLOG("Bodyparts - Fade in");

    startNewRound();
 
    
}


void Bodyparts::showTutorial() {

	CCLOG("Bodyparts - Show tutorial");

}

void Bodyparts::hideTutorial() {

	CCLOG("Bodyparts - Hide tutorial");

}

bool Bodyparts::onTouchBegan(Touch* touch, Event* event) {

	CCLOG("Bodyparts - Touch began");

	// Manage the start of a touch event

	return true;

}

void Bodyparts::onTouchMoved(Touch* touch, Event* event) {

	CCLOG("Bodyparts - Touch moved");

	// Manage a touch event

}

void Bodyparts::onTouchEnded(Touch* touch, Event* event) {

	CCLOG("Bodyparts - Touch ended");

	// Manage the end of a touch event

}

void Bodyparts::endGame(bool gameOver) {

	CCLOG("Bodyparts - End game");
    Logger::getInstance()->logEvent(NAME, Logger::WIN, "");

}

void Bodyparts::homeButtonPressed() {
    
    simpleAudioEngine->stopBackgroundMusic();
    
    Logger::getInstance()->logEvent(NAME, Logger::CLOSE, "");
    if ( TEST_ENABLED ) {
        dataProvider->setGameCompleted(NAME);
        dataProvider->setWatchmanReaction(WatchmanScene::GOOD_REACTION);
    } else {
        dataProvider->setWatchmanReaction(WatchmanScene::BAD_REACTION);
    }
    _director->replaceScene(TransitionFade::create(TRANSITION_TIME, WatchmanScene::createScene(), TRANSITION_COLOR));
}


void Bodyparts::endRound(bool positiveEnd) {
    

    if (!positiveEnd)
    {
        scorePercent -= scoreToSubtract;
        CCLOG("Lo score vale %f", scorePercent);
    }
    
    body->zoomOut();
    
    
    this->runAction(Sequence::create(
                                     DelayTime::create( body->zoomAnimDuration  ),
                                     CallFunc::create(
                                                      [=]() {
                                                          
                                                          string animName = "negative";
                                                          if ( positiveEnd )  {
                                                              animName = "positive";
                                                              bodyPartsToTapVector.erase(bodyPartsToTapVector.begin()); // remove first element
                                                          }
                                                          
                                                          body->play(animName, [=]() {
                                                              
                                                              board->play("exit");
                                                              
                                                              body->play("exit", [=]() {
                                                                  
                                                                  
                                                                  if ( bodyPartsToTapVector.empty() ) {
                                                                      simpleAudioEngine->stopBackgroundMusic();
                                                                      Logger::getInstance()->logEvent(NAME, Logger::CLOSE, "");
                                                                      dataProvider->setGameCompleted(NAME);
                                                                      dataProvider->setWatchmanReaction(WatchmanScene::GOOD_REACTION);
                                                                      _director->replaceScene(TransitionFade::create(TRANSITION_TIME, WatchmanScene::createScene(), TRANSITION_COLOR));
                                                                      body->clearLastFrameCallFunc();
                                                                      
                                                                  } else {
                                                                      CallFunc *runCallback1 = CallFunc::create(CC_CALLBACK_0(Bodyparts::startNewRound, this));
                                                                      this->runAction(Sequence::create(DelayTime::create(0.2), runCallback1, nullptr));
                                                                      body->clearLastFrameCallFunc();
                                                                  }
                                                                  
                                                                  
                                                              });
                                                              
                                                              
                                                              
                                                          });
                                                          
                                                          
                                                      }), nullptr)
                    );
    
  
    
    
  
}


void Bodyparts::startNewRound() {
    
    bodyPartToTap = bodyPartsToTapVector.at(0); // getRandomBodyPart();
    
    cocos2d::ui::Text *boardTextUi = static_cast<cocos2d::ui::Text *>(rootNode->getChildByName("board")->getChildByName("master_board")->getChildByName("text")->getChildByName("text"));
    boardTextUi->setString(bodyPartToTap);

    boardTextUi->setString("");
    boardTextUi2->setString(ArabicHelperForGames::getInstance()->getInArabic(bodyPartToTap));
  
    body->disableTouchOnParts();
    simpleAudioEngine->playEffect((PATH+"Audio/game_body_now_lets_try.mp3").c_str());
    
    this->runAction(Sequence::create(DelayTime::create(3.5f), CallFunc::create([=](){
        
        int skin = dataProvider->getSkin();
        if (skin == 1) simpleAudioEngine->playEffect((PATH+"Audio/parts/" + bodyPartToTap + "_" + "sima" + ".mp3").c_str());
        else simpleAudioEngine->playEffect((PATH+"Audio/parts/" + bodyPartToTap + "_" + "samir" + ".mp3").c_str());
        
    }),  nullptr));
    
    
    body->play("enter", [=]() {
        
        body->play("standing", nullptr, true);
        board->play("enter");
        
        body->zoomIn(bodyPartToTap);
        body->enableTouchOnParts(bodyPartToTap);
        body->clearLastFrameCallFunc();
    });
   
}


string Bodyparts::getRandomBodyPart() {
    // return "shoulder";
    vector<string> parts;
    parts.push_back("nose");
    parts.push_back("head");
    parts.push_back("arm");
    parts.push_back("chin");
    parts.push_back("mouth");
    parts.push_back("hand");
    parts.push_back("tongue");
    parts.push_back("foot");
    parts.push_back("knee");
    parts.push_back("leg");
    parts.push_back("ear");
    parts.push_back("hair");
    parts.push_back("neck");
    parts.push_back("shoulder");
    parts.push_back("eye");
    
    parts.push_back("finger");
    parts.push_back("elbow");
    
    //  srand( static_cast<unsigned int>(time(NULL)));
    int randomIindex = rand() % parts.size();
    //CCLOG("randomIindex = %d", randomIindex);
    return parts.at(randomIindex);
}


bool Bodyparts::isCorrectMatch(string touchName) {
  
    if ( bodyPartToTap == touchName) return true;
    else if ( ( bodyPartToTap == "eye") && ( (touchName=="eye1") || (touchName=="eye2") ) ) return true;
    else if ( ( bodyPartToTap == "arm") && ( (touchName=="arm1") || (touchName=="arm2") ) ) return true;
    else if ( ( bodyPartToTap == "hand") && ( (touchName=="hand1") || (touchName=="hand2") ) ) return true;
    else if ( ( bodyPartToTap == "finger") && ( (touchName=="finger1") || (touchName=="finger2") ) ) return true;
    else if ( ( bodyPartToTap == "elbow") && ( (touchName=="elbow1") || (touchName=="elbow2") ) ) return true;
    else if ( ( bodyPartToTap == "ear") && ( (touchName=="ear1") || (touchName=="ear2") ) ) return true;
    else if ( ( bodyPartToTap == "leg") && ( (touchName=="leg1") || (touchName=="leg2") ) ) return true;
    else if ( ( bodyPartToTap == "foot") && ( (touchName=="foot1") || (touchName=="foot2") ) ) return true;
    else if ( ( bodyPartToTap == "knee") && ( (touchName=="knee1") || (touchName=="knee2") ) ) return true;
    else if ( ( bodyPartToTap == "hair") && ( (touchName=="hair1") || (touchName=="hair2") || (touchName=="hair3") ) ) return true;
    
    // elbow
    return false;
}


