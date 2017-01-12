#include "TunnelLoop.h"
#include "../Utils/Data/DataProvider.h"
#include "../Utils/Data/Logger.h"
#include "../VideoScene/VideoScene.h"
#include "../WatchmanScene/WatchmanScene.h"


cocos2d::Scene* (*TunnelLoop::NEXT_SCENE_CREATE_SCENE)() = nullptr;

const bool TunnelLoop::ENABLE_TOUCH = true;								// Used to disable tutorial on first touch and manage general touch events
const string TunnelLoop::PATH = "TunnelLoop/";								// Resources' subfolder path for this game

Scene* TunnelLoop::createScene() {

	CCLOG("TunnelLoop - createScene");

	// 'scene' is an autorelease object
	Scene* scene = Scene::create();

	// 'layer' is an autorelease object			 
	auto layer = TunnelLoop::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;

}

TunnelLoop::~TunnelLoop() {

	CCLOG("~TunnelLoop");

	// Delete objects created with new
	//this->unscheduleUpdate();
	delete sema;
    delete bg;


}

bool TunnelLoop::init() {

	CCLOG("TunnelLoop - init");

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

void TunnelLoop::startGame() {

	CCLOG("TunnelLoop - startGame");


	Logger::getInstance()->logEvent("TunnelTransition", Logger::OPEN, "");
    

	initVariables();
	initAudio();
	initGameObjects();
	fadeIn();

	// this->scheduleUpdate();
}

void TunnelLoop::initVariables() {

	dataProvider = DataProvider::getInstance();

}

void TunnelLoop::initAudio() {

	//CCLOG("TunnelLoop - Init audio");

	simpleAudioEngine = SimpleAudioEngine::getInstance();

	// Preload audio files
	//simpleAudioEngine->preloadEffect("TunnelLoop/audio/backhome.mp3");
	simpleAudioEngine->playBackgroundMusic("TunnelLoop/audio/loop.mp3", true);
	
}

void TunnelLoop::initGameObjects() {
		
    auto frameSize =  rootNode->getBoundingBox().size;
    //bg = new GameObject(*rootNode, Vec2(frameSize.width / 2, frameSize.height / 2), "WatchmanScene/CSD/Passaggio.csb");
    bg = new GameObject(*rootNode, Vec2(frameSize.width / 2, frameSize.height / 2), "TunnelLoop/Passaggio.csb");
    
    bg->play("passaggio_loop", [=]() {
        closePage();
        bg->clearLastFrameCallFunc();
    });
    
    
	sema = new GameObject(*rootNode, Vec2(640.0f, 200.0f), "WatchmanScene/CSD/Sema_front.csb");
   
}

void TunnelLoop::fadeIn() {
	
	sema->play("Sema_Vola", nullptr, true);

	/*
	CallFunc *runCallback_end = CallFunc::create(CC_CALLBACK_0(TunnelLoop::closePage, this));
    if ( WatchmanScene::TEST_ENABLED ) {
        this->runAction(Sequence::create(DelayTime::create(3.0), runCallback_end, nullptr));
    } else {
        this->runAction(Sequence::create(DelayTime::create(3.0), runCallback_end, nullptr));
    }
	*/
	

}

void TunnelLoop::closePage(){
    Logger::getInstance()->logEvent("TunnelTransition", Logger::CLOSE, "");
    assert(NEXT_SCENE_CREATE_SCENE != nullptr);
    simpleAudioEngine->stopBackgroundMusic();
    Director::getInstance()->replaceScene(TransitionFade::create(0.7, NEXT_SCENE_CREATE_SCENE(), Color3B(255, 255, 255)));
    
    NEXT_SCENE_CREATE_SCENE = nullptr;
    
}



