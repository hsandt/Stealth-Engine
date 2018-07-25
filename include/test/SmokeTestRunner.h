//
// Created by L Nguyen Huu on 14/10/2017 ap. J.-C..
//

#pragma once

#include "application/RunMode.h"

class EngineCore;
class Scene;

class SmokeTestRunner
{
private:
    /// Engine core (owned)
    EngineCore *engineCore = nullptr;

    /* Parameters */


    /* State vars */

    /// Has the game application been initialized?
    bool initialized = false;

    /// Is the game running?
    bool isRunning = false;

    /// active scene (shared pointer)
    Scene* currentScene;

public:
    SmokeTestRunner();
    virtual ~SmokeTestRunner();

    SmokeTestRunner(const SmokeTestRunner &) = delete;
    SmokeTestRunner & operator=(const SmokeTestRunner &) & = delete;

    /// Initialize engine, passing the game config
    void init(RunMode runMode = RunMode::Test);

    /// Run the game in the current scene
    void skip(double duration);

public:
    /// Exit the game
    void stop();

private:
    /// Call the start callback of all components in the scene
    void start();
    /// Called to update AI and physics (mainly via BehaviourComponents)
    void update(float dt);

};
