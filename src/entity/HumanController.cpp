//
// Created by L Nguyen Huu on 02/03/15 ap. J.-C..
// Copyright (c) 2015 L Nguyen Huu. All rights reserved.
//

#include <iostream>
#include <memory>

#include "enum/Button.h"
#include "enum/ButtonState.h"
#include "service/Locator.h"
#include "service/InputManager.h"

#include "HumanController.h"

using namespace std;

HumanController::HumanController() {

}

HumanController::~HumanController() {

}

void HumanController::setIntention() {
    //weak_ptr<InputManager> wim = Locator::weakGetInputManager();
    shared_ptr<InputManager> inputManager = Locator::getInputManager();
    //shared_ptr<InputManager> inputManager = wim.lock();
    if (!inputManager) {
        cout << "HumanController: couldd not get shared pointer to InputManager" << endl;
        return;
    }

    // TODO: improve by giving priority to last direction pressed (snap)
    // set move intention based on directional keys pressed (origin at top-left)
    double moveIntentionX = 0;
    double moveIntentionY = 0;

    if (inputManager->isPressedOrDown(Button::LEFT)) {
        moveIntentionX = -1;
    }
    else if (inputManager->isPressedOrDown(Button::RIGHT)) {
        moveIntentionX = 1;
    }

    if (inputManager->isPressedOrDown(Button::UP)) {
        moveIntentionY = -1;
    }
    else if (inputManager->isPressedOrDown(Button::DOWN)) {
        moveIntentionY = 1;
    }

    intention.move = {moveIntentionX, moveIntentionY, 0};

}
