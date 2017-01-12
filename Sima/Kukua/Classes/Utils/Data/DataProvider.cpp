#include "DataProvider.h"
#include "../StringUtility.h"
#include <cctype>


DataProvider::DataProvider() {

	CCLOG("DataProvider()");
    
    
    
    
    
    
}

void DataProvider::init() {
    db = new DatabaseHelper("KukuaDB");
    
    
    //currentDBWatchman = new DBWatchman(1, 1);
    //currentDBKnowledgeBubble = new DBKnowledgeBubble("s", true);
    
    db->initTablesForGames();

    skin = 1;
    lastCompletedGame = "";
}

DataProvider::~DataProvider() {

	CCLOG("~DataProvider()");
    
    db->close();
    
	delete currentDBWatchman;
	delete currentDBKnowledgeBubble;
	delete currentDBGame;

    
}


void DataProvider::initUser() {
    cocos2d::UserDefault *userDef=cocos2d::UserDefault::getInstance();
    userId = userDef->getStringForKey("CURRENT_USER_ID", "noUsers");
    CCLOG("initUser - userId = %s", userId.c_str());
    db->initEpisodesTable(userId);
    
    unlockEntireEpisode(1); // togliere
    unlockEntireEpisode(2); // togliere
    unlockEntireEpisode(3); // togliere
    unlockEntireEpisode(4); // togliere
    unlockEntireEpisode(5); // togliere
    unlockEntireEpisode(6); // togliere
    unlockEntireEpisode(7); // togliere
    unlockEntireEpisode(8); // togliere
    unlockEntireEpisode(9); // togliere
    
    setStatusFromLatestUnlockedPhoneme();
    
    
}

int DataProvider::getCurrentEpisode() {
    return getCurrentDBWatchman()->getEpisode();
}

const DBKnowledgeBubble* const DataProvider::getCurrentDBKnowledgeBubble() const {
    
    if ( (isIntensifierGameTurn) && (inGame) ) {
        return currentIntensifier->getDBKnowledgeBubble();
    } else {
        return currentDBKnowledgeBubble;
    }
    
}

const DBWatchman* const DataProvider::getCurrentDBWatchman() {
    
    if ( (isIntensifierGameTurn) && (inGame) ) {
        return getDBWatchman(   *currentIntensifier->getDBKnowledgeBubble()   );
    } else {
        return currentDBWatchman;
    }
    
}

/*int DataProvider::getEpisode() const {

	return episode;

}

void DataProvider::setEpisode(int episode) {

	this->episode = episode;

}

int DataProvider::getWatchman() const {

	return watchman;

}

void DataProvider::setWatchman(int watchman) {

	this->watchman = watchman;

}*/


void DataProvider::updateCurrentStatusToNext() { // da chiamare alla fine del blending
    
    resetGamesCompleted();
    intensifierGameCompleted = false;
    
    
    CCLOG("updateCurrentStatusToNext - currentPhoneme = %s", currentDBKnowledgeBubble->getPhoneme().c_str());
    
    // unlock the next phoneme
    string nextPhoneme = getNextPhoneme();
    CCLOG("updateCurrentStatusToNext - nextPhoneme = %s", nextPhoneme.c_str());
    unlockPhoneme(nextPhoneme);
    
    DBKnowledgeBubble *dbKnowledgeBubble = new DBKnowledgeBubble(nextPhoneme, false);
    setCurrentDBWatchman( getDBWatchman( *dbKnowledgeBubble ) );
    setCurrentDBKnowledgeBubble( dbKnowledgeBubble );
    
    if (StringUtility::startsWith(nextPhoneme, "IntensifierGame")) {
        isIntensifierGameTurn = true;
        string nextPhonemeStr = nextPhoneme.substr(15, nextPhoneme.length()); // 15 is "IntensifierGame" length
        lastIntensifierGameNum = StringUtility::stringToNumber<int>(nextPhonemeStr);
        calculateIntensifier(lastIntensifierGameNum);
    } else {
        lastIntensifierGameNum = -1;
        isIntensifierGameTurn = false;
    }
    
    
}


string DataProvider::getNextPhoneme() {
    
    char **table;
    int rowTot,colTot;
    
    // get last id of current phoneme
    string queryString1;
    
    string phoneme = currentDBKnowledgeBubble->getPhoneme();
    
    CCLOG("getNextPhoneme - lastIntensifierGameNum = %d", lastIntensifierGameNum);
    
    if (lastIntensifierGameNum > 0) {
        queryString1 = string("select") + " * from episodes_"+userId+" WHERE episode = " + StringUtility::toString( getCurrentEpisode() ) + " AND game= '" + "IntensifierGame" + StringUtility::toString( lastIntensifierGameNum ) + "'";
    } else {
        queryString1 = string("select") + " * from episodes_"+userId+" WHERE episode = " + StringUtility::toString( getCurrentEpisode() ) + " AND phoneme= '" + phoneme + "'";
    }
    
    CCLOG("getNextPhoneme - queryString1 = %s", queryString1.c_str());
    
    sqlite3_get_table(db->pdb, queryString1.c_str(),&table,&rowTot,&colTot,NULL);
    string idVal = db->getCell(table, colTot, rowTot, 0).c_str();
    CCLOG("idVal = %s", idVal.c_str() );
    
    // get the next phoneme
    string queryString2 = string("select") + " * from episodes_"+userId+" WHERE ID > " + idVal + " ORDER BY ID LIMIT 1";
    sqlite3_get_table(db->pdb, queryString2.c_str(),&table,&rowTot,&colTot,NULL);
    string kbPhonemeStr = db->getCell(table, colTot, rowTot, 3).c_str();
    
     CCLOG("getNextPhoneme - queryString2 = %s", queryString2.c_str());
    
    CCLOG("getNextPhoneme - kbPhonemeStr = %s", kbPhonemeStr.c_str());
    
    return kbPhonemeStr;
}

void DataProvider::setGameCompleted(string gameName, float score, string portalStringNum) {
    lastCompletedGame = gameName;
    cocos2d::UserDefault *userDef=cocos2d::UserDefault::getInstance();
    //userDef->setBoolForKey(gameName.append("_completed").c_str(), true);
    userDef->setBoolForKey(gameName.append("_completed"+portalStringNum).c_str(), true);
    userDef->flush();
    
    updateScore(gameName, score);
    
}
string DataProvider::getLastCompletedGame() {
    return lastCompletedGame;
}
string DataProvider::getLastPortalOpened() {
    return lastPortalOpened;
}
void DataProvider::setLastPortalOpened(string portalName) {
    lastPortalOpened = portalName;
}

void DataProvider::resetGamesCompleted() {
    cocos2d::UserDefault *userDef=cocos2d::UserDefault::getInstance();
    lastCompletedGame = "";
    vector<DBGame*> currentGames = getDBGames( *getCurrentDBKnowledgeBubble() );
    for (vector<DBGame*>::iterator iterator = currentGames.begin(); iterator != currentGames.end(); ++iterator) {
        string gameName = (*iterator)->getName();
        userDef->setBoolForKey(gameName.append("_completed").c_str(), false);
    }
    
    userDef->setBoolForKey("Blending1_completed", false);
    userDef->setBoolForKey("FallingLetters_completed", false);
    userDef->setBoolForKey("PenaltyKick_completed", false);
    userDef->setBoolForKey("Platform_completed", false);
    userDef->setBoolForKey("Scale_completed", false);
    
    userDef->setBoolForKey("WordReading_completed", false);
    userDef->setBoolForKey("WritingLetters_completed", false);
    userDef->setBoolForKey("WritingLetters_completedPortal1", false);
    userDef->setBoolForKey("WritingLetters_completedPortal2", false);
    userDef->setBoolForKey("WritingLetters_completedPortal3", false);
    
    userDef->setBoolForKey("WritingMath_completed", false);
    userDef->setBoolForKey("TubGame_completed", false);
    userDef->setBoolForKey("FallingLetters_completed", false);
    userDef->setBoolForKey("MultiplicationGame_completed", false);
    
    userDef->setBoolForKey("WordReading_completed", false);

    userDef->setBoolForKey("SentenceReading_completed", false);
    userDef->setBoolForKey("WordDictation_completed", false);
    userDef->setBoolForKey("ListComprehens_completed", false);

    userDef->setBoolForKey("ShapeIdentifier_completed", false);
    userDef->setBoolForKey("ShapeNaming_completed", false);
    userDef->setBoolForKey("BodyParts_completed", false);

    userDef->setBoolForKey("ReadComprehens_completed", false);
    userDef->setBoolForKey("WordProblem_completed", false);
    
    userDef->setBoolForKey("SentenceDictation_completed", false);
    userDef->setBoolForKey("ShuffledSentence_completed", false);
    
    userDef->setBoolForKey("TubGame_completed", false);
    
    userDef->setBoolForKey("OralPassage_completed", false);
    
    userDef->setBoolForKey("NightrunnerGame_1_4_completed", false);
    
    
    
    userDef->flush();
}

void DataProvider::setCurrentDBGame(const DBGame* currentDBGame) {

	delete (this->currentDBGame);

	if (currentDBGame == nullptr) {
		this->currentDBGame = nullptr;
	} else {
		this->currentDBGame = new DBGame(*currentDBGame);
	}

}

vector<DBKnowledgeBubble*> DataProvider::getDBKnowledgeBubbles(const DBWatchman& watchman) {
    
    vector<DBKnowledgeBubble*> dbKnowledgeBubbles;
    
    char **table;
    int rowTot,colTot;
    string queryString = string("select") + " * from episodes_"+userId+" WHERE " +
    "episode = " + StringUtility::toString(watchman.getEpisode()) +
    " AND watchman = " + StringUtility::toString(watchman.getNumber());
    
    sqlite3_get_table(db->pdb, queryString.c_str(),&table,&rowTot,&colTot,NULL);
    
    int i;
    string prevPhoneme = "";
    for (i = 1; i<= rowTot; i++) {
        string phoneme = db->getCell(table, colTot, i, 3);
        
        if ( getCurrentEpisode() >= 4 ) {
            if ( StringUtility::startsWith(phoneme, "bubble") ) {
                if (phoneme != prevPhoneme) {
                    prevPhoneme = phoneme;
                    string kbStr = db->getCell(table, colTot, i, 4).c_str();
                    bool kb = StringUtility::stringToBool<bool>( kbStr );
                    dbKnowledgeBubbles.push_back(new DBKnowledgeBubble( db->getCell(table, colTot, i, 3).c_str() , kb ));
                }
            }
        } else if ( ( getCurrentEpisode() == 2 ) || ( getCurrentEpisode() == 3 ) ) {
            if ( (StringUtility::endsWith(phoneme, "writing") == false )  && ( isSimplePhoneme(phoneme) ) ) {
                if (phoneme != prevPhoneme) {
                    prevPhoneme = phoneme;
                    string kbStr = db->getCell(table, colTot, i, 4).c_str();
                    bool kb = StringUtility::stringToBool<bool>( kbStr );
                    dbKnowledgeBubbles.push_back(new DBKnowledgeBubble( db->getCell(table, colTot, i, 3).c_str() , kb ));
                }
            }
        } else {
            if ( isSimplePhoneme(phoneme) ) {
                if (phoneme != prevPhoneme) {
                    prevPhoneme = phoneme;
                    string kbStr = db->getCell(table, colTot, i, 4).c_str();
                    bool kb = StringUtility::stringToBool<bool>( kbStr );
                    dbKnowledgeBubbles.push_back(new DBKnowledgeBubble( db->getCell(table, colTot, i, 3).c_str() , kb ));
                }
            }
        }
    }
    
    sqlite3_free_table(table);
    
    return dbKnowledgeBubbles;
    
}


vector<DBKnowledgeBubble*> DataProvider::getDBKnowledgeBubbles(int episode) {
    
    vector<DBKnowledgeBubble*> dbKnowledgeBubbles;
    
    char **table;
    int rowTot,colTot;
    string queryString = string("select") + " * from episodes_"+userId+" WHERE " +
    "episode = " + StringUtility::toString(episode );
    
    sqlite3_get_table(db->pdb, queryString.c_str(),&table,&rowTot,&colTot,NULL);
    
    int i;
    string prevPhoneme = "";
    for (i = 1; i<= rowTot; i++) {
        string phoneme = db->getCell(table, colTot, i, 3);
        
        if ( getCurrentEpisode() >= 4 ) {
            if ( StringUtility::startsWith(phoneme, "bubble") ) {
                if (phoneme != prevPhoneme) {
                    prevPhoneme = phoneme;
                    string kbStr = db->getCell(table, colTot, i, 4).c_str();
                    bool kb = StringUtility::stringToBool<bool>( kbStr );
                    dbKnowledgeBubbles.push_back(new DBKnowledgeBubble( db->getCell(table, colTot, i, 3).c_str() , kb ));
                }
            }
        } else if ( ( getCurrentEpisode() == 2 ) || ( getCurrentEpisode() == 3 ) ) {
            if ( (StringUtility::endsWith(phoneme, "writing") == false )  && ( isSimplePhoneme(phoneme) ) ) {
                if (phoneme != prevPhoneme) {
                    prevPhoneme = phoneme;
                    string kbStr = db->getCell(table, colTot, i, 4).c_str();
                    bool kb = StringUtility::stringToBool<bool>( kbStr );
                    dbKnowledgeBubbles.push_back(new DBKnowledgeBubble( db->getCell(table, colTot, i, 3).c_str() , kb ));
                }
            }
        } else {
            if ( isSimplePhoneme(phoneme) ) {
                if (phoneme != prevPhoneme) {
                    prevPhoneme = phoneme;
                    string kbStr = db->getCell(table, colTot, i, 4).c_str();
                    bool kb = StringUtility::stringToBool<bool>( kbStr );
                    dbKnowledgeBubbles.push_back(new DBKnowledgeBubble( db->getCell(table, colTot, i, 3).c_str() , kb ));
                }
            }
        }
        
    }
    
    sqlite3_free_table(table);
    
    return dbKnowledgeBubbles;
    
}


vector<DBKnowledgeBubble*> DataProvider::getUnlockedDBKnowledgeBubbles(const DBWatchman& watchman) {
    
    vector<DBKnowledgeBubble*> dbKnowledgeBubbles;
    
    char **table;
    int rowTot,colTot;
    string queryString = string("select") + " * from episodes_"+userId+" WHERE " +
    "episode = " + StringUtility::toString(watchman.getEpisode()) +
    " AND watchman = " + StringUtility::toString(watchman.getNumber()) +
    " AND locked = 0";
    
    sqlite3_get_table(db->pdb, queryString.c_str(),&table,&rowTot,&colTot,NULL);
    
    int i;
    string prevPhoneme = "";
    for (i = 1; i<= rowTot; i++) {
        string phoneme = db->getCell(table, colTot, i, 3);
        
        if (getCurrentEpisode() >= 4) {            
            if ( StringUtility::startsWith(phoneme, "bubble")) {
                if (phoneme != prevPhoneme) {
                    prevPhoneme = phoneme;
                    string kbStr = db->getCell(table, colTot, i, 4).c_str();
                    bool kb = StringUtility::stringToBool<bool>( kbStr );
                    dbKnowledgeBubbles.push_back(new DBKnowledgeBubble( db->getCell(table, colTot, i, 3).c_str() , kb ));
                }
            }
        } else {
            if ( isSimplePhoneme(phoneme) ) {
                if (phoneme != prevPhoneme) {
                    prevPhoneme = phoneme;
                    string kbStr = db->getCell(table, colTot, i, 4).c_str();
                    bool kb = StringUtility::stringToBool<bool>( kbStr );
                    dbKnowledgeBubbles.push_back(new DBKnowledgeBubble( db->getCell(table, colTot, i, 3).c_str() , kb ));
                }
            }
        }
    }
    
    sqlite3_free_table(table);
    
    return dbKnowledgeBubbles;
    
}

vector<DBGame*> DataProvider::getDBGames(const DBKnowledgeBubble& dbDBKnowledgeBubble) {
    
    vector<DBGame*> dbGames;
    
    char **table;
    int rowTot,colTot;
    string queryString = string("select") + " * from episodes_"+userId+" WHERE " +
    "episode = " + StringUtility::toString( getCurrentEpisode() ) +
    " AND phoneme = '" + StringUtility::toString(dbDBKnowledgeBubble.getPhoneme()) + "'";
    
    // CCLOG("queryString: = %s", queryString.c_str());
    
    sqlite3_get_table(db->pdb, queryString.c_str(),&table,&rowTot,&colTot,NULL);
    
    int i;
    for (i = 1; i<= rowTot; i++) {
        string skinStr = db->getCell(table, colTot, i, 6).c_str();
        int skin = StringUtility::stringToNumber<int>( skinStr );
        
        dbGames.push_back(new DBGame( db->getCell(table, colTot, i, 5).c_str() , skin ));
        // CCLOG("-----gioco = %s",   db->getCell(table, colTot, i, 5).c_str()  );
    }
    
    sqlite3_free_table(table);
    
    return dbGames;    

}


bool DataProvider::unlockPhoneme(string phoneme) {
    
    char **table;
    int rowTot,colTot;
    
    string updateString = string("UPDATE") + " episodes_"+userId+" SET locked = 0 WHERE episode = " + StringUtility::toString( getCurrentEpisode() ) + " AND phoneme= '" + phoneme + "'";
    int result = sqlite3_exec(db->pdb, updateString.c_str(),NULL, NULL, NULL);
    if (result == SQLITE_OK)
        return true;
    else
        return false;
    
    
    //sqlite3_free_table(table);
}

// update 'currentDBWatchman' and 'currentDBKnowledgeBubble'
void DataProvider::setStatusFromLatestUnlockedPhoneme() {
    
    char **table;
    int rowTot,colTot;
    string queryString = string("select") + " * from episodes_"+userId+" WHERE " + "locked = 0";
    CCLOG("setStatusFromLatestUnlockedPhoneme - queryString = %s", queryString.c_str());
    sqlite3_get_table(db->pdb, queryString.c_str(),&table,&rowTot,&colTot,NULL);
    
    // watchman
    string watchmanEpStr = db->getCell(table, colTot, rowTot, 1).c_str();
    int watchmanEp = StringUtility::stringToNumber<int>( watchmanEpStr );
    
    string watchmanNumStr = db->getCell(table, colTot, rowTot, 2).c_str();
    int watchmanNum = StringUtility::stringToNumber<int>( watchmanNumStr );
    
    currentDBWatchman = new DBWatchman(watchmanEp, watchmanNum);
    
    // Knowledge Bubble
    string kbPhonemeStr = db->getCell(table, colTot, rowTot, 3).c_str();
    
    string kbLockedStr = db->getCell(table, colTot, rowTot, 4).c_str();
    bool kbLocked = StringUtility::stringToBool<bool>( kbLockedStr ); // anyway, it will be true
    CCLOG("current phoneme = %s", kbPhonemeStr.c_str() );
    intensifierGameCompleted = false;
    currentDBKnowledgeBubble = new DBKnowledgeBubble(kbPhonemeStr, kbLocked );
    if (StringUtility::startsWith(kbPhonemeStr, "IntensifierGame")) {
        isIntensifierGameTurn = true;
        string kbPhonemeStrTemp = kbPhonemeStr.substr(15, kbPhonemeStr.length()); // 15 is "IntensifierGame" length
        lastIntensifierGameNum = StringUtility::stringToNumber<int>(kbPhonemeStrTemp);
        calculateIntensifier(lastIntensifierGameNum);
    } else {
        lastIntensifierGameNum = -1;
        isIntensifierGameTurn = false;
    }
    
    sqlite3_free_table(table);
}


string DataProvider::getRandomWrongPhoneme(string correctPhoneme, bool includeSyllabes, int onlyFromEpisodeNum) {
   
    vector<string> unlockedPhonemes;
    
    char **table;
    int rowTot,colTot;
    string queryString;
    
    if (onlyFromEpisodeNum == -1) {
        queryString = string("select") + " * from episodes_"+userId+" WHERE episode = " + StringUtility::toString( getCurrentEpisode() ) + " AND locked = 0";
        
    } else {
        queryString = string("select") + " * from episodes_"+userId+" WHERE episode = " + StringUtility::toString( onlyFromEpisodeNum ) + " AND locked = 0";
    }

    sqlite3_get_table(db->pdb, queryString.c_str(),&table,&rowTot,&colTot,NULL);
    
    
    bool correctPhonemeIsNumber = isNumber(correctPhoneme);
    char * p ;
    strtol(correctPhoneme.c_str(), &p, 10) ;
    int i;
    for (i = 1; i<= rowTot; i++) {
        string phoneme = db->getCell(table, colTot, i, 3);
        
        if ( correctPhonemeIsNumber == isNumber(phoneme) ) {
            if ( isSimplePhoneme(phoneme) == false ) {
                if (includeSyllabes) unlockedPhonemes.push_back( phoneme );
            } else {
                unlockedPhonemes.push_back( phoneme );
            }
        }
    }
    sqlite3_free_table(table);
    
    
    // remove duplicates
    sort( unlockedPhonemes.begin(), unlockedPhonemes.end() );
    unlockedPhonemes.erase( unique( unlockedPhonemes.begin(), unlockedPhonemes.end() ), unlockedPhonemes.end() );
    
    
    // remove correct phoneme
    unlockedPhonemes.erase(std::remove(unlockedPhonemes.begin(), unlockedPhonemes.end(), correctPhoneme), unlockedPhonemes.end());
    
    if ( unlockedPhonemes.size() == 0) return "b"; // for the first letter
    // get random element
    srand( static_cast<unsigned int>(time(NULL)));
    int randomIndex = rand() % unlockedPhonemes.size();
    string randomElement = unlockedPhonemes[randomIndex];
    
    if ( (correctPhoneme == "th1") && (randomElement == "th2") ) return getRandomWrongPhoneme(correctPhoneme, includeSyllabes);
    if ( (correctPhoneme == "th2") && (randomElement == "th1") ) return getRandomWrongPhoneme(correctPhoneme, includeSyllabes);
    if ( (correctPhoneme == "oo1") && (randomElement == "oo2") ) return getRandomWrongPhoneme(correctPhoneme, includeSyllabes);
    if ( (correctPhoneme == "oo2") && (randomElement == "oo1") ) return getRandomWrongPhoneme(correctPhoneme, includeSyllabes);
    
    if ( getCurrentEpisode() == 2 ) {
        if ( unlockedPhonemes.size() == 1)  return "b";
        randomElement = randomElement.substr(0, randomElement.find("_"));
    }
    if ( getCurrentEpisode() == 1 ) {
        string::size_type idxEp1 = randomElement.find("#ep1");
        if (idxEp1 != string::npos)
            randomElement.erase(idxEp1, 4); // 4 is length of "#ep1"
    }
    
    return randomElement;
}



// TODO zzzz
string DataProvider::getRandomPhonemeForNightrunnerGame_1_4(int episodeNum) {
    

    char **table;
    int rowTot,colTot;
    
    string queryString;
    
    if ( (episodeNum == 1) || (episodeNum == 2) ) {
        
        queryString = string("select") +
            " * from episodes_"+userId+" WHERE episode = " +
            StringUtility::toString( episodeNum ) +
            " AND game NOT LIKE 'IntensifierGame%'" +
            " AND game NOT LIKE 'Photo%'" +
            " AND game NOT LIKE 'Health%'" +
            " AND game NOT LIKE 'Social%'" +
            " AND game NOT LIKE 'Emotional%'" +
            " AND game NOT LIKE 'Video%'" +
            " AND game NOT LIKE 'Blending%'" +
            " ORDER BY RANDOM() LIMIT 1";
        
    } else if (episodeNum == 3) {
        queryString = string("select") +
        " * from blending WHERE " +
        " phoneme LIKE 'Blending_ep3%'" +
        " ORDER BY RANDOM() LIMIT 1";
    } else if (episodeNum == 4) {
        queryString = string("select") +
        " * from blending WHERE " +
        " phoneme LIKE '%_ep4%'" +
        " ORDER BY RANDOM() LIMIT 1";
    }

    
    
    sqlite3_get_table(db->pdb, queryString.c_str(),&table,&rowTot,&colTot,NULL);
    
    string phoneme;
    
    if ( (episodeNum == 1) || (episodeNum == 2) ) {
        phoneme = db->getCell(table, colTot, rowTot, 3).c_str();
        
    } else if ( (episodeNum == 3) || (episodeNum == 4) ) {
        phoneme = db->getCell(table, colTot, rowTot, 2).c_str();
    }
    
    
    sqlite3_free_table(table);
    
    
    
    if ( episodeNum == 1 ) {
        string::size_type idxEp1 = phoneme.find("#ep1");
        if (idxEp1 != string::npos)
            phoneme.erase(idxEp1, 4); // 4 is length of "#ep1"
    } else if ( episodeNum == 2 ) {
        phoneme = phoneme.substr(0, phoneme.find("_"));
    }
    
    phoneme = checkAndCorrectDuplicatePhoneme(phoneme);
    
    return phoneme;
}


bool DataProvider::isNumber(std::string & s)
{
    if ( (s == "10-11") || (s == "12-13") || (s == "14-15") || (s == "16-17") || (s == "18-20") ) return true;
    if ( (s == "bubble21-22_ep4") || (s == "bubble23-24_ep4") || (s == "bubble25-26_ep4") || (s == "bubble27-28_ep4") || (s == "bubble29-30_ep4") ) return true;
    return !s.empty() && std::find_if(s.begin(),s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

void DataProvider::setWatchmanState(string status) {
    cocos2d::UserDefault *userDef=cocos2d::UserDefault::getInstance();
    userDef->setStringForKey("WATCHMAN_STATUS", status);
    userDef->flush();
}
void DataProvider::setWatchmanReaction(string reaction) {
    inGame = false;
    intensifierGameCompleted = false;
    if (isIntensifierGameTurn) {
        if (reaction == "GOOD_REACTION") intensifierGameCompleted = true;
    }
    cocos2d::UserDefault *userDef=cocos2d::UserDefault::getInstance();
    userDef->setStringForKey("WATCHMAN_REACTION", reaction);
    userDef->flush();
}

string DataProvider::getWatchmanState() {
    cocos2d::UserDefault *userDef=cocos2d::UserDefault::getInstance();
    return userDef->getStringForKey("WATCHMAN_STATUS", "FIRST_TIME");
}

string DataProvider::getWatchmanReaction() {
    cocos2d::UserDefault *userDef=cocos2d::UserDefault::getInstance();
    return userDef->getStringForKey("WATCHMAN_REACTION", "NONE_REACTION");
}

vector<string> DataProvider::getVectorWordsForGame() {
    return _vectorWordsForGame;
}

void DataProvider::setVectorWordsForGame(vector<string> vectorWordsForGame) {
    _vectorWordsForGame = vectorWordsForGame;
}

void DataProvider::setCurrentDBKnowledgeBubble(const DBKnowledgeBubble* knowledgeBubble) {
    
    delete (this->currentDBKnowledgeBubble);
                              
    if (knowledgeBubble == nullptr) {
        this->currentDBKnowledgeBubble = nullptr;
    } else {
        this->currentDBKnowledgeBubble = new DBKnowledgeBubble(*knowledgeBubble);
    }
}

void DataProvider::setCurrentDBWatchman(const DBWatchman* watchman) {
    
    delete (this->currentDBWatchman);
    
    if (watchman == nullptr) {
        this->currentDBWatchman = nullptr;
    } else {
        this->currentDBWatchman = new DBWatchman(*watchman);
    }
}

DBWatchman* DataProvider::getDBWatchman(DBKnowledgeBubble kb) {
   // kb->getPhoneme();
    
    
    char **table;
    int rowTot,colTot;
    //string queryString = string("select") + " * from episodes_"+userId+" WHERE episode = " + StringUtility::toString( getCurrentEpisode() ) + " AND phoneme = '" + StringUtility::toString(kb.getPhoneme()) + "'";
    string queryString = string("select") + " * from episodes_"+userId+" WHERE " +
    " phoneme = '" + StringUtility::toString(kb.getPhoneme()) + "'";
    
    
    sqlite3_get_table(db->pdb, queryString.c_str(),&table,&rowTot,&colTot,NULL);
    
    string episodeStr;
    string watchmanStr;
    int i;
    for (i = 1; i<= rowTot; i++) {
        episodeStr = db->getCell(table, colTot, i, 1);
        watchmanStr = db->getCell(table, colTot, i, 2);
    }
    
    sqlite3_free_table(table);
    
    return new DBWatchman( StringUtility::stringToNumber<int>(episodeStr) , StringUtility::stringToNumber<int>(watchmanStr) );
}

string DataProvider::getWordForPhoneme(string phoneme) {
    char **table;
    int rowTot,colTot;
    string queryString = string("select") + " * from wordsForPhonemes WHERE " + "phoneme = '" + phoneme + "'";
    sqlite3_get_table(db->pdb, queryString.c_str(),&table,&rowTot,&colTot,NULL);
    string word;
    if (rowTot == 0) {
        word = "empty";
    } else {
        word = db->getCell(table, colTot, 1, 2);
    }
    sqlite3_free_table(table);
    return word;
}

bool DataProvider::isSimplePhoneme(string phoneme) {
    if ( db->isBlending(phoneme) ) return false;
    if (StringUtility::startsWith(phoneme, "IntensifierGame")) return false;
    if (StringUtility::startsWith(phoneme, "Photo")) return false;
    if (StringUtility::startsWith(phoneme, "HealthGame")) return false;
    if (StringUtility::startsWith(phoneme, "SocialWeal")) return false;
    if (StringUtility::startsWith(phoneme, "Emotional")) return false;
    if (StringUtility::startsWith(phoneme, "Video")) return false;
    if (StringUtility::startsWith(phoneme, "Blending")) return false;
    if (StringUtility::startsWith(phoneme, "WritingEp3")) return false;
    return true;
}

int DataProvider::getRandomSkin(int maxVal) {
    srand( static_cast<unsigned int>(time(NULL)));
    int randomSkin = 1+ rand() % maxVal;
    return randomSkin;
}

int DataProvider::getSkin() {
    return skin;
}
void DataProvider::setSkin(int skinNumber) {
    skin = skinNumber;
}


void DataProvider::unlockEntireEpisode(int episodeNum) { // only for debug purpose
    setCurrentDBWatchman(new DBWatchman(episodeNum, 1));
    auto dbKnowledgeBubbles = getDBKnowledgeBubbles(episodeNum);
    
    bool updated = true;
    sqlite3_exec(db->pdb, "BEGIN TRANSACTION;", NULL, NULL, NULL);
    
    for (auto iterator = dbKnowledgeBubbles.begin(); iterator != dbKnowledgeBubbles.end(); ++iterator) {
       updated = unlockPhoneme( (*iterator)->getPhoneme() );
    }
    
    if (updated)
         sqlite3_exec(db->pdb, "COMMIT;", NULL, NULL, NULL);
    else
         sqlite3_exec(db->pdb, "ROLLBACK;", NULL, NULL, NULL);
    
    setNightRunnerUnlockedForEpisode(episodeNum);
}

void DataProvider::setRandomState(int episode) {
    
    char **table;
    int rowTot,colTot;
    
    string queryString = string("select") +
    " * from episodes_"+userId+" WHERE episode = " +
    StringUtility::toString( episode ) + " ORDER BY RANDOM() LIMIT 1";

    
    sqlite3_get_table(db->pdb, queryString.c_str(),&table,&rowTot,&colTot,NULL);
    
    
    string watchman = db->getCell(table, colTot, rowTot, 2).c_str();
    string phoneme = db->getCell(table, colTot, rowTot, 3).c_str();
    string game = db->getCell(table, colTot, rowTot, 5).c_str();
    string skin = db->getCell(table, colTot, rowTot, 6).c_str();
    
    int watchmanInt = StringUtility::stringToNumber<int>(watchman);
    int skinInt = StringUtility::stringToNumber<int>(skin);
    
    
    setCurrentDBWatchman( new DBWatchman(episode, watchmanInt) );
    setCurrentDBGame( new DBGame( game , skinInt ) );
    setCurrentDBKnowledgeBubble( new DBKnowledgeBubble(phoneme, true ));
    
    /*
    setCurrentDBWatchman( new DBWatchman(1, 1) );
    setCurrentDBGame( new DBGame( "Blending1" , 1 ) );
    setCurrentDBKnowledgeBubble( new DBKnowledgeBubble("sa", true ));
    */
    
    
    sqlite3_free_table(table);
}



void DataProvider::updateScore(string gameName, float score) {
  
    char **table;
    int rowTot,colTot;
    string updateString = string("UPDATE") + " episodes_"+userId+" SET score = " +  StringUtility::toString( score ) +
    " WHERE episode = " + StringUtility::toString( getCurrentEpisode() ) +
    " AND phoneme= '" + getCurrentDBKnowledgeBubble()->getPhoneme() + "'";
    " AND game= '" + gameName + "'";
    sqlite3_get_table(db->pdb, updateString.c_str(),&table,&rowTot,&colTot,NULL);
    sqlite3_free_table(table);
}


string DataProvider::checkAndCorrectDuplicatePhoneme(string phoneme) {
    if (phoneme == "oo1") return "oo";
    if (phoneme == "oo2") return "oo";
    if (phoneme == "th1") return "th";
    if (phoneme == "th2") return "th";
    return phoneme;
}


void DataProvider::unlockNextEpisode() {
    
    resetGamesCompleted();
    
    
    char **table;
    int rowTot,colTot;
    string updateString = string("UPDATE") + " episodes_"+userId+" SET locked = 0 WHERE episode=1 AND phoneme= 'Video1'";
    
    int currEpisode = getCurrentEpisode();
    int nextEpisodeNum = currEpisode + 1;
    string nextEpisodeNumStr = StringUtility::toString(nextEpisodeNum);
    
    // unlock first record of next episode
    updateString = string("UPDATE") + " episodes_"+userId+" SET locked = 0 WHERE episode="+nextEpisodeNumStr+" AND phoneme= 'Video"+nextEpisodeNumStr+"'";
    
    sqlite3_get_table(db->pdb, updateString.c_str(),&table,&rowTot,&colTot,NULL);
    sqlite3_free_table(table);
}


/*
float DataProvider::getHomeButtonYPosition(cocos2d::Node* rootNode, float homeButtonHeight) {
 
    float winHeight = cocos2d::Director::getInstance()->getWinSize().height;
    float rootNodeHeight = rootNode->getBoundingBox().size.height;
    
    float y = winHeight;
    if ( winHeight > rootNodeHeight ) { // like iPad
        float delta = (winHeight-rootNodeHeight) / 2;
        y = rootNodeHeight + delta - (homeButtonHeight/2);
    }
    y = y - (homeButtonHeight /2);
    
    return y;
}
*/


// calculate the game with the wroste score
DBKnowledgeBubbleAndGame* DataProvider::calculateIntensifier(int intensifierNum) {
    
    int episode = getCurrentEpisode();
    
    delete (this->currentIntensifier);
    
    // init for queries
    int prevIntensifierNum = intensifierNum-1;
    char **table;
    int rowTot,colTot;
    
    string queryStringForRecords;
    
    if (intensifierNum == -1) {
        // nightrunner case
        
        queryStringForRecords = string("select") +
        " * from episodes_"+userId+" WHERE episode = " +
        StringUtility::toString( episode ) +
        " AND game NOT LIKE 'IntensifierGame%'" +
        " AND game NOT LIKE 'Photo%'" +
        " AND game NOT LIKE 'Health%'" +
        " AND game NOT LIKE 'Social%'" +
        " AND game NOT LIKE 'Emotional%'" +
        " AND game NOT LIKE 'Video%'" +
        // " ORDER BY RANDOM() LIMIT 1"; //togliere
        " ORDER BY score LIMIT 1"; // ok mettere
        
    } else {
        
        if (episode >= 7) {
            
            // get all games
            queryStringForRecords = string("select") +
            " * from episodes_"+userId+" WHERE locked = 0" +
            " AND game NOT LIKE 'IntensifierGame%'" +
            " AND game NOT LIKE 'Photo%'" +
            " AND game NOT LIKE 'Health%'" +
            " AND game NOT LIKE 'Social%'" +
            " AND game NOT LIKE 'Emotional%'" +
            " AND game NOT LIKE 'Video%'" +
            // " ORDER BY RANDOM() LIMIT 1"; //togliere
            " ORDER BY score LIMIT 1"; // ok mettere
            
        } else {
            
            // normal case....
            
            string idPrevIntensifierGame = "0";
            if (intensifierNum != 1) {
                // get id of previous IntensifierGame
                string queryStringForPrev = string("select * from episodes_"+userId+" WHERE ") +
                "phoneme = '" + StringUtility::toString( "IntensifierGame"+StringUtility::toString(prevIntensifierNum) ) + "'";
                sqlite3_get_table(db->pdb, queryStringForPrev.c_str(),&table,&rowTot,&colTot,NULL);
                idPrevIntensifierGame = db->getCell(table, colTot, rowTot, 0).c_str();
            }
            
            // get id of current IntensifierGame
            string queryStringForCurrent = string("select * from episodes_"+userId+" WHERE ") +
            "phoneme = '" + StringUtility::toString( "IntensifierGame"+StringUtility::toString(intensifierNum) ) + "'";
            sqlite3_get_table(db->pdb, queryStringForCurrent.c_str(),&table,&rowTot,&colTot,NULL);
            string idCurrentIntensifierGame = db->getCell(table, colTot, rowTot, 0).c_str();
            
            // last query
            queryStringForRecords = string("select") +
            " * from episodes_"+userId+" WHERE episode = " +
            StringUtility::toString( episode ) +
            " AND game NOT LIKE 'IntensifierGame%'" +
            " AND game NOT LIKE 'Photo%'" +
            " AND game NOT LIKE 'Health%'" +
            " AND game NOT LIKE 'Social%'" +
            " AND game NOT LIKE 'Emotional%'" +
            " AND game NOT LIKE 'Video%'" +
            " AND watchman = " +
            StringUtility::toString( currentDBWatchman->getNumber() ) +
            " AND ID > " + idPrevIntensifierGame + " AND ID < " + idCurrentIntensifierGame +
            // " ORDER BY RANDOM() LIMIT 1"; //togliere
            " ORDER BY score LIMIT 1"; // ok mettere
            
        }
        
        
    }
    
    sqlite3_get_table(db->pdb, queryStringForRecords.c_str(),&table,&rowTot,&colTot,NULL);
    
    string phoneme = db->getCell(table, colTot, rowTot, 3).c_str();
    string game = db->getCell(table, colTot, rowTot, 5).c_str();
    
    currentIntensifier = new DBKnowledgeBubbleAndGame(
                                                      new DBKnowledgeBubble( phoneme , true ),
                                                      new DBGame( game , 1 )
                                                      );
    
    sqlite3_free_table(table);
    
    
    return currentIntensifier;
}

// for Users

void DataProvider::createUser(string id, string path){
    
    // add users to users table
    string creationString = string("INSERT INTO") + " users (userId,photoPath) VALUES ('" + id + "','" + path + "')";
    CCLOG("createUser creationString = %s", creationString.c_str() );
    sqlite3_exec(db->pdb, creationString.c_str() ,NULL,NULL,NULL);
    
    cocos2d::UserDefault *userDef=cocos2d::UserDefault::getInstance();
    userDef->setStringForKey("CURRENT_USER_ID", id);
    userDef->flush();
    
    userId = id;
}

string DataProvider::getUserPhotoPath(string id) {
    
    char **table;
    int rowTot,colTot;
    string queryString = string("select") + " * from users WHERE userId = '" + id + "'";
   
    sqlite3_get_table(db->pdb, queryString.c_str(),&table,&rowTot,&colTot,NULL);
    
    string val = "";
    if (rowTot>0) {
        val = db->getCell(table, colTot, rowTot, 2).c_str();
    }
    sqlite3_free_table(table);
    
    return val;
}


vector<string> DataProvider::getAllUsersId() {
    
    vector<string> idVector;
    
    char **table;
    int rowTot,colTot;
    string queryString = string("select") + " * from users";
    
    sqlite3_get_table(db->pdb, queryString.c_str(),&table,&rowTot,&colTot,NULL);
    
    int i;
    for (i = 1; i<= rowTot; i++) {
        idVector.push_back( db->getCell(table, colTot, i, 1).c_str()  );
    }
    
    sqlite3_free_table(table);
    
    return idVector;
    
}

// for Map
string DataProvider::getSemaInitialPortalCode() {
    return semaInitialPortalCode;
}
void DataProvider::setSemaInitialPortalCode(string initialPortalCode) {
    semaInitialPortalCode = initialPortalCode;
}

string DataProvider::getSemaInitialAction() {
    return semaInitialAction;
}
void DataProvider::setSemaInitialAction(string initialAction) {
    semaInitialAction = initialAction;
}

bool DataProvider::getMustUnlockNewPortalMap() {
    return mustUnlockNewPortal;
}
void DataProvider::setMustUnlockNewPortalMap(bool value) {
    mustUnlockNewPortal = value;
}

void DataProvider::setNightRunnerUnlockedForEpisode(int numEpisode) {
    cocos2d::UserDefault *userDef=cocos2d::UserDefault::getInstance();
    string nightrunnerStr = userId+"nightrunner_unlocked_";
    string numEpisodeStr = StringUtility::toString(numEpisode);
    userDef->setBoolForKey(nightrunnerStr.append(numEpisodeStr).c_str(), true);
    userDef->flush();
}

bool DataProvider::isNightRunnerUnlockedForEpisode(int numEpisode) {
    cocos2d::UserDefault *userDef=cocos2d::UserDefault::getInstance();
    string nightrunnerStr = userId+"nightrunner_unlocked_";
    string numEpisodeStr = StringUtility::toString(numEpisode);
    bool toReturn = userDef->getBoolForKey(nightrunnerStr.append(numEpisodeStr).c_str(), false);
    return toReturn;
}



bool DataProvider::nextPhonemeIsLocked() {
    // TODO
    return false;
}

int DataProvider::getLastUnlockedEpisodeNum() {
    
    char **table;
    int rowTot,colTot;
    string queryString = string("select") + " * from episodes_"+userId+" WHERE " + "locked = 0";
    sqlite3_get_table(db->pdb, queryString.c_str(),&table,&rowTot,&colTot,NULL);
    
    string epStr = db->getCell(table, colTot, rowTot, 1).c_str();
    int ep = StringUtility::stringToNumber<int>( epStr );
    
    sqlite3_free_table(table);
    
    return ep;
}
int DataProvider::getLastUnlockedWatchmanNum() {
    char **table;
    int rowTot,colTot;
    string queryString = string("select") + " * from episodes_"+userId+" WHERE " + "locked = 0";
    sqlite3_get_table(db->pdb, queryString.c_str(),&table,&rowTot,&colTot,NULL);
    
    string watchmanNumStr = db->getCell(table, colTot, rowTot, 2).c_str();
    int watchmanNum = StringUtility::stringToNumber<int>( watchmanNumStr );
    
    sqlite3_free_table(table);
    return watchmanNum;
}


string DataProvider::getPhonemeForPortalCode(string portalCode) {
    
    vector<string> portalCodeSplitted = StringUtility::split(portalCode, '-');
    string episodeNumStr = portalCodeSplitted.at(0);
    string watchmanNumStr = portalCodeSplitted.at(1);
    
    char **table;
    int rowTot,colTot;
  
    
    string queryString = string("select") +
    " * from episodes_"+userId+" WHERE episode = " + episodeNumStr +
    " AND watchman = " + watchmanNumStr +
    " LIMIT 1";
    
    sqlite3_get_table(db->pdb, queryString.c_str(),&table,&rowTot,&colTot,NULL);
    
    string phonemeToReturn = db->getCell(table, colTot, rowTot, 3).c_str();

    sqlite3_free_table(table);
    return phonemeToReturn;

}
//



bool DataProvider::areProportionsLikeIpad(cocos2d::Node* rootNode) {
    
    float winHeight = cocos2d::Director::getInstance()->getWinSize().height;
    float rootHieght = rootNode->getBoundingBox().size.height;
    
    if ( winHeight < rootHieght ) {
        return false;
    } else {
        return true;
    }
    
    return false;
}


vector<string> DataProvider::getWordsForGame(string phoneme, string tableName) {
    
    vector<string> wordsVector;
    
    char **table;
    int rowTot,colTot;
    string queryString = string("select") + " * from "+tableName+" WHERE " +
    "phoneme = '" + phoneme + "'";
    
    sqlite3_get_table(db->pdb, queryString.c_str(),&table,&rowTot,&colTot,NULL);
    
    int i;
    for (i = 1; i<= rowTot; i++) {
        wordsVector.push_back( db->getCell(table, colTot, i, 2).c_str()  );
    }
    
    sqlite3_free_table(table);
    
    return wordsVector;
    
}
