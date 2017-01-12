#include "HomeElephant.h"
#include "HomeGame.h"


HomeElephant::HomeElephant(Node& parentNode, string nodeName, EventDispatcher* eventDispatcher)
	: TouchableGameObject(parentNode, nodeName, HomeGame::PATH + "Elephant.csb", "RootBone/Collider", eventDispatcher),
	interacting(false)
{
	simpleAudioEngine = SimpleAudioEngine::getInstance();
	simpleAudioEngine->preloadEffect("Home/audio/elephaLow.mp3");

}

HomeElephant::~HomeElephant() {

}

bool HomeElephant::onTouchBegan(Touch* touch, Event* event) {

	if (TouchableGameObject::onTouchBegan(touch, event)) {

		if (!interacting) {

			interacting = true;
			simpleAudioEngine->playEffect("Home/audio/elephaLow.mp3");
			play("interact", [&]() {
				interacting = false;
				play("standing", nullptr, true);
                getActionTimeline()->clearLastFrameCallFunc();
			});

		}

	}

	return false;

}