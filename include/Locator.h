//
// Created by L Nguyen Huu on 25/02/15 ap. J.-C..
// Copyright (c) 2015 L Nguyen Huu. All rights reserved.

#pragma once

class GameApplication;
class InputManager;

class Locator {
public:
	friend class GameApplication; // does not compile, add class or import

	Locator() = delete;

    static GameApplication* getGameApplication();
    static InputManager* getInputManager();

private:
	static GameApplication *gameApplication;
    static InputManager *inputManager;

};
