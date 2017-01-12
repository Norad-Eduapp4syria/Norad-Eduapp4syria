#include "SentenceDictation.h"
#include "../Utils/Data/DataProvider.h"
#include "../Utils/Data/Logger.h"
#include "../WatchmanScene/WatchmanScene.h"
#include "../Utils/StringUtility.h"
#include "../AppMacros.h"

#include "../Utils/Data/ArabicHelper.h"
#include "../Utils/Data/ArabicHelperForGames.h"

using namespace std;

template<> const bool kukua::Game<SentenceDictation>::USE_PHYSICS = false;										// Enable/disable physics
template<> const bool kukua::Game<SentenceDictation>::ENABLE_TOUCH = false;										// Used to disable tutorial on first touch and manage general touch events
template<> string kukua::Game<SentenceDictation>::PATH = "WordDictation/";											// Resources' subfolder path for this game
template<> const string kukua::Game<SentenceDictation>::BACKGROUND_MUSIC_FILENAME = "";							// Background music filename
template<> bool kukua::Game<SentenceDictation>::SHOWN_TUTORIAL = false;											// Used for showing tutorial on first execution, set to true only if tutorial is not needed
template<> Scene* kukua::Game<SentenceDictation>::scene = nullptr;
//template<> const string kukua::Game<SentenceDictation>::NAME = "SentenceDictation";
std::string SentenceDictation::NAME = ""; // To set

SentenceDictation::~SentenceDictation() {

	CCLOG("~SentenceDictation");
    _eventDispatcher->removeEventListener(clickButton);
    delete tatu;
    delete leterBox;
    delete keyboard;
    delete backGround;
    
    for (vector<GameObject*>::iterator iterator = arrayCharBox.begin(); iterator != arrayCharBox.end(); ++iterator) {
        delete (*iterator);
    }
    
    if (letter != nullptr) delete letter;
    
}



void SentenceDictation::initVariables() {
	lowercase = true;
    score = 100.0;
	charActive = -1;
	inPauseInsert = false;

    letter = nullptr;
    line = 1;
    spaceCounter = 0;
    ///
    
    vector<string> wordsVector = DataProvider::getInstance()->getVectorWordsForGame(); // RIMETTERE

    for (vector<string>::iterator iterator = wordsVector.begin(); iterator != wordsVector.end(); ++iterator) {
        //    (*iterator)
        CCLOG("parole = %s", (*iterator).c_str() );
    }
    if ( wordsVector.empty() ) {
        CCLOG("ho finito...devo tornare al watchman.. non dovrebbe mai succedere");
        return;
    }
    string word = wordsVector.back(); // get the last word
    
    word = ArabicHelperForGames::getInstance()->getInArabic_sentenceDictation(word);
    
    // changes to word
    /*word = StringUtility::toLowerCase(word);
    string lastChar = &word.back();
    if (lastChar == ".") word.pop_back(); // remove last .
    */
    
    wordArray = StringUtility::split(word, '#');
    
    CCLOG("word = %s", word.c_str());
    
    
    //from db
    //word = "i#n#m";
    
    word.erase(std::remove(word.begin(), word.end(), '#'), word.end()); // remove # char
    
    wordToRead = word;
    
    useCapitalLetters = false;
    
    ///
	//int remainingWidth = (int)(1280 - 430 - (word.size() * 140));
    //remWidthRef = 430 + (remainingWidth / 2);

	pathLetters = "LettersGame/";

	progreLetter = 0;
	stateInteraction = 3; // 0=ready 1=progress 2=cancellation 3=changestep or finish
}


void SentenceDictation::initAudio() {
    
    simpleAudioEngine->preloadBackgroundMusic("common/audio/bg/GAME_2.mp3");
    simpleAudioEngine->playBackgroundMusic("common/audio/bg/GAME_2.mp3", true);
    
}


void SentenceDictation::toFront(Node* _child, Node* _parent) {
	if (_parent == nullptr) _parent = static_cast<Node*>(_child->getParent());
	_child->retain();
	_child->removeFromParent();
	_parent->addChild(_child);
	_child->release();
}


void SentenceDictation::initGameObjects() {

	tatu = new GameObject(*rootNode, "Tatu_Welldone", PATH + "CSD/TATU_Well.csb");
	leterBox = new GameObject(*rootNode, Vec2(_director->getWinSize().width / 2, _director->getWinSize().height / 2), PATH + "CSD/board.csb");
	keyboard = new Keyboard(*rootNode, Vec2(0, 0), lowercase, _eventDispatcher);
	
    int skin = DataProvider::getInstance()->getSkin();
    string skinStr = StringUtility::toString(skin);
    
    backGround = new GameObject(*rootNode->getChildByName("FondaleRef"), Vec2::ZERO, PATH + "CSD/Background_Composition_skin"+skinStr+".csb");

}





void SentenceDictation::fadeIn() {
	//DataProvider::getInstance()->updateCurrentStatusToNext();
	CCLOG("SentenceDictation - Fade in");

	//keyboard->play("intro", nullptr, false);

    playAudioWord();
    
	backGround->play("composition", ([=]() {
		createWord();
		backGround->getActionTimeline()->clearLastFrameCallFunc();
	}), false);

	clickButton = EventListenerCustom::create("keyboard_click_button", [=](EventCustom* event){
		if (!inPauseInsert){
			auto targ = static_cast<KeyboardButton*>(event->getUserData());
			string name = targ->name;
			CCLOG("KeyboardButton - onTouchBegan %s", name.c_str());
			if (name == "space" || name == "canc"){
				setChar(charActive, "");
			}
			else if (name == "enter"){
				/*charActive = -1;
				keyboard->play("exit", nullptr, false);
				for (int j = 0; j < arrayCharBox.size(); j++) {
				auto objectBack = static_cast<Sprite*>(arrayCharBox[j]->getChild("Bone_box_font/box_font"));
				objectBack->setOpacity(255);
				}*/
			}
			else{
				setChar(charActive, targ->editText);
			}
		}
	});
	_eventDispatcher->addEventListenerWithFixedPriority(clickButton, 1);
    
    addListenButton();
}


void SentenceDictation::createWord(){
    xPosIndex = 0;
	for (int i = 0; i < wordArray.size(); i++){
        string c = wordArray.at(i); //.substr(i, 1);
		//CCLOG("lettera %i: %s", i, c.c_str());
		
		createChar(i,c);
	}
	CallFunc *runCallback_start = CallFunc::create(CC_CALLBACK_0(SentenceDictation::startGame, this));
	this->runAction(Sequence::create(DelayTime::create(0.5), runCallback_start, nullptr));
}

void SentenceDictation::createChar(int _id,string _char){
    float yPos = 0;
    if (line == 1) yPos = 680;
    else if (line == 2) yPos = 580;
    else if (line == 3) yPos = 480;
    
    //float xPos = remWidthRef + ( 140 * xPosIndex );
    float xPos = 1000 - ( 100 * xPosIndex );
    if (_char == " ") xPos -= 50;
    xPosIndex++;
    
	auto charBox = new GameObject(*rootNode, Vec2( xPos, yPos), PATH + "CSD/Box_carattere.csb");
    charBox->setScale(0.7);
    if (_char == " ") {
        spaceCounter++;
        charBox->getChild("Bone_box_font")->setVisible(false);
        charBox->getChild("Bone_spirale")->setVisible(false);
        if ( (spaceCounter % 2) == 0) {
            spaceCounter = 0;
            line++;
            xPosIndex = 0;
        }
    }
	auto label = static_cast<cocos2d::ui::Text*>(charBox->getChild("Bone_box_font/Text_1"));
	label->setString("");
	charBox->play("Lett_IN", nullptr, false);
	arrayCharBox.push_back(charBox);
}

void SentenceDictation::setChar(int _id, string _char){
	auto label = static_cast<cocos2d::ui::Text*>(arrayCharBox[_id]->getChild("Bone_box_font/Text_1"));
	label->setString( ArabicHelper::getInstance()->getInArabic(_char));
	if (_char != ""){
		inPauseInsert = true;
		CallFunc *runCallback_start = CallFunc::create(CC_CALLBACK_0(SentenceDictation::checkChar, this));
		this->runAction(Sequence::create(DelayTime::create(0.3), runCallback_start, nullptr));
	}
}


void SentenceDictation::startGame(){
	charActive = 0;
	selectBox(charActive);
	keyboard->play("intro", nullptr, false);
}


void SentenceDictation::checkChar(){
    CCLOG("..checkChar..");
	bool correct = false;
	auto label = static_cast<cocos2d::ui::Text*>(arrayCharBox[charActive]->getChild("Bone_box_font/Text_1"));
	string c1 = label->getString();
	string c2 = wordArray.at(charActive); //.substr(charActive, 1);
    CCLOG("c1 = %s", c1.c_str());
    CCLOG("c2 = %s", c2.c_str());
    CCLOG("charActive = %d", charActive);
    // CCLOG("word = %s", word.c_str());
	if (c1 == c2){
		correct = true;
	}
	
	if (correct){
		arrayCharBox[charActive]->bringToFront();
		arrayCharBox[charActive]->play("Lett_OK", ([=]() {
			inPauseInsert = false;
			backGround->getActionTimeline()->clearLastFrameCallFunc();
		}), false);
		
        charActive++;
        
		if (wordArray.size() == charActive){
			selectBox(-1);
			keyboard->play("exit", nullptr, false);
			finishFase1();
		}else{
            
            string spaceCheck = wordArray.at(charActive); //.substr(charActive, 1);
            if (spaceCheck == " " ) charActive++;
            
			selectBox(charActive);
		}
	}
	else{
		arrayCharBox[charActive]->play("Lett_NO", ([=]() {
            score -= 5;
			setChar(charActive, "");
			inPauseInsert = false;
			backGround->getActionTimeline()->clearLastFrameCallFunc();
		}), false);
	}
}
void SentenceDictation::selectBox(int _id) {
	for (int j = 0; j < arrayCharBox.size(); j++) {
		auto objectBack1 = static_cast<Sprite*>(arrayCharBox[j]->getChild("Bone_box_font/box_front/box_front"));
		auto objectBack2 = static_cast<Sprite*>(arrayCharBox[j]->getChild("Bone_box_font/box_ok/box_ok"));
		auto objectBack3 = static_cast<Sprite*>(arrayCharBox[j]->getChild("Bone_box_font/box_select/box_select"));
		objectBack1->setVisible(true);
		objectBack2->setVisible(false);
		objectBack3->setVisible(false);
	}
	if (_id != -1){
		auto objectBack = static_cast<Sprite*>(arrayCharBox[_id]->getChild("Bone_box_font/box_select/box_select"));
		objectBack->setVisible(true);
	}
}

void SentenceDictation::finishFase1() {
	CCLOG("finishFase1");
/*
	for (int j = 0; j < arrayCharBox.size(); j++) {

		MoveBy *letterMoveActionAc = MoveBy::create(1,Vec2(-200, 0));
		auto letterMoveAction = EaseSineInOut::create(letterMoveActionAc->clone());
		arrayCharBox[j]->play(letterMoveAction);
	}
*/
    
    finisGame();
}



void SentenceDictation::showTutorial() {

}

void SentenceDictation::hideTutorial() {



}


void SentenceDictation::homeButtonPressed() {
	simpleAudioEngine->stopBackgroundMusic();
    
    Logger::getInstance()->logEvent(NAME, Logger::CLOSE, "");
    if ( TEST_ENABLED ) {
        DataProvider::getInstance()->setGameCompleted(NAME, score);
        DataProvider::getInstance()->setWatchmanReaction(WatchmanScene::GOOD_REACTION);
    } else {
        DataProvider::getInstance()->setWatchmanReaction(WatchmanScene::BAD_REACTION);
    }
    
}



void SentenceDictation::update(float delta) {
	CCLOG("stateInteraction: %i", stateInteraction);
}



void SentenceDictation::finisGame(){
	CCLOG("FINISH");
	tatu->play("Try_Apparizione", ([=]() {
        vector<string> wordsVector = DataProvider::getInstance()->getVectorWordsForGame();
        wordsVector.pop_back();
        if ( wordsVector.empty() ) {
            DataProvider::getInstance()->setGameCompleted(NAME, score);
            DataProvider::getInstance()->setWatchmanReaction(WatchmanScene::GOOD_REACTION);
            Logger::getInstance()->logEvent(NAME, Logger::WIN, "");
            Logger::getInstance()->logEvent(NAME, Logger::CLOSE, "");
            _director->replaceScene(TransitionFade::create(TRANSITION_TIME, WatchmanScene::createScene(), TRANSITION_COLOR));
            tatu->getActionTimeline()->clearLastFrameCallFunc();
            return;
        }
        DataProvider::getInstance()->setVectorWordsForGame(wordsVector);
        Logger::getInstance()->logEvent(NAME, Logger::CLOSE, "");
        _director->replaceScene(TransitionFade::create(TRANSITION_TIME, SentenceDictation::createScene(), TRANSITION_COLOR));
        tatu->getActionTimeline()->clearLastFrameCallFunc();
    }), false);
        
}


void SentenceDictation::playLetters(string _path){

	//CCLOG("AUDIO PHONEMA: %s %s", ("common/audio/" + _path + "/phonemes/" + phoneme + ".mp3").c_str(), phoneme.c_str());
	simpleAudioEngine->playEffect(("common/audio/" + _path + "/phonemes/" + phoneme + ".mp3").c_str());
}

bool SentenceDictation::onTouchBegan(Touch* touch, Event* event) {
    return true;
}
void SentenceDictation::onTouchMoved(Touch* touch, Event* event) {
}
void SentenceDictation::onTouchEnded(Touch* touch, Event* event) {
}


void SentenceDictation::addListenButton(){
    
    
    auto backNode = cocos2d::ui::Button::create(PATH+"PNG/listen_button.png", PATH+"PNG/listen_button.png", PATH+"PNG/listen_button.png");
    
    auto frameSize = cocos2d::Director::getInstance()->getWinSize();
    auto x = frameSize.width - 90;//frameSize.width * 0.5f;
    auto y = frameSize.height * 0.9f;
    backNode->setOpacity(0);
    backNode->setPosition(Vec2(x,y));
    addChild(backNode, 10);
    backNode->runAction(FadeIn::create(0.4f));
    
    
    backNode->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                playAudioWord();
                break;
            default:
                break;
        }
    });
    
}

void SentenceDictation::playAudioWord()
{
    CCLOG("SD playAudioWord - wordToRead = %s ", wordToRead.c_str());
  
    string sentenceToRead = ArabicHelperForGames::getInstance()->getFilenameInEnglish_sentenceDictation(wordToRead);
    CCLOG("sentenceToRead = %s", sentenceToRead.c_str());
    
    //string sentenceToRead = wordToRead;
    
    std::replace( sentenceToRead.begin(), sentenceToRead.end(), ' ', '_'); // replace all ' ' to '_'
    sentenceToRead = StringUtility::toLowerCase(sentenceToRead);
    
      CCLOG("sentenceToRead file = %s", sentenceToRead.c_str());
    
    
    simpleAudioEngine->playEffect((PATH + "audio/sentences/"+ sentenceToRead + ".mp3").c_str());
  
}

