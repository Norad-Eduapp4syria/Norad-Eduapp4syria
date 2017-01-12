#include "ListComprehens.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "../Utils/GameObject.h"
#include "../Utils/Data/DataProvider.h"
#include "../Utils/Data/Logger.h"
#include "../WatchmanScene/WatchmanScene.h"
#include "../Utils/StringUtility.h"
#include "../AppMacros.h"
#include "../Utils/Data/ArabicHelper.h"
#include "../Utils/Data/ArabicHelperForGames.h"

USING_NS_CC;

const std::string ListComprehens::PATH = "ListComprehens/";
std::string ListComprehens::NAME = ""; // To set

using namespace cocostudio::timeline;

// round manager
int ListComp_RoundManager::target;
int ListComp_RoundManager::objID;
int ListComp_RoundManager::colorID;
int ListComp_RoundManager::bigObjID;
int ListComp_RoundManager::triggerBigID;
int ListComp_RoundManager::characterID;
int ListComp_RoundManager::sideCharacterID;
int ListComp_RoundManager::charID[2];
int ListComp_RoundManager::chosenCharID;
int ListComp_RoundManager::draggedObjID;
string ListComp_RoundManager::sentence;
bool ListComp_RoundManager::roundActive;
bool ListComp_RoundManager::boolTriggers[N_BIG_TRIGS_OBJS];
const Sprite *ListComp_RoundManager::bigTrigCollider[N_BIG_TRIGS_OBJS];
const Sprite *ListComp_RoundManager::charCollider[2]; 
//temp !!!!
MenuItemImage *newRoundItem;

Scene* ListComprehens::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ListComprehens::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}



// on "init" you need to initialize your instance
bool ListComprehens::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    CCLOG("Type Game: %s", NAME.c_str());
    
    simpleAudioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
    
	//temp button
	newRoundItem = MenuItemImage::create(
		PATH+"PNG/Dummy.png",
		PATH+"PNG/Dummy.png",
		CC_CALLBACK_1(ListComprehens::callback_NewRound, this));
	newRoundItem->setPosition(Vec2(50, 600));
	
	auto menu = Menu::create(newRoundItem, NULL);
	menu->setPosition(Vec2(10, 10));
	this->addChild(menu, 1);

    rootNode = CSLoader::createNode(PATH + "MainScene.csb");

    rootNode->setAnchorPoint(Point(0.5, 0.5));
    rootNode->setPosition(Point(_director->getWinSize().width / 2, 
								_director->getWinSize().height / 2));
    addChild(rootNode);
	
    objWell = nullptr;
    objTry = nullptr;
    
    
	roundNumber = 0;
	// round settings
	for (int c = 0; c < roundNumbers; c++)
	{
		rounds[c] = new RoundSettings(c);
		
		// if you want to set ...
		/*
		rounds[c]->isRandom = true;
		rounds[c]->rightCharacterID = limbo;
		rounds[c]->rightTriggerID = limbo;
		rounds[c]->rightDragObjID = limbo;
		rounds[c]->rightColorID = limbo;
		*/
	}


	// for fading
	Size s = _director->getWinSize();
	objFade = new GameObject(*rootNode, Vec2(s.width / 2, s.height / 2));
	fadeSprite = Sprite::create();
	objFade->getNode().addChild(fadeSprite);	
	
	fadeSprite->setTexture(PATH+"PNG/blankPixel.png");
	fadeSprite->setPositionZ(20);
	fadeSprite->setScale(500, 500);
	fadeSprite->runAction(FadeOut::create(0.5f));

	// help hand
	objHelpHand = new GameObject(*rootNode, "help_hand", 
								  PATH + "CSD/HELP_Hand_1.csb", 
								         "Bone_mano/Manina_1");

	ListComp_RoundManager::draggedObjID = limbo;
    startGame();
    
    scoreToSubtract = 10.0f;
    roundScorePercent[roundNumber] = 100.0f;
    
    
    // audio
    simpleAudioEngine->preloadBackgroundMusic("common/audio/bg/GAME_2.mp3");
    simpleAudioEngine->playBackgroundMusic("common/audio/bg/GAME_2.mp3", true);
    //
    

    return true;
}


void ListComprehens::callback_NewRound(Ref* pSender)
{
   objFade->bringToFront();
 
   fadeSprite->runAction(
		Sequence::create(FadeIn::create(0.2f), 
		CallFunc::create([=]() {
	     fadeSprite->runAction(FadeOut::create(0.4f));
		 // sets a new round
		 // with no new instances
		 setDraggableObjects();
		 setNewRound();
	}),
		nullptr
		)
	);
}

// randomize excluding values function
int ListComprehens::getRandomWithExclusion(int start, int end, vector<int> exclude)
{
	int size = exclude.size();
	int random = cocos2d::RandomHelper::random_int(start, end);
	for (int c = 0; c < size; c++)
	{
		if (random == exclude[c])
		{
			return getRandomWithExclusion(start, end, exclude);
			break;
		}
	}
	return random;
}


void ListComprehens::startGame() 
{
	// store the big obj and char pos
	bigObjOriginalPos = rootNode->getChildByName("obj_BIG")->getPosition();
	char1OriginalPos = rootNode->getChildByName("char_01")->getPosition();
	char2OriginalPos = rootNode->getChildByName("char_02")->getPosition();

    // compose the background
	objFondale = new GameObject(*rootNode, "background",
									  PATH + "CSD/fondale_formazione.csb");
	objFondale->play("compositing");

	// initialize the draggable objects list
	setGridObjects();
	setDraggableObjects();

	//set big objects
	objBig = new GameObject(*rootNode, "obj_BIG", PATH + "CSD/object_big.csb",
									                     "Bone_object_big/object_big_1");
	
	// set grid big objects triggers instances
	for (int c = 0; c < N_BIG_TRIGS_OBJS; c++)
	{
		string path = "obj_ref0" + StringUtility::toString(c + 1);
		string spr = "Sprite_ref0" + StringUtility::toString(c + 1);
		bigTriggersObj[c] = new GameObject(*rootNode, path,
											PATH + "CSD/object_small.csb",
											//"bone_object_small/reference"
											spr);
		bigTriggersObj[c]->getChild("bone_spiral")->setOpacity(0);
		bigTriggersObj[c]->getChild("bone_spiral/bone spiral")->setOpacity(0);
		static_cast<Sprite*>(bigTriggersObj[c]->getChild("bone_spiral/bone spiral"))->setTexture("");
		static_cast<Sprite*>(bigTriggersObj[c]->getChild("bone_object_small/reference"))->setTexture("");
		ListComp_RoundManager::bigTrigCollider[c] = bigTriggersObj[c]->getColliderSprite();
	}


	// set sign
	objSign = new GameObject(*rootNode, "sign", PATH + "CSD/Sign.csb");
	lblSentence = ArabicHelper::getInstance()->createLabel("", 35); //Label::createWithTTF("SENTENCE", "common/fonts/NO/Century Gothic Regular.ttf", 40);
	static_cast<Sprite*>(objSign->
		getChild("Bone_sign/sign_1"))->
		addChild(lblSentence);

    
    if (NAME == "ListComprehens") {
        addListenButton();
    }
    
    
	// set rounds	
	setNewRound();
    addBackToHomeButton();
}

void ListComprehens::setNewRound()
{
	// it is a character or big object situation?
	// roll it ...
	if (cocos2d::RandomHelper::random_int(0, 100) < roundBalancer) //(1 == 1)
	{
		roundBalancer -= cocos2d::RandomHelper::random_int(5, 20);
		if (roundBalancer <= 10 || roundBalancer >= 90)
			roundBalancer = 50;

		// char
		ListComp_RoundManager::target = 0;
		
		Node *chNode1 = rootNode->getChildByName("char_01");
		Node *chNode2 = rootNode->getChildByName("char_02");

		chNode1->getChildren().clear();
		chNode2->getChildren().clear();

        if (characterObj[0] != nullptr) {
            delete(characterObj[0]);
            characterObj[0] = nullptr;
        }
        if (characterObj[1] != nullptr) {
            delete(characterObj[1]);
            characterObj[1] = nullptr;
        }
	
		// set and append characters
		vector<int> pickedChars;

		// if the round is random picks random, else picks from settings
		ListComp_RoundManager::characterID = (rounds[roundNumber]->isRandom) ?
			                           cocos2d::RandomHelper::random_int(0, N_CHARS - 1)
									   : rounds[roundNumber]->rightCharacterID;

		pickedChars.push_back(ListComp_RoundManager::characterID);
		ListComp_RoundManager::sideCharacterID = getRandomWithExclusion(0, N_CHARS - 1, pickedChars);
	
		// shuffle
		ListComp_RoundManager::chosenCharID = 0;
		int p1 = ListComp_RoundManager::characterID,
			p2 = ListComp_RoundManager::sideCharacterID;
		
		if (cocos2d::RandomHelper::random_int(0, N_CHARS - 1))
		{
			ListComp_RoundManager::chosenCharID = 1;
			p2 = ListComp_RoundManager::characterID,
			p1 = ListComp_RoundManager::sideCharacterID;
		}

		// reset chosenCharID because it will be
		// set again when the player will drop the drag
		// on a character
		ListComp_RoundManager::chosenCharID = limbo;

		//instance
		ListComp_RoundManager::charID[0] = p1;
		ListComp_RoundManager::charID[1] = p2;

		Vec2 pos1 = char1OriginalPos;
		Vec2 pos2 = char2OriginalPos;

		pos1.x -= 250;
		pos2.x -= 250;
		
		characterObj[0] = new GameObject(*chNode1, Vec2(0, 0), 
										  PATH + "CSD/" + objChars[p1] + ".csb", 
										  "MASTER/Bone_body/man_body");

		characterObj[1] = new GameObject(*chNode2, Vec2(0, 0), 
										  PATH + "CSD/" + objChars[p2] + ".csb", 
										  "MASTER/Bone_body/man_body");
		
		// scroll chars from outscreen to right
		chNode1->setPosition(pos1);
		chNode2->setPosition(pos2);

		auto moveTo1 = MoveTo::create(0.4f, char1OriginalPos);
		auto moveTo2 = MoveTo::create(0.4f, char2OriginalPos);

		chNode1->runAction(moveTo1);
		chNode2->runAction(moveTo2);

		// set colliders for chars
		ListComp_RoundManager::charCollider[0] = characterObj[0]->getColliderSprite();
		ListComp_RoundManager::charCollider[1] = characterObj[1]->getColliderSprite();

		prefix = "give the";
		conc = "to the";
		suffix = objCharNames[ListComp_RoundManager::characterID];
		
		characterObj[0]->bringToFront();

		characterObj[0]->play("idle", nullptr, true);
		characterObj[1]->play("idle", nullptr, true);
	}
	else
	{
		roundBalancer += cocos2d::RandomHelper::random_int(5, 20);
		if (roundBalancer <= 10 || roundBalancer >= 90)
			roundBalancer = 50;

		// big objects	
		ListComp_RoundManager::target = 1;
		
		ListComp_RoundManager::bigObjID = cocos2d::RandomHelper::random_int(0, N_BIG_OBJS - 1);
		ListComp_RoundManager::triggerBigID = (rounds[roundNumber]->isRandom) ?
									  cocos2d::RandomHelper::random_int(0, N_BIG_TRIGS_NAMES - 1)
									  : rounds[roundNumber]->rightTriggerID;

		for (int c = 0; c < N_BIG_TRIGS_OBJS; c++)
			ListComp_RoundManager::boolTriggers[c] = false;

		switch (ListComp_RoundManager::triggerBigID)
		{
			case 0:  //top
			case 5:
			    ListComp_RoundManager::boolTriggers[0] = true;
			    break;
		 
			case 1: //left or right
		        ListComp_RoundManager::boolTriggers[1] = true;
				ListComp_RoundManager::boolTriggers[3] = true;
				break;

			case 2: //under
				ListComp_RoundManager::boolTriggers[2] = true;
				break;

			case 3: //right
				ListComp_RoundManager::boolTriggers[3] = true;
				break;

			case 4: //left
				ListComp_RoundManager::boolTriggers[1] = true;
				break;
		}
		
		prefix = "put the";
		conc = objBigTriggerNames[ListComp_RoundManager::triggerBigID];
		suffix = objBigNames[ListComp_RoundManager::bigObjID];

		// Scroll big object to right
		Node *bigObjNode = rootNode->getChildByName("obj_BIG");
		Vec2 pos = bigObjNode->getPosition();
		pos.x -= 300;
		bigObjNode->setPosition(pos);

		auto moveTo = MoveTo::create(0.4f, bigObjOriginalPos);
		bigObjNode->runAction(moveTo);
	}
	
 
    // reset the score for this round
    roundScorePercent[roundNumber] = 100.0f;
	
	// sets the current right obj and color id
	// to round manager
	ListComp_RoundManager::objID = chosenGridID;
	ListComp_RoundManager::colorID = rightColorID;

	// sentence
	//sentence = prefix + " " + objColorNames[rightColorID] + " " + objNames[rightObjID] + " " + conc + " " + suffix; // english
    // sentence = suffix + " " + conc + " " + objNames[rightObjID] + " " + objColorNames[rightColorID]  + " " + prefix; // arabic
    
    string sentenceInEnglish = prefix + " " + objColorNames[rightColorID] + " " + objNames[rightObjID] + " " + conc + " " + suffix;
    
    CCLOG("sentenceInEnglish scritta: %s", sentenceInEnglish.c_str());
    /*
    sentence = ArabicHelperForGames::getInstance()->getInArabic(suffix) + " " +
               ArabicHelperForGames::getInstance()->getInArabic(conc) + " " +
               ArabicHelperForGames::getInstance()->getInArabic(objColorNames[rightColorID])  + " " +
               ArabicHelperForGames::getInstance()->getInArabic(objNames[rightObjID]) + " " +
               ArabicHelperForGames::getInstance()->getInArabic(prefix);
    */
    
    sentence = ArabicHelperForGames::getInstance()->getInArabic(prefix) + " " +
                ArabicHelperForGames::getInstance()->getInArabic(objNames[rightObjID]) + " " +
                ArabicHelperForGames::getInstance()->getInArabic(objColorNames[rightColorID])  + " " +
                ArabicHelperForGames::getInstance()->getInArabic(conc) + " " +
                ArabicHelperForGames::getInstance()->getInArabic(suffix);
    
    CCLOG("sentence in arabo scritta: %s", sentence.c_str());
    
    sentenceToRead = prefix + "#" + objNames[rightObjID] + "#" + objColorNames[rightColorID]  + "#" + conc +  "#" + suffix;
    
    CCLOG("sentenceToRead in arabo: %s", sentenceToRead.c_str());
    
	// update the round manager settings
	ListComp_RoundManager::sentence = sentence;

	// set big objects and characters
	if (ListComp_RoundManager::characterID != limbo)
	{
		// chars	
		objBig->setVisible(false);
	}
	else
	{
		// big obj
		objBig->setVisible(true);

		// sets chars invisible
		if (characterObj[0] != nullptr)
		{
			characterObj[0]->setVisible(false);
			characterObj[1]->setVisible(false);
		}
	
		//set big object sprite
		static_cast<Sprite*>(objBig->
			getChild("Bone_object_big/object_big_1"))->
			setTexture(PATH+"object_big/" +
			objBigNames[ListComp_RoundManager::bigObjID] + ".png");
	}

    // Set the sentence sign
    if (NAME == "ReadComprehens")	{
        setSign();
    } else if (NAME == "ListComprehens") {
        // listenBtn = new GameObject(*rootNode, "listen_button", PATH + "CSD/listen_button.csb");
        // listenBtn->play("button_popin");
        playAudioCommand();
    }

	//hand sequence
	objHelpHand->bringToFront();
	objHelpHand->getNode().runAction
		(
		Sequence::create(FadeIn::create(0.2f),
		CallFunc::create([=]()
	{
		static_cast<Sprite*>(objHelpHand->
			getChild("Bone_mano/Manina_1"))->
			runAction(FadeIn::create(0.2f));
		objHelpHand->play("drag", nullptr, true);
	}),
		nullptr
		)
	);
}

void ListComprehens::playAudioCommand()
{
    CCLOG("sentenceToRead = %s", sentenceToRead.c_str());
        
    std::replace( sentenceToRead.begin(), sentenceToRead.end(), ' ', '_'); // replace all ' ' to '_'
    sentenceToRead = StringUtility::toLowerCase(sentenceToRead);
    
    vector<string> wordsVectorSplitted = StringUtility::split(sentenceToRead, '#');
    float delay = 0.0;
    int idx;
    for (idx = 0; idx< wordsVectorSplitted.size(); idx++ ) {
        string currentWord = wordsVectorSplitted.at(idx);
        string prevWord = "";
        if (idx > 0 ) {
            prevWord = wordsVectorSplitted.at(idx-1);
        }
        
        CCLOG(">> %s", currentWord.c_str());
        
        CallFunc *runCallback_fruit5 = CallFunc::create(CC_CALLBACK_0(ListComprehens::playAudioCommandPart, this, currentWord));
        
        delay += (0.25 * prevWord.length());
        
        this->runAction(Sequence::create(DelayTime::create(delay), runCallback_fruit5, nullptr));
        //this->runAction(Sequence::create(DelayTime::create(idx*1.6), runCallback_fruit5, nullptr));
    }
    
    
    
}

void ListComprehens::playAudioCommandPart(string word) {
    simpleAudioEngine->playEffect((PATH + "audio/"+ word + ".mp3").c_str());
}

void ListComprehens::setSign()
{
	// set sentence
	lblSentence->setPositionZ(10);
	lblSentence->setString(sentence);
    lblSentence->setVerticalAlignment(TextVAlignment::CENTER) ;
    lblSentence->setHorizontalAlignment(TextHAlignment::CENTER);
	lblSentence->enableWrap(true);
	lblSentence->setDimensions(550, 130);
	//lblSentence->setOverflow(Label::Overflow::CLAMP);
	lblSentence->setAnchorPoint(Vec2(-0.25f, -0.5f));
	lblSentence->setColor(Color3B(102, 51, 51));  //#663333
	//
	objSign->play("sign_popin");
}

void ListComprehens::setGridObjects()
{

    int c = 0;
    
    if (cDraggableObj[0] != nullptr)  {
        for (c = 0; c < N_DRAG_OBJS; c++) {
            delete(cDraggableObj[c]);
            cDraggableObj[c] = nullptr;
        }
    }
    
	// set grid draggable objects instances
	for (c = 0; c < N_DRAG_OBJS; c++)
	{
		cDraggableObj[c] = new ListComp_DragGO(*rootNode, "obj_0" + StringUtility::toString(c + 1),
			PATH + "CSD/object_small.csb",
			"bone_object_small/reference", _eventDispatcher);

		// set original pos
		cDraggableObj[c]->originalPos = cDraggableObj[c]->getPosition();
	}
}

void ListComprehens::callback_TouchBegan()
{
	// reset chosenCharID because it will be
	// set again when the player will drop the drag
	// on a character
	ListComp_RoundManager::chosenCharID = limbo;

	static_cast<Sprite*>(objHelpHand->
		getChild("Bone_mano/Manina_1"))->
	              runAction(FadeOut::create(0.2f));
}

void ListComprehens::callback_SUCCESS()
{
	
	for (int c = 0; c < N_DRAG_OBJS; c++)
	{
		cDraggableObj[c]->getChild("bone_spiral/bone spiral")->setOpacity(0);
		if (cDraggableObj[c]->index != chosenGridID
			&& cDraggableObj[c]->isActive)
			cDraggableObj[c]->play("pop_out", [=](){
			cDraggableObj[c]->SetOpacity(0);
			cDraggableObj[c]->clearLastFrameCallFunc();
		});
	}
	cDraggableObj[chosenGridID]->getChild("bone_spiral/bone spiral")->setOpacity(255);


	// if chars round, we make 
	// the right obj to disappear
	if (ListComp_RoundManager::target == 0)
		cDraggableObj[chosenGridID]->play("pop_out", [=](){ 
		             cDraggableObj[chosenGridID]->SetOpacity(0); 
					 cDraggableObj[chosenGridID]->getChild("bone_spiral/bone spiral")
											    ->setOpacity(0);
					 cDraggableObj[chosenGridID]->clearLastFrameCallFunc(); 
	});

	// the character plays a positive feedback
	if (ListComp_RoundManager::target == 0)
		characterObj[ListComp_RoundManager::chosenCharID]->play("Positive");

	GameObject *objWell = new GameObject(*rootNode, "well_done", PATH + "CSD/SEMA_Well.csb");
	objWell->bringToFront();

	// play well done animation
	runAction(
		Sequence::create(
		//DelayTime::create(1.f),
		CallFunc::create(
		[=]() {
		objWell->play("Well_Apparizione");
	}),
		DelayTime::create(2.f),
		CallFunc::create(
		[=]() {
		objWell->play("Well_Sparizione", [=]() {
		
			// if was the last round, log + end
			if (roundNumber == roundNumbers - 1)
			{
				log("ROUNDS ARE OVER !!!");


                // calcoliamo il total score
                for (int c = 0; c < roundNumbers; c++)
                    scorePercent += roundScorePercent[c];
                
                // media dello score
                scorePercent /= roundNumbers;
                
                
                Logger::getInstance()->logEvent(NAME, Logger::CLOSE, "");
                DataProvider::getInstance()->setGameCompleted(NAME);
                DataProvider::getInstance()->setWatchmanReaction(WatchmanScene::GOOD_REACTION);
                simpleAudioEngine->stopBackgroundMusic();
                _director->replaceScene(TransitionFade::create(TRANSITION_TIME, WatchmanScene::createScene(), TRANSITION_COLOR));
                
				objWell->clearLastFrameCallFunc();
				return;
			}
			else
				// else increment 
				roundNumber++;

			//
			// IF YOU WANT TO MANAGE THE ROUND CHANGE WITH A BUTTON:
			// newRoundItem->setVisible(true);
            // ELSE here's a callback with null sender:
			callback_NewRound(nullptr);
			// stop disappear animation
			objWell->clearLastFrameCallFunc();
		});
	}),
		nullptr
		)
	);
}

void ListComprehens::callback_FAIL()
{
       // subtract score
       roundScorePercent[roundNumber] -= scoreToSubtract;
       CCLOG("score di questo round ora vale: %f", roundScorePercent[roundNumber]);
  
	// the character plays negative feedback
	if (ListComp_RoundManager::target == 0 && ListComp_RoundManager::chosenCharID != limbo)
	{
		characterObj[ListComp_RoundManager::chosenCharID]->play("negative", [=]() {
			characterObj[ListComp_RoundManager::chosenCharID]->play("idle", nullptr, true);
			characterObj[ListComp_RoundManager::chosenCharID]->clearLastFrameCallFunc();
		});
	}
	//characterObj[RoundManager::chosenCharID]->play("negative");

	GameObject *objTry = new GameObject(*rootNode, "try_again", PATH + "CSD/SEMA_Try.csb");
	objTry->bringToFront();

	// play well done animation
	runAction(
		Sequence::create(
		//DelayTime::create(1.f),
		CallFunc::create(
		[=]() {
		objTry->play("Well_Apparizione");
	}),
		DelayTime::create(2.f),
		CallFunc::create(
		[=]() {
		objTry->play("Well_Sparizione", [=]() {
			// log..
			objTry->clearLastFrameCallFunc();
		});
	}),
		nullptr
		)
		);

	/*GameObject *objTry = new GameObject(*rootNode, "try_again", PATH + "CSD/SEMA_Try.csb");
	objTry->bringToFront();
	objTry->play("Try_Apparizione", [=](){ 
		objTry->play("Try_Sparizione"); 
		objTry->clearLastFrameCallFunc(); 
	});*/
}

void ListComprehens::setDraggableObjects()
{
	CCLOG("loading");
	
	// reset objects and settings
	resetScene();

	// we need a list of picked object and color id from the whole collection
	vector<int> pickedObjs, pickedColors;
	// and a list of picked object id from the grid collection
	vector<int> pickedGridObjs;

	// randomize the right object and his right color
	rightObjID = (rounds[roundNumber]->isRandom) ?
				  cocos2d::RandomHelper::random_int(0, N_ALL_DRAG_OBJS - 1)
		          : rounds[roundNumber]->rightDragObjID;
	
	rightColorID = (rounds[roundNumber]->isRandom) ?
				    cocos2d::RandomHelper::random_int(0, N_COLORS - 1)
					: rounds[roundNumber]->rightColorID;

	// push the chosen one in the list of picked ones
	pickedObjs.push_back(rightObjID);
	pickedColors.push_back(rightColorID);

	// set the right object and color to a specific object on the grid
	int chosenGrid_0 = cocos2d::RandomHelper::random_int(0, N_DRAG_OBJS - 1);
	chosenGridID = chosenGrid_0;
	cDraggableObj[chosenGrid_0]->name = rightObjID;
	cDraggableObj[chosenGrid_0]->index = chosenGridID;
	cDraggableObj[chosenGrid_0]->color = rightColorID;

	// push the chosen grid obj into the grid-picked list
	pickedGridObjs.push_back(chosenGrid_0);
	pickedColors.push_back(rightColorID);

	// now we need to pick side colors from the correct
	// one and set to other two rnd objects on the grid

	// pick other two colors from the main list
	int chosenColor_1 = getRandomWithExclusion(0, N_COLORS - 1, pickedColors);
	pickedColors.push_back(chosenColor_1);
	
	int chosenColor_2 = getRandomWithExclusion(0, N_COLORS - 1, pickedColors);
	pickedColors.push_back(chosenColor_2);

	// choose other two objects from the list randomly
	int chosenGrid_1 = getRandomWithExclusion(0, N_DRAG_OBJS - 1, pickedGridObjs);
	pickedGridObjs.push_back(chosenGrid_1);
	
	int chosenGrid_2 = getRandomWithExclusion(0, N_DRAG_OBJS - 1, pickedGridObjs);
	pickedGridObjs.push_back(chosenGrid_1);

	// we make sure the correct object wont pop up again
	pickedObjs.push_back(rightObjID);

	// so these two are same of the righe one ...
	cDraggableObj[chosenGrid_1]->name = rightObjID;
	cDraggableObj[chosenGrid_2]->name = rightObjID;

	// ... but with two alternate colors
	cDraggableObj[chosenGrid_1]->color = chosenColor_1;
	cDraggableObj[chosenGrid_2]->color = chosenColor_2;		

	// now, we pick the rest of the grid list and associate
	// every object to the rest of unpicked objects randomly

	for (int c = 0; c < N_DRAG_OBJS; c++)
	{
		// if not yet set
		if (cDraggableObj[c]->name == limbo)
		{
			cDraggableObj[c]->name = getRandomWithExclusion(0, N_ALL_DRAG_OBJS - 1, pickedObjs);
			cDraggableObj[c]->index = c;
			pickedObjs.push_back(cDraggableObj[c]->name);
			pickedGridObjs.push_back(c);

			// we dont need to exclude any color for the wrong objects
			cDraggableObj[c]->color = cocos2d::RandomHelper::random_int(0, N_COLORS - 1);
		}
	}

	// now we can create the real objects on screen and set sprites
	string name, color, fileName;
	for (int c = 0; c < N_DRAG_OBJS; c++)
	{
		// fill the file name with related properites
		name = objNames[cDraggableObj[c]->name];
		color = objColors[cDraggableObj[c]->color];
		fileName = name + color + ".png";

		// set the sprite
		static_cast<Sprite*>(cDraggableObj[c]->
							  getChild("bone_object_small/reference"))->
							   setTexture(PATH+"object_small/" + fileName);

		// play pop animation
		cDraggableObj[c]->SetOpacity(255);
		cDraggableObj[c]->play("pop_in");
		
		// make it draggable
		cDraggableObj[c]->setTouchable(true);
		cDraggableObj[c]->setSwallow(true);

		// bring to front
		cDraggableObj[c]->bringToFront();

		//set callback
		cDraggableObj[c]->setTouchBeganCallBack(bind(&ListComprehens::callback_TouchBegan, this));
		cDraggableObj[c]->setSuccessCallBack(bind(&ListComprehens::callback_SUCCESS, this));
		cDraggableObj[c]->setFailCallBack(bind(&ListComprehens::callback_FAIL, this));
	}		
}


void ListComprehens::resetScene()
{
	for (int c = 0; c < N_DRAG_OBJS; c++)
	{
		cDraggableObj[c]->name = limbo;
		cDraggableObj[c]->index = limbo;
		cDraggableObj[c]->color = limbo;
		cDraggableObj[c]->isActive = true;
		cDraggableObj[c]->setPosition(cDraggableObj[c]->originalPos);
	}

	ListComp_RoundManager::roundActive = true;
	ListComp_RoundManager::objID = limbo;
	ListComp_RoundManager::colorID = limbo;
	ListComp_RoundManager::bigObjID = limbo;
	ListComp_RoundManager::triggerBigID = limbo;
	ListComp_RoundManager::characterID = limbo;
	ListComp_RoundManager::sideCharacterID = limbo;
	ListComp_RoundManager::sentence = "";

	newRoundItem->setVisible(false);
}


ListComprehens::ListComprehens()
{

}

ListComprehens::~ListComprehens()
{
	// delete objects ...
	
    if (characterObj[0] != nullptr) {
        delete(characterObj[0]);
        characterObj[0] = nullptr;
    }
    if (characterObj[1] != nullptr) {
        delete(characterObj[1]);
        characterObj[1] = nullptr;
    }
    
	delete(objFade);
	delete(objHelpHand);
    
    delete objFondale;
    delete objBig;
    delete objSign;
    
    if (objWell != nullptr) delete objWell;
    if (objTry != nullptr) delete objTry;
    
    int c = 0;
	for (c = 0; c < N_BIG_TRIGS_OBJS; c++)
		delete(bigTriggersObj[c]);

    if (cDraggableObj[0] != nullptr)  {
        for (c = 0; c < N_DRAG_OBJS; c++) {
            delete(cDraggableObj[c]);
            cDraggableObj[c] = nullptr;
        }
    }
    
    
    if (rounds[0] != nullptr)  {
        int arrayLength = sizeof(rounds)/sizeof(rounds[0]);
        for (c = 0; c < arrayLength; c++) {
            delete(rounds[c]);
            rounds[c] = nullptr;
        }
    }

}


void ListComprehens::addListenButton(){
    
    
    auto backNode = cocos2d::ui::Button::create(PATH+"PNG/listen_button.png", PATH+"PNG/listen_button.png", PATH+"PNG/listen_button.png");
    
    auto frameSize = cocos2d::Director::getInstance()->getWinSize();
    auto x = frameSize.width - 90;//frameSize.width * 0.5f;
    auto y = frameSize.height * 0.9f;
    backNode->setPosition(Vec2(x,y));
    addChild(backNode, 10);
    
    backNode->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                playAudioCommand();
                break;
            default:
                break;
        }
    });
    
}


void ListComprehens::addBackToHomeButton(){
    
    auto backNode = cocos2d::ui::Button::create("common/homeBtn.png", "common/homeBtn.png", "common/homeBtn.png");
    
    auto frameSize = cocos2d::Director::getInstance()->getWinSize();
    auto x = 90;//frameSize.width * 0.5f;
    auto y = frameSize.height * 0.9f;
    backNode->setPosition(Vec2(x,y));
    addChild(backNode, 10);
    
    backNode->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
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

