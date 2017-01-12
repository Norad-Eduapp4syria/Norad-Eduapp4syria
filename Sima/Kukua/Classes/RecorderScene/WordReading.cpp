#include "WordReading.h"
#include "PMAudioEngine.cpp"

#include <array>
#include <cstring>
#include <fcntl.h>
#include <sstream>

#include "../Utils/Data/Logger.h"

#include "../Utils/GameObject.h"
#include "WRLetter.h"
#include "../AppMacros.h"
#include "../WatchmanScene/WatchmanScene.h"
#include "../Utils/Data/ArabicHelper.h"
#include "../Utils/Data/ArabicHelperForGames.h"
#include "../Utils/StringUtility.h"

USING_NS_CC;

PMAudioEngine pmAudioWR;

// pre-recorded sound clips, both are 8 kHz mono 16-bit signed little endian
const char hello[] =
#include "hello_clip.h"
;
using namespace std;


const string WordReading::PATH = "WordReading/";								// Resources' subfolder path for this game
string WordReading::NAME = ""; // TO_SET

// the audioSample struct is to
// contain basic data such as
// audio filename

std::array<audioSample, 4> samplesWR
{
        audioSample(false, false, "drum.mp3", true),
        audioSample(false, false, "guitar.mp3", true),
        audioSample(false, false, "background.mp3", true),
        audioSample(false, false, "", false),
};

GameObject* deskWR;
GameObject* listenWord;
GameObject* character;
GameObject* speak;
GameObject* sema;
GameObject* recMetObj;
GameObject* helpHand;
GameObject* background;

std::vector<WRLetter*> wrLetters;


// obj
GameObject* objFade;
Sprite *fadeSprite;

static bool recCreated = false;

// randomize excluding values function
int getRandomWithExclusion(int start, int end, vector<int> exclude)
{
	int size = exclude.size();
	int random = cocos2d::RandomHelper::random_int(start, end);
	for (int c = 0; c < size; c++)
	{
		if (random == exclude.at(c))
		{
			return getRandomWithExclusion(start, end, exclude);
			break;
		}
	}
	return random;
}

Scene* WordReading::createScene()
{
    
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = WordReading::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool WordReading::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    Logger::getInstance()->logEvent(NAME, Logger::OPEN, "");
    
    CCLOG("game name : %s", NAME.c_str());
    
	//
	isComposing = true;
	roundNumber = 0;

	oldWhich = -1;
	newRecording = true;
	initForRecord();

	// clean word
	word.clear();
	words.clear();

    
    //
    character = nullptr;
    sema = nullptr;
    deskWR = nullptr;
    speak = nullptr;
    
	// init the temp word variable
	std::vector<std::string> tempword;

	/*
	m#or#n#i#ng
	ch#i#ck#e#n
	j#a#ck#e#t
	t#r#ai#n
	p#o#ck#e#t
	*/
    auto dataProvider = DataProvider::getInstance();
    string currentPhoneme = dataProvider->getCurrentDBKnowledgeBubble()->getPhoneme();
    //CCLOG("WR currentPhoneme = %s", currentPhoneme.c_str());
    
    
    vector<string> wordsVector;
    if (NAME == "WordReading") {
        wordsVector = dataProvider->getWordsForGame(currentPhoneme, "wordReading");
    } else if (NAME == "SentenceReading") {
        wordsVector = dataProvider->getWordsForGame(currentPhoneme, "sentenceReading");
    }
    
    
    
    for (vector<string>::iterator iterator = wordsVector.begin(); iterator != wordsVector.end(); ++iterator) {
        CCLOG("singleWord in english = %s", (*iterator).c_str());
        string singleWord = ArabicHelper::getInstance()->getInArabic( (*iterator) );
        CCLOG("singleWord = %s", singleWord.c_str());
        tempword = split( singleWord , '#');
        wordsEnglish.push_back(  split( (*iterator) , '#######') );
        words.push_back(tempword);
    }
    
    simpleAudioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
    
    rootNode = CSLoader::createNode(PATH + "MainScene.csb");
    
    rootNode->setAnchorPoint(Vec2(0.5, 0.5));
    rootNode->setPosition(Vec2(_director->getWinSize().width / 2, _director->getWinSize().height / 2));
    addChild(rootNode);
    
    
    background = new GameObject(*rootNode, "background", PATH + "Csd/background.csb");
    background->play("background_loop", nullptr, true);
    
    recPressed = false;
    stopClick = false;

	// randomize the word
	int ln = words.size();

	log("************** WORDS LEN IS %d", ln);
    if (ln == 0) {
        log("************** ERROR!!!!! WORDS LEN IS 0");
        addHomeButton();
        return true;
    }
	//word = words[cocos2d::RandomHelper::random_int(0, ln - 1)];
	int ch = getRandomWithExclusion(0, ln - 1, chosenWords);
    word = words.at(ch);
	chosenWords.push_back(ch);
	
	wordToRead = "";
	for (auto const& s : word) { wordToRead += s; }

    wordToReadEnglish = "";
    for (auto const& s : wordsEnglish.at(ch)) { wordToReadEnglish += s; }
    
	log("************** WORD IS %s", wordToRead.c_str());

	// for fading
	/*
    Size s = Director::sharedDirector()->getWinSize();
	objFade = new GameObject(*rootNode, Vec2(s.width / 2, s.height / 2));
    */
    
   // Size s = Director::sharedDirector()->getWinSize();
    objFade = new GameObject(*rootNode, Vec2(_director->getWinSize().width / 2, _director->getWinSize().height / 2));
    
	fadeSprite = Sprite::create();
	objFade->getNode().addChild(fadeSprite);

	fadeSprite->setTexture("WordReading/Png/blankPixel.png");
	fadeSprite->setPositionZ(20);
	fadeSprite->setScale(500, 500);
	fadeSprite->runAction(FadeOut::create(0.5f));

    startGame();
        
    addHomeButton();
    
    
    if (NAME == "SentenceReading") {
        boardLabel = ArabicHelper::getInstance()->createLabel("", 70);
        auto txtNode = static_cast<Node*>( rootNode->getChildByName("sentence_board")->getChildByName("cartel")->getChildByName("Text") );
        txtNode->addChild(boardLabel);
    }
    

    return true;
}

void WordReading::PlaySample(int which)
{
    if (samplesWR.at(which).isFile)
    {
        if (!samplesWR.at(which).isCreated)
            CreateFromFile(which);
    }
    else
        CreateFromData(hello, sizeof(hello));

    samplesWR.at(which).isCreated = true;
    //
    if (which == 3) newRecording = true;

    PlayAudioSample(which);
}

WordReading::~WordReading() {
    
    CCLOG("~WordReading");
    this->unscheduleUpdate();
    if (deskWR != nullptr) delete deskWR;
    delete listenWord;
    delete background;
    if (character != nullptr) delete character;
    if (speak != nullptr) delete speak;
    if (sema != nullptr) delete sema;

    int c;
    for (c = 0; c < wrLetters.size(); c++) {
       delete wrLetters[c];
    }
    wrLetters.clear();
    
}

void WordReading::startGame()
{
    
    CallFunc *runCallback1 = CallFunc::create(CC_CALLBACK_0(WordReading::composeScene, this));
    this->runAction(Sequence::create(DelayTime::create(0.4), runCallback1, nullptr));

}


void WordReading::setNewRound()
{
	// delete old
	int wLen = word.size() / sizeof(wordToRead[0]);
	for (int c = 0; c < wLen; c++)
	{
		stringstream name;
		name << "letter_" << word[c] << c + 1;

		Node *node = rootNode->getChildByName(name.str());
		rootNode->removeChild(node);
		//delete(node);
	}

	
	recPressed = false;

	speak->getChild("pull_speak/pull_speak")->setOpacity(255);
	listenWord->getChild("pull_listen/pull_listen")->setOpacity(255);

	speak->setVisible(false);
	listenWord->setVisible(false);

	// randomize the new word
	int ln = words.size();

	//word = words[cocos2d::RandomHelper::random_int(0, ln - 1)];
	int ch = getRandomWithExclusion(0, ln - 1, chosenWords);
	word = words.at(ch);
	chosenWords.push_back(ch);

	wordToRead = "";
	for (auto const& s : word) { wordToRead += s; }

    wordToReadEnglish = "";
    for (auto const& s : wordsEnglish.at(ch)) { wordToReadEnglish += s; }
    
    
    if (NAME == "WordReading") {
        addLetters();
    } else if (NAME == "SentenceReading") {
        addBoard();
    }
    

	for (int c = 0; c < 5; c++)
	{
		stringstream path;
		path << "tac_" << c + 1 << "/tac_" << c + 1;
		(recMetObj->getChild(path.str()))->setVisible(false);
	}
}
void WordReading::playAudioReference()
{
    
    if (NAME == "WordReading") {
        simpleAudioEngine->playEffect(("common/audio/grandpa/words/" + ArabicHelper::getInstance()->getFilenameInEnglish(wordToRead) + ".mp3").c_str());
    } else if (NAME == "SentenceReading") {
        
        string wordToReadAudio = ArabicHelperForGames::getInstance()->getFilenameInEnglish_sentenceReading(wordToRead);
        std::replace( wordToReadAudio.begin(), wordToReadAudio.end(), ' ', '_'); // replace all ' ' to '_'
        wordToReadAudio = StringUtility::toLowerCase(wordToReadAudio);
        
        simpleAudioEngine->playEffect((PATH+"Audio/sentences/" + wordToReadAudio + ".mp3").c_str());
    }
    
}

void WordReading::composeScene()
{
    /*
    auto desk = static_cast<Node*>(rootNode->getChildByName("desk"));
    
    
    cocostudio::timeline::ActionTimeline* deskTimeline = CSLoader::createTimeline( PATH + "Csd/desk.csb");
    desk->runAction(deskTimeline);
    deskTimeline->setLastFrameCallFunc([this, deskTimeline](){
        addLetters();
        deskTimeline->clearLastFrameCallFunc();
    });
    deskTimeline->play("start", false);
    */
  
	

	if (sema != nullptr) delete sema;
    sema = new GameObject(*rootNode, "sema_positive", PATH + "Csd/sema_positive.csb");
	
	if (deskWR != nullptr) delete deskWR;
    deskWR = new GameObject(*rootNode, "desk", PATH + "Csd/desk.csb");

	simpleAudioEngine->playEffect((PATH+"Audio/desk_start.mp3").c_str());

    deskWR->play("start", [=]() {
        
        if (NAME == "WordReading") {
            addLetters();
        } else if (NAME == "SentenceReading") {
            addBoard();
        }
		
        // -- playWordBtn
        listenWord = new GameObject(*rootNode, "listen_word", PATH + "Csd/pull_listen.csb");
        
        auto playWordBtn = static_cast< cocos2d::ui::Button*>(rootNode->getChildByName("playWordBtn"));
        playWordBtn->addClickEventListener([=](Ref *){

			if (isComposing) return;
            if (stopClick) return;
			if (recPressed) return;
			
			CCLOG("playWordBtn.. %s", wordToReadEnglish.c_str());
            listenWord->play("press");
			simpleAudioEngine->playEffect((PATH+"Audio/listen_press.mp3").c_str());

            playAudioReference();
            

			helpHand->setVisible(true);
			helpHand->setPosition(Vec2(speak->getPosition().x, speak->getPosition().y - 150));
			helpHand->bringToFront();
			helpHand->play("help_loop", nullptr, true);
            
        });
		
		listenWord->bringToFront();
		listenWord->setVisible(false);
		
		// UP listen word button
		Vec2 pos = listenWord->getPosition();
		pos.y += 50;
		listenWord->setPosition(pos);

		// help hand
		helpHand = new GameObject(*rootNode, Vec2(listenWord->getPosition()), PATH + "Csd/help.csb");
		helpHand->setVisible(false);
		helpHand->setScale(0.5f);

        // --lplayWordBtn
        
        int skin = DataProvider::getInstance()->getSkin();
        string skinStr = StringUtility::toString(skin);
        
        if (character != nullptr) delete character;
		//character = new GameObject(*rootNode, rootNode->getChildByName("charRef")->getPosition(), PATH + "Csd/chara_1.csb");
        character = new GameObject(*rootNode, rootNode->getChildByName("charRef")->getPosition(), PATH + "Csd/chara_"+skinStr+".csb");
        
        character->getNode().setRotation(-12.6);
        simpleAudioEngine->playEffect((PATH+"Audio/tatu_enter.mp3").c_str());
        character->play("enter", [=]() {
            character->play("standing", nullptr, true);
            character->clearLastFrameCallFunc();
        });
        
		sema->bringToFront();
		character->bringToFront();

		// -- rec meter
		recMetObj = new GameObject(*rootNode->getChildByName("desk")->
			getChildByName("master_desk")->
			getChildByName("tac"), Vec2(0, 0), PATH + "Csd/tac_recording.csb");

		recMetObj->bringToFront();
		recMetObj->setVisible(true);

		for (int c = 0; c < 5; c++)
		{
			stringstream path;
			path << "tac_" << c + 1 << "/tac_" << c + 1;
			(recMetObj->getChild(path.str()))->setVisible(false);
		}


        // ------ record button ------
		if (speak != nullptr) delete speak;
        speak = new GameObject(*rootNode, "pull_speak", PATH + "Csd/pull_speak.csb");
		speak->setVisible(false);
        
        auto recBtn = static_cast< cocos2d::ui::Button*>(rootNode->getChildByName("recBtn"));
        recBtn->addClickEventListener([=](Ref *){

			if (isComposing) return;
			if (stopClick) return;
            
            if (recPressed == false) {

				helpHand->setVisible(false);
				setTouchLetters(false);

				speak->play("press_1");
				simpleAudioEngine->playEffect((PATH+"Audio/puls_speak.mp3").c_str());
				log("audio recorder click");
                character->play("rec");
				CCLOG(">> ------ inizio registrazione");
                recPressed = true;
			
				//rec + listen
				runAction(Sequence::create(CallFunc::create([&]() 
				{ 
					speak->getChild("pull_speak/pull_speak")->setOpacity(128);
					listenWord->getChild("pull_listen/pull_listen")->setOpacity(128);

					Rec(nullptr); 
					for (int c = 0; c < 5; c++)
					{
						runAction(Sequence::create(DelayTime::create(recMeterTime * c), CallFunc::create([=]()
						{
							stringstream path;
							path << "tac_" << c + 1 << "/tac_" << c + 1;
							recMetObj->getChild(path.str())->setVisible(true);
							//simpleAudioEngine->playEffect("Audio/tac_recording.mp3");
						}), 
						nullptr));
					}
				}), 
			    DelayTime::create(3.5f), CallFunc::create([&]() { PlayRecordedBuffer(nullptr); }), nullptr));
				runAction(
					Sequence::create(
					DelayTime::create(7.f),
					CallFunc::create(
					[&]() {
                        
                    playAudioReference();

                    playSpiralAnimationAfterDelay(2.0);
					
                    int roundCounter = roundNumber;
                    roundCounter++;
                    if (roundCounter < words.size()) {
                        playCharacterFeedbackAfterDelay(3.5);
                    }
					setTouchLetters(false);
				}),
					DelayTime::create(3.5),
					CallFunc::create(
					[&]()
				{
					objFade->bringToFront();

					fadeSprite->runAction(
						Sequence::create(FadeIn::create(0.2f),
						CallFunc::create([=]() {
						fadeSprite->runAction(FadeOut::create(0.4f));
						// sets a new round
						// with no new instances
						roundNumber++;
                            
                        if (roundNumber < words.size()) {
							setNewRound();
                        } else {
                            log("....FINE ROUNDS");
                            
                            character->play("exit", [&]() {
                                playWellDoneAndEndGame();
                                character->getActionTimeline()->clearLastFrameCallFunc();
                            });
                            
                        }
							
							
					}),
						nullptr
						)
						);
				}
					),
					nullptr
					)
					);

			}
			else Rec(nullptr);
		
        });
        // ------ record button ------
        
        
	
        // ------ playYouBtn button ------
        /*
        listen_you = new GameObject(*rootNode, "listen_you", PATH + "Csd/pull_listen.csb");
        listen_you->play("enter");
        
        auto playYouBtn = static_cast< cocos2d::ui::Button*>(rootNode->getChildByName("playYouBtn"));
        playYouBtn->addClickEventListener([=](Ref *){
            if (stopClick) return;
            CCLOG("playYouBtn");
            listen_you->play("press");
            PlayRecordedBuffer(nullptr);
            playWellDoneAnimationAfterDelay(3.0);
        });
        */
        // ------ playYouBtn button ------
        
        
        
        deskWR->clearLastFrameCallFunc();
    });
}


void WordReading::addBoard()
{
   
    auto dataProvider = DataProvider::getInstance();
    string currentPhoneme = dataProvider->getCurrentDBKnowledgeBubble()->getPhoneme();
    vector<string> wordsVector = dataProvider->getWordsForGame(currentPhoneme, "sentenceReading");
    
    Node* board = static_cast<Node*>(rootNode->getChildByName("sentence_board"));
    
    boardLabel->setString( ArabicHelper::getInstance()->getInArabic( wordsVector.at(roundNumber) ) );
    
    cocostudio::timeline::ActionTimeline* boardTimeline = CSLoader::createTimeline(PATH + "Csd/sentence_board.csb");
    board->runAction(boardTimeline);
    boardTimeline->play("enter", false);
    
    
    // listen button
				runAction(
                          Sequence::create(
                                           DelayTime::create(0.5f),
                                           CallFunc::create(
                                                            [=]() {
                                                                isComposing = false;
                                                                listenWord->setVisible(true);
                                                                listenWord->bringToFront();
                                                                simpleAudioEngine->playEffect((PATH+"Audio/listen_enter.mp3").c_str());
                                                                listenWord->play("enter");
                                                                
                                                                helpHand->setVisible(true);
                                                                helpHand->setPosition(Vec2(listenWord->getPosition().x, listenWord->getPosition().y - 150));
                                                                helpHand->bringToFront();
                                                                helpHand->play("help_loop", nullptr, true);
                                                                
                                                            }), nullptr));
    
    
    
				// speak button
				runAction(
                          Sequence::create(
                                           DelayTime::create(0.8f),
                                           CallFunc::create(
                                                            [=]() {
                                                                
                                                                speak->setVisible(true);
                                                                speak->play("enter");
                                                                simpleAudioEngine->playEffect((PATH+"Audio/puls_enter.mp3").c_str());
                                                                speak->bringToFront();
                                                                
                                                                setTouchLetters(true);
                                                                
                                                            }), nullptr));
    
    
    
}


void WordReading::addLetters()
{
	// fixed width of the screen is 1280

	// length of the word
    int wLen = word.size() / sizeof(wordToRead[0]);
    CCLOG("add letters - wLen = %d", wLen);
	// compose word
	int startPos = 440;

	// starts from center then add offset to left
	if (wLen > 3)
		startPos -= (150 * (wLen - 3)) - 100;
	if (startPos < 220) startPos = 220;

    // 
    float yLetters = 550.0;

	log("***************** WORD SIZE IS %d", wLen);

    int c;
    for (c = 0; c < wrLetters.size(); c++) {
        delete wrLetters[c];
    }
	wrLetters.clear();


    for (c = (wLen-1); c >= 0; c--)
    //for (c = 0; c < wLen; c++)
	{
        //CCLOG("..push back %s", (word[c]).c_str() );
		auto letter = new WRLetter(*rootNode, Vec2(startPos, yLetters), _eventDispatcher, word[c]);
		wrLetters.push_back(letter);
        //wrLetters.push_back(*letter);

		//letter->play("enter");

		stringstream name;
		name << "letter_" << word[c] << c + 1;
		letter->getNode().setName(name.str());
		letter->setTouchable(false);
        letter->getParent()->runAction(
                    Sequence::create(
                        DelayTime::create(0.15f * c),
                        CallFunc::create([=]() {
                            simpleAudioEngine->playEffect((PATH+"Audio/letter_enter.mp3").c_str());
                            letter->play("enter", [=]() {
                                    if (c == wLen - 1) {
                                        runAction(Sequence::create( CallFunc::create([=]() {
                                                character->bringToFront();
                                                simpleAudioEngine->playEffect((PATH+"Audio/game_word_dictation.mp3").c_str()); // help
                                                }),
                                                DelayTime::create(5.0f),
                                                CallFunc::create([=]() { spelling(); }),
                                                nullptr)
                                        );
                                    } // close  if (c == wLen - 1)
                              letter->clearLastFrameCallFunc();
                            });
                        }),
                        nullptr
                        )
        );

		// auto size for letter tile
		int dist = 165;
		if (wLen > 5)
			dist = 155;

		if (word.at(c).size() == 2)
		{
			letter->getChild("letter_master/letter_box/letter_box")->setScaleX(1.25f);

			// moves a little left
			int spc = 21;
			Vec2 pos = letter->getPosition();
			pos.x += spc;
			letter->setPosition(pos);

			startPos += dist + (spc * 2);
		}
		else
		{
			startPos += dist;
			if (c > 0)
			{
				if (word[c - 1].size() == 1)
				{
					Vec2 pos = letter->getPosition();
					pos.x += 10;
					letter->setPosition(pos);
					startPos += 10;
				}
			}
		}

		float defaultScale = 0.9f;
		letter->setScale(defaultScale);
		
		// for words > 5 tiles
		if (wLen > 5)
		{
			// auto size for longer words
			float scale = defaultScale - float(wLen - 5) / (float)12;
			letter->getChild("letter_master/letter_box")->setScale(scale);

			// offset to adjust distance
			float offs = 21.f;
			if (wLen >= 8) offs = 18.f;

			//adjust distance
			if (c > 0)
			{
				Vec2 pos = letter->getPosition();
				pos.x -= ((wLen - 5) * offs) * c;
				    if (c == 8 ) //9 letters
						pos.x -= 10;
				letter->setPosition(pos);
			}
		}
	}
}

void WordReading::setTouchLetters(bool touchable)
{
    for (int c = 0; c < wrLetters.size(); c++) {
		wrLetters.at(c)->setTouchable(touchable);
    }
}

void WordReading::spelling()
{
		log("SPELLING");

	// enlights the letters playing their sounds
	int wLen = word.size() / sizeof(wordToRead.at(0));

    int letterIndex = wLen;
    
	for (int c = 0; c < wLen; c++)
	//for (int c = (wLen-1); c >= 0; c--)
    {
        letterIndex--;
		log("LETTERNAME : %s", ("letter_" + word[letterIndex]).c_str());
		stringstream name;
		name << "letter_" << word.at(c) << c + 1;

		auto letter = rootNode->getChildByName(name.str());
		
		//log("LETTERNAME : %s", (letter->getName()).c_str());
		//log("LETTERNAME child : %s", (letter->getChildren().at(0)->getName()).c_str());

		letter->getParent()->runAction(
			Sequence::create(
			DelayTime::create(0.75f * c),
			CallFunc::create(
			[=]() {
                
                string txtAudio = ArabicHelper::getInstance()->getInLetter( word.at(c) );
                simpleAudioEngine->playEffect(("common/audio/sema/phonemes/" + txtAudio + ".mp3").c_str());
                wrLetters.at(letterIndex)->play("press_letter");
		}),
			DelayTime::create(0.75f),
			CallFunc::create(
			[=]() {
			/*static_cast<Sprite*>(letter->getChildByName("letter_master")->
										 getChildByName("letter_box")->
										 getChildByName("letter_box"))->
										 setColor(Color3B(255, 255, 255));*/

			if (c == wLen - 1)
			{
				isComposing = false;
                
                playAudioReference();
				

				// listen button
				runAction(
					Sequence::create(
					DelayTime::create(0.25f * c),
					CallFunc::create(
					[=]() {

					listenWord->setVisible(true);
					listenWord->bringToFront();
					simpleAudioEngine->playEffect((PATH+"Audio/listen_enter.mp3").c_str());
					listenWord->play("enter");

					helpHand->setVisible(true);
					helpHand->setPosition(Vec2(listenWord->getPosition().x, listenWord->getPosition().y - 150));
					helpHand->bringToFront();
					helpHand->play("help_loop", nullptr, true);

				}), nullptr));



				// speak button
				runAction(
					Sequence::create(
					DelayTime::create(0.55f * c),
					CallFunc::create(
					[=]() {

					speak->setVisible(true);
					speak->play("enter");
					simpleAudioEngine->playEffect((PATH+"Audio/puls_enter.mp3").c_str());
					speak->bringToFront();

					setTouchLetters(true);

				}), nullptr));
			}
		}),
			nullptr
			)
			);
	}
}

void WordReading::initForRecord()
{
    // create Engine
    pmAudioWR.CreateEngine();
    
    // set buffer
    int sampleRate = 0;
    int bufSize = 0;
    
    // create buffer queue for player
    pmAudioWR.CreateBufferQueuePlayer(sampleRate, bufSize);
    
    //main loop
    this->scheduleUpdate();
    

}


void WordReading::playSpiralAnimationAfterDelay(float delay) {
    runAction(
              Sequence::create(
                               DelayTime::create(delay),
                               CallFunc::create(
                                                [&]() {
                                                    speak->play("spiral");
                                                    //simpleAudioEngine->playEffect((PATH+"Audio/sema_appar.mp3").c_str());
                                                }),
                               nullptr
                               )
              );
}


void WordReading::playCharacterFeedbackAfterDelay(float delay) {
    runAction(
              Sequence::create(
                               DelayTime::create(delay),
                               CallFunc::create(
                                                [&]() {
                                                    character->play("feedback_positive");
                                                    //simpleAudioEngine->playEffect((PATH+"Audio/sema_appar.mp3").c_str());
                                                }),
                               nullptr
                               )
              );
}


void WordReading::playWellDoneAndEndGame() {
    runAction(
              Sequence::create(
                               CallFunc::create(
                                                [&]() {
													sema->bringToFront();
                                                    sema->play("Well_Apparizione");
													simpleAudioEngine->playEffect((PATH+"Audio/sema_appar.mp3").c_str());
                                                }),
                               DelayTime::create(2.5),
                               CallFunc::create(
                                                [&]() {
                                                    sema->play("Well_Sparizione", [&]() {
														simpleAudioEngine->playEffect((PATH+"Audio/sema_spar.mp3").c_str());
                                                        CCLOG("...fine...");
                                                       // stopClick = false;
                                                        endGame();
                                                        
                                                        sema->getActionTimeline()->clearLastFrameCallFunc();
                                                    });
                                                }),
                               nullptr
                               )
              );
}


void WordReading::startGame2()
{
    
    
    // create Engine
    pmAudioWR.CreateEngine();
    
    // set buffer
    int sampleRate = 0;
    int bufSize = 0;
    
    // create buffer queue for player
    pmAudioWR.CreateBufferQueuePlayer(sampleRate, bufSize);
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    auto recItem = MenuItemImage::create(
                                         PATH+"btn/Rec.png",
                                         PATH+"btn/RecOn.png",
                                         CC_CALLBACK_1(WordReading::Rec, this));
    
    
    auto playRecordedItem = MenuItemImage::create(
                                                  PATH+"btn/Play.png",
                                                  PATH+"btn/PlayOn.png",
                                                  CC_CALLBACK_1(WordReading::PlayRecordedBuffer, this));
    
    auto playFile1Item = MenuItemImage::create(
                                               PATH+"btn/Play.png",
                                               PATH+"btn/PlayOn.png",
                                               CC_CALLBACK_0(WordReading::PlaySample, this, 0));
    
    auto playFile2Item = MenuItemImage::create(
                                               PATH+"btn/Play.png",
                                               PATH+"btn/PlayOn.png",
                                               CC_CALLBACK_0(WordReading::PlaySample, this, 1));
    
    auto playFile3Item = MenuItemImage::create(
                                               PATH+"btn/Play.png",
                                               PATH+"btn/PlayOn.png",
                                               CC_CALLBACK_0(WordReading::PlaySample, this, 2));
    
    auto playDataItem = MenuItemImage::create(
                                              PATH+"btn/Play.png",
                                              PATH+"btn/PlayOn.png",
                                              CC_CALLBACK_0(WordReading::PlaySample, this, 3));
    
    
    recItem->setPosition(Vec2(origin.x + 30,
                              origin.y + visibleSize.height - recItem->getContentSize().height * 1.5f));
    
    playRecordedItem->setPosition(Vec2(origin.x + 80,
                                       origin.y + visibleSize.height - playRecordedItem->getContentSize().height * 1.5f));
    
    playFile1Item->setPosition(Vec2(origin.x + 120,
                                    origin.y + 50));
    
    playFile2Item->setPosition(Vec2(origin.x + 200,
                                    origin.y + 50));
    
    playFile3Item->setPosition(Vec2(origin.x + 280,
                                    origin.y + 50));
    
    playDataItem->setPosition(Vec2(origin.x + 360,
                                   origin.y + 50));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(recItem, playRecordedItem, playFile1Item,
                             playFile2Item, playFile3Item, playDataItem, NULL);
    menu->setPosition(Vec2::ZERO);
    rootNode->addChild(menu, 1);
    
    
    
    // create and initialize labels
    
    auto label = Label::createWithTTF("Audio Rec/Play", "common/fonts/Marker Felt.ttf", 20);
    recorderLabel = Label::createWithTTF("No Recording", "common/fonts/Marker Felt.ttf", 10);
    audioRecPlayerStateLabel = Label::createWithTTF("No Playing", "common/fonts/Marker Felt.ttf", 10);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width / 2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    
    recorderLabel->setPosition(Vec2(origin.x + 30, origin.y + visibleSize.height - recorderLabel->getContentSize().height - 70));
    audioRecPlayerStateLabel->setPosition(Vec2(origin.x + 80, origin.y + visibleSize.height - audioRecPlayerStateLabel->getContentSize().height - 70));
    
    // add the label as a child to this layer
    rootNode->addChild(label, 1);
    rootNode->addChild(recorderLabel, 1);
    rootNode->addChild(audioRecPlayerStateLabel, 1);

    //main loop
    this->scheduleUpdate();
    

}

bool WordReading::CreateFromFile(int which)
{
    
    
    simpleAudioEngine->playEffect("drum.mp3");
    
    return true;
}

void WordReading::PlayAudioSample(int which)
{
    //play data
    if (!samplesWR[which].isFile)
    {
        pmAudioWR.EnqueueClip(false);
        return;
    }

    //play file
    samplesWR[which].isPlaying = !samplesWR[which].isPlaying;
    pmAudioWR.SetPlayingAssetAudioPlayer(samplesWR[which], samplesWR[which].isPlaying);
}



void WordReading::Rec(Ref* pSender)
{
	if (isAudioRecording || isRecordPlaying)
    {
        //pmAudioWR.StopRecording();
		//log("AudioRecord stopped");
        return;
    }

    if (!recCreated) {
        log("create AudioRecord");
        recCreated = pmAudioWR.CreateAudioRecorder();
    }

    if (recCreated) {
		 newRecording = true;
        if (!isRecordPlaying)
            pmAudioWR.SetRecPlayingPaused(false);

        pmAudioWR.StartRecording();
		log("AudioRecord start rec ...");
    }else 
		log("AudioRecord not created!");
}


void WordReading::CreateFromData(const char* data, unsigned dataSize)
{
    pmAudioWR.CreateDataBuffer(data, dataSize);	
}

void WordReading::PlayRecordedBuffer(Ref* pSender)
{
	log("Audiorecord playback");

    character->play("rec_return");
    
    CCLOG("AUDIO PLAYING : %s RECORDING : %s", (isRecordPlaying ? "true" : "false"), (isAudioRecording ? "true" : "false"));

	if (isAudioRecording)
	{
		pmAudioWR.StopRecording();
	}
   
	CCLOG("NO AUDIO RECORDING");

	log("Audiorecord 1");

	// pause
	if (isRecordPlaying)
	{
		if (pmAudioWR.Pause()){
			pmAudioWR.SetRecordPlaying(false);
			pmAudioWR.SetRecPlayingPaused(true);
		};
		return;
	}

	CCLOG("NO AUDIO PLAYING");

	pmAudioWR.SetRecorderBuffer();

	log("Audiorecord 2");

	// we push again the record buffer
	// content only if the record/player
	// changed or player is stopped
	if (newRecording || (!isRecordPlaying && !isRecPlayingPaused))
	{
		CCLOG("CALL ENQUEUE");
		log("Audiorecord ENQUEUE");

		if (pmAudioWR.EnqueueClip(true))
		{
			newRecording = false;
			log("Audiorecord ENQUEUE -> OK !!");
		}
	}

	// we play anyway
	if (pmAudioWR.Play()){
		pmAudioWR.SetRecPlayingPaused(false);
		pmAudioWR.SetRecordPlaying(true);
	};
}


//main loop
void WordReading::update(float delta)
{
     pmAudioWR.Update();

  //  recorderLabel->setString((isAudioRecording) ? "RECORDING" : "No recording");
  //  audioRecPlayerStateLabel->setString((isRecordPlaying) ? "* PLAYING *" : "Paused");
}



//////
void WordReading::addHomeButton() {
    
    cocos2d::ui::Button *backNode = cocos2d::ui::Button::create("common/homeBtn.png",
																"common/homeBtn.png",
																"common/homeBtn.png");
    backNode->setScale(0.9);
    backNode->setName("HomeButton");
    backNode->setAnchorPoint(Vec2(0.5, 0.5));
    
    auto x = 90;
    
    
    float winHeight = cocos2d::Director::getInstance()->getWinSize().height;
    float rootNodeHeight = rootNode->getBoundingBox().size.height;
    
    float y = winHeight;
    if ( winHeight > rootNodeHeight ) { // like iPad
        float delta = (winHeight-rootNodeHeight) / 2;
        y = rootNode->getBoundingBox().size.height + delta - (backNode->getBoundingBox().size.height/2);
    }
    y = y - (backNode->getBoundingBox().size.height /2);
    
    
    backNode->setPosition(Vec2(x, y));
    rootNode->addChild(backNode,100);
    
    backNode->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                Logger::getInstance()->logEvent(NAME, Logger::CLOSE, "");
                
                if ( TEST_ENABLED ) {
                    DataProvider::getInstance()->setGameCompleted(NAME);
                    DataProvider::getInstance()->setWatchmanReaction(WatchmanScene::GOOD_REACTION);
                } else {
                    DataProvider::getInstance()->setWatchmanReaction(WatchmanScene::BAD_REACTION);
                }
                
                simpleAudioEngine->stopBackgroundMusic();
                _director->replaceScene(TransitionFade::create(TRANSITION_TIME, WatchmanScene::createScene(), TRANSITION_COLOR));
                break;
            default:
                break;
        }
    });
    
}

vector<string> WordReading::split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}






void WordReading::endGame() {
    
    
    Logger::getInstance()->logEvent(NAME, Logger::CLOSE, "");
    
    DataProvider::getInstance()->setGameCompleted(NAME);
    DataProvider::getInstance()->setWatchmanReaction(WatchmanScene::GOOD_REACTION);
 
    simpleAudioEngine->stopBackgroundMusic();
    _director->replaceScene(TransitionFade::create(TRANSITION_TIME, WatchmanScene::createScene(), TRANSITION_COLOR));
}
    
