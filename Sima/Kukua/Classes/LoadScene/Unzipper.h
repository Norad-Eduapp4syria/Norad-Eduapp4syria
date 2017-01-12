#ifndef __UNZIPPER_H__
#define __UNZIPPER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

using namespace std;
using namespace cocostudio::timeline;

class Unzipper : public cocos2d::Layer
{
private:
	Node* downloadNode;
	ActionTimeline* downloadTimeLine;
	int chargeLen;
    void openNextScene();
    Node* rootNode;

public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
	
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	void Download();
	void Unzip();
	string PATH;
	string zipFile;
   // cocos2d::Label *downloadlabel;
    // implement the "static create()" method manually
    CREATE_FUNC(Unzipper);
};

#endif // __UNZIPPER_H__
