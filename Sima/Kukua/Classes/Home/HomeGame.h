#pragma once

#include "../Utils/Game.h"
#include "HomeSema.h"
#include "HomeTatu.h"
#include "PlayButton.h"
#include "HomeElephant.h"
#include "Giraffe.h"
#include "Gazelle.h"
#include "Hen.h"
#include "../Utils/Data/DataProvider.h"

class HomeGame : public kukua::Game<HomeGame> {

public:
	// Public variables

	// implement the "static create()" method manually
	CREATE_FUNC(HomeGame);

	virtual ~HomeGame();

	void initVariables();
	void initAudio();
	void initGameObjects();
	void fadeIn();
	void showTutorial();
	void hideTutorial();
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void endGame(bool gameOver = false);
    void homeButtonPressed();
    void addSettingsButton();
    void addLogoutButton();
    
private:
	GameObject* logo;
	HomeSema* sema;
	GameObject* hill1;
	GameObject* hill2;
	HomeTatu* tatu;
	PlayButton* playButton;
	Hen* hen1;
	Hen* hen2;
	Hen* hen3;
	GameObject* cloud1;
	GameObject* cloud2;
	GameObject* cloud3;
	GameObject* cloud4;
    int cornerTapCounter;
    DataProvider* dataProvider;
};
