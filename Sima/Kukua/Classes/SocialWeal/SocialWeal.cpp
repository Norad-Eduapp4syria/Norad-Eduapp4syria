#include "SocialWeal.h"
#include "../Utils/Data/DataProvider.h"
#include "../Utils/Data/Logger.h"
#include "../Utils/StringUtility.h"
#include "../MapScene/MapScene.h"
#include "../AppMacros.h"

const bool SocialWeal::ENABLE_TOUCH = true;								// Used to disable tutorial on first touch and manage general touch events
const string SocialWeal::PATH = "SocialWeal/";								// Resources' subfolder path for this game

Scene* SocialWeal::createScene() {

	// 'scene' is an autorelease object
	Scene* scene = Scene::create();

	// 'layer' is an autorelease object			 
	auto layer = SocialWeal::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

SocialWeal::~SocialWeal() {
	
	delete samir;
    delete sima;

	if (hand != nullptr){
		delete hand;
	}

	if (emotes != nullptr){
		delete emotes;
	}
	
	for (int i = 0; i < arrayButton.size(); i++) {
		delete arrayButton[i];
	}
}

bool SocialWeal::init() {

	if (!Layer::init())
	{
		return false;
	}
    
    string phoneme = DataProvider::getInstance()->getCurrentDBKnowledgeBubble()->getPhoneme();
    string skinNum = phoneme.substr(11, phoneme.length()); // 11 is "SocialWeal_" length
    
    SKIN = StringUtility::stringToNumber<int>(skinNum); // from 1 to 9
    

	//create world
	rootNode = CSLoader::createNode(PATH + "MainScene.csb");
	rootNode->setAnchorPoint(Point(0.5, 0.5));
	rootNode->setPosition(Point(_director->getWinSize().width / 2, _director->getWinSize().height / 2));
	addChild(rootNode);


	bgNode = rootNode->getChildByName("BgNode");
	samirNode = rootNode->getChildByName("SamirNode");
	simaNode = rootNode->getChildByName("SimaNode");

	//create bg
	auto bg = Sprite::create(PATH + "PNG/Backgrounds/skin" + StringUtility::toString(SKIN) + ".png");
	bg->setPosition(Vec2(_director->getWinSize().width/2, rootNode->getBoundingBox().size.height / 2));
	bgNode->addChild(bg);

	samir = new GameObject(*samirNode, Vec2(0,0), PATH + "CSD/SAMIR/Samir_skin" + StringUtility::toString(SKIN) + ".csb");
	sima = new GameObject(*simaNode, Vec2(0, 0), PATH + "CSD/SIMA/Sima_Skin" + StringUtility::toString(SKIN) + ".csb");
	samir->play("standing", nullptr, true);
	sima->play("standing", nullptr, true);

	hand = new GameObject(*rootNode, "Hand", PATH + "CSD/hand.csb");

	next = new GameObject(*rootNode, "arrow", PATH + "CSD/INTERFACE/Arrow.csb");
	
	startGame();

	return true;
}

void SocialWeal::createButton(int _id) {
	auto node = dynamic_cast<Node*>(rootNode->getChildByName("Button" + StringUtility::toString(_id)));
	auto button = new GameObject(*node, Vec2(0, 0), PATH + "CSD/INTERFACE/Button_Emote.csb");

	auto icoNode = button->getChild("Button/IcoBone/Ico");
	auto ico = Sprite::create(PATH + "PNG/Gift/ico" + StringUtility::toString(_id) + ".png");
	ico->setScale(0.3);
	icoNode->addChild(ico);

	button->play("popin", nullptr, false);

	arrayButton.push_back(button);
	button->getChild("Selected")->setVisible(false);
}


void SocialWeal::createAnimation(int _character, int _id){
	activeClick = false;
	Node* nodeCharacter;
	if (_character == 1)nodeCharacter = simaNode;
	else nodeCharacter = samirNode;
	emotes = new GameObject(*nodeCharacter, Vec2(0, 0), PATH + "CSD/EMOTES/emotes" + StringUtility::toString(_id) + ".csb");
	emotes->play("all", ([=]() {
		nodeCharacter->removeChild(&(emotes->getNode()));
		delete emotes;
		emotes = nullptr;

		activeNext();

		for (int i = 0; i < arrayButton.size(); i++) {
			arrayButton[i]->getChild("Selected")->setVisible(false);
		}
		//emotes->getActionTimeline()->clearLastFrameCallFunc();
		activeClick = true;
	}), false);	
}
	
void SocialWeal::startGame() {
	Logger::getInstance()->logEvent("SocialWeal", Logger::OPEN, "");
	emotes = nullptr;

	initVariables();
	initAudio();
	initGameObjects();
	fadeIn();
}

void SocialWeal::initVariables() {

	//dataProvider = DataProvider::getInstance();
	arrayButton = {};
	activeClick = false;
	activedNext = false;
	firstClick = false;
	selected = 0;
	inTalk = 0;
	timeAudioIntro = { 12.0f, 13.0f, 13.0f, 13.0f, 13.0f, 15.0f, 13.0f, 14.0f, 14.0f };
	timeAudioSamir = { 8.0f, 8.5f, 6.0f, 6.5f, 10.0f, 10.0f, 6.0f, 8.5f, 6.5f };
	timeAudioSima = { 5.6f, 4.0f, 5.5f, 5.5f, 6.5f, 10.0f, 6.0f, 11.0f, 8.5f };

}

void SocialWeal::initAudio() {
	audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
}

void SocialWeal::initGameObjects() {


}

void SocialWeal::activeNext(){
	if (!activedNext){
		next->play("popin", ([=]() {
			activedNext = true;
			next->play("standing", nullptr, true);
		}), false);
	}
}



void SocialWeal::fadeIn() {

	string linkAudio = PATH + "audio/skin" + StringUtility::toString(SKIN) + "/intro_skin" + StringUtility::toString(SKIN) + ".mp3";
	audioEngine->playEffect(linkAudio.c_str());

	CallFunc *runCallback_jump = CallFunc::create(CC_CALLBACK_0(SocialWeal::activeClickCharacter, this));
	this->runAction(Sequence::create(DelayTime::create(timeAudioIntro[SKIN-1]), runCallback_jump, nullptr));

	
	//declare touch event
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(SocialWeal::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(SocialWeal::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(SocialWeal::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, rootNode);
    
    addBackToMapButton();
}


void SocialWeal::activeClickCharacter() {
	hand->play("tap", nullptr, true);
	activeClick = true;
}
void SocialWeal::stopTalk(){
	
	this->stopActionByTag(90);
	if (inTalk == 1)sima->play("standing", nullptr, true);
	if (inTalk == 2)samir->play("standing", nullptr, true);
	inTalk = 0;
}

void SocialWeal::clickCharacter(int _id){
	if (hand!=nullptr){
		rootNode->removeChild(&(hand->getNode()));
		delete hand;
		hand = nullptr;
	}
	if (!firstClick){
		for (int i = 1; i <= 6; i++)createButton(i);
	}

	stopTalk();

	if (selected != 0){
		createAnimation(_id, selected);
		selected = 0;
	}
	else{
		audioEngine->stopAllEffects();

		float t;
		if (_id == 1)t = timeAudioSima[SKIN - 1];
		else t = timeAudioSamir[SKIN - 1];

		CallFunc *stopTalk = CallFunc::create(CC_CALLBACK_0(SocialWeal::stopTalk, this));
		Action *stopTalkAction = Sequence::create(DelayTime::create(t), stopTalk, nullptr);
		stopTalkAction->setTag(90);
		this->runAction(stopTalkAction);

		if (_id == 1)sima->play("talk", nullptr, true);
		else samir->play("talk", nullptr, true);

		inTalk = _id;

		string linkAudio;
		if (_id == 1)linkAudio = PATH + "audio/skin" + StringUtility::toString(SKIN) + "/sima_skin" + StringUtility::toString(SKIN) + ".mp3";
		else linkAudio = PATH + "audio/skin" + StringUtility::toString(SKIN) + "/samir_skin" + StringUtility::toString(SKIN) + ".mp3";
		audioEngine->playEffect(linkAudio.c_str());
	}

	firstClick = true;

}

void SocialWeal::clickButton(int _id){
	audioEngine->stopAllEffects();

	stopTalk();

	string linkAudio = PATH + "audio/audio" + StringUtility::toString(_id) + ".mp3";
	audioEngine->playEffect(linkAudio.c_str());


	selected = _id;
	for (int i = 0; i < arrayButton.size(); i++) {
		arrayButton[i]->getChild("Selected")->setVisible(false);
	}
	arrayButton[_id-1]->getChild("Selected")->setVisible(true);
}

void SocialWeal::clickNext(){
	CCLOG("AVANTI"); // LUCA click del next... che chiude il gioco
    closeGame();
}

bool SocialWeal::onTouchBegan(Touch* touch, cocos2d::Event* event) {
	float touchX = touch->getLocation().x;
	float touchY = touch->getLocation().y;

	float simaX = sima->getPosition().x;
	float simaY = sima->getPosition().y;

	float samirX = samir->getPosition().x;
	float samirY = samir->getPosition().y;

	float nextX = next->getPosition().x;
	float nextY = next->getPosition().y;

	//CCLOG("touchX: %f", touchX);
	//CCLOG("touchY: %f", touchY);

	if (touchX > simaX - 80 && touchX < simaX + 80 && touchY > simaY - 200 && touchY < simaY + 200){
		if (activeClick)clickCharacter(1);
	}

	if (touchX > samirX - 80 && touchX < samirX + 80 && touchY > samirY - 130 && touchY < samirY + 130){
		if (activeClick)clickCharacter(2);
	}
	if (touchX > nextX - 80 && touchX < nextX + 80 && touchY > nextY - 130 && touchY < nextY + 130){
		if (activedNext)clickNext();
	}
	
	for (int i = 0; i < arrayButton.size(); i++) {

		float buttonX = arrayButton[i]->getPosition().x;
		float buttonY = arrayButton[i]->getPosition().y;

		if (touchX > buttonX - 75 && touchX < buttonX + 75 && touchY > buttonY - 75 && touchY < buttonY + 75){
			if (activeClick)clickButton(i+1);
		}
	}



	return true;
}

void SocialWeal::onTouchMoved(Touch* touch, cocos2d::Event* event) {

}

void SocialWeal::onTouchEnded(Touch* touch, cocos2d::Event* event) {

}

void SocialWeal::closeGame() {
    Logger::getInstance()->logEvent("SocialWeal", Logger::CLOSE, "");
    audioEngine->stopAllEffects();
    audioEngine->stopBackgroundMusic();
    _director->replaceScene(TransitionFade::create(TRANSITION_TIME, MapScene::createScene(), TRANSITION_COLOR));
}


void SocialWeal::addBackToMapButton(){
    
    auto backNode = cocos2d::ui::Button::create(PATH+"PNG/backGuardian_btn.png", PATH+"PNG/backGuardian_btn.png", PATH+"Png/backGuardian_btn.png");
    
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
                closeGame();
                break;
            default:
                break;
        }
    });
    
}
