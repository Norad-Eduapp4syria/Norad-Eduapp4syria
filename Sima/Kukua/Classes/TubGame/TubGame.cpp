#include "TubGame.h"
//#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
//#include "MyBodyParser.h"
#include "time.h"
#include <cmath>
#include <vector>
#include "../Utils/StringUtility.h"
#include "../Utils/Data/Logger.h"
#include "../WatchmanScene/WatchmanScene.h"
#include "../AppMacros.h"
#include "../Utils/Data/ArabicHelper.h"

USING_NS_CC;

using namespace cocostudio::timeline;

string TubGame::NAME = "TubGame";

Scene* TubGame::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TubGame::create();

    // add layer as a child to scene
    scene->addChild(layer);

	// add physic gravity
	//scene->getPhysicsWorld()->setGravity(Vec2(0, -980));
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);

    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool TubGame::init()
{

    if ( !Layer::init() )
    {
        return false;
    }
	
    Logger::getInstance()->logEvent(NAME, Logger::OPEN, "");

    dataProvider = DataProvider::getInstance();
    
    preloadAudio();
    
    matchCounter = 1;
    correctAnswerCounter = 0;
 
    rootNode = CSLoader::createNode("TubGame/MainScene.csb");
	rootNode->setAnchorPoint(Point(0.5, 0.5));
	rootNode->setPosition(Point(_director->getWinSize().width / 2, _director->getWinSize().height / 2));
    addChild(rootNode);

	countBallExit = 0;
	clicked = false;
    
    
    ball1 = static_cast<Node*>(rootNode->getChildByName("bolla_1"));
    ball2 = static_cast<Node*>(rootNode->getChildByName("bolla_2"));
    
    

	/*
	Bolla1 - BOLLA_arrivo - BOLLA_standing - BOLLA_esce - BOLLA_positive - BOLLA_negative
	Bolla2 - BOLLA_arrivo - BOLLA_standing - BOLLA_esce - BOLLA_positive - BOLLA_negative
	Spirale - animation0
	Tinozza - TATU_arrivo - TATU_standing - TATU_Negative - TATU_Positive
	Bollicine - bolle_generic
	*/

	ball1->setVisible(false);
	ball2->setVisible(false);
	rootNode->getChildByName("spiral")->setVisible(false);


	auto node1 = static_cast<Node*>(ball1->getChildByName("Bone_bolla")->getChildByName("val"));
	auto node2 = static_cast<Node*>(ball2->getChildByName("Bone_bolla")->getChildByName("val"));
	
    string correct = dataProvider->getCurrentDBKnowledgeBubble()->getPhoneme();

    if (DataProvider::getInstance()->getCurrentEpisode() == 3) {
        correct = correct.substr(0, correct.find("#"));
        correct = correct + "_u";
    }
    
    label1 = ArabicHelper::getInstance()->createLabel(correct, 180);
	node1->addChild(label1);

    label2 = ArabicHelper::getInstance()->createLabel(correct, 180);
    node2->addChild(label2);
    
    setValuesInBubbbles();

    CallFunc *runCallback_tutorial = CallFunc::create(CC_CALLBACK_0(TubGame::showHelp, this));
    this->runAction(Sequence::create(DelayTime::create(0.1), runCallback_tutorial, nullptr));

    
	addBackToHomeButton();

    return true;
}

void TubGame::setValuesInBubbbles() {
    CCLOG("setValuesInBubbbles");
    srand( static_cast<unsigned int>(time(NULL)));
    highestOrLowest = 1;;
    number1 = 1 + rand() % 99;
    number2 = 1 + rand() % 99;
    if (number1 == number2) number2++;
    	//CCLOG("%i %i %i", highestOrLowest, number1, number2);
    
    string correct = dataProvider->getCurrentDBKnowledgeBubble()->getPhoneme();
    if (DataProvider::getInstance()->getCurrentEpisode() == 3) {
        correct = correct.substr(0, correct.find("#"));
        correct = correct + "_u";
    }
    
    string wrong = dataProvider->getRandomWrongPhoneme(correct);
    wrong = wrong.substr(0, wrong.find("_"));

    if (DataProvider::getInstance()->getCurrentEpisode() == 3) {
        wrong = wrong.substr(0, wrong.find("#"));
    }
    
    while (wrong == correct) {
        wrong = dataProvider->getRandomWrongPhoneme(correct);
        wrong = wrong.substr(0, wrong.find("_"));
        if (DataProvider::getInstance()->getCurrentEpisode() == 3) {
            wrong = wrong.substr(0, wrong.find("#"));
        }
    }
    
 
    
    // CCLOG("----correct = %s", correct.c_str() );
    // CCLOG("----wrong = %s", wrong.c_str() );
    
    if (number1 > number2) {
        
        label1->setString( ArabicHelper::getInstance()->getInArabic( correct )  );
        label2->setString( ArabicHelper::getInstance()->getInArabic( wrong )  );
        
    }else {
        
        label1->setString( ArabicHelper::getInstance()->getInArabic( wrong )  );
        label2->setString( ArabicHelper::getInstance()->getInArabic( correct )  );
        
    }
    

    

}


void TubGame::preloadAudio() {
    audio = CocosDenshion::SimpleAudioEngine::getInstance();
    
    audio->preloadEffect("TubGame/audio/bollAppare.mp3");
    audio->preloadEffect("TubGame/audio/bollKO.mp3");
    audio->preloadEffect("TubGame/audio/bollOK.mp3");
    audio->preloadEffect("TubGame/audio/bollVaVia.mp3");
    audio->preloadEffect("TubGame/audio/popHigher.mp3");
    audio->preloadEffect("TubGame/audio/popLower.mp3");
    audio->preloadEffect("TubGame/audio/Tap_to_pop_the_letter.mp3");
    audio->preloadEffect("TubGame/audio/Tatu_KO.mp3");
    audio->preloadEffect("TubGame/audio/Tatu_OK.mp3");
    audio->preloadEffect("TubGame/audio/tinozza.mp3");
    
    
    audio->preloadBackgroundMusic("common/audio/bg/GAME_4.mp3");
    audio->playBackgroundMusic("common/audio/bg/GAME_4.mp3", true);
}

void TubGame::addBackToHomeButton() {

	auto backNode = cocos2d::ui::Button::create("common/homeBtn.png", "common/homeBtn.png", "common/homeBtn.png");

	auto frameSize = cocos2d::Director::getInstance()->getWinSize();
	auto x = 90;//frameSize.width * 0.5f;
	auto y = frameSize.height * 0.9f;
	backNode->setPosition(Vec2(x, y));
	addChild(backNode, 10);

	backNode->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
            Logger::getInstance()->logEvent(NAME, Logger::CLOSE, "");
			audio->stopBackgroundMusic();
            if ( TEST_ENABLED ) {
                DataProvider::getInstance()->setGameCompleted("TubGame");
                DataProvider::getInstance()->setWatchmanReaction(WatchmanScene::GOOD_REACTION);
            } else {
                DataProvider::getInstance()->setWatchmanReaction(WatchmanScene::BAD_REACTION);
            }
            _director->replaceScene(TransitionFade::create(TRANSITION_TIME, WatchmanScene::createScene(), TRANSITION_COLOR));
			break;
		default:
			break;
		}
	});

}


void TubGame::showHelp() {
    
    auto helpRef = static_cast<Node*>(rootNode->getChildByName("helpRef"));
    
    
    string correct = dataProvider->getCurrentDBKnowledgeBubble()->getPhoneme();
    
    if (DataProvider::getInstance()->getCurrentEpisode() == 3) {
        correct = correct.substr(0, correct.find("#"));
        correct = correct + "_u";
    }
    
    auto labelHelp = ArabicHelper::getInstance()->createLabel(correct, 220, true);
    labelHelp->setColor(Color3B(47,109,182));
    
    Node* help = CSLoader::createNode("Main_prop/Help/Main_Help.csb");
    help->getChildByName("Lettera_a")->getChildByName("ref")->addChild(labelHelp);
    helpRef->addChild(help);
    
    auto helpTimeline = CSLoader::createTimeline("Main_prop/Help/Main_Help.csb");
    
    help->runAction(helpTimeline);
    helpTimeline->play("Help", false);
    
    audio->playEffect("TubGame/audio/Tap_to_pop_the_letter.mp3");
    
    runAction(
        Sequence::createWithTwoActions(
                DelayTime::create(2.2),
                CallFunc::create([=]() {
                    playAudioPhoneme();
                    CallFunc *runCallback_letter2 = CallFunc::create(CC_CALLBACK_0(TubGame::playAudioPhoneme, this));
                    this->runAction(Sequence::create(DelayTime::create(2.1), runCallback_letter2, nullptr));
                })
        )
    );

    
    
    
    
    helpTimeline->setLastFrameCallFunc([=](){
        
        addDefaultObj();
        helpTimeline->clearLastFrameCallFunc();
    });
    
    
    return;
    /*
    string txt = dataProvider->getCurrentDBKnowledgeBubble()->getPhoneme();
    
    auto help = static_cast<Node*>(rootNode->getChildByName("Help"));
    auto letterPart = static_cast<Node*>(help->getChildByName("Lettera_a"));
    
    auto letterHelpImg = Sprite::create("common/images/letters/big_blue/"+txt+".png");
    help->getChildByName("Lettera_a")->addChild(letterHelpImg);
    
    
    
    //
    help->setVisible(true);
    auto helpTimeline = CSLoader::createTimeline("TubGame/CSD/Help_TubGame.csb");
    help->runAction(helpTimeline);
    helpTimeline->play("Help", false);
    
    audio->playEffect("TubGame/audio/Tap_to_pop_the_letter.mp3");
    
    letterPart->runAction(
        Sequence::createWithTwoActions(
            DelayTime::create(2.2),
            CallFunc::create([=]() {
                playAudioPhoneme();
                CallFunc *runCallback_letter2 = CallFunc::create(CC_CALLBACK_0(TubGame::playAudioPhoneme, this));
                this->runAction(Sequence::create(DelayTime::create(2.1), runCallback_letter2, nullptr));
            })
         )
    );
    
    helpTimeline->setLastFrameCallFunc([=](){
        
        addDefaultObj();
        helpTimeline->clearLastFrameCallFunc();
    });
    */
}
void TubGame::playAudioPhoneme(){
    string correct = dataProvider->getCurrentDBKnowledgeBubble()->getPhoneme();
    
    if (DataProvider::getInstance()->getCurrentEpisode() == 3) {
        correct = correct.substr(0, correct.find("#"));
        correct = correct + "_u";
    }
    
    audio->playEffect(("common/audio/grandpa/phonemes/" + correct + ".mp3").c_str());
}


// call when the page is in creation
void TubGame::addDefaultObj() {
	CCLOG("addDefaultObj");

	CallFunc *runCallback1 = CallFunc::create(CC_CALLBACK_0(TubGame::addTub, this));
	this->runAction(Sequence::create(DelayTime::create(0.3), runCallback1, nullptr));

    addBall1();
    addBall2();

}

// the tub goes 
void TubGame::addTub() {

	audio->playEffect("TubGame/audio/tinozza.mp3");
	auto tub = static_cast<Node*>(rootNode->getChildByName("tatu"));
	tubTimeline = CSLoader::createTimeline("TubGame/CSD/tatu.csb");
	tub->runAction(tubTimeline);
	tubTimeline->play("TATU_arrivo", false);

	tubTimeline->setLastFrameCallFunc([=]() {
		tubTimeline->play("TATU_standing", true);
        tubTimeline->clearLastFrameCallFunc();
	});
}

// the ball 1 goes 
void TubGame::addBall1() {
	audio->playEffect("TubGame/audio/bollAppare.mp3");
    ball1->setPositionY(535);
    ball1->setVisible(true);
    ball1Timeline = CSLoader::createTimeline("TubGame/CSD/bolla.csb");
	ball1->runAction(ball1Timeline);
	ball1Timeline->play("BOLLA_arrivo", false);

	ball1Timeline->setLastFrameCallFunc([=]() {
		//rootNode->getChildByName("Balloon_lower")->setVisible(false);
		playAnimationUp();
        ball1Timeline->clearLastFrameCallFunc();
	});
}

// the ball 2 goes 
void TubGame::addBall2() {
	audio->playEffect("TubGame/audio/bollAppare.mp3");
    ball2->setVisible(true);
    ball2->setPositionY(535);
    ball2Timeline = CSLoader::createTimeline("TubGame/CSD/bolla.csb");
	ball2->runAction(ball2Timeline);
	ball2Timeline->play("BOLLA_arrivo", false);
}

// ball 1 go to standing
void TubGame::ball1InStanding() {
	ball1Timeline->play("BOLLA_standing", true);
	
	button1 = static_cast<ui::Button*>(ball1->getChildByName("Button"));
	if (matchCounter==1) button1->addClickEventListener(CC_CALLBACK_0(TubGame::buttonPressed1, this));
    button1->setEnabled(true);
}

// ball 2 go to standing
void TubGame::ball2InStanding() {
	ball2Timeline->play("BOLLA_standing", true);

	button2 = static_cast<ui::Button*>(ball2->getChildByName("Button"));
	if (matchCounter==1) button2->addClickEventListener(CC_CALLBACK_0(TubGame::buttonPressed2, this));
    button2->setEnabled(true);

}
void TubGame::removeClickButton(){
    button1->setEnabled(false);  // button1->removeClickEventListener(CC_CALLBACK_0(TubGame::buttonPressed1, this));
    
    button2->setEnabled(false);  // ->removeClickEventListener(CC_CALLBACK_0(TubGame::buttonPressed2, this));
}



void TubGame::buttonPressed1() {
    removeClickButton();
	CCLOG("PRESS1");

	if (highestOrLowest == 1 && number1 > number2) {
		ball1Timeline->play("BOLLA_positive", false);
		ball2Timeline->play("BOLLA_esce", false);
		clickResult(true);
	}else if (highestOrLowest == 2 && number1 < number2) {
		ball1Timeline->play("BOLLA_positive", false);
		ball2Timeline->play("BOLLA_esce", false);
		clickResult(true);
	}else if (highestOrLowest == 1) {
		ball1Timeline->play("BOLLA_negative", false);
		ball2Timeline->play("BOLLA_esce", false);
		clickResult(false);
	}else if (highestOrLowest == 2) {
		ball1Timeline->play("BOLLA_negative", false);
		ball2Timeline->play("BOLLA_esce", false);
		clickResult(false);
	}

	ball1Timeline->setLastFrameCallFunc([=]() {
		ball1->setVisible(false);
	});

	ball2Timeline->setLastFrameCallFunc([=]() {
		ball2->setVisible(false);
	});


}

void TubGame::buttonPressed2() {
    removeClickButton();
    CCLOG("PRESS2");

	if (highestOrLowest == 1 && number2 > number1) {
		ball1Timeline->play("BOLLA_esce", false);
		ball2Timeline->play("BOLLA_positive", false);
		clickResult(true);
	}
	else if (highestOrLowest == 2 && number2 < number1) {
		ball1Timeline->play("BOLLA_esce", false);
		ball2Timeline->play("BOLLA_positive", false);
		clickResult(true);
	}
	else if (highestOrLowest == 1) {
		ball1Timeline->play("BOLLA_esce", false);
		ball2Timeline->play("BOLLA_negative", false);
		clickResult(false);
	}
	else if (highestOrLowest == 2) {
		ball1Timeline->play("BOLLA_esce", false);
		ball2Timeline->play("BOLLA_negative", false);
		clickResult(false);
	}

	ball1Timeline->setLastFrameCallFunc([=]() {
		ball1->setVisible(false);
	});

	ball2Timeline->setLastFrameCallFunc([=]() {
		ball2->setVisible(false);
	});
}

void TubGame::clickResult(bool _right) {
	CallFunc *runCallbackResultAnim;
	if (_right) {
		runCallbackResultAnim = CallFunc::create(CC_CALLBACK_0(TubGame::resulAnimOK, this));
	}else {
		runCallbackResultAnim = CallFunc::create(CC_CALLBACK_0(TubGame::resulAnimKO, this));
	}
	this->runAction(Sequence::create(DelayTime::create(0.5), runCallbackResultAnim, nullptr));

	clicked = true;

	ball1->stopAction(ball1MoveAction);
	ball2->stopAction(ball2MoveAction);

	audio->playEffect("TubGame/audio/bollVaVia.mp3");
}


void TubGame::resulAnimOK() {
    correctAnswerCounter++;
    Logger::getInstance()->logEvent(NAME, Logger::CORRECT, "");
    Logger::getInstance()->logEvent(NAME, Logger::WIN, "");
	audio->playEffect("TubGame/audio/bollOK.mp3");
	audio->playEffect("TubGame/audio/tatu_OK.mp3");
	tubTimeline->play("TATU_Positive", false);
	rootNode->getChildByName("spiral")->setVisible(true);
	auto spirale = static_cast<Node*>(rootNode->getChildByName("spiral"));
	auto spiraleTimeline = CSLoader::createTimeline("TubGame/CSD/spiral.csb");
	spirale->runAction(spiraleTimeline);
	spiraleTimeline->play("animation0", false);

	spiraleTimeline->setLastFrameCallFunc([=]() {		
		endGame();
		rootNode->getChildByName("spiral")->setVisible(false);
        spiraleTimeline->clearLastFrameCallFunc();
	});
}

void TubGame::resulAnimKO() {

    // subtract score
    scorePercent -= scoreToSubtract;
    
    Logger::getInstance()->logEvent(NAME, Logger::WRONG, "");
    Logger::getInstance()->logEvent(NAME, Logger::LOSE, "");
	audio->playEffect("TubGame/audio/bollKO.mp3");
	audio->playEffect("TubGame/audio/tatu_KO.mp3");
	tubTimeline->play("TATU_Negative", false);
	CallFunc *runCallbackEnd = CallFunc::create(CC_CALLBACK_0(TubGame::endGame, this));
	this->runAction(Sequence::create(DelayTime::create(2), runCallbackEnd, nullptr));
}



// ball 1 e ball 2 go up, when the balls is up the screen game over
void TubGame::playAnimationUp() {
    
	ball1InStanding();
	ball2InStanding();
	
	ball1MoveAction = MoveBy::create(10, Vec2(0, 500));
    CallFunc *callback1 = CallFunc::create(CC_CALLBACK_0(TubGame::ballExit, this));
	ball1->runAction(Sequence::create(ball1MoveAction, callback1, nullptr));

	ball2MoveAction = MoveBy::create(10, Vec2(0, 500));
    CallFunc *callback2 = CallFunc::create(CC_CALLBACK_0(TubGame::ballExit, this));
	ball2->runAction(Sequence::create(ball2MoveAction, callback2, nullptr));
	
    
    
    
}

void TubGame::ballExit(){
	if (!clicked) {
		CCLOG("Ball Exit");
		countBallExit++;
		if (countBallExit == 2) {
			audio->playEffect("TubGame/audio/tatu_KO.mp3");
			tubTimeline->play("TATU_Negative", false);
			endGame();
		}
	}
}

void TubGame::endGame() {
	restartGame();
}
void TubGame::restartGame() {
    CCLOG("---restart");
    matchCounter++;
    
    if (matchCounter == 6) {
        Logger::getInstance()->logEvent(NAME, Logger::CLOSE, "");
        
        audio->stopBackgroundMusic();
        
        if (correctAnswerCounter > 3) {
            DataProvider::getInstance()->setGameCompleted("TubGame");
            DataProvider::getInstance()->setWatchmanReaction(WatchmanScene::GOOD_REACTION);
        } else {
            DataProvider::getInstance()->setWatchmanReaction(WatchmanScene::BAD_REACTION);
        }
        
        _director->replaceScene(TransitionFade::create(TRANSITION_TIME, WatchmanScene::createScene(), TRANSITION_COLOR));
        
        return;
    }
    
    
    
    ////
    
    countBallExit = 0;
    clicked = false;
    ball1Timeline->stop();
    ball2Timeline->stop();
    ball1->stopAllActions();
    ball2->stopAllActions();
    
    ball1->setVisible(false);
    ball2->setVisible(false);
    rootNode->getChildByName("spiral")->setVisible(false);
    
    ////
  
    setValuesInBubbbles();
    
    ///
    
    tubTimeline->play("TATU_standing", true);
    
    
    addBall1();
    addBall2();
    
    
	
}
