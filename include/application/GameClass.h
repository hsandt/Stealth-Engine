//
// Created by wing on 17/04/11.
//

#pragma once

#include "core/EngineCore.h"

// Currently unused, will be useful later to log automatically
// in context, e.g. prepending message with [Tag] where Tag
// is return by the overriden GameClass::getTag()
class GameClass
{
protected:

public:
	GameClass();
	virtual ~GameClass();
};


