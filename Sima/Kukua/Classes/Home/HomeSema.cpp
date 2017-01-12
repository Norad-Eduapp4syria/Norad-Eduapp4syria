#include "HomeSema.h"
#include "HomeGame.h"


HomeSema::HomeSema(Node& parentNode, Vec2 pos, EventDispatcher* eventDispatcher)
	: TouchableGameObject(parentNode, pos, HomeGame::PATH + "Sema_standup.csb", "Collider", eventDispatcher),
	interacting(false)
{

	simpleAudioEngine = SimpleAudioEngine::getInstance();
	simpleAudioEngine->preloadEffect("Home/audio/Welcome.mp3");
    
	mouth = new GameObject(*(node->getChildByName("sima_master")->getChildByName("mouth_close")->getChildByName("Node")), Vec2::ZERO, HomeGame::PATH + "SemaMouth_new.csb");
	baloon = new GameObject(*(node->getChildByName("baloon_sema")->getChildByName("Node")), Vec2::ZERO, HomeGame::PATH + "SemaBaloon.csb");
	mouth->setVisible(false);
	baloon->setVisible(false);
    
}

HomeSema::~HomeSema() {

	delete mouth;
	delete baloon;

}

bool HomeSema::onTouchBegan(Touch* touch, Event* event) {

	if (TouchableGameObject::onTouchBegan(touch, event)) {

		if (!interacting) {

			interacting = true;

			mouth->setVisible(true);
			baloon->setVisible(true);
			simpleAudioEngine->playEffect("Home/audio/Welcome.mp3");
			mouth->play("animation0");
			baloon->play("Balloon_sema", [&]() {
				interacting = false;
				mouth->setVisible(false);
				baloon->setVisible(false);
                baloon->getActionTimeline()->clearLastFrameCallFunc();
			});

		}

	}

	return false;

}
