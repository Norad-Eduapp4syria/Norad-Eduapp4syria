#pragma once

#include "../Utils/Game.h"
#include "../Utils/PhysicsGameObject.h"
#include "LetterBox.h"
class MouthButton;
class BoxButton;
class Cannon;
class Box;
class WoodenBox;
class FeedbackSignboard;


class Blending1Game : public kukua::Game<Blending1Game> {

public:
	// Public variables

	// implement the "static create()" method manually
	CREATE_FUNC(Blending1Game);

	virtual ~Blending1Game();

    static int NUM_WORDS;    

	void initVariables();
	void initAudio();
	void initGameObjects();
	void fadeIn();
	void showTutorial();				// Unused
	void showAimTutorial();
	void showShotTutorial();
	void hideTutorial();				// Unused
	void hideAimTutorial();
	void hideShotTutorial();
	bool onTouchBegan(Touch* touch, Event* event);		// Optional, needed if ExampleGame::ENABLE_TOUCH is set to true
	void onTouchMoved(Touch* touch, Event* event);		// Optional, needed if ExampleGame::ENABLE_TOUCH is set to true
	void onTouchEnded(Touch* touch, Event* event);		// Optional, needed if ExampleGame::ENABLE_TOUCH is set to true
	void endGame(bool gameOver = false);
	const string& getCurrentPhoneme() const;
	vector<Box*> getActiveBoxes() const;
	BoxButton* getCurrentBoxButton() const;
	void initBoxConfigurations();
	void updateBoxes(bool sendNewConfiguration, bool enableCannonTouch);
	void animateCorrectLetter(const Vec2& startWorldPosition);
	void decreaseLifes();
	void animateCurrentBoxButton();
    void homeButtonPressed();
    
    static const string PATH_AUDIO;
        
private:
	static bool SHOWN_AIM_TUTORIAL;
	static bool SHOWN_SHOT_TUTORIAL;
	bool showingAimTutorial;
	bool showingShotTutorial;
	static const int START_LIFES = 3;
	vector<vector<pair<Vec2, Box*>>> boxConfigurations;
	string word;
	vector<string> correctPhonemes;
	vector<string> wrongPhonemes;
	vector<LetterBox::Color> correctPhonemesColors;
	int currentPhonemeIndex;
	int lifes;
	GameObject* help;
	//MouthButton* mouthButton;
	vector<BoxButton*> boxButtons;
	Cannon* cannon;
	GameObject* leftHill;
	PhysicsGameObject* rightHill;
	GameObject* aimHelpHand;
	GameObject* shotHelpHand;
	vector<WoodenBox*> woodenBoxes;
	vector<LetterBox*> yellowLetterBoxes;
	vector<LetterBox*> redLetterBoxes;
	vector<LetterBox*> blueLetterBoxes;
	vector<Box*> activeBoxes;
	vector<GameObject*> lifeGameObjects;
	GameObject* tatuTryAgain;
	FeedbackSignboard* feedbackSignboard;
    
    float scorePercent = 100.0f;
    float scoreToSubtract = 0.0f;
 
    void showIntroHelp();
    void showHelp();
    void composeGame();
    
    void closeGame();
    
    vector<string> split(const string &s, char delim);
    string wordAudioFilename;
    bool justAudio;
};

inline const string& Blending1Game::getCurrentPhoneme() const {

	return correctPhonemes[currentPhonemeIndex];

}

inline vector<Box*> Blending1Game::getActiveBoxes() const {

	return activeBoxes;

}

inline BoxButton* Blending1Game::getCurrentBoxButton() const {

	if (currentPhonemeIndex >= 0 && currentPhonemeIndex < boxButtons.size()) {
		return boxButtons[currentPhonemeIndex];
	} else {
		return nullptr;
	}

}
