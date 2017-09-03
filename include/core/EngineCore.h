//
// Created by wing on 17/03/13.
//

#pragma once

#include <stdexcept>

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
	/// Game Application (weak ref)
	GameApplication* gameApplication = nullptr;

	/// Window manager (strong ref)
	WindowManager *windowManager = nullptr;
	/// Factory (strong ref)
	Factory *factory = nullptr;
	/// Scene manager (strong ref)
	SceneManager *sceneManager = nullptr;
	/// Input manager (strong ref)
	InputManager *inputManager = nullptr;
	/// Renderer (strong ref)
	Renderer *renderer = nullptr;

	/// Logger (strong ref)
	Logger *logger;

	/// Singleton instance (weak ref)
	static EngineCore* instance;

private:
	EngineCore();
public:
	virtual ~EngineCore();

	EngineCore(const EngineCore &) = delete;
	EngineCore & operator=(const EngineCore &) & = delete;

	/// Return the singleton instance (nullptr if none)
	inline static EngineCore* getInstance() { return instance; }

	/// Return the singleton instance, or throw an exception if none
	inline static EngineCore* requireInstance() {
		if (instance)
			return instance;

		throw std::runtime_error("[EngineCore] No singleton instance found.");
	}

	/// Return the singleton instance if any, create and return a new instance else
	inline static EngineCore* getOrCreateInstance()
	{
		if (instance)
			return instance;

		instance = new EngineCore;
		return instance;
	}

	void bindGameApplication(GameApplication* gameApplication);

	/// Initialize all the modules
	void init(const GameConfig & gameConfig);

	/// Return the game application
	inline static GameApplication* getGameApplication() { return requireInstance()->gameApplication; }

	/// Return the window manager
	inline static WindowManager* getWindowManager() { return requireInstance()->windowManager; }

	/// Return the factory
	inline static Factory* getFactory() { return requireInstance()->factory; }

	/// Return the scene manager
	inline static SceneManager* getSceneManager() { return requireInstance()->sceneManager; }

	/// Return the input manager
	inline static InputManager* getInputManager() { return requireInstance()->inputManager; }

	/// Return the renderer
	inline static Renderer* getRenderer() { return requireInstance()->renderer; }

	/// Return the logger
	inline static Logger* getLogger() { return requireInstance()->logger; }

};


