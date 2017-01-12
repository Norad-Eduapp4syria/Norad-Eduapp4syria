#pragma once

#include "../Utils/TouchableGameObject.h"
#include "../Utils/LabelGameObject.h"

class Train;


class TouchablePart : public TouchableGameObject {

    
    
    
public:
  
   TouchablePart(Node& parentNode, const Vec2& localPosition, string csbPath, string colliderSpritePath, string partName, EventDispatcher* eventDispatcher);
    
    virtual ~TouchablePart();
  
    string getName();
    void enableTouch();
    void disableTouch();

protected:
	virtual bool onTouchBegan(Touch* touch, Event* event);

private:
      string name;
	TouchablePart(const TouchablePart& otherTouchablePart);					// Unimplemented
	TouchablePart& operator=(const TouchablePart& otherTouchablePart);		// Unimplemented

};

