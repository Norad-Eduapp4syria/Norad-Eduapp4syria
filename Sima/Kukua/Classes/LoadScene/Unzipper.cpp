#include "Unzipper.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "cocos-ext.h"
#include "../Utils/NativeBridge/NativeBridge.h"
#include "../AppMacros.h"

#include "../UserScene/UserCreateScene.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "iosUnzip.h"
#endif

USING_NS_CC;

using namespace cocostudio::timeline;




Scene* Unzipper::createScene()
{
	//unzFile file;

    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Unzipper::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Unzipper::init()
{
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    PATH = "LoadScene/";
    
    
    rootNode = CSLoader::createNode(PATH+"MainScene.csb");
    
    
    /*

    auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

    downloadlabel = Label::createWithTTF("Downloading ...", "common/fonts/Century Gothic Bold.ttf", 30);
	downloadlabel->setColor(Color3B(100, 100, 100));
	this->addChild(downloadlabel, 1);
	downloadlabel->setPosition(Vec2(origin.x + 280, origin.y + visibleSize.height - downloadlabel->getContentSize().height - 50));
    */
    
    addChild(rootNode);

	// Sema timeline	
	downloadNode = rootNode->getChildByName("Loading");
	downloadTimeLine = CSLoader::createTimeline(PATH + "Loading.csb");
	chargeLen = downloadTimeLine->getDuration();
	downloadNode->runAction(downloadTimeLine);
	
	Download();

    return true;
}

void Unzipper::Download()
{
    
	string url = "http://www.melazeta.eu/kukua/KukuaSyria.zip";

	//zipFile = "/sdcard/unzipMe.zip";
	zipFile = FileUtils::getInstance()->getWritablePath() + "KukuaSyria.zip";
	
	CCLOG("provo a scaricare file in %s", zipFile.c_str());

	network::Downloader *downloader = new (nothrow) network::Downloader();
	downloadTimeLine->play("loading", false);
	downloadTimeLine->pause();

	downloader->onTaskProgress = ([&](const network::DownloadTask& task, int64_t bytesReceived, int64_t totalBytesReceived, int64_t totalBytesExpected) {
		
		//downloading progress

		float percent = ((float)totalBytesReceived / (float)totalBytesExpected) * 100;
		stringstream ss;
		ss << (int)percent;

		//Since loader frames are 81, a conversion is needed
		int frame = 81 * percent / 100;
		
		if (bytesReceived > 0)
			downloadTimeLine->gotoFrameAndPause(frame);

		//downloadlabel->setString("Downloading : " + ss.str() + string(" %"));

        if (percent == 100) {
            CCLOG("Unzipping ...");
			// downloadlabel->setString("Unzipping ... ");
        }
	});

	downloader->onFileTaskSuccess = ([&](const network::DownloadTask& task) {
		//file downloaded, do what you need next

		CCLOG("Downloaded!!");
		// downloadlabel->setString("Downloaded");
        //
		Unzip();
	});

	downloader->onTaskError = ([&](const network::DownloadTask& task, int errorCode, int errorCodeInternal, const std::string& errorStr) {
		//file downloading error
        CCLOG("Download >> Error");
        Node* errorNode = CSLoader::createNode(PATH + "Error.csb");
        auto errorTimeLine = CSLoader::createTimeline(PATH + "Error.csb");
        errorNode->runAction(errorTimeLine);
        rootNode->addChild(errorNode, 10);
        errorNode->setPosition(640,400);
        errorTimeLine->play("pop_alert", false);
	});

	downloader->createDownloadFileTask(url, zipFile);
}

void Unzipper::Unzip()
{
    CCLOG("Unzipping ...");
	//downloadlabel->setString("Unzipping ... ");
    
    auto timeNode = rootNode->getChildByName("Time");
    auto timeTimeLine = CSLoader::createTimeline(PATH + "Time.csb");
    timeNode->runAction(timeTimeLine);
    timeTimeLine->play("loop", true);
    timeNode->setVisible(true);
  
    
	//NativeBridge::getInstance()->unZipArchiveToFolder(zipFile, FileUtils::getInstance()->getWritablePath());
    
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        NativeBridge::getInstance()->unZipArchiveToFolder(zipFile, FileUtils::getInstance()->getWritablePath());
    #endif
        
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        CCLOG("Invoco unzipper ...");
        iosUnzip unz;
        unz.unZipArchiveToFolder(zipFile, FileUtils::getInstance()->getWritablePath());
    #endif
    

	//downloadlabel->setString("Unzipped");
    CCLOG("Unzipped!");
    
    
    openNextScene();
 
    FileUtils::getInstance()->removeFile(zipFile); // delete zip file

}

void Unzipper::openNextScene()
{
    cocos2d::UserDefault *userDef=cocos2d::UserDefault::getInstance();
    userDef->setBoolForKey("zipDownloaded", true);
    
    _director->replaceScene(TransitionFade::create(TRANSITION_TIME, UserCreateScene::createScene(), TRANSITION_COLOR));
}

