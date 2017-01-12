#include "HomeTatu.h"
#include "HomeGame.h"


HomeTatu::HomeTatu(Node& parentNode, EventDispatcher* eventDispatcher)
	: TouchableGameObject(parentNode, Vec2::ZERO, HomeGame::PATH + "Tatu.csb", "RootBone/Collider", eventDispatcher),
	interacting(false)
{

}

HomeTatu::~HomeTatu() {

}

bool HomeTatu::onTouchBegan(Touch* touch, Event* event) {

	if (TouchableGameObject::onTouchBegan(touch, event)) {

		if (!interacting) {

			interacting = true;
            SimpleAudioEngine::getInstance()->playEffect("Home/audio/tatu_home.mp3");
			play("Tatu_tap", [&]() {

				interacting = false;
				play("Tatu_standing", nullptr, true);
                getActionTimeline()->clearLastFrameCallFunc();
			});

		}

	}

	return false;

}
