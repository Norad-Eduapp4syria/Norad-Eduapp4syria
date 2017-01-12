#pragma once

#include "Box.h"
#include "../Utils/LabelGameObject.h"
#include "SimpleAudioEngine.h"
#include <ctype.h>
class Blending1Game;
class Cannon;


class LetterBox : public Box {

public:
	enum Color {
		YELLOW = 0,
		RED = 1,
		BLUE = 2
	};
	LetterBox(Node& parentNode, string nodeName, Color color, EventDispatcher* eventDispatcher, string phoneme, Blending1Game* blending1Game, Cannon* cannon);
	LetterBox(Node& parentNode, const Vec2& localPosition, Color color, EventDispatcher* eventDispatcher, string phoneme, Blending1Game* blending1Game, Cannon* cannon);
	virtual ~LetterBox();
	Color getColor() const;
	string getPhoneme() const;
	void setPhoneme(string phoneme);
	virtual void explode();

protected:
	CocosDenshion::SimpleAudioEngine* simpleAudioEngine;
	virtual bool onContactBegin(PhysicsContact& contact);
	
private:
	Color color;
	string phoneme;
	Blending1Game* blending1Game;
	Cannon* cannon;
	//bool hit;
	LabelGameObject* labelGameObject;
	LetterBox();										// Unimplemented
	LetterBox(const LetterBox& other);					// Unimplemented
	LetterBox& operator=(const LetterBox& other);		// Unimplemented

};

inline LetterBox::Color LetterBox::getColor() const {

	return color;

}

inline string LetterBox::getPhoneme() const {

	return phoneme;

}

inline void LetterBox::setPhoneme(string phoneme) {
    
	this->phoneme = phoneme;
	labelGameObject->setText(phoneme, false);
	char firstChar = phoneme.front();
	if (phoneme.size() > 0 && islower(firstChar) != 0 && (firstChar != 'f' && firstChar != 'h' && firstChar != 'k' && firstChar != 'l' && firstChar != 't')) {
		labelGameObject->setLocalPosition(Vec2(0.f, 10.f));
	} else {
		labelGameObject->setLocalPosition(Vec2::ZERO);
	}

}
