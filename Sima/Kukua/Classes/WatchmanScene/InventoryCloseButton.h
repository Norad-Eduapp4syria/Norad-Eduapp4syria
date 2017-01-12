#pragma once

#include "../Utils/TouchableGameObject.h"
class WatchmanScene;
class Inventory;


class InventoryCloseButton : public TouchableGameObject {

public:
	InventoryCloseButton(Node& parentNode, const Vec2& position, EventDispatcher* eventDispatcher, Inventory* inventory);
	virtual ~InventoryCloseButton();

protected:
	virtual bool onTouchBegan(Touch* touch, Event* event);

private:
	Inventory* inventory;
	InventoryCloseButton();													// Unimplemented
	InventoryCloseButton(const InventoryCloseButton& other);				// Unimplemented
	InventoryCloseButton& operator=(const InventoryCloseButton& other);		// Unimplemented

};
