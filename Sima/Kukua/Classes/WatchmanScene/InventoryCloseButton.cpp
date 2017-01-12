#include "InventoryCloseButton.h"
#include "WatchmanScene.h"
#include "Inventory.h"


InventoryCloseButton::InventoryCloseButton(Node& parentNode, const Vec2& position, EventDispatcher* eventDispatcher, Inventory* inventory)
	: TouchableGameObject(parentNode, position, "Main_prop/csd/inventory_btn.csb", "RootBone/Sprite", eventDispatcher)
{

	CCLOG("InventoryCloseButton()");

	this->inventory = inventory;

}

InventoryCloseButton::~InventoryCloseButton() {

	CCLOG("~InventoryCloseButton()");

}

bool InventoryCloseButton::onTouchBegan(Touch* touch, Event* event) {

	if (TouchableGameObject::onTouchBegan(touch, event)) {

		setTouchable(false);
		inventory->hide();

	}

	return false;

}