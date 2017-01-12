#include "WordDictation.h"
#include "../Utils/Data/DataProvider.h"
#include "../Utils/Data/Logger.h"
#include "../WatchmanScene/WatchmanScene.h"
#include "../Utils/StringUtility.h"
#include "../AppMacros.h"

#include "../Utils/Data/ArabicHelper.h"
#include "../Utils/Data/ArabicHelperForGames.h"


using namespace std;

template<> const bool kukua::Game<WordDictation>::USE_PHYSICS = false;										// Enable/disable physics
template<> const bool kukua::Game<WordDictation>::ENABLE_TOUCH = true;										// Used to disable tutorial on first touch and manage general touch events
template<> string kukua::Game<WordDictation>::PATH = "WordDictation/";											// Resources' subfolder path for this game
template<> const string kukua::Game<WordDictation>::BACKGROUND_MUSIC_FILENAME = "";							// Background music filename
template<> bool kukua::Game<WordDictation>::SHOWN_TUTORIAL = false;											// Used for showing tutorial on first execution, set to true only if tutorial is not needed
template<> Scene* kukua::Game<WordDictation>::scene = nullptr;
//template<> const string kukua::Game<WordDictation>::NAME = "WordDictation";
std::string WordDictation::NAME = ""; // To set

WordDictation::~WordDictation() {

	CCLOG("~WordDictation");
    _eventDispatcher->removeEventListener(clickButton);
    delete tatu;
    delete leterBox;
    delete wordBox;
    delete keyboard;
    delete backGround;
    
    for (vector<GameObject*>::iterator iterator = arrayCharBox.begin(); iterator != arrayCharBox.end(); ++iterator) {
        delete (*iterator);
    }
    
    for (vector<GameObject*>::iterator iterator = arrayAllShape.begin(); iterator != arrayAllShape.end(); ++iterator) {
        delete (*iterator);
    }
    
    if (letter != nullptr) delete letter;
    
}



void WordDictation::initVariables() {
	lowercase = true;
    score = 100.0;
	charActive = -1;
	inPauseInsert = false;

    letter = nullptr;
    
    ///
    vector<string> wordsVector = DataProvider::getInstance()->getVectorWordsForGame();
    
    /* togliere
    vector<string> wordsVector;
    wordsVector.push_back("ب#ا#ص");
    */
    
    
    if ( wordsVector.empty() ) {
        CCLOG("ho finito...devo tornare al watchman.. non dovrebbe mai succedere");
        return;
    }
    string word = wordsVector.back(); // get the last word
    
    word = ArabicHelperForGames::getInstance()->getInArabic_wordDictation(word);
    
    CCLOG("word = %s", word.c_str());
    wordArray = StringUtility::split(word, '#');
    
    //from db
    //word = "i#n#m";
    
    word.erase(std::remove(word.begin(), word.end(), '#'), word.end()); // remove # char
    
    wordInArabic = word;
    
    
    useCapitalLetters = false;
   
    ///
    remainingWidth = 210;// (int)(1280 - 430 - (word.size() * 140));


	pathLetters = "LettersGame/";

	progreLetter = 0;
	stateInteraction = 3; // 0=ready 1=progress 2=cancellation 3=changestep or finish
}

void WordDictation::selectLetter(){
	arrayPoint = {};

	step = 0;
	actualStep = 0;
	actualShape = 0;

	typeSymbol = 1 + rand() % 3;

    phoneme = wordArray.at(progreLetter); // word.substr(progreLetter, 1);


    phoneme = ArabicHelper::getInstance()->getInLetter(phoneme);
    
//	abcdefghilmnopqrstuvzxkjwy


    // ep. 2
    
    if (phoneme == "a_initial") letterID = 0;
    if (phoneme == "a_medial")  letterID = 1;
    if (phoneme == "a_final")   letterID = 2;
    if (phoneme == "b_initial") letterID = 3;
    if (phoneme == "b_medial")  letterID = 4;
    if (phoneme == "b_final")   letterID = 5;
    if (phoneme == "t_initial") letterID = 6;
    if (phoneme == "t_medial")  letterID = 7;
    if (phoneme == "t_final")   letterID = 8;
    if (phoneme == "th_initial") letterID = 9;
    if (phoneme == "th_medial")  letterID = 10;
    if (phoneme == "th_final")   letterID = 11;
    if (phoneme == "g_initial") letterID = 12;
    if (phoneme == "g_medial")  letterID = 13;
    if (phoneme == "g_final")   letterID = 14;
    if (phoneme == "ha_initial") letterID = 15;
    if (phoneme == "ha_medial")  letterID = 16;
    if (phoneme == "ha_final")   letterID = 17;
    if (phoneme == "ja_initial") letterID = 18;
    if (phoneme == "ja_medial")  letterID = 19;
    if (phoneme == "ja_final")   letterID = 20;
    if (phoneme == "d_initial") letterID = 21;
    if (phoneme == "d_medial")  letterID = 22;
    if (phoneme == "d_final")   letterID = 23;
    if (phoneme == "dh_initial") letterID = 24;
    if (phoneme == "dh_medial")  letterID = 25;
    if (phoneme == "dh_final")   letterID = 26;
    if (phoneme == "r_initial") letterID = 27;
    if (phoneme == "r_medial")  letterID = 28;
    if (phoneme == "r_final")   letterID = 29;
    if (phoneme == "z_initial") letterID = 30;
    if (phoneme == "z_medial")  letterID = 31;
    if (phoneme == "z_final")   letterID = 32;
    if (phoneme == "s_initial") letterID = 33;
    if (phoneme == "s_medial")  letterID = 34;
    if (phoneme == "s_final")   letterID = 35;
    if (phoneme == "sh_initial") letterID = 36;
    if (phoneme == "sh_medial")  letterID = 37;
    if (phoneme == "sh_final")   letterID = 38;
    if (phoneme == "sad_initial") letterID = 39;
    if (phoneme == "sad_medial")  letterID = 40;
    if (phoneme == "sad_final")   letterID = 41;
    if (phoneme == "daad_initial") letterID = 42;
    if (phoneme == "daad_medial")  letterID = 43;
    if (phoneme == "daad_final")   letterID = 44;
    if (phoneme == "taa_initial") letterID = 45;
    if (phoneme == "taa_medial")  letterID = 46;
    if (phoneme == "taa_final")   letterID = 47;
    if (phoneme == "zaa_initial") letterID = 48;
    if (phoneme == "zaa_medial")  letterID = 49;
    if (phoneme == "zaa_final")   letterID = 50;
    if (phoneme == "aa_initial") letterID = 51;
    if (phoneme == "aa_medial")  letterID = 52;
    if (phoneme == "aa_final")   letterID = 53;
    if (phoneme == "gh_initial") letterID = 54;
    if (phoneme == "gh_medial")  letterID = 55;
    if (phoneme == "gh_final")   letterID = 56;
    if (phoneme == "f_initial") letterID = 57;
    if (phoneme == "f_medial")  letterID = 58;
    if (phoneme == "f_final")   letterID = 59;
    if (phoneme == "q_initial") letterID = 60;
    if (phoneme == "q_medial")  letterID = 61;
    if (phoneme == "q_final")   letterID = 62;
    if (phoneme == "k_initial") letterID = 63;
    if (phoneme == "k_medial")  letterID = 64;
    if (phoneme == "k_final")   letterID = 65;
    if (phoneme == "l_initial") letterID = 66;
    if (phoneme == "l_medial")  letterID = 67;
    if (phoneme == "l_final")   letterID = 68;
    if (phoneme == "m_initial") letterID = 69;
    if (phoneme == "m_medial")  letterID = 70;
    if (phoneme == "m_final")   letterID = 71;
    if (phoneme == "n_initial") letterID = 72;
    if (phoneme == "n_medial")  letterID = 73;
    if (phoneme == "n_final")   letterID = 74;
    if (phoneme == "h_initial") letterID = 75;
    if (phoneme == "h_medial")  letterID = 76;
    if (phoneme == "h_final")   letterID = 77;
    if (phoneme == "w_initial") letterID = 78;
    if (phoneme == "w_medial")  letterID = 79;
    if (phoneme == "w_final")   letterID = 80;
    if (phoneme == "y_initial") letterID = 81;
    if (phoneme == "y_medial")  letterID = 82;
    if (phoneme == "y_final")   letterID = 83;
    
    // ep 1
    
    if (phoneme == "a")letterID = 84;
    if (phoneme == "b")letterID = 85;
    if (phoneme == "t")letterID = 86;
    if (phoneme == "th")letterID = 87;
    if (phoneme == "g")letterID = 88;
    if (phoneme == "ha")letterID = 89;
    if (phoneme == "ja")letterID = 90;
    if (phoneme == "d")letterID = 91;
    if (phoneme == "dh")letterID = 92;
    if (phoneme == "r")letterID = 93;
    if (phoneme == "z")letterID = 94;
    
    if (phoneme == "s")letterID = 95;
    if (phoneme == "sh")letterID = 96;
    if (phoneme == "sad")letterID = 97;
    if (phoneme == "daad")letterID = 98;
    if (phoneme == "taa")letterID = 99;
    if (phoneme == "zaa")letterID = 100;
    if (phoneme == "aa")letterID = 101;
    if (phoneme == "gh")letterID = 102;
    if (phoneme == "f")letterID = 103;
    if (phoneme == "q")letterID = 104;
    
    if (phoneme == "k")letterID = 105;
    if (phoneme == "l")letterID = 106;
    if (phoneme == "m")letterID = 107;
    if (phoneme == "n")letterID = 108;
    if (phoneme == "h")letterID = 109;
    if (phoneme == "w")letterID = 110;
    if (phoneme == "y")letterID = 111;
    
    
    
    
    // ep 2
    
    arrayConfigLetter.push_back({ { 1,8 }}); //a_initial
    arrayConfigLetter.push_back({ { 1,8 }}); //a_medial
    arrayConfigLetter.push_back({ { 1,8 }}); //a_final
    
    arrayConfigLetter.push_back({ { 1,6 }, { 7,7 } }); //b_initial
    arrayConfigLetter.push_back({ { 1,9 }, { 10,10 } }); //b_medial
    arrayConfigLetter.push_back({ { 1,17 }, { 18,18 } }); //b_medial
    
    arrayConfigLetter.push_back({ { 1,7 }, { 8,8 }, { 9,9 } }); //t_initial
    arrayConfigLetter.push_back({ { 1,8 }, { 9,9 }, { 10,10 } }); //t_medial
    arrayConfigLetter.push_back({ { 1,15 }, { 16,16 }, { 17,17 } }); //t_final
    
    arrayConfigLetter.push_back({ { 1,7 }, { 8,8 }, { 9,9 }, { 10,10 } }); //th_initial
    arrayConfigLetter.push_back({ { 1,7 }, { 8,8 }, { 9,9 }, { 10,10 } }); //th_medial
    arrayConfigLetter.push_back({ { 1,18 }, { 19,19 }, { 20,20 }, { 21,21 } }); //th_final
    
    arrayConfigLetter.push_back({ { 1,14 }, { 15,15 } }); //g_initial
    arrayConfigLetter.push_back({ { 1,3 }, { 4,11 }, { 12,18 }, { 19,19 } }); //g_medial
    arrayConfigLetter.push_back({ { 1,27 }, { 28,28 } }); //g_final
    
    arrayConfigLetter.push_back({ { 1,15 }}); //ha_initial
    arrayConfigLetter.push_back({ { 1,3 }, { 4,11 }, { 12,18 } }); //ha_medial
    arrayConfigLetter.push_back({ { 1,3 }, { 4,30 } }); //ha_final
    
    arrayConfigLetter.push_back({ { 1,15 }, { 16,16 } }); //ja_initial
    arrayConfigLetter.push_back({ { 1,3 }, { 4,11 }, { 12,18 }, { 19,19 } }); //ja_medial
    arrayConfigLetter.push_back({ { 1,3 }, { 4,30 }, { 31,31 } }); //ja_final
    
    arrayConfigLetter.push_back({ { 1,12 }}); //d_initial
    arrayConfigLetter.push_back({ { 1,13 }}); //d_medial
    arrayConfigLetter.push_back({ { 1,12 }}); //d_final
    
    arrayConfigLetter.push_back({ { 1,12 }, { 13,13 } }); //dh_initial
    arrayConfigLetter.push_back({ { 1,13 }, { 14,14 } }); //dh_medial
    arrayConfigLetter.push_back({ { 1,12 }, { 13,13 } }); //dh_final
    
    arrayConfigLetter.push_back({ { 1,10 }}); //r_initial
    arrayConfigLetter.push_back({ { 1,11 }}); //r_medial
    arrayConfigLetter.push_back({ { 1,11 }}); //r_medial
    
    arrayConfigLetter.push_back({ { 1,10 }, { 11,11 } }); //z_initial
    arrayConfigLetter.push_back({ { 1,11 }, { 12,12 } }); //z_medial
    arrayConfigLetter.push_back({ { 1,10 }, { 11,11 } }); //z_medial
    
    arrayConfigLetter.push_back({ { 1,17 }}); //s_initial
    arrayConfigLetter.push_back({ { 1,17 }}); //s_medial
    arrayConfigLetter.push_back({ { 1,23 }}); //s_final
    
    arrayConfigLetter.push_back({ { 1,17 }, { 18,18 }, { 19,19 }, { 20,20 } }); //sh_initial
    arrayConfigLetter.push_back({ { 1,20 }, { 21,21 }, { 22,22 }, { 23,23 } }); //sh_medial
    arrayConfigLetter.push_back({ { 1,25 }, { 26,26 }, { 27,27 }, { 28,28 } }); //sh_final
    
    arrayConfigLetter.push_back({ { 1,18 }}); //sad_initial
    arrayConfigLetter.push_back({ { 1,2 }, { 3,23 } }); //sad_medial
    arrayConfigLetter.push_back({ { 1,26 }}); //sad_final
    
    arrayConfigLetter.push_back({ { 1,28 }, { 29,30 } }); //daad_initial
    arrayConfigLetter.push_back({ { 1,2 }, { 3,28 }, { 29,30 } }); //daad_medial
    arrayConfigLetter.push_back({ { 1,2 }, { 3,37 }, { 38,39 } }); //daad_final
    
    arrayConfigLetter.push_back({ { 1,32 } }); //taa_initial
    arrayConfigLetter.push_back({ { 1,2 }, { 3,33 } }); //taa_medial
    arrayConfigLetter.push_back({ { 1,39 } }); //taa_final
    
    arrayConfigLetter.push_back({ { 1,32 }, { 33,34 } }); //zaa_initial
    arrayConfigLetter.push_back({ { 1,2 }, { 3,33 }, { 34,35 } }); //zaa_medial
    arrayConfigLetter.push_back({ { 1,2 }, { 3,41 }, { 42,43 } }); //zaa_final
    
    arrayConfigLetter.push_back({ { 1,23 } }); //aa_initial
    arrayConfigLetter.push_back({ { 1,25 } }); //aa_medial
    arrayConfigLetter.push_back({ { 1,33 } }); //aa_final
    
    arrayConfigLetter.push_back({ { 1,23 }, { 24,25 } }); //gh_initial
    arrayConfigLetter.push_back({ { 1,26 }, { 27,28 } }); //gh_medial
    arrayConfigLetter.push_back({ { 1,36 }, { 37,38 } }); //gh_final
    
    arrayConfigLetter.push_back({ { 1,24 }, { 25,26 } }); //f_initial
    arrayConfigLetter.push_back({ { 1,24 }, { 25,26 } }); //f_medial
    arrayConfigLetter.push_back({ { 1,35 }, { 36,37 } }); //f_final
    
    arrayConfigLetter.push_back({ { 1,24 }, { 25,26 }, { 27,28 } }); //q_initial
    arrayConfigLetter.push_back({ { 1,24 }, { 25,26 }, { 27,28 } }); //q_medial
    arrayConfigLetter.push_back({ { 1,34 }, { 35,36 }, { 37,38 } }); //q_medial
    
    arrayConfigLetter.push_back({ { 1,10 }, { 11,47 } }); //k_initial
    arrayConfigLetter.push_back({ { 1,10 }, { 11,22 } }); //k_medial
    arrayConfigLetter.push_back({ { 1,23 }, { 24,34 } }); //k_final
    
    arrayConfigLetter.push_back({ { 1,15 } }); //l_initial
    arrayConfigLetter.push_back({ { 1,28 } }); //l_medial
    arrayConfigLetter.push_back({ { 1,24 } }); //l_final
    
    arrayConfigLetter.push_back({ { 1,32 } }); //m_initial
    arrayConfigLetter.push_back({ { 1,34 } }); //m_medial
    arrayConfigLetter.push_back({ { 1,47 } }); //m_final
    
    arrayConfigLetter.push_back({ { 1,11 }, { 12,13 } }); //n_initial
    arrayConfigLetter.push_back({ { 1,14 }, { 15,16 } }); //n_medial
    arrayConfigLetter.push_back({ { 1,20 }, { 21,22 } }); //n_final
    
    arrayConfigLetter.push_back({ { 1,37 } }); //h_initial
    arrayConfigLetter.push_back({ { 1,57 } }); //h_medial
    arrayConfigLetter.push_back({ { 1,13 }, { 14,27 } }); //h_final
    
    arrayConfigLetter.push_back({ { 1,28 } }); //w_initial
    arrayConfigLetter.push_back({ { 1,28 } }); //w_medial
    arrayConfigLetter.push_back({ { 1,28 } }); //w_final
    
    arrayConfigLetter.push_back({ { 1,8 }, { 9,9 }, { 10,10 } }); //y_initial
    arrayConfigLetter.push_back({ { 1,8 }, { 9,9 }, { 10,10 } }); //y_medial
    arrayConfigLetter.push_back({ { 1,20 }, { 21,21 }, { 22,22 } }); //y_final
    
    
    // ep 1
    
    arrayConfigLetter.push_back({ { 1,8 }}); //a
    arrayConfigLetter.push_back({ { 1,18 }, { 19,19 } }); //b
    arrayConfigLetter.push_back({ { 1,18 }, { 19,19 }, { 20,20 } }); //t
    arrayConfigLetter.push_back({ { 1,18 }, { 19,19 }, { 20,20 }, { 21,21 } }); //th
    arrayConfigLetter.push_back({ { 1,24}, { 25,25 } }); //g
    arrayConfigLetter.push_back({ { 1,24 }}); //ha
    arrayConfigLetter.push_back({ { 1,24}, { 25,25 } }); //ja
    arrayConfigLetter.push_back({ { 1,12 }}); //d
    arrayConfigLetter.push_back({ { 1,12}, { 13,13 } }); //dh
    arrayConfigLetter.push_back({ { 1,12 }}); //r
    arrayConfigLetter.push_back({ { 1,10}, { 11,11 } }); //z
    arrayConfigLetter.push_back({ { 1,27 }}); //s
    arrayConfigLetter.push_back({ { 1,27 }, { 28, 28 },  { 29, 29 }, { 30, 30} }); //sh
    arrayConfigLetter.push_back({ { 1,26 }}); //sad
    arrayConfigLetter.push_back({ { 1,26}, { 27,27 } }); //daad
    arrayConfigLetter.push_back({ { 1,19}, { 20,25 } }); //taa
    arrayConfigLetter.push_back({ { 1,19}, { 20,25 }, { 26,26 } }); //zaa
    arrayConfigLetter.push_back({ { 1,26 }}); //aa
    arrayConfigLetter.push_back({ { 1,26}, { 27,27 } }); //gh
    arrayConfigLetter.push_back({ { 1,26}, { 27,27 } }); //f
    arrayConfigLetter.push_back({ { 1,25}, { 26,26 }, { 27,27 } }); //q
    arrayConfigLetter.push_back({ { 1,18}, { 19,26 } }); //k
    arrayConfigLetter.push_back({ { 1,16 }}); //l
    arrayConfigLetter.push_back({ { 1,17 }}); //m
    arrayConfigLetter.push_back({ { 1,17}, { 18,18} }); //n
    arrayConfigLetter.push_back({ { 1,16 }}); //h
    arrayConfigLetter.push_back({ { 1,20 }}); //w
    arrayConfigLetter.push_back({ { 1,21 }, { 22,22 }, { 23,23 } }); //y
    
    ///
    
    
    
    
}


void WordDictation::initAudio() {
  
    simpleAudioEngine->preloadBackgroundMusic("common/audio/bg/GAME_2.mp3");
    simpleAudioEngine->playBackgroundMusic("common/audio/bg/GAME_2.mp3", true);
}


void WordDictation::toFront(Node* _child, Node* _parent) {
	if (_parent == nullptr) _parent = static_cast<Node*>(_child->getParent());
	_child->retain();
	_child->removeFromParent();
	_parent->addChild(_child);
	_child->release();
}


void WordDictation::initGameObjects() {

	tatu = new GameObject(*rootNode, "Tatu_Welldone", PATH + "CSD/TATU_Well.csb");
	leterBox = new GameObject(*rootNode, Vec2(_director->getWinSize().width / 2, _director->getWinSize().height / 2), PATH + "CSD/board.csb");
	wordBox = new GameObject(*rootNode, Vec2(190 + (remainingWidth / 2), 550), PATH + "CSD/Paletta_immagine.csb");
	keyboard = new Keyboard(*rootNode, Vec2(0, 0), lowercase, _eventDispatcher);
    
    int skin = DataProvider::getInstance()->getSkin();
    string skinStr = StringUtility::toString(skin);
    
	backGround = new GameObject(*rootNode->getChildByName("FondaleRef"), Vec2::ZERO, PATH + "CSD/Background_Composition_skin"+skinStr+".csb");

    
    // set image in the box
    CCLOG("WD - wordInArabic = %s ", wordInArabic.c_str());
    
    englishImageName = ArabicHelperForGames::getInstance()->getFilenameInEnglish_wordDictation(wordInArabic);
    CCLOG("englishImageName = %s", englishImageName.c_str());
    
    std::replace( englishImageName.begin(), englishImageName.end(), ' ', '_'); // replace all ' ' to '_'
    englishImageName = StringUtility::toLowerCase(englishImageName);
    
    CCLOG("englishImageName file = %s", englishImageName.c_str());
    
    static_cast<Sprite*>(wordBox->getChild("Bone_corda/Bone_box_Front/pallone0002_2"))->setTexture(PATH+"DRAWINGS/" + englishImageName + ".png");
    
    //////
    
    
   
 
}





void WordDictation::fadeIn() {
	//DataProvider::getInstance()->updateCurrentStatusToNext();
	CCLOG("WordDictation - Fade in");

	simpleAudioEngine->playEffect((PATH+"audio/game_word_dictation.mp3").c_str());
    this->runAction(Sequence::create(DelayTime::create(4.5f), CallFunc::create([=](){
        
        playAudioWord();
        
    }),  nullptr));

    
    
    
	//keyboard->play("intro", nullptr, false);

	backGround->play("composition", ([=]() {
		createWord();
		backGround->getActionTimeline()->clearLastFrameCallFunc();
	}), false);

	enableTouch();

	
	clickButton = EventListenerCustom::create("keyboard_click_button", [=](EventCustom* event){
		if (!inPauseInsert){
			auto targ = static_cast<KeyboardButton*>(event->getUserData());
			string name = targ->name;
			CCLOG("WD KeyboardButton - onTouchBegan %s", name.c_str());
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


void WordDictation::createWord(){
	
	
	wordBox->play("corda_IN", nullptr, false);
	for (int i = 0; i < wordArray.size(); i++){
        string c = wordArray.at(i); // .substr(i, 1);
		//CCLOG("lettera %i: %s", i, c.c_str());
		
		createChar(i,c);
	}
	CallFunc *runCallback_start = CallFunc::create(CC_CALLBACK_0(WordDictation::startGame, this));
	this->runAction(Sequence::create(DelayTime::create(0.5), runCallback_start, nullptr));
}

void WordDictation::createChar(int _id,string _char){
	//auto charBox = new GameObject(*rootNode, Vec2(_id * 140 + 430 + (remainingWidth / 2), 500), PATH + "CSD/Box_carattere.csb");
	
    float xPos = 1000 - ( 140 * _id );
 
    auto charBox = new GameObject(*rootNode, Vec2( xPos, 550), PATH + "CSD/Box_carattere.csb");
    
    
    auto label = static_cast<cocos2d::ui::Text*>(charBox->getChild("Bone_box_font/Text_1"));
	label->setString("");
	charBox->play("Lett_IN", nullptr, false);
	arrayCharBox.push_back(charBox);
}

void WordDictation::setChar(int _id, string _char){
	auto label = static_cast<cocos2d::ui::Text*>(arrayCharBox[_id]->getChild("Bone_box_font/Text_1"));
    label->setString( ArabicHelper::getInstance()->getInArabic(_char));
	if (_char != ""){
		inPauseInsert = true;
		CallFunc *runCallback_start = CallFunc::create(CC_CALLBACK_0(WordDictation::checkChar, this));
		this->runAction(Sequence::create(DelayTime::create(1), runCallback_start, nullptr));
	}
}


void WordDictation::startGame(){
	charActive = 0;
	selectBox(charActive);
	keyboard->play("intro", nullptr, false);
}


void WordDictation::checkChar(){
	
	bool correct = false;
	auto label = static_cast<cocos2d::ui::Text*>(arrayCharBox[charActive]->getChild("Bone_box_font/Text_1"));
	string c1 = label->getString();
    string c2 = wordArray.at(charActive); //  word.substr(charActive, 1);
    CCLOG("c1 = %s", c1.c_str());
    CCLOG("c2 = %s", c2.c_str());
    if (c1 == c2 ){
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
			selectBox(charActive);
		}
	}
	else{
		arrayCharBox[charActive]->play("Lett_NO", ([=]() {
            score -= 10;
			setChar(charActive, "");
			inPauseInsert = false;
			backGround->getActionTimeline()->clearLastFrameCallFunc();
		}), false);
	}
}
void WordDictation::selectBox(int _id) {
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

void WordDictation::finishFase1() {
	CCLOG("finishFase1");

	

	wordBox->play("corda_OUT", nullptr, false);

	for (int j = 0; j < arrayCharBox.size(); j++) {

		MoveBy *letterMoveActionAc = MoveBy::create(1,Vec2(-200, 0));
		auto letterMoveAction = EaseSineInOut::create(letterMoveActionAc->clone());
		arrayCharBox[j]->play(letterMoveAction);
	}


	CallFunc *runCallback_game = CallFunc::create(CC_CALLBACK_0(WordDictation::playGameLetter, this));
	this->runAction(Sequence::create(DelayTime::create(2), runCallback_game, nullptr));
	/*
	leterBox->play("corda_IN", ([=]() {
		createLetterGame();
		leterBox->getActionTimeline()->clearLastFrameCallFunc();
	}), false);
	*/
}

void WordDictation::playGameLetter(){
	leterBox->bringToFront();
	leterBox->play("in", ([=]() {
		createLetterGame();
		leterBox->getActionTimeline()->clearLastFrameCallFunc();
	}), false);
}


void WordDictation::createLetterGame(){
	CCLOG("CREA LETTER GAME");
	selectLetter();

	auto nodeObj = static_cast<Node*>(leterBox->getChild("board/letterNode"));
	
    
    letter = new GameObject(*nodeObj, Point(0, 0), pathLetters + "csd/letters/Ep_1/letter_" + phoneme + ".csb");
  
    
	letter->setScale(0.8);
	step = arrayConfigLetter[letterID].size();


	simpleAudioEngine->playEffect("LettersGame/audio/Letter_enter.mp3");
	letter->play("letter_pop", ([=]() {
		setObjectStep();
		letter->getActionTimeline()->clearLastFrameCallFunc();
	}), false);

}



void WordDictation::showTutorial() {

}

void WordDictation::hideTutorial() {



}







bool WordDictation::onTouchBegan(Touch* touch, Event* event) {

	CCLOG("LettersGame - Touch began");

	// Manage the start of a touch event


	if (stateInteraction == 0) {
		float markerX = arrayMarker[arrayMarker.size() - 2]->getPosition().x;
		float markerY = arrayMarker[arrayMarker.size() - 2]->getPosition().y;
		float touchX = touch->getLocation().x;
		float touchY = touch->getLocation().y;

		if (std::abs(markerX - touchX)<50 && std::abs(markerY - touchY)<50) {
			stateInteraction = 1;
		}


		if (arrayConfigLetter[letterID][actualStep - 1].size() == 1){
			//CCLOG("UNICO %i", arrayPoint.size());
			arrayMarker[arrayMarker.size() - 1]->getParent()->setVisible(false);

			GameObject* appPoint = arrayPoint[actualShape];
			appPoint->getParent()->setVisible(true);
			int appstep = actualStep;
			CCLOG("p1 %i", actualShape);
			simpleAudioEngine->playEffect("LettersGame/audio/shape_pop.mp3");
			arrayPoint[actualShape]->play("shape_pop", ([=]() {
				CCLOG("p3");
				if (stateInteraction == 1 || actualStep>appstep) {
					appPoint->play("shape_loop", nullptr, true);
				}
				stateInteraction = 3;
				setObjectStep();
				appPoint->getActionTimeline()->clearLastFrameCallFunc();
			}), false);


			actualShape++;
			CCLOG("p2");
		}
	}

	for (int i = 0; i < arrayAnt.size(); i++) {

		float antX = arrayAnt[i]->getPosition().x;
		float antY = arrayAnt[i]->getPosition().y;
		float touchX = touch->getLocation().x;
		float touchY = touch->getLocation().y;

		if (std::abs(antX - touchX)<50 && std::abs(antY - touchY)<50) {
			//simpleAudioEngine->playEffect("LettersGame/audio/ant.mp3");
			arrayAntVelocity[i] = 5.0f;
		}
	}

	return true;
}

void WordDictation::onTouchMoved(Touch* touch, Event* event) {

	//CCLOG("LettersGame - Touch moved %i", stateInteraction);

	if (stateInteraction == 1) {

		float touchX = touch->getLocation().x;
		float touchY = touch->getLocation().y;

		if (actualShape<arrayConfigLetter[letterID][actualStep - 1][1]){
			CCLOG("POINT");
			float pointX = arrayPoint[actualShape]->getPosition().x;
			float pointY = arrayPoint[actualShape]->getPosition().y;

			if (std::abs(pointX - touchX)<50 && std::abs(pointY - touchY)<50) {
				GameObject* appPoint = arrayPoint[actualShape];
				int appstep = actualStep;
				simpleAudioEngine->playEffect("LettersGame/audio/shape_pop.mp3");
				arrayPoint[actualShape]->play("shape_pop", ([=]() {
					if (stateInteraction == 1 || actualStep>appstep) {
						appPoint->play("shape_loop", nullptr, true);
					}
					appPoint->getActionTimeline()->clearLastFrameCallFunc();
				}), false);
				actualShape++;
				stateInteraction = 1;
			}
		}
		else{
			CCLOG("MARKER");

			float markerX = arrayMarker[arrayMarker.size() - 1]->getPosition().x;
			float markerY = arrayMarker[arrayMarker.size() - 1]->getPosition().y;
			float touchX = touch->getLocation().x;
			float touchY = touch->getLocation().y;

			if (std::abs(markerX - touchX)<50 && std::abs(markerY - touchY)<50) {
				stateInteraction = 3;
				arrayMarker[arrayMarker.size() - 1]->play("marker_spiral", nullptr, false);
				simpleAudioEngine->playEffect("LettersGame/audio/pop_marker_spirale.mp3");
				simpleAudioEngine->playEffect("LettersGame/audio/step_markertomaker.mp3");
				setObjectStep();
			}
		}
	}


	//float yThreshold = (blender->getParent()->convertToWorldSpace(blender->getPosition())).y + 250;


	// Manage a touch event
}


void WordDictation::onTouchEnded(Touch* touch, Event* event) {
	if (stateInteraction == 1) {
		stateInteraction = 2;
		regressPoint();
	}
}


void WordDictation::homeButtonPressed() {
	simpleAudioEngine->stopBackgroundMusic();
    
    Logger::getInstance()->logEvent(NAME, Logger::CLOSE, "");
    if ( TEST_ENABLED ) {
        DataProvider::getInstance()->setGameCompleted(NAME, score);
        DataProvider::getInstance()->setWatchmanReaction(WatchmanScene::GOOD_REACTION);
    } else {
        DataProvider::getInstance()->setWatchmanReaction(WatchmanScene::BAD_REACTION);
    }
    
}



void WordDictation::update(float delta) {
	CCLOG("stateInteraction: %i", stateInteraction);
}


void WordDictation::replayDesk(){
	

	leterBox->play("in", ([=]() {
		letter->getNode().retain();
		letter->getNode().removeFromParent();
        if (letter != nullptr) delete letter;
		letter = nullptr;
		createLetterGame();
		leterBox->getActionTimeline()->clearLastFrameCallFunc();
	}), false);
}

void WordDictation::flyPoint() {
	CCLOG("FINE");
	progreLetter++;

	ScaleTo *letterMoveActionAc = ScaleTo::create(0.2, 0.0001);
	auto letterMoveAction = EaseSineInOut::create(letterMoveActionAc->clone());
	letter->play(letterMoveAction);
	
	leterBox->play("out", ([=]() {

		auto objectBack = static_cast<Sprite*>(arrayCharBox[progreLetter - 1]->getChild("Bone_box_font/box_ok/box_ok"));
		objectBack->setVisible(true);

		if (progreLetter < wordArray.size()){
			
			CallFunc *runCallback_game = CallFunc::create(CC_CALLBACK_0(WordDictation::replayDesk, this));
			this->runAction(Sequence::create(DelayTime::create(2), runCallback_game, nullptr));
			
		}
		else{
			finisGame();
		}
	}), false);
}

void WordDictation::finisGame(){
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
        _director->replaceScene(TransitionFade::create(TRANSITION_TIME, WordDictation::createScene(), TRANSITION_COLOR));
        tatu->getActionTimeline()->clearLastFrameCallFunc();
    }), false);
        
}

void WordDictation::setObjectStep() {
	actualStep++;
	CCLOG("actualStep %i", actualStep);
	CCLOG("step %i", step);
	if (actualStep <= step) {
		if (arrayConfigLetter[letterID][actualStep - 1].size() == 1){
			CCLOG("SOLO 1");

			CallFunc *runCallback_marker = CallFunc::create(CC_CALLBACK_0(WordDictation::playStartMarker, this, actualStep * 2 - 1, 1));
			this->runAction(Sequence::create(DelayTime::create(0), runCallback_marker, nullptr));

			CallFunc *runCallback_shape = CallFunc::create(CC_CALLBACK_0(WordDictation::playStartPoint, this, arrayConfigLetter[letterID][actualStep - 1][0]));
			this->runAction(Sequence::create(DelayTime::create(0), runCallback_shape, nullptr));


		}
		else{


			int nPoint = arrayConfigLetter[letterID][actualStep - 1][1] - arrayConfigLetter[letterID][actualStep - 1][0];
			float delayPoint = 0.1;

			int i = 0;
			for (i = actualStep * 2 - 1; i <= actualStep * 2; i++) {
				int m = i % 2;
				if (m == 0)m = 2;

                float delayTime = (m*nPoint*delayPoint) - (nPoint*delayPoint);
                if (delayTime<0.5) delayTime = 0.5;
                
				CallFunc *runCallback_regress = CallFunc::create(CC_CALLBACK_0(WordDictation::playStartMarker, this, i, m));
				this->runAction(Sequence::create(DelayTime::create(delayTime), runCallback_regress, nullptr));

			}
			int cPoint = 0;
			for (i = arrayConfigLetter[letterID][actualStep - 1][0]; i <= arrayConfigLetter[letterID][actualStep - 1][1]; i++) {
				cPoint++;
				CallFunc *runCallback_regress = CallFunc::create(CC_CALLBACK_0(WordDictation::playStartPoint, this, i));
				this->runAction(Sequence::create(DelayTime::create(cPoint * delayPoint), runCallback_regress, nullptr));
			}

		}
	}
	else {

		CallFunc *runCallback_play = CallFunc::create(CC_CALLBACK_0(WordDictation::playLetters, this, "sema"));
		this->runAction(Sequence::create(DelayTime::create(1), runCallback_play, nullptr));

		CallFunc *runCallback_fly = CallFunc::create(CC_CALLBACK_0(WordDictation::flyPoint, this));
		this->runAction(Sequence::create(DelayTime::create(3), runCallback_fly, nullptr));
	}
}


void WordDictation::playLetters(string _path){

	//CCLOG("AUDIO PHONEMA: %s %s", ("common/audio/" + _path + "/phonemes/" + phoneme + ".mp3").c_str(), phoneme.c_str());
	simpleAudioEngine->playEffect(("common/audio/" + _path + "/phonemes/" + phoneme + ".mp3").c_str());
}



void WordDictation::playStartMarker(int _i, int _m) {
	auto marker = new GameObject(*letter->getChild("letter/marker_" + StringUtility::toString(_i)), Vect::ZERO, pathLetters + "csd/Main_prop/marker_" + StringUtility::toString(_m) + ".csb");
	marker->play("marker_pop", nullptr, false);
	simpleAudioEngine->playEffect("LettersGame/audio/marker_pop.mp3");
	arrayMarker.push_back(marker);
	arrayAllShape.push_back(marker);

	if (_m == 2 || arrayConfigLetter[letterID][actualStep - 1].size() == 1) {
		stateInteraction = 0;
	}

}

void WordDictation::playStartPoint(int _i) {
	//srand(time(NULL));
	auto point = new GameObject(*letter->getChild("letter/shape_" + StringUtility::toString(_i)), Vect::ZERO, pathLetters + "csd/Main_prop/shape_" + StringUtility::toString(typeSymbol) + ".csb");
	arrayPoint.push_back(point);
	arrayAllShape.push_back(point);

	static_cast<Node*>(&(point->getNode()))->getChildByName("pallozWhite")->getChildByName("pallozWhite")->setVisible(false);

	if (arrayConfigLetter[letterID][actualStep - 1].size() == 1) {
		point->getParent()->setVisible(false);
	}
}





void WordDictation::regressPoint() {
	if (actualShape >= arrayConfigLetter[letterID][actualStep - 1][0]) {
		actualShape--;

		simpleAudioEngine->playEffect("LettersGame/audio/back.mp3");
		arrayPoint[actualShape]->getActionTimeline()->play("shape_poof", false);
		CallFunc *runCallback_regress = CallFunc::create(CC_CALLBACK_0(WordDictation::regressPoint, this));
		this->runAction(Sequence::create(DelayTime::create(0.1), runCallback_regress, nullptr));
	}
	else {
		stateInteraction = 0;
	}
}


void WordDictation::addListenButton(){
    
    
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

void WordDictation::playAudioWord()
{
    
    simpleAudioEngine->playEffect((PATH + "audio/words/"+ englishImageName + ".mp3").c_str());
    
}
