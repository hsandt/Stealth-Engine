//
//  InputManager.h
//  Stealth
//
//  Created by L Nguyen Huu on 04/02/27 H.
//  Copyright (c) 27 Heisei L Nguyen Huu. All rights reserved.
//

#pragma once

#include <map>
#include <SDL2/SDL.h>

#include "enum/Button.h"
#include "enum/ButtonState.h"
#include "enum/ButtonEvent.h"


class InputManager
{
public:
    InputManager();
    virtual ~InputManager();
    
    InputManager(const InputManager &) = delete;
    InputManager &operator=(const InputManager &) & = delete;
    InputManager(InputManager&&) = delete;
    InputManager &operator=(InputManager&&) & = delete;
    
    void processInputs();
    ButtonState getButtonState(Button const button) const;
    // return true if the button has been pressed or down during this frame
    bool isPressedOrDown(const Button button) const;

private:
    // map of button -> (button state, first event handled on this frame) (only in processButton)
    std::map<Button, std::pair<ButtonState, ButtonEvent>> buttonStateMap;

    // update the button state in the map based on whether it is pressed or released
    void processButton(Button const button, Uint32 const eventType);
};

