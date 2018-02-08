//
//  GameApplication.cpp
//  Stealth
//
//  Created by L Nguyen Huu on 04/02/27 H.
//  Copyright (c) 27 Heisei L Nguyen Huu. All rights reserved.
//

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <memory>
#include <vector>

// Engine
#include "application/GameApplication.h"
#include "application/RunMode.h"
#include "application/RunModeData.h"
#include "application/WindowManager.h"
#include "component/Transform.h"
#include "core/EngineCore.h"
#include "core/EngineCore.h"
#include "core/Logger.h"
#include "world/GameObject.h"
#include "core/factory/Factory.h"
#include "core/math/Vector2.h"
#include "physics/PhysicsManager.h"
#include "renderer/Renderer.h"
#include "renderer/ShaderUtils.h"
#include "world/Scene.h"
#include "world/SceneManager.h"
#include "input/InputManager.h"
#include "gameplay/ScriptManager.h"

using namespace std;

GameApplication::GameApplication() :
		isRunning(false) {
	if (config.fps <= 0)
		config.fps = 60;  // default if invalid value
}

GameApplication::~GameApplication() {
	LOG("[GAME] Destroying GameApplication...");
	delete engineCore;
}

void GameApplication::loadConfig(const char* filePath)
{
	// TODO
}

void GameApplication::setTitle(const string & title)
{
	config.title = title;
}

void GameApplication::setInitialWindowSize(int width, int height)
{
	config.initialWindowWidth = width;
	config.initialWindowHeight = height;
}

void GameApplication::init(RunMode runMode) {
    if (!(runMode == RunMode::Play || runMode == RunMode::Simulation || runMode == RunMode::TestWithRendering))
        throw std::invalid_argument("RunMode::Test is not accepted for GameApplication");

    this->runMode = runMode;
    runModeData = &RunModeDataSet::getRunModeData(runMode);

	// initialize Engine Core, which will initialize all the modules
	engineCore = EngineCore::getOrCreateInstance();
	engineCore->bindGameApplication(this);  // currently, ref to GameApplication is unused
	engineCore->init(runModeData, config);

	// query loading of initial scene
	EngineCore::getSceneManager()->queryLoadScene(config.initialSceneName);

	initialized = true;
}

void GameApplication::run() {
	if (!initialized)
		throw std::runtime_error("[GameApplication] Cannot run uninitialized game app.");

	double currentTime;
	double endTime = glfwGetTime();
	double lag = 0;
	double sleep;

	isRunning = true;

    start();

	WindowManager* windowManager = engineCore->getWindowManager();
    double frameDuration = engineCore->getFrameDuration();

	// update loop
	while (isRunning)
    {
        // track the current time before loading a new scene
        // because it may take some time in sync and we want
        // to skip any time that passed during sync loading
        currentTime = glfwGetTime();
        lag += currentTime - endTime;

        // if a new scene should be loaded, load it now (sync)
        if (EngineCore::getSceneManager())
        {
            if (EngineCore::getSceneManager()->shouldLoadScene())
            {
                EngineCore::getSceneManager()->loadNextScene();
                onLoadNextScene();
            }
        }

        // get the current time but don't add lag, so that time
        // does not pass during sync scene loading
        currentTime = glfwGetTime();

        // Even if input is inactive, poll normal events so we can stop the game
        // with ESCAPE or the close icon (to interrupt a Simulation or a TestWithRendering)
        windowManager->pollEvents();

        if (windowManager->windowShouldClose())
            isRunning = false;

        if (runModeData->inputActive)
        {
            processInput();
            applyInputBindings();
        }

        while (lag >= frameDuration) {
			// TODO: add limit for number of iterations to catch back
			// pass fixed deltaTime as update argument, in sec
			// ALT: use a gameplay locator for deltaTime (fixed)
			update((float)frameDuration);
			// TODO: compute at once
			lag -= frameDuration;
		}

		render();

		endTime = glfwGetTime();
		lag += endTime - currentTime;

		sleep = frameDuration - lag;
		if (sleep > 0) {
			// we are in advance, wait
//			SDL_Delay(sleep);
//			Sleep();
			glfwWaitEventsTimeout(sleep);
		} else {
			// rendering required more than the end of the frame, not time to sleep!
			cout << "No time to sleep!" << endl;
//			glfwPollEvents();
		}

		windowManager->swapBuffers();

	}

}

void GameApplication::onLoadNextScene()
{
	// now that scene has been loaded, actually start what you should
	// TODO: don't start objects already started (when switching scene while having persistent game objects)

	// Start all rigidbodies
	EngineCore::getPhysicsManager()->start();

	// Start all behavior scripts
	EngineCore::getScriptManager()->start();
}

void GameApplication::stop() {
	isRunning = false;
}

void GameApplication::processInput() {
	if (EngineCore::getInputManager())
		EngineCore::getInputManager()->processInputs();
}
void GameApplication::applyInputBindings()
{
	if (EngineCore::getInputManager())
		EngineCore::getInputManager()->applyInputBindings();
}

void GameApplication::start()
{
    if (!initialized)
        throw std::runtime_error("[GameApplication] Cannot start in uninitialized game app.");

	// don't call start here, scene is not loaded yet (this is not the game start)
}

void GameApplication::update(float dt) {
	// OPTIMIZE: when using smart pointers, we can store smart ptr to current scene and just check validity here
	Scene* currentScene = EngineCore::getSceneManager()->getCurrentScene();
	if (!currentScene)
		return;  // no error message here because it would loop too fast (or use a LOG_ONCE)

	map<int, GameObject*> gameObjects{currentScene->getGameObjects()};
	for (auto goPair : gameObjects) {
		GameObject* go{goPair.second};
		// this is equivalent to Unreal's Tick update,
		// and has no equivalent in Unity which counts entirely on Components
		// unless we compact game objects with custom allocation,
		// this has absolutely no data locality (components are easier to pack)
		go->update(dt);
		// go -> SetPosition(go -> GetPosition() + Vector3 {23, 2, 0});
	}

    // apply physics step (this is done after custom script updates)
    EngineCore::getPhysicsManager()->update(dt);

	// update all custom script components
    EngineCore::getScriptManager()->update(dt);
}

void GameApplication::render()
{
	EngineCore::getRenderer()->clear();
	EngineCore::getRenderer()->render();

	/*
	std::map<int, std::shared_ptr<GameObject>> gameObjects {currentScene->getGameObjects()};
	for (auto goIt(gameObjects.begin()); goIt != gameObjects.end(); ++goIt) {
		// do not use GameObject& which would be invalid if all shared_ptr
		// to the game world disappeared in the meanwhile (~raw pointer issue)
		shared_ptr<GameObject> go {goIt->second};
		go->render(renderer);
	}
	*/

//	SDL_RenderPresent(renderer);
}
