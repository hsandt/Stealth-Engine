//
// Created by L Nguyen Huu on 25/02/15 ap. J.-C..
// Copyright (c) 2015 L Nguyen Huu. All rights reserved.
//

#include <iostream>

#include "GameApplication.h"
#include "engine/include/InputManager.h"

#include "Locator.h"

using namespace std;

weak_ptr<GameApplication> Locator::gameApplication;  // default initialization to nullptr (required)
weak_ptr<InputManager> Locator::inputManager;
weak_ptr<GameObjectFactory> Locator::gameObjectFactory;

// maybe return a shared_ptr for faster processing
shared_ptr<GameApplication> Locator::getGameApplication() {
    if (gameApplication.expired()) {
        cout << "Locator: could not locate GameApplication service." << endl;
        // throw exception here! or lock will be invalid
        // (or at least return nullptr)
        return nullptr;
    }
    return gameApplication.lock();
}

shared_ptr<InputManager> Locator::getInputManager() {
    if (inputManager.expired()) {
        cout << "Locator: could not locate InputManager service." << endl;
        return nullptr;
    }
    return inputManager.lock();
}

shared_ptr<GameObjectFactory> Locator::getGameObjectFactory() {
    if (gameObjectFactory.expired()) {
        cout << "Locator: could not locate GameObjectFactory service." << endl;
        return nullptr;
    }
    return gameObjectFactory.lock();
}
