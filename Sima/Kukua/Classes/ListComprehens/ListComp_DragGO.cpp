#include "ListComp_DragGO.h"
#include "ListComp_RoundManager.h"
#include "base/ccMacros.h"

//int ListComp_RoundManager::draggedObjID;

ListComp_DragGO::ListComp_DragGO(Node& parentNode, string nodeName, string csbPath, string colliderSpritePath, EventDispatcher* eventDispatcher)
	: DraggableGameObject(parentNode, nodeName, csbPath, colliderSpritePath, eventDispatcher)
{
	getStartLocalPos() = node->getPosition();

	assert(colliderSprite != nullptr);

	this->eventDispatcher = eventDispatcher;
	
	touchListener = nullptr;

	static_cast<Sprite*>(
		getChild("bone_spiral/bone spiral"))->
		setOpacity(0);

	//disappearCallback = bind(&ListComp_DragGO::Disappear, this);
}

void ListComp_DragGO::setSwallow(bool value)
{
	touchListener->setSwallowTouches(true);
}

void ListComp_DragGO::setTouchBeganCallBack(std::function<void()> _touchBeganCallback)
{
	touchBeganCallback = _touchBeganCallback;
}

void ListComp_DragGO::setSuccessCallBack(std::function<void()> _successCallback)
{
	successCallback = _successCallback;
}

void ListComp_DragGO::setFailCallBack(std::function<void()> _failCallback)
{
	failCallback = _failCallback;
}

void ListComp_DragGO::SetOpacity(GLubyte opacity)
{
	colliderSprite->setOpacity(opacity);
}

//touchListener->onTouchEnded = CC_CALLBACK_2(TouchableGameObject::onTouchEnded, this);

/*
ListComp_DragGO::ListComp_DragGO(Node& parentNode, const Vec2& localPosition, string csbPath, string colliderSpritePath, EventDispatcher* eventDispatcher)
	: DraggableGameObject(parentNode, localPosition, csbPath, colliderSpritePath, eventDispatcher)
{
	getStartLocalPos() = node->getPosition();
	
	assert(colliderSprite != nullptr);
	
	this->eventDispatcher = eventDispatcher;
	
	touchListener = nullptr;
}*/


ListComp_DragGO::~ListComp_DragGO() {

}

bool ListComp_DragGO::touchBegan(Touch* touch, Event* event) {
	
	CCLOG("DraggableGameObject - touchBegan");
	return (intersectsPoint(*touch) && onTouchBegan(touch, event));

}

void ListComp_DragGO::touchMoved(Touch* touch, Event* event) {
	
	CCLOG("DraggableGameObject - touchMoved");

	return onTouchMoved(touch, event);

}

void ListComp_DragGO::touchEnded(Touch* touch, Event* event) {

	CCLOG("DraggableGameObject - touchEnded");
	
	return onTouchEnded(touch, event);

}

bool ListComp_DragGO::onTouchBegan(Touch* touch, Event* event) {
	
	if (DraggableGameObject::onTouchBegan(touch, event))
	{
		if (!isActive || !ListComp_RoundManager::roundActive)
			return false;

		/*if (ListComp_RoundManager::draggedObjID == -99 ||
			ListComp_RoundManager::draggedObjID == index)
			ListComp_RoundManager::draggedObjID = index;
			else
			return false;*/

		CCLOG("DraggableGameObject - onTouchBegan");

		// inform main scene
		touchBeganCallback();

		bringToFront();
		play("press");

		return (intersectsPoint(*touch));
	}
	return false;
}

void ListComp_DragGO::jumpBack()
{
	// end callback iteration
	clearLastFrameCallFunc();
    
    Vec2 pos =  getParent()->convertToNodeSpace( originalPos );
    
	auto moveTo = MoveTo::create(0.25f, pos);
    getNode().runAction(moveTo);
}

void ListComp_DragGO::disappear()
{
	play("pop_out", [=](){
		SetOpacity(0);
		clearLastFrameCallFunc();
	});

	// end callback iteration
	clearLastFrameCallFunc();
}

void ListComp_DragGO::onTouchEnded(Touch* touch, Event* event) {

	if (!isActive) return;

	ListComp_RoundManager::draggedObjID = -99;

	play("release");

	int result = ListComp_RoundManager::checkIntersection(colliderSprite, index, color);
	
	//
	switch (result)
	{
	    case  ListComp_RoundManager::SUCCESS:

			play("feedback_positive");

			isActive = false;
			
			ListComp_RoundManager::roundActive = false;

			// returns successful to main
			successCallback();

			break;
	
		case  ListComp_RoundManager::FAIL_BACK:

			play("feedback_negative", bind(&ListComp_DragGO::jumpBack, this), false);

			// call fail main callback
			failCallback();

			break;

		case  ListComp_RoundManager::FAIL_FADE:
			
			isActive = false;

			play("feedback_negative", bind(&ListComp_DragGO::disappear, this), false);

			// call fail main callback
			failCallback();
			
			break;
	}
	

	CCLOG("DraggableGameObject - onTouchEnded");

}
