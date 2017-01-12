#pragma once

#include "../Utils/PhysicsGameObject.h"
#include "../Utils/LabelGameObject.h"
class FallingLetters;


class FLFruit : public PhysicsGameObject {

public:
	FLFruit(Node& parentNode, const Vec2& localPosition, EventDispatcher* eventDispatcher, int tag, FallingLetters* fallingLetters);
	virtual ~FLFruit();
	LabelGameObject& getLabelGameObject() const;
	string getLetter() const;
	void setLetter(string letter);
	bool isFalling() const;
	void startFalling();
	void stopFalling(bool jumpAway = false);

protected:
	virtual bool onContactBegin(PhysicsContact& contact);

private:
	int tag;
	string letter;
	bool falling;
	Node* startParentNode;
	Vec2 startLocalPosition;
	Action* fallEndAction;
	LabelGameObject* label;
	FallingLetters* fallingLetters;
	FLFruit();										// Unimplemented
	FLFruit(const FLFruit& otherFruit);					// Unimplemented
	FLFruit& operator=(const FLFruit& otherFruit);		// Unimplemented

};

inline string FLFruit::getLetter() const {
	
	return letter;

}

inline LabelGameObject& FLFruit::getLabelGameObject() const {

	return *label;

}

inline bool FLFruit::isFalling() const {

	return falling;

}