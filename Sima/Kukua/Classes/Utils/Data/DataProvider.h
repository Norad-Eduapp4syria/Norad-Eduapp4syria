#pragma once

#include "../Singleton.h"
#include "DBKnowledgeBubble.h"
#include "DBGame.h"
#include "DBKnowledgeBubbleAndGame.h"
#include "DBWatchman.h"
#include "DatabaseHelper.h"

class DataProvider : public Singleton<DataProvider> {
	friend class Singleton<DataProvider>;

public:
	~DataProvider();
    void init();
	/*int getEpisode() const;
	void setEpisode(int episode);
	int getWatchman() const;
	void setWatchman(int watchman);*/
    void setStatusFromLatestUnlockedPhoneme();
    int getCurrentEpisode();
	void setCurrentDBGame(const DBGame* currentDBGame);
    void setCurrentDBKnowledgeBubble(const DBKnowledgeBubble* knowledgeBubble);
    void setCurrentDBWatchman(const DBWatchman* watchman);
    
	const DBWatchman* const getCurrentDBWatchman();
	const DBKnowledgeBubble* const getCurrentDBKnowledgeBubble() const;
	DBGame* getCurrentDBGame();
	vector<DBKnowledgeBubble*> getDBKnowledgeBubbles(const DBWatchman& watchman);
    vector<DBKnowledgeBubble*> getDBKnowledgeBubbles(int episode);
    vector<DBKnowledgeBubble*> getUnlockedDBKnowledgeBubbles(const DBWatchman& watchman);
	vector<DBGame*> getDBGames(const DBKnowledgeBubble& dbDBKnowledgeBubble);
    // float getHomeButtonYPosition(cocos2d::Node* rootNode, float homeButtonHeight = 80);
    void setRandomState(int episode);
    void setGameCompleted(string gameName, float score=101.0f, string portalStringNum="");
    void resetGamesCompleted();
    bool isSimplePhoneme(string phoneme);
    void updateCurrentStatusToNext();
    string getRandomWrongPhoneme(string correctPhoneme, bool includeSyllabes = false, int onlyFromEpisodeNum=-1);
    string getRandomPhonemeForNightrunnerGame_1_4(int episodeNum);
    bool isNumber(std::string & s);
    void setWatchmanState(string status);
    string getWatchmanState();
    void setWatchmanReaction(string reaction);
    string getWatchmanReaction();
    string getWordForPhoneme(string phoneme);
    int getSkin();
    int getRandomSkin(int maxVal);
    void setSkin(int skinNumber);
    string getLastCompletedGame();
    void unlockNextEpisode();
    string checkAndCorrectDuplicatePhoneme(string phoneme);
    
    DBWatchman* getDBWatchman(DBKnowledgeBubble kb);
    
    string getLastPortalOpened();
    void setLastPortalOpened(string portalName);
    string lastPortalOpened;
    
    bool isIntensifierGameTurn;
    
    DBKnowledgeBubbleAndGame* getCurrentIntensifier();
    void setCurrentIntensifier(const DBKnowledgeBubbleAndGame* currentIntensifier);
    
    DBKnowledgeBubbleAndGame *calculateIntensifier(int intensifierNum);
    

    int lastIntensifierGameNum;
    
    void createUser(string id, string path);
    string getUserPhotoPath(string id);
    
    
    vector<string> getAllUsersId();
    void initUser();
    
    // for map
    string getSemaInitialPortalCode();
    void setSemaInitialPortalCode(string initialPortalCode);
    string getSemaInitialAction();
    void setSemaInitialAction(string initialAction);
    bool getMustUnlockNewPortalMap();
    void setMustUnlockNewPortalMap(bool value);
    string getPhonemeForPortalCode(string portalCode);
    bool nextPhonemeIsLocked();
    void setNightRunnerUnlockedForEpisode(int numEpisode);
    bool isNightRunnerUnlockedForEpisode(int numEpisode);
    //
    int getLastUnlockedEpisodeNum();
    int getLastUnlockedWatchmanNum();
    bool areProportionsLikeIpad(cocos2d::Node* rootNode);
    
    // string getUTF8(string phoneme);
    vector<string> getWordsForGame(string phoneme, string tableName);
    vector<string> getVectorWordsForGame();
    void setVectorWordsForGame(vector<string> vectorWordsForGame);
    
    bool inGame;
    bool intensifierGameCompleted;
    
    int gameRoundCounter;
    
protected:
	DataProvider();

private:

	DBWatchman* currentDBWatchman;
	DBKnowledgeBubble* currentDBKnowledgeBubble;
	DBGame* currentDBGame;
    DBKnowledgeBubbleAndGame* currentIntensifier;
                               
	DataProvider(const DataProvider& other);				// Unimplemented
	DataProvider& operator=(const DataProvider& other);		// Unimplemented
    DatabaseHelper *db;
    
    void unlockEntireEpisode(int episodeNum);
    
    bool unlockPhoneme(string phoneme);
    string getNextPhoneme();
    vector<string> _vectorWordsForGame;
    int skin;
    string lastCompletedGame;
   

    string userId;
    // for map
    string semaInitialPortalCode;
    string semaInitialAction;
    bool mustUnlockNewPortal;
    //vector<bool> nightrunnerLockVector;
    //

    void updateScore(string gameName, float score);
};


inline DBGame* DataProvider::getCurrentDBGame() {

	return currentDBGame;

}

inline DBKnowledgeBubbleAndGame* DataProvider::getCurrentIntensifier() {
    
    return currentIntensifier;
    
}
