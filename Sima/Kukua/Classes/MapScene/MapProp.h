#pragma once

#include "../Utils/TouchableGameObject.h"

class MapProp : public TouchableGameObject {

    
    
    
public:
  
   MapProp(Node& parentNode, const Vec2& localPosition, string csbPath, string colliderSpritePath, string partName, EventDispatcher* eventDispatcher);
    
    virtual ~MapProp();
  
    string getName();

protected:
	virtual bool onTouchBegan(Touch* touch, Event* event);

private:
    string name;
	MapProp(const MapProp& otherMapProp);					// Unimplemented
	MapProp& operator=(const MapProp& otherMapProp);		// Unimplemented
    
    void playStanding();
    float getRandomTime();
    Action* standingAction;
    void playAudioTap();
};

