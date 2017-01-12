#include "EmoCustomDragGameObject.h"
#include "base/ccMacros.h"

//int RoundManager::draggedObjID;

EmoCustomDragGameObject::EmoCustomDragGameObject(Node& parentNode, string nodeName, string csbPath, string colliderSpritePath, EventDispatcher* eventDispatcher)
	: DraggableGameObject(parentNode, nodeName, csbPath, colliderSpritePath, eventDispatcher)
{
	getStartLocalPos() = node->getPosition();

	assert(colliderSprite != nullptr);

	this->eventDispatcher = eventDispatcher;
	
	touchListener = nullptr;

	originalPos = getStartLocalPos();

	tapisPosition = getPosition();

	/*static_cast<Sprite*>(
		getChild("bone_spiral/bone spiral"))->
		setOpacity(0);*/

	//disappearCallback = bind(&EmoCustomDragGameObject::Disappear, this);
}

void EmoCustomDragGameObject::setSwallow(bool value)
{
	touchListener->setSwallowTouches(true);
}

void EmoCustomDragGameObject::setTouchEndCallBack(std::function<void(Sprite*, int)> _touchEndCallback)
{
	touchEndCallback = _touchEndCallback;
}

void EmoCustomDragGameObject::SetOpacity(GLubyte opacity)
{
	colliderSprite->setOpacity(opacity);
}

EmoCustomDragGameObject::~EmoCustomDragGameObject() {

}

bool EmoCustomDragGameObject::touchBegan(Touch* touch, Event* event) {
	
	CCLOG("DraggableGameObject - touchBegan");
	return (intersectsPoint(*touch) && onTouchBegan(touch, event));
}

void EmoCustomDragGameObject::touchMoved(Touch* touch, Event* event) {
	
	CCLOG("DraggableGameObject - touchMoved");
	return onTouchMoved(touch, event);
}

void EmoCustomDragGameObject::touchEnded(Touch* touch, Event* event) {

	CCLOG("DraggableGameObject - touchEnded");
	return onTouchEnded(touch, event);
}

bool EmoCustomDragGameObject::onTouchBegan(Touch* touch, Event* event) {
	
	if (DraggableGameObject::onTouchBegan(touch, event))
	{
		isActive = true;
		return (intersectsPoint(*touch));
	}
	return false;
}

void EmoCustomDragGameObject::jumpBack()
{
	// end callback iteration
	//clearLastFrameCallFunc();

	//Vec2 pos = getParent()->convertToNodeSpace(tapisPosition);
	//pos.y += 23;
	//auto moveTo = MoveTo::create(0.5f, pos);

	getNode().runAction(Sequence::create(CallFunc::create(
		[=]() {
		play("take", nullptr, false);
	}),
		DelayTime::create(0.1f),
		CallFunc::create(
			[=]() {
		isActive = false;
	}), nullptr));

	//play("take", [=]() { isActive = false; }, false);
}

void EmoCustomDragGameObject::disappear()
{
	play("pop_out", [=](){
		SetOpacity(0);
		clearLastFrameCallFunc();
	});

	// end callback iteration
	clearLastFrameCallFunc();
}

void EmoCustomDragGameObject::onTouchEnded(Touch* touch, Event* event) 
{
	CCLOG("HEALTH DraggableGameObject - onTouchEnded : %d", index);
	printf("HEALTH Callback - onTouchEnded : %d", index); 

	std:stringstream ss;
	ss << "HEALTH DraggableGameObject - onTouchEnded : ";
	ss << index;

	//MessageBox(ss.str().c_str(), "suca");
	touchEndCallback(colliderSprite, index);
}
