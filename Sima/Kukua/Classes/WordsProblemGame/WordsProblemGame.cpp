#include "WordsProblemGame.h"
#include "../Utils/StringUtility.h"
#include "../Utils/Data/Logger.h"

template<> const bool kukua::Game<WordsProblemGame>::USE_PHYSICS = false;									// Enable/disable physics
template<> const bool kukua::Game<WordsProblemGame>::ENABLE_TOUCH = true;									// Used to disable tutorial on first touch and manage general touch events
template<> string kukua::Game<WordsProblemGame>::PATH = "WordsProblemGame/";							// Resources' subfolder path for this game
template<> const string kukua::Game<WordsProblemGame>::BACKGROUND_MUSIC_FILENAME = "BGMLoopLOW.mp3";		// Background music filename
template<> bool kukua::Game<WordsProblemGame>::SHOWN_TUTORIAL = false;										// Used for showing tutorial on first execution, set to true only if tutorial is not needed
template<> Scene* kukua::Game<WordsProblemGame>::scene = nullptr;
template<> const string kukua::Game<WordsProblemGame>::NAME = "Bongos";

WordsProblemGame::~WordsProblemGame() {

	CCLOG("~WordsProblemGame");

	// Delete objects created with new
	delete help;
	delete helpPentagram;
	delete palm1;
	delete palm2;
	delete plant1;
	delete plant2;
	delete plant3;
	delete plant4;
	delete plant5;
	delete plant6;
	delete bongo1;
	delete bongo2;
	delete bongo3;
	delete musicBaloon;
	for (int index = 0; index < NOTE_COUNT; ++index) {
		delete notes[index];
	}
	delete problemSignboard;
	delete helpHand;
	delete tatu;
	delete tatuNumber;
	delete pentagram;
	for (vector<GameObject*>::iterator iterator = stars.begin(); iterator < stars.end(); ++iterator) {
		delete (*iterator);
	}

}

void WordsProblemGame::initVariables() {
	
	CCLOG("WordsProblemGame - Init variables");

	correctSolution = 8;

	srand( static_cast<unsigned int>(time(NULL)));
    
	do {
		wrongSolution1 = MIN_NUMBER + rand() % (MAX_NUMBER + 1 - MIN_NUMBER);
	} while (wrongSolution1 == correctSolution);

	do {
		wrongSolution2 = MIN_NUMBER + rand() % (MAX_NUMBER + 1 - MIN_NUMBER);
	} while (wrongSolution2 == correctSolution || wrongSolution2 == wrongSolution1);

	noteIndex = 0;

}

void WordsProblemGame::initAudio() {

	CCLOG("WordsProblemGame - Init audio");

	// Preload audio files
	simpleAudioEngine->preloadEffect((PATH + "Audio/cartello.mp3").c_str());
	simpleAudioEngine->preloadEffect((PATH + "Audio/FeedNeg5.mp3").c_str());
	simpleAudioEngine->preloadEffect((PATH + "Audio/FeedPosFinaleTatu.mp3").c_str());
	simpleAudioEngine->preloadEffect((PATH + "Audio/fill1OK.mp3").c_str());
	simpleAudioEngine->preloadEffect((PATH + "Audio/fill1OK_plin.mp3").c_str());
	simpleAudioEngine->preloadEffect((PATH + "Audio/fill2OK.mp3").c_str());
	simpleAudioEngine->preloadEffect((PATH + "Audio/fill2OK_plin.mp3").c_str());
	simpleAudioEngine->preloadEffect((PATH + "Audio/fill3OK.mp3").c_str());
	simpleAudioEngine->preloadEffect((PATH + "Audio/fill3OK_plin.mp3").c_str());
	simpleAudioEngine->preloadEffect((PATH + "Audio/fill4OK.mp3").c_str());
	simpleAudioEngine->preloadEffect((PATH + "Audio/fill4OK_plin.mp3").c_str());
	simpleAudioEngine->preloadEffect((PATH + "Audio/foglie.mp3").c_str());
	simpleAudioEngine->preloadEffect((PATH + "Audio/help.mp3").c_str());
	simpleAudioEngine->preloadEffect((PATH + "Audio/notinaKO.mp3").c_str());
	simpleAudioEngine->preloadEffect((PATH + "Audio/notinaOK.mp3").c_str());
	simpleAudioEngine->preloadEffect((PATH + "Audio/popNotina.mp3").c_str());
	simpleAudioEngine->preloadEffect((PATH + "Audio/solve.mp3").c_str());
	simpleAudioEngine->preloadEffect((PATH + "Audio/TatuScende.mp3").c_str());
	simpleAudioEngine->preloadEffect((PATH + "Audio/Bonghi_salgono.mp3").c_str());
	simpleAudioEngine->preloadEffect((PATH + "Audio/carello_back.mp3").c_str());

}

void WordsProblemGame::initGameObjects() {

	CCLOG("WordsProblemGame - Init objects");

	// Instantiate gameObjects

	help = new GameObject(*rootNode, "Help", PATH + "Help.csb");
	helpPentagram = new GameObject(*(help->getNode().getChildByName("striscione")->getChildByName("score_help")), "score_help", PATH + "Help.csb");
	helpPentagram->setVisible(false);

	palm1 = new GameObject(*rootNode, "Palm1", PATH + "Palm.csb");
	palm2 = new GameObject(*rootNode, "Palm2", PATH + "Palm.csb");

	plant1 = new GameObject(*rootNode, "Plant1", PATH + "Plant2.csb");
	plant2 = new GameObject(*rootNode, "Plant2", PATH + "Plant1.csb");
	plant3 = new GameObject(*rootNode, "Plant3", PATH + "Plant2.csb");
	plant4 = new GameObject(*rootNode, "Plant4", PATH + "Plant1.csb");
	plant5 = new GameObject(*rootNode, "Plant5", PATH + "Plant3.csb");
	plant6 = new GameObject(*rootNode, "Plant6", PATH + "Plant1.csb");

	bongo1 = new Bongo(*rootNode, "Bongo1", PATH + "Bongo2.csb", _eventDispatcher, this, PATH + "Audio/fill4OK.mp3");
	touchableGameObjects.push_back(bongo1);
	bongo2 = new Bongo(*rootNode, "Bongo2", PATH + "Bongo1.csb", _eventDispatcher, this, PATH + "Audio/fill2OK.mp3");
	touchableGameObjects.push_back(bongo2);
	bongo3 = new Bongo(*rootNode, "Bongo3", PATH + "Bongo2.csb", _eventDispatcher, this, PATH + "Audio/fill3OK.mp3");
	touchableGameObjects.push_back(bongo3);

	musicBaloon = new GameObject(*rootNode, "MusicBaloon", PATH + "MusicBaloon.csb");

	for (int index = 0; index < NOTE_COUNT; ++index) {
		notes[index] = new GameObject(*(musicBaloon->getNode().getChildByName("RootBone")->getChildByName("Note" + StringUtility::toString(index + 1) + "Bone")->getChildByName("Node")), Vec2::ZERO, PATH + "Note.csb");
		notes[index]->setVisible(false);
	}

	problemSignboard = new GameObject(*rootNode, "ProblemSignboard", PATH + "ProblemSignboard.csb");

	helpHand = new GameObject(*rootNode, "HelpHand", PATH + "HelpHand.csb");
	helpHand->setVisible(false);

	tatu = new GameObject(*rootNode, "TatuNumber", PATH + "TatuNumber.csb");
	tatuNumber = new LabelGameObject(*(tatu->getNode().getChildByName("RootBone")->getChildByName("NumberBone")), Vec2::ZERO, "common/fonts/Arabic-Regular.ttf", 160, StringUtility::toString(correctSolution), Color3B(189, 112, 18));

	pentagram = new GameObject(*rootNode, "Pentagram", PATH + "Pentagram.csb");

	Node* pentagramRootBone = pentagram->getNode().getChildByName("RootBone");
	Node* starBone;
	for (int index = 4; /*(starBone = pentagramRootBone->getChildByName("Node_" + to_string(index))) != nullptr*/index < 36; ++index) {
		CCLOG("-- %d", index);
		starBone = pentagramRootBone->getChildByName("Node_" + StringUtility::toString(index));
		stars.push_back(new GameObject(*starBone, Vec2::ZERO, PATH + "Star.csb"));
	}
	CCLOG("stars count: %d", stars.size());

}

void WordsProblemGame::fadeIn() {

	CCLOG("WordsProblemGame - Fade in");
	
	// Start fade in animations

	helpPentagram->play(
		Sequence::create(
			DelayTime::create(2.f),
			CallFunc::create(
				[&]() {
					helpPentagram->setVisible(true);
				}),
			FadeIn::create(0.5f),
			nullptr
			)
		);

	simpleAudioEngine->playEffect((PATH + "Audio/solve.mp3").c_str());
	simpleAudioEngine->playEffect((PATH + "Audio/help.mp3").c_str());
	help->play("Help", [&]() {
		runAction(
			Sequence::create(
				CallFunc::create(
					[&]() {
						simpleAudioEngine->playEffect((PATH + "Audio/Bonghi_salgono.mp3").c_str());
						bongo1->play("Bongo_start");
					}),
				DelayTime::create(0.25f),
				CallFunc::create(
					[&]() {
						simpleAudioEngine->playEffect((PATH + "Audio/Bonghi_salgono.mp3").c_str());
						bongo2->play("Bongo_start");
					}),
				DelayTime::create(0.25f),
				CallFunc::create(
					[&]() {
						simpleAudioEngine->playEffect((PATH + "Audio/Bonghi_salgono.mp3").c_str());
						bongo3->play("Bongo_start");
					}),
				DelayTime::create(0.4f),
				CallFunc::create(
					[&]() {
						simpleAudioEngine->playEffect((PATH + "Audio/TatuScende.mp3").c_str());
						musicBaloon->play("Balloon_music_start", [&]() {
							runAction(
								Sequence::create(
									CallFunc::create(
										[&]() {
											simpleAudioEngine->playEffect((PATH + "Audio/popNotina.mp3").c_str());
											notes[0]->setVisible(true);
											notes[0]->play("note_start");
										}),
									DelayTime::create(0.25f),
									CallFunc::create(
										[&]() {
											simpleAudioEngine->playEffect((PATH + "Audio/popNotina.mp3").c_str());
											notes[1]->setVisible(true);
											notes[1]->play("note_start");
										}),
									DelayTime::create(0.25f),
									CallFunc::create(
										[&]() {
											simpleAudioEngine->playEffect((PATH + "Audio/popNotina.mp3").c_str());
											notes[2]->setVisible(true);
											notes[2]->play("note_start");
										}),
									DelayTime::create(0.25f),
									CallFunc::create(
										[&]() {
											simpleAudioEngine->playEffect((PATH + "Audio/popNotina.mp3").c_str());
											notes[3]->setVisible(true);
											notes[3]->play("note_start");
										}),
									DelayTime::create(0.25f),
									CallFunc::create(
										[&]() {
											simpleAudioEngine->playEffect((PATH + "Audio/popNotina.mp3").c_str());
											notes[4]->setVisible(true);
											notes[4]->play("note_start", [&]() {
												simpleAudioEngine->playEffect((PATH + "Audio/cartello.mp3").c_str());
												problemSignboard->play("show", [&]() {
													Game::enableTouch();
													Game::showTutorial();
													setBongosNumbers();
													problemSignboard->getActionTimeline()->clearFrameEndCallFuncs();
												});
											});
										}),
									nullptr
								));
							musicBaloon->getActionTimeline()->clearFrameEndCallFuncs();
						});
					}),
				nullptr
				)
			);
		help->getActionTimeline()->clearLastFrameCallFunc();
	});

	palm1->play("Palm", nullptr, true, 0.f, 0);
	palm2->play("Palm", nullptr, true, 0.f, 100);

	plant1->play("move", nullptr, true, 0.f, 0);
	plant2->play("move", nullptr, true, 0.f, 60);
	plant3->play("move", nullptr, true, 0.f, 120);
	plant4->play("move", nullptr, true, 0.f, 180);
	plant5->play("move", nullptr, true);
	plant6->play("move", nullptr, true, 0.f, 100);


}

void WordsProblemGame::showTutorial() {

	CCLOG("WordsProblemGame - Show tutorial");

	// Start tutorial animation
	helpHand->setVisible(true);
	helpHand->getNode().getChildByName("Manina")->getChildByName("Manina")->runAction(
		Sequence::create(
			FadeIn::create(0.25f),
			CallFunc::create(
				[&]() {
					helpHand->play("help_hand", nullptr, true);
				}),
			nullptr
		));

}

void WordsProblemGame::hideTutorial() {

	CCLOG("WordsProblemGame - Hide tutorial");

	// End tutorial animation
	helpHand->pause();
	helpHand->setVisible(false);

}

bool WordsProblemGame::onTouchBegan(Touch* touch, Event* event) {

	CCLOG("WordsProblemGame - Touch began");

	// Manage the start of a touch event

	return true;

}

void WordsProblemGame::onTouchMoved(Touch* touch, Event* event) {

	CCLOG("WordsProblemGame - Touch moved");

	// Manage a touch event
}

void WordsProblemGame::onTouchEnded(Touch* touch, Event* event) {

	CCLOG("WordsProblemGame - Touch ended");

	// Manage the end of a touch event

}

void WordsProblemGame::endGame() {

	CCLOG("WordsProblemGame - End game");
    Logger::getInstance()->logEvent(WordsProblemGame::NAME, Logger::WIN, "");
	// Manage end game and start fade out animations
	
	disableTouch();

	static_cast<Label*>(bongo1->getLabel()->getNode().getChildByName("Label"))->runAction(FadeOut::create(0.25f));
	static_cast<Label*>(bongo2->getLabel()->getNode().getChildByName("Label"))->runAction(FadeOut::create(0.25f));
	static_cast<Label*>(bongo3->getLabel()->getNode().getChildByName("Label"))->runAction(FadeOut::create(0.25f));

	simpleAudioEngine->playEffect((PATH + "Audio/carello_back.mp3").c_str());
	problemSignboard->play("hide", [&]() {
		playBongosSequence();
		simpleAudioEngine->playEffect((PATH + "Audio/TatuScende.mp3").c_str());
		tatu->play("tatu_number", [&]() {
			simpleAudioEngine->playEffect((PATH + "Audio/FeedPosFinaleTatu.mp3").c_str());
			tatu->play("tatu_number_standing_A", [&]() {
				tatu->play("tatu_number_standing_B", nullptr, true);
                tatu->getActionTimeline()->clearLastFrameCallFunc();
			});
		});
		problemSignboard->getActionTimeline()->clearFrameEndCallFuncs();
	});

	/*playBongosSequence();
	runAction(
		Sequence::create(
			DelayTime::create(10.f),
			CallFunc::create(
				[&]() {
					simpleAudioEngine->playEffect((PATH + "Audio/TatuScende.mp3").c_str());
					tatuNumber->play("tatu_number", [&]() {
						simpleAudioEngine->playEffect((PATH + "Audio/FeedPosFinaleTatu.mp3").c_str());
						tatuNumber->play("tatu_number_standing_A", [&]() {
							tatuNumber->play(
								"tatu_number_standing_B",
								[&]() {
									_director->replaceScene(TransitionFade::create(0.8, WordsProblemGame::createScene(), Color3B(255, 255, 255)));
								},
								true);
						});
					});	
				}),
			nullptr)
		);*/

}

void WordsProblemGame::setBongosNumbers() {

	CCLOG("WordsProblemGame - setBongosNumbers game");

	srand( static_cast<unsigned int>(time(NULL)));

	do {
		wrongSolution1 = MIN_NUMBER + rand() % (MAX_NUMBER + 1 - MIN_NUMBER);
	} while (wrongSolution1 == correctSolution);

	do {
		wrongSolution2 = MIN_NUMBER + rand() % (MAX_NUMBER + 1 - MIN_NUMBER);
	} while (wrongSolution2 == correctSolution || wrongSolution2 == wrongSolution1);

	
	switch (rand() % 3) {

	case 0:
		bongo1->setNumber(correctSolution);
		if (rand() % 2 == 0) {
			bongo2->setNumber(wrongSolution1);
			bongo3->setNumber(wrongSolution2);
		} else {
			bongo2->setNumber(wrongSolution2);
			bongo3->setNumber(wrongSolution1);
		}
		break;

	case 1:
		bongo2->setNumber(correctSolution);
		if (rand() % 2 == 0) {
			bongo1->setNumber(wrongSolution1);
			bongo3->setNumber(wrongSolution2);
		} else {
			bongo1->setNumber(wrongSolution2);
			bongo3->setNumber(wrongSolution1);
		}
		break;

	case 2:
		bongo3->setNumber(correctSolution);
		if (rand() % 2 == 0) {
			bongo1->setNumber(wrongSolution1);
			bongo2->setNumber(wrongSolution2);
		} else {
			bongo1->setNumber(wrongSolution2);
			bongo2->setNumber(wrongSolution1);
		}
		break;

	}

}

void WordsProblemGame::checkBongosNumber(Bongo* bongo) {

	CCLOG("WordsProblemGame - checkBongosNumber");

	if (bongo->getNumber() == correctSolution) {

		bongosSequence.push_back(bongo);
		bongosAudioFiles.push_back(bongo->getAudioFile());

		musicBaloon->play("Balloon_music_noteok", [&]() {
			simpleAudioEngine->playEffect((PATH + "Audio/notinaOK.mp3").c_str());
			GameObject* note = notes[noteIndex++];
			note->play("note_feedpos", [=]() {
				if (noteIndex >= NOTE_COUNT) {
					endGame();
				} else {
					setBongosNumbers();
					runAction(
						Sequence::createWithTwoActions(
							DelayTime::create(0.5f),
							CallFunc::create(
								[&]() {
									enableTouch();	
								})
							)
						);
				}
				note->getActionTimeline()->clearLastFrameCallFunc();
			});
			musicBaloon->getActionTimeline()->clearLastFrameCallFunc();
		});

	} else {

		bongosSequence.clear();
		bongosAudioFiles.clear();

		simpleAudioEngine->playEffect((PATH + "Audio/notinaKO.mp3").c_str());
		musicBaloon->play("Balloon_music_error", [&]() {
			/*
			notes[noteIndex]->play("note_error_A", [&]() {
					while (noteIndex >= 0) {
						notes[noteIndex]->play("note_error_B");
						--noteIndex;
					}
					noteIndex = 0;
					enableTouch();
				});
			*/
			--noteIndex;
			if (noteIndex > 0) {
				notes[noteIndex]->play("note_error_A", [&]() {
					runAction(
						Sequence::create(
							Repeat::create(
								Sequence::createWithTwoActions(
									DelayTime::create(0.2f),
									CallFunc::create(
										[&]() {
											notes[noteIndex]->play("note_error_B");
											notes[noteIndex]->getActionTimeline()->clearLastFrameCallFunc();
											--noteIndex;	
										})
									),
								noteIndex + 1
							),
							CallFunc::create(
								[&]() {
									noteIndex = 0;
									enableTouch();
								}),
							nullptr
						));
				});
			} else {
				/*while (noteIndex >= 0) {
					notes[noteIndex]->play("note_error_B");
					--noteIndex;
				}
				noteIndex = 0;
				enableTouch();*/
				//GameObject* note = notes[noteIndex];
				runAction(
					Sequence::create(
						Repeat::create(
							Sequence::createWithTwoActions(
								DelayTime::create(0.2f),
								CallFunc::create(
									[&]() {
										notes[noteIndex]->play("note_error_B");
										--noteIndex;	
									})
								),
							noteIndex + 1
						),
						CallFunc::create(
							[&]() {
								noteIndex = 0;
								enableTouch();
							}),
						nullptr
					));
			}

			musicBaloon->getActionTimeline()->clearLastFrameCallFunc();

		});

		setBongosNumbers();
		
	}

}

void WordsProblemGame::playBongosSequence() {

	CCLOG("WordsProblemGame - playBongosSequence");

	/*int index = 0;
	for (vector<Bongo*>::iterator iterator = bongosSequence.begin(); iterator != bongosSequence.end(); ++iterator) {
		bongosAudioFiles.push_back((*iterator)->getAudioFile());
	}*/

	/*for (vector<string>::iterator iterator = bongosAudioFiles.begin(); iterator != bongosAudioFiles.end(); ++iterator) {
		CCLOG((*iterator).c_str());
	}*/

	//vector<string>::iterator bongosAudioFilesIterator = bongosAudioFiles.begin();
	//simpleAudioEngine->playEffect((*bongosAudioFilesIterator).c_str());
	/*runAction(
		Repeat::create(
			Sequence::create(
				CallFunc::create(
					[&]() {
						simpleAudioEngine->playEffect((*bongosAudioFilesIterator).c_str());
						++bongosAudioFilesIterator;
					}),
				DelayTime::create(1.5f),
				nullptr
				),
			bongosAudioFiles.size()
			)			
		);*/
	/*runAction(
		Sequence::create(
			DelayTime::create(1.f),
			CallFunc::create(
				[&]() {
					//CCLOG(bongosAudioFiles[0].c_str());
					bongosSequence[0]->play("bongo_suona", [=]() {
							bongosSequence[0]->play("bongo_suona");
						});
					simpleAudioEngine->playEffect(bongosAudioFiles[0].c_str());
				}),
			DelayTime::create(1.75f),
			CallFunc::create(
				[&]() {
					//CCLOG(bongosAudioFiles[1].c_str());
					bongosSequence[1]->play("bongo_suona", [=]() {
						bongosSequence[1]->play("bongo_suona");
					});
					simpleAudioEngine->playEffect(bongosAudioFiles[1].c_str());
				}),
			DelayTime::create(1.75f),
			CallFunc::create(
				[&]() {
					//CCLOG(bongosAudioFiles[2].c_str());
					bongosSequence[2]->play("bongo_suona", [=]() {
						bongosSequence[2]->play("bongo_suona");
					});
					simpleAudioEngine->playEffect(bongosAudioFiles[2].c_str());
				}),
			DelayTime::create(1.75f),
			CallFunc::create(
				[&]() {
					//CCLOG(bongosAudioFiles[3].c_str());
					bongosSequence[3]->play("bongo_suona", [=]() {
						bongosSequence[3]->play("bongo_suona");
					});
					simpleAudioEngine->playEffect(bongosAudioFiles[3].c_str());
				}),
			DelayTime::create(1.75f),
			CallFunc::create(
				[&]() {
					//CCLOG(bongosAudioFiles[4].c_str());
					bongosSequence[4]->play("bongo_suona", [=]() {
						bongosSequence[4]->play("bongo_suona");
					});
					simpleAudioEngine->playEffect(bongosAudioFiles[4].c_str());
				}),
			nullptr
			)
		);*/

	bongo1->play("bongo_suona", nullptr, true, 0.f, 0);
	bongo2->play("bongo_suona", nullptr, true, 0.f, 15);
	bongo3->play("bongo_suona", nullptr, true, 0.f, 30);
	runAction(
		Sequence::create(
			CallFunc::create(
				[&]() {
					simpleAudioEngine->playEffect(bongosAudioFiles[0].c_str());
				}),
			DelayTime::create(1.25f),
			CallFunc::create(
				[&]() {
					simpleAudioEngine->playEffect(bongosAudioFiles[1].c_str());
				}),
			DelayTime::create(1.25f),
			CallFunc::create(
				[&]() {
					simpleAudioEngine->playEffect(bongosAudioFiles[2].c_str());
				}),
			DelayTime::create(1.25f),
				CallFunc::create(
				[&]() {
					simpleAudioEngine->playEffect(bongosAudioFiles[3].c_str());
				}),
			DelayTime::create(1.25f),
			CallFunc::create(
				[&]() {
					simpleAudioEngine->playEffect(bongosAudioFiles[4].c_str());
				}),
			DelayTime::create(1.25f),
			CallFunc::create(
				[&]() {
					bongo1->pause();
					bongo2->pause();
					bongo3->pause();
				}),
			/*DelayTime::create(2.5f),
			CallFunc::create(
				[&]() {
					_director->replaceScene(TransitionFade::create(0.8, WordsProblemGame::createScene(), Color3B(255, 255, 255)));
				}),*/
			nullptr
			)
		);
	runAction(
		Sequence::create(
			DelayTime::create(5.f),
			CallFunc::create(
				[&]() {
                    Logger::getInstance()->logEvent(NAME, Logger::CLOSE, "");
					_director->replaceScene(TransitionFade::create(0.8, WordsProblemGame::createScene(), Color3B(255, 255, 255)));
				}),
			nullptr
			)
		);

	pentagram->play(
		MoveBy::create(7.f, Vec2(4000.f, 0.f))
		);
	int index = 0;
	for (vector<GameObject*>::iterator iterator = stars.begin(); iterator < stars.end(); ++iterator) {
		(*iterator)->play("animation", nullptr, true, 0.f, (index * 20) % 60);
		++index;
	}
	
}

void WordsProblemGame::homeButtonPressed() {
}