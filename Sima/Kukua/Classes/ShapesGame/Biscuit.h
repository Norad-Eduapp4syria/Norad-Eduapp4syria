#pragma once

#include "../Utils/DraggableGameObject.h"
class Gorilla;


class Biscuit : public DraggableGameObject {

public:
	enum Shape { CIRCLE, TRIANGLE, SQUARE, RECTAGLE, TRAPEZE, RHOMBUS, PENTA, HEXAGON, OCTA, OVAL, PARALL };
	Biscuit(Node& parentNode, string nodeName, string csbPath, string colliderSpritePath, EventDispatcher* eventDispatcher, Gorilla* gorilla, Shape shape);
    Biscuit(Node& parentNode, const Vec2& localPosition, string csbPath, string colliderSpritePath, EventDispatcher* eventDispatcher, Gorilla* gorilla, Shape shape);
	virtual ~Biscuit();
	Shape getShape() const;
	void reset(Vec2 newLocalPosition);
	void fadeIn(float seconds);
	void fadeOut(float seconds);

private:
	static const float MIN_SCALE;
	static const float MAX_SCALE;
	static const float DELTA_SCALE;
	static const float MOUTH_RADIUS;
	Shape shape;
	Node* shadowNode;
	Gorilla* gorilla;
	Node* gorillaMouthNode;
	float startDistanceToMouth;
	Biscuit();											// Unimplemented
	Biscuit(const Biscuit& otherBiscuit);				// Unimplemented
	Biscuit& operator=(const Biscuit& otherBiscuit);	// Unimplemented
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);

};

inline Biscuit::Shape Biscuit::getShape() const {

	return shape;

}
