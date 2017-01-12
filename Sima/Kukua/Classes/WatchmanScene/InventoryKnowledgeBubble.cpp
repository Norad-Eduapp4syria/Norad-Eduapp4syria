#include "InventoryKnowledgeBubble.h"
#include "WatchmanScene.h"
#include "../Utils/Data/Logger.h"
#include "../AppMacros.h"

InventoryKnowledgeBubble::InventoryKnowledgeBubble(Node& parentNode, const Vec2& localPosition, EventDispatcher* eventDispatcher, string csbPath, Inventory* inventory, DBKnowledgeBubble dbKnowledgeBubble)
	: TouchableGameObject(parentNode, localPosition, csbPath, "Sprite", eventDispatcher),
	dbKnowledgeBubble(dbKnowledgeBubble)
{
	// CCLOG("InventoryKnowledgeBubble()");

	this->inventory = inventory;

	 label = new LabelGameObject(*(getChild("Master_ball/ball_piena/text")), Vec2::ZERO, "common/fonts/Arabic-Regular.ttf", 80, dbKnowledgeBubble.getPhoneme(), Color3B(24, 95, 166), true);
    label2 = new LabelGameObject(*(getChild("Master_ball/ball_active/text")), Vec2::ZERO, "common/fonts/Arabic-Regular.ttf", 80, dbKnowledgeBubble.getPhoneme(), Color3B(24, 95, 166), true);
	//setScale(0.8f);

}

InventoryKnowledgeBubble::~InventoryKnowledgeBubble() {
	// CCLOG("~InventoryKnowledgeBubble()");
	delete label;
    delete label2;
}

bool InventoryKnowledgeBubble::onTouchBegan(Touch* touch, Event* event) {

	// CCLOG("InventoryKnowledgeBubble - onTouchBegan");

	if (TouchableGameObject::onTouchBegan(touch, event)) {
        
        if ( getDBKnowledgeBubble().isLocked() ) return false;
                
		inventory->disableTouch();
		play("ball_press", [=]() {
            
            
            CCLOG(">>Pressed: %s", getDBKnowledgeBubble().getPhoneme().c_str() );
            
            auto dataProvider = DataProvider::getInstance();
            
            dataProvider->resetGamesCompleted(); // questo non sarebbe da fare se rimango nella stessa lettera
            
            if ( dataProvider->getCurrentEpisode() == 2 ) {
                string ph = getDBKnowledgeBubble().getPhoneme().c_str();
                dbKnowledgeBubble = *new DBKnowledgeBubble(ph.append("_writing"), true);
            }
            
            dataProvider->setCurrentDBWatchman( dataProvider->getDBWatchman( dbKnowledgeBubble ) );
            
            dataProvider->setCurrentDBKnowledgeBubble( &dbKnowledgeBubble );
            
            
            SimpleAudioEngine::getInstance()->stopAllEffects();
            SimpleAudioEngine::getInstance()->stopBackgroundMusic();
            
            SimpleAudioEngine::getInstance()->playEffect((WatchmanScene::PATH + "Audio/board/TapLetterboard.mp3").c_str());
            
            Logger::getInstance()->logEvent("Watchman", Logger::CLOSE, "");
			Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, WatchmanScene::createScene(), TRANSITION_COLOR));
            getActionTimeline()->clearLastFrameCallFunc();
		});
	}

	return false;
}



void InventoryKnowledgeBubble::setText(string txt)
{
    label->setText(txt);
    label2->setText(txt);
}

void InventoryKnowledgeBubble::setNotCompletedImage(string spritePath)
{
    static_cast<Sprite*>(getChild("Master_ball/ball_vuota/ball_vuota"))->setTexture(spritePath);
}
void InventoryKnowledgeBubble::setCompletedImage(string spritePath)
{
    static_cast<Sprite*>(getChild("Master_ball/ball_piena/ball_piena"))->setTexture(spritePath);
}
void InventoryKnowledgeBubble::setActiveImage(string spritePath)
{
    static_cast<Sprite*>(getChild("Master_ball/ball_active/ball_active"))->setTexture(spritePath);
}