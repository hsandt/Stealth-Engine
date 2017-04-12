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
#include "renderer/Renderer.h"

EngineCore* EngineCore::instance = nullptr;

EngineCore::EngineCore(GameApplication* gameApplication)
	: gameApplication(gameApplication)
{
	if (instance)
		throw runtime_error("An instance of EngineCore has already been created");

	instance = this;
}

void EngineCore::init(const GameConfig & gameConfig)
{
	// always create the Logger 1st
	logger = new Logger(std::cout, std::cout, std::cerr);

	windowManager = new GLFWWindowManager();
	windowManager->init(gameConfig);

	// Create logger on standard output stream

	factory = new Factory();

	inputManager = new InputManager();

	renderer = new Renderer();
	// initialize Renderer (will load all standard shaders)
	renderer->init();
}

EngineCore::~EngineCore()
{
	delete factory;
	delete inputManager;
	delete renderer;
	delete logger;
}
