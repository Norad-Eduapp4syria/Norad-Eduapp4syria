#include "FLBaloon.h"
#include "FallingLetters.h"
#include "../Utils/StringUtility.h"

FLBaloon::FLBaloon(Node& parentNode, string nodeName)
	: GameObject(parentNode, nodeName, kukua::Game<FallingLetters>::PATH + "csd/FLBaloon.csb")
{

	CCLOG("FLBaloon");

	label = new LabelGameObject(*(node->getChildByName("RootBone")), Vec2::ZERO, "common/fonts/Arabic-Regular.ttf", 100, "0x0", Color3B(164, 81, 21));

}

FLBaloon::~FLBaloon() {

	CCLOG("~FLBaloon");
    delete label;
}

void FLBaloon::setFactors(string multiplicand) {

	label->setText(multiplicand);

}
