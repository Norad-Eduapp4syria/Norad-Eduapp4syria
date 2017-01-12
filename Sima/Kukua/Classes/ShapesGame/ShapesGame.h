#pragma once

#include "../Utils/Game.h"
#include "../Utils/GameObject.h"
#include "Gorilla.h"
#include "Biscuit.h"
#include "../Utils/Data/DataProvider.h"

class ShapesGame : public kukua::Game<ShapesGame> {

public:
	// Public variables

	// implement the "static create()" method manually
	CREATE_FUNC(ShapesGame);

	virtual ~ShapesGame();

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
	void endGame(bool gameOver = false);

	Biscuit::Shape getRequestedShape() const;
	vector<Biscuit*>* getBiscuits();
	void resetBiscuits();
    float score;
    string requestedSymbol;
    
private:
	Biscuit::Shape requestedShape;
	GameObject* help;
	GameObject* helpHand;
	GameObject* hill;
	GameObject* palm;
	Gorilla* gorilla;
	vector<Biscuit*> biscuits;
	GameObject* spiral;
	GameObject* semaWellDone;
	GameObject* semaTryAgain;
	vector<GameObject*> backDrops;
	vector<GameObject*> frontDrops;
	vector<GameObject*> hungryIcons;
	int previousEatenBiscuits;
	int lifes;
    DataProvider *dataProvider;
    
    void createBiscuits();
    void createBiscuit(string shape, string refPos);
    int skin;
};

inline Biscuit::Shape ShapesGame::getRequestedShape() const {

	return requestedShape;

}

inline vector<Biscuit*>* ShapesGame::getBiscuits() {

	return &biscuits;

}
