#pragma once

#include "../Utils/DraggableGameObject.h"

class PhotoCharacter : public DraggableGameObject {

public:
	PhotoCharacter(Node& parentNode, string nodeName, string csbPath, string dragSpritePath,  string colliderSpritePath, EventDispatcher* eventDispatcher);
	virtual ~PhotoCharacter();
    void activate();
    void deactivate();
    
protected:
	Vec2 touchOffset;
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);

private:
	PhotoCharacter();												// Unimplemented
	PhotoCharacter(const PhotoCharacter& other);					// Unimplemented
	PhotoCharacter& operator=(const PhotoCharacter& other);		// Unimplemented
    
    string colliderSpritePath;
};