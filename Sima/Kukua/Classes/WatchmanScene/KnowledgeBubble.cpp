#include "KnowledgeBubble.h"
#include "WatchmanScene.h"


KnowledgeBubble::KnowledgeBubble(Node& parentNode, string nodeName, EventDispatcher* eventDispatcher, string csbPath, DBKnowledgeBubble dbKnowledgeBubble)
	: TouchableGameObject(parentNode, nodeName, csbPath, "Sprite", eventDispatcher),
	dbKnowledgeBubble(dbKnowledgeBubble)
{

    
    string phoneme = dbKnowledgeBubble.getPhoneme();
    
    if ( DataProvider::getInstance()->getCurrentEpisode() == 2 ) {
        phoneme = phoneme.substr(0, phoneme.find("_"));
    }
    
    
    label = new LabelGameObject(*(getChild("Master_ball/ball_piena/text")),  Vec2::ZERO, "common/fonts/Arabic-Regular.ttf", 80, phoneme, Color3B(24,95,166), true);
    label2 = new LabelGameObject(*(getChild("Master_ball/ball_active/text")), Vec2::ZERO, "common/fonts/Arabic-Regular.ttf", 80, phoneme, Color3B(24,95,166), true);

}

KnowledgeBubble::KnowledgeBubble(Node& parentNode, string nodeName, Vec2 pos, EventDispatcher* eventDispatcher, string csbPath, DBKnowledgeBubble dbKnowledgeBubble)
	: TouchableGameObject(parentNode, pos, csbPath, "Sprite", eventDispatcher),
	dbKnowledgeBubble(dbKnowledgeBubble)
{
    
    string phoneme = dbKnowledgeBubble.getPhoneme();
    
    if ( DataProvider::getInstance()->getCurrentEpisode() == 2 ) {
        phoneme = phoneme.substr(0, phoneme.find("_"));
    }
    
    
    label = new LabelGameObject(*(getChild("Master_ball/ball_piena/text")),  Vec2::ZERO, "common/fonts/Arabic-Regular.ttf", 80, phoneme, Color3B(24,95,166), true);
    label2 = new LabelGameObject(*(getChild("Master_ball/ball_active/text")), Vec2::ZERO, "common/fonts/Arabic-Regular.ttf", 80, phoneme, Color3B(24,95,166), true);
}

KnowledgeBubble::~KnowledgeBubble() {
	// CCLOG("~KnowledgeBubble()");
	delete label;
    delete label2;
}

void KnowledgeBubble::setText(string txt)
{
    label->setText(txt);
    label2->setText(txt);
}

void KnowledgeBubble::setNotCompletedImage(string spritePath)
{
    static_cast<Sprite*>(getChild("Master_ball/ball_vuota/ball_vuota"))->setTexture(spritePath);
}
void KnowledgeBubble::setCompletedImage(string spritePath)
{
    static_cast<Sprite*>(getChild("Master_ball/ball_piena/ball_piena"))->setTexture(spritePath);
}
void KnowledgeBubble::setActiveImage(string spritePath)
{
    static_cast<Sprite*>(getChild("Master_ball/ball_active/ball_active"))->setTexture(spritePath);
}