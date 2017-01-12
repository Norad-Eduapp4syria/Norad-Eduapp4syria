#pragma once

#include "DBKnowledgeBubble.h"
#include "DBGame.h"

class DBKnowledgeBubbleAndGame {

public:
	DBKnowledgeBubbleAndGame(DBKnowledgeBubble* dbKnowledgeBubble, DBGame* dbGame);
	//virtual ~DBKnowledgeBubbleAndGame();
	friend bool operator==(const DBKnowledgeBubbleAndGame& lhs, const DBKnowledgeBubbleAndGame& rhs);
	friend bool operator!=(const DBKnowledgeBubbleAndGame& lhs, const DBKnowledgeBubbleAndGame& rhs);

    DBKnowledgeBubble* getDBKnowledgeBubble() const;
    DBGame* getDBGame() const;

private:
    DBKnowledgeBubble *dbKnowledgeBubble;
    DBGame *dbGame;
	//vector<DBKnowledgeBubble*> dbKnowledgeBubbles;
	DBKnowledgeBubbleAndGame();											// Unimplemented
	/*DBKnowledgeBubbleAndGame(const DBKnowledgeBubbleAndGame& other);					// Unimplemented
	DBKnowledgeBubbleAndGame& operator=(const DBKnowledgeBubbleAndGame& other);			// Unimplemented*/

};

inline bool operator==(const DBKnowledgeBubbleAndGame& lhs, const DBKnowledgeBubbleAndGame& rhs) {

	return (lhs.getDBKnowledgeBubble() == rhs.getDBKnowledgeBubble() && lhs.getDBGame() == rhs.getDBGame());

}

inline bool operator!=(const DBKnowledgeBubbleAndGame& lhs, const DBKnowledgeBubbleAndGame& rhs) {

	return !(lhs == rhs);

}


inline DBKnowledgeBubble* DBKnowledgeBubbleAndGame::getDBKnowledgeBubble() const {
    
    return dbKnowledgeBubble;
    
}

inline DBGame* DBKnowledgeBubbleAndGame::getDBGame() const {
    
    return dbGame;
    
}