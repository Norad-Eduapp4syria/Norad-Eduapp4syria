#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"

#include <string>

using namespace std;
using namespace cocos2d;
using namespace cocostudio::timeline;


class GameObject {

public:
	GameObject(Node& parentNode, string nodeName, string animationCsbPath, string colliderSpritePath = string());				// For existing nodes in scene
	GameObject(Node& parentNode, const Vec2& localPosition, string csbPath = string(), string colliderSpritePath = string());	// For nodes to be instantiated from a csb or new nodes
	virtual ~GameObject();
	Node& getNode();
	ActionTimeline* getActionTimeline();
	Vec2 getPosition() const; // return world position
	void setPosition(Vec2 worldPosition);
	Vec2 getLocalPosition() const;
	void setLocalPosition(Vec2 localPosition);
	float getScale() const;
	void setScale(float scale);
	bool isVisible();
	void setVisible(bool visible);
	void play(string animationName, std::function<void()> callback = nullptr, bool looping = false, float delay = 0.f, int startFrameOffset = 0);
	void play(Action* action);
	void clearLastFrameCallFunc();
	void pause();
	void resume();
	bool intersectsPoint(Touch& touch) const;
	Node* getParent() const;
	void setParent(Node& parentNode);
	void setParent(Node& parentNode, const Vec2& localPosition);
	Node* getChild(string path);
	void bringToFront();			// To be tested
	const Sprite* const getColliderSprite() const;

protected:
	Node* node;
	Sprite* colliderSprite;
	ActionTimeline* actionTimeline;
	//GameObject(Node& parentNode, const Vec2& localPosition, string colliderSpritePath = string());		// Constructor for subclasses that create a new node

private:
	GameObject();				// Unimplemented

};

inline Node& GameObject::getNode() {
	return *node;
}

inline ActionTimeline* GameObject::getActionTimeline() {
	return actionTimeline;
}

inline Vec2 GameObject::getPosition() const {

	return node->getParent()->convertToWorldSpace(node->getPosition());

}

inline Vec2 GameObject::getLocalPosition() const {

	return node->getPosition();

}

inline float GameObject::getScale() const {

	return node->getScale();

}

inline bool GameObject::isVisible() {

	return node->isVisible();

}

inline void GameObject::setVisible(bool visible) {

	return node->setVisible(visible);

}

inline Node* GameObject::getParent() const {

	return node->getParent();

}

inline const Sprite* const GameObject::getColliderSprite() const {

	return colliderSprite;

}