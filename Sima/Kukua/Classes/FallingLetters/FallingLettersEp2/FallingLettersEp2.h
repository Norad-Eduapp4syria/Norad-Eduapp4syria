#pragma once

#include "../../Utils/Game.h"
#include "../../Utils/DraggableGameObject.h"
#include "Sema.h"
#include "MultiplicationBaloon.h"
#include "../../Utils/GameObject.h"
class Fruit;

#include <map>

class FallingLettersEp2 : public kukua::Game<FallingLettersEp2> {

public:
	// Public variables
	static const int FRUIT_COUNT = 5;
	static const int FRUITS_BASE_TAG;

	// implement the "static create()" method manually
	CREATE_FUNC(FallingLettersEp2);

	virtual ~FallingLettersEp2();

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
	void checkFruitNumber(int number);

	int getMultiplier() const;
	map<int, Fruit*>& getFruits();

private:
	// Private variables
	static const int MAX_LIFES = 5;
	int multiplier;
	int lifes;
    int phonemesToCollect;
	GameObject* help;
	GameObject* helpHand;
	Sema* sema;
	GameObject* semaTryagain;
	MultiplicationBaloon* multiplicationBaloon;
	GameObject* signboardPositive;
	GameObject* signboardNegative;
	GameObject* spiral;
	map<int, Fruit*> fruits;
	GameObject* lifesGameObjects[MAX_LIFES];
	Action* sendFruits;
	bool onContactBegin(PhysicsContact& contact);

};


inline int FallingLettersEp2::getMultiplier() const {

	return multiplier;

}

inline map<int, Fruit*>& FallingLettersEp2::getFruits() {

	return fruits;

}
