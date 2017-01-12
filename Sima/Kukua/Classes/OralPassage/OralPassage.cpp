#include "OralPassage.h"
#include "../Utils/StringUtility.h"
#include "../Utils/Data/DataProvider.h"
#include "../Utils/Data/Logger.h"
#include "../AppMacros.h"
#include "../Utils/Data/ArabicHelper.h"

using namespace std;

template<> const bool kukua::Game<OralPassage>::USE_PHYSICS = false;										// Enable/disable physics
template<> const bool kukua::Game<OralPassage>::ENABLE_TOUCH = true;										// Used to disable tutorial on first touch and manage general touch events
template<> string kukua::Game<OralPassage>::PATH = "OralPassage/";									// Resources' subfolder path for this game
template<> const string kukua::Game<OralPassage>::BACKGROUND_MUSIC_FILENAME = "";							// Background music filename
template<> bool kukua::Game<OralPassage>::SHOWN_TUTORIAL = false;											// Used for showing tutorial on first execution, set to true only if tutorial is not needed
template<> Scene* kukua::Game<OralPassage>::scene = nullptr;
template<> const string kukua::Game<OralPassage>::NAME = "OralPassage";

OralPassage::~OralPassage() {

	CCLOG("~OralPassage");

	//destroy update schedular
	this->unscheduleUpdate();
    
    _eventDispatcher->removeEventListener(touchListener);
    
    delete textProvider;
    
    delete story;
    delete questPanel;
    delete sema;
    delete tree;
    delete tryagain;
    delete welldone;
    delete butterfly;
    delete hand;
    delete life1;
    delete life2;
    delete life3;
    
    delete button1;
    delete button2;
    delete button3;
    
}

void OralPassage::initText(){
    CCLOG("init text 1");
	
    int numQuestion = questCorrect + 1;
 
    
    string textQuest = textProvider->getQuestion(numQuestion);
 
    textAnswer1 = textProvider->getAnswer1Correct(numQuestion);
 
    string textAnswer2 = textProvider->getAnswer2(numQuestion);
    string textAnswer3 = textProvider->getAnswer3(numQuestion);
    
    
	int r = 1 + rand() % 6;

	if (r == 1) orderAns = { textAnswer1, textAnswer2, textAnswer3 };
	if (r == 2) orderAns = { textAnswer1, textAnswer3, textAnswer2 };
	if (r == 3) orderAns = { textAnswer2, textAnswer1, textAnswer3 };
	if (r == 4) orderAns = { textAnswer1, textAnswer3, textAnswer2 };
	if (r == 5) orderAns = { textAnswer3, textAnswer1, textAnswer2 };
	if (r == 6) orderAns = { textAnswer3, textAnswer2, textAnswer1 };

    
    questLabel->setString(textQuest);
    answer1Label->setString(orderAns.at(0));
    answer2Label->setString(orderAns.at(1));
    answer3Label->setString(orderAns.at(2));

	quest++;

}

void OralPassage::initVariables() {
  
	questCorrect = 0;
	lifes = 3;
	quest = 0;
	helpIsOpen = false;
	velocityButterfly = 15.0;
	rotationButterfly = 0.0;
	clikEnabled = false;
    
    textProvider = new OPTextProvider();

	audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
    
    scorePercent = 100.0f;
    scoreToSubtract = 33.0f;
    
}

void OralPassage::initAudio() {

	//audioEngine->playBackgroundMusic("OralPassage/audio/AmbienceWindyForestLoopEQ.mp3");
}


void OralPassage::initGameObjects() {

    int skin = DataProvider::getInstance()->getSkin();
    static_cast<Sprite*>(rootNode->getChildByName("cielo_1"))->setTexture(PATH+"PNG/FONDALE/cielo_" +  StringUtility::toString(skin) + ".png");
    
	//start schedular update
	this->scheduleUpdate();
	
	//create GameObject from stage obj

	story = new GameObject(*rootNode, "textbox", PATH + "CSD/box_narration.csb");
	questPanel = new GameObject(*rootNode, "pannello_domande", PATH + "CSD/question_menu.csb");
	sema = new GameObject(*rootNode, "Sema", PATH + "CSD/Sema.csb");
	tree = new GameObject(*rootNode, "tree", PATH + "CSD/tronco.csb");
	tryagain = new GameObject(*rootNode, "tryagain", PATH + "CSD/SEMA_Try.csb");
	welldone = new GameObject(*rootNode, "welldone", PATH + "CSD/SEMA_Well.csb");
	butterfly = new GameObject(*rootNode, "butterfly", PATH + "CSD/farfalla.csb");
	hand = new GameObject(*rootNode, "hand", PATH + "CSD/Manina_Help_select.csb");
	life1 = new GameObject(*rootNode, "life1", PATH + "CSD/Libro_Vita.csb");
	life2 = new GameObject(*rootNode, "life2", PATH + "CSD/Libro_Vita.csb");
	life3 = new GameObject(*rootNode, "life3", PATH + "CSD/Libro_Vita.csb");
	

	float winHeight = cocos2d::Director::getInstance()->getWinSize().height;
	life1->getNode().setPositionY(winHeight - 50);
	life2->getNode().setPositionY(winHeight - 50);
	life3->getNode().setPositionY(winHeight - 50);

	//auto boneMainAns1 = questPanel->getChild("panel_Master");
	auto boneMainAnsA = questPanel->getChild("panel_Master/Bone_Pan_A");
	auto boneMainAnsB = questPanel->getChild("panel_Master/Bone_pan_B");
	auto boneMainAnsC = questPanel->getChild("panel_Master/Bone_pan_C");

	button1 = new GameObject(*boneMainAnsA, Point(0, 0), PATH + "CSD/pan_A.csb");
	button2 = new GameObject(*boneMainAnsB, Point(0, 0), PATH + "CSD/pan_B.csb");
	button3 = new GameObject(*boneMainAnsC, Point(0, 0), PATH + "CSD/pan_C.csb");


	story->play("intro", ([&]() {
		helpIsOpen = true;
		story->getActionTimeline()->clearLastFrameCallFunc();
	}), false);


	//declare touch event
    touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(OralPassage::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(OralPassage::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(OralPassage::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, rootNode);

    /*
	story->bringToFront();
	life1->bringToFront();
	life2->bringToFront();
	life3->bringToFront();
    */
    
    longTextLabel = ArabicHelper::getInstance()->createLabel("", 46);
    longTextLabel->setVerticalAlignment(TextVAlignment::CENTER) ;
    longTextLabel->setHorizontalAlignment(TextHAlignment::RIGHT);
    longTextLabel->setColor(Color3B(0, 0, 0));
    longTextLabel->setWidth( 850.0 );
    longTextLabel->setHeight(700.0);
    story->getChild("Bone_fogliobase/Bone_scroll/Bone_text")->addChild(longTextLabel);
    
    questLabel = ArabicHelper::getInstance()->createLabel("", 50);
    questLabel->setColor(Color3B(26, 26, 26));
    questPanel->getChild("panel_Master/Bone_quest_mrnu")->addChild(questLabel);
    
    answer1Label = ArabicHelper::getInstance()->createLabel("", 40);
    answer1Label->setColor(Color3B(26, 26, 26));
    button1->getChild("Bone_pan_A")->addChild(answer1Label);
    
    answer2Label = ArabicHelper::getInstance()->createLabel("", 40);
    answer2Label->setColor(Color3B(26, 26, 26));
    button2->getChild("Bone_pan_A")->addChild(answer2Label);
    
    answer3Label = ArabicHelper::getInstance()->createLabel("", 40);
    answer3Label->setColor(Color3B(26, 26, 26));
    button3->getChild("Bone_pan_A")->addChild(answer3Label);

    longTextLabel->setString( textProvider->getStory() );
    
    story->bringToFront();
}




void OralPassage::fadeIn() {

	sema->play("sema_idle", nullptr, true);

	butterfly->play("fly", nullptr, true);

	life1->play("apparizione", nullptr, false);
	life2->play("apparizione", nullptr, false);
	life3->play("apparizione", nullptr, false);
	

	//DataProvider::getInstance()->updateCurrentStatusToNext();
	CCLOG("OralPassage - Fade in");
}


void OralPassage::showTutorial() {

}

void OralPassage::hideTutorial() {

}

bool OralPassage::onTouchBegan(Touch* touch, Event* event) {
	//CCLOG("CLICK");
	//auto text = story->getChild("Bone_fogliobase/Bone_scroll/Bone_text/Text_1");
	auto buttonOK = story->getChild("Bone_fogliobase/Bone_OK");
	auto boneMain = story->getChild("Bone_fogliobase");
	auto buttonUp = story->getChild("Bone_fogliobase/Bone_AR_up");
	auto buttonDw = story->getChild("Bone_fogliobase/Bone_AR_dw");
	//auto scroll = story->getChild("Bone_Indic_scorr");

	float buttonOKX = buttonOK->getPosition().x + boneMain->getPosition().x + story->getPosition().x;
	float buttonOKY = buttonOK->getPosition().y + boneMain->getPosition().y + story->getPosition().y;
	float buttonUpX = buttonUp->getPosition().x + boneMain->getPosition().x + story->getPosition().x;
	float buttonUpY = buttonUp->getPosition().y + boneMain->getPosition().y + story->getPosition().y;
	float buttonDwX = buttonDw->getPosition().x + boneMain->getPosition().x + story->getPosition().x;
	float buttonDwY = buttonDw->getPosition().y + boneMain->getPosition().y + story->getPosition().y;
	float touchX = touch->getLocation().x;
	float touchY = touch->getLocation().y;

	//CCLOG("CLICK %f %f", buttonOKX, touchX);



	//CLICK OK
	if (touchX > buttonOKX - 130 && touchX < buttonOKX + 130 && touchY > buttonOKY - 80 && touchY < buttonOKY + 80) {
		//CCLOG("CLICK BUTTON OK");
		string anim = "intro";
		if (helpIsOpen)anim = "exit";
		story->play(anim, ([&]() {
			if (helpIsOpen){
				openQuest();
				helpIsOpen = false;
			}
			else{
				closeQuest(false);
				helpIsOpen = true;
			}
			story->getActionTimeline()->clearLastFrameCallFunc();
		}), false);
	}

	//CLICK UP
	if (touchX > buttonUpX - 65 && touchX < buttonUpX + 65 && touchY > buttonUpY - 65 && touchY < buttonUpY + 65) {
		CCLOG("CLICK BUTTON UP");
		//	text->set
	}

	if (touchX > buttonDwX - 65 && touchX < buttonDwX + 65 && touchY > buttonDwY - 65 && touchY < buttonDwY + 65) {
		CCLOG("CLICK BUTTON DW");
	}

	auto boneMainAns1 = questPanel->getChild("panel_Master");
	auto boneMainAns2A = questPanel->getChild("panel_Master/Bone_Pan_A");
	auto boneMainAns2B = questPanel->getChild("panel_Master/Bone_pan_B");
	auto boneMainAns2C = questPanel->getChild("panel_Master/Bone_pan_C");
	auto ans1 = questPanel->getChild("panel_Master/Bone_Pan_A/Node_Panel_A");
	auto ans2 = questPanel->getChild("panel_Master/Bone_pan_B/Node_panel_B");
	auto ans3 = questPanel->getChild("panel_Master/Bone_pan_C/Node_panel_C");

	float buttonAns1X = ans1->getPosition().x + boneMainAns1->getPosition().x + boneMainAns2A->getPosition().x + questPanel->getPosition().x;
	float buttonAns1Y = ans1->getPosition().y + boneMainAns1->getPosition().y + boneMainAns2A->getPosition().y + questPanel->getPosition().y;
	float buttonAns2X = ans2->getPosition().x + boneMainAns1->getPosition().x + boneMainAns2B->getPosition().x + questPanel->getPosition().x;
	float buttonAns2Y = ans2->getPosition().y + boneMainAns1->getPosition().y + boneMainAns2B->getPosition().y + questPanel->getPosition().y;
	float buttonAns3X = ans3->getPosition().x + boneMainAns1->getPosition().x + boneMainAns2C->getPosition().x + questPanel->getPosition().x;
	float buttonAns3Y = ans3->getPosition().y + boneMainAns1->getPosition().y + boneMainAns2C->getPosition().y + questPanel->getPosition().y;
	
	if (clikEnabled){
			if (touchX > buttonAns1X - 310 && touchX < buttonAns1X + 310 && touchY > buttonAns1Y - 70 && touchY < buttonAns1Y + 70) {
				button1->play("panel_press", nullptr, false);
			}

		if (touchX > buttonAns2X - 310 && touchX < buttonAns2X + 310 && touchY > buttonAns2Y - 70 && touchY < buttonAns2Y + 70) {
			button2->play("panel_press", nullptr, false);
		}

		if (touchX > buttonAns3X - 310 && touchX < buttonAns3X + 310 && touchY > buttonAns3Y - 70 && touchY < buttonAns3Y + 70) {
			button3->play("panel_press", nullptr, false);
		}
	}
	
	return true;
}
/*

*/
void OralPassage::onTouchMoved(Touch* touch, Event* event) {
	
}


void OralPassage::onTouchEnded(Touch* touch, Event* event) {
	float touchX = touch->getLocation().x;
	float touchY = touch->getLocation().y;

	auto boneMainAns1 = questPanel->getChild("panel_Master");
	auto boneMainAns2A = questPanel->getChild("panel_Master/Bone_Pan_A");
	auto boneMainAns2B = questPanel->getChild("panel_Master/Bone_pan_B");
	auto boneMainAns2C = questPanel->getChild("panel_Master/Bone_pan_C");
	auto ans1 = questPanel->getChild("panel_Master/Bone_Pan_A/Node_Panel_A");
	auto ans2 = questPanel->getChild("panel_Master/Bone_pan_B/Node_panel_B");
	auto ans3 = questPanel->getChild("panel_Master/Bone_pan_C/Node_panel_C");

	float buttonAns1X = ans1->getPosition().x + boneMainAns1->getPosition().x + boneMainAns2A->getPosition().x + questPanel->getPosition().x;
	float buttonAns1Y = ans1->getPosition().y + boneMainAns1->getPosition().y + boneMainAns2A->getPosition().y + questPanel->getPosition().y;
	float buttonAns2X = ans2->getPosition().x + boneMainAns1->getPosition().x + boneMainAns2B->getPosition().x + questPanel->getPosition().x;
	float buttonAns2Y = ans2->getPosition().y + boneMainAns1->getPosition().y + boneMainAns2B->getPosition().y + questPanel->getPosition().y;
	float buttonAns3X = ans3->getPosition().x + boneMainAns1->getPosition().x + boneMainAns2C->getPosition().x + questPanel->getPosition().x;
	float buttonAns3Y = ans3->getPosition().y + boneMainAns1->getPosition().y + boneMainAns2C->getPosition().y + questPanel->getPosition().y;
	
	if (clikEnabled){
		if (touchX > buttonAns1X - 310 && touchX < buttonAns1X + 310 && touchY > buttonAns1Y - 70 && touchY < buttonAns1Y + 70) {
			button1->play("panel_release");
			CCLOG("CLICK BUTTON 1");
			checkResult(1);
		}

		if (touchX > buttonAns2X - 310 && touchX < buttonAns2X + 310 && touchY > buttonAns2Y - 70 && touchY < buttonAns2Y + 70) {
			button2->play("panel_release");
			CCLOG("CLICK BUTTON 2");
			checkResult(2);
		}

		if (touchX > buttonAns3X - 310 && touchX < buttonAns3X + 310 && touchY > buttonAns3Y - 70 && touchY < buttonAns3Y + 70) {
			button3->play("panel_release");
			CCLOG("CLICK BUTTON 3");
			checkResult(3);
		}
	}
}


void OralPassage::homeButtonPressed() {
    
    simpleAudioEngine->stopBackgroundMusic();

    Logger::getInstance()->logEvent(NAME, Logger::CLOSE, "");
    if ( TEST_ENABLED ) {
        DataProvider::getInstance()->setGameCompleted(NAME);
        DataProvider::getInstance()->setWatchmanReaction(WatchmanScene::GOOD_REACTION);
    } else {
        DataProvider::getInstance()->setWatchmanReaction(WatchmanScene::BAD_REACTION);
    }
    _director->replaceScene(TransitionFade::create(TRANSITION_TIME, WatchmanScene::createScene(), TRANSITION_COLOR));
    
}

/**/

void OralPassage::update(float delta) {
	


	velocityButterfly = velocityButterfly - 0.05f;
	if (velocityButterfly<1)velocityButterfly = 1.0f;

	//srand(time(NULL));
	int runAnt = velocityButterfly;
	int rv = rand() % 5 - 2;

	rotationButterfly = rotationButterfly + rv;
	float radiant = rotationButterfly / 180.0f * M_PI;

	float rot = static_cast<int>(rotationButterfly) % 360;

	//CCLOG("ANGOLO %f", rot);
	if (rot>270 || rot<90){
		butterfly->getNode().setScaleX(-1);
	} else{
		butterfly->getNode().setScaleX(1);
	}
	//butterfly->getNode().setRotation(-rotationButterfly + 90.0f);



	butterfly->setPosition(Vec2(butterfly->getPosition().x + std::cos(radiant) * runAnt, butterfly->getPosition().y + std::sin(radiant) * runAnt));


	if (butterfly->getPosition().x<-100 || butterfly->getPosition().x>(int(_director->getWinSize().width) + 100) || butterfly->getPosition().y<-100 || butterfly->getPosition().y>(int(_director->getWinSize().height) + 100)) {
		rotationButterfly = rotationButterfly + 180.0f;
	}
}



void OralPassage::openText(){
	
}

void OralPassage::closeText(){
	
}


void OralPassage::openQuest(){
    CCLOG("openQuest");
    
	initText();
	   
    CCLOG("openQuest - after initText");
	
    questPanel->play("Panel_Arrivo", ([&]() {

		CCLOG("Panel_Arrivo anim end");
		clikEnabled = true;
		if (quest == 1){
			hand->play("animation", nullptr, true);
			hand->setVisible(true);
		}
		questPanel->getActionTimeline()->clearLastFrameCallFunc();
	}), false);
}

void OralPassage::closeQuest(bool _new){
    CCLOG("closeQuest");
	clikEnabled = false;
	hand->setVisible(false);
	questPanel->play("panel_Out", ([&]() {
		
		if (questCorrect == 5){
			finishGame(true);
            questPanel->getActionTimeline()->clearLastFrameCallFunc();
		} else{
			if (_new && lifes>=0){
				openQuest();
            } else {
                questPanel->getActionTimeline()->clearLastFrameCallFunc();
            }
		}
	}), false);
}


void OralPassage::climbUp(){
	//MoveBy *treeMoveAction = MoveBy::create(4, Vec2(0,-950));
    MoveBy *treeMoveAction = MoveBy::create(4, Vec2(0,-750));
    
    
    sema->play("animation_climb", nullptr, true);
    
    CallFunc *stopSemaCallback = CallFunc::create(CC_CALLBACK_0(OralPassage::stopSema, this));
    Action *seq = Sequence::create(treeMoveAction,stopSemaCallback, nullptr);
    
	tree->play(seq);
}


void OralPassage::stopSema(){
    sema->play("sema_idle", nullptr, true);
}


void OralPassage::fall(){
    
	sema->play("feedback_negative", ([&]() {
		stopSema();
		sema->getActionTimeline()->clearLastFrameCallFunc();
	}), false);
  
}

void OralPassage::loseLife(){
	if (lifes == 3)life1->play("Perdita_vita", nullptr, false);
	if (lifes == 2)life2->play("Perdita_vita", nullptr, false);
	if (lifes == 1)life3->play("Perdita_vita", nullptr, false);
	if (lifes == 0)finishGame(false);
	lifes--;
    
    // subtract score
    scorePercent -= scoreToSubtract;
    CCLOG("lo score ora vale: %f", scorePercent);
}

void OralPassage::checkResult(int _id){

    string tappedAnswer = orderAns[_id - 1];
	if (tappedAnswer == textAnswer1) {
        CCLOG("correct!");
		questCorrect++;
		climbUp();
	}else{
        CCLOG("wrong!");
		loseLife();
		fall();
	}

	closeQuest(true);
}

void OralPassage::finishGame(bool _win) {
	if (_win){
		welldone->play("Well_Apparizione", ([&]() {
            closeGame(_win);
			sema->getActionTimeline()->clearLastFrameCallFunc();
		}));
	}
	else{
		tryagain->play("Try_Apparizione", ([&]() {
            closeGame(_win);
			sema->getActionTimeline()->clearLastFrameCallFunc();
		}));
	}
	
}

void OralPassage::closeGame(bool goodEnd) {
   
    simpleAudioEngine->stopBackgroundMusic();
    
    Logger::getInstance()->logEvent(NAME, Logger::CLOSE, "");
    if ( goodEnd ) {
        DataProvider::getInstance()->setGameCompleted(NAME);
        DataProvider::getInstance()->setWatchmanReaction(WatchmanScene::GOOD_REACTION);
    } else {
        DataProvider::getInstance()->setWatchmanReaction(WatchmanScene::BAD_REACTION);
    }
    _director->replaceScene(TransitionFade::create(TRANSITION_TIME, WatchmanScene::createScene(), TRANSITION_COLOR));
     
}
