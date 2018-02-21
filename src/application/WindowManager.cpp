//
//  WindowManager.cpp
//  Stealth
//
//  Created by L Nguyen Huu on 04/02/27 H.
//  Copyright (c) 27 Heisei L Nguyen Huu. All rights reserved.
//

#include <iostream>
#include <core/Logger.h>

#include "application/WindowManager.h"

using namespace std;

WindowManager::WindowManager()
{
}

WindowManager::~WindowManager()
{
}

void WindowManager::errorCallback(int error, const char* description)
{
	// store error number and log error immediately
	LOGERR("[WindowManager] Error: ", description);
}
