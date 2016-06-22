//
//  InputManager.cpp
//  Stealth
//
//  Created by L Nguyen Huu on 04/02/27 H.
//  Copyright (c) 27 Heisei L Nguyen Huu. All rights reserved.
//

#include <utility>
#include "GLFW/glfw3.h"

#include "../../include/enum/KeyDynamicState.h"
#include "enum/Button.h"
#include "InputManager.h"

using namespace std;

InputManager::InputManager(GLFWwindow *window) : window(window)
{
//    for (Button button : allButtons) {
//        buttonStateMap.emplace(button, make_pair(ButtonState::UP, ButtonEvent::NONE));
//    }

	for (int key : allKeys) {
		keyDynamicStateMap.emplace(key, KeyDynamicState::UP);
	}

}

InputManager::~InputManager()
{
}



void InputManager::processInputs() {

    // GLFW only provides a function to get the static state of a key (pressed or released)
    // In order to track the dynamic state of a key (just pressed, down, just release, up), we need to monitor
    // the evolution of its static state

    // array of keys for which we track the state
    int keys[] = {GLFW_KEY_LEFT, GLFW_KEY_RIGHT, GLFW_KEY_DOWN, GLFW_KEY_UP, GLFW_KEY_ESCAPE};

	// update dynamic state of all keys, including switching from pressed to down and released to up
    for (int key : keys) {
        int staticState = glfwGetKey(window, key);
		processKey(key, staticState);
    }
}

bool InputManager::isKeyDown(int key) const {
	KeyDynamicState dynamicState = keyDynamicStateMap.at(key);
	return dynamicState == KeyDynamicState::PRESSED || dynamicState == KeyDynamicState::DOWN;
}

//ButtonState InputManager::getButtonState(Button const button) const {
//    return buttonStateMap.at(button).first;
//}

// TODO: add is pressed or released_pressed, etc. methods

//bool InputManager::isPressedOrDown(Button const button) const {
//    ButtonState buttonPair = buttonStateMap.at(button).first;
//    return buttonPair != ButtonState::UP && buttonPair != ButtonState::RELEASED;
//}

void InputManager::processKey(int key, int newState) {
    // TODO: replace button pair with a clearer struct, OR use 2 distinct maps
	// Previous key state
	KeyDynamicState &keyState = keyDynamicStateMap.at(key);

    // in order to get references instead of getting the element from the key twice
    if (keyState == KeyDynamicState::RELEASED)
	{
		if (newState == GLFW_RELEASE) keyState = KeyDynamicState::UP;
		else keyState = KeyDynamicState::PRESSED;
	}
	else if (keyState == KeyDynamicState::UP)
	{
		if (newState == GLFW_PRESS) keyState = KeyDynamicState::PRESSED;
	}
	else if (keyState == KeyDynamicState::PRESSED)
	{
		if (newState == GLFW_PRESS) keyState = KeyDynamicState::DOWN;
		else keyState = KeyDynamicState::RELEASED;
	}
	else
	{
		if (newState == GLFW_RELEASE) keyState = KeyDynamicState::RELEASED;
	}
}
