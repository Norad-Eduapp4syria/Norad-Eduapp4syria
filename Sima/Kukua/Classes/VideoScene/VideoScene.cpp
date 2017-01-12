#include "VideoScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <vector>
#include "SimpleAudioEngine.h"
#include "../WatchmanScene/WatchmanScene.h"
#include "VideoPlayer.h"
#include <string>
#include "../Utils/StringUtility.h"
#include "../Utils/Data/Logger.h"
#include "../AppMacros.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace std;


string VideoScene::VIDEO_PATH = "";
cocos2d::Scene* (*VideoScene::NEXT_SCENE_CREATE_SCENE)() = nullptr;

Scene* VideoScene::createScene() {

    // 'scene' is an autorelease object
	auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = VideoScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;

}

VideoScene::~VideoScene() {
    
    delete videoPlayer;

}

// on "init" you need to initialize your instance
bool VideoScene::init() {

    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	//videoPlayer = new VideoPlayer(*this, "Videos/test.mp4");
    videoPlayer = new VideoPlayer(*this, VIDEO_PATH);

    
    Logger::getInstance()->logEvent("Video", Logger::OPEN, "");
    
	runAction(
		Sequence::createWithTwoActions(
			DelayTime::create(2.f),
			CallFunc::create(
				[&]() {
					videoPlayer->play([=]() {
						videoEnded();
					});
				})
			)
		);
    /*videoPlayer->play([=]() {
		videoEnded();
	});*/
    
    return true;

}

void VideoScene::videoEnded() {

    Logger::getInstance()->logEvent("Video", Logger::CLOSE, "");
	assert(NEXT_SCENE_CREATE_SCENE != nullptr);

	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, NEXT_SCENE_CREATE_SCENE(), TRANSITION_COLOR));

	VIDEO_PATH = "";
	NEXT_SCENE_CREATE_SCENE = nullptr;

}

