#include "PlayButton.h"
#include "HomeGame.h"
#include "../VideoScene/VideoScene.h"
#include "../MapScene/MapScene.h"
#include "../AppMacros.h"

PlayButton::PlayButton(Node& parentNode, string nodeName, EventDispatcher* eventDispatcher, HomeGame* homeGame)
	: TouchableGameObject(parentNode, nodeName, HomeGame::PATH + "PlayButton.csb", "RootBone/Collider", eventDispatcher),
	homeGame(homeGame),
	interacting(false)
{
	simpleAudioEngine = SimpleAudioEngine::getInstance();
	
	simpleAudioEngine->preloadEffect("Home/audio/playHome.mp3");
	
}

PlayButton::~PlayButton() {

}

bool PlayButton::onTouchBegan(Touch* touch, Event* event) {

	if (TouchableGameObject::onTouchBegan(touch, event)) {

		if (!interacting) {

			interacting = true;
			homeGame->disableTouch();
			simpleAudioEngine->playEffect("Home/audio/playHome.mp3");
			play("Play_B", [&]() {
                simpleAudioEngine->stopBackgroundMusic();
                Logger::getInstance()->logEvent("Home", Logger::CLOSE, "");
				//VideoScene::VIDEO_PATH = "Videos/video1.mp4";
				//VideoScene::NEXT_SCENE_CREATE_SCENE = MapScene::createScene;
				//VideoScene::NEXT_SCENE_CREATE_SCENE = MapSceneOld::createScene;
                Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, MapScene::createScene(), TRANSITION_COLOR));
                getActionTimeline()->clearLastFrameCallFunc();
			});

		}

	}

	return false;

}
