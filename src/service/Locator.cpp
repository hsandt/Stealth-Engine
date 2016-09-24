//
// Created by L Nguyen Huu on 25/02/15 ap. J.-C..
// Copyright (c) 2015 L Nguyen Huu. All rights reserved.
//

#include <iostream>

#include "GameApplication.h"
#include "InputManager.h"

#include "Locator.h"

using namespace std;

GameApplication *Locator::gameApplication;  // default initialization to nullptr for static (required)
InputManager *Locator::inputManager;
GameObjectFactory *Locator::gameObjectFactory;

// maybe return a shared_ptr for faster processing
GameApplication* Locator::getGameApplication() {
    return gameApplication;
}

InputManager* Locator::getInputManager() {
    return inputManager;
}

GameObjectFactory* Locator::getGameObjectFactory() {
    return gameObjectFactory;
}
