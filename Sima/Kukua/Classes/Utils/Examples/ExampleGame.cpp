#include "ExampleGame.h"

template<> const bool kukua::Game<ExampleGame>::USE_PHYSICS = false;										// Enable/disable physics
template<> const bool kukua::Game<ExampleGame>::ENABLE_TOUCH = true;										// Used to disable tutorial on first touch and manage general touch events
template<> string kukua::Game<ExampleGame>::PATH = "ExampleGame/";									// Resources' subfolder path for this game
template<> const string kukua::Game<ExampleGame>::BACKGROUND_MUSIC_FILENAME = "backgroundMusic.wav";		// Background music filename
template<> bool kukua::Game<ExampleGame>::SHOWN_TUTORIAL = false;											// Used for showing tutorial on first execution, set to true only if tutorial is not needed
template<> Scene* kukua::Game<ExampleGame>::scene = nullptr;
template<> const string kukua::Game<ExampleGame>::NAME = "Example";

ExampleGame::~ExampleGame() {

	CCLOG("~ExampleGame");

	// Delete objects created with new

}

void ExampleGame::initVariables() {

	CCLOG("ExampleGame - Init variables");

}

void ExampleGame::initAudio() {

	CCLOG("ExampleGame - Init audio");

	// Preload audio files

}

void ExampleGame::initGameObjects() {

	CCLOG("ExampleGame - Init objects");

	// Instantiate gameObjects

}

void ExampleGame::fadeIn() {

	CCLOG("ExampleGame - Fade in");

	// Start fade in animations

}

void ExampleGame::showTutorial() {

	CCLOG("ExampleGame - Show tutorial");

	// Start tutorial animation

}

void ExampleGame::hideTutorial() {

	CCLOG("ExampleGame - Hide tutorial");

	// End tutorial animation

}

bool ExampleGame::onTouchBegan(Touch* touch, Event* event) {

	CCLOG("ExampleGame - Touch began");

	// Manage the start of a touch event

	return true;

}

void ExampleGame::onTouchMoved(Touch* touch, Event* event) {

	CCLOG("ExampleGame - Touch moved");

	// Manage a touch event
}

void ExampleGame::onTouchEnded(Touch* touch, Event* event) {

	CCLOG("ExampleGame - Touch ended");

	// Manage the end of a touch event

}

void ExampleGame::endGame(bool gameOver) {

	CCLOG("ExampleGame - End game");

	// Manage end game and start fade out animations

}


void ExampleGame::homeButtonPressed() {
    
    CCLOG("ExampleGame - homeButtonPressed");
}