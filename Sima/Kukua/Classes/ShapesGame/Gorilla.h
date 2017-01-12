#pragma once

#include "../utils/TouchableGameObject.h"
#include "Biscuit.h"

class ShapesGame;


class Gorilla : public TouchableGameObject {

public:
	Gorilla(Node& parentNode, const Vec2& localPosition, string csbPath, EventDispatcher* eventDispatcher, ShapesGame* shapesGame);
	virtual ~Gorilla();
	void askBiscuit();
	void openMouth();
	void closeMouth();
	void eat(Biscuit::Shape shape);
	int getEatenBiscuits() const;

private:
	static const int MAX_EATEN_BISCUITS = 5;
	enum MouthState { ASKING, CLOSED, OPENING, OPEN, CLOSING };
	MouthState mouthState;
	ShapesGame* shapesGame;
	int eatenBiscuits;
	CocosDenshion::SimpleAudioEngine* simpleAudioEngine;
	Gorilla();												// Unimplemented
	Gorilla(const Gorilla& otherGorilla);					// Unimplemented
	Gorilla& operator=(const Gorilla& otherGorilla);		// Unimplemented
	virtual bool onTouchBegan(Touch* touch, Event* event);

};

inline int Gorilla::getEatenBiscuits() const {

	return eatenBiscuits;

}
