#pragma once

#include "../Utils/DraggableGameObject.h"

class ListComp_DragGO : public DraggableGameObject {

public:
	
	ListComp_DragGO(Node& parentNode, string nodeName, string csbPath, string colliderSpritePath, EventDispatcher* eventDispatcher);
	ListComp_DragGO(Node& parentNode, const Vec2& localPosition, string csbPath, string colliderSpritePath, EventDispatcher* eventDispatcher);
	
	virtual ~ListComp_DragGO();

	virtual void setSwallow(bool value);

	void setTouchBeganCallBack(std::function<void()> _touchBeganCallback);
	void setSuccessCallBack(std::function<void()> _successCallback);
	void setFailCallBack(std::function<void()> _failCallback);
	void SetOpacity(GLubyte opacity);
	
	std::function<void()> touchBeganCallback;
	std::function<void()> successCallback;
	std::function<void()> failCallback;
	//std::function<void()> disappearCallback;

	bool isActive = true;

	int name, color, index;

	Vec2					originalPos;

	Vec2					getStartLocalPos()					{ return startLocalPosition; }


protected:
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);

	virtual bool touchBegan(Touch* touch, Event* event);
	virtual void touchMoved(Touch* touch, Event* event);
	virtual void touchEnded(Touch* touch, Event* event);
	
	virtual void jumpBack();
	virtual void disappear();
};
