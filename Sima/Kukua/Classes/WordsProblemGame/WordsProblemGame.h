#pragma once

#include "../Utils/Game.h"
#include "../Utils/GameObject.h"
#include "Bongo.h"


class WordsProblemGame : public kukua::Game<WordsProblemGame> {

public:

	// implement the "static create()" method manually
	CREATE_FUNC(WordsProblemGame);

	virtual ~WordsProblemGame();

	void initVariables();
	void initAudio();
	void initGameObjects();
	void fadeIn();
	void showTutorial();
	void hideTutorial();
    void homeButtonPressed();
	bool onTouchBegan(Touch* touch, Event* event);		// Optional, needed if ExampleGame::ENABLE_TOUCH is set to true
	void onTouchMoved(Touch* touch, Event* event);		// Optional, needed if ExampleGame::ENABLE_TOUCH is set to true
	void onTouchEnded(Touch* touch, Event* event);		// Optional, needed if ExampleGame::ENABLE_TOUCH is set to true
	void endGame();

	void setBongosNumbers();
	void checkBongosNumber(Bongo* bongo);

	int getCorrectSolution() const;

	void playBongosSequence();

private:
	static const int NOTE_COUNT = 5;
	static const int MIN_NUMBER = 0;
	static const int MAX_NUMBER = 10;
	int correctSolution;
	int wrongSolution1;
	int wrongSolution2;
	int noteIndex;
	GameObject* help;
	GameObject* helpPentagram;
	GameObject* palm1;
	GameObject* palm2;
	GameObject* plant1;
	GameObject* plant2;
	GameObject* plant3;
	GameObject* plant4;
	GameObject* plant5;
	GameObject* plant6;
	Bongo* bongo1;
	Bongo* bongo2;
	Bongo* bongo3;
	GameObject* musicBaloon;
	GameObject* notes[NOTE_COUNT];
	GameObject* problemSignboard;
	GameObject* helpHand;
	GameObject* tatu;
	LabelGameObject* tatuNumber;
	vector<Bongo*> bongosSequence;
	vector<string> bongosAudioFiles;
	GameObject* pentagram;
	vector<GameObject*> stars;

};

inline int WordsProblemGame::getCorrectSolution() const {

	return correctSolution;

}