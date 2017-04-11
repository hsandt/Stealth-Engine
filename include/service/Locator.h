//
// Created by L Nguyen Huu on 25/02/15 ap. J.-C..
// Copyright (c) 2015 L Nguyen Huu. All rights reserved.

#pragma once

class Logger;
class GameApplication;
class Factory;
class InputManager;
class Renderer;

class Locator {
public:
	Locator() = delete;

	// NATIVE POINTERS: we delete the objects in GameApplication destructor

    static Logger* getLogger();
    static GameApplication* getGameApplication();
    static Factory* getFactory();
    static InputManager* getInputManager();
    static Renderer* getRenderer();

private:
	static Logger *logger;
	static GameApplication *gameApplication;
    static Factory *factory;
    static InputManager *inputManager;
    static Renderer *renderer;

	friend class GameApplication;
	friend class EngineCore;
};
