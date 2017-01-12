#pragma once

#include "../Utils/TouchableGameObject.h"
#include "LetterBox.h"
#include "BoxButtonLetterBox.h"
#include "SimpleAudioEngine.h"


class BoxButton : public TouchableGameObject {

public:
	//BoxButton(Node& parentNode, string nodeName, EventDispatcher* eventDispatcher);
	BoxButton(Node& parentNode, const Vec2& localPosition, EventDispatcher* eventDispatcher, Blending1Game* blending1Game, string phoneme, LetterBox::Color color);
	virtual ~BoxButton();
	BoxButtonLetterBox& getBoxButtonLetterBox() const;
	void playAudio();

protected:
	CocosDenshion::SimpleAudioEngine* simpleAudioEngine;
	virtual bool onTouchBegan(Touch* touch, Event* event);

private:
	Blending1Game* blending1Game;
	string phoneme;
	BoxButtonLetterBox* boxButtonLetterBox;
	BoxButton();										// Unimplemented
	BoxButton(const BoxButton& other);					// Unimplemented
	BoxButton& operator=(const BoxButton& other);		// Unimplemented

};

inline BoxButtonLetterBox& BoxButton::getBoxButtonLetterBox() const {

	return *boxButtonLetterBox;

}