#pragma once

#include "../Utils/TouchableGameObject.h"
#include "../Utils/LabelGameObject.h"
#include "../Utils/Data/DBKnowledgeBubble.h"
class Inventory;


class InventoryKnowledgeBubble : public TouchableGameObject {

public:
	InventoryKnowledgeBubble(Node& parentNode, const Vec2& localPosition, EventDispatcher* eventDispatcher, string csbPath, Inventory* inventory, DBKnowledgeBubble dbKnowledgeBubble);
	virtual ~InventoryKnowledgeBubble();
	DBKnowledgeBubble getDBKnowledgeBubble() const;
    
    void setText(string txt);
    void setNotCompletedImage(string spritePath);
    void setCompletedImage(string spritePath);
    void setActiveImage(string spritePath);

protected:
	virtual bool onTouchBegan(Touch* touch, Event* event);

private:
	Inventory* inventory;
	DBKnowledgeBubble dbKnowledgeBubble;
	LabelGameObject* label;
    LabelGameObject* label2;
	InventoryKnowledgeBubble();																// Unimplemented
	InventoryKnowledgeBubble(const InventoryKnowledgeBubble& other);						// Unimplemented
	InventoryKnowledgeBubble& operator=(const InventoryKnowledgeBubble& other);				// Unimplemented

};

inline DBKnowledgeBubble InventoryKnowledgeBubble::getDBKnowledgeBubble() const {

	return dbKnowledgeBubble;

}