#pragma once


//#include "../Utils/GameObject.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class WordReading : public cocos2d::Layer {
    
public:
    
    static const std::string PATH;								// Resources' subfolder path for this game
    
    static std::string NAME;
    
    static cocos2d::Scene* createScene();
    virtual ~WordReading();
    virtual bool init();
    void update(float) override;
    // a selector callback
    void Rec(cocos2d::Ref* pSender);
    void PlaySample(int which);
    void CreateFromData(const char* data, unsigned dataSize);
    void PlayRecordedBuffer(cocos2d::Ref* pSender);
    bool CreateFromFile(int which);
    void PlayAudioSample(int which);
    //void Set_Asset_Manager(AAssetManager* manager);

    //labels
    cocos2d::Label *recorderLabel;
    cocos2d::Label *audioRecPlayerStateLabel;
    
	// locks controls while composing word
	bool isComposing;

    bool newRecording = true;
    int oldWhich;

	std::vector<std::string> word;

	// 9 is max length of the word
	std::vector<std::vector<std::string>> words;
    std::vector<std::vector<std::string>> wordsEnglish;
	std::vector<int> chosenWords;

	int roundNumber;
    
protected:
    
    Node* rootNode;
    CocosDenshion::SimpleAudioEngine* simpleAudioEngine;
    
private:
    void addLetters();
    void addBoard();
    void composeScene();
    void startGame();
    void startGame2();
    void addHomeButton();
    void initForRecord();
    void playSpiralAnimationAfterDelay(float delay);
    void playWellDoneAndEndGame();
    void playCharacterFeedbackAfterDelay(float delay);
    bool recPressed;
    bool stopClick;
	void spelling();
	void setNewRound();
    void endGame();
	void setTouchLetters(bool touchable);
    std::vector<std::string> split(const std::string &s, char delim);
    
    std::string wordToRead;
    std::string wordToReadEnglish;
	float recMeterTime = 0.65f;  // 5 / 3secs
	int maxLetters = 9;

    cocos2d::Label* boardLabel;
    
    void playAudioReference();
    
    // implement the "static create()" method manually
    CREATE_FUNC(WordReading);
};


