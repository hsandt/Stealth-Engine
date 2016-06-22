//
//  InputManager.h
//  Stealth
//
//  Created by L Nguyen Huu on 04/02/27 H.
//  Copyright (c) 27 Heisei L Nguyen Huu. All rights reserved.
//

#pragma once

#include <map>
#include "GLFW/glfw3.h"

#include "enum/KeyDynamicState.h"
#include "enum/Button.h"
#include "enum/ButtonState.h"
#include "enum/ButtonEvent.h"

//constexpr std::array<int, static_cast<int>(Button::COUNTER)> allKeys = {
constexpr int allKeys[] = {
    GLFW_KEY_LEFT,
    GLFW_KEY_RIGHT,
    GLFW_KEY_DOWN,
    GLFW_KEY_UP,
    GLFW_KEY_ESCAPE
};

class InputManager
{
public:
    InputManager(GLFWwindow *window);
    virtual ~InputManager();
    
    InputManager(const InputManager &) = delete;
    InputManager &operator=(const InputManager &) & = delete;
    InputManager(InputManager&&) = delete;
    InputManager &operator=(InputManager&&) & = delete;

    /// Update key dynamic states based on static state changes from last frame
    void processInputs();
    bool isKeyDown(int key) const;
//    ButtonState getButtonState(Button const button) const;
    // return true if the button has been pressed or down during this frame
//    bool isPressedOrDown(const Button button) const;

private:
    /// Application window
    GLFWwindow *window;

    // map of key -> button state (only in processKey)
    std::map<int, KeyDynamicState> keyDynamicStateMap;

    // map of button -> button state (only in processKey)
//    std::map<Button, ButtonState> buttonStateMap;

    // update the button state in the map based on whether it is pressed or released
    void processKey(int key, int newState);
};

