#include "AppDelegate.h"
#include "Home/HomeGame.h"
#include "WatchmanScene/WatchmanScene.h"
#include "Utils/Data/Logger.h"
#include "MapScene/MapScene.h"
#include "PhotoScene/PhotoScene.h"
#include "UserScene/UserCreateScene.h"
#include "UserScene/UserSelectScene.h"
#include "VideoScene/VideoScene.h"
#include "AppMacros.h"
#include "Utils/NativeBridge/NativeBridge.h"
#include "MapScene/MapScene.h"
#include "LoadScene/Unzipper.h"


USING_NS_CC;

const Size AppDelegate::FRAME_SIZE(1280, 800);

AppDelegate::AppDelegate() {
    CCLOG("AppDelegate -- AppDelegate");
}

AppDelegate::~AppDelegate() 
{
    CCLOG("AppDelegate -- ~AppDelegate");
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    CCLOG("AppDelegate -- initGLContextAttrs");
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    
    CCLOG("AppDelegate -- applicationDidFinishLaunching");
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::createWithRect("Kukua", Rect(0, 0, 1280, 800));
        director->setOpenGLView(glview);
    }

    director->getOpenGLView()->setDesignResolutionSize(1280, 800, ResolutionPolicy::FIXED_WIDTH);

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    FileUtils::getInstance()->addSearchPath("res");
    FileUtils::getInstance()->addSearchPath(FileUtils::getInstance()->getWritablePath());
    
    
    #if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID    
         NativeBridge::getInstance()->createFolder("Kukua");
         NativeBridge::getInstance()->createFolder("Kukua/Logs");
        
    #endif
    
    srand( static_cast<unsigned int>(time(NULL)));

    DataProvider::getInstance()->init();
  
    
    if (TEST_ENABLED) {        
        
        auto scene = HomeGame::createScene(); // ok per test
        //auto scene = EmotionalGame::createScene();
        director->runWithScene(scene);
        return true;
    }
    
    
    cocos2d::UserDefault *userDef=cocos2d::UserDefault::getInstance();
    
    bool zipDownloaded = userDef->getBoolForKey("zipDownloaded", false);
    
    if (zipDownloaded == false) {
        auto scene = Unzipper::createScene();
        director->runWithScene(scene);
        return true;
    }
    
    string userId = userDef->getStringForKey("CURRENT_USER_ID", "noUsers");
    if (userId == "noUsers") {
        director->runWithScene( UserCreateScene::createScene() );
    } else if (userId == "loggedOut") {
        director->runWithScene( UserSelectScene::createScene() );
    } else {
        director->runWithScene( HomeGame::createScene() );
    }
    
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCLOG("AppDelegate -- applicationDidEnterBackground");
    Director::getInstance()->stopAnimation();
    Logger::getInstance()->logEvent("APP", "Background", "");
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCLOG("AppDelegate -- applicationWillEnterForeground");
    Director::getInstance()->startAnimation();
    
    UserDefault *def=UserDefault::getInstance();
    int sessionNum = def->getIntegerForKey("Session", 0);
    sessionNum++;
    def->setIntegerForKey("Session", sessionNum);
    def->flush();
    
    if (sessionNum != 1) {
        Logger::getInstance()->logSession();
    }
    
    Logger::getInstance()->logEvent("APP", "Foreground", "");
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    
}
