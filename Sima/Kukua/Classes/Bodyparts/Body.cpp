#include "Body.h"
#include "Bodyparts.h"


Body::Body(Node& rootNode, const Vec2& localPosition, string csbPath, string skinName, EventDispatcher* eventDispatcher, Bodyparts& bodyparts)
	: GameObject(rootNode, localPosition, csbPath)
{

    
    CCLOG("Body");

    skin = skinName;
    
    setScale(0.6);
    
    simpleAudioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
  
    addTouchableParts(eventDispatcher);
    
    zoomAnimDuration = 1.0f;
    
}

Body::~Body() {

	CCLOG("~Body");
    for (auto iterator = touchableParts.begin(); iterator != touchableParts.end(); ++iterator) {
        delete *iterator;
    }
    
}


void Body::enableTouchOnParts(string bodyPart) {
    for (auto iterator = touchableParts.begin(); iterator != touchableParts.end(); ++iterator) {
        string touchName = (*iterator)->getName();
        if ( bodyPart == touchName) (*iterator)->enableTouch();
        else if ( ( bodyPart == "eye") && ( (touchName=="eye1") || (touchName=="eye2") ) ) (*iterator)->enableTouch();
        else if ( ( bodyPart == "arm") && ( (touchName=="arm1") || (touchName=="arm2") ) ) (*iterator)->enableTouch();
        else if ( ( bodyPart == "hand") && ( (touchName=="hand1") || (touchName=="hand2") ) ) (*iterator)->enableTouch();
        else if ( ( bodyPart == "finger") && ( (touchName=="finger1") || (touchName=="finger2") ) ) (*iterator)->enableTouch();
        else if ( ( bodyPart == "elbow") && ( (touchName=="elbow1") || (touchName=="elbow2") ) ) (*iterator)->enableTouch();
        else if ( ( bodyPart == "ear") && ( (touchName=="ear1") || (touchName=="ear2") ) ) (*iterator)->enableTouch();
        else if ( ( bodyPart == "leg") && ( (touchName=="leg1") || (touchName=="leg2") ) ) (*iterator)->enableTouch();
        else if ( ( bodyPart == "foot") && ( (touchName=="foot1") || (touchName=="foot2") ) ) (*iterator)->enableTouch();
        else if ( ( bodyPart == "knee") && ( (touchName=="knee1") || (touchName=="knee2") ) ) (*iterator)->enableTouch();
        else if ( ( bodyPart == "hair") && ( (touchName=="hair1") || (touchName=="hair2") || (touchName=="hair3") ) ) (*iterator)->enableTouch();
    }
    wrongHit->enableTouch();
}
void Body::disableTouchOnParts() {
    for (auto iterator = touchableParts.begin(); iterator != touchableParts.end(); ++iterator) {
        (*iterator)->disableTouch();
    }
}

void Body::zoomIn(string bodyPart) {
  // return; // togliere
    string zoomType = "noZoom";
    
    if ( (bodyPart == "nose") || (bodyPart == "head") || (bodyPart == "chin") || (bodyPart == "mouth") || (bodyPart == "tongue") ||
         (bodyPart == "ear")  || (bodyPart == "hair") || (bodyPart == "eye") ) {
    
          zoomType = "topZoom";
    }
    else if ( (bodyPart == "arm") || (bodyPart == "hand") || (bodyPart == "finger") || (bodyPart == "elbow") || (bodyPart == "neck") || (bodyPart == "shoulder") ) {
        
        zoomType = "centerZoom";
    }
    else if ( (bodyPart == "foot") || (bodyPart == "leg") || (bodyPart == "knee") ) {
        
        zoomType = "bottomZoom";
    }
    
    
    
    
    
    float yMove = 0;
    
 
    if ( zoomType == "topZoom") {
        
        if (skin=="sema") yMove = -500;
        else  yMove = -350;
        
    } else if ( zoomType == "centerZoom") {
         yMove = 10;
    } else if ( zoomType == "bottomZoom") {
         yMove = 530;
    }

    ScaleTo* scaleAction = ScaleTo::create(zoomAnimDuration, 1.5);
   // MoveBy* moveAction = MoveBy::create(zoomAnimDuration, Vec2(0, yMove));
    MoveTo* moveAction = MoveTo::create(zoomAnimDuration, Vec2( 309, node->getPositionY() + yMove));
    
    node->runAction(scaleAction);
    node->runAction(moveAction);
}

void Body::zoomOut() {
    
    ScaleTo* scale = ScaleTo::create(zoomAnimDuration, 0.6);
    node->runAction(scale);
    
    //MoveBy* move = MoveBy::create(zoomAnimDuration, Vec2(0, 500));
    MoveTo* move = MoveTo::create(zoomAnimDuration, Vec2(309, 380));
    node->runAction(move);
    
}


void Body::addTouchableParts(EventDispatcher* eventDispatcher) {
    
    Node *placeholderNode = node->getChildByName("body_master")->getChildByName("head_master")->getChildByName("placeholders");

    wrongHit = new TouchablePart(*node, node->getChildByName("body_master")->getChildByName("head_master")->getChildByName("wrong")->getChildByName("wrong")->getPosition(), "Bodyparts/csd/hitArea.csb", "hitSprite", "wrong", eventDispatcher);
    touchableParts.push_back(wrongHit);
    
    addTouchablePart("nose", placeholderNode, eventDispatcher);
    addTouchablePart("mouth", placeholderNode, eventDispatcher);
    addTouchablePart("head", placeholderNode, eventDispatcher);
    addTouchablePart("chin", placeholderNode, eventDispatcher);
    addTouchablePart("eye1", placeholderNode, eventDispatcher);
    addTouchablePart("eye2", placeholderNode, eventDispatcher);
    addTouchablePart("arm1", placeholderNode, eventDispatcher);
    addTouchablePart("arm2", placeholderNode, eventDispatcher);
    addTouchablePart("hand1", placeholderNode, eventDispatcher);
    addTouchablePart("hand2", placeholderNode, eventDispatcher);
    addTouchablePart("finger1", placeholderNode, eventDispatcher);
    addTouchablePart("finger2", placeholderNode, eventDispatcher);
    addTouchablePart("elbow1", placeholderNode, eventDispatcher);
    addTouchablePart("elbow2", placeholderNode, eventDispatcher);
    addTouchablePart("neck", placeholderNode, eventDispatcher);
    addTouchablePart("tongue", placeholderNode, eventDispatcher);
    addTouchablePart("ear1", placeholderNode, eventDispatcher);
    addTouchablePart("ear2", placeholderNode, eventDispatcher);
    addTouchablePart("shoulder", placeholderNode, eventDispatcher);
    addTouchablePart("leg1", placeholderNode, eventDispatcher);
    addTouchablePart("leg2", placeholderNode, eventDispatcher);
    addTouchablePart("foot2", placeholderNode, eventDispatcher);
    addTouchablePart("foot1", placeholderNode, eventDispatcher);
    addTouchablePart("knee2", placeholderNode, eventDispatcher);
    addTouchablePart("knee1", placeholderNode, eventDispatcher);
    addTouchablePart("hair1", placeholderNode, eventDispatcher);
    addTouchablePart("hair2", placeholderNode, eventDispatcher);
    addTouchablePart("hair3", placeholderNode, eventDispatcher);
}


void Body::addTouchablePart(string name, Node *placeholderNode, EventDispatcher* eventDispatcher) {
    auto hit = new TouchablePart(*node, placeholderNode->getChildByName(name)->getPosition(), "Bodyparts/csd/hitArea.csb", "hitSprite", name, eventDispatcher);
    touchableParts.push_back(hit);
}
