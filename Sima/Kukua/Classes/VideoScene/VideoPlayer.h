#ifndef __VIDEO_PLAYER_H__
#define __VIDEO_PLAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"
#include "../Utils/GameObject.h"

using namespace std;

class VideoPlayer
{
public:
    VideoPlayer(Node &parentNode, std::string videoName);
    virtual ~VideoPlayer();
    void play(std::function<void()> callback = nullptr);
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    cocos2d::experimental::ui::VideoPlayer *videoPlayer;
#endif
    
private:
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    void videoEventCallback(cocos2d::Ref *sender, cocos2d::experimental::ui::VideoPlayer::EventType eventType, std::function<void()> callback);
    Node *parentNode;
#endif
    std::function<void()> callbackFunc;
};

#endif