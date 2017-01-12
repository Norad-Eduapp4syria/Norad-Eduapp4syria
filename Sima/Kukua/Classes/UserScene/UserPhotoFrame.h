#pragma once

#include "../Utils/TouchableGameObject.h"


class UserPhotoFrame : public TouchableGameObject {

public:
	UserPhotoFrame(Node& parentNode, const Vec2& position, EventDispatcher* eventDispatcher, string photoPath, int index, string userId);
	virtual ~UserPhotoFrame();
    void hidePlayButton();

protected:
	virtual bool onTouchBegan(Touch* touch, Event* event);

private:
	UserPhotoFrame();													// Unimplemented
	UserPhotoFrame(const UserPhotoFrame& other);				// Unimplemented
	UserPhotoFrame& operator=(const UserPhotoFrame& other);		// Unimplemented
    Node* playNode;
    cocostudio::timeline::ActionTimeline* playNodeTimeline;
    int index;
    void addPlayButton();
    string userId;
};
