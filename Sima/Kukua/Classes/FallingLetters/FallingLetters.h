#pragma once

#include "../Utils/Game.h"
#include "../Utils/DraggableGameObject.h"
#include "FLSema.h"
#include "FLBaloon.h"
#include "../Utils/GameObject.h"
class FLFruit;

#include <map>

class FallingLetters : public kukua::Game<FallingLetters> {

public:
	// Public variables
	static const int FRUIT_COUNT = 5;
	static const int FRUITS_BASE_TAG;

	// implement the "static create()" method manually
	CREATE_FUNC(FallingLetters);

	virtual ~FallingLetters();

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

	void update(float dt);

	void startSendingFruits();
	void stopSendingFruits();
	void checkFruitLetter(string letter);

	string getLetterToGet() const;
	map<int, FLFruit*>& getFruits();

private:
	// Private variables
	static const int MAX_LIFES = 5;
	string letterToGet;
	int lifes;
	GameObject* help;
	GameObject* helpHand;
	LabelGameObject* helpLabel;
	FLSema* sema;
	GameObject* semaTryagain;
	FLBaloon* flBaloon;
	GameObject* signboardPositive;
	GameObject* signboardNegative;
	GameObject* spiral;
	map<int, FLFruit*> fruits;
	GameObject* lifesGameObjects[MAX_LIFES];
	Action* sendFruits;
	bool onContactBegin(PhysicsContact& contact);

    float scorePercent = 100.0f;
    float scoreToSubtract = 5.0f;

    int matchCounter;
    
};

inline string FallingLetters::getLetterToGet() const {

	return letterToGet;

}


inline map<int, FLFruit*>& FallingLetters::getFruits() {

	return fruits;

}
