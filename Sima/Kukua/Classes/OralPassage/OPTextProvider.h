#ifndef __OPTEXTPROVIDER_H__
#define __OPTEXTPROVIDER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

using namespace std;

class OPTextProvider
{
public:
    OPTextProvider();
    virtual ~OPTextProvider();
    string getStory();
    string getQuestion(int num);
    string getAnswer1Correct(int num);
    string getAnswer2(int num);
    string getAnswer3(int num);
    
private:
    int currentPhonemeNum;
};

#endif
