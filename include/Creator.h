//
// Created by wing on 17/01/14.
// Creator base class for the Factory
// http://cecilsunkure.blogspot.fr/2012/08/game-object-factory-distributed-factory.html
//

#pragma once

#include "Object.h"

class Creator {
public:
	virtual ~Creator() {};

private:
	template<class T>
	T* Create();
};

