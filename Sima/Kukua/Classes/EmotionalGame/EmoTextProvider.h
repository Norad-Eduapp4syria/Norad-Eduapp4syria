#ifndef __EmoTextProvider_H__
#define __EmoTextProvider_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

using namespace std;

class EmoTextProvider
{
public:
    EmoTextProvider(int chosenMood);
    virtual ~EmoTextProvider();
    string getQuestion();
    string getAnswer1();
    string getAnswer2();
    string getAnswer3();
    string getAnswer4();
    string getAnswer5();
    string getAnswer6();
    
private:
    string mood;
};

#endif
