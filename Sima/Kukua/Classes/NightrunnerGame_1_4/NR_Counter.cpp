#include "NR_Counter.h"
#include "../Utils/StringUtility.h"


NR_Counter::NR_Counter(Node& parentNode, string nodeName, EventDispatcher* eventDispatcher)
	: GameObject(parentNode, nodeName, "NightrunnerGame_1_4/csd/Ball.csb")
{

    _eventDispatcher = eventDispatcher;
	CCLOG("NR_Counter()");
    currentPieces = 0;
    play("enter");
 

    startCounter();
}

NR_Counter::~NR_Counter() {
 
    getNode().stopActionByTag(190);
    
}


void NR_Counter::startCounter() {
    
    CallFunc *closeCallback = CallFunc::create(CC_CALLBACK_0(NR_Counter::addPiece, this));
    Action *closeTimeAction = Sequence::create(DelayTime::create(7.5),closeCallback, nullptr);
    closeTimeAction->setTag(190);
    getNode().runAction(closeTimeAction);
    
}

void NR_Counter::addPiece() {
    currentPieces++;
    
    auto base = getChild("Master_counter");
    
    base->getChildByName( StringUtils::toString(currentPieces)  )->setVisible(true);
    
    
    if ( currentPieces == 8) {
        
        EventCustom event("TimeFinishedEvent");
        _eventDispatcher->dispatchEvent(&event);
        
        return;
    }
    
    CallFunc *closeCallback = CallFunc::create(CC_CALLBACK_0(NR_Counter::addPiece, this));
    Action *closeTimeAction = Sequence::create(DelayTime::create(7.5),closeCallback, nullptr);
    closeTimeAction->setTag(190);
    getNode().runAction(closeTimeAction);
    
}

