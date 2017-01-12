#include "LabelGameObject.h"
#include "Data/DataProvider.h"
#include "Data/ArabicHelper.h"

/*LabelGameObject::LabelGameObject(Node& parentNode, string nodeName, string csbPath, string colliderSpritePath)
	: GameObject(parentNode, nodeName, csbPath, colliderSpritePath)
{

	CCLOG("LabelGameObject");

}*/

LabelGameObject::LabelGameObject(Node& parentNode, const Vec2& localPosition, string fontPath, float fontSize, string text, Color3B color, bool useAutomaticAlignment, string colliderSpritePath, bool changeInArabic)
	: GameObject(parentNode, localPosition, colliderSpritePath)
{
    
    if (fontSize > 300) fontSize = 300; // needed for arabic font
    
    DataProvider* dataProvider = DataProvider::getInstance();
    
    text = dataProvider->checkAndCorrectDuplicatePhoneme(text);
    
    if ( ( text.size() > 1 ) &&   (dataProvider->isNumber(text) == false ) ) {
        fontSize = fontSize * 0.85;
    }
    
 
    
    // TODO.. fare meglio questa serie di if
    if (text == "bubble21-22_ep4") text = "21-22";
    if (text == "bubble23-24_ep4") text = "23-24";
    if (text == "bubble25-26_ep4") text = "25-26";
    if (text == "bubble27-28_ep4") text = "27-28";
    if (text == "bubble29-30_ep4") text = "29-30";
    
    if ( (text == "10-11") ||  (text == "12-13") ||  (text == "14-15") ||  (text == "16-17") || (text == "18-20") ||
         (text == "21-22") ||  (text == "23-24") ||  (text == "25-26") ||  (text == "27-28") || (text == "29-30")
        ) {
        fontSize = fontSize * 0.5;
    }

    if (changeInArabic) {
        text = ArabicHelper::getInstance()->getInArabic( text );
    }
    
    
	//label = Label::createWithTTF(text, fontPath, fontSize);
    label = ArabicHelper::getInstance()->createLabel(text, fontSize);
	label->setColor(color);
	label->setName("Label");
	node->addChild(label);

    
    
    if (useAutomaticAlignment) {
        if ( (text != "t") && (text != "i") && (text != "h") && (text != "d") && (text != "l") && (text != "f") && (text != "b") &&
             (text != "0") && (text != "1") && (text != "2") && (text != "3") && (text != "4") && (text != "5") && (text != "6") && (text != "7") && (text != "8") && (text != "9")  )
        label->setPosition(label->getPositionX() , label->getPositionY() + (fontSize/10) );
    }
    
}

LabelGameObject::~LabelGameObject() {

}

void LabelGameObject::setText(string& text,  bool changeInArabic ) {

	//CCLOG("LabelGameObject - setText");
    
    text = DataProvider::getInstance()->checkAndCorrectDuplicatePhoneme(text); // todo: controllare se è corretto... perchè passo string&  e non so come si comporta...
    if (changeInArabic) {
        text = ArabicHelper::getInstance()->getInArabic( text );
    }
	label->setString(text);

}
