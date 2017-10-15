//
// Created by wing on 17/03/13.
//

#include <iostream>
#include <stdexcept>

#include "application/GLFWWindowManager.h"
#include "debug/Logger.h"
#include "core/EngineCore.h"
#include "application/GameApplication.h"
#include "application/RunModeData.h"
#include "application/ApplicationResult.h"
#include "factory/Factory.h"
#include "scene/SceneManager.h"
#include "renderer/Renderer.h"
#include "physics/PhysicsManager.h"

EngineCore* EngineCore::instance = nullptr;

EngineCore::EngineCore()
{

}

void EngineCore::bindGameApplication(GameApplication* pApplication)
{
	gameApplication = pApplication;
}

void EngineCore::bindSmokeTestRunner(SmokeTestRunner *pTestRunner)
{
    smokeTestRunner = pTestRunner;
}

void EngineCore::init(const RunModeData* runModeData, const GameConfig &gameConfig)
{
    frameDuration = 1. / (double)gameConfig.fps;

	// REFACTOR: use smart pointers for all modules and maybe other objects
	// so that we can check if a pointer is valid or not after destruction
	// To simplify user API, provide getters that always return raw pointers, returning nullptr
	// if a weak pointer is invalid, so that the user can check it easily without causing a SIGSEV.

	// Engine module initialization order:
	// - Logger, so that you can log from other modules
	// - Window manager
	// - Major managers
	// - Minor managers, typically that depend on major managers

	// Create logger on standard output stream
	logger = new Logger(std::cout, std::cout, std::cerr);

	// create and initialize Renderer (will load all standard shaders)
	if (runModeData->renderingActive)
	{
        windowManager = new GLFWWindowManager();
        windowManager->init(gameConfig);

		renderer = new Renderer();
		renderer->init();
	}

	// create physics manager
	physicsManager = new PhysicsManager();

	factory = new Factory();

	sceneManager = new SceneManager();
	sceneManager->init();

	if (runModeData->inputActive)
		inputManager = new InputManager();
}

EngineCore::~EngineCore()
{
	// Destroy all modules in reverse order
    // Since we are still using raw pointers for now, we'd better nullify the pointers after delete to prevent
    // referencing destroyed managers via EngineCore (since some managers indirectly refer to others in their destructors)
	LOG("[ENGINE] Destroying engine core...");

	delete inputManager;
    inputManager = nullptr;

	// Destroy sceneManager before physicsManager, because the latter destroys the world with itself, so we prefer
	// destroying the b2Body of a Rigidbody in the Rigidbody destructor properly before that (not required though,
	// but in this check that physicsManager/the world still exists in Rigidbody destructor).
	delete sceneManager;
	sceneManager = nullptr;

	delete factory;
    factory = nullptr;

    delete physicsManager;
    physicsManager = nullptr;

    delete renderer;
	renderer = nullptr;

	delete windowManager;
	windowManager = nullptr;

    delete logger;
    logger = nullptr;

	// if you are the singleton instance (and you should be,
	// unless you're an invalid 2nd instance about to be destroyed)
	// then you should clear the pointer to instance now, else
	// it will be invalid and next time we check for instance (in getInstance, LOG, etc.), it will cause SIGSEGV
	// Don't delete it! it would cause a recursive delete and SIGSEGV on delete invalid renderer pointer
	if (instance == this)
		instance = nullptr;
}
