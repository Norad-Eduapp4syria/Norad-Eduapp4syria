#include "LettersGame.h"
#include "../Utils/StringUtility.h"
#include "../Utils/Data/ArabicHelper.h"

using namespace std;

template<> const bool kukua::Game<LettersGame>::USE_PHYSICS = false;										// Enable/disable physics
template<> const bool kukua::Game<LettersGame>::ENABLE_TOUCH = true;										// Used to disable tutorial on first touch and manage general touch events
template<> string kukua::Game<LettersGame>::PATH = "LettersGame/";									// Resources' subfolder path for this game
template<> const string kukua::Game<LettersGame>::BACKGROUND_MUSIC_FILENAME = "";		// Background music filename
template<> bool kukua::Game<LettersGame>::SHOWN_TUTORIAL = false;											// Used for showing tutorial on first execution, set to true only if tutorial is not needed
template<> Scene* kukua::Game<LettersGame>::scene = nullptr;
template<> const string kukua::Game<LettersGame>::NAME = "LettersGame";

LettersGame::~LettersGame() {

	CCLOG("~LettersGame");

    //azzeriamo i timer
    this->stopActionByTag(99);
    this->unschedule(schedule_selector(LettersGame::subtractScore));
    this->unscheduleUpdate();
    
	// Delete objects created with new

    if (letter != nullptr) {
        delete letter;
    }
	delete help;
        
    if (hand != nullptr) {
        delete hand;
    }
    
    if (handTutorial != nullptr) {
        delete handTutorial;
    }
    

    
    
	for (int i = 0; i < arrayAllShape.size(); i++) {
		delete arrayAllShape[i];
	}
	for (int i = 0; i < arrayAnt.size(); i++) {
		delete arrayAnt[i];
	}

}



void LettersGame::playAutomatic(){
	// CCLOG("LettersGame - playAutomatic");
	
	if(actualShape<arrayConfigLetter[letterID][actualStep - 1][1]){
		GameObject* appPoint = arrayPoint[actualShape];
		int appstep = actualStep;
		simpleAudioEngine->playEffect("LettersGame/audio/shape_pop.mp3");
		arrayPoint[actualShape]->play("shape_pop", ([=]() {
			if (stateInteraction == 1 || actualStep>appstep) {
				appPoint->play("shape_loop", nullptr, true);
			}
			appPoint->getActionTimeline()->clearLastFrameCallFunc();
		}) , false);
		



		MoveTo *handTutorialMoveActionAc = MoveTo::create(0.01, Vec2(arrayPoint[actualShape]->getPosition().x, arrayPoint[actualShape]->getPosition().y));
		auto handTutorialMoveAction = EaseSineInOut::create(handTutorialMoveActionAc->clone());
		handTutorial->play(handTutorialMoveAction);

		actualShape++;
		stateInteraction = 1;




		CallFunc *runCallback_auto = CallFunc::create(CC_CALLBACK_0(LettersGame::playAutomatic, this));
		this->runAction(Sequence::create(DelayTime::create(0.1), runCallback_auto, nullptr));

			
	}else{
        
		MoveTo *handTutorialMoveActionAc = MoveTo::create(0.01, Vec2(arrayMarker[arrayMarker.size() - 1]->getPosition().x, arrayMarker[arrayMarker.size() - 1]->getPosition().y));
		auto handTutorialMoveAction = EaseSineInOut::create(handTutorialMoveActionAc->clone());
		handTutorial->play(handTutorialMoveAction);
		

		stateInteraction = 3;
		arrayMarker[arrayMarker.size() - 1]->play("marker_spiral", nullptr, false);
		simpleAudioEngine->playEffect("LettersGame/audio/pop_marker_spirale.mp3");
		simpleAudioEngine->playEffect("LettersGame/audio/step_markertomaker.mp3");
		setObjectStep();

		
			
	}

	
}


void LettersGame::initVariables() {

	CCLOG("LettersGame - Init variables");
 
    step = 0;
    actualStep = 0;
	actualShape = 0;
	stateInteraction = 3; // 0=ready 1=progress 2=cancellation 3=changestep or finish

    letter = nullptr;
    hand = nullptr;
    handTutorial = nullptr;
    
    
    hiatusTimer = 20.0f;
    singleInterval = 0.5f;
    scorePercent = 100.0f;
    unitScoreToSubtract = 1.0f;
    
    
    phonemesToPlay = 1;
    if (DataProvider::getInstance()->getCurrentEpisode() == 3) {
        phonemesToPlay = 3;
    }
    
    
    if (DataProvider::getInstance()->getCurrentEpisode() == 1) {
        showHelp = true;
        showMiddlePhase = true;
    } else {
        showHelp = false;
        showMiddlePhase = false;
    }
    

    
    if (showHelp) {
        level = 1;
    } else {
        level = 2;
    }
    int skin = DataProvider::getInstance()->getSkin();
    
    static_cast<Sprite*>(rootNode->getChildByName("background"))->setTexture(PATH+"png/background/background_" +  StringUtility::toString(skin) + ".png");
    
    
    
}

void LettersGame::initAudio() {

	CCLOG("LettersGame - Init audio");

	simpleAudioEngine->preloadEffect("LettersGame/audio/Letter_enter.mp3");
	simpleAudioEngine->preloadEffect("LettersGame/audio/marker_pop.mp3");
	simpleAudioEngine->preloadEffect("LettersGame/audio/pop_marker_spirale.mp3");
	simpleAudioEngine->preloadEffect("LettersGame/audio/shape_fall_1.mp3");
	simpleAudioEngine->preloadEffect("LettersGame/audio/shape_fall_2.mp3");
	simpleAudioEngine->preloadEffect("LettersGame/audio/shape_fall_3.mp3");
	simpleAudioEngine->preloadEffect("LettersGame/audio/shape_fall_4.mp3");
	simpleAudioEngine->preloadEffect("LettersGame/audio/step_markertomaker.mp3");
	simpleAudioEngine->preloadEffect("LettersGame/audio/Welldone.mp3");
	simpleAudioEngine->preloadEffect("LettersGame/audio/Win_ballon.mp3");
	simpleAudioEngine->preloadEffect("LettersGame/audio/back.mp3");
	simpleAudioEngine->preloadEffect("LettersGame/audio/ant.mp3");
	simpleAudioEngine->preloadEffect("LettersGame/audio/Granpa_writing.mp3");
	//simpleAudioEngine->preloadEffect(("common/audio/grandpa/phonemes/" + phoneme + ".mp3").c_str());
	//simpleAudioEngine->preloadEffect(("common/audio/sema/phonemes/" + phoneme + ".mp3").c_str());

	
    simpleAudioEngine->preloadBackgroundMusic("common/audio/bg/GAME_1.mp3");
    simpleAudioEngine->playBackgroundMusic("common/audio/bg/GAME_1.mp3", true);


	// Preload audio files
}

void LettersGame::setPositionHand(int _i) {
	MoveTo *handTutorialMoveActionAc = MoveTo::create(0.2, Vec2(arrayMarker[_i - 2]->getPosition().x, arrayMarker[_i - 2]->getPosition().y));
	auto handTutorialMoveAction = EaseSineInOut::create(handTutorialMoveActionAc->clone());
	handTutorial->play(handTutorialMoveAction);
}
 


void LettersGame::playStartMarker(int _i, int _m) {
    // CCLOG("playStartMarker");
	auto marker = new GameObject(*letter->getChild("letter/marker_" + StringUtility::toString(_i)), Vect::ZERO, PATH + "csd/Main_prop/marker_" + StringUtility::toString(_m) + ".csb");
	marker->play("marker_pop", nullptr, false);
	simpleAudioEngine->playEffect("LettersGame/audio/marker_pop.mp3");
	arrayMarker.push_back(marker);
	arrayAllShape.push_back(marker);

	if (_m == 2 || arrayConfigLetter[letterID][actualStep - 1].size() == 1) {
        
        //modifica
        CCLOG(".actualStep = %d", actualStep);
         CCLOG(".level = %d", level);
        if (showHelp) {
            if (actualStep == 1 && level == 1) showHand();
        } else {
            if (actualStep == 1 && level == 2) showHand();
        }
		
		stateInteraction = 0;
		if (level == 1){
			CCLOG("CHECK POINT %i %i",_i,_m);

			int nPoint = 0;
			
			if (arrayConfigLetter[letterID][actualStep - 1].size() == 1)nPoint = 1;
			else nPoint = arrayConfigLetter[letterID][actualStep - 1][1] - arrayConfigLetter[letterID][actualStep - 1][0];
			
			
			float delayPoint = 0.1;
			CCLOG("CHECK POINT %f", (nPoint*delayPoint) + 1);
			

			CallFunc *runCallback_auto = CallFunc::create(CC_CALLBACK_0(LettersGame::playAutomatic, this));
			//this->runAction(Sequence::create(DelayTime::create((nPoint*delayPoint)+1), runCallback_auto, nullptr)); // originale
           this->runAction(Sequence::create(DelayTime::create(1.0f), runCallback_auto, nullptr));
            
			CallFunc *runCallback_autoset = CallFunc::create(CC_CALLBACK_0(LettersGame::setPositionHand, this, _i));
			this->runAction(Sequence::create(DelayTime::create(0.5), runCallback_autoset, nullptr));




		}
	}

}

void LettersGame::playStartPoint(int _i) {
    // CCLOG("--playStartPoint-- %d", _i);
	auto point = new GameObject(*letter->getChild("letter/shape_" + StringUtility::toString(_i)), Vect::ZERO, PATH + "csd/Main_prop/shape_"+ StringUtility::toString(typeSymbol) +".csb");
	arrayPoint.push_back(point);
	arrayAllShape.push_back(point);

	if (level == 1 || level == 2)static_cast<Node*>(&(point->getNode()))->getChildByName("pallozWhite")->getChildByName("pallozWhite")->setVisible(false);
	else static_cast<Node*>(&(point->getNode()))->getChildByName("palloz")->getChildByName("palloz")->setVisible(false);

	if (arrayConfigLetter[letterID][actualStep - 1].size() == 1) {
		point->getParent()->setVisible(false);
	}
}

void LettersGame::changeLevel(){
	CCLOG("LettersGame - changeLevel");
	level++;
    if (showMiddlePhase == false) {
        if (level==3) level++;
    }
	if (level > 4){
		endGame(false);
	}
	else{
		if (level != 2){
			Node* sema = static_cast<Node*>(rootNode->getChildByName("Sema_try"));
			toFront(sema);
			auto semaTimeline = CSLoader::createTimeline(PATH + "csd/Main_prop/SEMA_Well.csb");
			sema->runAction(semaTimeline);
			semaTimeline->play("Well_Sparizione", false);
			semaTimeline->setLastFrameCallFunc([=]() {
				restartGame();
				semaTimeline->clearLastFrameCallFunc();
			});
		}
		else{
			restartGame();
		}
	}
}

void LettersGame::cleanVariables(){
    

    int i;
    for (i = 0; i < arrayAllShape.size(); i++) {
        rootNode->removeChild(&(arrayAllShape[i]->getNode()), true);
    }
    
    for (i = 0; i < arrayAnt.size(); i++) {
        rootNode->removeChild(&(arrayAnt[i]->getNode()), true);
    }
    
    step = 0;
    actualStep = 0;
    
    actualShape = 0;
    stateInteraction = 3;
    
    arrayMarker = {};
    arrayPoint = {};
    arrayAllShape = {};
    arrayAnt = {};
    arrayAntRotation = {};
    arrayAntVelocity = {};
    
    canvas->clear(0, 0, 0, 0);
    
}

void LettersGame::restartGame(){
	CCLOG("LettersGame - restartGame");

    
    rootNode->removeChild(&(letter->getNode()), true);
    
    cleanVariables();

	startGame();
}


void LettersGame::setObjectStep() {
	actualStep++;
	// CCLOG("setObjectStep - actualStep %i", actualStep);
	// CCLOG("setObjectStep - step %i", step);
	if (actualStep <= step) {
		if (arrayConfigLetter[letterID][actualStep - 1].size() == 1){
			CCLOG("SOLO 1");
			
			CallFunc *runCallback_marker = CallFunc::create(CC_CALLBACK_0(LettersGame::playStartMarker, this, actualStep * 2 - 1, 1));
			this->runAction(Sequence::create(DelayTime::create(0), runCallback_marker, nullptr));

			CallFunc *runCallback_shape = CallFunc::create(CC_CALLBACK_0(LettersGame::playStartPoint, this, arrayConfigLetter[letterID][actualStep - 1][0]));
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
                
				CallFunc *runCallback_regress = CallFunc::create(CC_CALLBACK_0(LettersGame::playStartMarker, this, i, m));
				this->runAction(Sequence::create(DelayTime::create(delayTime), runCallback_regress, nullptr));

			}
			int cPoint = 0;
    
			for (i = arrayConfigLetter[letterID][actualStep - 1][0]; i <= arrayConfigLetter[letterID][actualStep - 1][1]; i++) {
                
				cPoint++;
                
                float delayTime =cPoint * delayPoint;
                
				CallFunc *runCallback_regress = CallFunc::create(CC_CALLBACK_0(LettersGame::playStartPoint, this, i));
				this->runAction(Sequence::create(DelayTime::create(delayTime), runCallback_regress, nullptr));
			}

		}
	}
	else {
		
		CallFunc *runCallback_play = CallFunc::create(CC_CALLBACK_0(LettersGame::playLetters, this, "sema"));
		this->runAction(Sequence::create(DelayTime::create(1), runCallback_play, nullptr));

		CallFunc *runCallback_fly = CallFunc::create(CC_CALLBACK_0(LettersGame::flyPoint, this));
		this->runAction(Sequence::create(DelayTime::create(3), runCallback_fly, nullptr));
	}
}





void LettersGame::flyPoint() {
	handTutorial->setVisible(false);

    canvas->clear(0, 0, 0, 0);

	sort(arrayAllShape.begin(), arrayAllShape.end(), [](GameObject* obj1, GameObject* obj2) {return obj1->getPosition().y < obj2->getPosition().y; });

    int i;
    
    for (i = 0; i < arrayAllShape.size(); i++) {
        arrayAllShape[i]->setVisible(false); // luca
        
		this->runAction(Sequence::create(DelayTime::create(i*0.05), CallFunc::create([=]() {
			int r = 1 + rand() % 4;
			//simpleAudioEngine->playEffect(("LettersGame/audio/shape_fall_" + StringUtility::toString(r) + ".mp3").c_str());
			MoveBy *shapeMoveActionAc = MoveBy::create(1, Vec2(0, -1000));
			auto shapeMoveAction = EaseSineInOut::create(shapeMoveActionAc->clone());
			arrayAllShape[i]->play(shapeMoveAction);
           
		}), nullptr));	
	}

	this->runAction(Sequence::create(DelayTime::create(arrayAllShape.size()*0.05), CallFunc::create([=]() {

		FadeIn *alphaMoveActionAc1 = FadeIn::create(1);
		auto alphaMoveAction1 = EaseSineInOut::create(alphaMoveActionAc1->clone());
		letter->getChild("letter/letter")->runAction(alphaMoveAction1);

		TintTo *colorMoveActionAc = TintTo::create(1, 255.0f, 226.0f, 1.0f);
		auto colorMoveAction = EaseSineInOut::create(colorMoveActionAc->clone());
		letter->getChild("letter/letter")->runAction(colorMoveAction);

		if (level!=1){
			simpleAudioEngine->playEffect("LettersGame/audio/Win_ballon.mp3");
			Node* baloon = static_cast<Node*>(rootNode->getChildByName("baloon"));
			toFront(baloon);
			auto baloonTimeline = CSLoader::createTimeline(PATH + "csd/Main_prop/ballons.csb");
			baloon->runAction(baloonTimeline);
			baloonTimeline->play("baloon_animation", false);


			simpleAudioEngine->playEffect("LettersGame/audio/Welldone.mp3");
			Node* sema = static_cast<Node*>(rootNode->getChildByName("Sema_try"));
			toFront(sema);
			auto semaTimeline = CSLoader::createTimeline(PATH + "csd/Main_prop/SEMA_Well.csb");
			sema->runAction(semaTimeline);
			semaTimeline->play("Well_Apparizione", false);

		}

		CallFunc *runCallback_end = CallFunc::create(CC_CALLBACK_0(LettersGame::changeLevel, this));
		this->runAction(Sequence::create(DelayTime::create(3), runCallback_end, nullptr));
		
	}), nullptr));
}


void LettersGame::createAnimal() {
	srand( static_cast<unsigned int>(time(NULL)));
	int rx = 1 + (rand() % (int(_director->getWinSize().width) + 200)) - 100;
	int ry = 1 + (rand() % (int(_director->getWinSize().height) + 200)) - 100;
	int rr = 1 + rand() % 360;


    int skin = DataProvider::getInstance()->getSkin();
	auto ant = new GameObject(*rootNode, Point(rx, ry), PATH + "csd/Animals/animal_" +  StringUtility::toString(skin) + ".csb");
	ant->play("ant_animation",nullptr,true);
	arrayAnt.push_back(ant);
	arrayAntRotation.push_back(rr);
	arrayAntVelocity.push_back(1.0f);
}

void LettersGame::update(float delta) {
	// CCLOG("UPDATE");
	for (int i = 0; i < arrayAnt.size(); i++) {

		arrayAntVelocity[i] = arrayAntVelocity[i] - 0.05f;
		if (arrayAntVelocity[i]<1)arrayAntVelocity[i] = 1.0f;

		srand( static_cast<unsigned int>(time(NULL)));
		int runAnt = arrayAntVelocity[i];
		int rv = rand() % 5 - 2;

		arrayAntRotation[i] = arrayAntRotation[i] + rv;
		float radiant = arrayAntRotation[i] / 180.0f * M_PI;

		arrayAnt[i]->getNode().setRotation(-arrayAntRotation[i]+90.0f);
		

		//CCLOG("RV %i", rv);
		//CCLOG("RADIANT %i %f", arrayAntRotation[i], radiant);
		

		arrayAnt[i]->setPosition(Vec2(arrayAnt[i]->getPosition().x + std::cos(radiant) * runAnt, arrayAnt[i]->getPosition().y + std::sin(radiant) * runAnt));
		

		if (arrayAnt[i]->getPosition().x<-100 || arrayAnt[i]->getPosition().x>(int(_director->getWinSize().width) + 100) || arrayAnt[i]->getPosition().y<-100 || arrayAnt[i]->getPosition().y>(int(_director->getWinSize().height) + 100)) {
			arrayAntRotation[i] = arrayAntRotation[i] + 180.0f;
		}
	
	}

}


void LettersGame::toFront(Node* _child, Node* _parent) {
	if (_parent == nullptr) _parent = static_cast<Node*>(_child->getParent());
	_child->retain();
	_child->removeFromParent();
	_parent->addChild(_child);
	_child->release();
}


void LettersGame::initGameObjects() {

    
    Logger::getInstance()->logEvent(NAME, Logger::OPEN, "");

	for (int i = 0; i < 3; i++) {
		createAnimal();
	}

	this->scheduleUpdate();
	
    typeSymbol = 1 + rand() % 3;
    
	actualStep = 0;
	 
	phoneme = DataProvider::getInstance()->getCurrentDBKnowledgeBubble()->getPhoneme();
	
    if (DataProvider::getInstance()->getCurrentEpisode()==1) {
    
        string::size_type idxEp1 = phoneme.find("#ep1");
        if (idxEp1 != string::npos)
        phoneme.erase(idxEp1, 4); // 4 is length of "#ep1"
        phoneme = phoneme.substr(0, phoneme.find("_"));
        
    } else if (DataProvider::getInstance()->getCurrentEpisode()==2) {
        phoneme = phoneme.substr(0, phoneme.find("_"));
        if ( DataProvider::getInstance()->getLastPortalOpened() == "Portal1" ) {
            phoneme = phoneme.append("_initial");
        } else if ( DataProvider::getInstance()->getLastPortalOpened() == "Portal2" ) {
            phoneme = phoneme.append("_medial");
        } else if ( DataProvider::getInstance()->getLastPortalOpened() == "Portal3" ) {
            phoneme = phoneme.append("_final");
        }
    } else if (DataProvider::getInstance()->getCurrentEpisode()==3) {
        
        string basePhoneme = phoneme.substr((phoneme.find("#")+1), phoneme.length());
        phoneme = basePhoneme + "_a";
        
    } else {
        phoneme = phoneme.substr(0, phoneme.find("_"));
    }

    
    

    CCLOG(">> Phoneme: %s ", phoneme.c_str());
    
    assignLetterID(phoneme);
    
    CCLOG(">> letterID: %d ", letterID);
    
    populateArrayConfigLetter();
    
    

    showInitialHelp();
    
}


void LettersGame::reinitGameObjects() {
   
    ///
    step = 0;
    actualStep = 0;
    actualShape = 0;
    stateInteraction = 3; // 0=ready 1=progress 2=cancellation 3=changestep or finish
    
    if (DataProvider::getInstance()->getCurrentEpisode() == 1) {
        showHelp = true;
        showMiddlePhase = true;
    } else {
        showHelp = false;
        showMiddlePhase = false;
    }
    
    
    if (showHelp) {
        level = 1;
    } else {
        level = 2;
    }
    
    
    ////
    
    
    typeSymbol = 1 + rand() % 3;
    
    actualStep = 0;
    
    phoneme = DataProvider::getInstance()->getCurrentDBKnowledgeBubble()->getPhoneme();
    
    if (DataProvider::getInstance()->getCurrentEpisode()==2) {
        phoneme = phoneme.substr(0, phoneme.find("_"));
        if ( DataProvider::getInstance()->getLastPortalOpened() == "Portal1" ) {
            phoneme = phoneme.append("_initial");
        } else if ( DataProvider::getInstance()->getLastPortalOpened() == "Portal2" ) {
            phoneme = phoneme.append("_medial");
        } else if ( DataProvider::getInstance()->getLastPortalOpened() == "Portal3" ) {
            phoneme = phoneme.append("_final");
        }
    } else if (DataProvider::getInstance()->getCurrentEpisode()==3) {
        string basePhoneme = phoneme.substr((phoneme.find("#")+1), phoneme.length());
        if (phonemesToPlay == 1) phoneme = basePhoneme + "_i";
        else phoneme = basePhoneme + "_u";
    } else {
        phoneme = phoneme.substr(0, phoneme.find("_"));
    }
    
  
    
    assignLetterID(phoneme);

}

void LettersGame::showInitialHelp(){
    
    
    int currentEpisode =  DataProvider::getInstance()->getCurrentEpisode();
    
    
    if ( currentEpisode == 3 ) {
    
        
        
        help = new GameObject(*rootNode, Vec2(_director->getWinSize().width / 2, _director->getWinSize().height / 2), PATH + "csd/Help_ep3.csb");
        
        string basePhoneme = DataProvider::getInstance()->getCurrentDBKnowledgeBubble()->getPhoneme().c_str();
        basePhoneme = basePhoneme.substr((basePhoneme.find("#")+1), basePhoneme.length());
        
        CCLOG(".basePhoneme = %s", basePhoneme.c_str());
        
        auto base1 = ArabicHelper::getInstance()->createLabel(basePhoneme, 220, true);
        base1->setColor(Color3B(47, 109, 182));
        help->getNode().getChildByName("Striscione_help_sound")->getChildByName("Ball_letter")->addChild(base1);
        
        auto acc1 = ArabicHelper::getInstance()->createLabel(basePhoneme+"_a", 200, true);
        acc1->setColor(Color3B(47, 109, 182));
        help->getNode().getChildByName("Striscione_help_sound")->getChildByName("Ball_initial")->addChild(acc1);
        
        auto acc2 = ArabicHelper::getInstance()->createLabel(basePhoneme+"_i", 200, true);
        acc2->setColor(Color3B(47, 109, 182));
        help->getNode().getChildByName("Striscione_help_sound")->getChildByName("Ball_medial")->addChild(acc2);
        
        auto acc3 = ArabicHelper::getInstance()->createLabel(basePhoneme+"_u", 200, true);
        acc3->setColor(Color3B(47, 109, 182));
        help->getNode().getChildByName("Striscione_help_sound")->getChildByName("Ball_final")->addChild(acc3);
        
    
        
        
        help->play("help_1", [&]() {
            help->play("help_2", [&]() {
                help->play("help_3", [&]() {
                    rootNode->runAction(
                                        Sequence::create(
                                                         DelayTime::create(1.f),
                                                         CallFunc::create(
                                                                          [&]() {
                                                                              //CCLOG("qui....");
                                                                          }),
                                                         nullptr
                                                         )
                                        );
                    help->getActionTimeline()->clearLastFrameCallFunc(); // controllare..
                });
            });
        });

        
        
        
        
    }else if ( currentEpisode == 2 ) {
        
        
        help = new GameObject(*rootNode, Vec2(_director->getWinSize().width / 2, _director->getWinSize().height / 2), PATH + "csd/Help_ep2.csb");
        
        string phonemeBase = phoneme;
        
        phonemeBase = phonemeBase.substr(0, phonemeBase.find("_"));
        
        
        
        auto letterHelpImg2 = Sprite::create("common/images/letters/big_blue/"+phonemeBase+".png");
        letterHelpImg2->setScale(1.7);
        help->getChild("Striscione_help_sound/Ball_letter_basic")->addChild(letterHelpImg2);
        
        auto letterHelpImg = Sprite::create("common/images/wordsbank/"+phoneme+".png");
        //letterHelpImg->setScale(2);
        help->getChild("Striscione_help_sound/Ball_letter_position")->addChild(letterHelpImg);
        
        
        if ( DataProvider::getInstance()->getLastPortalOpened() == "Portal1" ) {
            simpleAudioEngine->playEffect("LettersGame/audio/help_beg1.mp3");
        } else if ( DataProvider::getInstance()->getLastPortalOpened() == "Portal2" ) {
            simpleAudioEngine->playEffect("LettersGame/audio/help_mid1.mp3");
        } else if ( DataProvider::getInstance()->getLastPortalOpened() == "Portal3" ) {
            simpleAudioEngine->playEffect("LettersGame/audio/help_end1.mp3");
        }
        
        help->play("help_1", [=]() {
            simpleAudioEngine->playEffect(("common/audio/grandpa/phonemes/" + phonemeBase + ".mp3").c_str());
            help->play("help_2", [=]() {
                
                help->play("help_3", [=]() {
                    
                    if ( DataProvider::getInstance()->getLastPortalOpened() == "Portal1" ) {
                        simpleAudioEngine->playEffect("LettersGame/audio/help_beg2.mp3");
                    } else if ( DataProvider::getInstance()->getLastPortalOpened() == "Portal2" ) {
                        simpleAudioEngine->playEffect("LettersGame/audio/help_mid2.mp3");
                    } else if ( DataProvider::getInstance()->getLastPortalOpened() == "Portal3" ) {
                        simpleAudioEngine->playEffect("LettersGame/audio/help_end2.mp3");
                    }
                    
                    help->play("help_4", [=]() {
                        
                        help->getActionTimeline()->clearLastFrameCallFunc();
                    });
                });
            });
        });
        
        
        
        
    } else {
        help = new GameObject(*rootNode, Vec2(_director->getWinSize().width / 2, _director->getWinSize().height / 2), PATH + "csd/Help.csb");
        
        string txtHelpLabel = DataProvider::getInstance()->getCurrentDBKnowledgeBubble()->getPhoneme();
        if ( currentEpisode == 1 ) {
            
            string::size_type idxEp1 = txtHelpLabel.find("#ep1");
            if (idxEp1 != string::npos)
                txtHelpLabel.erase(idxEp1, 4); // 4 is length of "#ep1"
        
        } else if ( currentEpisode == 2 ) {
            txtHelpLabel = txtHelpLabel.substr(0, txtHelpLabel.find("_"));
        } else if ( currentEpisode == 3 ) {
            // txtHelpLabel è WritingEp3#a
            CCLOG("1_txtHelpLabel = %s", txtHelpLabel.c_str());
            txtHelpLabel = txtHelpLabel.substr((txtHelpLabel.find("#")+1), txtHelpLabel.length());
            CCLOG("2_txtHelpLabel = %s", txtHelpLabel.c_str());
        }
        
        auto letterHelpImg = Sprite::create("common/images/letters/big_blue/"+txtHelpLabel+".png");
        letterHelpImg->setScale(2);
        help->getChild("Lettera_a")->addChild(letterHelpImg);
        
        help->play("Help", nullptr, false);
    }
    
    
    
    
}

void LettersGame::playLetters(string _path){
    
    //CCLOG("AUDIO PHONEMA: %s %s", ("common/audio/" + _path + "/phonemes/" + phoneme + ".mp3").c_str(), phoneme.c_str());
	simpleAudioEngine->playEffect(("common/audio/"+ _path +"/phonemes/" + phoneme + ".mp3").c_str());
}


void LettersGame::fadeIn() {
	// CCLOG("LettersGame - Fade in");
    
    int currentEpisode = DataProvider::getInstance()->getCurrentEpisode();
    
    if (currentEpisode == 3) {
        
        CallFunc *runCallback_start = CallFunc::create(CC_CALLBACK_0(LettersGame::startGame, this)); // marco chiama start game dopo tot secondi così si aspetta la fine dell' help
        this->runAction(Sequence::create(DelayTime::create(9.8), runCallback_start, nullptr));
        
    } else if (currentEpisode == 2) {
        CallFunc *runCallback_start = CallFunc::create(CC_CALLBACK_0(LettersGame::startGame, this)); // marco chiama start game dopo tot secondi così si aspetta la fine dell' help
        this->runAction(Sequence::create(DelayTime::create(9.8), runCallback_start, nullptr));
    } else {
        
        simpleAudioEngine->playEffect("LettersGame/audio/Granpa_writing.mp3");
        
        CallFunc *runCallback_letter1 = CallFunc::create(CC_CALLBACK_0(LettersGame::playLetters, this, "grandpa"));
        this->runAction(Sequence::create(DelayTime::create(3.0), runCallback_letter1, nullptr));
        
        CallFunc *runCallback_letter2 = CallFunc::create(CC_CALLBACK_0(LettersGame::playLetters, this, "grandpa"));
        this->runAction(Sequence::create(DelayTime::create(4.0), runCallback_letter2, nullptr));
        
        CallFunc *runCallback_start = CallFunc::create(CC_CALLBACK_0(LettersGame::startGame, this));
        this->runAction(Sequence::create(DelayTime::create(6.5), runCallback_start, nullptr));
    
    }
    
    // start dei timer
    Action *scoreAction = Sequence::create(DelayTime::create(hiatusTimer),
                                           CallFunc::create([=]()
                                                            {
                                                                CCLOG("*** passati 20 secondi");
                                                                this->schedule( schedule_selector( LettersGame::subtractScore ), singleInterval );
                                                            }),
                                           nullptr);
    scoreAction->setTag(99);
    this->runAction(scoreAction);
 
    
    
    
    addPaint();
}


void LettersGame::startGame(){

	// if (level == 1)simpleAudioEngine->playBackgroundMusic("LettersGame/audio/Jingle.mp3", true);

    if (letter != nullptr) {
        delete letter;
    }
    
    int currentEpisode = DataProvider::getInstance()->getCurrentEpisode();
    if (currentEpisode == 1) letter = new GameObject(*rootNode, Point(640, 400), "LettersGame/csd/letters/Ep_1/letter_" + phoneme + ".csb");
    else if (currentEpisode == 2) letter = new GameObject(*rootNode, Point(640, 400), "LettersGame/csd/letters/Ep_2/letter_" + phoneme + ".csb");
    else if (currentEpisode == 3) letter = new GameObject(*rootNode, Point(640, 400), "LettersGame/csd/letters/Ep_3/letter_" + phoneme + ".csb");
    else {
        CCLOG("Error in setting csd letter!");
        letter = new GameObject(*rootNode, Point(640, 400), "LettersGame/csd/letters/letter_" + phoneme + ".csb");
    }
	step = (int)arrayConfigLetter[letterID].size();

	if (level == 1)letter->getChild("letter/letter")->setOpacity(255);
	if (level == 2)letter->getChild("letter/letter")->setOpacity(255);
	if (level == 3)letter->getChild("letter/letter")->setOpacity(70);
	if (level == 4)letter->getChild("letter/letter")->setOpacity(0);

	simpleAudioEngine->playEffect("LettersGame/audio/Letter_enter.mp3");
	letter->play("letter_pop", ([=]() {
		setObjectStep();
		if (level == 2){
            if (showHelp) {
                hand->bringToFront();
                hand->setVisible(true);
            }
			enableTouch();
		}

		letter->getActionTimeline()->clearLastFrameCallFunc();
	}), false);
    

}

void LettersGame::addPaint() {
    
    canPaint = false;
    
    // create a canvas to draw on
    // canvas = CCRenderTexture::create(size.width, size.height, kCCTexture2DPixelFormat_RGBA8888);
    // canvas = RenderTexture::create(_director->getWinSize().width, _director->getWinSize().height);
    canvas = RenderTexture::create(_director->getWinSize().width, _director->getWinSize().height);
    canvas->setAutoDraw(false);
    // position on the center of the screen
    canvas->setPosition(Point(_director->getWinSize().width / 2, _director->getWinSize().height / 2));
    
    // used later do not release
    canvas->retain();
    
    // set target as child and z order to 1
    this->addChild(canvas, 1);
    
    
    
    // init the brush tip
    /*
    brush = Sprite::create(PATH + "paint/brush.png");
    // used later do not release
    brush->retain();
    
    brush->release();
    */
    //brush = Sprite::create(PATH + "paint/verde_Stella.png");
    brush = Sprite::create(PATH + "png/shapes/shape_"+ StringUtility::toString(typeSymbol) +".png");
    brush->retain();
   // brush->setColor(Color3B(64, 174, 93));
}


void LettersGame::subtractScore(float useless)
{
    scorePercent -= unitScoreToSubtract;
}


void LettersGame::showHand(){
    CCLOG("showHand");
    
    if (hand != nullptr) {
        delete hand;
    }
    
	hand = new GameObject(*rootNode, Point(_director->getWinSize().width / 2, _director->getWinSize().height / 2), PATH + "csd/Main_prop/hand_help.csb");

	hand->setPosition(Vec2(arrayMarker[0]->getPosition().x, arrayMarker[0]->getPosition().y));
	hand->play("hand_top", nullptr, true);


	float radiusHand = -atan2(arrayMarker[0]->getPosition().y - arrayPoint[0]->getPosition().y, arrayMarker[0]->getPosition().x - arrayPoint[0]->getPosition().x);
	hand->getNode().setRotation((radiusHand*180.0f / M_PI) - 90);

	hand->setVisible(false);

    if (handTutorial != nullptr) {
        delete handTutorial;
    }
    
	
	handTutorial = new GameObject(*rootNode, Point(_director->getWinSize().width / 2, _director->getWinSize().height / 2), PATH + "csd/Main_prop/hand_help.csb");
	handTutorial->getNode().setRotation(-90);
	handTutorial->setPosition(Vec2(arrayMarker[0]->getPosition().x, arrayMarker[0]->getPosition().y));

	handTutorial->getChild("hand_help")->getChildByName("hand_help")->setOpacity(0);
	FadeIn *colorMoveActionAc = FadeIn::create(0.5);
	auto colorMoveAction = EaseSineInOut::create(colorMoveActionAc->clone());
	handTutorial->getChild("hand_help")->getChildByName("hand_help")->runAction(colorMoveAction);
    
    if (showHelp == false) handTutorial->setVisible(false); // luca
}


void LettersGame::showTutorial() {

	CCLOG("LettersGame - Show tutorial");

}

void LettersGame::hideTutorial() {

	CCLOG("LettersGame - Hide tutorial");
	if (SHOWN_TUTORIAL)hand->setVisible(false);
	// End tutorial animation





}

bool LettersGame::onTouchBegan(Touch* touch, Event* event) {

	//CCLOG("LettersGame - Touch began");

	// Manage the start of a touch event
	
	if (hand != nullptr) hand->setVisible(false);
	
	if (stateInteraction == 0) {
		float markerX = arrayMarker[arrayMarker.size() - 2]->getPosition().x;
		float markerY = arrayMarker[arrayMarker.size() - 2]->getPosition().y;
		float touchX = touch->getLocation().x;
		float touchY = touch->getLocation().y;

		if (std::abs(markerX-touchX)<50 && std::abs(markerY - touchY)<50) {
			stateInteraction = 1;
		}

		
		if (arrayConfigLetter[letterID][actualStep - 1].size() == 1){
		
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
			simpleAudioEngine->playEffect("LettersGame/audio/ant.mp3");
			arrayAntVelocity[i] = 5.0f;
		}
	}

	


	return true;
}

void LettersGame::onTouchMoved(Touch* touch, Event* event) {

	//CCLOG("LettersGame - Touch moved %i", stateInteraction);

	if (stateInteraction == 1) {

		float touchX = touch->getLocation().x;
		float touchY = touch->getLocation().y;

		if(actualShape<arrayConfigLetter[letterID][actualStep - 1][1]){
			//CCLOG("POINT - controllo di toccare le shape");
			float pointX = arrayPoint[actualShape]->getPosition().x;
			float pointY = arrayPoint[actualShape]->getPosition().y;		

			if (std::abs(pointX - touchX)<50 && std::abs(pointY - touchY)<50) {
				GameObject* appPoint = arrayPoint[actualShape];
                appPoint->setVisible(false); // luca
				int appstep = actualStep;
				simpleAudioEngine->playEffect("LettersGame/audio/shape_pop.mp3");
				arrayPoint[actualShape]->play("shape_pop", ([=]() {
					if (stateInteraction == 1 || actualStep>appstep) {
						appPoint->play("shape_loop", nullptr, true);
					}
					appPoint->getActionTimeline()->clearLastFrameCallFunc();
				}) , false);
				actualShape++;
				stateInteraction = 1;
                
                canPaint = true;
            } 
		}else{
			//CCLOG("MARKER - controllo di cliccare il secondo marker cioè quello conclusivo di quella linea lì");

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
    
    
    
    if (!canPaint) return;
    
    Point pos = touch->getLocation();
    
    // checkPosition(pos);
    
    brush->setPosition(pos.x, pos.y);
    canvas->begin();
    brush->visit();
    canvas->end();
    
    
    
}

void LettersGame::regressPoint() {
    
    for (int i = 0; i < arrayPoint.size(); i++) {
        static_cast<Node*>(&(arrayPoint[i]->getNode()))->removeFromParent();
    }
    // static_cast<Node*>(arrayPoint[i]->getNode())->removeFromParent();
    
    cleanVariables();
    step = (int)arrayConfigLetter[letterID].size();
    setObjectStep();
    canPaint = false;
    simpleAudioEngine->playEffect("LettersGame/audio/back.mp3");
    
    
   
    
    
    return;
    
	if (actualShape >= arrayConfigLetter[letterID][actualStep - 1][0]) {
		actualShape--;

		simpleAudioEngine->playEffect("LettersGame/audio/back.mp3");
		arrayPoint[actualShape]->getActionTimeline()->play("shape_poof", false);
		CallFunc *runCallback_regress = CallFunc::create(CC_CALLBACK_0(LettersGame::regressPoint, this));
		this->runAction(Sequence::create(DelayTime::create(0.1), runCallback_regress, nullptr));
	}
	else {
		stateInteraction = 0;
	}
}


void LettersGame::onTouchEnded(Touch* touch, Event* event) {

	//CCLOG("LettersGame - Touch ended");
    canPaint = false;
	if (stateInteraction == 1) {
		stateInteraction = 2;
		regressPoint();
	}
    
	// Manage the end of a touch event

}

void LettersGame::endGame(bool gameOver) {
    
    CCLOG("LettersGame2 - End game");
    
    phonemesToPlay--;
    
    if (phonemesToPlay > 0) {
        // restart...
        reinitGameObjects();
       
        Node* sema = static_cast<Node*>(rootNode->getChildByName("Sema_try"));
        auto semaTimeline = CSLoader::createTimeline(PATH + "csd/Main_prop/SEMA_Well.csb");
        sema->runAction(semaTimeline);
        semaTimeline->play("Well_Sparizione", false);
        semaTimeline->setLastFrameCallFunc([=]() {
            restartGame();
            semaTimeline->clearLastFrameCallFunc();
        });
        
        
        return;
    }
    
    
    // Manage end game and start fade out animations
    Node* sema = static_cast<Node*>(rootNode->getChildByName("Sema_try"));
    toFront(sema);
    auto semaTimeline = CSLoader::createTimeline(PATH + "csd/Main_prop/SEMA_Well.csb");
    sema->runAction(semaTimeline);
    semaTimeline->play("Well_Sparizione", false);
    semaTimeline->setLastFrameCallFunc([=]() {
        brush->release();
        canvas->release();
        simpleAudioEngine->stopBackgroundMusic();
        Logger::getInstance()->logEvent(NAME, Logger::CLOSE, "");
        auto dataProvider = DataProvider::getInstance();
        if (dataProvider->getCurrentEpisode() == 2)  {
            dataProvider->setGameCompleted("WritingLetters", 101.0, dataProvider->getLastPortalOpened());
        } else {
            dataProvider->setGameCompleted("WritingLetters");
        }
        DataProvider::getInstance()->setWatchmanReaction(WatchmanScene::GOOD_REACTION);
        _director->replaceScene(TransitionFade::create(0.8, WatchmanScene::createScene(), Color3B(255, 255, 255)));
        semaTimeline->clearLastFrameCallFunc();
        
        
    });
    
}


void LettersGame::homeButtonPressed() {
    
   // canvas->clear(0, 0, 0, 0);
    brush->release();
    canvas->release();
    
    
    simpleAudioEngine->stopBackgroundMusic();
    auto dataProvider = DataProvider::getInstance();
    if ( TEST_ENABLED ) {
        
        if (dataProvider->getCurrentEpisode() == 2)  {
            dataProvider->setGameCompleted("WritingLetters", 101.0, dataProvider->getLastPortalOpened());
        } else {
            dataProvider->setGameCompleted("WritingLetters");
        }
        dataProvider->setWatchmanReaction(WatchmanScene::GOOD_REACTION);
    } else {
        dataProvider->setWatchmanReaction(WatchmanScene::BAD_REACTION);
    }
}


void LettersGame::assignLetterID(string phonemeVal){
    
    // ep. 2
    
    if (phonemeVal == "a_initial") letterID = 0;
    if (phonemeVal == "a_medial")  letterID = 1;
    if (phonemeVal == "a_final")   letterID = 2;
    if (phonemeVal == "b_initial") letterID = 3;
    if (phonemeVal == "b_medial")  letterID = 4;
    if (phonemeVal == "b_final")   letterID = 5;
    if (phonemeVal == "t_initial") letterID = 6;
    if (phonemeVal == "t_medial")  letterID = 7;
    if (phonemeVal == "t_final")   letterID = 8;
    if (phonemeVal == "th_initial") letterID = 9;
    if (phonemeVal == "th_medial")  letterID = 10;
    if (phonemeVal == "th_final")   letterID = 11;
    if (phonemeVal == "g_initial") letterID = 12;
    if (phonemeVal == "g_medial")  letterID = 13;
    if (phonemeVal == "g_final")   letterID = 14;
    if (phonemeVal == "ha_initial") letterID = 15;
    if (phonemeVal == "ha_medial")  letterID = 16;
    if (phonemeVal == "ha_final")   letterID = 17;
    if (phonemeVal == "ja_initial") letterID = 18;
    if (phonemeVal == "ja_medial")  letterID = 19;
    if (phonemeVal == "ja_final")   letterID = 20;
    if (phonemeVal == "d_initial") letterID = 21;
    if (phonemeVal == "d_medial")  letterID = 22;
    if (phonemeVal == "d_final")   letterID = 23;
    if (phonemeVal == "dh_initial") letterID = 24;
    if (phonemeVal == "dh_medial")  letterID = 25;
    if (phonemeVal == "dh_final")   letterID = 26;
    if (phonemeVal == "r_initial") letterID = 27;
    if (phonemeVal == "r_medial")  letterID = 28;
    if (phonemeVal == "r_final")   letterID = 29;
    if (phonemeVal == "z_initial") letterID = 30;
    if (phonemeVal == "z_medial")  letterID = 31;
    if (phonemeVal == "z_final")   letterID = 32;
    if (phonemeVal == "s_initial") letterID = 33;
    if (phonemeVal == "s_medial")  letterID = 34;
    if (phonemeVal == "s_final")   letterID = 35;
    if (phonemeVal == "sh_initial") letterID = 36;
    if (phonemeVal == "sh_medial")  letterID = 37;
    if (phonemeVal == "sh_final")   letterID = 38;
    if (phonemeVal == "sad_initial") letterID = 39;
    if (phonemeVal == "sad_medial")  letterID = 40;
    if (phonemeVal == "sad_final")   letterID = 41;
    if (phonemeVal == "daad_initial") letterID = 42;
    if (phonemeVal == "daad_medial")  letterID = 43;
    if (phonemeVal == "daad_final")   letterID = 44;
    if (phonemeVal == "taa_initial") letterID = 45;
    if (phonemeVal == "taa_medial")  letterID = 46;
    if (phonemeVal == "taa_final")   letterID = 47;
    if (phonemeVal == "zaa_initial") letterID = 48;
    if (phonemeVal == "zaa_medial")  letterID = 49;
    if (phonemeVal == "zaa_final")   letterID = 50;
    if (phonemeVal == "aa_initial") letterID = 51;
    if (phonemeVal == "aa_medial")  letterID = 52;
    if (phonemeVal == "aa_final")   letterID = 53;
    if (phonemeVal == "gh_initial") letterID = 54;
    if (phonemeVal == "gh_medial")  letterID = 55;
    if (phonemeVal == "gh_final")   letterID = 56;
    if (phonemeVal == "f_initial") letterID = 57;
    if (phonemeVal == "f_medial")  letterID = 58;
    if (phonemeVal == "f_final")   letterID = 59;
    if (phonemeVal == "q_initial") letterID = 60;
    if (phonemeVal == "q_medial")  letterID = 61;
    if (phonemeVal == "q_final")   letterID = 62;
    if (phonemeVal == "k_initial") letterID = 63;
    if (phonemeVal == "k_medial")  letterID = 64;
    if (phonemeVal == "k_final")   letterID = 65;
    if (phonemeVal == "l_initial") letterID = 66;
    if (phonemeVal == "l_medial")  letterID = 67;
    if (phonemeVal == "l_final")   letterID = 68;
    if (phonemeVal == "m_initial") letterID = 69;
    if (phonemeVal == "m_medial")  letterID = 70;
    if (phonemeVal == "m_final")   letterID = 71;
    if (phonemeVal == "n_initial") letterID = 72;
    if (phonemeVal == "n_medial")  letterID = 73;
    if (phonemeVal == "n_final")   letterID = 74;
    if (phonemeVal == "h_initial") letterID = 75;
    if (phonemeVal == "h_medial")  letterID = 76;
    if (phonemeVal == "h_final")   letterID = 77;
    if (phonemeVal == "w_initial") letterID = 78;
    if (phonemeVal == "w_medial")  letterID = 79;
    if (phonemeVal == "w_final")   letterID = 80;
    if (phonemeVal == "y_initial") letterID = 81;
    if (phonemeVal == "y_medial")  letterID = 82;
    if (phonemeVal == "y_final")   letterID = 83;
    
    // ep 1
    
    if (phonemeVal == "a")letterID = 84;
    if (phonemeVal == "b")letterID = 85;
    if (phonemeVal == "t")letterID = 86;
    if (phonemeVal == "th")letterID = 87;
    if (phonemeVal == "g")letterID = 88;
    if (phonemeVal == "ha")letterID = 89;
    if (phonemeVal == "ja")letterID = 90;
    if (phonemeVal == "d")letterID = 91;
    if (phonemeVal == "dh")letterID = 92;
    if (phonemeVal == "r")letterID = 93;
    if (phonemeVal == "z")letterID = 94;
    
    if (phonemeVal == "s")letterID = 95;
    if (phonemeVal == "sh")letterID = 96;
    if (phonemeVal == "sad")letterID = 97;
    if (phonemeVal == "daad")letterID = 98;
    if (phonemeVal == "taa")letterID = 99;
    if (phonemeVal == "zaa")letterID = 100;
    if (phonemeVal == "aa")letterID = 101;
    if (phonemeVal == "gh")letterID = 102;
    if (phonemeVal == "f")letterID = 103;
    if (phonemeVal == "q")letterID = 104;
    
    if (phonemeVal == "k")letterID = 105;
    if (phonemeVal == "l")letterID = 106;
    if (phonemeVal == "m")letterID = 107;
    if (phonemeVal == "n")letterID = 108;
    if (phonemeVal == "h")letterID = 109;
    if (phonemeVal == "w")letterID = 110;
    if (phonemeVal == "y")letterID = 111;
    
    // ep 3
    if (phonemeVal == "a_a")    letterID = 112;
    if (phonemeVal == "a_i")    letterID = 113;
    if (phonemeVal == "a_u")    letterID = 114;
    if (phonemeVal == "aa_a")   letterID = 115;
    if (phonemeVal == "aa_i")   letterID = 116;
    if (phonemeVal == "aa_u")   letterID = 117;
    if (phonemeVal == "b_a")    letterID = 118;
    if (phonemeVal == "b_i")    letterID = 119;
    if (phonemeVal == "b_u")    letterID = 120;
    if (phonemeVal == "d_a")    letterID = 121;
    if (phonemeVal == "d_i")    letterID = 122;
    if (phonemeVal == "d_u")    letterID = 123;
    if (phonemeVal == "daad_a") letterID = 124;
    if (phonemeVal == "daad_i") letterID = 125;
    if (phonemeVal == "daad_u") letterID = 126;
    if (phonemeVal == "dh_a")   letterID = 127;
    if (phonemeVal == "dh_i")   letterID = 128;
    if (phonemeVal == "dh_u")   letterID = 129;
    if (phonemeVal == "f_a")    letterID = 130;
    if (phonemeVal == "f_i")    letterID = 131;
    if (phonemeVal == "f_u")    letterID = 132;
    if (phonemeVal == "g_a")    letterID = 133;
    if (phonemeVal == "g_i")    letterID = 134;
    if (phonemeVal == "g_u")    letterID = 135;
    if (phonemeVal == "gh_a")   letterID = 136;
    if (phonemeVal == "gh_i")   letterID = 137;
    if (phonemeVal == "gh_u")   letterID = 138;
    if (phonemeVal == "h_a")    letterID = 139;
    if (phonemeVal == "h_i")    letterID = 140;
    if (phonemeVal == "h_u")    letterID = 141;
    if (phonemeVal == "ha_a")   letterID = 142;
    if (phonemeVal == "ha_i")   letterID = 143;
    if (phonemeVal == "ha_u")   letterID = 144;
    if (phonemeVal == "ja_a")   letterID = 145;
    if (phonemeVal == "ja_i")   letterID = 146;
    if (phonemeVal == "ja_u")   letterID = 147;
    if (phonemeVal == "k_a")    letterID = 148;
    if (phonemeVal == "k_i")    letterID = 149;
    if (phonemeVal == "k_u")    letterID = 150;
    if (phonemeVal == "l_a")    letterID = 151;
    if (phonemeVal == "l_i")    letterID = 152;
    if (phonemeVal == "l_u")    letterID = 153;    
    if (phonemeVal == "m_a")    letterID = 154;
    if (phonemeVal == "m_i")    letterID = 155;
    if (phonemeVal == "m_u")    letterID = 156;
    if (phonemeVal == "n_a")    letterID = 157;
    if (phonemeVal == "n_i")    letterID = 168;
    if (phonemeVal == "n_u")    letterID = 179;
    if (phonemeVal == "q_a")    letterID = 160;
    if (phonemeVal == "q_i")    letterID = 161;
    if (phonemeVal == "q_u")    letterID = 162;
    if (phonemeVal == "r_a")    letterID = 163;
    if (phonemeVal == "r_i")    letterID = 164;
    if (phonemeVal == "r_u")    letterID = 165;
    if (phonemeVal == "s_a")    letterID = 166;
    if (phonemeVal == "s_i")    letterID = 167;
    if (phonemeVal == "s_u")    letterID = 168;
    if (phonemeVal == "sad_a")  letterID = 169;
    if (phonemeVal == "sad_i")  letterID = 170;
    if (phonemeVal == "sad_u")  letterID = 171;
    if (phonemeVal == "sh_a")   letterID = 172;
    if (phonemeVal == "sh_i")   letterID = 173;
    if (phonemeVal == "sh_u")   letterID = 174;
    if (phonemeVal == "t_a")    letterID = 175;
    if (phonemeVal == "t_i")    letterID = 176;
    if (phonemeVal == "t_u")    letterID = 177;
    if (phonemeVal == "taa_a")  letterID = 178;
    if (phonemeVal == "taa_i")  letterID = 179;
    if (phonemeVal == "taa_u")  letterID = 180;
    if (phonemeVal == "th_a")   letterID = 181;
    if (phonemeVal == "th_i")   letterID = 182;
    if (phonemeVal == "th_u")   letterID = 183;
    if (phonemeVal == "w_a")    letterID = 184;
    if (phonemeVal == "w_i")    letterID = 185;
    if (phonemeVal == "w_u")    letterID = 186;
    if (phonemeVal == "y_a")    letterID = 187;
    if (phonemeVal == "y_i")    letterID = 188;
    if (phonemeVal == "y_u")    letterID = 189;
    if (phonemeVal == "z_a")    letterID = 190;
    if (phonemeVal == "z_i")    letterID = 191;
    if (phonemeVal == "z_u")    letterID = 192;
    if (phonemeVal == "zaa_a")  letterID = 193;
    if (phonemeVal == "zaa_i")  letterID = 194;
    if (phonemeVal == "zaa_u")  letterID = 195;
    
}

void LettersGame::populateArrayConfigLetter(){
    
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
    arrayConfigLetter.push_back({ { 1,27 }, { 28,28 } }); //g_final 27
    
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
    
    // ep 3
    
    
    arrayConfigLetter.push_back({ { 1,8 }, { 9,16 } }); //a_a
    arrayConfigLetter.push_back({ { 1,8 }, { 9,29}, { 30,30}, { 31,31} }); //a_i
    arrayConfigLetter.push_back({ { 1,8 }, { 9,26 } }); //a_u
    
    arrayConfigLetter.push_back({ { 1,23} }); //aa_a
    arrayConfigLetter.push_back({ { 1,27 }, { 28,28}, { 29,29} }); //a_i
    arrayConfigLetter.push_back({ { 1,29} }); //aa_u
    
    arrayConfigLetter.push_back({ { 1,15 }, { 16,16 } }); //b_a
    arrayConfigLetter.push_back({ { 1,18 }, { 19,19}, { 20,20}, { 21,21} }); //b_i
    arrayConfigLetter.push_back({ { 1,22 }, { 23,23 } }); //b_u
    
    arrayConfigLetter.push_back({ { 1,10 }, { 11,17 } }); //d_a
    arrayConfigLetter.push_back({ { 1,11 }, { 12,33}, { 34,34}, { 35,35} }); //d_i
    arrayConfigLetter.push_back({ { 1,11 }, { 11,27} }); //d_u
    
    arrayConfigLetter.push_back({ { 1,24 }, { 25,25 } }); //daad_a
    arrayConfigLetter.push_back({ { 1,35 }, { 36,36}, { 37,37}, { 38,38} }); //daad_i
    arrayConfigLetter.push_back({ { 1,36 }, { 37,37} }); //daad_u
    
    arrayConfigLetter.push_back({ { 1,11 }, { 12,19 }, { 20,20 } }); //dh_a
    arrayConfigLetter.push_back({ { 1,12 }, { 13,34}, { 35,35}, { 36,36}, { 37,37} }); //dh_i
    arrayConfigLetter.push_back({ { 1,11 }, { 12,27}, { 28,28} }); //dh_u
    
    arrayConfigLetter.push_back({ { 1,24 }, { 25,25 } }); //f_a
    arrayConfigLetter.push_back({ { 1,32 }, { 33,33}, { 34,34}, { 35,35} }); //f_i
    arrayConfigLetter.push_back({ { 1,31 }, { 32,32} }); //f_u
    
    arrayConfigLetter.push_back({ { 1,24 }, { 25,25 } }); //g_a
    arrayConfigLetter.push_back({ { 1,35 }, { 36,36 }, { 37,37 }, { 38,38 } }); //g_i
    arrayConfigLetter.push_back({ { 1,37 }, { 38,38 } }); //g_u
    
    arrayConfigLetter.push_back({ { 1,25 }, { 26,26 } }); //gh_a --ok--136
    arrayConfigLetter.push_back({ { 1,34 }, { 35,35 }, { 36,36 }, { 37,37 } }); //gh_i
    arrayConfigLetter.push_back({ { 1,39 }, { 40,40 } }); //gh_u
    
    arrayConfigLetter.push_back({ { 1,33 } }); //h_a
    arrayConfigLetter.push_back({ { 1,40 }, { 41,41 }, { 42,42 } }); //h_i
    arrayConfigLetter.push_back({ { 1,43 } }); //h_u
    
    arrayConfigLetter.push_back({ { 1,28 } }); //ha_a
    arrayConfigLetter.push_back({ { 1,33 }, { 34,34 }, { 35,35 } }); //ha_i
    arrayConfigLetter.push_back({ { 1,31 } }); //ha_u
    
    arrayConfigLetter.push_back({ { 1,27 }, { 28,28 } }); //ja_a
    arrayConfigLetter.push_back({ { 1,35 }, { 36,36 }, { 37,37 }, { 38,38 } }); //ja_i
    arrayConfigLetter.push_back({ { 1,31 }, { 32,32 } }); //ja_u
    
    arrayConfigLetter.push_back({ { 1,29 } }); //k_a --ok--148
    arrayConfigLetter.push_back({ { 1,32 }, { 33,33 }, { 34,34 } }); //k_i
    arrayConfigLetter.push_back({ { 1,43 } }); //k_u
    
    arrayConfigLetter.push_back({ { 1,15 }, { 16,24 } }); //l_a
    arrayConfigLetter.push_back({ { 1,28 }, { 29,29 }, { 30,30 } }); //l_i
    arrayConfigLetter.push_back({ { 1,37 } }); //l_u
    
    arrayConfigLetter.push_back({ { 1,26 } }); //m_a
    arrayConfigLetter.push_back({ { 1,32 }, { 33,33 }, { 34,34 } }); //m_i
    arrayConfigLetter.push_back({ { 1,34 } }); //m_u
    
    arrayConfigLetter.push_back({ { 1,20 }, { 21,21 } }); //n_a
    arrayConfigLetter.push_back({ { 1,23 }, { 24,24 }, { 25,25 }, { 26,26 } }); //n_i
    arrayConfigLetter.push_back({ { 1,28 }, { 29,29 } }); //n_u
    
    arrayConfigLetter.push_back({ { 1,28 }, { 29,29 }, { 30,30 } }); //q_a
    arrayConfigLetter.push_back({ { 1,34 }, { 35,35 }, { 36,36 }, { 37,37}, { 38,38} }); //q_i
    arrayConfigLetter.push_back({ { 1,39 }, { 40,40 }, { 41,41 } }); //q_u
    
    arrayConfigLetter.push_back({ { 1,13 }, { 14,24 } }); //r_a
    arrayConfigLetter.push_back({ { 1,11 }, { 12,37 }, { 38,38 }, { 39,39} }); //r_i
    arrayConfigLetter.push_back({ { 1,11 }, { 12,28 } }); //r_u
    
    arrayConfigLetter.push_back({ { 1,24 } }); //s_a
    arrayConfigLetter.push_back({ { 1,36 }, { 37,37 }, { 38,38 } }); //s_i
    arrayConfigLetter.push_back({ { 1,34 } }); //s_u
    
    arrayConfigLetter.push_back({ { 1,25 } }); //sad_a
    arrayConfigLetter.push_back({ { 1,35 }, { 36,36 }, { 37,37 } }); //sad_i
    arrayConfigLetter.push_back({ { 1,36 } }); //sad_u
    
    arrayConfigLetter.push_back({ { 1,24 }, { 25,25}, { 26,26}, { 27,27 } }); //sh_a
    arrayConfigLetter.push_back({ { 1,36 }, { 37,37}, { 38,38}, { 39,39}, { 40,40}, { 41,41 } }); //sh_i
    arrayConfigLetter.push_back({ { 1,34 }, { 35,35}, { 36,36}, { 37,37} }); //sh_u
    
    arrayConfigLetter.push_back({ { 1,20 }, { 21,21 }, { 22,22 } }); //t_a
    arrayConfigLetter.push_back({ { 1,23 }, { 24,24 }, { 25,25}, { 26,26}, { 27,27 } }); //t_i
    arrayConfigLetter.push_back({ { 1,28 }, { 29,29 }, { 30,30 } }); //t_u
    
    arrayConfigLetter.push_back({ { 1,27} }); //taa_a
    arrayConfigLetter.push_back({ { 1,34 }, { 35,35}, { 36,36} }); //taa_i
    arrayConfigLetter.push_back({ { 1,34} }); //taa_u
    
    arrayConfigLetter.push_back({ { 1,20 }, { 21,21 }, { 22,22}, { 23,23} }); //th_a
    arrayConfigLetter.push_back({ { 1,23 }, { 24,24 }, { 25,25}, { 26,26}, { 27,27 }, { 28,28 } }); //th_i
    arrayConfigLetter.push_back({ { 1,28 }, { 29,29 }, { 30,30 }, { 31,31 } }); //th_u
    
    arrayConfigLetter.push_back({ { 1,16 }, { 17,22 } }); //w_a
    arrayConfigLetter.push_back({ { 1,16 }, { 16,36 }, { 37,37}, { 38,38} }); //w_i
    arrayConfigLetter.push_back({ { 1,16 }, { 17,32 } }); //w_u
    
    arrayConfigLetter.push_back({ { 1,14 }, { 15,15}, { 16,16} }); //y_a
    arrayConfigLetter.push_back({ { 1,22 }, { 23,23 }, { 24,24}, { 25,25}, { 26,26} }); //y_i
    arrayConfigLetter.push_back({ { 1,23 }, { 24,24}, { 25,25} }); //y_u
    
    arrayConfigLetter.push_back({ { 1,9 }, { 10,10}, { 11,16} }); //z_a
    arrayConfigLetter.push_back({ { 1,9 }, { 10,10}, { 11,31}, { 32,32}, { 33,33 } }); //z_i
    arrayConfigLetter.push_back({ { 1,9 }, { 10,10}, { 11,26} }); //z_u
    
    arrayConfigLetter.push_back({ { 1,27},{ 28,28} }); //zaa_a
    arrayConfigLetter.push_back({ { 1,34 }, { 35,35}, { 36,36}, { 37,37} }); //zaa_i
    arrayConfigLetter.push_back({ { 1,34 }, { 35,35} }); //zaa_u
    
    
}
