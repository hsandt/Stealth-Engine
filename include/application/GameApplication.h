//
//  GameApplication.h
//  Stealth
//
//  Created by L Nguyen Huu on 04/02/27 H.
//  Copyright (c) 27 Heisei L Nguyen Huu. All rights reserved.
//

#pragma once

#include <memory>
#include <string>

#include "application/GameConfig.h"
#include "application/RunModeData.h"

class EngineCore;
class Scene;

class GameApplication
{
private:
	/// Engine core (owned)
	EngineCore *engineCore = nullptr;

	/* Parameters */

	/// Game configuration data
	GameConfig config;

	/* State vars */

	/// Run mode
	RunMode runMode = RunMode::None;
	const RunModeData* runModeData;

	/// Has the game application been initialized?
	bool initialized = false;

	/// Is the game running?
	bool isRunning = false;

	/// active scene (make it a unique_ptr if you are sure no one else uses it)
	Scene* currentScene;

public:
    GameApplication();
    virtual ~GameApplication();

    GameApplication(const GameApplication &) = delete;
    GameApplication & operator=(const GameApplication &) & = delete;

    /// Load configuration from the provided file
    void loadConfig(const char* filePath);

	/// Set the app title in the config
	void setTitle(const std::string & title);

	/// Set the initial window size in the config
	void setInitialWindowSize(int width, int height);

    /// Initialize engine, passing the game config
    void init(RunMode runMode);

    /// Run the game in the current scene
    void run();

protected:
	/// Post-process callback after new scene loading
	/// In debug, you can use this to add custom game objects on every scene, but don't abuse it
	virtual void onLoadNextScene();

public:
	/// Exit the game
    void stop();

private:
    /// Called to process user input and store the new input dynamic states
    void processInput();
    /// Called to apply any callbacks bound to an input, mainly via InputComponents
    void applyInputBindings();
    /// Call the start callback of all components in the scene
    void start();
    /// Called to update AI and physics (mainly via BehaviourComponents)
    void update(float dt);
    /// Called to render the game view, mainly via RenderComponents
    void render();


};
