#include "MultiplicationBaloon.h"
#include "FallingLettersEp2.h"
#include "../../Utils/StringUtility.h"

MultiplicationBaloon::MultiplicationBaloon(Node& parentNode, string nodeName)
	: GameObject(parentNode, nodeName, kukua::Game<FallingLettersEp2>::PATH + "csd/FLBaloon.csb")
{

	CCLOG("MultiplicationBaloon");

    labelImg = Sprite::create("common/images/wordsbank/void.png");
    labelImg->setScale(0.5);
    node->getChildByName("RootBone")->addChild(labelImg);
    
}

MultiplicationBaloon::~MultiplicationBaloon() {

}

void MultiplicationBaloon::setFactors(int multiplier) {
    //string txt = StringUtility::toString(multiplicand) + "x" + StringUtility::toString(multiplier);
    
    string phoneme = DataProvider::getInstance()->getCurrentDBKnowledgeBubble()->getPhoneme();
    
    if (multiplier == 0) labelImg->setTexture("common/images/wordsbank/"+phoneme+"_initial.png");
    else if (multiplier == 1) labelImg->setTexture("common/images/wordsbank/"+phoneme+"_medial.png");
    else if (multiplier == 2) labelImg->setTexture("common/images/wordsbank/"+phoneme+"_final.png");
    
    else if (multiplier == 3) labelImg->setTexture("common/images/wordsbank/"+phoneme+"_initial.png");
    else if (multiplier == 4) labelImg->setTexture("common/images/wordsbank/"+phoneme+"_medial.png");
    else if (multiplier == 5) labelImg->setTexture("common/images/wordsbank/"+phoneme+"_final.png");
    
    else {
        labelImg->setTexture("common/images/wordsbank/void.png");
    }
    
}
