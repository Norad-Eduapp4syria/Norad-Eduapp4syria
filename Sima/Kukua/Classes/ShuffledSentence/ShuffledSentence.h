#ifndef __GAME_PLAY_H__
#define __GAME_PLAY_H__

//#include "GameController.h"
#include "cocos2d.h"
//#include "extensions/cocos-ext.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

//using namespace cocos2d::extension;
class ShuffledSentence : public cocos2d::Layer {
public:
	static cocos2d::Scene* createScene();
    static const std::string PATH;
	ShuffledSentence();
	~ShuffledSentence(void);
	virtual void onEnter();
	virtual void onExit();
	static ShuffledSentence* getInstance() { return gamePlayObject; }
	void createAllListener();
	void setGameState(int state);

	//void menuCloseCallback(Ref *pSender);
	//void pauseBtnCallback(Ref *pSender);

	// For Multi Touch
	/*void onTouchesBegan(const std::vector<Touch *> &touches, Event *event);
	void onTouchesMoved(const std::vector<Touch *> &touches, Event *event);
	void onTouchesEnded(const std::vector<Touch *> &touches, Event *event);
	void onTouchesCancelled(const std::vector<Touch *> &touches, Event *event);*/
	// For single Touch
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchCancelled(cocos2d::Touch *touch, Event *event);


	void createLayerOf(int index);
	void updateGame(float dt);
	void initGame();
	void createWords();
	void rhinoCome();
	void changeZorder(Ref *pSender);
	void createParticale();
	void callWellDoneAnimation();
	void callOutAnimation();
	void stopAction(Ref *pSender);
	void showHint();
	void boxGoLeft();

	static const int STATE_START		= 0;
	static const int STATE_GAME_RUN		= 1;
	static const int STATE_GAME_PAUSE	= 2;
	static const int STATE_GAME_LOSE	= 3;
	static const int STATE_GAME_WIN		= 4;

private:
	// Instance of this class, mainly using for interrupt handling
	static ShuffledSentence *gamePlayObject;

    void addBackToHomeButton();
    void backToWatchmanWin();
    
	// Screen size object
	Size frameSize, viewSize;
	float scaleFactor;

    float scorePercent = 100.0f;
    float scoreToSubtract = 10.0f;


	bool onContactBegin(PhysicsContact &contact);
	void onContactSeparate(PhysicsContact &contact);
	EventListenerPhysicsContact *contactListener;

	// current game state
	int gameState, level;

	long pauseStartTime, pressStartTime;
	Layer *tutoLayer, *hudLayer, *pauseLayer, *gameOverLayer, *gameLayer;
	Sprite *hintHand;
	Node *rhino,*spiral,*girl,*bord;
	Label *lblOnBox[30];
	cocos2d::ui::Scale9Sprite *imgBox[30];
	std::vector<std::string>sentence;
	std::vector<Vec2>BoxPos[10];
	std::vector<float>boxRotation[10];
	std::vector<Vec2>dummyBoxPos[10];
	cocos2d::ui::Scale9Sprite *middlePart[30];

	int alocPos[20],moveTag,boxDistroy;
	float tempRotation;
	Vec2 tempPos;
	int totalWords, posIndex;
	int mainScore;

    int getRandom(int lowerLimit, int upperLimit);
    int getRandom(int lowerLimit, int upperLimit, int gap);
    
    CocosDenshion::SimpleAudioEngine* simpleAudioEngine;
    void playAudioCommand();
};

#endif // __GAME_PLAY_H__
