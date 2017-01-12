#include "InventoryButton.h"
#include "WatchmanScene.h"


InventoryButton::InventoryButton(Node& parentNode, string nodeName, EventDispatcher* eventDispatcher, WatchmanScene* watchmanScene, Inventory* inventory)
	: TouchableGameObject(parentNode, nodeName, "Main_prop/csd/inventory_btn.csb", "RootBone/Sprite", eventDispatcher),
	state(HIDE_INVENTORY)
{

	this->watchmanScene = watchmanScene;
	this->inventory = inventory;

}

InventoryButton::~InventoryButton() {

}

bool InventoryButton::onTouchBegan(Touch* touch, Event* event) {

	if (TouchableGameObject::onTouchBegan(touch, event)) {

		watchmanScene->disableTouch();

        SimpleAudioEngine::getInstance()->playEffect((WatchmanScene::PATH + "Audio/board/pul_board.mp3").c_str());
        
		if (state == HIDE_INVENTORY) {

			inventory->show();
            
			play("showInventory", [&]() {
				state = SHOW_INVENTORY;
				setTouchable(true);
				clearLastFrameCallFunc();
			});

		} else {

			inventory->hide();

			play("hideInventory", [&]() {
				state = HIDE_INVENTORY;
				watchmanScene->enableTouch();
				clearLastFrameCallFunc();
			});

		}

		/*watchmanScene->disableTouch();
		inventory->show();*/

	}

	return false;

}