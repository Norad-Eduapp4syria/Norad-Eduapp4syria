#pragma once

#include "../Utils/TouchableGameObject.h"
#include "Inventory.h"
class WatchmanScene;


class InventoryButton : public TouchableGameObject {

public:
	InventoryButton(Node& parentNode, string nodeName, EventDispatcher* eventDispatcher, WatchmanScene* watchmanScene, Inventory* inventory);
	virtual ~InventoryButton();

protected:
	virtual bool onTouchBegan(Touch* touch, Event* event);

private:
	enum State { SHOW_INVENTORY, HIDE_INVENTORY };
	State state;
	WatchmanScene* watchmanScene;
	Inventory* inventory;
	InventoryButton();												// Unimplemented
	InventoryButton(const InventoryButton& other);					// Unimplemented
	InventoryButton& operator=(const InventoryButton& other);		// Unimplemented
	
};