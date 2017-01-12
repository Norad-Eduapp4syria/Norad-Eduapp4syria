#include "TatuProjectile.h"
#include "Blending1Game.h"


TatuProjectile::TatuProjectile(Node& parentNode, const Vec2& localPosition, EventDispatcher* eventDispatcher)
	: PhysicsGameObject(parentNode, localPosition, Blending1Game::PATH + "TatuProjectile.csb", "RootBone/Sprite", true, false, eventDispatcher, 0xFFFFFFFF, PhysicsMaterial(0.08f, 3.f, 0.75f), PhysicsShape::Type::CIRCLE),
	startLocalPosition(localPosition)
{

	setScale(0.8);

	sprite = static_cast<Sprite*>(getChild("RootBone/Sprite"));

	setVisible(false);
	setPhysicsActivated(true);
	physicsBody->setMass(1.f);
	physicsBody->setLinearDamping(0.5f);
	physicsBody->setAngularDamping(0.8f);
	physicsBody->setRotationEnable(true);

}

TatuProjectile::~TatuProjectile() {

}

void TatuProjectile::load() {

	setVisible(false);
	setGravityEnabled(false);
	physicsBody->resetForces();
	physicsBody->setVelocity(Vec2::ZERO);
	physicsBody->setAngularVelocity(0.f);
	setLocalPosition(startLocalPosition);

}

void TatuProjectile::shot(Vec2 impulse) {

	sprite->setOpacity(255);
	setVisible(true);
	setLocalPosition(startLocalPosition);
	setGravityEnabled(true);
	physicsBody->applyImpulse(impulse);
	physicsBody->setAngularVelocity(CC_DEGREES_TO_RADIANS(-720.f));

}

void TatuProjectile::fadeOut(float time) {

	sprite->runAction(FadeOut::create(time));

}