#include "Gazelle.h"
#include "HomeGame.h"


Gazelle::Gazelle(Node& parentNode, string nodeName, EventDispatcher* eventDispatcher)
	: TouchableGameObject(parentNode, nodeName, HomeGame::PATH + "Gazelle.csb", "RootBone/Collider", eventDispatcher),
	interacting(false)
{
	simpleAudioEngine = SimpleAudioEngine::getInstance();
	simpleAudioEngine->preloadEffect("Home/audio/impala.mp3");

}

Gazelle::~Gazelle() {

}

bool Gazelle::onTouchBegan(Touch* touch, Event* event) {

	if (TouchableGameObject::onTouchBegan(touch, event)) {

		if (!interacting) {

			interacting = true;
			simpleAudioEngine->playEffect("Home/audio/impala.mp3");
			play("interact", [&]() {
				interacting = false;
				play("standing", nullptr, true);
                getActionTimeline()->clearLastFrameCallFunc();
			});

		}

	}

	return false;

}