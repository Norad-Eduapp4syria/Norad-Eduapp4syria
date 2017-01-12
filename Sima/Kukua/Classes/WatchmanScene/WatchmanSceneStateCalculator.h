#pragma once
#include "WatchmanScene.h"
#include "../Utils/Data/DataProvider.h"
#include <string>

using namespace std;


class WatchmanSceneStateCalculator {

public:
	WatchmanSceneStateCalculator(WatchmanScene &watchmanScene);
	virtual ~WatchmanSceneStateCalculator();
    void calculateState();

private:
    void clearVectorGamesState();
    
	DataProvider* dataProvider;
    string state;
    vector<DBGame*> vectorGamesState;
    WatchmanScene* watchman;
    
    bool areAllGamesCompleted();
    int getNumberOfGamesForPhoneme(string phoneme);
    bool isEpisodeCompleted();
};
