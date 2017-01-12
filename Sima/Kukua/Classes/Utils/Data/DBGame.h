#pragma once

#include "DBKnowledgeBubble.h"
#include <string>
using namespace std;


class DBGame {

public:
	DBGame(const string& name, int skin);
	//virtual ~DBGame();
	friend bool operator==(const DBGame& lhs, const DBGame& rhs);
	friend bool operator!=(const DBGame& lhs, const DBGame& rhs);
	string getName() const;
	int getSkin() const;

private:
	string name;
	int skin;
	DBGame();										// Unimplemented
	/*DBGame(const DBGame& other);					// Unimplemented
	DBGame& operator=(const DBGame& other);			// Unimplemented*/

};

inline bool operator==(const DBGame& lhs, const DBGame& rhs) {

	return (lhs.getName().compare(rhs.getName()) == 0 && lhs.getSkin() == rhs.getSkin());

}

inline bool operator!=(const DBGame& lhs, const DBGame& rhs) {

	return !(lhs == rhs);

}

inline string DBGame::getName() const {

	return name;

}

inline int DBGame::getSkin() const {

	return skin;

}