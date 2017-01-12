#include "NightrunnerGame_1_4.h"
#include "../Utils/Data/DataProvider.h"
#include "../Utils/Data/Logger.h"
#include "../AppMacros.h"
#include "../Utils/StringUtility.h"
#include "../WatchmanScene/WatchmanScene.h"
#include "../Utils/Data/ArabicHelper.h"



const bool NightrunnerGame_1_4::ENABLE_TOUCH = true;								// Used to disable tutorial on first touch and manage general touch events
const string NightrunnerGame_1_4::PATH = "NightrunnerGame_1_4/";								// Resources' subfolder path for this game

Scene* NightrunnerGame_1_4::createScene() {

	// 'scene' is an autorelease object
	Scene* scene = Scene::create();

	// 'layer' is an autorelease object			 
	auto layer = NightrunnerGame_1_4::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;

}

NightrunnerGame_1_4::~NightrunnerGame_1_4() {
    ball1->setTouchable(false);
    ball2->setTouchable(false);
    ball3->setTouchable(false);
    delete ball1;
    delete ball2;
    delete ball3;
    delete bossPos;
    delete bossNeg;
    delete counter;
     _eventDispatcher->removeEventListener(touchBallEventHandler);
     _eventDispatcher->removeEventListener(timeFinishedHandler);
}

bool NightrunnerGame_1_4::init() {

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



void NightrunnerGame_1_4::startGame() {

	Logger::getInstance()->logEvent("NightrunnerGame_1_4", Logger::OPEN, "");
    

	initVariables();
	initAudio();
	initGameObjects();
    
    CallFunc *fadeInCallback = CallFunc::create(CC_CALLBACK_0(NightrunnerGame_1_4::fadeIn, this));
    Action *fadeInAction = Sequence::create(DelayTime::create(0.4),fadeInCallback, nullptr);
    this->runAction(fadeInAction);
    
}

void NightrunnerGame_1_4::initVariables() {
    
	dataProvider = DataProvider::getInstance();
    score = 0;
    wrongAnserCounter = 0;
    currentEpisode = dataProvider->getCurrentEpisode();
    //
    
    touchBallEventHandler = EventListenerCustom::create("TouchBallEvent", [=](EventCustom* event){
        
        string ballNumTouched = "";
        char* buf = static_cast<char*>(event->getUserData());
        ballNumTouched += buf;
        handleBallTouched(ballNumTouched);
        CCLOG("TouchBallEvent... %s", ballNumTouched.c_str());
    
    });
    _eventDispatcher->addEventListenerWithFixedPriority(touchBallEventHandler, 1);
    //
    
    timeFinishedHandler = EventListenerCustom::create("TimeFinishedEvent", [=](EventCustom* event){
        
        CCLOG("TimeFinishedEvent..");
        
        handleFinishTime();
        
    });
    _eventDispatcher->addEventListenerWithFixedPriority(timeFinishedHandler, 1);
    
}

void NightrunnerGame_1_4::initAudio() {

	simpleAudioEngine = SimpleAudioEngine::getInstance();
   
    
}

void NightrunnerGame_1_4::initGameObjects() {

    bossNeg = new GameObject(*rootNode, "boss_posi", PATH + "csd/Boss_pos.csb");
    bossPos = new GameObject(*rootNode, "boss_nega", PATH + "csd/Boss_nega.csb");
 
}





void NightrunnerGame_1_4::fadeIn() {
    
    CCLOG("NightrunnerGame_1_4 fade in");
    
    // score
    auto scoreNode = static_cast<Node*>(rootNode->getChildByName("score"));
    cocostudio::timeline::ActionTimeline* scoreTimeline = CSLoader::createTimeline(PATH+"csd/Score.csb");
    scoreNode->runAction(scoreTimeline);
    scoreTimeline->play("enter", false);
    
    
    counter = new NR_Counter(*rootNode, "counter", _eventDispatcher);
    
    ball1 = new NR_Ball(*rootNode, "ball_1", _eventDispatcher, "1");
    ball2 = new NR_Ball(*rootNode, "ball_2", _eventDispatcher, "2");
    ball3 = new NR_Ball(*rootNode, "ball_3", _eventDispatcher, "3");
    
    correctBallNum = "1";
    
    addBackToHomeButton();
    
    startMatch();
}


void NightrunnerGame_1_4::addBackToHomeButton() {
    
    auto backNode = cocos2d::ui::Button::create("common/homeBtn.png", "common/homeBtn.png", "common/homeBtn.png");
    
    auto frameSize = cocos2d::Director::getInstance()->getWinSize();
    auto x = 90;//frameSize.width * 0.5f;
    auto y = frameSize.height * 0.9f;
    backNode->setPosition(Vec2(x,y));
    addChild(backNode, 10);
    
    backNode->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                Logger::getInstance()->logEvent("NightrunnerGame_1_4", Logger::CLOSE, "");
                if ( TEST_ENABLED ) {
                    DataProvider::getInstance()->setGameCompleted("NightrunnerGame_1_4");
                    DataProvider::getInstance()->setWatchmanReaction(WatchmanScene::GOOD_REACTION);
                } else {
                    DataProvider::getInstance()->setWatchmanReaction(WatchmanScene::BAD_REACTION);
                }
                simpleAudioEngine->stopBackgroundMusic();
                _director->replaceScene(TransitionFade::create(TRANSITION_TIME, WatchmanScene::createScene(), TRANSITION_COLOR));
                break;
            default:
                break;
        }
    });
    
}

void NightrunnerGame_1_4::handleBallTouched(string ballTouchedNum) {
    
    if (ballTouchedNum == "1") {
    
        ball2->play("out");
        ball3->play("out");
        
    } else if (ballTouchedNum == "2") {
        
        ball1->play("out");
        ball3->play("out");
        
    } else if (ballTouchedNum == "3") {
        ball1->play("out");
        ball2->play("out");
    }
    
    if (correctBallNum == ballTouchedNum) {
        simpleAudioEngine->playEffect((PATH+"Audio/pop_positive.mp3").c_str());
        simpleAudioEngine->playEffect((PATH+"Audio/GolemArgh.mp3").c_str());
        updateScore();
        // update score

        
        // anim pos
        bossPos->play("in");
        
        bossPos->play("int", [&]() {
            startMatch();
            bossPos->clearLastFrameCallFunc();
        });
        
    } else {
        // anim neg
        simpleAudioEngine->playEffect((PATH+"Audio/pop_negative.wav").c_str());
        simpleAudioEngine->playEffect((PATH+"Audio/GolemLaugh.mp3").c_str());
        wrongAnserCounter++;
        bossNeg->play("in");
        
        bossNeg->play("int", [&]() {
            startMatch();
            bossNeg->clearLastFrameCallFunc();
        });
        
    }
    
}

string NightrunnerGame_1_4::getCompleteWord(string word) {
    
    string wordToSplit = ArabicHelper::getInstance()->getInArabic(word);
    vector<string> wordsVectorSplitted = StringUtility::split(wordToSplit, '#');
    string valArab = "";
    for (int idx = 0; idx< wordsVectorSplitted.size(); idx++ ) {
        valArab.append( wordsVectorSplitted.at(idx) );
    }
    return valArab;
}

void NightrunnerGame_1_4::startMatch() {
    int corrctBallNumInt = rand() % 3 + 1;
    correctBallNum = StringUtility::toString(corrctBallNumInt);
    
    string correctVal;
    string wrongVal1;
    string wrongVal2;

    
    correctVal = dataProvider->getRandomPhonemeForNightrunnerGame_1_4(currentEpisode);
    wrongVal1 = dataProvider->getRandomPhonemeForNightrunnerGame_1_4(currentEpisode);
    
    while (wrongVal1 == correctVal) {
        wrongVal1 = dataProvider->getRandomPhonemeForNightrunnerGame_1_4(currentEpisode);
    }
    
    wrongVal2 = dataProvider->getRandomPhonemeForNightrunnerGame_1_4(currentEpisode);
    while ((wrongVal2 == correctVal) || (wrongVal2 == wrongVal1) ) {
        wrongVal2 = dataProvider->getRandomPhonemeForNightrunnerGame_1_4(currentEpisode);
    }
    
    if (currentEpisode == 2) {
        //add _a _i _u
        correctVal = addRandomSuffixEp2(correctVal);
        wrongVal1 = addRandomSuffixEp2(wrongVal1);
        wrongVal2 = addRandomSuffixEp2(wrongVal2);
    }
    
    CCLOG("correctVal = %s", correctVal.c_str());
    CCLOG("wrongVal1 = %s", wrongVal1.c_str());
    CCLOG("wrongVal2 = %s", wrongVal2.c_str());

    
    if ( (currentEpisode == 1) || (currentEpisode == 2) ) {
        simpleAudioEngine->playEffect(("common/audio/sema/phonemes/"+correctVal+".mp3").c_str());
    } else if ( (currentEpisode == 3) || (currentEpisode == 4) ) {
        
        /*
        string wordToSplit = ArabicHelper::getInstance()->getInArabic(correctVal);
        vector<string> wordsVectorSplitted = StringUtility::split(wordToSplit, '#');
        string correctValArab = "";
        for (int idx = 0; idx< wordsVectorSplitted.size(); idx++ ) {
            correctValArab.append( wordsVectorSplitted.at(idx) );
        }
        CCLOG("correctValArab = %s", correctValArab.c_str());
        */
        string completeWordForAudio = getCompleteWord(correctVal);
        string wordAudioFilename = ArabicHelper::getInstance()->getFilenameInEnglish( completeWordForAudio );
        CCLOG("wordAudioFilename = %s", wordAudioFilename.c_str());
        simpleAudioEngine->playEffect(("common/audio/sema/words/" + wordAudioFilename + ".mp3").c_str());
    }

    
    
     if ( (currentEpisode == 3) || (currentEpisode == 4) ) {
         correctVal = getCompleteWord(correctVal);
         wrongVal1 = getCompleteWord(wrongVal1);
         wrongVal2 = getCompleteWord(wrongVal2);
     }
     
    
    if (correctBallNum == "1") {
        
        ball1->setValue(correctVal, currentEpisode);
        ball2->setValue(wrongVal1, currentEpisode);
        ball3->setValue(wrongVal2, currentEpisode);
        
    } else if (correctBallNum == "2") {
    
        ball2->setValue(correctVal, currentEpisode);
        ball1->setValue(wrongVal1, currentEpisode);
        ball3->setValue(wrongVal2, currentEpisode);
        
    } else { // correctBallNum == "3")
        
        ball3->setValue(correctVal, currentEpisode);
        ball2->setValue(wrongVal1, currentEpisode);
        ball1->setValue(wrongVal2, currentEpisode);
        
    }
    
    simpleAudioEngine->playEffect((PATH+"Audio/pop_enter_ball.wav").c_str());
    ball1->play("enter");
    ball2->play("enter");
    ball3->play("enter");
    
    
}

void NightrunnerGame_1_4::updateScore() {
    cocos2d::ui::Text *txt = static_cast<cocos2d::ui::Text *>(rootNode->getChildByName("score")->getChildByName("Master_score")->getChildByName("Text"));
    score++;
    txt->setString( StringUtility::toString(score) );
    simpleAudioEngine->playEffect((PATH+"Audio/in_counter_score.mp3").c_str());
}

string NightrunnerGame_1_4::addRandomSuffixEp2(string phoneme) {
    int randSuffix = rand() % 3 + 1;
    if (randSuffix == 1) phoneme += "_a";
    else if (randSuffix == 2) phoneme += "_i";
    else  phoneme += "_u";
    return phoneme;
}

void NightrunnerGame_1_4::handleFinishTime() {
    
    ball1->setTouchable(false);
    ball2->setTouchable(false);
    ball3->setTouchable(false);
    
    bool winnedGame = false;
    int totQuestions = score + wrongAnserCounter;
    int percent = 0;
    if (totQuestions > 0) percent = 100 * score / totQuestions;
    
    if (percent > 79) winnedGame = true;
    
    Logger::getInstance()->logEvent("NightrunnerGame_1_4", Logger::CLOSE, "");
    if ( winnedGame ) {
        DataProvider::getInstance()->setGameCompleted("NightrunnerGame_1_4");
        DataProvider::getInstance()->setWatchmanReaction(WatchmanScene::GOOD_REACTION);
    } else {
        DataProvider::getInstance()->setWatchmanReaction(WatchmanScene::BAD_REACTION);
    }
    simpleAudioEngine->stopBackgroundMusic();
    _director->replaceScene(TransitionFade::create(TRANSITION_TIME, WatchmanScene::createScene(), TRANSITION_COLOR));
    
}
