#pragma once

#include "../Utils/GameObject.h"
#include "TouchablePart.h"

class Bodyparts;

#include <map>
#include <vector>


class Body : public GameObject {

public:
	Body(Node& rootNode, const Vec2& localPosition, string csbPath, string skinName, EventDispatcher* eventDispatcher, Bodyparts& comprehensionGame);
	virtual ~Body();
    void zoomIn(string bodyPart);
    void zoomOut();
    void enableTouchOnParts(string bodyPart);
    void disableTouchOnParts();
    float zoomAnimDuration;
    
private:
    void addTouchableParts(EventDispatcher* eventDispatcher);
    void addTouchablePart(string name, Node *placeholderNode, EventDispatcher* eventDispatcher);
	CocosDenshion::SimpleAudioEngine* simpleAudioEngine;
    
    vector<TouchablePart*> touchableParts;
    TouchablePart* wrongHit;
    string skin;
};