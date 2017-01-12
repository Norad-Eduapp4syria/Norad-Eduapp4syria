#include "WatchmanSceneStateCalculator.h"

#include "cocos2d.h"


WatchmanSceneStateCalculator::WatchmanSceneStateCalculator(WatchmanScene &watchmanScene)
{
    watchman = &watchmanScene;
    
    dataProvider = DataProvider::getInstance();
    
    
    // watchman->state = dataProvider->getWatchmanState();
    
    
}

WatchmanSceneStateCalculator::~WatchmanSceneStateCalculator() {
    
    clearVectorGamesState();

    
}

void WatchmanSceneStateCalculator::clearVectorGamesState()
{
    for (vector<DBGame*>::iterator iterator = vectorGamesState.begin(); iterator != vectorGamesState.end(); ++iterator) {
        delete (*iterator);
    }
    vectorGamesState.clear();
}

void WatchmanSceneStateCalculator::calculateState()
{
 
    string currentPhoneme = dataProvider->getCurrentDBKnowledgeBubble()->getPhoneme();
    
       CCLOG("--calculateState START!  currentPhoneme = %s", currentPhoneme.c_str());
    
    vectorGamesState = dataProvider->getDBGames( *dataProvider->getCurrentDBKnowledgeBubble() );
    
           CCLOG("--vectorGamesState size = %lu", vectorGamesState.size() );
    
    int numberOfGames = getNumberOfGamesForPhoneme(currentPhoneme);
    
    if (dataProvider->isIntensifierGameTurn) numberOfGames = 1;
    
    if ( areAllGamesCompleted() ) {
        
        /*
        if ( isEpisodeCompleted() ) {
            watchman->mustShowNightRunnerScene = true;
            return;
        }
        */
        dataProvider->updateCurrentStatusToNext(); // get new phoneme  (e set it as new current phoneme)
        
        if ( (dataProvider->isSimplePhoneme( dataProvider->getCurrentDBKnowledgeBubble()->getPhoneme() ) )  &&
            (dataProvider->isIntensifierGameTurn == false) ) { // TODO: migliorare questo if
           
            if (dataProvider->getCurrentEpisode() == 1) {
                watchman->newPhonemeDiscovered = true;   // mark/save che il guardiano deve mostrare la fascia della nuova lettera
            }
            
            
        }
        
       
        clearVectorGamesState();
        calculateState();
        
        
    } else {
        
        if (numberOfGames == 1) {
            CCLOG("----------------------------------------------------------------mostra UN portale");
            watchman->state = WatchmanScene::SHOW_1_PORTAL;
        } else if (numberOfGames == 2) {
            CCLOG("----------------------------------------------------------------mostra DUE portali");
            watchman->state = WatchmanScene::SHOW_2_PORTALS;
        } else if (numberOfGames == 3) {
            CCLOG("----------------------------------------------------------------mostra TRE portali");
            watchman->state = WatchmanScene::SHOW_3_PORTALS;
        }
        
        if (dataProvider->isIntensifierGameTurn) {
            watchman->state = WatchmanScene::SHOW_1_PORTAL;
            CCLOG("----------------------------------------------------------------no, correzione, mostra UN solo portale");
        }
        
    }
    
    
    /*
    state = dataProvider->getWatchmanState();

    
    int currentEpisode = dataProvider->getCurrentEpisode();
    
    if (currentEpisode == 1) calculateStateEpisode1();
    else if (currentEpisode == 2) calculateStateEpisode2();
    else CCLOG("Error in WatchmanSceneStateCalculator! currentEpisode = %d", currentEpisode);
    
    
    watchman->state = state;
    
    */
}

bool WatchmanSceneStateCalculator::areAllGamesCompleted() {
    
    if ( (dataProvider->isIntensifierGameTurn) && (dataProvider->intensifierGameCompleted) ) {
        return true;
    }
    
    int completedGames = 0;
    int numbersOfGames = 0;
    
    cocos2d::UserDefault *userDef=cocos2d::UserDefault::getInstance();
    for (auto iterator = vectorGamesState.begin(); iterator != vectorGamesState.end(); ++iterator) {
        DBGame *dbgame = *iterator;
        string gameName = dbgame->getName();
        numbersOfGames++;
        if (userDef->getBoolForKey(gameName.append("_completed").c_str(), false)) {
            completedGames++;
        }
        
    }
    if (dataProvider->isIntensifierGameTurn) numbersOfGames = 1;
    
    
    if ( (dataProvider->getCurrentEpisode() == 2) && ( (numbersOfGames==3) || (dataProvider->isIntensifierGameTurn) ) ) {
        completedGames = 0;
        cocos2d::UserDefault *userDef=cocos2d::UserDefault::getInstance();
        if (userDef->getBoolForKey("WritingLetters_completedPortal1", false)) {
            completedGames++;
        }
        if (userDef->getBoolForKey("WritingLetters_completedPortal2", false)) {
            completedGames++;
        }
        if (userDef->getBoolForKey("WritingLetters_completedPortal3", false)) {
            completedGames++;
        }
    }
    
    CCLOG("numbersOfGames = %d", numbersOfGames);
    CCLOG("completedGames = %d", completedGames);
    if (numbersOfGames == completedGames) return true;
    return false;
    
}

int WatchmanSceneStateCalculator::getNumberOfGamesForPhoneme(string phoneme) {
    
    return (int)vectorGamesState.size();

}

bool WatchmanSceneStateCalculator::isEpisodeCompleted() {
    int currEp = dataProvider->getCurrentEpisode();
    string currentPhoneme = dataProvider->getCurrentDBKnowledgeBubble()->getPhoneme();
    int numEpisodeCompleted = -1;
    
    // TODO: controllare..
    if ( currentPhoneme == "Blending_ep1_w5_2" ) numEpisodeCompleted = 1;
    else if ( (currEp == 2)  && (currentPhoneme == "y") ) numEpisodeCompleted = 2;
    else if ( currentPhoneme == "Blending_ep3_w5_6") numEpisodeCompleted = 3;
    else if ( currentPhoneme == "IntensifierGame56") numEpisodeCompleted = 4;
    else if ( currentPhoneme == "extraBlending_ep5_w4_6") numEpisodeCompleted = 5;
    else if ( currentPhoneme == "bubble12_ep6") numEpisodeCompleted = 6;
    else if ( currentPhoneme == "extraOralPassagebubble20_ep7") numEpisodeCompleted = 7;
    else if ( currentPhoneme == "extraOralPassagebubble20_ep8") numEpisodeCompleted = 8;
    else if ( currentPhoneme == "extraOralPassagebubble20_ep9") numEpisodeCompleted = 9;
    
    if ( numEpisodeCompleted != -1) {
        
        CCLOG("--Episode num %d  completed!", numEpisodeCompleted);
        
        return true;
    } else {
        return false;
    }
    
}

