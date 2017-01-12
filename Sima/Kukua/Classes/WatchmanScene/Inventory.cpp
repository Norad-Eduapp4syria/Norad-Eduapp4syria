#include "Inventory.h"
#include "WatchmanScene.h"
#include "InventoryCloseButton.h"
#include "InventoryKnowledgeBubble.h"
#include "../VideoScene/VideoScene.h"
#include "../MapScene/MapScene.h"
#include "../Utils/Data/Logger.h"
#include "../AppMacros.h"
#include "../Utils/StringUtility.h"

Inventory::Inventory(Node& parentNode, const Vec2& localPosition, string csbPath, EventDispatcher* eventDispatcher, WatchmanScene* watchmanScene)
	: GameObject(parentNode, localPosition, csbPath)
{
   
	this->watchmanScene = watchmanScene;
   
    simpleAudioEngine = CocosDenshion::SimpleAudioEngine::getInstance();

	dataProvider = DataProvider::getInstance();
 
    
    dbKnowledgeBubbles = dataProvider->getDBKnowledgeBubbles(dataProvider->getCurrentDBWatchman()->getEpisode());
    
	for (auto iterator = dbKnowledgeBubbles.begin(); iterator != dbKnowledgeBubbles.end(); ++iterator) {
        
		if (getChild("RootBone/Phoneme_" + (*iterator)->getPhoneme() + "/KnowledgeBubbleParentNode") != nullptr) {
            
            InventoryKnowledgeBubble* inventoryKnowledgeBubble;
            string phonemeValue = (*iterator)->getPhoneme();
            if (dataProvider->isNumber( phonemeValue )) {
                inventoryKnowledgeBubble = new InventoryKnowledgeBubble(*(getChild("RootBone/Phoneme_" + (*iterator)->getPhoneme() + "/KnowledgeBubbleParentNode")), Vec2::ZERO, eventDispatcher, WatchmanScene::PATH + "CSD/knowledgenumbers.csb", this, **iterator);
            } else {
                inventoryKnowledgeBubble = new InventoryKnowledgeBubble(*(getChild("RootBone/Phoneme_" + (*iterator)->getPhoneme() + "/KnowledgeBubbleParentNode")), Vec2::ZERO, eventDispatcher, WatchmanScene::PATH + "CSD/knowledgeBubble.csb", this, **iterator);
                
                if (dataProvider->getCurrentEpisode() >= 4) {
                    string epStr = StringUtility::toString( dataProvider->getCurrentEpisode() );
                    inventoryKnowledgeBubble->setText("");
                    inventoryKnowledgeBubble->setNotCompletedImage(WatchmanScene::PATH + "PNG/knowledge_spheres/ep"+epStr+"/ball_empty.png");
                    inventoryKnowledgeBubble->setCompletedImage(WatchmanScene::PATH + "PNG/knowledge_spheres/ep"+epStr+"/ball_full.png");
                    inventoryKnowledgeBubble->setActiveImage(WatchmanScene::PATH + "PNG/knowledge_spheres/ep"+epStr+"/ball_select.png");
                }
                
            }
            

            
			if (!(*iterator)->isLocked()) {
                // CCLOG("INVENTORY - white phoneme _%s_", (*iterator)->getPhoneme().c_str());
				inventoryKnowledgeBubble->play("ball_white_stop"); //inventoryKnowledgeBubble->play("ball_white");
            } else {
                // CCLOG("INVENTORY - empty phoneme _%s_", (*iterator)->getPhoneme().c_str());
                inventoryKnowledgeBubble->play("Ball_empty");
            }
			touchableGameObjects.push_back(inventoryKnowledgeBubble);
			inventoryKnowledgeBubbles.push_back(inventoryKnowledgeBubble);
		} else {
			CCLOG("no phoneme %s", (*iterator)->getPhoneme().c_str());
		}
	}

	setVisible(false);
    
    
    int currEpisode = dataProvider->getCurrentEpisode();
    
    
    if (currEpisode > 1) {
        achantiBlock = new GameObject(*getChild("RootBone/Achanti_contenitore/Achanti"), Vec2::ZERO, WatchmanScene::PATH + "CSD/achanti.csb");
        
        if (currEpisode > 2) {
            auto block2 = new GameObject(*achantiBlock->getChild("gemma_vuota_1/gemma_piena/gemma_piena"), Vec2::ZERO, WatchmanScene::PATH + "CSD/Achanti_Tokens/jewel.csb");
            block2->play("achanti_stop");
            achantiBlocks.push_back(block2);
        }
        if (currEpisode > 3) {
            auto block3 = new GameObject(*achantiBlock->getChild("gemma_vuota_2/gemma_piena/gemma_piena"), Vec2::ZERO, WatchmanScene::PATH + "CSD/Achanti_Tokens/jewel.csb");
            block3->play("achanti_stop");
            achantiBlocks.push_back(block3);
        }
        if (currEpisode > 4) {
            auto block4 = new GameObject(*achantiBlock->getChild("gemma_vuota_3/gemma_piena/gemma_piena"), Vec2::ZERO, WatchmanScene::PATH + "CSD/Achanti_Tokens/jewel.csb");
            block4->play("achanti_stop");
            achantiBlocks.push_back(block4);
        }
        if (currEpisode > 5) {
            auto block5 = new GameObject(*achantiBlock->getChild("gemma_vuota_4/gemma_piena/gemma_piena"), Vec2::ZERO, WatchmanScene::PATH + "CSD/Achanti_Tokens/jewel.csb");
            block5->play("achanti_stop");
            achantiBlocks.push_back(block5);
        }
        if (currEpisode > 6) {
            auto block6 = new GameObject(*achantiBlock->getChild("gemma_vuota_5/gemma_piena/gemma_piena"), Vec2::ZERO, WatchmanScene::PATH + "CSD/Achanti_Tokens/jewel.csb");
            block6->play("achanti_stop");
            achantiBlocks.push_back(block6);
        }
        if (currEpisode > 7) {
            auto block7 = new GameObject(*achantiBlock->getChild("gemma_vuota_6/gemma_piena/gemma_piena"), Vec2::ZERO, WatchmanScene::PATH + "CSD/Achanti_Tokens/jewel.csb");
            block7->play("achanti_stop");
            achantiBlocks.push_back(block7);
        }
        if (currEpisode > 8) {
            auto block8 = new GameObject(*achantiBlock->getChild("gemma_vuota_7/gemma_piena/gemma_piena"), Vec2::ZERO, WatchmanScene::PATH + "CSD/Achanti_Tokens/jewel.csb");
            block8->play("achanti_stop");
            achantiBlocks.push_back(block8);
        }
        if (currEpisode > 9) {
            auto block9 = new GameObject(*achantiBlock->getChild("gemma_vuota_8/gemma_piena/gemma_piena"), Vec2::ZERO, WatchmanScene::PATH + "CSD/Achanti_Tokens/jewel.csb");
            block9->play("achanti_stop");
            achantiBlocks.push_back(block9);
        }
        
    } else {
        achantiBlock = nullptr;
    }
    
    
    
    
    
    
    /*
	auto v = dataProvider->getUnlockedDBKnowledgeBubbles(*(dataProvider->getCurrentDBWatchman()));
	for (auto iterator = v.begin(); iterator != v.end(); ++iterator) {
		CCLOG("unlocked phoneme %s", (*iterator)->getPhoneme().c_str());
	}
    */
}

Inventory::~Inventory() {

	//delete inventoryCloseButton;
	for (auto iterator = dbKnowledgeBubbles.begin(); iterator != dbKnowledgeBubbles.end(); ++iterator) {
		delete *iterator;
	}
	for (auto iterator = inventoryKnowledgeBubbles.begin(); iterator != inventoryKnowledgeBubbles.end(); ++iterator) {
		delete *iterator;
	}
    
    for (auto iterator = achantiBlocks.begin(); iterator != achantiBlocks.end(); ++iterator) {
        delete *iterator;
    }
    
    if (achantiBlock != nullptr) delete achantiBlock;
}

void Inventory::enableTouch() {

	// Enable thouch events on touchableGameObjects
	for (vector<TouchableGameObject*>::iterator iterator = touchableGameObjects.begin(); iterator != touchableGameObjects.end(); ++iterator) {
		(*iterator)->setTouchable(true);
	}

}

void Inventory::disableTouch() {

	// Disable thouch events on touchableGameObjects
	for (vector<TouchableGameObject*>::iterator iterator = touchableGameObjects.begin(); iterator != touchableGameObjects.end(); ++iterator) {
		(*iterator)->setTouchable(false);
	}

}

void Inventory::showUnlockedNewKnowledgeBubble(DBKnowledgeBubble dbKnowledgeBubble, std::function<void()> callback) {

	setVisible(true);

	auto inventoryKnowledgeBubbleIterator = find_if(inventoryKnowledgeBubbles.begin(), inventoryKnowledgeBubbles.end(), [dbKnowledgeBubble](const InventoryKnowledgeBubble* inventoryKnowledgeBubbles) {
        
        string dbKbPhoneme =dbKnowledgeBubble.getPhoneme();
        dbKbPhoneme = dbKbPhoneme.substr(0, dbKbPhoneme.find("_"));
        return inventoryKnowledgeBubbles->getDBKnowledgeBubble().getPhoneme() == dbKbPhoneme;
    
    });
	assert(inventoryKnowledgeBubbleIterator != inventoryKnowledgeBubbles.end());	
	InventoryKnowledgeBubble* inventoryKnowledgeBubble = *inventoryKnowledgeBubbleIterator;

	inventoryKnowledgeBubble->play("Ball_empty");

    simpleAudioEngine->playEffect((WatchmanScene::PATH + "Audio/board/Board_scende_sale.mp3").c_str());
    getParent()->getChildByName("blackBG")->setOpacity(0);
    getParent()->getChildByName("blackBG")->setVisible(true);
    getParent()->getChildByName("blackBG")->runAction(FadeIn::create(0.5f));
	play("show", [=]() {
		inventoryKnowledgeBubble->play("ball_pop", [=]() {
            simpleAudioEngine->playEffect((WatchmanScene::PATH + "Audio/board/Board_scende_sale.mp3").c_str());
            getParent()->getChildByName("blackBG")->runAction(FadeOut::create(0.5f));
			play("hide", [=]() {
                getParent()->getChildByName("blackBG")->setVisible(false);
				setVisible(false);
                callback();
                clearLastFrameCallFunc();
			});
			inventoryKnowledgeBubble->clearLastFrameCallFunc();
		});
		clearLastFrameCallFunc();
	});

}

void Inventory::show() {

	//watchmanScene->disableTouch();
	setVisible(true);

	DBKnowledgeBubble dbKnowledgeBubble = *(dataProvider->getCurrentDBKnowledgeBubble());
    CCLOG("fuori dbKbPhoneme = %s", (dbKnowledgeBubble.getPhoneme()).c_str());
    CCLOG("cc = %lu", inventoryKnowledgeBubbles.size());
    
    if ( dataProvider->isSimplePhoneme( dbKnowledgeBubble.getPhoneme() ) && (dataProvider->isIntensifierGameTurn==false) ) {
      
        auto inventoryKnowledgeBubbleIterator = find_if(inventoryKnowledgeBubbles.begin(), inventoryKnowledgeBubbles.end(), [dbKnowledgeBubble](const InventoryKnowledgeBubble* inventoryKnowledgeBubbles) {
            
            string dbKbPhoneme =dbKnowledgeBubble.getPhoneme();
            
            if ( DataProvider::getInstance()->getCurrentEpisode() < 4 ) {
                dbKbPhoneme = dbKbPhoneme.substr(0, dbKbPhoneme.find("_"));
            }
            
            CCLOG("dbKbPhoneme = %s", dbKbPhoneme.c_str());
            return inventoryKnowledgeBubbles->getDBKnowledgeBubble().getPhoneme() == dbKbPhoneme;
            
        });
        
        CCLOG("qui");
        
        assert(inventoryKnowledgeBubbleIterator != inventoryKnowledgeBubbles.end());
        InventoryKnowledgeBubble* inventoryKnowledgeBubble = *inventoryKnowledgeBubbleIterator;
        inventoryKnowledgeBubble->play("ball_active", nullptr, true);
    
    }

    if ( dataProvider->getCurrentEpisode() >= 4 ) {
        CCLOG("inventario... gestione bubble per episodi dal 4 in più...");
        auto inventoryKnowledgeBubbleIterator = find_if(inventoryKnowledgeBubbles.begin(), inventoryKnowledgeBubbles.end(), [dbKnowledgeBubble](const InventoryKnowledgeBubble* inventoryKnowledgeBubbles) { return inventoryKnowledgeBubbles->getDBKnowledgeBubble().getPhoneme() == dbKnowledgeBubble.getPhoneme(); });
        assert(inventoryKnowledgeBubbleIterator != inventoryKnowledgeBubbles.end());
        InventoryKnowledgeBubble* inventoryKnowledgeBubble = *inventoryKnowledgeBubbleIterator;
        inventoryKnowledgeBubble->play("ball_active", nullptr, true);
    }
    
    simpleAudioEngine->playEffect((WatchmanScene::PATH + "Audio/board/Board_scende_sale.mp3").c_str());
    getParent()->getChildByName("blackBG")->setOpacity(0);
    getParent()->getChildByName("blackBG")->setVisible(true);
    getParent()->getChildByName("blackBG")->runAction(FadeIn::create(0.5f));
    play("show", [=]() {
		enableTouch();
        getActionTimeline()->clearLastFrameCallFunc();
    });

 /*
	play(
		Sequence::createWithTwoActions(
			MoveTo::create(1.f, Vec2(640.f, 500.f)),
			CallFunc::create(
				[&]() {
					inventoryCloseButton->setTouchable(true);
				})
			)
		);
    */
}

void Inventory::hide() {

	disableTouch();
    simpleAudioEngine->playEffect((WatchmanScene::PATH + "Audio/board/Board_scende_sale.mp3").c_str());
    getParent()->getChildByName("blackBG")->runAction(FadeOut::create(0.5f));
    play("hide", [=]() {
        getParent()->getChildByName("blackBG")->setVisible(false);
        setVisible(false);
        clearLastFrameCallFunc();
    });
}

void Inventory::addLetterToAchantiBlock(string letter) {
    auto block1 = new GameObject(*achantiBlock->getChild("gemma_vuota_"+letter+"/gemma_piena/gemma_piena"), Vec2::ZERO, WatchmanScene::PATH + "CSD/Achanti_Tokens/jewel.csb"); //zzzzz
    achantiBlocks.push_back(block1);
    
    float animTime = 1.7f;
    
    block1->getChild("gemma_piena/gemma_vuota")->setOpacity(0);
    auto fadeIn1 = FadeIn::create(animTime);
    block1->getChild("gemma_piena/gemma_vuota")->runAction(fadeIn1);
    
    block1->play("achanti_glow", nullptr, true);
}

void Inventory::showNightrunnerAnimation() {
    
    
    setVisible(true);
    simpleAudioEngine->playEffect((WatchmanScene::PATH + "Audio/board/Board_scende_sale.mp3").c_str());
    getParent()->getChildByName("blackBG")->setOpacity(0);
    getParent()->getChildByName("blackBG")->setVisible(true);
    getParent()->getChildByName("blackBG")->runAction(FadeIn::create(0.5f));
    play("show");
    
    if (dataProvider->getCurrentEpisode()==1) {
        // add achanti block
        achantiBlock = new GameObject(*getChild("RootBone/Achanti_contenitore/Achanti"), Vec2::ZERO, WatchmanScene::PATH + "CSD/achanti.csb");
        
        achantiBlock->getChild("Achanti_2/Achanti_2")->setOpacity(0);
        auto fadeIn = FadeIn::create(1.7f);
        achantiBlock->getChild("Achanti_2/Achanti_2")->runAction(fadeIn);
        
        achantiBlock->play("Achanti_1", nullptr, true);
    
    } else if (dataProvider->getCurrentEpisode()==2) {
        addLetterToAchantiBlock("1");
    } else if (dataProvider->getCurrentEpisode()==3) {
        addLetterToAchantiBlock("2");
    } else if (dataProvider->getCurrentEpisode()==4) {
        addLetterToAchantiBlock("3");
    } else if (dataProvider->getCurrentEpisode()==5) {
        addLetterToAchantiBlock("4");
    } else if (dataProvider->getCurrentEpisode()==6) {
        addLetterToAchantiBlock("5");
    } else if (dataProvider->getCurrentEpisode()==7) {
        addLetterToAchantiBlock("6");
    } else if (dataProvider->getCurrentEpisode()==8) {
        addLetterToAchantiBlock("7");
    } else if (dataProvider->getCurrentEpisode()==9) {
        addLetterToAchantiBlock("8");
    }
    
    
    // open map
    getNode().runAction(
                Sequence::create(
                    DelayTime::create(0.5f),
                    CallFunc::create(
                        [=]() {
                            
                            if ( (dataProvider->getCurrentEpisode()==3)  || (dataProvider->getCurrentEpisode()==9) )  {
                                simpleAudioEngine->playEffect((WatchmanScene::PATH + "Audio/board/Granpa/woman/Granpa_Fantastic.mp3").c_str());
                            } else {
                                simpleAudioEngine->playEffect((WatchmanScene::PATH + "Audio/board/Granpa/Granpa_Fantastic.mp3").c_str());
                            }
                            
                        }),
                    DelayTime::create(5.5f),
                                 CallFunc::create(
                                                  [=]() {
                                                      simpleAudioEngine->playEffect((WatchmanScene::PATH + "Audio/sema_we_ve_gained.mp3").c_str());
                                                  }),
                     DelayTime::create(4.0f),
                                 CallFunc::create(
                                                  [=]() {
                                                      
                                                      Logger::getInstance()->logEvent("Watchman", Logger::CLOSE, "");
                                                      simpleAudioEngine->stopBackgroundMusic();
                                                      simpleAudioEngine->stopAllEffects();
                                                      
                                                      if (dataProvider->getCurrentEpisode()==9) {
                                                          VideoScene::NEXT_SCENE_CREATE_SCENE = MapScene::createScene;
                                                          VideoScene::VIDEO_PATH = "Videos/video10.mp4";
                                                          Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, VideoScene::createScene(), TRANSITION_COLOR));
                                                      } else {
                                                          dataProvider->unlockNextEpisode(); // unlock next level
                                                          Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, MapScene::createScene(), TRANSITION_COLOR));
                                                      }
                                                    
                                                  }),
                    nullptr)
             );
    
}
