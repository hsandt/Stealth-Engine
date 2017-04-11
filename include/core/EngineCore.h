//
// Created by wing on 17/03/13.
//

#pragma once


#include <application/GameApplication.h>

class EngineCore
{
private:

public:
	EngineCore(GameApplication* gameApplication);
	virtual ~EngineCore();

	EngineCore(const EngineCore &) = delete;
	EngineCore & operator=(const EngineCore &) = delete;
};


