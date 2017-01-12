#include "UserCreateScene.h"
#include "UserSelectScene.h"
#include "../Utils/Data/DataProvider.h"
#include "../Utils/Data/Logger.h"
#include "../Utils/CocosCamera/CocosCamera.h"
#include "../Utils/StringUtility.h"
#include "../AppMacros.h"
#include "../Home/HomeGame.h"
#include <time.h>


const bool UserCreateScene::ENABLE_TOUCH = true;								// Used to disable tutorial on first touch and manage general touch events
const string UserCreateScene::PATH = "UserScene/";								// Resources' subfolder path for this game

Scene* UserCreateScene::createScene() {

	// 'scene' is an autorelease object
	Scene* scene = Scene::create();

	// 'layer' is an autorelease object			 
	auto layer = UserCreateScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;

}

UserCreateScene::~UserCreateScene() {

	// CCLOG("~UserCreateScene");

}

bool UserCreateScene::init() {

	if (!Layer::init())
	{
		return false;
	}
	
	rootNode = CSLoader::createNode(PATH + "Create.csb");

	rootNode->setAnchorPoint(Point(0.5, 0.5));
	rootNode->setPosition(Point(_director->getWinSize().width / 2, _director->getWinSize().height / 2));
	addChild(rootNode);
    
    //////
    
	startGame();

	return true;

}



void UserCreateScene::startGame() {

	Logger::getInstance()->logEvent("UserCreateScene", Logger::OPEN, "");
    

	initVariables();
	initAudio();
	initGameObjects();
	fadeIn();
    
    
  
    
}

void UserCreateScene::initVariables() {

	dataProvider = DataProvider::getInstance();
 

}

void UserCreateScene::initAudio() {

	simpleAudioEngine = SimpleAudioEngine::getInstance();
    simpleAudioEngine->playBackgroundMusic("common/audio/bg/MAIN_THEME.mp3", true);
	
}

void UserCreateScene::initGameObjects() {
    disableClicks = false;
    addButtons();
    
}

void UserCreateScene::afterCaptured(bool succeed, const std::string& outputFile)
{
    if (succeed)
    {
         log("Capture screen ok!");
        // show screenshot
        /*
        auto sp = Sprite::create(outputFile);
        addChild(sp, 0, childName);
        Size s = Director::getInstance()->getWinSize();
        sp->setPosition(s.width / 2, s.height / 2);
        sp->setScale(0.25);
        */
        
        CCLOG("output file = %s", outputFile.c_str());
        CocosCamera::getInstance()->saveImage(outputFile);

    }
    else
    {
        log("Capture screen failed.");
      
    }
}
/*
void UserCreateScene::captureCallback(Ref* pSender)
{
    CocosCamera::getInstance()->openCamera("snapshot.png", 1040, 780, CC_CALLBACK_2(UserCreateScene::cameraResponse, this));
}
*/
void UserCreateScene::cameraResponse(bool isError, std::string imagePath) {
    CCLOG("sono in cameraResponse...");
    if (isError)
        CCLOG("Error capturing photo");
    else {
        CCLOG("cameraResponse called... %s from UserCreateScene", imagePath.c_str());
        
        photoPath = imagePath;
        
        Sprite *sp = Sprite::create(imagePath);
        // rootNode->getChildByName("photoContainer")->addChild(sp);
    
        rootNode->getChildByName("wind_photo")->getChildByName("black_bg")->getChildByName("photoHere")->addChild(sp);
        
        
        // hide shootNode1
        auto shootNode1 = static_cast<Node*>(rootNode->getChildByName("shootBtn1"));
        shootNode1->setVisible(false);
        
        // show buttons to shoot again or to go on
        
        auto shootNode2 = static_cast<Node*>(rootNode->getChildByName("shootBtn2"));
        shootNode2->setVisible(true);
        auto goOnNode = static_cast<Node*>(rootNode->getChildByName("goOnBtn"));
        goOnNode->setVisible(true);
        
        goOnNode->stopAllActions();
        cocostudio::timeline::ActionTimeline* goOnTimeline = CSLoader::createTimeline(PATH+"csd/goOnBtn.csb");
        goOnNode->runAction(goOnTimeline);
        goOnTimeline->play("loop", true);
        
        
    }
}



void UserCreateScene::fadeIn() {
  
}

string UserCreateScene::generateId() {
    
    time_t seconds_past_epoch = time(0);
    string ts =  StringUtility::toString(seconds_past_epoch);
    CCLOG("ts generateId : %s", ts.c_str());
    return ts;
    
    
    string idToReturn = Logger::getInstance()->getTimestamp("all");
    std::replace( idToReturn.begin(), idToReturn.end(), '/', '_'); // replace all '/' to '_'
    std::replace( idToReturn.begin(), idToReturn.end(), ' ', '_'); // replace all ' ' to '_'
    return idToReturn;
}


void UserCreateScene::addButtons() {
    
    auto shootNode1 = static_cast<Node*>(rootNode->getChildByName("shootBtn1"));
    cocostudio::timeline::ActionTimeline* shoot1Timeline = CSLoader::createTimeline(PATH+"csd/shootBtn.csb");
    shootNode1->runAction(shoot1Timeline);
    shoot1Timeline->play("loop", true);
    
    shootBtn1 = static_cast< cocos2d::ui::Button*>(rootNode->getChildByName("shootBtn1")->getChildByName("button"));
    shootBtn1->addClickEventListener([=](Ref *){
        if (disableClicks) return;
        currentId = generateId();        
        CocosCamera::getInstance()->openCamera(currentId+".png", 1040, 780, CC_CALLBACK_2(UserCreateScene::cameraResponse, this));
    });
    
    goOnBtn = static_cast< cocos2d::ui::Button*>(rootNode->getChildByName("goOnBtn")->getChildByName("button"));
    goOnBtn->addClickEventListener([=](Ref *){
        if (disableClicks) return;
        CCLOG("Pressed goOnBtn");
        
        //CCLOG("photoPath = %s", photoPath.c_str());
        disableClicks = true;
        rootNode->getChildByName("loading")->setVisible(true);
        
        /*
        auto loadingAnim = static_cast<Node*>(rootNode->getChildByName("loadingAnim"));
        loadingAnim->setVisible(true);
        cocostudio::timeline::ActionTimeline* loadingAnimTimeline = CSLoader::createTimeline(PATH+"csd/playBtn.csb");
        loadingAnim->runAction(loadingAnimTimeline);
        loadingAnimTimeline->play("play_pop", true);
        */
       ///
        runAction(Sequence::create(DelayTime::create(0.1), CallFunc::create([&](){
            
            dataProvider->createUser(currentId, photoPath);
            Logger::getInstance()->logEvent("UserCreateScene", Logger::CLOSE, "");
            _director->replaceScene(TransitionFade::create(TRANSITION_TIME, HomeGame::createScene(), TRANSITION_COLOR));
            
        }),  nullptr));
        
        ///
        
        
        
    });
    
    
    
    shootBtn2 = static_cast< cocos2d::ui::Button*>(rootNode->getChildByName("shootBtn2")->getChildByName("button"));
    shootBtn2->addClickEventListener([=](Ref *){
        if (disableClicks) return;
        currentId = generateId();
        CocosCamera::getInstance()->openCamera(currentId+".png", 1040, 780, CC_CALLBACK_2(UserCreateScene::cameraResponse, this));
    });
    
    auto shootNode2 = static_cast<Node*>(rootNode->getChildByName("shootBtn2"));
    shootNode2->setVisible(false);
    auto goOnNode = static_cast<Node*>(rootNode->getChildByName("goOnBtn"));
    goOnNode->setVisible(false);
    
}



