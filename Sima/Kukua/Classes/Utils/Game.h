#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"
#include "GameObject.h"
#include "TouchableGameObject.h"

#include "ui/CocosGUI.h"

#include "../WatchmanScene/WatchmanScene.h"
#include "../AppMacros.h"
#include <vector>
#include <typeinfo>
#include "Data/Logger.h"

using namespace std;
using namespace cocos2d;
using namespace cocostudio::timeline;
using namespace CocosDenshion;


namespace kukua {

	template <class GameClass>
	class Game : public cocos2d::Layer {

	public:
		static const bool USE_PHYSICS;							// Enable/disable physics
		static const bool ENABLE_TOUCH;							// Used to disable tutorial on first touch and manage general touch events
		static string PATH;								// Resources' subfolder path for this game
		static const string BACKGROUND_MUSIC_FILENAME;			// Background music filename
        static const string NAME;

		static Scene* createScene() {

			// 'scene' is an autorelease object
			if (GameClass::USE_PHYSICS) {
				GameClass::scene = Scene::createWithPhysics();

				// Enable physics debug
				//GameClass::scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

				// CCLOG("Use physics");
			} else {
				GameClass::scene = Scene::create();
				// CCLOG("Don't use physics");
			}

			// 'layer' is an autorelease object			 
			auto layer = GameClass::create();

			// add layer as a child to scene
			GameClass::scene->addChild(layer);

			// return the scene
			return GameClass::scene;

		}

		// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
		bool init() {

			if (!Layer::init())
			{
				return false;
			}
            
			rootNode = CSLoader::createNode(GameClass::PATH + "MainScene.csb");

			rootNode->setAnchorPoint(Point(0.5, 0.5));
			rootNode->setPosition(Point(_director->getWinSize().width / 2, _director->getWinSize().height / 2));
			addChild(rootNode);
            
			startGame();
			
			return true;

		}

		void startGame() {
            
            Logger::getInstance()->logEvent(GameClass::NAME, Logger::OPEN, "");

			initVariables();
			initAudio();
			initGameObjects();
			addHomeButton();
			fadeIn();

		}

		void initVariables() {

			static_cast<GameClass*>(this)->initVariables();

		}

		void initAudio() {

			simpleAudioEngine = SimpleAudioEngine::getInstance();

			if (BACKGROUND_MUSIC_FILENAME.length() > 0) {

				simpleAudioEngine->playBackgroundMusic((GameClass::PATH + "Audio/" + BACKGROUND_MUSIC_FILENAME).c_str(), true);

			}

			static_cast<GameClass*>(this)->initAudio();

		}

		void initGameObjects() {

			static_cast<GameClass*>(this)->initGameObjects();

		}

		void fadeIn() {

			static_cast<GameClass*>(this)->fadeIn();

		}

		void showTutorial() {

			if (showingTutorial) {
				return;
			}

			if (GameClass::SHOWN_TUTORIAL) {
				showingTutorial = false;
				return;
			}

			GameClass::SHOWN_TUTORIAL = true;
			showingTutorial = true;

			static_cast<GameClass*>(this)->showTutorial();

		}

		void hideTutorial() {

            if (!showingTutorial) {
				return;
			}

			static_cast<GameClass*>(this)->hideTutorial();

			showingTutorial = false;

		}

		void enableTouch() {

			if (GameClass::ENABLE_TOUCH) {

                
             //   assert(this != nullptr);
                
				touchListener = EventListenerTouchOneByOne::create();

				touchListener->onTouchBegan = CC_CALLBACK_2(GameClass::touchBegan, this);
				touchListener->onTouchMoved = CC_CALLBACK_2(GameClass::touchMoved, this);
				touchListener->onTouchEnded = CC_CALLBACK_2(GameClass::touchEnded, this);

				_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, rootNode);

			} else {

				touchListener = nullptr;

			}

			// Enable thouch events on touchableGameObjects
			for (vector<TouchableGameObject*>::iterator iterator = touchableGameObjects.begin(); iterator != touchableGameObjects.end(); ++iterator) {
				(*iterator)->setTouchable(true);
			}
			
		}

		void disableTouch() {

			if (GameClass::ENABLE_TOUCH) {

				_eventDispatcher->removeEventListener(touchListener);
                touchListener = nullptr;
			}

			// Disable thouch events on touchableGameObjects

			for (vector<TouchableGameObject*>::iterator iterator = touchableGameObjects.begin(); iterator != touchableGameObjects.end(); ++iterator) {
				(*iterator)->setTouchable(false);
			}

		}

		bool touchBegan(Touch* touch, Event* event) {

			if (showingTutorial) {
				hideTutorial();
			}

			return static_cast<GameClass*>(this)->onTouchBegan(touch, event);

		}

		void touchMoved(Touch* touch, Event* event) {

			static_cast<GameClass*>(this)->onTouchMoved(touch, event);

		}

		void touchEnded(Touch* touch, Event* event) {

			static_cast<GameClass*>(this)->onTouchEnded(touch, event);

		}

		void endGame(bool gameOver = false) {

			static_cast<GameClass*>(this)->endGame(gameOver);

		}
        
        void homeButtonPressed() {
            
            static_cast<GameClass*>(this)->homeButtonPressed();
        }


	protected:

		static bool SHOWN_TUTORIAL;								// Used for showing tutorial on first execution, set to true only if tutorial is not needed
		static Scene* scene;
		bool showingTutorial;
		SimpleAudioEngine* simpleAudioEngine;
		Node* rootNode;
		EventListenerTouchOneByOne* touchListener;
		vector<TouchableGameObject*> touchableGameObjects;

		CREATE_FUNC(Game);

		virtual ~Game() {

			// CCLOG("~Game");

		}

	private:

		void addHomeButton() {

			cocos2d::ui::Button *backNode = cocos2d::ui::Button::create("common/homeBtn.png", "common/homeBtn.png", "common/homeBtn.png");
			backNode->setName("HomeButton");

            backNode->setAnchorPoint(Vec2(0.5, 0.5));
            
            auto frameSize =  rootNode->getBoundingBox().size; //cocos2d::Director::getInstance()->getWinSize();
			auto x = 90;
            /*
            CCLOG("frameSize.height = %f", frameSize.height);
            CCLOG("cocos2d::Director::getInstance()->getWinSize() = %f", cocos2d::Director::getInstance()->getWinSize().height);
            CCLOG("rootNode->getBoundingBox().size = %f", rootNode->getBoundingBox().size.height);
            */
            float winHeight = cocos2d::Director::getInstance()->getWinSize().height;
            float rootHieght = rootNode->getBoundingBox().size.height;
            
            float y = 0;
            
            if ( winHeight < rootHieght ) {
                // come per iphone
                //CCLOG("like iphone");
                y = winHeight;
                
            } else {
                // come per ipad
                //   CCLOG("like ipad");
                float delta = (winHeight-rootHieght) / 2;
                y = rootHieght + delta;
                y -= 10;
            }
            
            
            y = y - (backNode->getBoundingBox().size.height /2);
            // auto y = frameSize.height * 0.9f; // originale
            //auto y = frameSize.height;
            
            backNode->setPosition(Vec2(x, y));
			//addChild(backNode, 10); //rootNode->addChild(backNode, 10);

            rootNode->addChild(backNode, 10); // originale
                        
			backNode->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
				switch (type) {
				case ui::Widget::TouchEventType::BEGAN:
					break;
				case ui::Widget::TouchEventType::ENDED:
                    homeButtonPressed();
                    Logger::getInstance()->logEvent(GameClass::NAME, Logger::CLOSE, "");
                    simpleAudioEngine->stopBackgroundMusic();
                    _director->replaceScene(TransitionFade::create(TRANSITION_TIME, WatchmanScene::createScene(), TRANSITION_COLOR));

					break;
				default:
					break;
				}
			});

		}

	};
	
}
