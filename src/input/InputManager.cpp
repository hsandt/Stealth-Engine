//
//  InputManager.cpp
//  Stealth
//
//  Created by L Nguyen Huu on 04/02/27 H.
//  Copyright (c) 27 Heisei L Nguyen Huu. All rights reserved.
//

#include <algorithm>
#include <iostream>
#include <utility>
#include <core/Logger.h>
#include <core/EngineCore.h>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "input/KeyStates.h"
#include "input/Key.h"
#include "input/InputManager.h"
#include "application/WindowManager.h"

using namespace std;

/* Public */

InputManager::InputManager()
{
	// initialize all keys by registering them for the input backend
	registerAllKeys();

	initializeKeyDynamicStateMap();
}

InputManager::~InputManager()
{
	LOG("[INPUT] InputManager destroyed");
}

void InputManager::registerInputComponent(InputComponent *inputComponent)
{
	inputComponents.push_back(inputComponent);  // shared to weak pointer conversion
}

void InputManager::unregisterInputComponent(InputComponent *inputComponent)
{
	auto it = find(inputComponents.begin(), inputComponents.end(), inputComponent);

	// REFACTOR: make a util function to remove element when present in container
	if (it != inputComponents.end())
	{
		// here, components == *it
		inputComponents.erase(it);
	}
	else
	{
		cout << "renderComponent not found in Renderer renderComponents" << endl;
	}
}

void InputManager::processInputs()
{
	// GLFW only provides a function to get the static state of a key (pressed or released).
	// In order to track the dynamic state of a key (just pressed, down, just release, up), we need to monitor
	// the evolution of its static state.

	// update dynamic state of all keys, including switching from pressed to down and released to up
	for (const auto& keyDataPair : allKeyData)
	{
		// GCC 7: for (auto& [key, value] : map)
		int keyCode = EngineCore::getWindowManager()->getKey(keyDataPair.second.glfwCode);
//		int glfwCode = glfwGetKey(window, keyDataPair.second.glfwCode);
		processKey(keyDataPair.first, EngineCore::getWindowManager()->toKeyStaticState(keyCode));
	}
}


void InputManager::applyInputBindings()
{
	for (auto inputComponent : inputComponents) {
		inputComponent->applyKeyBindings();
		// TODO: apply axis and action bindings
	}
}

KeyStaticState InputManager::getKeyStaticState(Key key) const
{
    return toKeyStaticState(keyDynamicStateMap.at(key));
}

KeyDynamicState InputManager::getKeyDynamicState(Key key) const
{
    return keyDynamicStateMap.at(key);
}

float InputManager::getAxisKeyValue(Key key) const
{
	return toAxisValue(keyDynamicStateMap.at(key));
}

bool InputManager::isKeyPressed(Key key) const
{
	KeyDynamicState dynamicState = keyDynamicStateMap.at(key);
	return dynamicState == KeyDynamicState::PRESSED;
}

bool InputManager::isKeyReleased(Key key) const
{
	KeyDynamicState dynamicState = keyDynamicStateMap.at(key);
	return dynamicState == KeyDynamicState::RELEASED;
}

bool InputManager::isKeyDown(Key key) const
{
	KeyDynamicState dynamicState = keyDynamicStateMap.at(key);
	return dynamicState == KeyDynamicState::PRESSED || dynamicState == KeyDynamicState::HELD_DOWN;
}

bool InputManager::isKeyUp(Key key) const
{
	KeyDynamicState dynamicState = keyDynamicStateMap.at(key);
	return dynamicState == KeyDynamicState::RELEASED || dynamicState == KeyDynamicState::HELD_UP;
}

/* Private */

void InputManager::registerAllKeys()
{
	// REFACTOR: move away any GLFW reference to GLFWWindowManager
	// create key data and copy directly to map instead of using a shared pointer as in Unreal Engine InputCoreTypes.cpp > AddKey
	registerKey(Key::ESCAPE, KeyData(GLFW_KEY_ESCAPE));
	registerKey(Key::RIGHT, KeyData(GLFW_KEY_RIGHT));
	registerKey(Key::LEFT, KeyData(GLFW_KEY_LEFT));
	registerKey(Key::DOWN, KeyData(GLFW_KEY_DOWN));
	registerKey(Key::UP, KeyData(GLFW_KEY_UP));
}

void InputManager::registerKey(Key key, KeyData keyData)
{
	allKeyData.emplace(key, keyData);
}

void InputManager::initializeKeyDynamicStateMap()
{
	for (const auto& keyDataPair : allKeyData)
	{
		keyDynamicStateMap.emplace(keyDataPair.first, KeyDynamicState::HELD_UP);
	}
}

void InputManager::processKey(Key key, KeyStaticState newStaticState)
{
	// DEBUG
	if (keyDynamicStateMap.find(key) == keyDynamicStateMap.end())
		return;

	// Get previous key state by reference so that we can update it inside the map if needed
	KeyDynamicState &keyState = keyDynamicStateMap.at(key);

	if (keyState == KeyDynamicState::RELEASED)
	{
		if (newStaticState == KeyStaticState::UP)
			keyState = KeyDynamicState::HELD_UP;
		else
			keyState = KeyDynamicState::PRESSED;  // pressed just after released
	}
	else if (keyState == KeyDynamicState::HELD_UP)
	{
		if (newStaticState == KeyStaticState::DOWN)
			keyState = KeyDynamicState::PRESSED;
	}
	else if (keyState == KeyDynamicState::PRESSED)
	{
		if (newStaticState == KeyStaticState::DOWN)
			keyState = KeyDynamicState::HELD_DOWN;
		else
			keyState = KeyDynamicState::RELEASED;  // released just after pressed
	}
	else  // keyState == KeyDynamicState::HELD_DOWN
	{
		if (newStaticState == KeyStaticState::UP)
			keyState = KeyDynamicState::RELEASED;
	}
}

