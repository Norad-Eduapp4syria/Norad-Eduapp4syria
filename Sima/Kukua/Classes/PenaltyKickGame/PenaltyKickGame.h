#ifndef __PENALTYKICKGAME_SCENE_H__
#define __PENALTYKICKGAME_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"
#include "../Utils/GameObject.h"
#include "../Utils/LabelGameObject.h"

class PenaltyKickGame : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	string PATH;
    
private:

	virtual ~PenaltyKickGame();

    // Methods
    void startGame();
    void showTutorial();
    void handAnimation();
    void hideObjects();
    void setInitialParameters();
    void preloadAudio();
    void launchBall(float xpos, float ypos, float time);
    void launchEnded();
    void resetLaunch();
    bool touchIsOnBall(cocos2d::Touch *touch);
    bool ballIsInCorrectDoor();
    void increaseScore(bool correct);
	bool isBallInDoor(int door);
    void randomizaCorrectDoor();
    void runPositiveFeedback();
    void runNegativeFeedback();
    void addBackToHomeButton();
    void startDetectingSwipe();
    void addPointsCounter();
	void playLetters();
    
	void runPaulPositiveFeedback();
	void runSemaPositiveFeedback();
	void runSemaNegativeFeedback();
	void finish(bool _result);


    void runSpiralAnimation();
    void runVuvuzelaAnimation();

	void kickBall(float angle, float power);
	void stopBall();
	int getKickResult(); //0 = out, 1 = goal-1, 2 = goal-2, 3 = pool-sx, 4 = pool-dx, 5 = crossbar, 
	void resetKickVars();
	void toFront(Node* _child, Node* _parent = nullptr);
	void adjustLevel(int _levelBall);
	void runOutFeedback();
	void setKeeper(int _ball);
	void fadeOutKeeper();
    
    // Properties
	bool moveBall;
	float anglekick;
	float powerLinear;
	float powerVertical;
	float posXLinear;
	float posYLinear;
	float heightBall;
	bool checkGoal;
	int directionY;
	int ballRotationR;
	int netLine;
	bool inGoal;
	bool ballStop;
	bool keeperAnimated;
	int positionKeeper;
	int orientationKeeper;
	int goalOK;

	string phonemeOk;
	string phonemeKo;

	GameObject* goalkeeper1;
	GameObject* goalkeeper2;

    float scorePercent = 100.0f;
    float scoreToSubtract = 20.0f;

    static bool IS_TUTORIAL_SHOWN;
    bool tutorialIsToShow;
    Node* rootNode;
    Node* hand;
    // cocostudio::timeline::ActionTimeline* handTimeline;
    CocosDenshion::SimpleAudioEngine *audioEngine;
    float gameTime;
    bool hasTocalculateTime;
    int goalDone;
    Node* ball;
    bool isDoorLeftTheCorrect;
    cocos2d::Label *letterLeft;
    cocos2d::Label *letterRight;
    bool canSwipe;
    
    ////
    cocos2d::Size visibleSize;
    
  
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);
    
    bool isTouchDown;
    
    float initialTouchPos[2];
    float currentTouchPos[2];
    
    void update(float dt);
    
    float startX;
    float startY;
    
    
    bool moveUpGestureDone;
    
    LabelGameObject* phonemeHelp;
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(PenaltyKickGame);
};

#endif
