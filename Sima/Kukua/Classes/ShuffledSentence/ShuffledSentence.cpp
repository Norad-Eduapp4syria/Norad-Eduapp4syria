#include "ShuffledSentence.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "../Utils/Data/DataProvider.h"
#include "../Utils/Data/Logger.h"
#include "../WatchmanScene/WatchmanScene.h"
#include "../Utils/StringUtility.h"
#include "../AppMacros.h"
#include "../Utils/Data/ArabicHelper.h"
#include "../Utils/Data/ArabicHelperForGames.h"


const std::string ShuffledSentence::PATH = "ShuffledSentence/";

#define IS_COLLIDED(A, B, A_BIT, B_BIT) ((A_BIT == A->getContactTestBitmask() && B_BIT == B->getContactTestBitmask()) || \
(B_BIT == A->getContactTestBitmask() && A_BIT == B->getContactTestBitmask()))

ShuffledSentence* ShuffledSentence::gamePlayObject = nullptr;

ShuffledSentence::~ShuffledSentence(void) {
}

void ShuffledSentence::onEnter() {
	Layer::onEnter();
}

void ShuffledSentence::onExit() {
	Layer::onExit();
}

Scene* ShuffledSentence::createScene() {
	Scene *scene = Scene::create();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//scene->getPhysicsWorld()->setGravity(Vec2(0, -600));
	Layer* layer = new ShuffledSentence();
	layer->autorelease();
	scene->addChild(layer);
	return scene;
}

ShuffledSentence::ShuffledSentence() {
	Layer::init();
	viewSize = Director::getInstance()->getWinSize();
	frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
	if (frameSize.height > 768)
		scaleFactor = 1.0f;
	else if (frameSize.height > 320)
		scaleFactor = 0.5f;
	else
		scaleFactor = 0.25f;

	gamePlayObject = nullptr;
	gamePlayObject = this;

	//setGameState(STATE_GAME_RUN);

	//createLayerOf(LAYER_TUTORIAL);
	createLayerOf(1); // LAYER_HUD
	createLayerOf(2); // LAYER_PAUSE
	createLayerOf(3); // LAYER_GAME_OVER

	createAllListener();

    //audio
    simpleAudioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
    simpleAudioEngine->preloadBackgroundMusic("common/audio/bg/GAME_1.mp3");
    simpleAudioEngine->playBackgroundMusic("common/audio/bg/GAME_1.mp3", true);
    
	initGame();
    
    addBackToHomeButton();
    
    


	this->schedule(schedule_selector(ShuffledSentence::update));
}

void ShuffledSentence::createLayerOf(int index) {
	switch (index) {
		case 1: {
			hudLayer = nullptr;
			hudLayer = Layer::create();

			//this->addChild(hudLayer, 11);
		}
		break;
		case 2 :{
			pauseLayer = nullptr;
			pauseLayer = Layer::create();

			LayerColor *darkLayer = LayerColor::create(Color4B(0, 0, 0, 150));
			pauseLayer->addChild(darkLayer);

			/*Label* pLabel = Label::createWithSystemFont("Game Paused", "Arial", 24);
			pLabel->setPosition(screenSize.width / 2, screenSize.height - 100);
			pauseLayer->addChild(pLabel);*/
			
			pauseLayer->setVisible(false);
			this->addChild(pauseLayer, 11);
		}
		break;
		case 3: {
			gameOverLayer = nullptr;
			gameOverLayer = Layer::create();

			LayerColor *darkLayer = LayerColor::create(Color4B(0, 0, 0, 150));
			gameOverLayer->addChild(darkLayer);

			gameOverLayer->setVisible(false);
			this->addChild(gameOverLayer, 11);
		}
		break;
	}
}

void ShuffledSentence::createAllListener() {

	auto listener2 = EventListenerTouchOneByOne::create();
	listener2->onTouchBegan = CC_CALLBACK_2(ShuffledSentence::onTouchBegan, this);
	listener2->onTouchMoved = CC_CALLBACK_2(ShuffledSentence::onTouchMoved, this);
	listener2->onTouchEnded = CC_CALLBACK_2(ShuffledSentence::onTouchEnded, this);
	listener2->onTouchCancelled = CC_CALLBACK_2(ShuffledSentence::onTouchCancelled, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);
	contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(ShuffledSentence::onContactBegin, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(ShuffledSentence::onContactSeparate, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void ShuffledSentence::initGame()
{
	gameState = STATE_GAME_PAUSE;
	gameLayer = nullptr;
	gameLayer = Layer::create();
	this->addChild(gameLayer, 2);

    auto dataProvider = DataProvider::getInstance();
    
    string phoneme = dataProvider->getCurrentDBKnowledgeBubble()->getPhoneme();
    
    level = 1;
    
    if (phoneme == "bubble1_ep9")  level = 1;
    else if (phoneme == "bubble2_ep9")  level = 2;
    else if (phoneme == "bubble3_ep9")  level = 3;
    else if (phoneme == "bubble4_ep9")  level = 4;
    else if (phoneme == "bubble5_ep9")  level = 5;
    else if (phoneme == "bubble6_ep9")  level = 6;
    else if (phoneme == "bubble7_ep9")  level = 7;
    else if (phoneme == "bubble8_ep9")  level = 8;
    else if (phoneme == "bubble9_ep9")  level = 9;
    else if (phoneme == "bubble10_ep9")  level = 10;
    else if (phoneme == "bubble11_ep9")  level = 11;
    else if (phoneme == "bubble12_ep9")  level = 12;
    else if (phoneme == "bubble13_ep9")  level = 13;
    else if (phoneme == "bubble14_ep9")  level = 14;
    else if (phoneme == "bubble15_ep9")  level = 15;
    else if (phoneme == "bubble16_ep9")  level = 16;
    else if (phoneme == "bubble17_ep9")  level = 17;
    else if (phoneme == "bubble18_ep9")  level = 18;
    else if (phoneme == "bubble19_ep9")  level = 19;
    else if (phoneme == "bubble20_ep9")  level = 20;
    
	
	//sentence.push_back("We go to the farm.");
    sentence.push_back("نهض عمر من سريره");
	sentence.push_back("أقف عند خط المشاة");
	sentence.push_back("ابتعد الخروف عن القطيع");
	sentence.push_back("الخوخ حلو ولذيذ");
	sentence.push_back("انا احب الرياضة");
	sentence.push_back("احلام ذكية ومهذبة");
	sentence.push_back("العب بالكرة الصغيرة");
	sentence.push_back("الغروب منظر جميل");
	sentence.push_back("لعبة امل جديدة");
	sentence.push_back("احب امي وابي");
	sentence.push_back("ذهبت امي الى السوق");
	sentence.push_back("المعلم يشرح الدرس");
	sentence.push_back("الولد يسمع نصيحة ابيه");
	sentence.push_back("هذه الأشجار عالية");
	sentence.push_back("مهند اهمل دروسه");
	sentence.push_back("انا نجحت في الامتحان");
	sentence.push_back("ليث صديقي المفضل");
	sentence.push_back("الاسماك تعيش في البحر");
	sentence.push_back("الجزر ينمو تحت التراب");
	sentence.push_back("دخلت المعلمة الى الصف");

	//5 Words 0
	//6 words 1
	//8 Words 2
	//4 Words 3
	
	BoxPos[0].push_back(Vec2(viewSize.width / 2-320, viewSize.height / 2 + 80));
	BoxPos[0].push_back(Vec2(viewSize.width / 2 , viewSize.height / 2+80));
	BoxPos[0].push_back(Vec2(viewSize.width / 2+320, viewSize.height / 2+80));
	BoxPos[0].push_back(Vec2(viewSize.width / 2 -180, viewSize.height / 2-80));
	BoxPos[0].push_back(Vec2(viewSize.width / 2+180, viewSize.height / 2 - 80));

	BoxPos[1].push_back(Vec2(viewSize.width / 2 - 320, viewSize.height / 2 + 80));
	BoxPos[1].push_back(Vec2(viewSize.width / 2, viewSize.height / 2 + 80));
	BoxPos[1].push_back(Vec2(viewSize.width / 2 + 320, viewSize.height / 2 + 80));
	BoxPos[1].push_back(Vec2(viewSize.width / 2 - 320, viewSize.height / 2 - 80));
	BoxPos[1].push_back(Vec2(viewSize.width / 2 , viewSize.height / 2 - 80));
	BoxPos[1].push_back(Vec2(viewSize.width / 2 + 320, viewSize.height / 2 - 80));

	BoxPos[2].push_back(Vec2(viewSize.width / 2 - 390, viewSize.height / 2 + 80));
	BoxPos[2].push_back(Vec2(viewSize.width / 2-130, viewSize.height / 2 + 80));
	BoxPos[2].push_back(Vec2(viewSize.width / 2 + 130, viewSize.height / 2 + 80));
	BoxPos[2].push_back(Vec2(viewSize.width / 2 + 390, viewSize.height / 2 + 80));
	BoxPos[2].push_back(Vec2(viewSize.width / 2-390, viewSize.height / 2 - 80));
	BoxPos[2].push_back(Vec2(viewSize.width / 2 -130, viewSize.height / 2 - 80));
	BoxPos[2].push_back(Vec2(viewSize.width / 2+130, viewSize.height / 2 - 80));
	BoxPos[2].push_back(Vec2(viewSize.width / 2 + 390, viewSize.height / 2 - 80));


	BoxPos[3].push_back(Vec2(viewSize.width / 2 - 150, viewSize.height / 2 + 80));
	BoxPos[3].push_back(Vec2(viewSize.width / 2 + 150, viewSize.height / 2 + 80));
	BoxPos[3].push_back(Vec2(viewSize.width / 2 - 150, viewSize.height / 2 - 80));
	BoxPos[3].push_back(Vec2(viewSize.width / 2 + 150, viewSize.height / 2 - 80));

//Dummy Positions
	dummyBoxPos[0].push_back(Vec2(viewSize.width / 2 - 380, viewSize.height / 2 + 250));
	dummyBoxPos[0].push_back(Vec2(viewSize.width / 2+50, viewSize.height / 2 + 250));
	dummyBoxPos[0].push_back(Vec2(viewSize.width / 2 + 380, viewSize.height / 2 + 250));
	dummyBoxPos[0].push_back(Vec2(viewSize.width / 2 - 280, viewSize.height / 2 - 250));
	dummyBoxPos[0].push_back(Vec2(viewSize.width / 2 + 320, viewSize.height / 2 - 250));

	dummyBoxPos[1].push_back(Vec2(viewSize.width / 2 - 390, viewSize.height / 2 + 250));
	dummyBoxPos[1].push_back(Vec2(viewSize.width / 2+70, viewSize.height / 2 + 250));
	dummyBoxPos[1].push_back(Vec2(viewSize.width / 2 + 400, viewSize.height / 2 + 250));
	dummyBoxPos[1].push_back(Vec2(viewSize.width / 2 - 380, viewSize.height / 2 - 250));
	dummyBoxPos[1].push_back(Vec2(viewSize.width / 2-50, viewSize.height / 2 - 250));
	dummyBoxPos[1].push_back(Vec2(viewSize.width / 2 + 360, viewSize.height / 2 - 250));

	dummyBoxPos[2].push_back(Vec2(viewSize.width / 2 - 440, viewSize.height / 2 + 250));
	dummyBoxPos[2].push_back(Vec2(viewSize.width / 2 - 150, viewSize.height / 2 + 250));
	dummyBoxPos[2].push_back(Vec2(viewSize.width / 2 + 150, viewSize.height / 2 + 250));
	dummyBoxPos[2].push_back(Vec2(viewSize.width / 2 + 460, viewSize.height / 2 + 250));
	dummyBoxPos[2].push_back(Vec2(viewSize.width / 2 - 410, viewSize.height / 2 - 250));
	dummyBoxPos[2].push_back(Vec2(viewSize.width / 2 - 110, viewSize.height / 2 - 250));
	dummyBoxPos[2].push_back(Vec2(viewSize.width / 2 + 150, viewSize.height / 2 - 250));
	dummyBoxPos[2].push_back(Vec2(viewSize.width / 2 + 400, viewSize.height / 2 - 250));


	dummyBoxPos[3].push_back(Vec2(viewSize.width / 2 - 350, viewSize.height / 2 + 250));
	dummyBoxPos[3].push_back(Vec2(viewSize.width / 2 + 350, viewSize.height / 2 + 250));
	dummyBoxPos[3].push_back(Vec2(viewSize.width / 2 - 350, viewSize.height / 2 - 250));
	dummyBoxPos[3].push_back(Vec2(viewSize.width / 2 + 350, viewSize.height / 2 - 250));

	//Rotation
	boxRotation[0].push_back(20.0f);
	boxRotation[0].push_back(-20.0f);
	boxRotation[0].push_back(20.0f);
	boxRotation[0].push_back(-30.0f);
	boxRotation[0].push_back(25.0f);

	boxRotation[1].push_back(20.0f);
	boxRotation[1].push_back(-20.0f);
	boxRotation[1].push_back(20.0f);
	boxRotation[1].push_back(-30.0f);
	boxRotation[1].push_back(20.0f);
	boxRotation[1].push_back(-20.0f);

	boxRotation[2].push_back(20.0f);
	boxRotation[2].push_back(-20.0f);
	boxRotation[2].push_back(20.0f);
	boxRotation[2].push_back(-30.0f);
	boxRotation[2].push_back(-30.0f);
	boxRotation[2].push_back(25.0f);
	boxRotation[2].push_back(-20.0f);
	boxRotation[2].push_back(35.0f);

	boxRotation[3].push_back(-30.0f);
	boxRotation[3].push_back(25.0f);
	boxRotation[3].push_back(25.0f);
	boxRotation[3].push_back(-30.0f);

    
    int skin = dataProvider->getSkin();
    string skinStr = StringUtility::toString( skin );
    
    Sprite *sprtBg = Sprite::create( PATH+"png/Background/background_"+skinStr+".png" );
    sprtBg->setPosition(viewSize / 2);
    gameLayer->addChild(sprtBg);
    
    Data rhinodata = FileUtils::getInstance()->getDataFromFile(PATH+"csd/Animal_"+skinStr+".csb");
    rhino = CSLoader::createNode(rhinodata);
    // rhino = CSLoader::createNode(PATH+"csd/Animal.csb");
    
    gameLayer->addChild(rhino,2);
    cocostudio::timeline::ActionTimeline* action = CSLoader::createTimeline(rhinodata, PATH+"csd/Animal_"+skinStr+".csb");
    // cocostudio::timeline::ActionTimeline* action = CSLoader::createTimeline(PATH+"csd/Animal.csb");
    rhino->runAction(action);
    action->gotoFrameAndPlay(0);
    rhino->setPosition(Vec2(viewSize.width / 2 - 1500, viewSize.height / 2 - 110));
    
    
    Data spiralData = FileUtils::getInstance()->getDataFromFile(PATH+"csd/spiral.csb");
	spiral = CSLoader::createNode(spiralData);
	gameLayer->addChild(spiral, 2);
	spiral->setPosition(Vec2(-150000000, -15000000));

	Data borddata = FileUtils::getInstance()->getDataFromFile(PATH+"csd/cartel_positive.csb");
	bord = CSLoader::createNode(borddata);
	gameLayer->addChild(bord, 2);
	bord->setPosition(Vec2(viewSize.width / 2, viewSize.height / 2 + 440));
	bord->setVisible(false);

	Data girldata = FileUtils::getInstance()->getDataFromFile(PATH+"csd/sema_positive.csb");
	girl = CSLoader::createNode(girldata);
	girl->setVisible(false);
	gameLayer->addChild(girl, 2);
	girl->setPosition(Vec2(viewSize.width / 2, viewSize.height / 2 - 230));

	
	hintHand = Sprite::create(PATH+"png/hand.png");
	gameLayer->addChild(hintHand, 12);
	hintHand->setPosition(Vec2(viewSize.width / 2, viewSize.height / 2));
	hintHand->setVisible(false);
	hintHand->setScale(0.8f);
	
    scorePercent = 100.0f;
    scoreToSubtract = 10.0f;

	//createParticale();

	for (int i = 0; i < 15; i++)
	{
		lblOnBox[i] = nullptr;
		imgBox[i] = nullptr;
	}
	createWords();
}

void ShuffledSentence::setGameState(int state)
{
	if (gameState == state)
		return;
	switch (state) {
	case STATE_START:
		break;
	case STATE_GAME_WIN:
		break;
	}
	gameState = state;
}

void ShuffledSentence::rhinoCome()
{
	rhino->setPosition(Vec2(viewSize.width / 2 - 1500, viewSize.height / 2 - 110));
	rhino->runAction(MoveTo::create(4.0f, Vec2(viewSize.width / 2 + 1500, viewSize.height / 2 - 110)));
	boxDistroy = 0;
	this->runAction(Sequence::create(DelayTime::create(4.1f),CallFunc::create(CC_CALLBACK_0(ShuffledSentence::showHint, this)), CallFunc::create(CC_CALLBACK_0(ShuffledSentence::setGameState, this, 1)), nullptr));
	schedule(SEL_SCHEDULE(&ShuffledSentence::updateGame));
}

void ShuffledSentence::showHint()
{
	unschedule(SEL_SCHEDULE(&ShuffledSentence::updateGame));
	hintHand->stopAllActions();
	hintHand->runAction(RepeatForever::create(Sequence::create(MoveTo::create(0.0f, Vec2(lblOnBox[0]->getPositionX(), lblOnBox[0]->getPositionY() - 70)), Show::create(), DelayTime::create(0.2f), MoveTo::create(0.8f, Vec2(imgBox[0]->getPositionX(), imgBox[0]->getPositionY()-70)), DelayTime::create(0.2f), Hide::create(), DelayTime::create(0.5f), nullptr)));
}

void ShuffledSentence::changeZorder(Ref *pSender)
{
	Label *tmp = (Label*)pSender;
	tmp->setLocalZOrder(1);
}

void ShuffledSentence::createParticale()
{
	for (int i = 0; i < 20; i++)
	{
		int rndval = getRandom(1, 5);
		Sprite *sprt = Sprite::create(StringUtils::format("ShuffledSentence/candy/candy_%d.png",rndval));
		sprt->setPosition(Vec2(getRandom(viewSize.width/2-500,viewSize.width/2+500,50), viewSize.height / 2 + 600));
		gameLayer->addChild(sprt,1);
		sprt->setTag(10000 + i);
		sprt->runAction(Sequence::create(DelayTime::create(i*0.1f), Spawn::create(MoveTo::create(getRandom(1.2f, 1.2f), Vec2(sprt->getPositionX(), viewSize.height / 2 - 500)), RotateBy::create(0.8f, getRandom(-350, 390, 20)), nullptr),/*RemoveSelf::create(),*/ nullptr));
		
		if (i == 19)
		{
			this->runAction(Sequence::create(DelayTime::create(1.8f),CallFunc::create(CC_CALLBACK_0(ShuffledSentence::boxGoLeft,this)), nullptr));
		}
	}
}

void ShuffledSentence::callWellDoneAnimation()
{
	Data girldata = FileUtils::getInstance()->getDataFromFile(PATH+"csd/sema_positive.csb");
	cocostudio::timeline::ActionTimeline* action1 = CSLoader::createTimeline(girldata, PATH+"csd/sema_positive.csb");
	girl->runAction(action1);
	action1->play("Well_Apparizione", false);
	girl->setVisible(true);
	Data borddata = FileUtils::getInstance()->getDataFromFile(PATH+"csd/cartel_positive.csb");
	cocostudio::timeline::ActionTimeline* bordaction1 = CSLoader::createTimeline(borddata, PATH+"csd/cartel_positive.csb");
	bord->runAction(bordaction1);
	bordaction1->play("enter", false);
	bord->setVisible(true);
	this->runAction(Sequence::create(DelayTime::create(3.0f), CallFunc::create(CC_CALLBACK_0(ShuffledSentence::callOutAnimation, this)), nullptr));
}

void ShuffledSentence::callOutAnimation()
{
	Data girldata = FileUtils::getInstance()->getDataFromFile(PATH+"csd/sema_positive.csb");
	cocostudio::timeline::ActionTimeline* action1 = CSLoader::createTimeline(girldata, PATH+"csd/sema_positive.csb");
	//RIMETTERE? girl->runAction(action1);
	action1->play("Well_Sparizione", false);

	Data borddata = FileUtils::getInstance()->getDataFromFile(PATH+"csd/cartel_positive.csb");
	cocostudio::timeline::ActionTimeline* bordaction1 = CSLoader::createTimeline(borddata, PATH+"csd/cartel_positive.csb");
	//RIMETTERE? bord->runAction(bordaction1);
	//	bordaction1->gotoFrameAndPlay(0);
	bordaction1->play("exit", false);
	level++;
	if (level > 20)
	{
		level = 1;
	}
	for (int i = 10000; i < 10100; i++)
	{
		if (gameLayer->getChildByTag(i))
		{
			gameLayer->getChildByTag(i)->removeFromParent();
		}
	}
	this->runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create(CC_CALLBACK_0(ShuffledSentence::backToWatchmanWin, this)), nullptr));
}

void ShuffledSentence::backToWatchmanWin() {
    simpleAudioEngine->stopBackgroundMusic();
    Logger::getInstance()->logEvent("ShuffledSentence", Logger::CLOSE, "");
    DataProvider::getInstance()->setGameCompleted("ShuffledSentence");
    DataProvider::getInstance()->setWatchmanReaction(WatchmanScene::GOOD_REACTION);
    _director->replaceScene(TransitionFade::create(TRANSITION_TIME, WatchmanScene::createScene(), TRANSITION_COLOR));
}

void ShuffledSentence::stopAction(Ref *pSender)
{

}

void ShuffledSentence::boxGoLeft()
{
	for (int i = 0; i < totalWords; i++)
	{
		if (i == totalWords - 1)
		{
			lblOnBox[i]->runAction(Sequence::create(DelayTime::create(1 + i), EaseBackIn::create(MoveTo::create(0.6f, Vec2(viewSize.width / 2 - 1200, lblOnBox[i]->getPositionY()))), CallFunc::create(CC_CALLBACK_0(ShuffledSentence::callWellDoneAnimation, this)), nullptr));
		}
		else
		{
			lblOnBox[i]->runAction(Sequence::create(DelayTime::create(1 + i), EaseBackIn::create(MoveTo::create(0.6f, Vec2(viewSize.width / 2 - 1200, lblOnBox[i]->getPositionY()))), nullptr));
		}
		
	}
}
void ShuffledSentence::createWords()
{
	for (int i = 0; i < 15; i++)
	{
		if (lblOnBox[i] != nullptr)
		{
			lblOnBox[i]->removeFromParent();
			lblOnBox[i] = nullptr;
		}
		if (imgBox[i] != nullptr)
		{
			imgBox[i]->removeFromParent();
			imgBox[i] = nullptr;
		}
	}
	moveTag = -10;
	std::string lblString[15];
	int tmp = 0;
	posIndex = mainScore = 0;
	for (int i = 0; i < sentence.at(level-1).length(); i++)
	{
		if (sentence.at(level-1).at(i) == ' ')
		{
			tmp++;
			continue;
		}
		lblString[tmp].append(StringUtils::format("%c", sentence.at(level-1).at(i)).c_str());
	}
	if (tmp + 1 == 4)
	{
		posIndex = 3;
	}
	else if (tmp + 1 == 5)
	{
		posIndex = 0;
	}
	else if (tmp + 1 == 6)
	{
		posIndex = 1;
	}
	else if (tmp + 1 == 8)
	{
		posIndex = 2;
	}
	for (int i = 0; i <= tmp; i++)
	{
        lblOnBox[i] = ArabicHelper::getInstance()->createLabel(lblString[i].c_str(), 70); //Label::createWithTTF(lblString[i].c_str(), "common/fonts/Century Gothic Bold.ttf", 70);
		lblOnBox[i]->setColor(Color3B(205, 133, 63));
		lblOnBox[i]->setTag(1000 + i);
		gameLayer->addChild(lblOnBox[i],1);
		lblOnBox[i]->setScale(0);

		lblOnBox[i]->setPosition(BoxPos[posIndex].at(i));
		//lblOnBox[i]->setRotation(boxRotation[posIndex].at(i));

		middlePart[i] = cocos2d::ui::Scale9Sprite::create(PATH+"box_full.png");
		middlePart[i]->setPosition(Vec2(lblOnBox[i]->getContentSize().width / 2, lblOnBox[i]->getContentSize().height / 2));
		middlePart[i]->setPreferredSize(Size(lblOnBox[i]->getContentSize().width + 100, 120));
		lblOnBox[i]->addChild(middlePart[i], -1);

		imgBox[i] = cocos2d::ui::Scale9Sprite::create(PATH+"box_empty.png");
		imgBox[i]->setPosition(BoxPos[posIndex].at(i));
		imgBox[i]->setVisible(false);
		imgBox[i]->setPreferredSize(Size(lblOnBox[i]->getContentSize().width + 100, 120));
		gameLayer->addChild(imgBox[i]);
		alocPos[i] = 0;
	}
	totalWords = tmp + 1;
	int rndVal = getRandom(0, tmp);
	for (int i = 0; i <= tmp; i++)
	{
		
		imgBox[i]->runAction(Sequence::create(DelayTime::create(i + 1.4f),Show::create(), nullptr));
		if (i == tmp)
		{
			lblOnBox[i]->runAction(Sequence::create(DelayTime::create(i + 0.2f), EaseBackOut::create(ScaleTo::create(0.4f, 1.0)),DelayTime::create(0.5f),CallFunc::create(CC_CALLBACK_0(ShuffledSentence::rhinoCome,this)), nullptr));
		}
		else
		{
			lblOnBox[i]->runAction(Sequence::create(DelayTime::create(i + 0.2f), EaseBackOut::create(ScaleTo::create(0.4f, 1.0)), nullptr));
		}
	}


    
    
    runAction(
        Sequence::createWithTwoActions(
              DelayTime::create(0.5f),
              CallFunc::create([&]() {
                    playAudioCommand();
              })
       )
   );
    
}



void ShuffledSentence::playAudioCommand() {
    string arab = sentence.at(level-1);
    string englishFileName = ArabicHelperForGames::getInstance()->getFilenameInEnglish_shuffledSentence(arab);
    
    std::replace( englishFileName.begin(), englishFileName.end(), ' ', '_'); // replace all ' ' to '_'
    englishFileName = StringUtility::toLowerCase(englishFileName);
    
    
    
    simpleAudioEngine->playEffect("ShuffledSentence/Audio/ShuffledSentence.mp3");
    this->runAction(Sequence::create(DelayTime::create(3.5f), CallFunc::create([=](){
        
        simpleAudioEngine->playEffect(("ShuffledSentence/Audio/sentences/"+englishFileName+".mp3").c_str());
        
    }),  nullptr));
    
    
    
}

bool ShuffledSentence::onContactBegin(PhysicsContact &contact) {
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();

	if (IS_COLLIDED(a, b, 0x00000111, 0x00000011)) {
		Sprite *s1 = (Sprite *)a->getNode();
		Sprite *s2 = (Sprite *)b->getNode();

	}
	else if (IS_COLLIDED(a, b, 0x00000111, 0x00111111)) {
		
	}

	return true;
}

void ShuffledSentence::onContactSeparate(PhysicsContact &contact) {
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();

}

bool ShuffledSentence::onTouchBegan(Touch *touch, Event *event)
{
	if (gameState != STATE_GAME_RUN)
	{
		return false;
	}
	for (int i = 0; i < totalWords; i++)
	{
		if (middlePart[i]->getBoundingBox().containsPoint(lblOnBox[i]->convertToNodeSpace(touch->getLocation())) && lblOnBox[i]->getNumberOfRunningActions() == 0 && lblOnBox[i]->getPosition() != BoxPos[posIndex].at(i))
		{
			tempPos = lblOnBox[i]->getPosition();
			tempRotation = lblOnBox[i]->getRotation();
			moveTag = i;
			lblOnBox[i]->setRotation(0);
			hintHand->stopAllActions();
			hintHand->setVisible(false);
			for (int i = 0; i < totalWords; i++)
			{
				lblOnBox[i]->setLocalZOrder(1);
			}
			return true;
		}
	}
	return true;
}

void ShuffledSentence::onTouchMoved(Touch *touch, Event *event) 
{
	if (moveTag != -10)
	{
		lblOnBox[moveTag]->setPosition(Vec2(touch->getLocation().x, touch->getLocation().y + 40));
		lblOnBox[moveTag]->setLocalZOrder(10);
	}
}

void ShuffledSentence::onTouchEnded(Touch *touch, Event *event)
{
	if (moveTag != -10)
	{
		if (lblOnBox[moveTag]->getBoundingBox().containsPoint(BoxPos[posIndex].at(moveTag)) && imgBox[moveTag]->isVisible() && imgBox[moveTag]->getNumberOfRunningActions()==0)
		{
			lblOnBox[moveTag]->setPosition(BoxPos[posIndex].at(moveTag));
			lblOnBox[moveTag]->runAction(Sequence::create(Spawn::create(ScaleTo::create(0.2f,1.5f),RotateBy::create(0.2f,720),nullptr),EaseBackIn::create(ScaleTo::create(0.2f,1.0f)),nullptr));
			imgBox[moveTag]->runAction(Sequence::create(DelayTime::create(0.7), Hide::create() , nullptr));
			for (int i = 0; i < totalWords; i++)
			{
				lblOnBox[i]->setLocalZOrder(1);
			}
			lblOnBox[moveTag]->setLocalZOrder(2);

			spiral->stopAllActions();
			spiral->setVisible(false);
			Data spiralData = FileUtils::getInstance()->getDataFromFile(PATH+"csd/spiral.csb");
			cocostudio::timeline::ActionTimeline* spiralaction = CSLoader::createTimeline(spiralData, PATH+"csd/spiral.csb");
			spiral->runAction(spiralaction);
			spiralaction->gotoFrameAndPlay(0);
			spiral->setPosition(BoxPos[posIndex].at(moveTag));
			spiral->runAction(Sequence::create(DelayTime::create(0.4f), Show::create(), DelayTime::create(0.8f), MoveTo::create(0.0f, Vec2(-1500000, -1500000000)), nullptr));
			lblOnBox[moveTag]->runAction(Sequence::create(DelayTime::create(1.2f), CallFunc::create(CC_CALLBACK_0(ShuffledSentence::changeZorder, this, lblOnBox[moveTag])), nullptr));
			moveTag = -10;
			gameState = STATE_GAME_PAUSE;
			mainScore++;
			if (mainScore == totalWords)
			{
				this->runAction(Sequence::create(DelayTime::create(1.5f), CallFunc::create(CC_CALLBACK_0(ShuffledSentence::createParticale, this)), nullptr));
			}
			else
			{
				this->runAction(Sequence::create(DelayTime::create(1.3f),CallFunc::create(CC_CALLBACK_0(ShuffledSentence::setGameState,this,1)), nullptr));
			}
			return;
		}
		else
		{
			for (int i = 0; i < totalWords; i++)
			{
				if (i == moveTag)
				{
					continue;
				}
				if (lblOnBox[moveTag]->getBoundingBox().containsPoint(BoxPos[posIndex].at(i)))
				{
 // errata assegnazione, sottraggo punteggio
                    scorePercent -= scoreToSubtract;
                    
					gameState = STATE_GAME_PAUSE;
					lblOnBox[moveTag]->runAction(Sequence::create(Repeat::create(Sequence::create(RotateBy::create(0.05f,-15),RotateBy::create(0.05f,15),nullptr),4),DelayTime::create(0.2f),Spawn::create(MoveTo::create(0.2f,tempPos),RotateTo::create(0.2f,tempRotation),nullptr),nullptr));
					lblOnBox[moveTag]->setLocalZOrder(1);
					moveTag = -10;
					this->runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create(CC_CALLBACK_0(ShuffledSentence::setGameState, this, 1)), nullptr));
					if (mainScore == 0)
					{
						this->runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create(CC_CALLBACK_0(ShuffledSentence::showHint, this)), nullptr));
					}
					return;
				}
			}
			gameState = STATE_GAME_PAUSE;
			lblOnBox[moveTag]->runAction(Sequence::create(DelayTime::create(0.2f), Spawn::create(MoveTo::create(0.2f, tempPos), RotateTo::create(0.2f, tempRotation),nullptr), nullptr));
			lblOnBox[moveTag]->setLocalZOrder(1);
			if (mainScore == 0)
			{
				this->runAction(Sequence::create(DelayTime::create(0.5f), CallFunc::create(CC_CALLBACK_0(ShuffledSentence::showHint, this)), nullptr));
			}
			this->runAction(Sequence::create(DelayTime::create(0.5f), CallFunc::create(CC_CALLBACK_0(ShuffledSentence::setGameState, this, 1)), nullptr));
			moveTag = -10;
			tempPos = Vec2(0, 0);
			tempRotation = 0;
			return;
		}
	}
}

void ShuffledSentence::onTouchCancelled(Touch *touch, Event *event) {
	onTouchEnded(touch, event);
}

void ShuffledSentence::updateGame(float dt) 
{
	for (int i = 0; i < totalWords; i++)
	{
		if (lblOnBox[i]->getBoundingBox().intersectsRect(rhino->getBoundingBox()) && lblOnBox[i]->getPosition() == BoxPos[posIndex].at(i) && lblOnBox[i]->getNumberOfRunningActions() == 0)
		{
			int rndVal = getRandom(0, totalWords-1);
			while (alocPos[rndVal] != 0)
			{
				rndVal = getRandom(0, totalWords-1);
			}
			alocPos[rndVal] = 1;
			//float distance = 100;
			float currDistance = BoxPos[posIndex].at(i).y - dummyBoxPos[posIndex].at(rndVal).y;
			if (currDistance < 0)
			{
				currDistance = -currDistance;
			}
			float speed = (currDistance*0.2f) / 100;
			lblOnBox[i]->runAction(Sequence::create(DelayTime::create(0.2f), Spawn::create(MoveTo::create(speed, dummyBoxPos[posIndex].at(rndVal)), RotateTo::create(speed, boxRotation[posIndex].at(rndVal)), nullptr), nullptr));
			boxDistroy++;
			if (boxDistroy==totalWords - 1)
			{
			//	
				//this->runAction(Sequence::create(DelayTime::create(0.2f), DelayTime::create(1.0f), CallFunc::create(CC_CALLBACK_0(ShuffledSentence::showHint, this)), nullptr));
			}
		}
	}
}


int ShuffledSentence::getRandom(int lowerLimit, int upperLimit) {
    return (lowerLimit + (rand() % (upperLimit - lowerLimit + 1)));
}

int ShuffledSentence::getRandom(int lowerLimit, int upperLimit, int gap) {
    int low = (lowerLimit / gap) + ((lowerLimit % gap == 0) ? 0 : 1);
    int high = upperLimit / gap;
    return ((low + (rand() % (high - low + 1))) * gap);
}


void ShuffledSentence::addBackToHomeButton(){
    
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
                Logger::getInstance()->logEvent("ShuffledSentence", Logger::CLOSE, "");
                if ( TEST_ENABLED ) {
                    DataProvider::getInstance()->setGameCompleted("ShuffledSentence");
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
