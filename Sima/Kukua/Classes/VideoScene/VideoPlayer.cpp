#include "VideoPlayer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <vector>
#include "SimpleAudioEngine.h" 
#include "../WatchmanScene/WatchmanScene.h"
#include <string>

#include "../Utils/StringUtility.h"

#include "../Utils/Data/Logger.h"


USING_NS_CC;

using namespace cocostudio::timeline;
using namespace std;



VideoPlayer::VideoPlayer(Node &parentNode, string videoName)
{
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
    this->parentNode = &parentNode;
    
    videoPlayer = cocos2d::experimental::ui::VideoPlayer::create();
    videoPlayer->setAnchorPoint(Point(0.5, 0.5));
    
    parentNode.addChild(videoPlayer);
    videoPlayer->setPosition(Point(cocos2d::Director::getInstance()->getWinSize().width / 2, cocos2d::Director::getInstance()->getWinSize().height / 2));
    
    videoPlayer->setContentSize(Size( Director::getInstance()->getWinSize().width ,Director::getInstance()->getWinSize().height ));
    videoPlayer->setKeepAspectRatioEnabled(true);
    
    videoPlayer->setFullScreenEnabled(true);
    
    videoPlayer->setFileName(videoName); // setFileName("Videos/test.mp4");
   
    
#endif
    
}


VideoPlayer::~VideoPlayer() {
    
}


void VideoPlayer::play(std::function<void()> callback) {

    callbackFunc = callback;
    
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS

    if (callback != nullptr) {
        videoPlayer->addEventListener(CC_CALLBACK_2(VideoPlayer::videoEventCallback, this, callback));
    }
    
    if (videoPlayer)
    {
        videoPlayer->play();
        
        
        // add skip button
        cocos2d::ui::Button *skipBtn = cocos2d::ui::Button::create("common/images/skip.png", "common/images/skip.png", "common/images/skip.png");
        skipBtn->setPosition(Vec2(cocos2d::Director::getInstance()->getWinSize().width - 10 - skipBtn->getBoundingBox().size.width/2 , 10 + skipBtn->getBoundingBox().size.height/2 ));
        parentNode->addChild(skipBtn);
        skipBtn->setOpacity(0);
        skipBtn->runAction(FadeIn::create(0.4));
        skipBtn->addClickEventListener([=](Ref *){
            skipBtn->setTouchEnabled(false);
            skipBtn->runAction(FadeOut::create(0.4));
            CCLOG("skipBtn Pressed");
            if (callback != nullptr) {
                callback();
            }
        });
        
        
    }

#else

	if (callback != nullptr) {
		callback();
	}

#endif

}


#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS

void VideoPlayer::videoEventCallback(cocos2d::Ref *sender, cocos2d::experimental::ui::VideoPlayer::EventType eventType, std::function<void()> callback)
{
    switch(eventType) {
        case experimental::ui::VideoPlayer::EventType::COMPLETED:
            // CCLOG("video finito");
            callback();
            break;
    }
}

#endif
