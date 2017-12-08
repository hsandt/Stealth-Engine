//
//  InputManager.h
//  Stealth
//
//  Created by L Nguyen Huu on 04/02/27 H.
//  Copyright (c) 27 Heisei L Nguyen Huu. All rights reserved.
//

#pragma once

#include <map>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "component/InputComponent.h"
#include "input/Key.h"
#include "input/KeyData.h"
#include "input/KeyStates.h"
#include "input/KeyEvent.h"

// REFACTOR: make Manager a base class of InputManager, future RenderManager, etc.
// also split InputManager in 2: InputManager and InputComponentCollector...
class InputManager
{
public:
    InputManager();
    virtual ~InputManager();
    
    InputManager(const InputManager &) = delete;
    InputManager &operator=(const InputManager &) & = delete;
    InputManager(InputManager&&) = delete;
    InputManager &operator=(InputManager&&) & = delete;

    /* Initilization */

    /// Register a new input component (weak pointer)
    void registerInputComponent(InputComponent* inputComponent);

    /// Unregister a input component (weak pointer)
    void unregisterInputComponent(InputComponent* inputComponent);

    /* Update */

    /// Update key dynamic states based on static state changes from last frame
    void processInputs();

    /// Apply input bindings from all registered input components
    void applyInputBindings();

    /* Input state query */

    /// Return the current state of the key, UP or DOWN
    KeyStaticState getKeyStaticState(Key key) const;

    /// Return the current state of the key, UP or DOWN
    KeyDynamicState getKeyDynamicState(Key key) const;

    /// Return 0 if key is UP, 1 if key is DOWN
    float getAxisKeyValue(Key key) const;

    /// Return true if the key has been pressed during this frame
    bool isKeyPressed(Key key) const;

    /// Return true if the key has been released during this frame
    bool isKeyReleased(Key key) const;

    /// Return true if the key is down, whether it has been pressed during this frame or earlier
    bool isKeyDown(Key key) const;

    /// Return true if the key is up, whether it has been released during this frame or earlier
    bool isKeyUp(Key key) const;

private:
    /* Key data */

    std::map<Key, KeyData> allKeyData;

    /* State vars */

    /// Map of key -> dynamic state (only in processKey)
    std::map<Key, KeyDynamicState> keyDynamicStateMap;

    /// All Input components in the current scene (weak pointers)
    std::vector<InputComponent*> inputComponents;

    /* Initialization */

    /// Register all keys (initialization)
    void registerAllKeys();

    /// Register a key with its data in the keymap
    void registerKey(Key key, KeyData keyData);

    /// Initialize all key dynamic states to held up
    void initializeKeyDynamicStateMap();

    /* Update */

    /// Update the button state in the map based on whether it is pressed or released
    void processKey(Key key, KeyStaticState newStaticState);

    /* Helper */

    static KeyStaticState toKeyStaticState(KeyDynamicState keyDynamicState) {
        if (keyDynamicState == KeyDynamicState::RELEASED || keyDynamicState == KeyDynamicState::HELD_UP)
            return KeyStaticState::UP;
        else
            return KeyStaticState::DOWN;
    }

    static float toAxisValue(KeyDynamicState keyDynamicState) {
        if (keyDynamicState == KeyDynamicState::RELEASED || keyDynamicState == KeyDynamicState::HELD_UP)
            return 0.0f;
        else
            return 1.0f;
    }

};

