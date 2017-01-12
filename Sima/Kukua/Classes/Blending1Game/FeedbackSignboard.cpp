#include "FeedbackSignboard.h"
#include "Blending1Game.h"
#include "SimpleAudioEngine.h"
#include "../Utils/StringUtility.h"
#include "../Utils/Data/ArabicHelper.h"
#include "../Utils/Data/ArabicHelperForGames.h"


FeedbackSignboard::FeedbackSignboard(Node& parentNode, string nodeName, string word, vector<string> phonemes, vector<LetterBox::Color> colors, string blendingIconSpriteName, bool justAudio)
	: GameObject(parentNode, nodeName, Blending1Game::PATH + "FeedbackSignboard.csb"),
	word(word),
    justAudio(justAudio)
{

	assert(phonemes.size() == colors.size());

    
    int phonemesSize = (int)phonemes.size();
    CCLOG("phonemesSize = %d", phonemesSize);
    
	int index = 0;
    
    float boxSpacing = 150.0f;
    float boxScale = 1.0f;
    if (phonemesSize < 6) {
        boxSpacing = 230.0f;
        boxScale = 1.6f;
    }
    //for (auto iterator = phonemes.begin(); iterator != phonemes.end(); ++iterator) {
    for (vector<string>::reverse_iterator iterator = phonemes.rbegin(); iterator != phonemes.rend(); ++iterator ) {
        BoxButtonLetterBox* boxButtonLetterBox = new BoxButtonLetterBox(*getChild("RootBone"), Vec2((-((phonemes.size() - 1) / 2.f) + index) * boxSpacing, 15.f), *iterator, colors.at(index));
        boxButtonLetterBox->play("reset");
        boxButtonLetterBox->setScale(boxScale);
        boxButtonLetterBoxes.push_back(boxButtonLetterBox);
        ++index;
    }
    wordEnglishFileName = "";
	blendingIcon = new GameObject(*getChild("RootBone/Bone_bollo"), Vec2::ZERO, Blending1Game::PATH + "BlendingIcon.csb");
    CCLOG("FeedbackSignboard - word: %s", word.c_str());
    if (DataProvider::getInstance()->getCurrentEpisode() == 1) {
        auto labelWord = ArabicHelper::getInstance()->createLabel(word.c_str(), 140, false);
        labelWord->setColor(Color3B(47,109,182));
        labelWord->setPosition(Vec2(0,0));
        blendingIcon->getChild("RootBone/SpriteBone")->addChild(labelWord);
    } else {
        
        CCLOG(">>>>> FeedbackSignboard costruttore - word = %s", word.c_str());
        
        wordEnglishFileName = ArabicHelperForGames::getInstance()->getFilenameInEnglish_blending(word); // TODO LUCAAAAAAAAA
        
        std::replace( wordEnglishFileName.begin(), wordEnglishFileName.end(), ' ', '_'); // replace all ' ' to '_'
        wordEnglishFileName = StringUtility::toLowerCase(wordEnglishFileName);
        
         CCLOG(">>>>> FeedbackSignboard costruttore - imageFileName = %s", wordEnglishFileName.c_str());
        static_cast<Sprite*>(blendingIcon->getChild("RootBone/SpriteBone/Sprite"))->setTexture("Blending1Game/words/images/" + wordEnglishFileName + ".png");
        // static_cast<Sprite*>(blendingIcon->getChild("RootBone/SpriteBone/Sprite"))->setTexture("common/images/words/" + blendingIconSpriteName );
    }
    


	simpleAudioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
	simpleAudioEngine->preloadEffect((Blending1Game::PATH_AUDIO + "Audio/signboardShow.mp3").c_str());
	simpleAudioEngine->preloadEffect((Blending1Game::PATH_AUDIO + "Audio/signboardHide.mp3").c_str());
	simpleAudioEngine->preloadEffect((Blending1Game::PATH_AUDIO + "Audio/feedbackPositive.mp3").c_str());

}



FeedbackSignboard::~FeedbackSignboard() {
    
	for (auto iterator = boxButtonLetterBoxes.begin(); iterator != boxButtonLetterBoxes.end(); ++iterator) {
		delete (*iterator);
	}

	delete blendingIcon;

}

void FeedbackSignboard::showStartGame(std::function<void()> callback) {

	blendingIcon->setVisible(false);
    if (justAudio) setVisible(false);
	if (!justAudio) simpleAudioEngine->playEffect((Blending1Game::PATH_AUDIO + "Audio/signboardShow.mp3").c_str());
	play("show", [=]() {

		const float stepDelay = 0.5f;
		float totalDelay = 0.f;

		//for (auto iterator = boxButtonLetterBoxes.begin(); iterator != boxButtonLetterBoxes.end(); ++iterator) {
        for (vector<BoxButtonLetterBox*>::reverse_iterator iterator = boxButtonLetterBoxes.rbegin(); iterator != boxButtonLetterBoxes.rend(); ++iterator ) { // REVERSE ITERATOR (funziona)
            BoxButtonLetterBox* boxButtonLetterBox = *iterator;
			play(
				Sequence::createWithTwoActions(
					DelayTime::create(totalDelay),
					CallFunc::create(
						[=]() {
							boxButtonLetterBox->playAudio();
							boxButtonLetterBox->play("show");
						})
					)
				);
			totalDelay += stepDelay;
		}

		play(
			Sequence::createWithTwoActions(
				DelayTime::create(totalDelay + 1.f),
				CallFunc::create(
					[=]() {
                        
                        if (DataProvider::getInstance()->getCurrentEpisode() == 1) {
                            simpleAudioEngine->playEffect(("common/audio/sema/words/" + wordAudioFilename + ".mp3").c_str());
                        } else {
                            simpleAudioEngine->playEffect(("Blending1Game/words/audio/" + wordEnglishFileName + ".mp3").c_str());
                        }
                        
						const float stepDelay = 0.5f;
						float totalDelay = 2.f;

						for (auto iterator = boxButtonLetterBoxes.begin(); iterator != boxButtonLetterBoxes.end(); ++iterator) {
							BoxButtonLetterBox* boxButtonLetterBox = *iterator;
							play(
								Sequence::createWithTwoActions(
									DelayTime::create(totalDelay),
									CallFunc::create(
										[=]() {
											boxButtonLetterBox->play("hide2");
										})	
									)
								);
							totalDelay += stepDelay;
						}

						play(
							Sequence::createWithTwoActions(
								DelayTime::create(totalDelay),
								CallFunc::create(
									[=]() {
										if (!justAudio) simpleAudioEngine->playEffect((Blending1Game::PATH_AUDIO + "Audio/signboardHide.mp3").c_str());
										play("hide", [=]() {
											callback();
											clearLastFrameCallFunc();
										});
									})
								)
							);

						clearLastFrameCallFunc();
					})
				)
			);
		
		clearLastFrameCallFunc();

	});

}

void FeedbackSignboard::showEndGame(std::function<void()> callback) {

	blendingIcon->setVisible(false);
    setVisible(true);
	simpleAudioEngine->playEffect((Blending1Game::PATH_AUDIO + "Audio/signboardShow.mp3").c_str());
	play("show", [=]() {

		const float stepDelay = 0.5f;
		float totalDelay = 0.f;

        
        for (vector<BoxButtonLetterBox*>::reverse_iterator iterator = boxButtonLetterBoxes.rbegin(); iterator != boxButtonLetterBoxes.rend(); ++iterator ) {
		// for (auto iterator = boxButtonLetterBoxes.begin(); iterator != boxButtonLetterBoxes.end(); ++iterator) {
			BoxButtonLetterBox* boxButtonLetterBox = *iterator;
			play(
				Sequence::createWithTwoActions(
					DelayTime::create(totalDelay),
					CallFunc::create(
						[=]() {
							boxButtonLetterBox->playAudio();
							boxButtonLetterBox->play("show");
						})
					)
				);
			totalDelay += stepDelay;
		}

		play(
			Sequence::createWithTwoActions(
				DelayTime::create(totalDelay + 1.f),
				CallFunc::create(
					[=]() {
                        
                        
                        CCLOG(">>>>> FeedbackSignboard::showEndGame - wordAudioFilename = %s", wordAudioFilename.c_str());
                        CCLOG(">>>>> FeedbackSignboard::showEndGame - wordEnglishFileName = %s", wordEnglishFileName.c_str());
                        
                        if (DataProvider::getInstance()->getCurrentEpisode() == 1) {
                            simpleAudioEngine->playEffect(("common/audio/sema/words/" + wordAudioFilename + ".mp3").c_str());
                        } else {
                            simpleAudioEngine->playEffect(("Blending1Game/words/audio/" + wordEnglishFileName + ".mp3").c_str());
                        }
                        
						const float stepDelay = 0.5f;
						float totalDelay = 2.f;

						for (auto iterator = boxButtonLetterBoxes.begin(); iterator != boxButtonLetterBoxes.end(); ++iterator) {
							BoxButtonLetterBox* boxButtonLetterBox = *iterator;
							play(
								Sequence::createWithTwoActions(
									DelayTime::create(totalDelay),
									CallFunc::create(
										[=]() {
											boxButtonLetterBox->play("hide2");
										})	
									)
								);
							totalDelay += stepDelay;
						}

						play(
							Sequence::create(
								DelayTime::create(totalDelay),
								CallFunc::create(
									[=]() {
										simpleAudioEngine->playEffect((Blending1Game::PATH_AUDIO + "Audio/feedbackPositive.mp3").c_str());
                                    
                                        blendingIcon->bringToFront();
										blendingIcon->setVisible(true);
										blendingIcon->play("show");
									}),
								DelayTime::create(2.25f),
								CallFunc::create(
									[=]() {
										simpleAudioEngine->playEffect((Blending1Game::PATH_AUDIO + "Audio/signboardHide.mp3").c_str());
										play("hide", [=]() {
											callback();
											// clearLastFrameCallFunc(); // commentata il 28 giugno... ma ci vorrebbe
										});
									}),
								nullptr
								)
							);

						clearLastFrameCallFunc();
					})
				)
			);
		
		clearLastFrameCallFunc();

	});

}
