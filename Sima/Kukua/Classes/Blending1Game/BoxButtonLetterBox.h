#pragma once

#include "../Utils/GameObject.h"
#include "../Utils/LabelGameObject.h"
#include "LetterBox.h"
#include "SimpleAudioEngine.h"


class BoxButtonLetterBox : public GameObject {

public:
	BoxButtonLetterBox(Node& parentNode, const Vec2& localPosition, string phoneme, LetterBox::Color color);
	virtual ~BoxButtonLetterBox();
	LetterBox::Color getColor() const;
	string getPhoneme() const;
	void setPhoneme(string phoneme);
	void playAudio();

protected:
	CocosDenshion::SimpleAudioEngine* simpleAudioEngine;

private:
	LetterBox::Color color;
	string phoneme;
	LabelGameObject* labelGameObject;
	BoxButtonLetterBox();												// Unimplemented
	BoxButtonLetterBox(const BoxButtonLetterBox& other);				// Unimplemented
	BoxButtonLetterBox& operator=(const BoxButtonLetterBox& other);		// Unimplemented

};

inline LetterBox::Color BoxButtonLetterBox::getColor() const {

	return color;

}

inline string BoxButtonLetterBox::getPhoneme() const {

	return phoneme;

}