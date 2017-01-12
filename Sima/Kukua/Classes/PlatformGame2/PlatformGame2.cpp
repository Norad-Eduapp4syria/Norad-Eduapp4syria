#include "PlatformGame2.h"
#include "../Utils/StringUtility.h"
#include "../Utils/Data/DataProvider.h"
#include "../WatchmanScene/WatchmanScene.h"
// lasciare commentato
#include "../AppMacros.h"
#include "../Utils/Data/ArabicHelper.h"

using namespace std;

/*
>UI (>barra, >vite)
>Salto
>Lettere
>Ostacoli
>Gestione livelli
>Volo
>Hit
>voragine
>tunnel
>Audio
>Fine Gioco positivo
>Fine Gioco Negativo
>Lettera help
>Fine gioco si ferma scorrimento
>Pozione + lunga
>Arcobaleno dopo presa pozzione.
>Finale no volo
>>bug - salto prima arcobaleno
>>Controllo livelli
bug - inArcobalenoMuore
hand help


*/


template<> const bool kukua::Game<PlatformGame2>::USE_PHYSICS = true;										// Enable/disable physics
template<> const bool kukua::Game<PlatformGame2>::ENABLE_TOUCH = true;										// Used to disable tutorial on first touch and manage general touch events
template<> string kukua::Game<PlatformGame2>::PATH = "PlatformGame2/skin1/";									// Resources' subfolder path for this game
template<> const string kukua::Game<PlatformGame2>::BACKGROUND_MUSIC_FILENAME = "";							// Background music filename
template<> bool kukua::Game<PlatformGame2>::SHOWN_TUTORIAL = false;											// Used for showing tutorial on first execution, set to true only if tutorial is not needed
template<> Scene* kukua::Game<PlatformGame2>::scene = nullptr;
template<> const string kukua::Game<PlatformGame2>::NAME = "PlatformGame2";

PlatformGame2::~PlatformGame2() {

	CCLOG("~PlatformGame2");

	//destroy update schedular
	this->unscheduleUpdate();
    
    for (int i = 0; i < arrayLetters.size(); i++) {
        delete arrayLetters[i];
    }
    for (int i = 0; i < arrayObstacleMove.size(); i++) {
        delete arrayObstacleMove[i];
    }

	for (int i = 0; i < arrayBar.size(); i++) {
		delete arrayBar[i];
	}

    
    delete help;
    delete life1;
    delete life2;
    delete life3;
    delete sema;
    delete sema_positive;
    delete sema_negative;
    //delete slider;

	audioEngine->stopAllEffects();
	this->stopActionByTag(90);
    
}




void PlatformGame2::initVariables() {
	potionCount = 0;


	middleY = rootNode->getBoundingBox().size.height / 2;
    
	//lasciare commentato 
	/*
    letterOk = "a";
	letterKo = "b";
	*/
	letterOk = DataProvider::getInstance()->getCurrentDBKnowledgeBubble()->getPhoneme();
	letterKo = DataProvider::getInstance()->getRandomWrongPhoneme(letterOk);
	                                                              
    letterOk = DataProvider::getInstance()->checkAndCorrectDuplicatePhoneme(letterOk);
    letterKo = DataProvider::getInstance()->checkAndCorrectDuplicatePhoneme(letterKo);
	
    if (DataProvider::getInstance()->getCurrentEpisode() == 3) {
        letterOk = letterOk.substr(0, letterOk.find("#"));
        letterOk = letterOk + "_i";
        letterKo = letterKo.substr(0, letterKo.find("#"));
    } else if (DataProvider::getInstance()->getCurrentEpisode() == 1) {
        string::size_type idxEp1b = letterOk.find("#ep1");
        if (idxEp1b != string::npos)
            letterOk.erase(idxEp1b, 4); // 4 is length of "#ep1"
        
        string::size_type idxEp1 = letterKo.find("#ep1");
        if (idxEp1 != string::npos)
            letterKo.erase(idxEp1, 4); // 4 is length of "#ep1"
    }
    

    
    
	level = DataProvider::getInstance()->getSkin();
	
	isFinishStandBy = false;
	isFinish = false;
	isStoped = false;
	slideEnabled = false;
	invincible = false;
	inPotion = false;

	levelDelayFactor =1.2f;
	oldValBar = 0;
	deltaTime = 0;
	lifes = 3;
	velocity = 0;
	ySemaOrigin = middleY - 100;
	whereGoingY = ySemaOrigin;
	energy = 0;
	inJump = false;
	inFly = false;
	inSlide = false;
	inCrack = false;

	
        scorePercent = 100.0f;

	audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();

}

void PlatformGame2::initAudio() {

	audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();

	audioEngine->preloadBackgroundMusic("common/audio/bg/GAME_3.mp3");


	audioEngine->preloadEffect("PlatformGame2/audio/armadillo.mp3");
	audioEngine->preloadEffect("PlatformGame2/audio/bird1.mp3");
	audioEngine->preloadEffect("PlatformGame2/audio/bird2.mp3");
	audioEngine->preloadEffect("PlatformGame2/audio/pig.mp3");
	audioEngine->preloadEffect("PlatformGame2/audio/monkey.mp3");
	audioEngine->preloadEffect("PlatformGame2/audio/feed_neg.mp3");
	audioEngine->preloadEffect("PlatformGame2/audio/feed_pos.mp3");
	audioEngine->preloadEffect("PlatformGame2/audio/hit_generic1.mp3");
	audioEngine->preloadEffect("PlatformGame2/audio/hit_generic2.mp3");
	audioEngine->preloadEffect("PlatformGame2/audio/hit_generic3.mp3");
	audioEngine->preloadEffect("PlatformGame2/audio/jump.mp3");
	audioEngine->preloadEffect("PlatformGame2/audio/jump_finish.mp3");
	audioEngine->preloadEffect("PlatformGame2/audio/run_loop.mp3");
	audioEngine->preloadEffect("PlatformGame2/audio/potion.mp3");
	audioEngine->preloadEffect("PlatformGame2/audio/scivolata_slide.mp3");
	audioEngine->preloadEffect("PlatformGame2/audio/step1fogliame.mp3");
	audioEngine->preloadEffect("PlatformGame2/audio/step2fogliame.mp3");
	audioEngine->preloadEffect("PlatformGame2/audio/step3fogliame.mp3");
	audioEngine->preloadEffect("PlatformGame2/audio/step4fogliame.mp3");
	audioEngine->preloadEffect("PlatformGame2/audio/step5fogliame.mp3");
	audioEngine->preloadEffect("PlatformGame2/audio/step6fogliame.mp3");
	audioEngine->preloadEffect("PlatformGame2/audio/turbo.mp3");
	audioEngine->preloadEffect("PlatformGame2/audio/voragine.mp3");
	audioEngine->preloadEffect("PlatformGame2/audio/Sema_tryagain.mp3");
	audioEngine->preloadEffect("PlatformGame2/audio/Sema_welldone.mp3");
	

	audioEngine->playBackgroundMusic("common/audio/bg/GAME_3.mp3", true);

	

}


void PlatformGame2::toFront(Sprite* _child) {
	if (_parent == nullptr) _parent = static_cast<Node*>(_child->getParent());
	_child->retain();
	_child->removeFromParent();
	_parent->addChild(_child);
	_child->release();
}
void PlatformGame2::toFront(Node* _child) {
	if (_parent == nullptr) _parent = static_cast<Node*>(_child->getParent());
	_child->retain();
	_child->removeFromParent();
	_parent->addChild(_child);
	_child->release();
}


void PlatformGame2::initGameObjects() {

	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_SHAPE);

	//start schedular update
	
	//Node& _parentNode, string _nodeName, string _animationCsbPath, string _colliderSpritePath, bool _dynamic, bool _gravityEnabled, EventDispatcher* _eventDispatcher, unsigned int _contactTestBitmask, const PhysicsMaterial& _material, PhysicsShape::Type _shape
	//create GameObject from stage obj
	
	

	sema_positive = new GameObject(*rootNode, "SemaPositive", PATH + "csd/SemaPositive.csb");
	sema_negative = new GameObject(*rootNode, "SemaNegative", PATH + "csd/SemaNegative.csb");

	//slider = new GameObject(*rootNode, "Slider", PATH + "csd/Slider.csb");
	//slider->getNode().setPosition(Vec2(_director->getWinSize().width / 2, middleY + (_director->getWinSize().height / 2) - 70));



	scoreBar = new GameObject(*rootNode, "Score_bar", PATH + "csd/Score_Bar.csb");
	scoreBar->getNode().setPosition(Vec2(_director->getWinSize().width / 2, middleY + (_director->getWinSize().height / 2) - 70));
	scoreBar->setScale(0.6);
	for (int i = 1; i <= 10; i++){
		auto node = scoreBar->getChild("Score_Empty_" + StringUtility::toString(i) + "/Node");
		auto barObj = new GameObject(*node, Vec2(0,0), PATH + "csd/Score.csb");
		barObj->play("pop",nullptr,false);
		arrayBar.push_back(barObj);
	}

	
	life1 = new GameObject(*rootNode->getChildByName("Life1"), Vec2(0, 0), PATH + "csd/Life.csb");
	life2 = new GameObject(*rootNode->getChildByName("Life2"), Vec2(0, 0), PATH + "csd/Life.csb");
	life3 = new GameObject(*rootNode->getChildByName("Life3"), Vec2(0, 0), PATH + "csd/Life.csb");
	rootNode->getChildByName("Life1")->setPosition(Vec2(rootNode->getChildByName("Life1")->getPosition().x, middleY + (_director->getWinSize().height / 2) - 70));
	rootNode->getChildByName("Life2")->setPosition(Vec2(rootNode->getChildByName("Life2")->getPosition().x, middleY + (_director->getWinSize().height / 2) - 70));
	rootNode->getChildByName("Life3")->setPosition(Vec2(rootNode->getChildByName("Life3")->getPosition().x, middleY + (_director->getWinSize().height / 2) - 70));

	help = new GameObject(*rootNode, Vec2(_director->getWinSize().width / 2, middleY), PATH + "csd/Help.csb");
	//lasciare commentato
	//auto letterHelpLabel = Label::createWithTTF("", "common/fonts/Century Gothic Regular.ttf", 400);
	
	auto letterHelpLabel = ArabicHelper::getInstance()->createLabel("", 300); // auto letterHelpLabel = Label::createWithTTF("", "common/fonts/Century Gothic Regular.ttf", 400);
	letterHelpLabel->setString( ArabicHelper::getInstance()->getInArabic( letterOk ) );
	letterHelpLabel->setColor(Color3B(47, 109, 182));
	

	auto letterPart = static_cast<Node*>(help->getChild("Lettera_a"));
	letterPart->addChild(letterHelpLabel, 100);
	letterHelpLabel->setPosition(Vec2(letterPart->getPosition().x, 50 + letterPart->getPosition().y));


	//story = new GameObject(*rootNode, "textbox", PATH + "CSD/box_narration.csb");
	backGround = rootNode->getChildByName("BackGround");
	firstPlane = rootNode->getChildByName("FirstPlane");
	secondPlane = rootNode->getChildByName("SecondPlane");
	rainbow = rootNode->getChildByName("Rainbow");
	letters = rootNode->getChildByName("Letters");
	obstacle = rootNode->getChildByName("Obstacle");
	player = rootNode->getChildByName("Player");

	//sema = new PlatformGameSema(*player, Vec2(200, 350), PATH + "csd/Sema.csb", "MASTER/hitarea", false, false, _eventDispatcher);
	sema = new GameObject(*player, Vec2(200, ySemaOrigin), PATH + "csd/Sema.csb");
	sema->setScale(0.4);

	createBg(2, true);
	createBg(2, false);
	createBg(1, true);
	createBg(1, false);


	CCLOG("Height: %f", _director->getWinSize().height);

	auto bg = Sprite::create(PATH + "png/bgElements/level" + StringUtility::toString(level) + "/back.png");
	bg->setPosition(Vec2(_director->getWinSize().width / 2, middleY));
	backGround->addChild(bg);



	buttonTunnel = Sprite::create(PATH + "png/obstacle/button_arrow.png");
	buttonTunnel->setPosition(Vec2(_director->getWinSize().width / 2, middleY));
	backGround->addChild(buttonTunnel);
	buttonTunnel->setScale(0.5);
	buttonTunnel->setVisible(false);
	

	
}


void PlatformGame2::createLetter(bool _inRainbow, float _x){

	if (_inRainbow)CCLOG("createLetter true %f", _x);
	else CCLOG("createLetter false %f", _x);

	if ((_inRainbow && inPotion) || (!_inRainbow && !inPotion)){
		
		CCLOG("createLetter OK");


		if (rand() % 3 == 0 && level >= 3 && potionCount == 0 && !inPotion){
			potionCount = 4;
			createPotion();
		}
		else{
			potionCount--;
			if (potionCount < 0)potionCount = 0;
			int h;
			int rn = 1 + rand() % 2;
			if (rn == 1) h = middleY + 240;
			else h = middleY - 200;

			if (_x == NULL)_x = _director->getWinSize().width + 300;

			PlatformGameLetter* letter = new PlatformGameLetter(*letters, Vec2(_x, h), PATH + "csd/Letter.csb"); //, "BoneHit/Hit", true, false, _eventDispatcher);

			arrayLetters.push_back(letter);
			//letter->setPhysicsActivated(true);
			//letter->getPhysicsBody().setContactTestBitmask(0xFFFFFFFF);
			//letter->getPhysicsBody().setTag(304);
			//letter->getPhysicsBody().setEnabled(false);

			//lasciare commentato
			//auto label = static_cast<cocos2d::ui::Text*>(letter->getChild("Bone_7/TextLetter"));
			
			auto label = ArabicHelper::getInstance()->createLabel("", 100); //auto label = static_cast<cocos2d::ui::Text*>(letter->getChild("Bone_7/TextLetter"));
			letter->getChild("Bone_7")->addChild(label);
			
            int unCorrect = rand() % 3;
			if (_inRainbow)unCorrect = 0;
			if (unCorrect == 1){
				//lasciare commentato
				//label->setString(letterKo);
				label->setString( ArabicHelper::getInstance()->getInArabic( letterKo ) );
				letter->correct = false;
			}
			else{
				//lasciare commentato
				//label->setString(letterOk);
				label->setString( ArabicHelper::getInstance()->getInArabic( letterOk ) );
				letter->correct = true;
			}
			
		}
	}
	if (!_inRainbow){
		this->runAction(Sequence::create(DelayTime::create(6 * levelDelayFactor), CallFunc::create([=](){
			createLetter(false);
		}), nullptr));
	}

}


void PlatformGame2::createObstacle(){
	CallFunc *runCallback_jump = CallFunc::create(CC_CALLBACK_0(PlatformGame2::createObstacle, this));
	this->runAction(Sequence::create(DelayTime::create(6 * levelDelayFactor), runCallback_jump, nullptr));

	/*
	type = 1 = ostacolo basso
	type = 2 = ostacolo basso 2
	type = 3 = ostacolo lungo
	type = 4 = buco
	type = 5 = ostacolo basso movimento
	type = 6 = ostacolo basso + alto
	type = 7 = ostacolo scivolata
	type = 8 = ostacolo scivolata + basso
	type = 9 = ostacolo basso + alto movimento
	type = 10 = 3 ostacoli basso movimento
	*/
	int type;
	int select;
	if (level == 10)select = 1 + rand() % 3;
	else select = 1 + rand() % 2;

	if (level == 1 && select == 1)type = 1;
	if (level == 1 && select == 2)type = 2;

	if (level == 2 && select == 1)type = 1;
	if (level == 2 && select == 2)type = 4;

	if (level == 3 && select == 1)type = 4;
	if (level == 3 && select == 2)type = 3;

	if (level == 4 && select == 1)type = 3;
	if (level == 4 && select == 2)type = 5;

	if (level == 5 && select == 1)type = 5;
	if (level == 5 && select == 2)type = 6;

	if (level == 6 && select == 1)type = 6;
	if (level == 6 && select == 2)type = 7;

	if (level == 7 && select == 1)type = 7;
	if (level == 7 && select == 2)type = 1;

	if (level == 8 && select == 1)type = 3;
	if (level == 8 && select == 2)type = 8;

	if (level == 9 && select == 1)type = 5;
	if (level == 9 && select == 2)type = 9;

	if (level == 10 && select == 1)type = 4;
	if (level == 10 && select == 2)type = 9;
	if (level == 10 && select == 3)type = 10;

	//lavoroqui
	if (type == 1){
		CCLOG("1");
		PlatformGameObstacle* img1 = new PlatformGameObstacle(PATH + "png/obstacle/lvl" + StringUtility::toString(level) + "_obs_1_low.png");
		img1->setPosition(Vec2(_director->getWinSize().width + 300, middleY - 220));
		img1->name = "low";
		obstacle->addChild(img1);
		arrayObstacle.push_back(img1);
	}
	if (type == 2){
		CCLOG("2");
		PlatformGameObstacle* img1 = new PlatformGameObstacle(PATH + "png/obstacle/lvl" + StringUtility::toString(level) + "_obs_2_low.png");
		img1->setPosition(Vec2(_director->getWinSize().width + 300, middleY - 220));
		img1->name = "low";
		obstacle->addChild(img1);
		arrayObstacle.push_back(img1);
	}
	if (type == 3){
		CCLOG("3");
		PlatformGameObstacle* img1 = new PlatformGameObstacle(PATH + "png/obstacle/lvl" + StringUtility::toString(level) + "_obs_long.png");
		img1->setPosition(Vec2(_director->getWinSize().width + 300, middleY - 220));
		img1->name = "long";
		obstacle->addChild(img1);
		arrayObstacle.push_back(img1);
	}
	if (type == 4){
		CCLOG("4");
		PlatformGameObstacle* img1 = new PlatformGameObstacle(PATH + "png/obstacle/lvl" + StringUtility::toString(level) + "_obs_crack.png");
		img1->name = "crack";
		if (level == 2)img1->setPosition(Vec2(_director->getWinSize().width + 300, middleY - 350));
		else img1->setPosition(Vec2(_director->getWinSize().width + 300, middleY - 350));
		obstacle->addChild(img1);
		arrayObstacle.push_back(img1);
		
	}

	if (type == 5){
		CCLOG("5");

		string nameObstacle;
		if (level == 4)nameObstacle = "ObstacleArmadillo";
		else if (level == 5)nameObstacle = "ObstacleMonkey";
		else nameObstacle = "ObstacleWarthog";

		PlatformGameObstacleMove* obs1 = new PlatformGameObstacleMove(*obstacle, Vec2(_director->getWinSize().width + 300, middleY - 250), PATH + "csd/" + nameObstacle + ".csb");
		arrayObstacleMove.push_back(obs1);
		obs1->name = nameObstacle;
		obs1->play("run", nullptr, true);
	}
	
	if (type == 6){
		CCLOG("6");
		PlatformGameObstacle* img1 = new PlatformGameObstacle(PATH + "png/obstacle/lvl" + StringUtility::toString(level) + "_obs_1_low.png");
		img1->setPosition(Vec2(_director->getWinSize().width + 300, middleY - 220));
		img1->name = "low";
		obstacle->addChild(img1);
		arrayObstacle.push_back(img1);


		PlatformGameObstacle* img2 = new PlatformGameObstacle(PATH + "png/obstacle/lvl" + StringUtility::toString(level) + "_obs_high.png");
		img2->setPosition(Vec2(_director->getWinSize().width + 1000, middleY + 400));
		img2->name = "high";
		obstacle->addChild(img2);
		arrayObstacle.push_back(img2);
	}

	if (type == 7){
		CCLOG("7");
		PlatformGameObstacle* img1 = new PlatformGameObstacle(PATH + "png/obstacle/lvl" + StringUtility::toString(level) + "_tunnel.png");
		img1->setPosition(Vec2(_director->getWinSize().width + 300, middleY + 250));
		img1->name = "tunnel";
		obstacle->addChild(img1);
		arrayObstacle.push_back(img1);

		runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create([=](){
			if (!inFly){
				toFront(buttonTunnel);
				if (!inPotion && !isFinish){
					buttonTunnel->setVisible(true);
					slideEnabled = true;
				}
			}
		}), NULL));

		runAction(Sequence::create(DelayTime::create(2.5f), CallFunc::create([=](){
			buttonTunnel->setVisible(false);
			slideEnabled = false;
		}), NULL));
		
	}

	if (type == 8){
		CCLOG("8");

		runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create([=](){
			if (!inFly){
				toFront(buttonTunnel);
				buttonTunnel->setVisible(true);
				slideEnabled = true;
			}
		}), NULL));

		runAction(Sequence::create(DelayTime::create(2.5f), CallFunc::create([=](){
			buttonTunnel->setVisible(false);
			slideEnabled = false;
		}), NULL));

		PlatformGameObstacle* img1 = new PlatformGameObstacle(PATH + "png/obstacle/lvl" + StringUtility::toString(level) + "_tunnel.png");
		img1->setPosition(Vec2(_director->getWinSize().width + 300, middleY + 250));
		img1->name = "tunnel";
		obstacle->addChild(img1);
		arrayObstacle.push_back(img1);

		PlatformGameObstacle* img2 = new PlatformGameObstacle(PATH + "png/obstacle/lvl" + StringUtility::toString(level) + "_obs_1_low.png");
		img2->setPosition(Vec2(_director->getWinSize().width + 1200, middleY - 220));
		img2->name = "low";
		obstacle->addChild(img2);
		arrayObstacle.push_back(img2);
	}
	
	if (type == 9){

		string nameObstacle;
		if (level == 4)nameObstacle = "ObstacleArmadillo";
		else if (level == 5)nameObstacle = "ObstacleMonkey";
		else nameObstacle = "ObstacleWarthog";

		PlatformGameObstacleMove* obs1 = new PlatformGameObstacleMove(*obstacle, Vec2(_director->getWinSize().width + 900, middleY - 250), PATH + "csd/" + nameObstacle + ".csb");
		arrayObstacleMove.push_back(obs1);
		obs1->name = nameObstacle;
		obs1->play("run", nullptr, true);

		if (level == 9)nameObstacle = "ObstacleBird1";
		else if (level == 10)nameObstacle = "ObstacleBird2";

		PlatformGameObstacleMove* obs2 = new PlatformGameObstacleMove(*obstacle, Vec2(_director->getWinSize().width + 300, middleY + 200), PATH + "csd/" + nameObstacle + ".csb");
		arrayObstacleMove.push_back(obs2);
		obs2->name = nameObstacle;
		obs2->play("run", nullptr, true);
	}

	if (type == 10){
		string nameObstacle;
		if (level == 4)nameObstacle = "ObstacleArmadillo";
		else if (level == 5)nameObstacle = "ObstacleMonkey";
		else nameObstacle = "ObstacleWarthog";

		PlatformGameObstacleMove* obs1 = new PlatformGameObstacleMove(*obstacle, Vec2(_director->getWinSize().width + 300, middleY - 250), PATH + "csd/" + nameObstacle + ".csb");
		arrayObstacleMove.push_back(obs1);
		obs1->name = "low_move";

		PlatformGameObstacleMove* obs2 = new PlatformGameObstacleMove(*obstacle, Vec2(_director->getWinSize().width + 500, middleY - 250), PATH + "csd/" + nameObstacle + ".csb");
		arrayObstacleMove.push_back(obs2);
		obs2->name = "low_move";

		PlatformGameObstacleMove* obs3 = new PlatformGameObstacleMove(*obstacle, Vec2(_director->getWinSize().width + 700, middleY - 250), PATH + "csd/" + nameObstacle + ".csb");
		arrayObstacleMove.push_back(obs3);
		obs3->name = "low_move";

		obs1->play("run", nullptr, true);
		obs2->play("run", nullptr, true);
		obs3->play("run", nullptr, true);

	}
}


void PlatformGame2::createRainbow(){

	

	CallFunc *runCallback_fly1 = CallFunc::create(CC_CALLBACK_0(PlatformGame2::flyStart, this));
	this->runAction(Sequence::create(DelayTime::create(1.5), runCallback_fly1, nullptr));


	Sprite* rnb1 = Sprite::create(PATH + "png/rainbow/rainbow0001.png");
	rnb1->setPosition(Vec2(_director->getWinSize().width * 1.5, middleY));
	rainbow->addChild(rnb1);
	arrayRainbow.push_back(rnb1);

	int i = 0;
	Sprite* rnb2;
	for (i = 0; i < 5; i++){
		createLetter(true, _director->getWinSize().width + 300 + (i * 1000));
	}

	for (i = 0; i < 9; i++){
		rnb2 = Sprite::create(PATH + "png/rainbow/rainbow0002.png");
		rnb2->setPosition(Vec2(_director->getWinSize().width * (2.5 + i), middleY));
		rainbow->addChild(rnb2);
		arrayRainbow.push_back(rnb2);
	}

	Sprite* rnb6 = Sprite::create(PATH + "png/rainbow/rainbow0003.png");
	rnb6->setPosition(Vec2(_director->getWinSize().width * (2.5 + i), middleY));
	rainbow->addChild(rnb6);
	arrayRainbow.push_back(rnb6);


	CallFunc *runCallback_fly2 = CallFunc::create(CC_CALLBACK_0(PlatformGame2::flyFinish, this));
	this->runAction(Sequence::create(DelayTime::create(3+i), runCallback_fly2, nullptr));
}


void PlatformGame2::createPotion(){
	int rn = 1 + rand() % 2;
	int h;
	if (rn == 1) h = middleY + 200;
	else h = middleY - 200;
	potion = new PlatformGameLetter(*letters, Vec2(_director->getWinSize().width + 300, h), PATH + "csd/Potion.csb");
	potion->play("stand", nullptr, true);
	potion->name = "potion";
	arrayLetters.push_back(potion);

}

void PlatformGame2::createSpeed(){
	//int d = _director->getWinSize().height - 400;
	//int rn = 1 + rand() % d;
	//potion = new GameObject(*letters, Vec2(_director->getWinSize().width + 300, rn + 300), PATH + "csd/Potion.csb");
}


void PlatformGame2::createBg(int _type, bool _first){

	CCLOG("heightRootNode: %f", rootNode->getBoundingBox().size.height);

	Sprite* bg;
	int typeSymbol;
	float molt = 0.5;
	if (!_first){ molt = 1.5; }
	if (_type == 1){
		typeSymbol = 1 + rand() % 4;
		bg = Sprite::create(PATH + "png/bgElements/level" + StringUtility::toString(level) + "/first/obj000" + StringUtility::toString(typeSymbol) + ".png");
		bg->setPosition(Vec2(_director->getWinSize().width * molt, rootNode->getBoundingBox().size.height / 2));
		firstPlane->addChild(bg);
		arrayBg1.push_back(bg);
	}
	else{
		typeSymbol = 1 + rand() % 2;
		bg = Sprite::create(PATH + "png/bgElements/level" + StringUtility::toString(level) + "/second/obj000" + StringUtility::toString(typeSymbol) + ".png");
		bg->setPosition(Vec2(_director->getWinSize().width * molt, rootNode->getBoundingBox().size.height / 2));
		secondPlane->addChild(bg);
		arrayBg2.push_back(bg);
	}
}





void PlatformGame2::jumpStart(){
	if (!inJump && !inFly && !inSlide && !inPotion && !isFinish && !inCrack){
		CCLOG("JUMP START");
		inJump = true;
		SimpleAudioEngine::getInstance()->stopEffect(audio1);
		audioEngine->playEffect("PlatformGame2/audio/jump.mp3");
		sema->play("jump_start", ([=]() {
			MoveBy *jumpMoveAc1 = MoveBy::create(0.7, Vec2(0, 300));
			MoveBy *jumpMoveAc2 = MoveBy::create(0.7, Vec2(0, -300));
			auto jumpMove1 = EaseSineOut::create(jumpMoveAc1->clone());
			auto jumpMove2 = EaseSineIn::create(jumpMoveAc2->clone());
			sema->getNode().runAction(Sequence::create(jumpMove1, jumpMove2, nullptr));
			sema->play("jump_float", nullptr, true);
			CallFunc *runCallback_jump = CallFunc::create(CC_CALLBACK_0(PlatformGame2::jumpFinish, this));
			this->runAction(Sequence::create(DelayTime::create(1.4), runCallback_jump, nullptr));
			sema->getActionTimeline()->clearLastFrameCallFunc();
		}), false);
	}
}


void PlatformGame2::jumpFinish(){
	CCLOG("JUMP FINISH");
	audioEngine->playEffect("PlatformGame2/audio/jump_finish.mp3");
	sema->play("jump_finish", ([=]() {
		inJump = false;
		audio1 = audioEngine->playEffect("PlatformGame2/audio/run_loop.mp3", true);
		sema->play("run", nullptr, true);
		sema->getActionTimeline()->clearLastFrameCallFunc();
	}), false);

	
}


void PlatformGame2::flyStart(){
	inJump = true;
	SimpleAudioEngine::getInstance()->stopEffect(audio1);
	sema->play("fly_start", ([=]() {
		inJump = false;
		inFly = true;
		sema->play("fly_float", nullptr, true);
		sema->getActionTimeline()->clearLastFrameCallFunc();
	}), false);
}

void PlatformGame2::flyFinish(){
	inPotion = false;
	invincible = false;
	inFly = false;
	inJump = true;
	whereGoingY = ySemaOrigin;
	MoveTo *flyMoveAc = MoveTo::create(0.3, Vec2(sema->getPosition().x, ySemaOrigin));
	auto flyMove = EaseSineInOut::create(flyMoveAc->clone());
	sema->play(flyMove);
	sema->play("fly_finish", ([=]() {
		inJump = false;
		audio1 = audioEngine->playEffect("PlatformGame2/audio/run_loop.mp3", true);
		sema->play("run", nullptr, true);
		sema->getActionTimeline()->clearLastFrameCallFunc();
	}), false);
	if (isFinishStandBy)endGame(true);
}
void PlatformGame2::collectSpritesInHierarchy(Node* node, vector<Sprite*>& spriteVector) {

	if (node != nullptr) {

		Sprite* sprite = dynamic_cast<Sprite*>(node);

		if (sprite != nullptr) {
			spriteVector.push_back(sprite);
		}

		auto children = node->getChildren();
		for (auto iterator = children.begin(); iterator != children.end(); ++iterator) {
			collectSpritesInHierarchy(*iterator, spriteVector);
		}

	}

}


void PlatformGame2::loseLife() {
	invincible = true;

        scorePercent -= 10.0f;

	for (auto iterator = semaSprites.begin(); iterator != semaSprites.end(); ++iterator) {
		(*iterator)->runAction(
			Sequence::create(
			EaseSineIn::create(TintTo::create(0.25f, Color3B::RED)),
			EaseSineOut::create(TintTo::create(0.25f, Color3B::WHITE)),
			EaseSineIn::create(TintTo::create(0.25f, Color3B::RED)),
			EaseSineOut::create(TintTo::create(0.25f, Color3B::WHITE)),
			EaseSineIn::create(TintTo::create(0.25f, Color3B::RED)),
			EaseSineOut::create(TintTo::create(0.25f, Color3B::WHITE)),
			EaseSineIn::create(TintTo::create(0.25f, Color3B::RED)),
			EaseSineOut::create(TintTo::create(0.25f, Color3B::WHITE)),
			nullptr
			)
		);
	}

	runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create([=](){
		invincible = false;
	}), NULL));


	lifes--;
	if (lifes == 2)life3->play("hide", nullptr, false);
	else if (lifes == 1)life2->play("hide", nullptr, false);
	else if (lifes == 0){
		life1->play("hide", nullptr, false);
		endGame(false);
	}

}

void PlatformGame2::endGame(bool _win) {
	CCLOG("FINE PARTITA");
	isFinish = true;

	

	runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create([=](){
		inJump = false;
		inFly = false;
		sema->play("run", nullptr, true);
		isStoped = true;
		MoveTo *exitMoveAc = MoveTo::create(1.0f, Vec2(_director->getWinSize().width + 300, ySemaOrigin));
		auto exitMove = EaseSineIn::create(exitMoveAc->clone());
		sema->play(exitMove);
	}), NULL));
	
	runAction(Sequence::create(DelayTime::create(3.0f), CallFunc::create([=](){
		if (_win){
			//lasciare commentato
			
            Logger::getInstance()->logEvent("Platform", Logger::WIN, "");
            DataProvider::getInstance()->setGameCompleted("Platform");
            DataProvider::getInstance()->setWatchmanReaction(WatchmanScene::GOOD_REACTION);
			
            
			audio1 = audioEngine->playEffect("PlatformGame2/audio/Sema_welldone.mp3");
			sema_positive->bringToFront();
			sema_positive->play("Sema_positive_A", nullptr, false);
		}
		else{
			//lasciare commentato
            DataProvider::getInstance()->setWatchmanReaction(WatchmanScene::BAD_REACTION);
            
			audio1 = audioEngine->playEffect("PlatformGame2/audio/Sema_tryagain.mp3");
			sema_negative->bringToFront();
			sema_negative->play("Sema_negative_A", nullptr, false);
		}
		CallFunc *runCallback_close = CallFunc::create(CC_CALLBACK_0(PlatformGame2::closeGame, this));
		this->runAction(Sequence::create(DelayTime::create(4), runCallback_close, nullptr));
	}), NULL));
	
	
}

void PlatformGame2::closeGame(){
    simpleAudioEngine->stopBackgroundMusic();
    simpleAudioEngine->stopAllEffects();
    Logger::getInstance()->logEvent("Platform", Logger::CLOSE, "");
	//lasciare commentato
	_director->replaceScene(TransitionFade::create(TRANSITION_TIME, WatchmanScene::createScene(), TRANSITION_COLOR));
}


void PlatformGame2::setBar(int _val){


	if (oldValBar > _val){
        if (oldValBar != 0 && oldValBar <= 10) {
            arrayBar[oldValBar - 1]->play("pop_full_out", nullptr, false);
            audioEngine->playEffect("PlatformGame2/audio/pop_full_out.mp3");
        }
	}
	else{
        if (_val != 0 && _val<=10) {
            arrayBar[_val - 1]->play("pop_full_in", nullptr, false);
            audioEngine->playEffect("PlatformGame2/audio/pop_full_in.mp3");
        }
        
	}
	if (_val == 10){
		if (!inFly){
			endGame(true);
		}
		else{
			isFinishStandBy = true;
		}
	}
	
	
	//slider->getActionTimeline()->gotoFrameAndPause(60 + _val * 6);
	

	oldValBar = _val;
}

void PlatformGame2::fadeIn() {

	
	//slider->play("intro", nullptr, false);

	life1->play("show", nullptr, false);
	life2->play("show", nullptr, false);
	life3->play("show", nullptr, false);


	help->play("Help", ([=]() {
		
		audio1 = audioEngine->playEffect("PlatformGame2/audio/run_loop.mp3", true);
		velocity = 10;
		help->setVisible(false);

		this->scheduleUpdate();

		enableTouch();
		sema->bringToFront();
		sema->play("run", nullptr, true);

		CallFunc *runCallback_jump = CallFunc::create(CC_CALLBACK_0(PlatformGame2::createObstacle, this));
		this->runAction(Sequence::create(DelayTime::create(3 * levelDelayFactor), runCallback_jump, nullptr));

		createLetter(false);

		sema->getActionTimeline()->clearLastFrameCallFunc();
	}), false);

	collectSpritesInHierarchy(static_cast<Node*>(sema->getChild("MASTER")), semaSprites);

	playAudioHelp();
}
void PlatformGame2::playAudioHelp() {

	audioEngine->playEffect("PlatformGame2/audio/AR_PlatformGuardian.mp3", false);
    
    
    runAction(
       Sequence::createWithTwoActions(
            DelayTime::create(2.0f),
            CallFunc::create([=]() {
                  audioEngine->playEffect(("common/audio/grandpa/phonemes/"+letterOk+".mp3").c_str(), false);
              })
        )
    );
    
	CallFunc *audio = CallFunc::create(CC_CALLBACK_0(PlatformGame2::playAudioHelp, this));
	Action *audioAction = Sequence::create(DelayTime::create(20.0), audio, nullptr);
	audioAction->setTag(90);
	this->runAction(audioAction);
   
}

void PlatformGame2::showTutorial() {

}

void PlatformGame2::hideTutorial() {

}

bool PlatformGame2::onTouchBegan(Touch* touch, Event* event) {

	float touchX = touch->getLocation().x;
	float touchY = touch->getLocation().y;

	float buttonTunnelX = buttonTunnel->getPosition().x;
	float buttonTunnelY = buttonTunnel->getPosition().y;

	if (slideEnabled && !inSlide && !inJump && !inFly){
		if (touchX > buttonTunnelX - 70 && touchX < buttonTunnelX + 70 && touchY > buttonTunnelY - 100 && touchY < buttonTunnelY + 100) {
			inSlide = true;
			SimpleAudioEngine::getInstance()->stopEffect(audio1);
			audioEngine->playEffect("PlatformGame2/audio/scivolata_slide.mp3");
			sema->play("slide_in", ([=]() {
				sema->play("slide_loop", nullptr, true);
				sema->getActionTimeline()->clearLastFrameCallFunc();
			}), false);

			runAction(Sequence::create(DelayTime::create(1.3f), CallFunc::create([=](){
				sema->play("slide_out", ([=]() {
					inSlide = false;
					audio1 = audioEngine->playEffect("PlatformGame2/audio/run_loop.mp3", true);
					sema->play("run", nullptr, true);
					sema->getActionTimeline()->clearLastFrameCallFunc();
				}), false);
			}), NULL));
		}
		else{
			jumpStart();
			if (inFly)whereGoingY = touch->getLocation().y;
		}
	}
	else{
		jumpStart();
		if (inFly)whereGoingY = touch->getLocation().y;
	}













	return true;
	
}

void PlatformGame2::onTouchMoved(Touch* touch, Event* event) {
	if (inFly)whereGoingY = touch->getLocation().y;
		
	
}


void PlatformGame2::onTouchEnded(Touch* touch, Event* event) {

}


void PlatformGame2::homeButtonPressed() {
	simpleAudioEngine->stopBackgroundMusic();
    simpleAudioEngine->stopAllEffects();
	//lasciare commentato
	
    if ( TEST_ENABLED ) {
        DataProvider::getInstance()->setGameCompleted("Platform");
        DataProvider::getInstance()->setWatchmanReaction(WatchmanScene::GOOD_REACTION);
    } else {
        DataProvider::getInstance()->setWatchmanReaction(WatchmanScene::BAD_REACTION);
    }
	
   
}


bool PlatformGame2::colliderWithSema(float _x, float _y, float _radiusX, float _radiusY){
	bool _return = false;


	

	float _xSema = sema->getPosition().x;
	float _ySema = sema->getPosition().y;

	

	int uSema = 80;
	//CCLOG("_ySema %f", (_ySema - _y));
	if (std::abs(_xSema - _x)<(uSema + (_radiusX - 20)) && std::abs(_ySema - _y)<(uSema * 2.2 + (_radiusY - 20))){

		CCLOG("_xSema: %f _ySema: %f", _xSema, _ySema);
		CCLOG("_x: %f _y: %f", _x, _y);
		CCLOG("_radiusX: %f _radiusY: %f", _radiusX, _radiusY);

		_return = true;
	}

	return _return;
}




void PlatformGame2::update(float delta) {

	deltaTime += delta;
	//CCLOG("DELTA %f", deltaTime);
		
	if (isStoped)velocity -= 0.1;
	if (velocity < 0)velocity = 0;


	if(inFly)sema->setPosition(Vec2(sema->getPosition().x, sema->getPosition().y - (sema->getPosition().y - whereGoingY) / 10));
	
	//remove
	for (int j = 0; j < arrayBg1.size(); j++) {
		arrayBg1[j]->setPositionX(arrayBg1[j]->getPositionX() - velocity);
		if (arrayBg1[j]->getPositionX() < -_director->getWinSize().width / 2){
			firstPlane->removeChild(arrayBg1[j]);
			arrayBg1.erase(arrayBg1.begin() + j);
			createBg(1, false);
		}
	}

	//remove
	for (int j = 0; j < arrayBg2.size(); j++) {
		arrayBg2[j]->setPositionX(arrayBg2[j]->getPositionX() - velocity / 2);
		if (arrayBg2[j]->getPositionX() < -_director->getWinSize().width / 2){
			secondPlane->removeChild(arrayBg2[j]);
			arrayBg2.erase(arrayBg2.begin() + j);
			createBg(2, false);
		}
	}
	for (int j = 0; j < arrayLetters.size(); j++) {
		
		//collider
		
		if (arrayLetters[j]->name=="potion"){
			if (!isFinish && !arrayLetters[j]->took && colliderWithSema(arrayLetters[j]->getPosition().x, arrayLetters[j]->getPosition().y, arrayLetters[j]->getNode().getBoundingBox().size.width / 2, 50)){
				arrayLetters[j]->took = true;
				inPotion = true;
				invincible = true;
				createRainbow();
				audioEngine->playEffect("PlatformGame2/audio/feed_pos.mp3");
				arrayLetters[j]->play("explo", nullptr, false);
			}
		} else{		
			if (!isFinish && !arrayLetters[j]->took && colliderWithSema(arrayLetters[j]->getPosition().x, arrayLetters[j]->getPosition().y, arrayLetters[j]->getNode().getBoundingBox().size.width / 2, arrayLetters[j]->getNode().getBoundingBox().size.height / 2)){
				arrayLetters[j]->took = true;
				if (arrayLetters[j]->correct){
					audioEngine->playEffect("PlatformGame2/audio/feed_pos.mp3");
					arrayLetters[j]->play("take", ([=]() {
						energy++;
						setBar(energy);
						arrayLetters[j]->getActionTimeline()->clearLastFrameCallFunc();
					}), false);
				}
				else{
					audioEngine->playEffect("PlatformGame2/audio/feed_neg.mp3");
					arrayLetters[j]->play("explo", ([=]() {
						energy--;
						if (energy < 0)energy = 0;
						scorePercent -= 10.0f;

						setBar(energy);
						arrayLetters[j]->getActionTimeline()->clearLastFrameCallFunc();
					}), false);
				}
			}
		}
		//remove
		arrayLetters[j]->setPosition(Vec2(arrayLetters[j]->getPosition().x - velocity, arrayLetters[j]->getPosition().y));
		if (arrayLetters[j]->getPosition().x < -_director->getWinSize().width / 2){
			arrayLetters[j]->getNode().removeFromParent();
			delete arrayLetters[j];
			arrayLetters.erase(arrayLetters.begin() + j);
		}
	}

	for (int j = 0; j < arrayObstacle.size(); j++) {
		arrayObstacle[j]->setPosition(Vec2(arrayObstacle[j]->getPosition().x - velocity, arrayObstacle[j]->getPosition().y));
		
		//collider

		
		if (arrayObstacle[j]->name == "crack"){
			if (!isFinish && !invincible && colliderWithSema(arrayObstacle[j]->getPosition().x, arrayObstacle[j]->getPosition().y, 10, (arrayObstacle[j]->sprite->getBoundingBox().size.height / 2) + 20)){
				if (!inJump && !inFly){
					inCrack = true;
					invincible = true;
					velocity = 0;
					SimpleAudioEngine::getInstance()->stopEffect(audio1);
					audioEngine->playEffect("PlatformGame2/audio/voragine.mp3");
					sema->play("fall_in", ([=]() {

						MoveTo *fallMoveAc = MoveTo::create(0.5, Vec2(sema->getPosition().x, -500));
						auto fallMove = EaseSineIn::create(fallMoveAc->clone());
						sema->play(fallMove);
						runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create([=](){
							loseLife();
							sema->getNode().setPosition(Vec2(sema->getPosition().x, ySemaOrigin));
							inCrack = false;
							velocity = 10;
							audio1 = audioEngine->playEffect("PlatformGame2/audio/run_loop.mp3", true);
							sema->play("run", nullptr, true);
						}), NULL));
						sema->play("fall_loop", ([=]() {

						}), true);
					}), false);
				}
					
			}

			//remove
			if (arrayObstacle[j]->getPosition().x < -_director->getWinSize().width / 2){
				obstacle->removeChild(arrayObstacle[j]);
				arrayObstacle.erase(arrayObstacle.begin() + j);
			}
			
		}
		else{
			if (!isFinish && !invincible && colliderWithSema(arrayObstacle[j]->getPosition().x, arrayObstacle[j]->getPosition().y, arrayObstacle[j]->sprite->getBoundingBox().size.width / 2, arrayObstacle[j]->sprite->getBoundingBox().size.height / 2)){
				if (!inFly){
					if (!((arrayObstacle[j]->name == "low" || arrayObstacle[j]->name == "low_move" || arrayObstacle[j]->name == "long") && (inJump || inFly))){
						CCLOG("----------------> %s", (arrayObstacle[j]->name).c_str());
						if (arrayObstacle[j]->name == "tunnel" && inSlide){

						}
						else{
							audioEngine->playEffect("PlatformGame2/audio/hit_generic1.mp3");
							loseLife();
						}
					}
				}
			}
		}
		
		
	}

	for (int j = 0; j < arrayObstacleMove.size(); j++) {
		arrayObstacleMove[j]->setPosition(Vec2(arrayObstacleMove[j]->getPosition().x - velocity * 1.5, arrayObstacleMove[j]->getPosition().y));
		
		//collider
		if (!isFinish && !invincible && colliderWithSema(arrayObstacleMove[j]->getPosition().x, arrayObstacleMove[j]->getPosition().y, arrayObstacleMove[j]->getNode().getBoundingBox().size.width / 2, arrayObstacleMove[j]->getNode().getBoundingBox().size.height / 2)){
			if (arrayObstacleMove[j]->name == "ObstacleWarthog")audioEngine->playEffect("PlatformGame2/audio/pig.mp3");
			if (arrayObstacleMove[j]->name == "ObstacleMonkey")audioEngine->playEffect("PlatformGame2/audio/monkey.mp3");
			if (arrayObstacleMove[j]->name == "ObstacleArmadillo")audioEngine->playEffect("PlatformGame2/audio/armadillo.mp3");
			if (arrayObstacleMove[j]->name == "ObstacleBird1")audioEngine->playEffect("PlatformGame2/audio/bird1.mp3");
			if (arrayObstacleMove[j]->name == "ObstacleBird2")audioEngine->playEffect("PlatformGame2/audio/bird2.mp3");
			loseLife();
			//arrayObstacleMove.erase(arrayObstacleMove.begin() + j);
		}

		//remove
		if (arrayObstacleMove[j]->getPosition().x < -_director->getWinSize().width / 2){
			arrayObstacleMove[j]->getNode().removeFromParent();
			delete arrayObstacleMove[j];
			arrayObstacleMove.erase(arrayObstacleMove.begin() + j);
		}
	}

	for (int j = 0; j < arrayRainbow.size(); j++) {
		arrayRainbow[j]->setPosition(Vec2(arrayRainbow[j]->getPosition().x - velocity * 2, arrayRainbow[j]->getPosition().y));
		if (arrayRainbow[j]->getPosition().x < -_director->getWinSize().width / 2){
			rainbow->removeChild(arrayRainbow[j]);
			arrayRainbow.erase(arrayRainbow.begin() + j);
		}
	}

	
	//sema

}



