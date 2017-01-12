#pragma once

#include "../Utils/TouchableGameObject.h"
#include "../Utils/LabelGameObject.h"
#include "../Utils/Data/DBKnowledgeBubble.h"


class KnowledgeBubble : public TouchableGameObject {

public:
	KnowledgeBubble(Node& parentNode, string nodeName, EventDispatcher* eventDispatcher, string csbPath, DBKnowledgeBubble dbKnowledgeBubble);
    
    KnowledgeBubble(Node& parentNode, string nodeName, Vec2 pos, EventDispatcher* eventDispatcher, string csbPath, DBKnowledgeBubble dbKnowledgeBubble);
    
	virtual ~KnowledgeBubble();
	DBKnowledgeBubble getDBKnowledgeBubble() const;
    void setText(string txt);
    void setNotCompletedImage(string spritePath);
    void setCompletedImage(string spritePath);
    void setActiveImage(string spritePath);

private:
	DBKnowledgeBubble dbKnowledgeBubble;
	LabelGameObject* label;
    LabelGameObject* label2;
	KnowledgeBubble();														// Unimplemented
	KnowledgeBubble(const KnowledgeBubble& other);							// Unimplemented
	KnowledgeBubble& operator=(const KnowledgeBubble& other);				// Unimplemented

};

inline DBKnowledgeBubble KnowledgeBubble::getDBKnowledgeBubble() const {

	return dbKnowledgeBubble;

}