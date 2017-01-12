#pragma once

#include "../Utils/DraggableGameObject.h"

class EmoCustomDragGameObject : public DraggableGameObject {

public:
	
	EmoCustomDragGameObject(Node& parentNode, string nodeName, string csbPath, string colliderSpritePath, EventDispatcher* eventDispatcher);
	EmoCustomDragGameObject(Node& parentNode, const Vec2& localPosition, string csbPath, string colliderSpritePath, EventDispatcher* eventDispatcher);
	
	virtual ~EmoCustomDragGameObject();

	virtual void setSwallow(bool value);

	virtual void jumpBack();

	void setTouchEndCallBack(std::function<void(Sprite *, int)> _touchEndCallback);
	void SetOpacity(GLubyte opacity);
	
	std::function<void(Sprite*, int)> touchEndCallback;
	//std::function<void()> disappearCallback;

	bool isActive = true;

	int name, color, index;

	Vec2					originalPos;

	Vec2					getStartLocalPos()					{ return startLocalPosition; }

	Vec2					tapisPosition;


protected:
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);

	virtual bool touchBegan(Touch* touch, Event* event);
	virtual void touchMoved(Touch* touch, Event* event);
	virtual void touchEnded(Touch* touch, Event* event);
	
	virtual void disappear();
};
