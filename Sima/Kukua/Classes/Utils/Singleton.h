#pragma once

#include "cocos2d.h"


template<typename Type>
class Singleton {

public:
	static Type* getInstance() {
		//CCLOG("Singleton - getInstance()");
		//static Type* instance = new Type();
		return &instance;
	};

protected:
	Singleton() {
		CCLOG("Singleton()");
	};

private:
	static Type instance;

};

template <typename Type>
Type Singleton<Type>::instance;