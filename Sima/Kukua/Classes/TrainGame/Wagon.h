#pragma once

#include "../Utils/TouchableGameObject.h"
#include "../Utils/LabelGameObject.h"

class Train;


class Wagon : public TouchableGameObject {

public:
	static const float SEND_TIME;
	static const Vec2 SEND_OFFSET;
	static const int MIN_NUMBER;
	static const int MAX_NUMBER;
	static const int CORRECT_NUMBER_PROBABILITY;
	//Wagon(Node& parentNode, string nodeName, string csbPath, string colliderSpritePath, EventDispatcher* eventDispatcher);
	Wagon(Node& parentNode, const Vec2& localPosition, string csbFolderPath, string csbFileName, string colliderSpritePath, EventDispatcher* eventDispatcher, const Color3B* color, int correctNumber, Train& train, Node* trainWagonNode);
	virtual ~Wagon();
	const Color3B* const getColor() const;
	LabelGameObject& getLabelGameObject() const;
	bool isSent() const;
	int getNumber() const;
	void setNumber(int number);
	int getCorrectNumber() const;
	void send();

protected:
	virtual bool onTouchBegan(Touch* touch, Event* event);

private:
	const Color3B* color;
	int correctNumber;
	int number;
	LabelGameObject* labelGameObject;
	Train* train;
	Vec2 startLocalPosition;
	bool sent;
	Action* sendAction;
	Node* wagonsPlaceholder;
	Node* trainWagonNode;
	Wagon(const Wagon& otherWagon);					// Unimplemented
	Wagon& operator=(const Wagon& otherWagon);		// Unimplemented

};

inline const Color3B* const Wagon::getColor() const {

	return color;

}

inline int Wagon::getCorrectNumber() const {

	return correctNumber;

}

inline LabelGameObject& Wagon::getLabelGameObject() const {

	return *labelGameObject;

}

inline int Wagon::getNumber() const {
	return number;
}

inline bool Wagon::isSent() const {
	return sent;
}