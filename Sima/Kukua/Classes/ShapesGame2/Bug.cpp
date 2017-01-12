#include "Bug.h"
#include "../Utils/StringUtility.h"



Bug::Bug(Node& _parentNode, const Vec2& _localPosition, string _csbPath, int _typeBug, EventDispatcher* _eventDispatcher)
	: TouchableGameObject(_parentNode, _localPosition, _csbPath + "CSD/bug" + StringUtility::toString(_typeBug) + ".csb", "hit", _eventDispatcher)
{
	
	name = "bug";

	audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();

	eventDispatcher = _eventDispatcher;
	localPosition = _localPosition;
	status = 1;
	clicked = false;
	typeBug = _typeBug;

	angleIn = 1 + rand() % 360;
	angleOut = 1 + rand() % 360;

	getNode().setRotation(-angleIn-90);

	int startPosX = (cos(angleIn / 180.0f * M_PI) * 2000) + localPosition.x;
	int startPosY = (sin(angleIn / 180.0f * M_PI) * 2000) + localPosition.y;
	this->setPosition(Vec2(startPosX, startPosY));

	shadow = new GameObject(getNode(), Point(0, 0), _csbPath + "CSD/shadow" + StringUtility::toString(_typeBug) + ".csb");

	update();
	flyIn();
}

Bug::~Bug() {
    delete shadow;
    getNode().stopAllActions();
	getNode().removeFromParent();
}


void Bug::update() {
	CallFunc *runCallback_upadate = CallFunc::create(CC_CALLBACK_0(Bug::update, this));
	getNode().runAction(Sequence::create(DelayTime::create(0.02f), runCallback_upadate, nullptr));
	
	int deltaX = ((getScale()-0.6) * 10) + getPosition().x;
	int deltaY = ((getScale()-0.6) * -100) + getPosition().y;

	shadow->setPosition(Vec2(deltaX, deltaY));
}

void Bug::stop(){
	
	this->setTouchable(true);

	//CCLOG("stop");
	this->getActionTimeline()->gotoFrameAndPause(1);
	//this->getActionTimeline()->clearLastFrameCallFunc();

	CallFunc *runCallback_flyout = CallFunc::create(CC_CALLBACK_0(Bug::flyOut, this));
	getNode().runAction(Sequence::create(DelayTime::create(2), runCallback_flyout, nullptr));
}

//Si posiziona a in un raggio di 2000px
//muove al centron con un andamento quadout
//si ferma per 3 secondi
//muove in un raggio di 2000px con andamento quadin
//(Si puo aggiungere al movimento lineare anche un movimento di oscillazione con il moveby di ampiezza random 50/100 px)
/*

*/
void Bug::scaleMore(){
	ScaleTo *bugMoveActionAc = ScaleTo::create(1, 1);
	auto bugMoveAction = EaseSineInOut::create(bugMoveActionAc->clone());
	this->play(bugMoveAction);
}

void Bug::scaleLess(){
	ScaleTo *bugMoveActionAc = ScaleTo::create(1,0.6);
	auto bugMoveAction = EaseSineInOut::create(bugMoveActionAc->clone());
	this->play(bugMoveAction);
}


void Bug::flyIn(){
	this->bringToFront();
	//CCLOG("flyIn");
	this->play("fly", nullptr, true);

	MoveTo *bugMoveActionAc = MoveTo::create(3, Vec2(localPosition.x, localPosition.y));
	auto bugMoveAction = EaseSineOut::create(bugMoveActionAc->clone());
	this->play(bugMoveAction);

	CallFunc *runCallback_scale = CallFunc::create(CC_CALLBACK_0(Bug::scaleLess, this));
	getNode().runAction(Sequence::create(DelayTime::create(2), runCallback_scale, nullptr));

	CallFunc *runCallback_stop = CallFunc::create(CC_CALLBACK_0(Bug::stop, this));
	getNode().runAction(Sequence::create(DelayTime::create(3.2), runCallback_stop, nullptr));
}

void Bug::flyOutCall(){
	clicked = false;
	flyOut();
	clicked = true;
}


void Bug::flyOut(){
	if (!clicked){
		audioEngine->playEffect("ShapesGame2/audio/insettiFly.mp3");
		this->setTouchable(false);
		//CCLOG("flyOut");
		this->bringToFront();
		this->play("open", ([=]() {
			this->play("fly", nullptr, true);

			int stopPosX = (cos(angleOut / 180.0f * M_PI) * 2000) + localPosition.x;
			int stopPosY = (sin(angleOut / 180.0f * M_PI) * 2000) + localPosition.y;

			scaleMore();

			RotateTo *bugRotateActionAc = RotateTo::create(0.5, -angleOut+90);
			auto bugRotateAction = EaseSineInOut::create(bugRotateActionAc->clone());
			this->play(bugRotateAction);

			MoveTo *bugMoveActionAc = MoveTo::create(3, Vec2(stopPosX, stopPosY));
			auto bugMoveAction = EaseSineIn::create(bugMoveActionAc->clone());
			this->play(bugMoveAction);

			CallFunc *runCallback_destroy = CallFunc::create(CC_CALLBACK_0(Bug::destroy, this));
			getNode().runAction(Sequence::create(DelayTime::create(3), runCallback_destroy, nullptr));

			this->getActionTimeline()->clearLastFrameCallFunc();
		}), false);
	}
}


bool Bug::onTouchBegan(Touch* touch, Event* event) {

	//CCLOG("BoxButton - onTouchBegan");
	
	if (TouchableGameObject::onTouchBegan(touch, event)) {
		if (!clicked){
			//CCLOG("TOUCH");

			EventCustom event("click_bug");
			event.setUserData(this);
			eventDispatcher->dispatchEvent(&event);
		}
	}

	return false;

}

void Bug::destroy(){
	EventCustom event("delete_bug");
	event.setUserData(this);
	eventDispatcher->dispatchEvent(&event);
	//delete this;
}
