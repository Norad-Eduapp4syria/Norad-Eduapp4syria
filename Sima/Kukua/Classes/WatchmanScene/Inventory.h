#pragma once

#include "../Utils/GameObject.h"
#include "../Utils/TouchableGameObject.h"
#include "../Utils/Data/DataProvider.h"
#include <vector>
#include <map>
class WatchmanScene;
class InventoryCloseButton;
class InventoryKnowledgeBubble;
using namespace std;


class Inventory : public GameObject {

public:
	Inventory(Node& parentNode, const Vec2& localPosition, string csbPath, EventDispatcher* eventDispatcher, WatchmanScene* watchmanScene);
	virtual ~Inventory();
	void enableTouch();
	void disableTouch();
    void showUnlockedNewKnowledgeBubble(DBKnowledgeBubble dbKnowledgeBubble, std::function<void()> callback = nullptr);
	void show();
	void hide();

    void showNightrunnerAnimation();
    
private:
	vector<TouchableGameObject*> touchableGameObjects;
	WatchmanScene* watchmanScene;
	//InventoryCloseButton* inventoryCloseButton;
	DataProvider* dataProvider;
	vector<DBKnowledgeBubble*> dbKnowledgeBubbles;
	vector<InventoryKnowledgeBubble*> inventoryKnowledgeBubbles;
	Inventory();										// Unimplemented
	Inventory(const Inventory& other);					// Unimplemented
	Inventory& operator=(const Inventory& other);		// Unimplemented
    GameObject *achantiBlock;
    CocosDenshion::SimpleAudioEngine* simpleAudioEngine;
    vector<GameObject*> achantiBlocks;
    void addLetterToAchantiBlock(string letter);
};