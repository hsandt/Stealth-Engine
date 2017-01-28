//
// Created by L Nguyen Huu on 02/03/15 ap. J.-C..
// Copyright (c) 2015 L Nguyen Huu. All rights reserved.
//

#include <iostream>
#include <memory>

#include "enum/Button.h"
#include "enum/ButtonState.h"
#include "Locator.h"
#include "InputManager.h"

#include "HumanController.h"

using namespace std;

HumanController::HumanController() {

}

HumanController::~HumanController() {

}

void HumanController::setIntention() {
    //weak_ptr<InputManager> wim = Locator::weakGetInputManager();
    InputManager *inputManager = Locator::getInputManager();
    //shared_ptr<InputManager> inputManager = wim.lock();
    if (!inputManager) {
        cout << "HumanController: could not get shared pointer to InputManager" << endl;
        return;
    }

    // TODO: improve by giving priority to last direction pressed (snap)
    // set move intention based on directional keys pressed (origin at top-left)
    float moveIntentionX = 0;
    float moveIntentionY = 0;

	// REFACTOR: layer on top of GLFW for custom enum keys (Input)
    if (inputManager->isKeyDown(GLFW_KEY_LEFT)) {
        moveIntentionX = -1;
    }
    else if (inputManager->isKeyDown(GLFW_KEY_RIGHT)) {
        moveIntentionX = 1;
    }

    if (inputManager->isKeyDown(GLFW_KEY_DOWN)) {
        moveIntentionY = -1;
    }
    else if (inputManager->isKeyDown(GLFW_KEY_UP)) {
        moveIntentionY = 1;
    }

    intention.move = {moveIntentionX, moveIntentionY, 0};

}
