#ifndef __VIDEO_SCENE_H__
#define __VIDEO_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"
#include "VideoPlayer.h"

class VideoScene : public cocos2d::Layer {

public:
	static string VIDEO_PATH;
	static cocos2d::Scene* (*NEXT_SCENE_CREATE_SCENE)();					// Example usage: VideoScene::NEXT_SCENE_CREATE_SCENE = WatchmanScene::createScene;

    static cocos2d::Scene* createScene();
    virtual ~VideoScene();
    virtual bool init();
    
private:
    VideoPlayer* videoPlayer;
    void videoEnded();
    
    CREATE_FUNC(VideoScene);

};

#endif
