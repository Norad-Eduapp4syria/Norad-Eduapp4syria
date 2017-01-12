#pragma once

#include "../Utils/TouchableGameObject.h"
#include "../Utils/LabelGameObject.h"
class WordsProblemGame;


class Bongo : public TouchableGameObject {

public:
	Bongo(Node& parentNode, string nodeName, string csbPath, EventDispatcher* eventDispatcher, WordsProblemGame* wordsProblemGame, string audioFile);
	virtual ~Bongo();
	int getNumber() const;
	void setNumber(int number);
	LabelGameObject* getLabel();
	const string& getAudioFile() const;

protected:
	virtual bool onTouchBegan(Touch* touch, Event* event);

private:
	static const int PARTICLE_SPRITE_COUNT = 8;
	int number;
	LabelGameObject* label;
	Sprite* particleSprites[PARTICLE_SPRITE_COUNT];
	WordsProblemGame* wordsProblemGame;
	string audioFile;
	CocosDenshion::SimpleAudioEngine* simpleAudioEngine;
	Bongo();
	Bongo(const Bongo& otherBongo);
	Bongo& operator=(const Bongo& otherBongo);

};

inline int Bongo::getNumber() const {

	return number;

}

inline LabelGameObject* Bongo::getLabel() {

	return label;

}

inline const string& Bongo::getAudioFile() const {

	return audioFile;

}