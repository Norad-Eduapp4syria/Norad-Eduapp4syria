#include "PlatformGameSema.h"
#include "../Utils/StringUtility.h"



PlatformGameSema::PlatformGameSema(Node& _parentNode, const Vec2& _localPosition, string animationCsbPath, string _colliderSpritePath, bool _dynamic, bool _gravityEnabled, EventDispatcher* _eventDispatcher, unsigned int _contactTestBitmask, const PhysicsMaterial& _material, PhysicsShape::Type _shape)
	: PhysicsGameObject(_parentNode, _localPosition, animationCsbPath, _colliderSpritePath, _dynamic, _gravityEnabled, _eventDispatcher, _contactTestBitmask, _material, _shape)

{
	name = "PlatformGameSema";
	setPhysicsActivated(true);
	audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
	eventDispatcher = _eventDispatcher;
	physicsBody->setTag(300);
	//physicsBody->setEnabled(false);

	
	//localPosition = _localPosition;
//	status = 1;
//	clicked = false;
//	typePlatformGameSema = _typePlatformGameSema;
	/*
	angleIn = 1 + rand() % 360;
	angleOut = 1 + rand() % 360;

	getNode().setRotation(-angleIn-90);

	int startPosX = (cos(angleIn / 180.0f * M_PI) * 2000) + localPosition.x;
	int startPosY = (sin(angleIn / 180.0f * M_PI) * 2000) + localPosition.y;
	this->setPosition(Vec2(startPosX, startPosY));

	shadow = new GameObject(getNode(), Point(0, 0), _csbPath + "CSD/shadow" + StringUtility::toString(_typePlatformGameSema) + ".csb");

	update();
	flyIn();
	*/
}

bool PlatformGameSema::onContactBegin(PhysicsContact& contact) {
	CCLOG("PlatformGameSema onContactBegin");
	
	auto nodeA = contact.getShapeA()->getBody();
	auto nodeB = contact.getShapeB()->getBody();

	CCLOG("nodeA %i", nodeA->getTag());
	CCLOG("nodeB %i", nodeB->getTag());
	int tag = 300;
	CCLOG("nodeA %i , nodeB %i", nodeA->getTag(), nodeB->getTag());
	if (nodeA && nodeB && (nodeA->getTag() == tag || nodeB->getTag() == tag)) {
		if (nodeB->getTag() == tag){
			nodeA->setEnabled(false);
		}
		else{
			nodeB->setEnabled(false);
		}
		
		
		//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect((Blending1Game::PATH_AUDIO + "Audio/woodenBoxHit.mp3").c_str());
		//play("hit");
		//hit = true;

	}
	
	return false;

}
PlatformGameSema::~PlatformGameSema() {
	//getNode().removeFromParent();
	CCLOG("DISTRUTTORE");
}


void PlatformGameSema::update() {

}


//Si posiziona a in un raggio di 2000px
//muove al centron con un andamento quadout
//si ferma per 3 secondi
//muove in un raggio di 2000px con andamento quadin
//(Si puo aggiungere al movimento lineare anche un movimento di oscillazione con il moveby di ampiezza random 50/100 px)
/*

*/
bool PlatformGameSema::onTouchBegan(Touch* touch, Event* event) {
	/*
	CCLOG("BoxButton - onTouchBegan");
	
	if (TouchableGameObject::onTouchBegan(touch, event)) {
		if (!clicked){
			CCLOG("TOUCH");

			EventCustom event("click_PlatformGameSema");
			event.setUserData(this);
			eventDispatcher->dispatchEvent(&event);
		}
	}
*/
	return false;

}

void PlatformGameSema::destroy(){
//	EventCustom event("delete_PlatformGameSema");
//	event.setUserData(this);
//	eventDispatcher->dispatchEvent(&event);
	//delete this;
}