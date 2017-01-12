#include "GameObject.h"

GameObject::GameObject(Node& parentNode, string nodeName, string animationCsbPath, string colliderSpritePath) {

	assert(&parentNode != nullptr);
	assert(parentNode.getChildByName(nodeName) != nullptr);

	node = parentNode.getChildByName(nodeName);
	// CCLOG("node: %s", node->getName().c_str());

	if (animationCsbPath.length() > 0) {
		//CCLOG("csb: %s", animationCsbPath.c_str());
		actionTimeline = CSLoader::createTimeline(animationCsbPath);
		node->runAction(actionTimeline);
	} else {
		actionTimeline = nullptr;
	}

	if (colliderSpritePath != string() && colliderSpritePath.length() > 0) {

		colliderSprite = static_cast<Sprite*>(getChild(colliderSpritePath));

	} else {

		colliderSprite = nullptr;

	}

}

GameObject::GameObject(Node& parentNode, const Vec2& localPosition, string csbPath, string colliderSpritePath) {

	assert(&parentNode != nullptr);

	if (csbPath != string() && csbPath.length() > 0) {
		node = CSLoader::createNode(csbPath);
		parentNode.addChild(node);
		node->setPosition(localPosition);

		assert(csbPath.length() > 0);
		//CCLOG("csb: %s", csbPath.c_str());
		actionTimeline = CSLoader::createTimeline(csbPath);
		node->runAction(actionTimeline);
	} else {
		node = Node::create();
		// CCLOG("parentNode.getName() %s", parentNode.getName().c_str());
		parentNode.addChild(node);
		node->setPosition(localPosition);

		actionTimeline = nullptr;
	}

	if (colliderSpritePath != string() && colliderSpritePath.length() > 0) {

		colliderSprite = static_cast<Sprite*>(getChild(colliderSpritePath));

	} else {

		colliderSprite = nullptr;

	}

}

GameObject::~GameObject() {

	//CCLOG("~GameObject");

}

void GameObject::setPosition(Vec2 worldPosition) {

	if (node->getParent() != nullptr) {
		node->setPosition(node->getParent()->convertToNodeSpace(worldPosition));
	} else {
		node->setPosition(worldPosition);
	}

}

void GameObject::setLocalPosition(Vec2 localPosition) {

	node->setPosition(localPosition);

}

void GameObject::setScale(float scale) {

	node->setScale(scale);

}

void GameObject::play(string animationName, std::function<void()> callback, bool looping, float delay, int startFrameOffset) {

	assert(actionTimeline != nullptr);

	if (delay > 0.f) {

		node->runAction(
			Sequence::create(
				DelayTime::create(delay),
				CallFunc::create([=]() {
					play(animationName, callback, looping, 0.f, startFrameOffset);
				}),
				nullptr));

	} else {
               
		if (startFrameOffset == 0) {
			actionTimeline->play(animationName, looping);
		} else {
			AnimationInfo animationInfo = actionTimeline->getAnimationInfo(animationName);
			actionTimeline->gotoFrameAndPlay(animationInfo.startIndex, animationInfo.endIndex, animationInfo.startIndex + startFrameOffset % (animationInfo.endIndex - animationInfo.startIndex), looping);
		}
        
        if (callback != nullptr) {
            actionTimeline->setLastFrameCallFunc(callback);
        }       
        
    }

}

void GameObject::clearLastFrameCallFunc() {

	actionTimeline->clearLastFrameCallFunc();

}

void GameObject::play(Action* action) {

	node->runAction(action);

}

void GameObject::pause() {

	//node->stopAllActions();
	Director::getInstance()->getActionManager()->pauseTarget(node);

}

void GameObject::resume() {

	Director::getInstance()->getActionManager()->resumeTarget(node);

}

bool GameObject::intersectsPoint(/*const */Touch& touch) const {

	if (colliderSprite != nullptr) {

		return colliderSprite->getBoundingBox().containsPoint(colliderSprite->getParent()->convertTouchToNodeSpace(&touch));

	}

	CCLOG("GameObject %s doesn't have a collider sprite", node->getName().c_str());

	return false;

}

void GameObject::setParent(Node& parentNode) {

	node->retain();
	Vec2 worldPosition = getPosition();
	node->getParent()->removeChild(node, false);
	parentNode.addChild(node);
	node->setPosition(parentNode.convertToNodeSpace(worldPosition));
	node->release();

}

void GameObject::setParent(Node& parentNode, const Vec2& localPosition) {

	node->retain();
	Vec2 worldPosition = getPosition();
	node->getParent()->removeChild(node, false);
	parentNode.addChild(node);
	node->setPosition(localPosition);
	node->release();

}

Node* GameObject::getChild(string path) {

	assert(path != string() && path.length() > 0);

	std::vector<std::string> nodeNames;
	std::stringstream stringstream(path);
	std::string item;
	while (std::getline(stringstream, item, '/')) {
		nodeNames.push_back(item);
	}

	vector<string>::iterator iterator = nodeNames.begin();
	Node* childNode = node->getChildByName(*(iterator++));
	while (childNode != nullptr && iterator != nodeNames.end()) {
		childNode = childNode->getChildByName(*(iterator++));
	}

	return childNode;

}

void GameObject::bringToFront() {
	
	Node* parent = getParent();

	assert(parent != nullptr);

	setParent(*parent);

}