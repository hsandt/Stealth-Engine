//
//  InputManager.cpp
//  Stealth
//
//  Created by L Nguyen Huu on 04/02/27 H.
//  Copyright (c) 27 Heisei L Nguyen Huu. All rights reserved.
//

#include <utility>
#include <SDL2/SDL.h>

#include "enum/Button.h"
#include "InputManager.h"

using namespace std;

InputManager::InputManager()
{
    for (Button button : allButtons) {
        buttonStateMap.emplace(button, make_pair(ButtonState::UP, ButtonEvent::NONE));
    }

}

InputManager::~InputManager()
{
}

void InputManager::processInputs() {

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    processButton(Button::UP, event.type);
                    break;
                case SDLK_DOWN:
                    processButton(Button::DOWN, event.type);
                    break;
                case SDLK_LEFT:
                    processButton(Button::LEFT, event.type);
                    break;
                case SDLK_RIGHT:
                    processButton(Button::RIGHT, event.type);
                    break;
                case SDLK_ESCAPE:
                    processButton(Button::QUIT, event.type);
            }
        } else if (event.type == SDL_QUIT) {
            // trick to simulate ESCAPE key press; FIXME: prefer high-level "actions"
            processButton(Button::QUIT, SDL_KEYDOWN);
                break;
        }
    }

    // if a button has not been processed during this frame, and it had just been pressed
    // or released in the last frame, update the state accordingly
    for (auto &buttonPair : buttonStateMap) {
        if (buttonPair.second.second == ButtonEvent::NONE) {
            if (buttonPair.second.first == ButtonState::PRESSED || buttonPair.second.first == ButtonState::RELEASED_PRESSED) {
                buttonPair.second.first = ButtonState::DOWN;
            } else if (buttonPair.second.first == ButtonState::RELEASED || buttonPair.second.first == ButtonState::PRESSED_RELEASED) {
                buttonPair.second.first = ButtonState::UP;
            }
            // else the button was UP or DOWN and there were no further input, so don't do anything
        } else {
            // the button has been flagged pressed or released, clear it before next frame
            buttonPair.second.second = ButtonEvent::NONE;
        }
    }
}

ButtonState InputManager::getButtonState(Button const button) const {
    return buttonStateMap.at(button).first;
}

// TODO: add is pressed or released_pressed, etc. methods

bool InputManager::isPressedOrDown(Button const button) const {
    ButtonState buttonPair = buttonStateMap.at(button).first;
    return buttonPair != ButtonState::UP && buttonPair != ButtonState::RELEASED;
}

void InputManager::processButton(Button const button, Uint32 const eventType) {
    // TODO: replace button pair with a clearer struct, OR use 2 distinct maps
    pair<ButtonState, ButtonEvent> &buttonPair = buttonStateMap.at(button);

    // in order to get references instead of getting the element from the key twice
    switch (eventType) {
    case SDL_KEYDOWN:
        if (buttonPair.second == ButtonEvent::RELEASE) {
            // the button was already released on this frame
            buttonPair.first = ButtonState::RELEASED_PRESSED;
        } else {
            // first event processed for this button (or we repeat press, but unlikely)
            // implicit pair construction
            buttonPair = {ButtonState::PRESSED, ButtonEvent::PRESS};
        }
        break;
    case SDL_KEYUP:
        if (buttonPair.second == ButtonEvent::PRESS) {
            // the button was already pressed on this frame
            buttonPair.first = ButtonState::PRESSED_RELEASED;
        } else {
            // first event processed for this button (or we repeat release, but unlikely)
            buttonPair = {ButtonState::RELEASED, ButtonEvent::RELEASE};
        }
        break;
    }
}
