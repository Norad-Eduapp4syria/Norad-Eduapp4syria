#include "ShapesGame2.h"
#include "../Utils/StringUtility.h"
#include "../Utils/Data/DataProvider.h"
#include "../WatchmanScene/WatchmanScene.h"
#include "../AppMacros.h"

using namespace std;

template<> const bool kukua::Game<ShapesGame2>::USE_PHYSICS = false;										// Enable/disable physics
template<> const bool kukua::Game<ShapesGame2>::ENABLE_TOUCH = true;										// Used to disable tutorial on first touch and manage general touch events
template<> string kukua::Game<ShapesGame2>::PATH = "ShapesGame2/";											// Resources' subfolder path for this game
template<> const string kukua::Game<ShapesGame2>::BACKGROUND_MUSIC_FILENAME = "";							// Background music filename
template<> bool kukua::Game<ShapesGame2>::SHOWN_TUTORIAL = false;											// Used for showing tutorial on first execution, set to true only if tutorial is not needed
template<> Scene* kukua::Game<ShapesGame2>::scene = nullptr;
template<> const string kukua::Game<ShapesGame2>::NAME = "ShapeIdentifier";

ShapesGame2::~ShapesGame2() {

	CCLOG("~ShapesGame2");
    
    
    _eventDispatcher->removeEventListener(clickBug);
    _eventDispatcher->removeEventListener(deleteBug);
    
    delete help;
    delete tree;
    delete tatu;
    delete leafs;
    delete semaTry;
    delete semaWell;
    delete formCounter1;
    delete formCounter2;
    delete formCounter3;
    delete formCounter4;
    delete formCounter5;
    delete form;
   
}

void ShapesGame2::initVariables() {
	test = false;
	nLedOn = 1;
	gameFinished = false;
    
    
    
    DataProvider *dataProvider = DataProvider::getInstance();
    string currentPhoneme = dataProvider->getCurrentDBKnowledgeBubble()->getPhoneme();
    
    vector<string> wordsVector = dataProvider->getWordsForGame( currentPhoneme, "shapeIdentif" );
    string symbol =  wordsVector.at(0);
    
    if (symbol == "circle") validSimbol = 1;
    else if (symbol == "triangle") validSimbol = 2;
    else if (symbol == "square") validSimbol = 3;
    else if (symbol == "trapezoid") validSimbol = 4;
    else if (symbol == "hexagon") validSimbol = 5;
    else if (symbol == "oval")         validSimbol = 6;
    else if (symbol == "octagon")  validSimbol = 7;
    else if (symbol == "rectangle") validSimbol = 8;
    else if (symbol == "pentagon") validSimbol = 9;
    else if (symbol == "parallelogram") validSimbol = 10;
    else if (symbol == "rhombus")   validSimbol = 11;
    else  {
        validSimbol = 1 + rand() % 11;
    }
    
}

void ShapesGame2::initAudio() {

	simpleAudioEngine = CocosDenshion::SimpleAudioEngine::getInstance();


	simpleAudioEngine->preloadEffect("ShapesGame2/audio/AlbeEntra.mp3");
	simpleAudioEngine->preloadEffect("ShapesGame2/audio/FeedPosTatu.mp3");
	simpleAudioEngine->preloadEffect("ShapesGame2/audio/fogliaEntra.mp3");
	simpleAudioEngine->preloadEffect("ShapesGame2/audio/help.mp3");
	simpleAudioEngine->preloadEffect("ShapesGame2/audio/insettiFly.mp3");
	simpleAudioEngine->preloadEffect("ShapesGame2/audio/insettiFlyHI.mp3");
	simpleAudioEngine->preloadEffect("ShapesGame2/audio/LinguaBite.mp3");
	simpleAudioEngine->preloadEffect("ShapesGame2/audio/popShape.mp3");
	simpleAudioEngine->preloadEffect("ShapesGame2/audio/SlurpBite.mp3");
	simpleAudioEngine->preloadEffect("ShapesGame2/audio/SlurpBite2.mp3");
	simpleAudioEngine->preloadEffect("ShapesGame2/audio/TatuSale.mp3");

    
    simpleAudioEngine->preloadBackgroundMusic("common/audio/bg/GAME_5.mp3");
    simpleAudioEngine->playBackgroundMusic("common/audio/bg/GAME_5.mp3", true);
}

void ShapesGame2::initGameObjects() {
    
    Logger::getInstance()->logEvent(NAME, Logger::OPEN, "");
    
    int skin = DataProvider::getInstance()->getSkin();
    string skinStr = StringUtility::toString(skin);
    
	//create GameObject from stage obj
	help = new GameObject(*rootNode, "help", PATH + "CSD/help.csb");
    tree = new GameObject(*rootNode->getChildByName("treeRef"), Vec2::ZERO, PATH + "CSD/tree_"+skinStr+".csb");
	tatu = new GameObject(*rootNode, "tatu", PATH + "CSD/tatu.csb");
	leafs = new GameObject(*rootNode, "leaf", PATH + "CSD/leafs.csb");
	semaTry = new GameObject(*rootNode, "sema_try", PATH + "CSD/semaTry.csb");
	semaWell = new GameObject(*rootNode, "sema_well", PATH + "CSD/semaWell.csb");
	formCounter1 = new GameObject(*rootNode, "counter1", PATH + "CSD/counter.csb");
	formCounter2 = new GameObject(*rootNode, "counter2", PATH + "CSD/counter.csb");
	formCounter3 = new GameObject(*rootNode, "counter3", PATH + "CSD/counter.csb");
	formCounter4 = new GameObject(*rootNode, "counter4", PATH + "CSD/counter.csb");
	formCounter5 = new GameObject(*rootNode, "counter5", PATH + "CSD/counter.csb");
	arrayCounter = {formCounter1, formCounter2, formCounter3, formCounter4, formCounter5};
    
    
    static_cast<Sprite*>(rootNode->getChildByName("bg"))->setTexture(PATH+"PNG/Fondale_" +  StringUtility::toString(skin) + "/Fondo.png");
    static_cast<Sprite*>(leafs->getChild("Bone_FOGLIA/foglie"))->setTexture(PATH+"PNG/Fondale_" +  StringUtility::toString(skin) + "/foglie.png");
    
    
    for (vector<Bug*>::iterator iterator = arrayBugToDelete.begin(); iterator != arrayBugToDelete.end(); ++iterator) {
        delete (*iterator);
    }
    

}

void ShapesGame2::createBug(){
	if (!gameFinished){

		int typeBug = 1 + rand() % 14; //1 + rand() % 11;

        if (typeBug > 11) typeBug = validSimbol;
        
        
		int xPos = 100 + rand() % 600;
		int yPos = 100 + rand() % (int(_director->getWinSize().height-200));

		auto bug = new Bug(*rootNode->getChildByName("bugs"), Point(xPos, yPos), PATH, typeBug, _eventDispatcher);
		arrayBug.push_back(bug);

		CallFunc *runCallback_createBug = CallFunc::create(CC_CALLBACK_0(ShapesGame2::createBug, this));
		this->runAction(Sequence::create(DelayTime::create(2), runCallback_createBug, nullptr));
	}
}


void ShapesGame2::gotoPauseOut(){
	gamePaused = false;
}
void ShapesGame2::openLeafs(){
	if (!gameFinished){
		
		CallFunc *runCallback_createBug = CallFunc::create(CC_CALLBACK_0(ShapesGame2::gotoPauseOut, this));
		this->runAction(Sequence::create(DelayTime::create(1), runCallback_createBug, nullptr));
	}
}

void ShapesGame2::closeLeafs(){
	leafs->play("exit", ([=]() {
		openLeafs();
		leafs->getActionTimeline()->clearLastFrameCallFunc();
	}), false);
}

void ShapesGame2::startAnimStartGame(){
	simpleAudioEngine->playEffect("ShapesGame2/audio/TatuSale.mp3");
	simpleAudioEngine->playEffect("ShapesGame2/audio/AlbeEntra.mp3");
	//play tree intro anim 
	tree->play("intro", ([=]() {
		help->getActionTimeline()->clearLastFrameCallFunc();
	}), false);

	//play tatu intro anim 
	tatu->play("intro", ([=]() {
		help->getActionTimeline()->clearLastFrameCallFunc();
	}), false);

	//play intro counter ball anim
	//formCounter1->play("intro", nullptr, false);
    formCounter1->play("turn_on", nullptr, false);
	formCounter2->play("intro", nullptr, false);
	formCounter3->play("intro", nullptr, false);
	formCounter4->play("intro", nullptr, false);
	formCounter5->play("intro", nullptr, false);
    
    simpleAudioEngine->playEffect("ShapesGame2/audio/fogliaEntra.mp3");
    leafs->play("intro", nullptr, false);
    
    // validSimbol = 1 + rand() % 5;
    auto *formContent = static_cast<Node*>(leafs->getChild("Bone_FOGLIA/Forma"));
    leafs->getChild("Bone_FOGLIA/Forma")->removeAllChildren();
    form = new GameObject(*formContent, Vec2::ZERO, PATH + "CSD/form" + StringUtility::toString(validSimbol) + ".csb");
    form->setScale(0.6);
   
    openLeafs();

	createBug();
}



void ShapesGame2::returnTongue(bool _correctBug, Bug* _target) {
	ScaleTo *tongueScaleActionAc = ScaleTo::create(0.5, 1, 1);
	auto tongueScaleAction = EaseSineInOut::create(tongueScaleActionAc->clone());
	tatu->getChild("BONE_MASTER/HEAD_MASTER/LINGUA_MASTER/bone_lingua")->runAction(tongueScaleAction);

	MoveTo *tongueMoveActionAc = MoveTo::create(0.5, Vec2(73, 0));
	auto tongueMoveAction = EaseSineInOut::create(tongueMoveActionAc->clone());
	tatu->getChild("BONE_MASTER/HEAD_MASTER/LINGUA_MASTER/bone_Puntalig")->runAction(tongueMoveAction);
	if (_correctBug){
		touchBugOK();

		CallFunc *runCallback_happy = CallFunc::create([=]() {
			simpleAudioEngine->playEffect("ShapesGame2/audio/FeedPosTatu.mp3");
			tatu->play("happy", ([=]() {
				//on complete start anim of all object
				tatu->play("stand", nullptr, true);
				tatu->getActionTimeline()->clearLastFrameCallFunc();
			}), false);
		});
		this->runAction(Sequence::create(DelayTime::create(0.5), runCallback_happy, nullptr));


		//tatu->bringToFront();

		float xDest = tatu->getPosition().x + tatu->getChild("BONE_MASTER")->getPosition().x + tatu->getChild("BONE_MASTER/HEAD_MASTER")->getPosition().x + tatu->getChild("BONE_MASTER/HEAD_MASTER/LINGUA_MASTER")->getPosition().x;
		float yDest = tatu->getPosition().y + tatu->getChild("BONE_MASTER")->getPosition().y + tatu->getChild("BONE_MASTER/HEAD_MASTER")->getPosition().y + tatu->getChild("BONE_MASTER/HEAD_MASTER/LINGUA_MASTER")->getPosition().y;

		MoveTo *bugMoveActionAc = MoveTo::create(0.5, Vec2(xDest, yDest));
		auto bugMoveAction = EaseSineInOut::create(bugMoveActionAc->clone());
		_target->play(bugMoveAction);

		_target->shadow->setVisible(false);
		ScaleTo *bugScaleActionAc = ScaleTo::create(0.25, 0.001);
		auto bugScaleAction = EaseSineInOut::create(bugScaleActionAc->clone());
		_target->play(bugScaleAction);

		CallFunc *runCallback_closeLeaf = CallFunc::create(CC_CALLBACK_0(ShapesGame2::openLeafs, this));
		this->runAction(Sequence::create(DelayTime::create(2), runCallback_closeLeaf, nullptr));

	}
	else{
		touchBugKO();
		_target->flyOutCall();
	}
}


void ShapesGame2::fadeIn() {
	
	// Start fade in animations

    simpleAudioEngine->playEffect("ShapesGame2/audio/game_shape_feed_TATU.mp3");
    
	if (!test){
		//play help anim
		simpleAudioEngine->playEffect("ShapesGame2/audio/help.mp3");
		help->play("helpAnimation", ([=]() {		
			//on complete start anim of all object
			startAnimStartGame();
			help->getActionTimeline()->clearLastFrameCallFunc();
		}), false);
	}else{
		startAnimStartGame();
	}

	

	clickBug = EventListenerCustom::create("click_bug", [=](EventCustom* event){
		if (!gameFinished && !gamePaused){

			gamePaused = true;
			// CCLOG("click_bug");

			auto targ = static_cast<Bug*>(event->getUserData());

			targ->clicked = true;
		
			float touchX = targ->getPosition().x;
			float touchY = targ->getPosition().y;
			float tatuX = tatu->getPosition().x + tatu->getChild("BONE_MASTER")->getPosition().x + tatu->getChild("BONE_MASTER/HEAD_MASTER")->getPosition().x;
			float tatuY = tatu->getPosition().y + tatu->getChild("BONE_MASTER")->getPosition().y + tatu->getChild("BONE_MASTER/HEAD_MASTER")->getPosition().y;
			float radiusHand = -atan2(touchY - tatuY, touchX - tatuX);
			int angle = (radiusHand*180.0f / M_PI) + 180;

			if (angle > 60 && angle < 180)angle = 60;
			else if (angle < 340 && angle > 180)angle = 340;
			if (angle < 180)tatu->getChild("BONE_MASTER/bone_collo")->setRotation(angle / 2);
			else tatu->getChild("BONE_MASTER/bone_collo")->setRotation(angle);
			tatu->getChild("BONE_MASTER/HEAD_MASTER")->setRotation(angle);

			float distance = sqrt(pow(touchX - tatuX, 2) + pow(touchY - tatuY, 2));

			// CCLOG("ANGLE: %i --- DISTANCE: %f", angle, distance);

			ScaleTo *tongueScaleActionAc = ScaleTo::create(0.5, distance / 72, 1);
			auto tongueScaleAction = EaseSineInOut::create(tongueScaleActionAc->clone());
			tatu->getChild("BONE_MASTER/HEAD_MASTER/LINGUA_MASTER/bone_lingua")->runAction(tongueScaleAction);

			MoveTo *tongueMoveActionAc = MoveTo::create(0.5, Vec2(distance, 0));
			auto tongueMoveAction = EaseSineInOut::create(tongueMoveActionAc->clone());
			tatu->getChild("BONE_MASTER/HEAD_MASTER/LINGUA_MASTER/bone_Puntalig")->runAction(tongueMoveAction);

			
			tatu->play("tongue", ([=]() {
				//on complete start anim of all object
				tatu->play("stand", nullptr, true);
				tatu->getActionTimeline()->clearLastFrameCallFunc();
			}), false);


			if (targ->typeBug == validSimbol){
				simpleAudioEngine->playEffect("ShapesGame2/audio/LinguaBite.mp3");
				CallFunc *runCallback_tongueReturn = CallFunc::create(CC_CALLBACK_0(ShapesGame2::returnTongue, this, true, targ));
				this->runAction(Sequence::create(DelayTime::create(0.5), runCallback_tongueReturn, nullptr));
			}else{
                scorePercent -= scoreToSubtract;
                CCLOG("score ora vale %f", scorePercent);
                CCLOG("targ->typeBug = %d", targ->typeBug);
                CCLOG("validSimbol = %d", validSimbol);
                
				simpleAudioEngine->playEffect("ShapesGame2/audio/SlurpBite.mp3");
				CallFunc *runCallback_tongueReturn = CallFunc::create(CC_CALLBACK_0(ShapesGame2::returnTongue, this, false, targ));
				this->runAction(Sequence::create(DelayTime::create(0.5), runCallback_tongueReturn, nullptr));
				
			}
		}
	});
	_eventDispatcher->addEventListenerWithFixedPriority(clickBug, 1);

	deleteBug = EventListenerCustom::create("delete_bug", [=](EventCustom* event){
		auto targ = static_cast<Bug*>(event->getUserData());
		delete targ;
        //int arrayBugSize = (int)arrayBug.size();
		for (int i = (int)arrayBug.size()-1; i >= 0; i--){
			if (static_cast<Bug*>(arrayBug[i]) == targ){
                arrayBugToDelete.push_back( arrayBug[i] );
				arrayBug.erase(arrayBug.begin() + i);
			}
		}
	});
	_eventDispatcher->addEventListenerWithFixedPriority(deleteBug, 1);


	enableTouch();
}

void ShapesGame2::closeGame(bool isWinning){
    simpleAudioEngine->stopBackgroundMusic();
    DataProvider *dataProvider = DataProvider::getInstance();
    
    Logger::getInstance()->logEvent(NAME, Logger::CLOSE, "");
    if ( isWinning ) {
        dataProvider->setGameCompleted(NAME);
        dataProvider->setWatchmanReaction(WatchmanScene::GOOD_REACTION);
    } else {
        dataProvider->setWatchmanReaction(WatchmanScene::BAD_REACTION);
    }
    _director->replaceScene(TransitionFade::create(TRANSITION_TIME, WatchmanScene::createScene(), TRANSITION_COLOR));
}

void ShapesGame2::finishGame(bool _win){
    CCLOG(">>>> finish game");
	gameFinished = true;
	int arrayBugSize = (int)arrayBug.size();
	for (int i = arrayBugSize-1; i >= 0; i--){
		static_cast<Bug*>(arrayBug[i])->flyOut();
	}

	if (_win){
		//finish ok
        
        runAction(
            Sequence::createWithTwoActions(
                    DelayTime::create(1.5f),
                    CallFunc::create([=]() {
                        tatu->play("exit", ([=]() {
                            semaWell->bringToFront();
                            semaWell->play("intro", ([=]() {
                                closeGame(_win);
                                semaWell->getActionTimeline()->clearLastFrameCallFunc();
                            }));
                            tatu->getActionTimeline()->clearLastFrameCallFunc();
                        }));
                
                    })
            )
        );
        
	}
	else{
		//finish ko
		tatu->play("exit", ([=]() {
			semaTry->bringToFront();
            semaTry->play("intro", ([=]() {
                closeGame(_win);
                semaTry->getActionTimeline()->clearLastFrameCallFunc();
            }));
			tatu->getActionTimeline()->clearLastFrameCallFunc();
		}));
		
	}
}

void ShapesGame2::touchBugOK() {
	nLedOn++;
	arrayCounter[nLedOn-1]->play("turn_on", nullptr, false);
	if (nLedOn == 5)finishGame(true);
}

void ShapesGame2::touchBugKO() {
	gamePaused = false;
	nLedOn--;
	if (nLedOn < 0)finishGame(false);
	else arrayCounter[nLedOn]->play("turn_off", nullptr, false);
}

void ShapesGame2::showTutorial() {
}

void ShapesGame2::hideTutorial() {
}

bool ShapesGame2::onTouchBegan(Touch* touch, Event* event) {

	return true;
}

void ShapesGame2::onTouchMoved(Touch* touch, Event* event) {
	if (!gamePaused){
		// Manage a touch event
		// Manage the start of a touch event
		float touchX = touch->getLocation().x;
		float touchY = touch->getLocation().y;
		float tatuX = tatu->getPosition().x + tatu->getChild("BONE_MASTER")->getPosition().x + tatu->getChild("BONE_MASTER/HEAD_MASTER")->getPosition().x;
		float tatuY = tatu->getPosition().y + tatu->getChild("BONE_MASTER")->getPosition().y + tatu->getChild("BONE_MASTER/HEAD_MASTER")->getPosition().y;
		float radiusHand = -atan2(touchY - tatuY, touchX - tatuX);
		int angle = (radiusHand*180.0f / M_PI) + 180;

		if (angle > 60 && angle < 180)angle = 60;
		else if (angle < 340 && angle > 180)angle = 340;
		if (angle < 180)tatu->getChild("BONE_MASTER/bone_collo")->setRotation(angle / 2);
		else tatu->getChild("BONE_MASTER/bone_collo")->setRotation(angle);
		tatu->getChild("BONE_MASTER/HEAD_MASTER")->setRotation(angle);

		float distance = sqrt(pow(touchX - tatuX, 2) + pow(touchY - tatuY, 2));

		// CCLOG("ANGLE: %i --- DISTANCE: %f", angle, distance);
	}

//	tatu->getChild("BONE_MASTER/HEAD_MASTER/LINGUA_MASTER/bone_lingua")->setScaleX(distance/72);
//	tatu->getChild("BONE_MASTER/HEAD_MASTER/LINGUA_MASTER/bone_Puntalig")->setPosition(Vec2(distance, 0));

}


void ShapesGame2::onTouchEnded(Touch* touch, Event* event) {


}


void ShapesGame2::homeButtonPressed() {
	simpleAudioEngine->stopBackgroundMusic();
    DataProvider *dataProvider = DataProvider::getInstance();
    
    Logger::getInstance()->logEvent(NAME, Logger::CLOSE, "");
    if ( TEST_ENABLED ) {
        dataProvider->setGameCompleted(NAME);
        dataProvider->setWatchmanReaction(WatchmanScene::GOOD_REACTION);
    } else {
        dataProvider->setWatchmanReaction(WatchmanScene::BAD_REACTION);
    }
    _director->replaceScene(TransitionFade::create(TRANSITION_TIME, WatchmanScene::createScene(), TRANSITION_COLOR));
}

