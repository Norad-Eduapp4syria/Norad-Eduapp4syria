#pragma once

#include "../Utils/GameObject.h"
#include "LetterBox.h"
#include "BoxButtonLetterBox.h"
#include "SimpleAudioEngine.h"


class FeedbackSignboard : public GameObject {

public:
	FeedbackSignboard(Node& parentNode, string nodeName, string word, vector<string> phonemes, vector<LetterBox::Color> colors, string blendingIconSpriteName, bool justAudio);
	virtual ~FeedbackSignboard();
	vector<BoxButtonLetterBox*>& getBoxButtonLetterBoxes();
	GameObject& getBlendingIcon() const;
	void showStartGame(std::function<void()> callback = nullptr);
	void showEndGame(std::function<void()> callback = nullptr);
    string wordAudioFilename;
    
protected:
	CocosDenshion::SimpleAudioEngine* simpleAudioEngine;

private:
	string word;
	vector<BoxButtonLetterBox*> boxButtonLetterBoxes;
	GameObject* blendingIcon;
	FeedbackSignboard();												// Unimplemented
	FeedbackSignboard(const FeedbackSignboard& other);					// Unimplemented
	FeedbackSignboard& operator=(const FeedbackSignboard& other);		// Unimplemented
    bool justAudio;
    string wordEnglishFileName;
   // string blendingIconSpriteWord;
    
};

inline vector<BoxButtonLetterBox*>& FeedbackSignboard::getBoxButtonLetterBoxes() {

	return boxButtonLetterBoxes;

}

inline GameObject& FeedbackSignboard::getBlendingIcon() const {

	return *blendingIcon;

}
