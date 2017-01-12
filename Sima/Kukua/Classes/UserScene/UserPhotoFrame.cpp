#include "UserPhotoFrame.h"
#include "../Utils/StringUtility.h"
#include "../AppMacros.h"
#include "../Home/HomeGame.h"

UserPhotoFrame::UserPhotoFrame(Node& parentNode, const Vec2& position, EventDispatcher* eventDispatcher, string photoPath, int index, string userId)
	: TouchableGameObject(parentNode, position, "UserScene/csd/userBtn.csb", "hitArea", eventDispatcher)
{

	//CCLOG("UserPhotoFrame()");
    this->index = index;
    
    if (photoPath != "") {
        
        this->userId = userId;
        
        setTouchable(true);
        
        Sprite *sp = Sprite::create(photoPath);
        
        
        // add photo
        getNode().getChildByName("user_master")->getChildByName("photoBone")->getChildByName("photoHere")->addChild(sp);
        
        
        addPlayButton();
        playNode->setVisible(false);
       
        
    } else {
       // CCLOG("error: no photoPath");
    }
    
    
    
}


void UserPhotoFrame::addPlayButton() {
   
    playNode = CSLoader::createNode("UserScene/csd/playBtn.csb");
    playNodeTimeline = CSLoader::createTimeline("UserScene/csd/playBtn.csb");
    playNode->runAction(playNodeTimeline);
    
    auto playHolder = static_cast< cocos2d::ui::Button*>(getNode().getChildByName("user_master")->getChildByName("play_select")->getChildByName("Node"));
    playHolder->addChild(playNode);
    
    
    
    auto btnPlay = static_cast< cocos2d::ui::Button*>(playNode->getChildByName("playBtn")->getChildByName("button"));
    btnPlay->addClickEventListener([=](Ref *){
        CCLOG("pressed btnPlay.. index = %d", index);
        playNodeTimeline->play("play_tap", false);
        setTouchable(false);
        
        
        
        cocos2d::UserDefault *userDef=cocos2d::UserDefault::getInstance();
        userDef->setStringForKey("CURRENT_USER_ID", userId);
        userDef->flush();
        
        
        Logger::getInstance()->logEvent("UserSelectScene", Logger::CLOSE, "");
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, HomeGame::createScene(), TRANSITION_COLOR));
    });
}


void UserPhotoFrame::hidePlayButton() {
    
    if (playNode->isVisible()) {
        playNodeTimeline->play("play_off", false);
        playNodeTimeline->setLastFrameCallFunc([=]() {
            playNode->setVisible(false);
            playNodeTimeline->clearLastFrameCallFunc();
        });
    }
}


UserPhotoFrame::~UserPhotoFrame() {

	// CCLOG("~UserPhotoFrame()");
    setTouchable(false);

}

bool UserPhotoFrame::onTouchBegan(Touch* touch, Event* event) {

	if (TouchableGameObject::onTouchBegan(touch, event)) {
       
		//setTouchable(false);
        
        EventCustom event("UserPhotoFrameTouched");
        eventDispatcher->dispatchEvent(&event);
        
        if (playNode->isVisible() == false) {
            playNode->setVisible(true);
            playNodeTimeline->play("play_pop", false);
        }
        
	}

	return false;

}
