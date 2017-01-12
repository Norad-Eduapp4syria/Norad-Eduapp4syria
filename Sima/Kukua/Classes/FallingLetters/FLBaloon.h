#pragma once

#include "../Utils/GameObject.h"
#include "../Utils/LabelGameObject.h"


class FLBaloon : public GameObject {

public:
	FLBaloon(Node& parentNode, string nodeName);
	virtual ~FLBaloon();
	LabelGameObject& getLabelGameObject() const;
	void setFactors(string multiplicand);

private:
	LabelGameObject* label;
	FLBaloon();																		// Unimplemented
	FLBaloon(const FLBaloon& otherFLBaloon);				// Unimplemented
	FLBaloon& operator=(const FLBaloon& otherFLBaloon);		// Unimplemented

};

inline LabelGameObject& FLBaloon::getLabelGameObject() const {

	return *label;

}