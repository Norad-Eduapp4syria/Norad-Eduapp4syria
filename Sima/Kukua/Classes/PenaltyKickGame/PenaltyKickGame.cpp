#include "PenaltyKickGame.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <vector>
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h" // serve per il buttone home
#include "../Utils/Data/DataProvider.h"
#include "../Utils/Data/Logger.h"
#include "../WatchmanScene/WatchmanScene.h"
#include "../Utils/StringUtility.h"
#include "../AppMacros.h"
#include "../Utils/Data/ArabicHelper.h"

USING_NS_CC;

using namespace cocostudio::timeline;

bool PenaltyKickGame::IS_TUTORIAL_SHOWN = false;

Scene* PenaltyKickGame::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics(); // Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = PenaltyKickGame::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

PenaltyKickGame::~PenaltyKickGame() {
	//destoyer
	this->unscheduleUpdate();

	delete goalkeeper1;
	delete goalkeeper2;
    delete phonemeHelp;
}

// on "init" you need to initialize your instance
bool PenaltyKickGame::init()
{
	
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	directionY = 1;
	
	// old ok PATH = "PenaltyKickGame/skin" + StringUtility::toString( DataProvider::getInstance()->getRandomSkin(4) ) + "/";

    PATH = "PenaltyKickGame/";
    
	rootNode = CSLoader::createNode(PATH + "MainScene.csb");
    rootNode->setAnchorPoint(Point(0.5, 0.5));
    rootNode->setPosition(Point(_director->getWinSize().width / 2, _director->getWinSize().height / 2));
    addChild(rootNode);
    
    
    int skin = DataProvider::getInstance()->getSkin();
    static_cast<Sprite*>(rootNode->getChildByName("Background"))->setTexture(PATH+"png/background/Background_" +  StringUtility::toString(skin) + ".png");

	
	goalkeeper1 = new GameObject(*rootNode, Vect::ZERO, PATH + "csd/Nightrunner_silhouette.csb");
	goalkeeper2 = new GameObject(*rootNode, Vect::ZERO, PATH + "csd/Nightrunner_silhouette.csb");
	goalkeeper1->setVisible(false);
	goalkeeper2->setVisible(false);
	
	resetKickVars();

    // init
	goalOK = 0;

	phonemeOk = DataProvider::getInstance()->getCurrentDBKnowledgeBubble()->getPhoneme();

    if (DataProvider::getInstance()->getCurrentEpisode() == 3) {
        phonemeOk = phonemeOk.substr(0, phonemeOk.find("#"));
        phonemeOk = phonemeOk + "_a";
    } else if (DataProvider::getInstance()->getCurrentEpisode() == 1) {
        string::size_type idxEp1 = phonemeOk.find("#ep1");
        if (idxEp1 != string::npos)
            phonemeOk.erase(idxEp1, 4); // 4 is length of "#ep1"
        
    }
    
    
    setInitialParameters();
    preloadAudio();
    
    
    hideObjects();
    
    hand = static_cast<Node*>(rootNode->getChildByName("manina"));

	if (cocos2d::Director::getInstance()->getWinSize().height > rootNode->getBoundingBox().size.height) { // like iPad
		rootNode->getChildByName("Punti_1")->setPosition(Point(rootNode->getChildByName("Punti_1")->getPosition().x, _director->getWinSize().height - 140));
		rootNode->getChildByName("Punti_2")->setPosition(Point(rootNode->getChildByName("Punti_2")->getPosition().x, _director->getWinSize().height - 140));
		rootNode->getChildByName("Punti_3")->setPosition(Point(rootNode->getChildByName("Punti_3")->getPosition().x, _director->getWinSize().height - 140));
		rootNode->getChildByName("Punti_4")->setPosition(Point(rootNode->getChildByName("Punti_4")->getPosition().x, _director->getWinSize().height - 140));
		rootNode->getChildByName("Punti_5")->setPosition(Point(rootNode->getChildByName("Punti_5")->getPosition().x, _director->getWinSize().height - 140));
	}
    
    tutorialIsToShow = !IS_TUTORIAL_SHOWN;
	//hide hand
	//tutorialIsToShow = false;
    CallFunc *runCallback;
	
   // if (tutorialIsToShow)
        runCallback = CallFunc::create(CC_CALLBACK_0(PenaltyKickGame::showTutorial, this));
    //else
     //   runCallback = CallFunc::create(CC_CALLBACK_0(PenaltyKickGame::startGame, this));


	
    this->runAction(Sequence::create(DelayTime::create(0.1), runCallback, nullptr));
   
    addBackToHomeButton();
    
    return true;
}

void PenaltyKickGame::setKeeper(int _ball){
	auto door1Node = static_cast<Node*>(rootNode->getChildByName("Porta_A"));
	auto door2Node = static_cast<Node*>(rootNode->getChildByName("Porta_B"));
	auto keeper1 = static_cast<Node*>(rootNode->getChildByName("keeper1"));
	auto keeper2 = static_cast<Node*>(rootNode->getChildByName("keeper2"));

    
    int skin = DataProvider::getInstance()->getSkin();
    if (skin <=3) _ball = 1;
    else if (skin <=6) _ball = 2;
    else _ball = 4;
    
    
	if (_ball > 1){
		//No keeper
		keeper1->setPosition(Vec2(0, -1000));
		keeper2->setPosition(Vec2(0, -1000));
	}
	if (_ball>1){
		//static keeper

		//alpha fade in
		goalkeeper1->setVisible(true);
		goalkeeper2->setVisible(true);
		goalkeeper1->getChild("Nightrunner_silhouette")->getChildByName("Nightrunner_silhouette")->setOpacity(0);
		goalkeeper2->getChild("Nightrunner_silhouette")->getChildByName("Nightrunner_silhouette")->setOpacity(0);
		FadeIn *alphaMoveActionAc1 = FadeIn::create(0.5);
		auto alphaMoveAction1 = EaseSineInOut::create(alphaMoveActionAc1->clone());
		FadeIn *alphaMoveActionAc2 = FadeIn::create(0.5);
		auto alphaMoveAction2 = EaseSineInOut::create(alphaMoveActionAc2->clone());
		goalkeeper1->getChild("Nightrunner_silhouette")->getChildByName("Nightrunner_silhouette")->runAction(alphaMoveAction1);
		goalkeeper2->getChild("Nightrunner_silhouette")->getChildByName("Nightrunner_silhouette")->runAction(alphaMoveAction2);

		//position
        //srand( static_cast<unsigned int>(time(NULL)));
		int sxOrDx = 1 + rand() % 2;
		int displacement = -100;
		if (sxOrDx == 1)displacement = 100;
		positionKeeper = displacement;
		orientationKeeper = 1;
		goalkeeper1->setPosition(Vec2(door1Node->getPosition().x + displacement, door1Node->getPosition().y - 80));
		goalkeeper2->setPosition(Vec2(door2Node->getPosition().x + displacement, door2Node->getPosition().y - 80));
		keeper1->setPosition(Vec2(goalkeeper1->getPosition().x, goalkeeper1->getPosition().y));
		keeper2->setPosition(Vec2(goalkeeper2->getPosition().x, goalkeeper2->getPosition().y));
	}
	if (_ball > 3){
		//dynamic keeper
		keeperAnimated = true;
	}

	
}



void PenaltyKickGame::hideObjects()
{
    auto sprial1 = static_cast<Node*>(rootNode->getChildByName("Spirale_A"));
    sprial1->setVisible(false);
    auto sprial2 = static_cast<Node*>(rootNode->getChildByName("Spirale_B"));
    sprial2->setVisible(false);
    
    
    auto doorLeftNode = static_cast<Node*>(rootNode->getChildByName("Porta_A"));
    doorLeftNode->setVisible(false);
    
    auto doorRightNode = static_cast<Node*>(rootNode->getChildByName("Porta_B"));
    doorRightNode->setVisible(false);
    
    auto handNode = static_cast<Node*>(rootNode->getChildByName("manina"));
    handNode->setVisible(false);
}

void PenaltyKickGame::playLetters(){
	// string correctPhonemeAudio = DataProvider::getInstance()->getCurrentDBKnowledgeBubble()->getPhoneme();
	audioEngine->playEffect(("common/audio/grandpa/phonemes/" + phonemeOk + ".mp3").c_str());
}


void PenaltyKickGame::showTutorial()
{
    
    auto help = static_cast<Node*>(rootNode->getChildByName("Help"));
   
    auto letterPart = static_cast<Node*>(help->getChildByName("Lettera_a"));
    
    CCLOG("creo phonemeHelp");
    string phHelp =  DataProvider::getInstance()->getCurrentDBKnowledgeBubble()->getPhoneme();
    if (DataProvider::getInstance()->getCurrentEpisode() == 3) {
        phHelp = phHelp.substr(0, phHelp.find("#"));
        phHelp = phHelp + "_a";
    } else if (DataProvider::getInstance()->getCurrentEpisode() == 1) {
        string::size_type idxEp1 = phHelp.find("#ep1");
        if (idxEp1 != string::npos)
            phHelp.erase(idxEp1, 4); // 4 is length of "#ep1"
    }
    phonemeHelp = new LabelGameObject(*letterPart, Vec2::ZERO, "common/fonts/Arabic-Regular.ttf", 300, phHelp, Color3B(47,109,182), true);
   
    //
    help->setVisible(true);
	auto helpTimeline = CSLoader::createTimeline(PATH + "csd/Help_Penalty.csb");
    help->runAction(helpTimeline);
    helpTimeline->play("Help", false);
    
    audioEngine->playEffect("PenaltyKickGame/audio/help.mp3");

    letterPart->runAction(
            Sequence::createWithTwoActions(
                    DelayTime::create(1.7),
                    CallFunc::create(
                            [=]() {
                                
                                if ( DataProvider::getInstance()->getSkin() == 9) {
                                    CCLOG("rain");
                                    static_cast<ParticleSystemQuad*>(rootNode->getChildByName("Particle"))->setVisible(true);
                                }
                                
                                //string correctPhoneme = DataProvider::getInstance()->getCurrentDBKnowledgeBubble()->getPhoneme();
                                //audioEngine->playEffect("common/audio/grandpa/phonemes/sh.mp3");
                               // audioEngine->playEffect(("common/audio/grandpa/phonemes/" + correctPhoneme + ".mp3").c_str());
								playLetters();

								CallFunc *runCallback_letter2 = CallFunc::create(CC_CALLBACK_0(PenaltyKickGame::playLetters, this));
								this->runAction(Sequence::create(DelayTime::create(2.1), runCallback_letter2, nullptr));
	
							})
            )
    );
    
    helpTimeline->setLastFrameCallFunc([=](){
      
        startGame();
        helpTimeline->clearLastFrameCallFunc();
    });
    
}

void PenaltyKickGame::handAnimation()
{
	auto handTimeline = CSLoader::createTimeline(PATH + "csd/manina_calcio.csb");
    hand->runAction(handTimeline);
    handTimeline->play("manina", true);
    
    hand->setOpacity(0);
    hand->setVisible(true);
    hand->runAction(FadeIn::create(0.5));
}


void PenaltyKickGame::startGame()
{
    CCLOG("PenaltyKickGame - startGame");
    Logger::getInstance()->logEvent("Soccer", Logger::OPEN, "");
    
	audioEngine->playBackgroundMusic("common/audio/bg/GAME_2.mp3", true);
  
    //---Animazione Palla
	auto ballTimeline = CSLoader::createTimeline(PATH + "csd/Palla.csb");
    ball->runAction(ballTimeline);
    ballTimeline->play("Palla_cade", false);
    audioEngine->playEffect("PenaltyKickGame/audio/palla_cade.mp3");
    
    ballTimeline->setLastFrameCallFunc([=](){
        
        startDetectingSwipe();
        
        canSwipe = true;
        
        if ( tutorialIsToShow ) {
            IS_TUTORIAL_SHOWN = true;
            // animazione manina
            handAnimation();
        }
        ballTimeline->clearLastFrameCallFunc();
        
    });
    
    
    
    
    // Porta left
    auto doorLeftNode = static_cast<Node*>(rootNode->getChildByName("Porta_A"));
    doorLeftNode->setVisible(true);
	auto doorLeftTimeline = CSLoader::createTimeline(PATH + "csd/Porta.csb");
    doorLeftNode->runAction(doorLeftTimeline);
    doorLeftTimeline->play("Porta_A", false);
    audioEngine->playEffect("PenaltyKickGame/audio/porta_pop.mp3");
    
	netLine = doorLeftNode->getPosition().y-127;

    // Porta right
    auto doorRightNode = static_cast<Node*>(rootNode->getChildByName("Porta_B"));
    doorRightNode->setVisible(true);
	auto doorRightTimeline = CSLoader::createTimeline(PATH + "csd/Porta.csb");
    doorRightNode->runAction(doorRightTimeline);
    doorRightTimeline->play("Porta_A", false);
    audioEngine->playEffect("PenaltyKickGame/audio/porta_pop.mp3");
    
    
    // create letters
    
    auto letterLeftCont = static_cast<Node*>(rootNode->getChildByName("letterLeftCont"));
    letterLeft = ArabicHelper::getInstance()->createLabel("", 165); // Label::createWithTTF("","common/fonts/Arabic-Regular.ttf",165);
    letterLeft->enableShadow(Color4B(15,44,98,128),Size(5,-5),0);
    letterLeft->setOpacity(0);
    letterLeftCont->addChild(letterLeft);
    
    auto letterRightCont = static_cast<Node*>(rootNode->getChildByName("letterRightCont"));
    letterRight = ArabicHelper::getInstance()->createLabel("", 165); // Label::createWithTTF("","common/fonts/Arabic-Regular.ttf",165);
    letterRight->enableShadow(Color4B(15,44,98,128),Size(5,-5),0);
    letterRight->setOpacity(0);
    letterRightCont->addChild(letterRight);
    
    
    addPointsCounter();
    
    
    randomizaCorrectDoor();
    
	setKeeper(1);
}


void PenaltyKickGame::setInitialParameters() {
    

    visibleSize = Director::getInstance()->getVisibleSize();
    canSwipe = false;
    gameTime = 0;
    goalDone = 0;
    hasTocalculateTime =false;
    
    ball = static_cast<Node*>(rootNode->getChildByName("Palla"));
    
    scorePercent = 100.0f;
    scoreToSubtract = 20.0f;
    
    int skin = DataProvider::getInstance()->getSkin();
    static_cast<Sprite*>(ball->getChildByName("Palla")->getChildByName("Palla"))->setTexture(PATH+"png/ball/ball_" +  StringUtility::toString(skin) + ".png");
    
}

void PenaltyKickGame::preloadAudio(){
    audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
   
    audioEngine->preloadBackgroundMusic("common/audio/bg/GAME_2.mp3");
    
    
    audioEngine->preloadEffect("PenaltyKickGame/audio/palla_cade.mp3");
    
    audioEngine->preloadEffect("PenaltyKickGame/audio/help.mp3");
    audioEngine->preloadEffect("PenaltyKickGame/audio/tiro.mp3");
    audioEngine->preloadEffect("PenaltyKickGame/audio/porta_pop.mp3");
    audioEngine->preloadEffect("PenaltyKickGame/audio/vuvuzela.mp3");
    audioEngine->preloadEffect("PenaltyKickGame/audio/follabuuu.mp3");

	audioEngine->preloadEffect("PenaltyKickGame/audio/error.mp3");
	audioEngine->preloadEffect("PenaltyKickGame/audio/hit_palo.mp3");
	audioEngine->preloadEffect("PenaltyKickGame/audio/Paul_tryagain.mp3");
	audioEngine->preloadEffect("PenaltyKickGame/audio/Paul_welldone.mp3");
	audioEngine->preloadEffect("PenaltyKickGame/audio/rimbalzo.mp3");
	audioEngine->preloadEffect("PenaltyKickGame/audio/Sema_tryagain.mp3");
	audioEngine->preloadEffect("PenaltyKickGame/audio/Sema_welldone.mp3");

	
	
	audioEngine->preloadEffect(("common/audio/sema/phonemes/" + StringUtility::toString(phonemeOk) + ".mp3").c_str());
	//audioEngine->preloadEffect(("common/audio/sema/phonemes/" + StringUtility::toString(phonemeKo) + ".mp3").c_str());
	
    
}


void PenaltyKickGame::randomizaCorrectDoor()
{
    isDoorLeftTheCorrect = false;
    
    int randomInt = rand() % 1000;
    if (randomInt < 500) isDoorLeftTheCorrect = true;
    
    
    letterLeft->runAction(FadeIn::create(0.5f));
    letterRight->runAction(FadeIn::create(0.5f));
    
    string correctLetter = DataProvider::getInstance()->getCurrentDBKnowledgeBubble()->getPhoneme();
    //string wrongLetter = DataProvider::getInstance()->getRandomWrongPhoneme(correctLetter);
	phonemeKo = DataProvider::getInstance()->getRandomWrongPhoneme(correctLetter);
    
    if (DataProvider::getInstance()->getCurrentEpisode() == 3) {
        phonemeKo = phonemeKo.substr(0, phonemeKo.find("#"));
    } else if (DataProvider::getInstance()->getCurrentEpisode() == 1) {
        string::size_type idxEp1 = phonemeKo.find("#ep1");
        if (idxEp1 != string::npos)
            phonemeKo.erase(idxEp1, 4); // 4 is length of "#ep1"
    }
    
    
    
    string phonemeOkToShow = DataProvider::getInstance()->checkAndCorrectDuplicatePhoneme(phonemeOk);
    string phonemeKoToShow = DataProvider::getInstance()->checkAndCorrectDuplicatePhoneme(phonemeKo);
    
    if (isDoorLeftTheCorrect) {
		letterLeft->setString( ArabicHelper::getInstance()->getInArabic( phonemeOkToShow ) ); //letterLeft->setString( "a" );
		letterRight->setString(  ArabicHelper::getInstance()->getInArabic( phonemeKoToShow ) ); // letterRight->setString("t");
    } else {
		letterLeft->setString(  ArabicHelper::getInstance()->getInArabic( phonemeKoToShow ) ); // letterLeft->setString("t");
		letterRight->setString(  ArabicHelper::getInstance()->getInArabic( phonemeOkToShow ) );  //letterRight->setString("a");
    }
    
    
    CCLOG("isDoorLeftTheCorrect = %d", isDoorLeftTheCorrect);
}

void PenaltyKickGame::startDetectingSwipe()
{
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(PenaltyKickGame::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(PenaltyKickGame::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(PenaltyKickGame::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(PenaltyKickGame::onTouchCancelled, this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    isTouchDown = false;
    
    initialTouchPos[0] = 0;
    initialTouchPos[1] = 0;
    
    this->scheduleUpdate();
}


void PenaltyKickGame::update(float dt)
{
    if (!canSwipe) return;
    
    if (hasTocalculateTime) gameTime += dt;
    
    if (true == isTouchDown)
    {
        
        if (initialTouchPos[0] - currentTouchPos[0] > visibleSize.width * 0.105)
        {
            CCLOG("SWIPED LEFT");
            isTouchDown = false;
            
        }
        if (initialTouchPos[0] - currentTouchPos[0] < - visibleSize.width * 0.108)
        {
            CCLOG("SWIPED RIGHT");
            isTouchDown = false;
            
        }
        if (initialTouchPos[1] - currentTouchPos[1] > visibleSize.width * 0.05)
        {
            CCLOG("SWIPED DOWN");
            isTouchDown = false;
            
        }
        if (initialTouchPos[1] - currentTouchPos[1] < - visibleSize.width * 0.05)
        {
            CCLOG("SWIPED UP");
            moveUpGestureDone = true;
            isTouchDown = false;
        }
        
    }


	if (keeperAnimated){
		auto door1Node = static_cast<Node*>(rootNode->getChildByName("Porta_A"));
		auto door2Node = static_cast<Node*>(rootNode->getChildByName("Porta_B"));
		auto keeper1 = static_cast<Node*>(rootNode->getChildByName("keeper1"));
		auto keeper2 = static_cast<Node*>(rootNode->getChildByName("keeper2"));

		positionKeeper += 5 * orientationKeeper;
		//CCLOG("positionKeeper %i", positionKeeper);
		if (positionKeeper > 100){
			positionKeeper = 100;
			orientationKeeper = -1;
		}
		if (positionKeeper < -100){
			positionKeeper = -100;
			orientationKeeper = 1;
		}

		goalkeeper1->setPosition(Vec2(door1Node->getPosition().x + positionKeeper, door1Node->getPosition().y - 80));
		goalkeeper2->setPosition(Vec2(door2Node->getPosition().x + positionKeeper, door2Node->getPosition().y - 80));
		keeper1->setPosition(Vec2(goalkeeper1->getPosition().x, goalkeeper1->getPosition().y));
		keeper2->setPosition(Vec2(goalkeeper2->getPosition().x, goalkeeper2->getPosition().y));
	}



	if (moveBall){
	//	anglekick = angle;
	//	powerLinear = 100;
	//	powerVertical = power;
		
		
		int deltaOutline = 70;
		if (inGoal)deltaOutline = 30;
		if (posYLinear >= netLine + deltaOutline){
			posYLinear = netLine + deltaOutline;
		}
		else{
			posXLinear = posXLinear + cos(anglekick)*powerLinear*ball->getScale();
			posYLinear = posYLinear + sin(anglekick)*powerLinear*directionY*ball->getScale();
		}
		heightBall = heightBall + powerVertical;

		if (heightBall < 0){
			//CCLOG("------------------------------------------powerVertical %f", powerVertical);
			if (powerVertical<-5.0f)audioEngine->playEffect("PenaltyKickGame/audio/rimbalzo.mp3");
			powerVertical = -powerVertical;
			powerVertical = powerVertical / 2;
			ballRotationR = ballRotationR / 2;
			if (powerVertical < 2){
				powerVertical = 0;
			}
			if (!ballStop){
				if (ballRotationR < 2 && ballRotationR>=0){
					ballRotationR = 2;
				}
				if (ballRotationR > -2 && ballRotationR < 0){
					ballRotationR = -2;
				}
			}
			heightBall = 1;
			
		}

		powerVertical = powerVertical - 1.0f;

		//CCLOG("posX %f", posXLinear);
		//CCLOG("posY %f", posYLinear);

		//CCLOG("powerVertical %f", powerVertical);

		float scaleBall = ((_director->getWinSize().height / 2) - posYLinear + 130) / (_director->getWinSize().height / 2);
		if (scaleBall < 0.0001)scaleBall = 0.0001;
		ball->setScale(scaleBall);


		
		ball->setPosition(Vec2(posXLinear, posYLinear + (heightBall*ball->getScale())));
		ball->getChildByName("ombra_palla")->setPositionY(-heightBall-80);

		ball->getChildByName("Palla")->getChildByName("Palla")->setRotation(ball->getChildByName("Palla")->getChildByName("Palla")->getRotation() + ballRotationR);



		if (posYLinear > netLine && !checkGoal){
			checkGoal = true;
			//isDoorLeftTheCorrect
			int a = getKickResult();
			CCLOG("TIPO DI RISULTATO: %i", a);
			inGoal = false;
			if (a == 0){
				//out
				ballStop = true;
				adjustLevel(0);
				runOutFeedback();
                              scorePercent -= scoreToSubtract;

			}else if (a == 1 || a == 2){
				//goal
				//moveBall = false;
				ballStop = true;
				adjustLevel(1);

                string phonemeOkAudio = phonemeOk;
                string phonemeKoAudio = phonemeKo;
                
				if (a == 1 && isDoorLeftTheCorrect){
					goalOK++;
					//runPositiveFeedback();
					CallFunc *runCallback_Feed = CallFunc::create(CC_CALLBACK_0(PenaltyKickGame::runPositiveFeedback, this));
					this->runAction(Sequence::create(DelayTime::create(1), runCallback_Feed, nullptr));
					audioEngine->playEffect(("common/audio/sema/phonemes/" + phonemeOkAudio + ".mp3").c_str());
				}
				else if(a == 2 && !isDoorLeftTheCorrect){
					goalOK++;
					//runPositiveFeedback();
					CallFunc *runCallback_Feed = CallFunc::create(CC_CALLBACK_0(PenaltyKickGame::runPositiveFeedback, this));
					this->runAction(Sequence::create(DelayTime::create(1), runCallback_Feed, nullptr));
					audioEngine->playEffect(("common/audio/sema/phonemes/" + phonemeOkAudio + ".mp3").c_str());
				}
				else{
					//runNegativeFeedback();
                                      scorePercent -= scoreToSubtract;

					CallFunc *runCallback_Feed = CallFunc::create(CC_CALLBACK_0(PenaltyKickGame::runNegativeFeedback, this));
					this->runAction(Sequence::create(DelayTime::create(1), runCallback_Feed, nullptr));
					audioEngine->playEffect(("common/audio/sema/phonemes/" + phonemeKoAudio + ".mp3").c_str());
				}
				inGoal = true;
			}else if (a == 3){
				//PoleSx
				adjustLevel(2);
				directionY = -1;
				runOutFeedback();
                              scorePercent -= scoreToSubtract;
				audioEngine->playEffect("PenaltyKickGame/audio/hit_palo.mp3");
			}else if (a == 4){
				//PoleDx
				adjustLevel(2);
				directionY = -1;
				runOutFeedback();
                              scorePercent -= scoreToSubtract;
				audioEngine->playEffect("PenaltyKickGame/audio/hit_palo.mp3");
			}else if (a == 5){
				//crossbar
				adjustLevel(2);
				directionY = -1;
				runOutFeedback();
				audioEngine->playEffect("PenaltyKickGame/audio/hit_palo.mp3");
			}else if (a == 6){
				//keeper
				adjustLevel(2);
				directionY = -1;
				runOutFeedback();                               
                              scorePercent -= scoreToSubtract;

				audioEngine->playEffect("PenaltyKickGame/audio/hit_palo.mp3");
			}
		}


		


	}
	/*if (checkGoal){
		int op = ball->getChildByName("Palla")->getChildByName("Palla")->getOpacity() - 5;
		if (op > 255)op = 255;
		ball->getChildByName("Palla")->getChildByName("Palla")->setOpacity(op);
	}*/
}

void PenaltyKickGame::adjustLevel(int _levelBall){
	if (_levelBall==0)toFront(ball);
	Node* net1 = static_cast<Node*>(rootNode->getChildByName("Porta_A"));
	toFront(net1);
	Node* net2 = static_cast<Node*>(rootNode->getChildByName("Porta_B"));
	toFront(net2);
	Node* letterLeftCont = static_cast<Node*>(rootNode->getChildByName("letterLeftCont"));
	toFront(letterLeftCont);
	Node* letterRightCont = static_cast<Node*>(rootNode->getChildByName("letterRightCont"));
	toFront(letterRightCont);
	if (_levelBall == 1)toFront(ball);
	goalkeeper1->bringToFront();
	goalkeeper2->bringToFront();
	if (_levelBall == 2)toFront(ball);
	Node* paulPositive = static_cast<Node*>(rootNode->getChildByName("Paul_positive"));
	toFront(paulPositive);
	Node* paulNegative = static_cast<Node*>(rootNode->getChildByName("Paul_negative"));
	toFront(paulNegative);
	Node* semaPositive = static_cast<Node*>(rootNode->getChildByName("Sema_positive"));
	toFront(semaPositive);
	Node* semaNegative = static_cast<Node*>(rootNode->getChildByName("Sema_negative"));
	toFront(semaNegative);
	Node* manina = static_cast<Node*>(rootNode->getChildByName("manina"));
	toFront(manina);
	Node* help = static_cast<Node*>(rootNode->getChildByName("Help"));
	toFront(help);

	
}


void PenaltyKickGame::resetKickVars(){
    //srand( static_cast<unsigned int>(time(NULL)));
	ballRotationR = (rand() % 20) - 10;
	if (ballRotationR > -2 && ballRotationR < 2)ballRotationR = 2;
	ballStop = false;
	powerLinear = 0;
	powerVertical = 0;
	anglekick = 0;
	moveBall = false;
	posXLinear = 640;
	posYLinear = 130;
	heightBall = 0;
	checkGoal = false;
	directionY = 1;
	keeperAnimated = false;
}

void PenaltyKickGame::toFront(Node* _child, Node* _parent) {
	if (_parent == nullptr) _parent = static_cast<Node*>(_child->getParent());
	_child->retain();
	_child->removeFromParent();
	_parent->addChild(_child);
	_child->release();
}


int PenaltyKickGame::getKickResult() {

	//  auto doorHit = door->getBoundingBox();

	int _val = 0;

	auto doorHit1_1 = static_cast<Node*>(rootNode->getChildByName("hit_1_1"))->getBoundingBox();
	auto doorHit1_2 = static_cast<Node*>(rootNode->getChildByName("hit_1_2"))->getBoundingBox();
	auto doorHit2_1 = static_cast<Node*>(rootNode->getChildByName("hit_2_1"))->getBoundingBox();
	auto doorHit2_2 = static_cast<Node*>(rootNode->getChildByName("hit_2_2"))->getBoundingBox();
	auto doorHitCross1 = static_cast<Node*>(rootNode->getChildByName("crossbar_1"))->getBoundingBox();
	auto doorHitCross2 = static_cast<Node*>(rootNode->getChildByName("crossbar_2"))->getBoundingBox();
	auto doorHitPoleSx1 = static_cast<Node*>(rootNode->getChildByName("pole_1_sx"))->getBoundingBox();
	auto doorHitPoleDx1 = static_cast<Node*>(rootNode->getChildByName("pole_1_dx"))->getBoundingBox();
	auto doorHitPoleSx2 = static_cast<Node*>(rootNode->getChildByName("pole_2_sx"))->getBoundingBox();
	auto doorHitPoleDx2 = static_cast<Node*>(rootNode->getChildByName("pole_2_dx"))->getBoundingBox();
	auto keeper1 = static_cast<Node*>(rootNode->getChildByName("keeper1"))->getBoundingBox();
	auto keeper2 = static_cast<Node*>(rootNode->getChildByName("keeper2"))->getBoundingBox();

	if (keeper1.containsPoint(ball->getPosition()) || keeper2.containsPoint(ball->getPosition())){
		CCLOG("-----KEEPER");
		_val = 6;
	}else
	if (doorHitCross1.containsPoint(ball->getPosition()) || doorHitCross2.containsPoint(ball->getPosition())){
		CCLOG("-----CROSSBAR");
		
		_val = 5;
	}
	else if (doorHitPoleSx1.containsPoint(ball->getPosition()) || doorHitPoleSx2.containsPoint(ball->getPosition())){
		CCLOG("-----POLE SX");
		_val = 3;
	}
	else if (doorHitPoleDx1.containsPoint(ball->getPosition()) || doorHitPoleDx2.containsPoint(ball->getPosition())){
		CCLOG("-----POLE DX");
		_val = 4;
	}
	else if (doorHit1_1.containsPoint(ball->getPosition()) || doorHit1_2.containsPoint(ball->getPosition())){
		CCLOG("-----GOAL");
		_val = 1;
	}
	else if (doorHit2_1.containsPoint(ball->getPosition()) || doorHit2_2.containsPoint(ball->getPosition())){
		CCLOG("-----GOAL");
		_val = 2;
		
	}
	else{
		CCLOG("-----OUT");
		_val = 0;
		
	}

	return _val;
}

bool PenaltyKickGame::touchIsOnBall(Touch *touch) {

    auto ballhitNode = static_cast<Node*>(rootNode->getChildByName("ballHit"));
    auto ballhit = ballhitNode->getBoundingBox();
    if (ballhit.containsPoint( touch->getLocation() )) {
        return true;
    }
    return false;
    
 
}

bool PenaltyKickGame::onTouchBegan(Touch *touch, Event *event)
{
    if (touchIsOnBall(touch) == false) return false;
    
    if (!canSwipe) return false;
    
    initialTouchPos[0] = touch->getLocation().x;
    initialTouchPos[1] = touch->getLocation().y;
    currentTouchPos[0] = touch->getLocation().x;
    currentTouchPos[1] = touch->getLocation().y;
    
    isTouchDown = true;
    moveUpGestureDone = false;
    gameTime = 0;
    hasTocalculateTime = true;
    startX = touch->getLocation().x;
    startY = touch->getLocation().y;
    
    //   CCLOG("onTouchBegan ID: %d, X: %f, Y: %f", touch->getID(), touch->getLocation().x, touch->getLocation().y);
    
    return true;
}



void PenaltyKickGame::onTouchMoved(Touch *touch, Event *event)
{
    if (!canSwipe) return;
    currentTouchPos[0] = touch->getLocation().x;
    currentTouchPos[1] = touch->getLocation().y;
}

void PenaltyKickGame::onTouchEnded(Touch *touch, Event *event)
{
    isTouchDown = false;
    
    hasTocalculateTime = false;
    CCLOG("gameTime = %f", gameTime);
    
	float angle = atan2(touch->getLocation().y - 130, touch->getLocation().x - 640);
	float power = sqrt(std::pow(640 - touch->getLocation().x, 2) + std::pow(130 - touch->getLocation().y, 2))*0.6;
	CCLOG("angle = %f", angle);
	CCLOG("power = %f", power);

   // Vec2 direction = Vec2( Vec2(startX,startY), Vec2(touch->getLocation().x, touch->getLocation().y) );

	if (angle < 0.4)angle = 0.4;
	if (angle > 2.7)angle = 2.7;
	if (power > 400)power = 400;
	if (power < 100)power = 100;
   // direction.normalize();
    
	kickBall(angle, power);


   /* if ((moveUpGestureDone) && (gameTime<0.5)) {
        launchBall(direction.x*500, direction.y*500, gameTime*1.2);
    }*/
}

void PenaltyKickGame::kickBall(float angle, float power){
	if (hand->isVisible()) {
		hand->stopAllActions();
		hand->setVisible(false);
	}

	moveBall = true;
	anglekick = angle;
	powerLinear = 10;
	powerVertical = power/10;
	if (powerVertical < 0)powerVertical = 0;
	toFront(ball);
}

void PenaltyKickGame::stopBall(){
	moveBall = false;
}



bool PenaltyKickGame::ballIsInCorrectDoor()
{
    
    if ( isBallInDoor(1) && isDoorLeftTheCorrect ) return true;
    if ( isBallInDoor(2) && !isDoorLeftTheCorrect ) return true;
    
    
    return false;
}


bool PenaltyKickGame::isBallInDoor(int door) {
    
  //  auto doorHit = door->getBoundingBox();

	auto doorHit1 = static_cast<Node*>(rootNode->getChildByName("hit_" + StringUtility::toString(door) + "_1"))->getBoundingBox();
	auto doorHit2 = static_cast<Node*>(rootNode->getChildByName("hit_" + StringUtility::toString(door) + "_2"))->getBoundingBox();
	auto doorHitCross = static_cast<Node*>(rootNode->getChildByName("crossbar_" + StringUtility::toString(door)))->getBoundingBox();
	auto doorHitPoleSx = static_cast<Node*>(rootNode->getChildByName("pole_" + StringUtility::toString(door) + "_sx"))->getBoundingBox();
	auto doorHitPoleDx = static_cast<Node*>(rootNode->getChildByName("pole_" + StringUtility::toString(door) + "_dx"))->getBoundingBox();


	if (doorHitCross.containsPoint(ball->getPosition())){
		CCLOG("-----CROSSBAR");
		return false;
	}else if (doorHitPoleSx.containsPoint(ball->getPosition())){
		CCLOG("-----POLE SX");
		return false;
	}else if (doorHitPoleDx.containsPoint(ball->getPosition())){
		CCLOG("-----POLE DX");
		return false;
	}else if (doorHit1.containsPoint(ball->getPosition()) || doorHit2.containsPoint(ball->getPosition())){
		CCLOG("-----GOAL");
		return true;
	}else{
		CCLOG("-----OUT");
		return false;
	}
    
     
}




void PenaltyKickGame::runSpiralAnimation()
{

    Node *feedNode;
    Node *doorNode;
    if (isDoorLeftTheCorrect) {
        feedNode = static_cast<Node*>(rootNode->getChildByName("Spirale_A"));
        doorNode = static_cast<Node*>(rootNode->getChildByName("Porta_A"));
    }
    else {
        feedNode = static_cast<Node*>(rootNode->getChildByName("Spirale_B"));
        doorNode = static_cast<Node*>(rootNode->getChildByName("Porta_B"));
    }
    
    feedNode->setVisible(true);
    

	auto feedTimeline = CSLoader::createTimeline(PATH + "csd/Spirale.csb");
    feedNode->runAction(feedTimeline);
    feedTimeline->play("Spirale_pop", false);
    
    feedTimeline->setLastFrameCallFunc([=](){
        feedNode->setVisible(false);
       // runVuvuzelaAnimation();
        feedTimeline->clearLastFrameCallFunc();
    });

	runVuvuzelaAnimation();
    
    // seconda animazione porta
	auto doorTimeline = CSLoader::createTimeline(PATH + "csd/Porta.csb");
    doorNode->runAction(doorTimeline);
    doorTimeline->play("porta_B", false);
}


void PenaltyKickGame::runVuvuzelaAnimation()
{
    audioEngine->playEffect("PenaltyKickGame/audio/vuvuzela.mp3");
    Node *feedNode = static_cast<Node*>(rootNode->getChildByName("Vuvuzela_1"));
	auto feedTimeline = CSLoader::createTimeline(PATH + "csd/vuvuzela.csb");
    feedNode->runAction(feedTimeline);
    feedTimeline->play("Vuvuzela_A", false);
    
    feedTimeline->setLastFrameCallFunc([=](){
        // feedTimeline->clearLastFrameCallFunc();
        feedTimeline->play("Vuvuzela_B", false);
        feedTimeline->setLastFrameCallFunc([=](){
			runPaulPositiveFeedback();
            feedTimeline->clearLastFrameCallFunc();
        });
    });
    
     
     
    Node *feedNode2 = static_cast<Node*>(rootNode->getChildByName("Vuvuzela_2"));
	auto feedTimeline2 = CSLoader::createTimeline(PATH + "csd/vuvuzela.csb");
    feedNode2->runAction(feedTimeline2);
    feedTimeline2->play("Vuvuzela_A", false);
    
    feedTimeline2->setLastFrameCallFunc([=](){
        feedTimeline2->play("Vuvuzela_B", false);
        feedTimeline2->clearLastFrameCallFunc();
    });
}

void PenaltyKickGame::runPaulPositiveFeedback()
{
    audioEngine->playEffect("PenaltyKickGame/audio/Paul_welldone.mp3");
    auto feedNode = static_cast<Node*>(rootNode->getChildByName("Paul_positive"));
	auto feedTimeline = CSLoader::createTimeline(PATH + "csd/Paul_positive.csb");
    feedNode->runAction(feedTimeline);
    feedTimeline->play("Paul_positive_A", false);
    
    feedTimeline->setLastFrameCallFunc([=](){
        // feedTimeline->clearLastFrameCallFunc();
        feedTimeline->play("Paul_positive_B", false);
        
        feedTimeline->setLastFrameCallFunc([=](){
            increaseScore(true);
            feedTimeline->clearLastFrameCallFunc();
        });
        
    });
}


void PenaltyKickGame::runSemaPositiveFeedback()
{
	audioEngine->playEffect("PenaltyKickGame/audio/Sema_welldone.mp3");
	auto feedNode = static_cast<Node*>(rootNode->getChildByName("Sema_positive"));
	auto feedTimeline = CSLoader::createTimeline(PATH + "csd/Sema_positive.csb");
	feedNode->runAction(feedTimeline);
	feedTimeline->play("Sema_positive_A", false);

	feedTimeline->setLastFrameCallFunc([=](){
		// feedTimeline->clearLastFrameCallFunc();
		feedTimeline->play("Sema_positive_B", false);

		feedTimeline->setLastFrameCallFunc([=](){
			finish(true);
			feedTimeline->clearLastFrameCallFunc();
		});

	});
}
void PenaltyKickGame::runSemaNegativeFeedback()
{
	audioEngine->playEffect("PenaltyKickGame/audio/Sema_tryagain.mp3");
	auto feedNode = static_cast<Node*>(rootNode->getChildByName("Sema_negative"));
	auto feedTimeline = CSLoader::createTimeline(PATH + "csd/Sema_negative.csb");
	feedNode->runAction(feedTimeline);
	feedTimeline->play("Sema_negative_A", false);

	feedTimeline->setLastFrameCallFunc([=](){
		// feedTimeline->clearLastFrameCallFunc();
		feedTimeline->play("Sema_negative_B", false);

		feedTimeline->setLastFrameCallFunc([=](){
			finish(false);
			feedTimeline->clearLastFrameCallFunc();
		});
	});
}

void PenaltyKickGame::finish(bool _result){
    // fine gioco!
    CCLOG("fine gioco");
    DataProvider *dataProvider = DataProvider::getInstance();
	audioEngine->stopBackgroundMusic();
    if (_result) {
        // è andato bene
        Logger::getInstance()->logEvent("Soccer", Logger::WIN, "");
        Logger::getInstance()->logEvent("Soccer", Logger::CLOSE, "");
        dataProvider->setGameCompleted("PenaltyKick", 3.2);
        dataProvider->setWatchmanReaction(WatchmanScene::GOOD_REACTION);
        _director->replaceScene(TransitionFade::create(TRANSITION_TIME, WatchmanScene::createScene(), TRANSITION_COLOR));
    } else {
        // ho perso
        Logger::getInstance()->logEvent("Soccer", Logger::LOSE, "");
        Logger::getInstance()->logEvent("Soccer", Logger::CLOSE, "");
        dataProvider->setWatchmanReaction(WatchmanScene::BAD_REACTION);
        _director->replaceScene(TransitionFade::create(TRANSITION_TIME, WatchmanScene::createScene(), TRANSITION_COLOR));
    }

}



void PenaltyKickGame::increaseScore(bool correct)
{
    goalDone++;
    
    
    //faccio animazione del pallone conta punti
    std::string dotName = "Punti_";
    dotName.append(cocos2d::StringUtils::toString(goalDone));
    auto dotNode = static_cast<Node*>(rootNode->getChildByName(dotName));
	auto dotTimeline = CSLoader::createTimeline(PATH + "csd/Punti.csb");
    
    dotNode->runAction(dotTimeline);
	if (correct){
		dotTimeline->play("Contenitore_B", false);
	}
	else{
		dotTimeline->play("Contenitore_C", false);
		audioEngine->playEffect("PenaltyKickGame/audio/error.mp3");
	}
    
    dotTimeline->setLastFrameCallFunc([=](){
		CCLOG("GOALLLLLLLLLL ::::::::::: %i", goalOK);
        if (goalDone == 5) {
			if (goalOK>=3)runSemaPositiveFeedback();
			else runSemaNegativeFeedback();
        } else {     
            resetLaunch();
        }
        
        dotTimeline->clearLastFrameCallFunc();
        
    });
    
   
}

void PenaltyKickGame::fadeOutKeeper(){
	if (goalDone != 0){
		//alpha fade out
		FadeOut *alphaMoveActionAc1 = FadeOut::create(0.5);
		auto alphaMoveAction1 = EaseSineInOut::create(alphaMoveActionAc1->clone());
		FadeOut *alphaMoveActionAc2 = FadeOut::create(0.5);
		auto alphaMoveAction2 = EaseSineInOut::create(alphaMoveActionAc2->clone());
		goalkeeper1->getChild("Nightrunner_silhouette")->getChildByName("Nightrunner_silhouette")->runAction(alphaMoveAction1);
		goalkeeper2->getChild("Nightrunner_silhouette")->getChildByName("Nightrunner_silhouette")->runAction(alphaMoveAction2);
	}

	letterLeft->runAction(FadeOut::create(0.5));
	letterRight->runAction(FadeOut::create(0.5));
}


void PenaltyKickGame::runPositiveFeedback()
{
	CallFunc *runCallback_fade = CallFunc::create(CC_CALLBACK_0(PenaltyKickGame::fadeOutKeeper, this));
	this->runAction(Sequence::create(DelayTime::create(0.5), runCallback_fade, nullptr));

	Logger::getInstance()->logEvent("Soccer", Logger::CORRECT, "");
	CCLOG("Feedback POSITIVO");
	runSpiralAnimation();
}

void PenaltyKickGame::runNegativeFeedback()
{
    CCLOG("Feedback NEGATIVO");
	CallFunc *runCallback_fade = CallFunc::create(CC_CALLBACK_0(PenaltyKickGame::fadeOutKeeper, this));
	this->runAction(Sequence::create(DelayTime::create(0.5), runCallback_fade, nullptr));

    Logger::getInstance()->logEvent("Soccer", Logger::WRONG, "");
    
    audioEngine->playEffect("PenaltyKickGame/audio/Paul_tryagain.mp3");
    audioEngine->playEffect("PenaltyKickGame/audio/follabuuu.mp3");
    
    auto feedNode = static_cast<Node*>(rootNode->getChildByName("Paul_negative"));
	auto feedTimeline = CSLoader::createTimeline(PATH + "csd/Paul_negative.csb");
    feedNode->runAction(feedTimeline);
    feedTimeline->play("Paul_negative_A", false);
   
    feedTimeline->setLastFrameCallFunc([=](){
        // feedTimeline->clearLastFrameCallFunc();
        feedTimeline->play("Paul_negative_B", false);
        
        feedTimeline->setLastFrameCallFunc([=](){
			increaseScore(false);
            feedTimeline->clearLastFrameCallFunc();
        });
        
    });
}
void PenaltyKickGame::runOutFeedback()
{
	CCLOG("Feedback NEGATIVO");

	CallFunc *runCallback_fade = CallFunc::create(CC_CALLBACK_0(PenaltyKickGame::fadeOutKeeper, this));
	this->runAction(Sequence::create(DelayTime::create(0.5), runCallback_fade, nullptr));

	
	Logger::getInstance()->logEvent("Soccer", Logger::WRONG, "");

	audioEngine->playEffect("PenaltyKickGame/audio/Paul_tryagain.mp3");
	audioEngine->playEffect("PenaltyKickGame/audio/follabuuu.mp3");

	auto feedNode = static_cast<Node*>(rootNode->getChildByName("Paul_negative"));
	auto feedTimeline = CSLoader::createTimeline(PATH + "csd/Paul_negative.csb");
	feedNode->runAction(feedTimeline);
	feedTimeline->play("Paul_negative_A", false);

	feedTimeline->setLastFrameCallFunc([=](){
		// feedTimeline->clearLastFrameCallFunc();
		feedTimeline->play("Paul_negative_B", false);

		feedTimeline->setLastFrameCallFunc([=](){
			resetLaunch();
			feedTimeline->clearLastFrameCallFunc();
		});

	});
}



void PenaltyKickGame::resetLaunch()
{
	
	

    CCLOG("resetLaunch");
    ball->getChildByName("Palla")->setOpacity(255.0);
    ball->getChildByName("ombra_palla")->setOpacity(255.0);
    ball->setScale(1.0);
    // ball->setPosition(Point(visibleSize.width/2, 0.2*visibleSize.height /2));
    ball->setPosition(Point(640,130));
    
	resetKickVars();
	setKeeper(goalDone + 1);
	toFront(ball);
    
	auto ballTimeline = CSLoader::createTimeline(PATH + "csd/Palla.csb");
    ball->runAction(ballTimeline);
    ballTimeline->play("Palla_cade", false);
    audioEngine->playEffect("PenaltyKickGame/audio/palla_cade.mp3");
	ball->getChildByName("Palla")->getChildByName("Palla")->setOpacity(255.0);
    
    ballTimeline->setLastFrameCallFunc([=](){
        canSwipe = true;
        
        ballTimeline->clearLastFrameCallFunc();
    });
	randomizaCorrectDoor();
    
    
    
}

void PenaltyKickGame::onTouchCancelled(Touch *touch, Event *event)
{
    onTouchEnded(touch, event);
}

void PenaltyKickGame::addPointsCounter(){
    
    int i;
    for (i=1; i<=5; i++) {
        std::string dotName = "Punti_";
        dotName.append(cocos2d::StringUtils::toString(i));
        auto dotNode = static_cast<Node*>(rootNode->getChildByName(dotName));
		auto dotTimeline = CSLoader::createTimeline(PATH + "csd/Punti.csb");
        dotNode->runAction(dotTimeline);
        dotTimeline->play("Contenitore_A", false);
    }
    
}


void PenaltyKickGame::addBackToHomeButton(){
    
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
                Logger::getInstance()->logEvent("Soccer", Logger::CLOSE, "");                
                if ( TEST_ENABLED ) {
                    DataProvider::getInstance()->setGameCompleted("PenaltyKick");
                    DataProvider::getInstance()->setWatchmanReaction(WatchmanScene::GOOD_REACTION);
                } else {
                    DataProvider::getInstance()->setWatchmanReaction(WatchmanScene::BAD_REACTION);
                }
                audioEngine->stopBackgroundMusic();
                _director->replaceScene(TransitionFade::create(TRANSITION_TIME, WatchmanScene::createScene(), TRANSITION_COLOR));
                break;
            default:
                break;
        }
    });

}

