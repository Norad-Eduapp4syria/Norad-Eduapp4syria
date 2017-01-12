#include "WoodenBox.h"
#include "Blending1Game.h"


WoodenBox::WoodenBox(Node& parentNode, string nodeName, EventDispatcher* eventDispatcher)
	: Box(parentNode, nodeName, Blending1Game::PATH + "WoodenBox.csb", "RootBone/BoxBone/Sprite", false, false, eventDispatcher),
	hit(false)
{

	physicsBody->setCollisionBitmask(0x0);


}

WoodenBox::WoodenBox(Node& parentNode, const Vec2& localPosition, EventDispatcher* eventDispatcher)
	: Box(parentNode, localPosition, Blending1Game::PATH + "WoodenBox.csb", "RootBone/BoxBone/Sprite", false, false, eventDispatcher),
	hit(false)
{

	physicsBody->setCollisionBitmask(0x0);

}

WoodenBox::~WoodenBox() {

}

bool WoodenBox::onContactBegin(PhysicsContact& contact) {

	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA && nodeB && (nodeA->getTag() == tag || nodeB->getTag() == tag) && !hit) {

		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect((Blending1Game::PATH_AUDIO + "Audio/woodenBoxHit.mp3").c_str());
		play("hit");
		hit = true;

	}

	return false;

}

void WoodenBox::explode() {

	if (!hit) {
		play("explode1");
	} else {
		play("explode2");
	}

}
