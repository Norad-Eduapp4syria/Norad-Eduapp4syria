#include "Giraffe.h"
#include "HomeGame.h"


Giraffe::Giraffe(Node& parentNode, string nodeName, EventDispatcher* eventDispatcher)
	: TouchableGameObject(parentNode, nodeName, HomeGame::PATH + "Giraffe.csb", "RootBone/Collider", eventDispatcher),
	interacting(false)
{
	simpleAudioEngine = SimpleAudioEngine::getInstance();
	simpleAudioEngine->preloadEffect("Home/audio/giraffa.mp3");

}

Giraffe::~Giraffe() {

}

bool Giraffe::onTouchBegan(Touch* touch, Event* event) {

	if (TouchableGameObject::onTouchBegan(touch, event)) {

		if (!interacting) {

			interacting = true;
			simpleAudioEngine->playEffect("Home/audio/giraffa.mp3");
			play("interact", [&]() {
				interacting = false;
				play("standing", nullptr, true);
                getActionTimeline()->clearLastFrameCallFunc();
			});

		}

	}

	return false;

}