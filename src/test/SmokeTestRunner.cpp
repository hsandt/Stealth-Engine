//
// Created by L Nguyen Huu on 14/10/2017 ap. J.-C..
//

#include <iostream>
#include <map>

#include "include/test/SmokeTestRunner.h"

#include "debug/Logger.h"
#include "core/EngineCore.h"
#include "entity/GameObject.h"
#include "scene/SceneManager.h"
#include "physics/PhysicsManager.h"
#include "scene/Scene.h"
#include "application/RunMode.h"
#include "application/RunModeData.h"

using namespace std;

SmokeTestRunner::SmokeTestRunner() :
        isRunning(false) {
}

SmokeTestRunner::~SmokeTestRunner() {
    LOG("[TEST] Destroying SmokeTestRunner...");
    delete engineCore;
}

void SmokeTestRunner::init(RunMode runMode)
{
    const RunModeData *runModeData = &RunModeDataSet::getRunModeData(runMode);

    // initialize Engine Core, which will initialize all the modules
    engineCore = EngineCore::getOrCreateInstance();
    engineCore->bindSmokeTestRunner(this);  // currently, ref to GameApplication is unused
    GameConfig config;
    config.fps = 60;  // optional: default anyway
    engineCore->init(runModeData, config);

    // immediately load first scene
    engineCore->getSceneManager()->queryLoadScene(config.initialSceneName);
    engineCore->getSceneManager()->loadNextScene();

    initialized = true;

    // start immediately (can also be called outside init, but add more checks
    // to make sure the developer has not forgotten to init, then start before skipping
    start();
}

void SmokeTestRunner::skip(double duration) {
    if (!initialized)
        throw std::runtime_error("[GameApplication] Cannot skip time in uninitialized smoke test runner.");

    double frameDuration = engineCore->getFrameDuration();

    double totalTime = 0.;

    isRunning = true;


    // update loop
    while (isRunning && totalTime < duration) {
        // if a new scene should be loaded, load it now (sync)
        // note that there is currently no config for an initial scene
        // queried in init(), so if you need to load an initial scene for testing,
        // you need to queryLoadScene manually (and you'll probably load only one scene
        // for the smoke test, so you can move this outside the loop too!)
        if (EngineCore::getSceneManager())
        {
            if (EngineCore::getSceneManager()->shouldLoadScene())
            {
                EngineCore::getSceneManager()->loadNextScene();
            }
        }

        update((float) frameDuration);
        totalTime += frameDuration;
    }

}

void SmokeTestRunner::stop() {
    isRunning = false;
}

void SmokeTestRunner::start()
{
    if (!initialized)
        throw std::runtime_error("[SmokeTestRunner] Cannot start in uninitialized smoke test runner.");

    // Start all behavior scripts

    // Start all rigidbodies
    EngineCore::getPhysicsManager()->start();
}

void SmokeTestRunner::update(float dt) {
    // OPTIMIZE: when using smart pointers, we can store smart ptr to current scene and just check validity here
    Scene* currentScene = EngineCore::getSceneManager()->getCurrentScene();
    if (!currentScene)
        return;  // no error message here because it would loop too fast (or use a LOG_ONCE)

    map<int, GameObject*> gameObjects{currentScene->getGameObjects()};
    for (auto goPair : gameObjects) {
        GameObject* go{goPair.second};
        go->update(dt);
    }

    // apply physics step (this is done after custom script updates)
    EngineCore::getPhysicsManager()->update(dt);
}
