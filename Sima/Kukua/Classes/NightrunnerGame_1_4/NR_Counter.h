#pragma once
#include "../Utils/GameObject.h"


class NR_Counter : public GameObject {

public:
	NR_Counter(Node& parentNode, string nodeName, EventDispatcher* eventDispatcher);
	virtual ~NR_Counter();
    void addPiece();
    void startCounter();

private:
	NR_Counter();										// Unimplemented
	NR_Counter(const NR_Counter& other);					// Unimplemented
	NR_Counter& operator=(const NR_Counter& other);		// Unimplemented
    int currentPieces;
    EventDispatcher* _eventDispatcher;
};
