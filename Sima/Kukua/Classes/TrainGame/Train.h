#pragma once

#include "../Utils/GameObject.h"
#include "../Utils/LabelGameObject.h"
#include "Wagon.h"

class ComprehensionGame;

#include <map>
#include <vector>


class Train : public GameObject {

public:
	Train(Node& rootNode, const Vec2& localPosition, string csbFolderPath, EventDispatcher* eventDispatcher, ComprehensionGame& comprehensionGame, Node* wagonsPlaceholder);
	virtual ~Train();
	void fadeIn(std::function<void()> callback = nullptr);
	void fadeOut(std::function<void()> callback = nullptr);
	//void setSendWagons(bool sendWagons);
	void startSendingWagons();
	void stopSendingWagons(const Color3B* color);
    void showTutorial();
    void hideTutorial();

    float scorePercent = 100.0f;
    float scoreToSubtract = 10.0f;
    
private:
	static const Color3B YELLOW_COLOR;
	static const Color3B GREEN_COLOR;
	static const Color3B ORANGE_COLOR;
	static const Color3B VIOLET_COLOR;
	static const int MIN_YELLOW_WAGON_NUMBER;
	static const int MAX_YELLOW_WAGON_NUMBER;
	//static const int SEND_CORRECT_WAGON_PROBABILITY;	// %
	static const int SEND_WAGON_PROBABILITY;			// %
	static const float SEND_WAGON_RATE;
	int yellowWagonNumber;
	//bool sendWagons;
	bool sendGreenWagons;
	bool sendOrangeWagons;
	bool sendVioletWagons;
	CocosDenshion::SimpleAudioEngine* simpleAudioEngine;
	ComprehensionGame* comprehensionGame;
	GameObject* locomotiveGameObject;
	vector<GameObject*> idleWagonsGameObjects;
	GameObject* endWagonGameObject;
	GameObject* endWagonBaloonGameObject;
	LabelGameObject* yellowWagonLabelGameObject;
	map<const Color3B*, vector<Wagon*>> wagons;
    GameObject *hand;
	//void update();
	/*Action* sendGreenWagonsAction;
	Action* sendOrangeWagonsAction;
	Action* sendVioletWagonsAction;*/
	Action* sendWagonsAction;
	//bool attachWagon(Wagon& wagon);

};