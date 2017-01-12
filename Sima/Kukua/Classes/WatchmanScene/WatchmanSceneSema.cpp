#include "WatchmanSceneSema.h"
#include "WatchmanScene.h"

const float WatchmanSceneSema::MAX_Y = 600.f;

WatchmanSceneSema::WatchmanSceneSema(Node& parentNode, string nodeName, string csbPath, string dragSpritePath, string colliderSpritePath, EventDispatcher* eventDispatcher)
: DraggableGameObject(parentNode, nodeName, csbPath, dragSpritePath, eventDispatcher),
touchOffset(Vec2::ZERO), colliderSpritePath(colliderSpritePath)
{

	touchValid = false;
    isOnPortal = false;
    lastX = 0;
    
    semaFront = new GameObject(*(this->getChild("RootBone")), Vec2::ZERO, WatchmanScene::PATH + "CSD/Sema_front.csb");
    semaSide = new GameObject(*(this->getChild("RootBone")), Vec2::ZERO, WatchmanScene::PATH + "CSD/Sema_side.csb");
    
    semaFront->setVisible(false);
    semaSide->setVisible(false);
    
    semaFront->play("Standing_Base", nullptr, true);
    semaSide->play("sema_34_walk", nullptr, true);
    
    isMovingToPortal = false;

}

WatchmanSceneSema::~WatchmanSceneSema() {
    delete semaFront;
    delete semaSide;
}

bool WatchmanSceneSema::onTouchBegan(Touch* touch, Event* event) {

	if (TouchableGameObject::onTouchBegan(touch, event)) {

		touchValid = true;
		touchOffset = node->getParent()->convertToNodeSpace(touch->getLocation() - getLocalPosition());
        
        if (isOnPortal) {
            semaFront->play("Sema_Float_out", [=]() {
                semaFront->play("Standing_Base", nullptr, true);
                semaSide->setVisible(true);
                semaFront->setVisible(false);
                semaFront->getActionTimeline()->clearLastFrameCallFunc();
            });
            
            
        } else {
            semaFront->setVisible(false);
            semaSide->setVisible(true);
        }
        
		return true;

	}

	return false;

}

void WatchmanSceneSema::onTouchMoved(Touch* touch, Event* event) {

	Vec2 touchLocalPosition = node->getParent()->convertToNodeSpace(touch->getLocation());
	Vec2 touchWorldPosition = node->convertToWorldSpace(touchLocalPosition);
	//CCLOG("touchLocalPosition x %f, y %f", touchLocalPosition.x, touchLocalPosition.y);
	//CCLOG("touchWorldPosition x %f, y %f", touchWorldPosition.x, touchWorldPosition.y);
   
	if (touchValid && touchWorldPosition.y - touchOffset.y < MAX_Y) {
		node->setPosition(touchLocalPosition - touchOffset);
        
        
        if (lastX < touchLocalPosition.x ) {
            semaSide->getNode().setScaleX(1);
        } else {
            semaSide->getNode().setScaleX(-1);
        }
        lastX = touchLocalPosition.x;
       
        
        
	} else if (touchValid && touchWorldPosition.y < MAX_Y + colliderSprite->getBoundingBox().size.height) {
		node->setPosition(Vec2((touchLocalPosition - touchOffset).x, getLocalPosition().y));
        
        
        if (lastX < touchLocalPosition.x ) {
            semaSide->getNode().setScaleX(1);
        } else {
            semaSide->getNode().setScaleX(-1);
        }
        lastX = touchLocalPosition.x;
               
        
        
	} else {
		touchValid = false;
	}

}

void WatchmanSceneSema::onTouchEnded(Touch* touch, Event* event) {

	touchValid = true;
    semaFront->getActionTimeline()->clearLastFrameCallFunc();
    semaSide->setVisible(false);
    
    semaFront->setVisible(true);
    
    if (isOnPortal) {
        
        semaFront->play("trans_floating", [=]() {
            semaFront->play("sema_Float", nullptr, true);
            semaFront->getActionTimeline()->clearLastFrameCallFunc();
        });
    }
    
}

Rect WatchmanSceneSema::getBoundingBox() {
    
    const Sprite* semaColliderSprite = static_cast<Sprite*>(getChild(colliderSpritePath));  //  getColliderSprite();
    
    return Rect(
                         semaColliderSprite->getParent()->convertToWorldSpace(semaColliderSprite->getPosition()).x - semaColliderSprite->getBoundingBox().size.width / 2,
                         semaColliderSprite->getParent()->convertToWorldSpace(semaColliderSprite->getPosition()).y - semaColliderSprite->getBoundingBox().size.height / 2,
                         semaColliderSprite->getBoundingBox().size.width,
                         semaColliderSprite->getBoundingBox().size.height
                         );
    
}


void WatchmanSceneSema::setLastPortalWasOn(Portal *portal) {
    portalWasOn = portal;
}
Portal* WatchmanSceneSema::getLastPortalWasOn() {
    return portalWasOn;
}

void WatchmanSceneSema::moveToPortal(Portal *portal) {
    
    if (portal->isVisible() == false) return;
    
    isMovingToPortal = true;    
    
    float xNow = getNode().getPosition().x;
    float xFinal = getNode().getParent()->convertToNodeSpace(portal->getPosition()).x;
    
    if (xNow < xFinal ) {
        semaSide->getNode().setScaleX(1);
    } else {
        semaSide->getNode().setScaleX(-1);
    }
    
    
    getNode().stopAllActions();
   
    semaFront->setVisible(false);
    semaSide->setVisible(true);
    
    CCLOG("--------moveToPortal");
    
    ///
    play(
         Sequence::createWithTwoActions(
                                        MoveTo::create(0.7f, getNode().getParent()->convertToNodeSpace(portal->getPosition())),
                                        CallFunc::create(
                                                         [=]() {
                                                             isOnPortal = true;
                                                             setLastPortalWasOn(portal);
                                                             semaSide->setVisible(false);
                                                             semaFront->setVisible(true);
                                                             isMovingToPortal = false;
                                                             portal->open();
                                                             
                                                             semaFront->play("trans_floating", [=]() {
                                                                 semaFront->play("sema_Float", nullptr, true);
                                                                 semaFront->getActionTimeline()->clearLastFrameCallFunc();
                                                             });
                                                             
                                                         }
                                                         )
                                        )
         );
    
    ///
    
    
    
}

void WatchmanSceneSema::jumpIntoPortal() {
    
    auto scaleDown = ScaleTo::create(0.8, 0.01);
    semaFront->play(scaleDown);
    semaFront->play("salto_portale", [=]() {
        semaFront->setVisible(false);
        semaFront->getActionTimeline()->clearLastFrameCallFunc();
    });
    
}

void WatchmanSceneSema::walkIn() {
   
    getNode().runAction(
                Sequence::create(
                        DelayTime::create(1.0),
                        CallFunc::create([=]() {
                                 semaSide->setVisible(true);
                        }),
                        MoveTo::create(0.9f, Vec2(220,280) ),
                        CallFunc::create([=]() {
                                 semaSide->setVisible(false);
                                 semaFront->setVisible(true);
                        }),
                        nullptr
                  )
    );

}

