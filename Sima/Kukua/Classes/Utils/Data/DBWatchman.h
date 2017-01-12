#pragma once

#include "DBKnowledgeBubble.h"
//#include <vector>
//using namespace std;


class DBWatchman {

public:
	DBWatchman(int episode, int number);
	//virtual ~DBWatchman();
	friend bool operator==(const DBWatchman& lhs, const DBWatchman& rhs);
	friend bool operator!=(const DBWatchman& lhs, const DBWatchman& rhs);
	int getEpisode() const;
	int getNumber() const;

private:
	int episode;
	int number;
	//vector<DBKnowledgeBubble*> dbKnowledgeBubbles;
	DBWatchman();											// Unimplemented
	/*DBWatchman(const DBWatchman& other);					// Unimplemented
	DBWatchman& operator=(const DBWatchman& other);			// Unimplemented*/

};

inline bool operator==(const DBWatchman& lhs, const DBWatchman& rhs) {

	return (lhs.getEpisode() == rhs.getEpisode() && lhs.getNumber() == rhs.getNumber());

}

inline bool operator!=(const DBWatchman& lhs, const DBWatchman& rhs) {

	return !(lhs == rhs);

}

inline int DBWatchman::getEpisode() const {

	return episode;

}

inline int DBWatchman::getNumber() const {

	return number;

}