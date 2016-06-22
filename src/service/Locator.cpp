//
// Created by L Nguyen Huu on 25/02/15 ap. J.-C..
// Copyright (c) 2015 L Nguyen Huu. All rights reserved.
//

#include <iostream>

// Engine
#include "InputManager.h"

// Game
#include "application/GameApplication.h"

#include "Locator.h"

using namespace std;

GameApplication *Locator::gameApplication;  // default initialization to nullptr for static (required)
InputManager *Locator::inputManager;

// maybe return a shared_ptr for faster processing
GameApplication* Locator::getGameApplication() {
    return gameApplication;
}

InputManager* Locator::getInputManager() {
    return inputManager;
}
