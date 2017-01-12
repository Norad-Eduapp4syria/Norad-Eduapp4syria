#ifndef __TUBGAME_H__
#define __TUBGAME_H__

#include "cocos2d.h"
#include <SimpleAudioEngine.h>
#include "cocostudio/CocoStudio.h"
#include "../Utils/Data/DataProvider.h"
#include "ui/CocosGUI.h"

class TubGame : public cocos2d::Layer
{
public:

    static std::string NAME;
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    
    //void touchEvent(Ref *pSender, TouchEventType type);
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    
private:
    
	CocosDenshion::SimpleAudioEngine* audio;
	cocos2d::Label *n4;
	Node* rootNode;

	int countBallExit = 0;

	bool clicked;

	int highestOrLowest = 0;
	int number1 = 0;
	int number2 = 0;

        float scorePercent = 100.0f;
        float scoreToSubtract = 20.0f;
	
	cocos2d::MoveBy* ball1MoveAction;
	cocos2d::MoveBy* ball2MoveAction;

	cocostudio::timeline::ActionTimeline*  tubTimeline;
	
	cocostudio::timeline::ActionTimeline* ball1Timeline;
	cocostudio::timeline::ActionTimeline* ball2Timeline;

    cocos2d::ui::Button *button1;
    cocos2d::ui::Button *button2;
    
	void addDefaultObj();
	void addTub();
	void addBall1();
	void addBall2();
	void playAnimationUp();
    void removeClickButton();
    void preloadAudio();
    void showHelp();
    

	
	void ball1InStanding();
	void ball2InStanding();

	void buttonPressed1();
	void buttonPressed2();

	void ballExit();
	void endGame();


	void clickResult(bool _right);
	void resulAnimOK();
	void resulAnimKO();
	
	void restartGame();

	void addBackToHomeButton();
	
    void playAudioPhoneme();

    int matchCounter;
    int correctAnswerCounter;
    
    Node* ball1;
    Node* ball2;
    
    cocos2d::Label *label1;
    cocos2d::Label *label2;
    
    void setValuesInBubbbles();
    
    DataProvider* dataProvider;
    
    // implement the "static create()" method manually
    CREATE_FUNC(TubGame);
};

#endif // __BLENDERGAME_H__
