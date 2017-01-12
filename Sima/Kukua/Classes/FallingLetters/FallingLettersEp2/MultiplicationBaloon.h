#pragma once

#include "../../Utils/GameObject.h"
#include "../../Utils/LabelGameObject.h"


class MultiplicationBaloon : public GameObject {

public:
	MultiplicationBaloon(Node& parentNode, string nodeName);
	virtual ~MultiplicationBaloon();
	void setFactors(int multiplier);

private:
    Sprite* labelImg;
	MultiplicationBaloon();																		// Unimplemented
	MultiplicationBaloon(const MultiplicationBaloon& otherMultiplicationBaloon);				// Unimplemented
	MultiplicationBaloon& operator=(const MultiplicationBaloon& otherMultiplicationBaloon);		// Unimplemented

};
