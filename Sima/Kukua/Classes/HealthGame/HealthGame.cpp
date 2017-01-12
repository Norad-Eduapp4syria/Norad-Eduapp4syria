#include "HealthGame.h"
#include "../Utils/Data/DataProvider.h"
#include "../Utils/Data/Logger.h"
#include "../AppMacros.h"
#include "../Utils/StringUtility.h"
#include "../MapScene/MapScene.h"

const bool HealthGame::ENABLE_TOUCH = true;								// Used to disable tutorial on first touch and manage general touch events
const string HealthGame::PATH = "HealthGame/";								// Resources' subfolder path for this game

Scene* HealthGame::createScene() {

	// 'scene' is an autorelease object
	Scene* scene = Scene::create();

	// 'layer' is an autorelease object			 
	auto layer = HealthGame::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;

}

HealthGame::~HealthGame() {
    //azzeriamo i timer
    this->stopActionByTag(90);
    this->stopActionByTag(91);
}

bool HealthGame::init() {

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



void HealthGame::startGame() {

	Logger::getInstance()->logEvent("HealthGame", Logger::OPEN, "");
    

	initVariables();
	initAudio();
	initGameObjects();
	fadeIn();
    
 
}

void HealthGame::initVariables() {
    
	dataProvider = DataProvider::getInstance();
    
 
    
}

void HealthGame::initAudio() {

	simpleAudioEngine = SimpleAudioEngine::getInstance();
   
    
}

void HealthGame::initGameObjects() {
    
 
}



void HealthGame::playAudioInstructions() {
    string instruction = PATH + "audio/salute_fisica_skin" + getSlideNum() + ".mp3";
    simpleAudioEngine->playBackgroundMusic(instruction.c_str());
}

void HealthGame::fadeIn() {
    
    CCLOG("HealthGame fade in");
    
   
    CallFunc *closeCallback = CallFunc::create(CC_CALLBACK_0(HealthGame::closeGame, this));
    Action *closeTimeAction = Sequence::create(DelayTime::create(120.0),closeCallback, nullptr);
    closeTimeAction->setTag(91);
    this->runAction(closeTimeAction);
    
    
    simpleAudioEngine->playEffect((PATH + "audio/salute_fisica_intro.mp3").c_str());
    CallFunc *audioCallback = CallFunc::create(CC_CALLBACK_0(HealthGame::playAudioInstructions, this));
    Action *audioTimeAction = Sequence::create(DelayTime::create(5.5),audioCallback, nullptr);
    audioTimeAction->setTag(90);
    this->runAction(audioTimeAction);
    
    
    
    slideNode = static_cast<Node*>(rootNode->getChildByName("Slide"));
    cocostudio::timeline::ActionTimeline* slideTimeline = CSLoader::createTimeline(PATH+"Csd/slide_salute_fisica.csb");
    auto slidePngRef = slideNode->getChildByName("Master_slide")->getChildByName("Slide_1")->getChildByName("Slide");
    static_cast<Sprite*>( slidePngRef )->setTexture(PATH+"slides/Slide_" +  getSlideNum() + ".png");
    slideNode->runAction(slideTimeline);
    slideTimeline->play("stop", false);
    
    
    addBackToHomeButton();
}

string  HealthGame::getSlideNum() {
    string phoneme = DataProvider::getInstance()->getCurrentDBKnowledgeBubble()->getPhoneme();
    string slideNum = phoneme.substr(11, phoneme.length()); // 11 is "HealthGame_" length
    return slideNum;
}

void HealthGame::addBackToHomeButton() {
    
    auto backNode = cocos2d::ui::Button::create(PATH+"Png/backGuardian_btn.png", PATH+"Png/backGuardian_btn.png", PATH+"Png/backGuardian_btn.png");
    /*
    auto frameSize = cocos2d::Director::getInstance()->getWinSize();
    auto x = 90;
    auto y = frameSize.height * 0.9f;
    */
    backNode->setPosition(Vec2(-560, 273));
    slideNode->getChildByName("Master_slide")->addChild(backNode, 10);
    
    backNode->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                closeGame();
                break;
            default:
                break;
        }
    });
    
}

void HealthGame::closeGame() {
    
    string portalCode = string("") + StringUtility::toString( dataProvider->getCurrentDBWatchman()->getEpisode() ) + "-" + StringUtility::toString( dataProvider->getCurrentDBWatchman()->getNumber() ) ;
    DataProvider::getInstance()->setSemaInitialPortalCode(portalCode);
    
    Logger::getInstance()->logEvent("HealthGame", Logger::CLOSE, "");
    simpleAudioEngine->stopAllEffects();
    simpleAudioEngine->stopBackgroundMusic();
    _director->replaceScene(TransitionSlideInL::create(TRANSITION_TIME, MapScene::createScene()));
}

