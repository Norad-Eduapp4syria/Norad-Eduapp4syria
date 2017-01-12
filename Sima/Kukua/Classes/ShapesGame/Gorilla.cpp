#include "Gorilla.h"
#include "ShapesGame.h"
#include "../Utils/StringUtility.h"
#include "../Utils/Data/Logger.h"

Gorilla::Gorilla(Node& parentNode, const Vec2& localPosition, string csbPath, EventDispatcher* eventDispatcher, ShapesGame* shapesGame)
	: TouchableGameObject(parentNode, localPosition, csbPath, "RootBone/Collider", eventDispatcher),
	mouthState(MouthState::CLOSED),
	eatenBiscuits(0)
{

	CCLOG("Gorilla");

	this->shapesGame = shapesGame;

	simpleAudioEngine = CocosDenshion::SimpleAudioEngine::getInstance();

}

Gorilla::~Gorilla() {

	CCLOG("~Gorilla");

}

void Gorilla::askBiscuit() {

	CCLOG("Gorilla - askBiscuit");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect((ShapesGame::PATH + "Audio/game_shape_feed_animal.mp3").c_str());
    
    getNode().runAction(Sequence::create(DelayTime::create(2.4f), CallFunc::create([=](){
        
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect((ShapesGame::PATH + "Audio/shapes/"+shapesGame->requestedSymbol+".mp3").c_str());
        
    }),  nullptr));
    
    
    

	mouthState = MouthState::ASKING;

	shapesGame->disableTouch();

	play("gorilla_fame_alza", [&]() {
		play("gorilla_fame_loop", [&]() {
			play("gorilla_fame_loop", [&]() {
				play("gorilla_fame_end", [&]() {
					mouthState = MouthState::CLOSED;
					shapesGame->enableTouch();
					play("Gorilla_Idle", nullptr, true);
                    getActionTimeline()->clearLastFrameCallFunc();
				});
			});
		});
	});

}

void Gorilla::openMouth() {

	if (mouthState == MouthState::CLOSED) {
		mouthState = MouthState::OPENING;
		play("Gorilla_Aprebocca", [=]() {
			mouthState = MouthState::OPEN;
			play("Boccaperta_loop", nullptr, true);
            getActionTimeline()->clearLastFrameCallFunc();
			/*if (mouthState == MouthState::CLOSING) {
				mouthState = MouthState::OPEN;
				closeMouth();
			} else {
				mouthState = MouthState::OPEN;
				play("Boccaperta_loop", nullptr, true);
			}*/
		});
	}

}

void Gorilla::closeMouth() {

	if (mouthState == MouthState::OPEN) {
		mouthState = MouthState::CLOSING;
		//simpleAudioEngine->playEffect((SubtractionGame::PATH + "Audio/close.wav").c_str());
		play("Gorilla_boccachiude", [=]() {
			mouthState = MouthState::CLOSED;
			play("Gorilla_Idle", nullptr, true);
            getActionTimeline()->clearLastFrameCallFunc();
		});
	}

}

void Gorilla::eat(Biscuit::Shape shape) {

	shapesGame->disableTouch();

	for (vector<Biscuit*>::iterator iterator = (*(shapesGame->getBiscuits())).begin(); iterator != (*(shapesGame->getBiscuits())).end(); ++iterator) {
		(*iterator)->fadeOut(0.25f);
	}

	simpleAudioEngine->playEffect((ShapesGame::PATH + "Audio/Swallo" + StringUtility::toString(rand() % 3 + 1) + ".mp3").c_str());
	play("Gorilla_Chiudebocca", [=]() {
		simpleAudioEngine->playEffect((ShapesGame::PATH + "Audio/masticamento.mp3").c_str());
		play("gorilla_mastica", [=]() {
			simpleAudioEngine->playEffect((ShapesGame::PATH + "Audio/masticamento.mp3").c_str());
			play("gorilla_mastica", [=]() {
				if (shape == shapesGame->getRequestedShape()) {
                    Logger::getInstance()->logEvent(ShapesGame::NAME, Logger::CORRECT, "");
					++eatenBiscuits;
					play("Goril_FeedOK", [=]() {
						mouthState = MouthState::CLOSED;
						play("Gorilla_Idle", nullptr, true);
						//shapesGame->enableTouch();
						if (eatenBiscuits >= MAX_EATEN_BISCUITS) {
							shapesGame->endGame();
						} else {
							shapesGame->resetBiscuits();
						}
                        getActionTimeline()->clearLastFrameCallFunc();
					});
				} else {
                    Logger::getInstance()->logEvent(ShapesGame::NAME, Logger::WRONG, "");
                    shapesGame->score -= 15;
					eatenBiscuits = 0;
					simpleAudioEngine->playEffect((ShapesGame::PATH + "Audio/NonnoNeg" + StringUtility::toString(rand() % 4 + 1) + ".wav").c_str());
					play("Gorilla_Feed_NO", [=]() {
						mouthState = MouthState::CLOSED;
						play("Gorilla_Idle", nullptr, true);
						shapesGame->resetBiscuits();
                        getActionTimeline()->clearLastFrameCallFunc();
					});
				}
			});
		});
	});

}


bool Gorilla::onTouchBegan(Touch* touch, Event* event) {

	CCLOG("Gorilla - onTouchBegan");

	if (TouchableGameObject::onTouchBegan(touch, event)) {

		askBiscuit();

	}

	return false;

}
