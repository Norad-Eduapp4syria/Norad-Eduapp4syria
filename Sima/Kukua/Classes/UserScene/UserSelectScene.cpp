#include "UserSelectScene.h"
#include "UserCreateScene.h"
#include "UserPhotoFrame.h"
#include "../Utils/Data/DataProvider.h"
#include "../Utils/Data/Logger.h"
#include "../Utils/CocosCamera/CocosCamera.h"
#include "../AppMacros.h"
#include "../Utils/StringUtility.h"
#include <math.h>


const bool UserSelectScene::ENABLE_TOUCH = true;								// Used to disable tutorial on first touch and manage general touch events
const string UserSelectScene::PATH = "UserScene/";								// Resources' subfolder path for this game

Scene* UserSelectScene::createScene() {

	// 'scene' is an autorelease object
	Scene* scene = Scene::create();

	// 'layer' is an autorelease object			 
	auto layer = UserSelectScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;

}

UserSelectScene::~UserSelectScene() {

    
    this->unscheduleUpdate();
    
    _eventDispatcher->removeEventListener(frameTouchedListener);
    
    for (vector<UserPhotoFrame*>::iterator iterator = framesVector.begin(); iterator != framesVector.end(); ++iterator) {
        delete (*iterator);
    }

}

bool UserSelectScene::init() {

	if (!Layer::init())
	{
		return false;
	}
	
	rootNode = CSLoader::createNode(PATH + "Select.csb");

	rootNode->setAnchorPoint(Point(0.5, 0.5));
	rootNode->setPosition(Point(_director->getWinSize().width / 2, _director->getWinSize().height / 2));
	addChild(rootNode);
    
    //////
    
	startGame();

	return true;

}



void UserSelectScene::startGame() {

	Logger::getInstance()->logEvent("UserSelectScene", Logger::OPEN, "");
    

	initVariables();
	initAudio();
	initGameObjects();
	fadeIn();
    
    
    startDetectingSwipe();
    canSwipe = true;
    
 
}

void UserSelectScene::initVariables() {

	dataProvider = DataProvider::getInstance();
    
    cocos2d::UserDefault *userDef=cocos2d::UserDefault::getInstance();
    lastUserId = userDef->getStringForKey("CURRENT_USER_ID", "noUsers");
    userDef->setStringForKey("CURRENT_USER_ID", "loggedOut");
    userDef->flush();
    
    scrollIndex = 1;
    scrollContainer = rootNode->getChildByName("scrollContainer");
    
    idsVector = dataProvider->getAllUsersId();
    /*
    if (test) {
        for (int j = 1; j <= 17; j++) {
            idsVector.push_back("");
        }
    }
    */
    totPages = ceil( (int)idsVector.size() / 8.0 );
    CCLOG("===tot Pages = %d", totPages);
    currentPageElementsCounter = 0;
}

void UserSelectScene::initAudio() {

	simpleAudioEngine = SimpleAudioEngine::getInstance();
    simpleAudioEngine->playBackgroundMusic("common/audio/bg/MAIN_THEME.mp3", true);
	
}

void UserSelectScene::initGameObjects() {
    
    
    frameTouchedListener = EventListenerCustom::create("UserPhotoFrameTouched", [=](EventCustom* event){
        hideAllPlayButtons();
    });
    _eventDispatcher->addEventListenerWithFixedPriority(frameTouchedListener, 1);
    
    
    
    addButtons();
    
}



void UserSelectScene::addButtons() {
    
    createNewBtn = static_cast< cocos2d::ui::Button*>(scrollContainer->getChildByName("createNewBtn")->getChildByName("button"));
    createNewBtn->addClickEventListener([=](Ref *){
        Logger::getInstance()->logEvent("UserSelectScene", Logger::CLOSE, "");
        _director->replaceScene(TransitionFade::create(TRANSITION_TIME, UserCreateScene::createScene(), TRANSITION_COLOR));
    });
    
}


void UserSelectScene::fadeIn() {
    
    
    rootNode->getChildByName("next_dx")->setVisible(false);
    rootNode->getChildByName("next_sx")->setVisible(false);
    
    loadPhotoFramesForPage(1);
    
  
}

void UserSelectScene::loadPhotoFramesForPage(int pageNum) {
    
    CCLOG("loadPhotoFramesForPage: %d", pageNum);
    
    previousPageElementsCounter = currentPageElementsCounter;
    CCLOG("qui previousPageElementsCounter = %d", previousPageElementsCounter);
    int indexStart = 8 * (pageNum-1);
    int indexEnd = indexStart+8;
    if (pageNum == 1) indexEnd--;
    
    if (indexEnd > idsVector.size() ) indexEnd = (int)idsVector.size();

    int i = indexStart;
    if (pageNum == 1) i++;
    currentPageElementsCounter = 0;
    for (int index=indexStart; index<indexEnd; ++index) {
        //CCLOG("index... %d", index);
        i++;
        string userId = idsVector.at(index).c_str();
        string photoPath = DataProvider::getInstance()->getUserPhotoPath(userId);
        
        /*
        if (test) {
            photoPath = "";
        }
        */
        
        auto frame = new UserPhotoFrame(*(scrollContainer), getFramePosition(i), _eventDispatcher, photoPath, i, userId);
        framesVector.push_back(frame);
        currentPageElementsCounter++;
    }
    CCLOG("qui currentPageElementsCounter = %d", currentPageElementsCounter);
    
    if (pageNum < totPages) rootNode->getChildByName("next_dx")->setVisible(true);
    else rootNode->getChildByName("next_dx")->setVisible(false);
   
    if (pageNum > 1 ) rootNode->getChildByName("next_sx")->setVisible(true);
    else rootNode->getChildByName("next_sx")->setVisible(false);
    
}


void UserSelectScene::deletePhotoFramesForPage(int pageNum) {
    
    CCLOG("deletePhotoFramesForPage: %d", pageNum);

    CCLOG("--------previousPageElementsCounter %d", previousPageElementsCounter);
    CCLOG("Prima -  framesVector size %lu", framesVector.size());
    
    for (int index = 0; index < previousPageElementsCounter; ++index) {
        delete framesVector[0];
        framesVector.erase(framesVector.begin());
    }

    CCLOG("Dopo -  framesVector size %lu", framesVector.size());
}

void UserSelectScene::hideAllPlayButtons() {
    for (vector<UserPhotoFrame*>::iterator iterator = framesVector.begin(); iterator != framesVector.end(); ++iterator) {
        (*iterator)->hidePlayButton();
    }
}

Vec2 UserSelectScene::getFramePosition(int index) {
    float page = ceil( index / 8.0 );
 
    int xpos = (page-1) * _director->getWinSize().width;
    
    int posInPage = index - ( (page-1) * 8);
    
    //CCLOG("index = %d, page = %f,  posInPage = %d", index, page, posInPage);
    
    if (posInPage == 1) return Vec2(xpos + 209, 517);
    if (posInPage == 2) return Vec2(xpos + 495, 517);
    if (posInPage == 3) return Vec2(xpos + 782, 517);
    if (posInPage == 4) return Vec2(xpos + 1069, 517);
    if (posInPage == 5) return Vec2(xpos + 209, 242);
    if (posInPage == 6) return Vec2(xpos + 495, 242);
    if (posInPage == 7) return Vec2(xpos + 782, 242);
    if (posInPage == 8) return Vec2(xpos + 1069, 242);
    

    return Vec2::ZERO;
}




//////


/// swipe part

void UserSelectScene::startDetectingSwipe()
{
    CCLOG("startDetectingSwipe");
    auto listener = EventListenerTouchOneByOne::create();
    // listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(UserSelectScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(UserSelectScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(UserSelectScene::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(UserSelectScene::onTouchCancelled, this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    isTouchDown = false;
    
    initialTouchPos[0] = 0;
    initialTouchPos[1] = 0;
    
    this->scheduleUpdate();
}


void UserSelectScene::update(float dt)
{
    if (!canSwipe) return;
    
    if (hasTocalculateTime) gameTime += dt;
    
    
    if (true == isTouchDown)
    {
        float threshold = 15; // - visibleSize.width * 0.1
        
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
            CCLOG("SWIPED DOWN");
            isTouchDown = false;
            
        }
        if (initialTouchPos[1] - currentTouchPos[1] < - visibleSize.width * 0.05)
        {
            CCLOG("SWIPED UP");
            isTouchDown = false;
        }
        
    }
    
}

bool UserSelectScene::onTouchBegan(Touch *touch, Event *event)
{
    CCLOG("-------onTouchBegan");
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



void UserSelectScene::onTouchMoved(Touch *touch, Event *event)
{
    if (!canSwipe) return;
    currentTouchPos[0] = touch->getLocation().x;
    currentTouchPos[1] = touch->getLocation().y;
}

void UserSelectScene::onTouchEnded(Touch *touch, Event *event)
{
    isTouchDown = false;
    
    hasTocalculateTime = false;
    // CCLOG("gameTime = %f", gameTime);
    
    Vec2 direction = Vec2( Vec2(startX,startY), Vec2(touch->getLocation().x, touch->getLocation().y) );
    
    direction.normalize();
    
    
    
    if ((moveLeftGestureDone) && (gameTime<0.5)) {
        CCLOG("ok moveLeftGestureDone!!");
        
        if (scrollIndex < totPages) { // todo cambiare il 4
            scrollIndex++;
            loadPhotoFramesForPage(scrollIndex);
             MoveBy *moveLeft = MoveBy::create(0.5, Point(-_director->getWinSize().width, 0));
            scrollContainer->runAction(Sequence::create(moveLeft, CallFunc::create([&](){
                deletePhotoFramesForPage(scrollIndex-1);
            }),  nullptr));
        }
    } else if ((moveRightGestureDone) && (gameTime<0.5)) {
        CCLOG("ok moveRightGestureDone!!");
        if (scrollIndex > 1) {
            scrollIndex--;
             loadPhotoFramesForPage(scrollIndex);
             MoveBy *moveRight = MoveBy::create(0.5, Point(_director->getWinSize().width, 0));
             scrollContainer->runAction(Sequence::create(moveRight, CallFunc::create([&](){
                 deletePhotoFramesForPage(scrollIndex+1);
            }),  nullptr));
            
            
        }
        
    }
    
    
}

void UserSelectScene::onTouchCancelled(Touch *touch, Event *event)
{
    onTouchEnded(touch, event);
}

// end swipe part


