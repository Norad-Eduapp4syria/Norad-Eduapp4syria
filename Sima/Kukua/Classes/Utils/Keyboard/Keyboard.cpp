#include "Keyboard.h"
#include "../StringUtility.h"
#include "../Data/ArabicHelper.h"



Keyboard::Keyboard(Node& _parentNode, const Vec2& _localPosition, bool _lowercase, EventDispatcher* eventDispatcher){
	assert(&_parentNode != nullptr);

	string csbPath = "Keyboard/KeyboardLetters.csb";
	node = CSLoader::createNode(csbPath);

	_parentNode.addChild(node);
	node->setPosition(_localPosition);

	actionTimeline = CSLoader::createTimeline(csbPath);
	node->runAction(actionTimeline);

	auto keyboardButtons = node->getChildByName("Keyboard");
	//auto nOfKey = keyboardButtons->getChildrenCount();
	//CCLOG("nOfKey %i", nOfKey);


	for (vector<Node*>::iterator iterator = keyboardButtons->getChildren().begin(); iterator != keyboardButtons->getChildren().end(); ++iterator) {
		Node *abc = (*iterator);
		
		string sAll = abc->getName();
		string s = sAll.substr(7, sAll.length());
		string sCase = s;
		std::locale loc;
		// if (_lowercase)sCase = std::tolower(s[0], loc);
        if (_lowercase)sCase = StringUtility::toLowerCase(s);
		//CCLOG("LETTER->%s", s.c_str());
		KeyboardButton* kb;
		if (s != "enter" && s != "space" && s != "canc"){
			kb = new KeyboardButton(*abc->getParent(), StringUtility::toString(sAll), "Keyboard/csd/Button.csb", eventDispatcher);
		}else{
			kb = new KeyboardButton(*abc->getParent(), StringUtility::toString(sAll), "Keyboard/csd/Button_" + StringUtility::toString(s) + ".csb", eventDispatcher);
		}
        keyboardButtonsVec.push_back(kb);
		kb->name = s;
		kb->editText = sCase;
		abc->setName(s);
		if (s != "enter" && s != "space" && s != "canc"){
			//CCLOG("NAME->%s", sAll.c_str());
			auto l = static_cast<cocos2d::ui::Text*>(abc->getChildByName("BoneButton")->getChildByName("Text"));
            l->setString( ArabicHelper::getInstance()->getInArabic( sCase ) );
		}
		
	}
}




Keyboard::~Keyboard() {

    for (vector<KeyboardButton*>::iterator iterator = keyboardButtonsVec.begin(); iterator != keyboardButtonsVec.end(); ++iterator) {
        delete (*iterator);
    }
}


void Keyboard::play(string animationName, std::function<void()> callback, bool looping, float delay, int startFrameOffset) {
	assert(actionTimeline != nullptr);


	if (animationName == "intro")isOpen = true;
	if (animationName == "exit")isOpen = false;

	if (delay > 0.f) {
		node->runAction(
			Sequence::create(
			DelayTime::create(delay),
			CallFunc::create([=]() {
			play(animationName, callback, looping, 0.f, startFrameOffset);
		}),
			nullptr));

	}
	else {
		if (startFrameOffset == 0) {
			actionTimeline->play(animationName, looping);
		}
		else {
			AnimationInfo animationInfo = actionTimeline->getAnimationInfo(animationName);
			actionTimeline->gotoFrameAndPlay(animationInfo.startIndex, animationInfo.endIndex, animationInfo.startIndex + startFrameOffset % (animationInfo.endIndex - animationInfo.startIndex), looping);
		}

		if (callback != nullptr) {
			actionTimeline->setLastFrameCallFunc(callback);
		}

	}

}
