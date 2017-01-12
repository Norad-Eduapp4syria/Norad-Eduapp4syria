#pragma once

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include <string>

using namespace std;
using namespace cocos2d;

class ListComp_RoundManager
{
public:

	static const int NOTHING = 0;           // nothing
	static const int FAIL_FADE = 1;         // fails and the obj disappear
	static const int FAIL_BACK = 2;         // fails and the obj goes back
	static const int SUCCESS = 3;           // success

	static bool roundActive;
	static int target; // 0: char, 1: obj
	static int objID;
	static int colorID;
	static int bigObjID;
	static int triggerBigID;
	static int characterID, chosenCharID;
	static int sideCharacterID;
	static string sentence;

	static int  draggedObjID;
	static bool isCutscenePlaying;

	static int charID[2];
	const static Sprite	*charCollider[2];
	const static Sprite	*bigTrigCollider[4];

	static bool boolTriggers[4];

	static int checkIntersection(Sprite *dragCollider, int objID, int colorID);

private:
	// Disallow creating an instance of this object
	ListComp_RoundManager() {}
};
