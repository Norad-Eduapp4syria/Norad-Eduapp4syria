#include "WatchmanSceneGrandpa.h"
#include "WatchmanScene.h"
#include "../Utils/StringUtility.h"
#include "../Utils/Data/DataProvider.h"

WatchmanSceneGrandpa::WatchmanSceneGrandpa(Node& parentNode, const Vec2& localPosition, EventDispatcher* eventDispatcher, WatchmanScene* watchmanScene, int skin, string csbPath)
	: GameObject(parentNode, localPosition, csbPath)
{

    simpleAudioEngine = SimpleAudioEngine::getInstance();
}

WatchmanSceneGrandpa::~WatchmanSceneGrandpa() {

}

void WatchmanSceneGrandpa::playGoodReaction() {
    
    play("talk", [&]() {
        play("standing", nullptr, true);
        getActionTimeline()->clearLastFrameCallFunc();
    });
    
    
    int random = 1+ rand() % 3;
    
    string gender = "man";
    if ( (DataProvider::getInstance()->getCurrentEpisode()==3)  || (DataProvider::getInstance()->getCurrentEpisode()==9) ) gender = "woman";
    
    if (random == 1) simpleAudioEngine->playEffect((WatchmanScene::PATH + "Audio/main/Granpa/"+gender+"/Feedback_positivi/Granpa_greatjob.mp3").c_str());
    else if (random == 2) simpleAudioEngine->playEffect((WatchmanScene::PATH + "Audio/main/Granpa/"+gender+"/Feedback_positivi/Granpa_wonderfull.mp3").c_str());
    else simpleAudioEngine->playEffect((WatchmanScene::PATH + "Audio/main/Granpa/"+gender+"/Feedback_positivi/Granpa_welldone.mp3").c_str());
}

void WatchmanSceneGrandpa::playBadReaction() {
  
    play("talk", [&]() {
        play("standing", nullptr, true);
        getActionTimeline()->clearLastFrameCallFunc();
    });

    
    string gender = "man";
    if ( (DataProvider::getInstance()->getCurrentEpisode()==3)  || (DataProvider::getInstance()->getCurrentEpisode()==9) ) gender = "woman";
    
    int random = 1+ rand() % 2;

    if (random == 1) simpleAudioEngine->playEffect((WatchmanScene::PATH + "Audio/main/Granpa/"+gender+"/Feedback_negativi/Granpa_youcandobetter.mp3").c_str());
    else simpleAudioEngine->playEffect((WatchmanScene::PATH + "Audio/main/Granpa/"+gender+"/Feedback_negativi/Granpa_tryagain.mp3").c_str());
}
