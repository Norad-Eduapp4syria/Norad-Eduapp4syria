#pragma once

#include "GameObject.h"


class LabelGameObject : public GameObject {

public:
	//LabelGameObject(Node& parentNode, string nodeName, string csbPath, string colliderSpritePath = string());				// For existing nodes in scene
	LabelGameObject(Node& parentNode, const Vec2& localPosition, string fontPath, float fontSize, string text = string(), Color3B color = Color3B::WHITE, bool useAutomaticAlignment = false, string colliderSpritePath = string(), bool changeInArabic = true);		// For nodes to be created
	virtual ~LabelGameObject();
	Label& getLabel() const;
	void setText(string& text, bool changeInArabic = true);

private:
	Label* label;
	LabelGameObject(const LabelGameObject& otherLabelGameObject);				// Unimplemented
	LabelGameObject& operator=(const LabelGameObject& otherLabelGameObject);	// Unimplemented

};

inline Label& LabelGameObject::getLabel() const {

	return *label;

}
