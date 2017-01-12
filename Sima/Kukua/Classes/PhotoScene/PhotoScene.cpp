#include "PhotoScene.h"
#include "../Utils/Data/DataProvider.h"
#include "../Utils/Data/Logger.h"
#include "../Home/HomeGame.h"
#include "../WatchmanScene/WatchmanScene.h"
#include "../Utils/CocosCamera/CocosCamera.h"
#include "../Utils/StringUtility.h"
#include "../AppMacros.h"
#include "../MapScene/MapScene.h"


const bool PhotoScene::ENABLE_TOUCH = true;								// Used to disable tutorial on first touch and manage general touch events
const string PhotoScene::PATH = "PhotoScene/";								// Resources' subfolder path for this game

Scene* PhotoScene::createScene() {

	// 'scene' is an autorelease object
	Scene* scene = Scene::create();

	// 'layer' is an autorelease object			 
	auto layer = PhotoScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;

}

PhotoScene::~PhotoScene() {

	// CCLOG("~PhotoScene");
    delete character1;
    delete character2;
    delete character3;
    delete character4;

}

bool PhotoScene::init() {

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



void PhotoScene::startGame() {

	Logger::getInstance()->logEvent("PhotoScene", Logger::OPEN, "");
    

	initVariables();
	initAudio();
	initGameObjects();
	fadeIn();
    
    
    simpleAudioEngine->playEffect((PATH + "Audio/great_you_can_take_special_photo.mp3").c_str());

    
    rootNode->runAction(
                Sequence::create(
                     DelayTime::create(5.5f),
                     CallFunc::create([&]() {
                        simpleAudioEngine->playEffect((PATH + "Audio/press_button_to_take_photo.mp3").c_str());
                        // hand_photo
                        cocostudio::timeline::ActionTimeline* handPhotoTimeline = CSLoader::createTimeline("PhotoScene/CSD/hand_help_01.csb");
                        handPhoto->runAction(handPhotoTimeline);
                        handPhotoTimeline->play("hand_top", true);
                    
                     }),
                     nullptr
                )
    );
}

void PhotoScene::initVariables() {

	dataProvider = DataProvider::getInstance();
    confirmNode = static_cast<Node*>(rootNode->getChildByName("Ok"));
    confirmNode->setVisible(false);
    
    handPhoto = static_cast<Node*>(rootNode->getChildByName("hand_photo"));
    handDrag = static_cast<Node*>(rootNode->getChildByName("hand_drag"));

}

void PhotoScene::initAudio() {

	simpleAudioEngine = SimpleAudioEngine::getInstance();
    simpleAudioEngine->playBackgroundMusic("common/audio/bg/MAIN_THEME.mp3", true);
	
}

void PhotoScene::initGameObjects() {
    
    addCharacters();
    addButtons();
    
}

void PhotoScene::afterCaptured(bool succeed, const std::string& outputFile)
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
        runConfirmAnimation();
        setUIVisibility(true);
    }
    else
    {
        log("Capture screen failed.");
        setUIVisibility(true);
    }
}

void PhotoScene::captureCallback(Ref* pSender)
{
    CocosCamera::getInstance()->openCamera("snapshot.png", 1040, 780, CC_CALLBACK_2(PhotoScene::cameraResponse, this));
}

void PhotoScene::cameraResponse(bool isError, std::string imagePath) {
    CCLOG("sono in cameraResponse...");
    if (isError)
        CCLOG("Error capturing photo");
    else {
        CCLOG("cameraResponse called... %s from PhotoScene", imagePath.c_str());
        
        
        Sprite *sp = Sprite::create(imagePath);
        rootNode->getChildByName("photoContainer")->addChild(sp);
        
        simpleAudioEngine->playEffect((PATH + "Audio/you_can_add_character_ to_photo.mp3").c_str());
        // hand_drag
        cocostudio::timeline::ActionTimeline* handDragTimeline = CSLoader::createTimeline("PhotoScene/CSD/hand_help_03.csb");
        handDrag->runAction(handDragTimeline);
        handDragTimeline->play("hand_top", true);
    
    }
}



void PhotoScene::fadeIn() {
  
}

void PhotoScene::runConfirmAnimation() {
    
    confirmNode->setVisible(true);
    cocostudio::timeline::ActionTimeline* confirmTimeline = CSLoader::createTimeline("PhotoScene/CSD/Ok.csb");
  
    confirmNode->runAction(confirmTimeline);
    confirmTimeline->play("pull_ok", false);
    
    confirmTimeline->setLastFrameCallFunc([this, confirmTimeline](){
        confirmNode->setVisible(false);
        confirmTimeline->clearLastFrameCallFunc();
    });
    
}

void PhotoScene::addButtons() {
    
    char1Btn = static_cast< cocos2d::ui::Button*>(rootNode->getChildByName("simaBtn"));
    char1Btn->setTag(0);
    char1Btn->addClickEventListener([=](Ref *){
        handDrag->setVisible(false);
        if ( char1Btn->getTag() > 0  ) {
            char1Btn->setTag(0);
            char1Btn->setHighlighted(false);
            character1->deactivate();
        } else {
            char1Btn->setTag(1);
            char1Btn->setHighlighted(true);
            character1->activate();
        }
    });
    
    
    char2Btn = static_cast< cocos2d::ui::Button*>(rootNode->getChildByName("samirBtn"));
    char2Btn->setTag(0);
    char2Btn->addClickEventListener([=](Ref *){
        handDrag->setVisible(false);
        if ( char2Btn->getTag() > 0  ) {
            char2Btn->setTag(0);
            char2Btn->setHighlighted(false);
            character2->deactivate();
        } else {
            char2Btn->setTag(1);
            char2Btn->setHighlighted(true);
            character2->activate();
        }
    });
    
    char3Btn = static_cast< cocos2d::ui::Button*>(rootNode->getChildByName("tatuBtn"));
    char3Btn->setTag(0);
    char3Btn->addClickEventListener([=](Ref *){
        handDrag->setVisible(false);
        if ( char3Btn->getTag() > 0  ) {
            char3Btn->setTag(0);
            char3Btn->setHighlighted(false);
            character3->deactivate();
        } else {
            char3Btn->setTag(1);
            char3Btn->setHighlighted(true);
            character3->activate();
        }
    });
    
    char4Btn = static_cast< cocos2d::ui::Button*>(rootNode->getChildByName("granpaBtn"));
    char4Btn->setTag(0);
    char4Btn->addClickEventListener([=](Ref *){
        handDrag->setVisible(false);
        if ( char4Btn->getTag() > 0  ) {
            char4Btn->setTag(0);
            char4Btn->setHighlighted(false);
            character4->deactivate();
        } else {
            char4Btn->setTag(1);
            char4Btn->setHighlighted(true);
            character4->activate();
        }
    });
    
    ///////
    
    backBtn = static_cast< cocos2d::ui::Button*>(rootNode->getChildByName("backBtn"));
    backBtn->addClickEventListener([=](Ref *){
        
        
        string portalCodeFromHomeButton = string("") + StringUtility::toString( dataProvider->getCurrentDBWatchman()->getEpisode() ) + "-" + StringUtility::toString( dataProvider->getCurrentDBWatchman()->getNumber() ) ;
        CCLOG("PhotoScene! portalCodeFromHomeButton = %s", portalCodeFromHomeButton.c_str());
        dataProvider->setSemaInitialPortalCode(portalCodeFromHomeButton);
        
        Logger::getInstance()->logEvent("PhotoScene", Logger::CLOSE, "");
        dataProvider->setGameCompleted( dataProvider->getCurrentDBKnowledgeBubble()->getPhoneme() , 101 );
        _director->replaceScene(TransitionFade::create(TRANSITION_TIME, MapScene::createScene(), TRANSITION_COLOR));
    });
    
    
    shootBtn = static_cast< cocos2d::ui::Button*>(rootNode->getChildByName("shootBtn"));
    shootBtn->addClickEventListener([=](Ref *){
        handPhoto->setVisible(false);
        CocosCamera::getInstance()->openCamera("snapshot.png", 1040, 780, CC_CALLBACK_2(PhotoScene::cameraResponse, this));
    });
    
    
    saveBtn = static_cast< cocos2d::ui::Button*>(rootNode->getChildByName("saveBtn"));
    saveBtn->addClickEventListener([=](Ref *){
        CCLOG("Pressed saveBtn");
        setUIVisibility(false);
        utils::captureScreen(CC_CALLBACK_2(PhotoScene::afterCaptured, this),"CaptureScreen.png");
    });
    
}


void PhotoScene::setUIVisibility(bool visibility) {
    char1Btn->setVisible(visibility);
    char2Btn->setVisible(visibility);
    char3Btn->setVisible(visibility);
    char4Btn->setVisible(visibility);
    
    backBtn->setVisible(visibility);
    shootBtn->setVisible(visibility);
    saveBtn->setVisible(visibility);
    
}

void PhotoScene::addCharacters() {
    
    character1 = new PhotoCharacter(*rootNode, "char1", "PhotoScene/CSD/char1.csb", "RootBone/dragSprite","RootBone/hitSprite", _eventDispatcher);
    character1->deactivate();
    
    character2 = new PhotoCharacter(*rootNode, "char2", "PhotoScene/CSD/char2.csb", "RootBone/dragSprite","RootBone/hitSprite", _eventDispatcher);
    character2->deactivate();
    
    character3 = new PhotoCharacter(*rootNode, "char3", "PhotoScene/CSD/char3.csb", "RootBone/dragSprite","RootBone/hitSprite", _eventDispatcher);
    character3->deactivate();
    
    character4 = new PhotoCharacter(*rootNode, "char4", "PhotoScene/CSD/char4.csb", "RootBone/dragSprite","RootBone/hitSprite", _eventDispatcher);
    character4->deactivate();
}

