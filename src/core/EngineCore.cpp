//
// Created by wing on 17/03/13.
//

#include <iostream>
#include <stdexcept>

#include "application/GLFWWindowManager.h"
#include "debug/Logger.h"
#include "core/EngineCore.h"
#include "application/GameApplication.h"
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

void EngineCore::init(const GameConfig & gameConfig)
{
	// always create the Logger 1st
	logger = new Logger(std::cout, std::cout, std::cerr);

	windowManager = new GLFWWindowManager();
	windowManager->init(gameConfig);

	// Create logger on standard output stream

	factory = new Factory();

	sceneManager = new SceneManager();
	sceneManager->init();

	inputManager = new InputManager();

	// create and initialize Renderer (will load all standard shaders)
	renderer = new Renderer();
	renderer->init();

	// create physics manager
	physicsManager = new PhysicsManager();
}

EngineCore::~EngineCore()
{
	// Destroy all modules in reverse order
	LOG("[ENGINE] Destroying engine core...");
	delete physicsManager;
	delete renderer;
	delete inputManager;
	delete sceneManager;
	delete factory;
	delete windowManager;
	delete logger;

	// if you are the singleton instance (and you should be,
	// unless you're an invalid 2nd instance about to be destroyed)
	// then you should clear the pointer to instance now, else
	// it will be invalid and next time we check for instance (in getInstance, LOG, etc.), it will cause SIGSEGV
	// Don't delete it! it would cause a recursive delete and SIGSEGV on delete invalid renderer pointer
	if (instance == this)
		instance = nullptr;
}
