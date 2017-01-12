#include "Hen.h"
#include "HomeGame.h"

const int Hen::STANDING_LOOP = 6;
int Hen::LAST_STANDING_OFFSET = 0;

Hen::Hen(Node& parentNode, string nodeName, EventDispatcher* eventDispatcher)
	: TouchableGameObject(parentNode, nodeName, HomeGame::PATH + "Hen.csb", "RootBone/Collider", eventDispatcher),
	standingOffset(LAST_STANDING_OFFSET = (LAST_STANDING_OFFSET + 2) % STANDING_LOOP),
	interacting(false)
{
	simpleAudioEngine = SimpleAudioEngine::getInstance();
	simpleAudioEngine->preloadEffect("Home/audio/gallina.mp3");

	standingAction = RepeatForever::create(
		Sequence::create(
			DelayTime::create(standingOffset),
			CallFunc::create(
				[&]() {
					play("standing");
				}),
			DelayTime::create(STANDING_LOOP - standingOffset),
			nullptr
			)
		);
	/*runningAction = RepeatForever::create(
		Sequence::create(
			DelayTime::create(6.f),
			CallFunc::create(
				[&]() {
					play("standing");
				}),
			nullptr
			)
		);*/
	node->runAction(standingAction);
	//simpleAudioEngine->preloadEffect("Home/audio/gallina.mp3");
}

Hen::~Hen() {

}

bool Hen::onTouchBegan(Touch* touch, Event* event) {

	if (TouchableGameObject::onTouchBegan(touch, event)) {

		if (!interacting) {

			node->stopAction(standingAction);
			//runningAction = standingAction->clone();
			//node->pause();
			interacting = true;
			simpleAudioEngine->playEffect("Home/audio/gallina.mp3");
			play("interact", [&]() {
				interacting = false;
				//play("standing", nullptr, true);
				/*play(
					RepeatForever::create(
						Sequence::create(
							DelayTime::create(6.f),
							CallFunc::create(
								[&]() {
									//node->resume();
									play("standing");
								}),
							nullptr
						)
					)
				);*/
				standingAction = RepeatForever::create(
					Sequence::create(
						DelayTime::create(standingOffset),
						CallFunc::create(
							[&]() {
								play("standing");
							}),
						DelayTime::create(STANDING_LOOP - standingOffset),
						nullptr
					)
				);
				node->runAction(standingAction);
                getActionTimeline()->clearLastFrameCallFunc();
			});

		}

	}

	return false;

}