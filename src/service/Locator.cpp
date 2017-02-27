//
// Created by L Nguyen Huu on 25/02/15 ap. J.-C..
// Copyright (c) 2015 L Nguyen Huu. All rights reserved.
//

#include <iostream>

#include "application/GameApplication.h"
#include "service/InputManager.h"

#include "service/Locator.h"

using namespace std;

// default initialization to nullptr for all static pointers (lines required)
Logger *Locator::logger;
GameApplication *Locator::gameApplication;
Factory *Locator::factory;
InputManager *Locator::inputManager;
Renderer *Locator::renderer;

Logger* Locator::getLogger() {
    return logger;
}

Factory* Locator::getFactory() {
    return factory;
}

GameApplication* Locator::getGameApplication() {
    return gameApplication;
}

InputManager* Locator::getInputManager() {
    return inputManager;
}

Renderer* Locator::getRenderer() {
    return renderer;
}

