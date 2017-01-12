#pragma once

#include "../../Utils/PhysicsGameObject.h"
#include "../../Utils/LabelGameObject.h"
class FallingLettersEp2;


class Fruit : public PhysicsGameObject {

public:
	Fruit(Node& parentNode, const Vec2& localPosition, EventDispatcher* eventDispatcher, int tag, FallingLettersEp2* multiplicationGame);
	virtual ~Fruit();
	int getNumber() const;
	void setNumber(int number);
	bool isFalling() const;
	void startFalling();
	void stopFalling(bool jumpAway = false);

protected:
	virtual bool onContactBegin(PhysicsContact& contact);

private:
	int tag;
	int number;
	bool falling;
	Node* startParentNode;
	Vec2 startLocalPosition;
	Action* fallEndAction;
    Sprite* labelImg;
	FallingLettersEp2* multiplicationGame;
	Fruit();										// Unimplemented
	Fruit(const Fruit& otherFruit);					// Unimplemented
	Fruit& operator=(const Fruit& otherFruit);		// Unimplemented

};

inline int Fruit::getNumber() const {
	
	return number;

}

inline bool Fruit::isFalling() const {

	return falling;

}
