//
// Created by L Nguyen Huu on 25/02/15 ap. J.-C..
// Copyright (c) 2015 L Nguyen Huu. All rights reserved.

#pragma once

class GameApplication;
class InputManager;
class Renderer;
class Factory;

class Locator {
public:
	Locator() = delete;

	// NATIVE POINTERS: we delete the objects in GameApplication destructor

    static GameApplication* getGameApplication();
    static InputManager* getInputManager();
    static Renderer* getRenderer();
    static Factory* getFactory();

private:
	static GameApplication *gameApplication;
    static InputManager *inputManager;
    static Renderer *renderer;
    static Factory *factory;

	friend class GameApplication;
};
