#pragma once

#include <string>
using namespace std;


class DBKnowledgeBubble {

public:
	DBKnowledgeBubble(const string& phoneme, bool locked);
	//virtual ~DBKnowledgeBubble();
	friend bool operator==(const DBKnowledgeBubble& lhs, const DBKnowledgeBubble& rhs);
	friend bool operator!=(const DBKnowledgeBubble& lhs, const DBKnowledgeBubble& rhs);
	string getPhoneme() const;
	bool isLocked() const;

private:
	string phoneme;
	bool locked;
	DBKnowledgeBubble();													// Unimplemented
	/*DBKnowledgeBubble(const DBKnowledgeBubble& other);						// Unimplemented
	DBKnowledgeBubble& operator=(const DBKnowledgeBubble& other);			// Unimplemented*/

};

inline bool operator==(const DBKnowledgeBubble& lhs, const DBKnowledgeBubble& rhs) {

	return (lhs.getPhoneme().compare(rhs.getPhoneme()) == 0);

}

inline bool operator!=(const DBKnowledgeBubble& lhs, const DBKnowledgeBubble& rhs) {

	return !(lhs == rhs);

}

inline string DBKnowledgeBubble::getPhoneme() const {

	return phoneme;

}

inline bool DBKnowledgeBubble::isLocked() const {

	return locked;

}