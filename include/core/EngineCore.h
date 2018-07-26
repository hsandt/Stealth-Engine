//
// Created by wing on 17/03/13.
//

#pragma once

#include <stdexcept>
#include "application/RunMode.h"
#include "application/RunModeData.h"

#include "application/GameConfig.h"

class ManagerFactory;
class GameApplication;
class SmokeTestRunner;
class WindowManager;
class Factory;
class SceneManager;
class InputManager;
class Renderer;
class PhysicsManager;
class ScriptManager;
class Logger;

class EngineCore
{
private:
    /// Singleton instance (weak ref)
    static EngineCore* instance;

	// ARCHITECTURE: only gameApplication or only smokeTestRunner is set, depending on the
    // run mode. Unfortunately, I find no elegant way not to have two members where one is
    // not be used, as a union of pointers to different types is risky.

    /// Game Application (weak ref)
	GameApplication* gameApplication = nullptr;

    /// Smoke Test Runner (weak ref)
	SmokeTestRunner* smokeTestRunner = nullptr;

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
	/// Physics manager (strong ref)
	PhysicsManager *physicsManager = nullptr;
	/// Script manager (strong ref)
	ScriptManager *scriptManager = nullptr;
	/// Logger (strong ref)
	Logger *logger;

    /// Run mode
	const RunModeData* runModeData = nullptr;

    /// Target update period (s)
    double frameDuration = 0.;

private:
	EngineCore() = default;
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

#if BUILD_TESTS
// This #if is tricky, it will only work for definitions inline in the header.
// Trying the same with a definition in the source will result in undefined reference.

    /// In unit tests, always get a new instance at the beginning
    /// to avoid side effects of previous tests
	inline static EngineCore* getNewInstance()
	{
		if (instance)
			delete instance;

		instance = new EngineCore;
		return instance;
	}
#endif

	void bindGameApplication(GameApplication* gameApplication);
	void bindSmokeTestRunner(SmokeTestRunner* pTestRunner);

	/// Initialize all the modules
    void init(const RunModeData* runModeData, const GameConfig &gameConfig, const ManagerFactory& managerFactory);

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

	/// Return the physics manager
	inline static PhysicsManager* getPhysicsManager() { return requireInstance()->physicsManager; }

	/// Return the custom scripts manager
	inline static ScriptManager* getScriptManager() { return requireInstance()->scriptManager; }

	/// Return the logger
	inline static Logger* getLogger() { return requireInstance()->logger; }

    /// Return the duration of a frame
    inline double getFrameDuration() const { return frameDuration; }
};


