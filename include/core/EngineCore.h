//
// Created by wing on 17/03/13.
//

#pragma once

#include "application/GameConfig.h"

class GameApplication;
class WindowManager;
class Factory;
class SceneManager;
class InputManager;
class Renderer;
class Logger;

class EngineCore
{
private:
	GameApplication* gameApplication = nullptr;
	WindowManager *windowManager = nullptr;

	Factory *factory = nullptr;
	SceneManager *sceneManager = nullptr;
	InputManager *inputManager = nullptr;
	Renderer *renderer = nullptr;

	Logger *logger;

	/// Singleton instance
	static EngineCore* instance;

public:
	EngineCore(GameApplication* gameApplication);
	virtual ~EngineCore();

	EngineCore(const EngineCore &) = delete;
	EngineCore & operator=(const EngineCore &) & = delete;

	/// Return the singleton instance (nullptr if none)
	inline static EngineCore* getInstance() { return instance; }

	/// Initialize all the modules
	void init(const GameConfig & gameConfig);

	/// Return the game application
	inline static GameApplication* getGameApplication() { return instance ? instance->gameApplication : nullptr; }

	/// Return the window manager
	inline static WindowManager* getWindowManager() { return instance ? instance->windowManager : nullptr; }

	/// Return the factory
	inline static Factory* getFactory() { return instance ? instance->factory : nullptr; }

	/// Return the scene manager
	inline static SceneManager* getSceneManager() { return instance ? instance->sceneManager : nullptr; }

	/// Return the input manager
	inline static InputManager* getInputManager() { return instance ? instance->inputManager : nullptr; }

	/// Return the renderer
	inline static Renderer* getRenderer() { return instance ? instance->renderer : nullptr; }

	/// Return the logger
	inline static Logger* getLogger() { return instance ? instance->logger : nullptr; }

};


