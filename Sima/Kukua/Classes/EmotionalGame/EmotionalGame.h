#ifndef __EMOTIONAL_GAME_H__
#define __EMOTIONAL_GAME_H__

#include "cocos2d.h"
#include "EmoCustomDragGameObject.h"
#include "EmoTextProvider.h"

using namespace std;
using namespace CocosDenshion;

class EmotionalGame : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	virtual void update(float delta);
	
    // implement the "static create()" method manually
    CREATE_FUNC(EmotionalGame);
    
    virtual ~EmotionalGame();

private:
	enum Emotions { CORAGGIO, GIOIA, SODDISFAZIONE, SERENITA, SORPRESA, STIMA, REAZIONE, PIACERE, FUTURO };
	enum Moods { PAURA, TRISTEZZA, DELUSIONE, RABBIA, INDIFFERENZA, DISPREZZO, RASSEGNAZIONE, DISGUSTO, NOSTALGIA };
	string PATH;
	Node* rootNode;
	float emoScrollSpeed = 100.0f;
	int chosenMood;
	void setSemaBadState(int state);
	void setSemaGoodState(int state);
	void setText();
	void showQuestion();
	void endScene();
	//
	bool isRolling = true;
	//
	GameObject *objTable;
	GameObject *objSema;
	//
	GameObject *objBoxQuestion;
	//cocos2d::ui::Text *textQuestion;
    Label* textQuestion;
	//
	GameObject *objAnswer[6];
	cocos2d::ui::Button *btnAnswer[6];
	Label *textAnswer[6];
	//
	EmoCustomDragGameObject *objEmoticon[9];
	cocos2d::ui::Button *audioButton;

	GameObject *objAudioBtn;

	void callback_TouchEnd(Sprite* dragCollider, int emoIndex);
	Rect  getAbsPos(const Sprite *spr, int w, int h);
	bool checkIntersection(Sprite *dragCollider);
    
    void closeGame();
    CocosDenshion::SimpleAudioEngine *audioEngine;
    EmoTextProvider *textProvider;
    bool gameIsClosing;
    void playAudioCommand();
    void playAudioQuestion();
};

#endif // __HELLOWORLD_SCENE_H__
