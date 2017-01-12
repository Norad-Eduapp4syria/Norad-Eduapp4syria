#include "Portal.h"
#include "WatchmanScene.h"
#include "../Utils/StringUtility.h"

Portal::Portal(Node& parentNode, string nodeName, string animationCsbPath, string colliderSpritePath, EventDispatcher* eventDispatcher)
: TouchableGameObject(parentNode, nodeName, animationCsbPath, colliderSpritePath, eventDispatcher)
{
    _linkedGame = nullptr;
    greenPortal = nullptr;
    
    playButton = new PortalPlay(*(this->getChild("RootBone/Node_Play/Node_Play")), eventDispatcher);
    playButton->portalName = nodeName;
    
    simpleAudioEngine = SimpleAudioEngine::getInstance();
    simpleAudioEngine->preloadEffect((WatchmanScene::PATH + "Audio/portal/portal_entrata.mp3").c_str());
    simpleAudioEngine->preloadEffect((WatchmanScene::PATH + "Audio/portal/portal_green.mp3").c_str());
    simpleAudioEngine->preloadEffect((WatchmanScene::PATH + "Audio/portal/portal_open.mp3").c_str());
    simpleAudioEngine->preloadEffect((WatchmanScene::PATH + "Audio/portal/portal_loop.mp3").c_str());
    simpleAudioEngine->preloadEffect((WatchmanScene::PATH + "Audio/portal/portal_play_appare.mp3").c_str());
    
    int numEp = DataProvider::getInstance()->getCurrentEpisode();
    static_cast<Sprite*>( getChild("RootBone/portal_1/portal_1") )->setTexture(WatchmanScene::PATH + "PNG/Portal_color/portal_color_" +  StringUtility::toString(numEp) + ".png");
    static_cast<Sprite*>( getChild("RootBone/portal_4/portal_4") )->setTexture(WatchmanScene::PATH + "PNG/Portal_color/portal_top_color_" +  StringUtility::toString(numEp) + ".png");
    
    setTouchable(true);
    semaIsOnPortal = false;
}

Portal::~Portal() {
    delete playButton;
    if (greenPortal != nullptr) delete greenPortal;
}

void Portal::setLinkedGameIsCompleted(bool justCompleted) {
    
    
    Sprite* greenSpriteTop =  static_cast<Sprite*>(node->getChildByName("RootBone")->getChildByName("portal_top_complete")->getChildByName("portal_top_complete"));
    
    if (justCompleted) {
        getNode().runAction(
                Sequence::createWithTwoActions(
                        DelayTime::create(1.0f),
                        CallFunc::create([=]() {
                                greenPortal = new GameObject(*(this->getChild("RootBone/portal_verde/portal_verde")), Vec2::ZERO, WatchmanScene::PATH + "CSD/portal_complete.csb");
                                Node* greenSprite = greenPortal->getChild("portal_complete/portal_1_verde");
                                greenSprite->setOpacity(0);
                                greenSprite->runAction(FadeIn::create(1.0f));
                                greenSpriteTop->setOpacity(0);
                                greenSpriteTop->runAction(FadeIn::create(1.0f));
                                greenPortal->play("portal_verde_stars");
                                simpleAudioEngine->playEffect((WatchmanScene::PATH + "Audio/portal/portal_green.mp3").c_str());
                                
                        })
                 )
          );
    } else {
        greenPortal = new GameObject(*(this->getChild("RootBone/portal_verde/portal_verde")), Vec2::ZERO, WatchmanScene::PATH + "CSD/portal_complete.csb");
        greenPortal->getActionTimeline()->gotoFrameAndPause(215);
        greenSpriteTop->setOpacity(255);
    }

}

void Portal::hideGreenPortal() {
    if (greenPortal != nullptr) greenPortal->setVisible(false);
    Sprite* greenSpriteTop =  static_cast<Sprite*>(node->getChildByName("RootBone")->getChildByName("portal_top_complete")->getChildByName("portal_top_complete"));
    greenSpriteTop->setOpacity(0);
}

void Portal::open() {
    simpleAudioEngine->playEffect((WatchmanScene::PATH + "Audio/portal/portal_open.mp3").c_str());
    
    loopOpenSoundEffect = simpleAudioEngine->playEffect((WatchmanScene::PATH + "Audio/portal/portal_loop.mp3").c_str(), true);
    playButton->loopOpenSoundEffect = loopOpenSoundEffect;
    
    play("Portal_open", [=]() {
        play("Portal_loop", nullptr, true);
        getActionTimeline()->clearLastFrameCallFunc();
    });
    
    simpleAudioEngine->playEffect((WatchmanScene::PATH + "Audio/portal/portal_play_appare.mp3").c_str());
    playButton->play("Play_open");
    playButton->setTouchable(true);
    semaIsOnPortal = true;
}
void Portal::close() {
    simpleAudioEngine->stopEffect(loopOpenSoundEffect);
    playButton->play("Play_close");
    playButton->setTouchable(false);
    play("Portal_Close", [=]() {
        setTouchable(true);
        play("Portal_loop_icon", nullptr, true);
        actionTimeline->clearLastFrameCallFunc();
    });
    semaIsOnPortal = false;
}

void Portal::moveIn(float delay) {
   
    simpleAudioEngine->playEffect((WatchmanScene::PATH + "Audio/portal/portal_entrata.mp3").c_str()); // andrebbe ritardato di delay
    
    play("Portal_enter", [=]() {
        play("Portal_loop_icon", nullptr, true);
        actionTimeline->clearLastFrameCallFunc();
    }, false, delay);
    
}

void Portal::showInClosedState() {
    getActionTimeline()->gotoFrameAndPause(55);
    play("Portal_loop_icon", nullptr, true);
}

Rect Portal::getBoundingBox() {
    
    const Sprite* portal1ColliderSprite =  static_cast<Sprite*>(getChild("hitSprite")); // getColliderSprite();
    return Rect(
                            portal1ColliderSprite->getParent()->convertToWorldSpace(portal1ColliderSprite->getPosition()).x - portal1ColliderSprite->getBoundingBox().size.width / 2,
                            portal1ColliderSprite->getParent()->convertToWorldSpace(portal1ColliderSprite->getPosition()).y - portal1ColliderSprite->getBoundingBox().size.height / 2,
                            portal1ColliderSprite->getBoundingBox().size.width,
                            portal1ColliderSprite->getBoundingBox().size.height
                            );
    
}

void Portal::setLinkedGame(DBGame *linkedGame) {
    _linkedGame = linkedGame;
    
    std::string imageName = WatchmanScene::PATH+"PNG/Portal_icons/";
    
    
    if ( (DataProvider::getInstance()->getCurrentEpisode()==2) && (linkedGame->getName() == "WritingLetters") ) {
        if (playButton->portalName == "Portal1") imageName.append( "WritingLetters_start" );
        else if (playButton->portalName == "Portal2") imageName.append( "WritingLetters_middle" );
        else if (playButton->portalName == "Portal3") imageName.append( "WritingLetters_end" );
    } else {
        imageName.append( linkedGame->getName() );
    }
    
    
    imageName.append(".png");
    // CCLOG("imageName = %s", imageName.c_str() );
    Sprite* imgSprite = static_cast<Sprite*>( this->getChild("RootBone/Icona_portale/Icona_calcio") );
    imgSprite->setTexture(imageName);
    
}
DBGame* Portal::getLinkedGame() {
    return _linkedGame;
}

bool Portal::onTouchBegan(Touch* touch, Event* event) {
    
    if (TouchableGameObject::onTouchBegan(touch, event)) {
        
        if (isVisible() == false) return false;
        if (semaIsOnPortal) return false;
        setTouchable(false);
        EventCustom event("MoveSemaOnPortalEvent");
        event.setUserData(this);
        eventDispatcher->dispatchEvent(&event);
        
    }
    
    return false;
    
}
