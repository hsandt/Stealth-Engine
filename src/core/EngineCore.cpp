//
// Created by wing on 17/03/13.
//

#include <iostream>

#include "debug/Logger.h"
#include "core/EngineCore.h"
#include "application/GameApplication.h"
#include "factory/Factory.h"
#include "renderer/Renderer.h"
#include "service/Locator.h"

EngineCore::EngineCore(GameApplication* gameApplication)
{
	// OGRE-style engine initialization (see Game Engine Architecture 5.1.3.1 p.236)
	// using new in engine core constructor, and deleting explicitly in core destructor.
	// This means we don't need separate startUp and shutDown methods, relying on
	// constructor and destructor only. However, we can create them if we need more
	// control on initialization and shut down.
	// Still use service Locator (instead of setting static singleton instance
	// in constructor as in OgreSingleton.h)

	// register Service Providers to Service Locators
	Locator::gameApplication = gameApplication;

	// Create logger on standard output stream
	Locator::logger = new Logger(std::cout, std::cout, std::cerr);

	Locator::factory = new Factory();

	Locator::inputManager = new InputManager(gameApplication->getWindow());

	Locator::renderer = new Renderer(gameApplication->getWindow());
	// initialize Renderer (will load all standard shaders)
	Locator::renderer->init();
}

EngineCore::~EngineCore()
{
	delete Locator::factory;
	delete Locator::inputManager;
	delete Locator::renderer;  // or use unique_ptr
	delete Locator::logger;

	// clear reverse references considered as weak
	Locator::factory = nullptr;
	Locator::inputManager = nullptr;
	Locator::renderer = nullptr;
	Locator::logger = nullptr;
}
