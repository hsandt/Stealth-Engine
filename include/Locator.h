//
// Created by L Nguyen Huu on 25/02/15 ap. J.-C..
// Copyright (c) 2015 L Nguyen Huu. All rights reserved.

#pragma once

class GameApplication;
class GameObjectFactory;
class InputManager;

class Locator {
public:
	friend class GameApplication; // does not compile, add class or import

	Locator() = delete;

    static std::shared_ptr<GameApplication> getGameApplication();
    static std::shared_ptr<InputManager> getInputManager();
    static std::shared_ptr<GameObjectFactory> getGameObjectFactory();

private:
	static std::weak_ptr<GameApplication> gameApplication;
    static std::weak_ptr<InputManager> inputManager;
    static std::weak_ptr<GameObjectFactory> gameObjectFactory;

};
