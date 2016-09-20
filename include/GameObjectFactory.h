//
// Created by wing on 15/09/06.
//

#pragma once

#include <memory>
#include <Locator.h>
#include <iostream>
#include "Scene.h"

// debug
#include "GameApplication.h"

class GameObjectFactory {
public:
    GameObjectFactory();
    virtual ~GameObjectFactory();

    GameObjectFactory(const GameObjectFactory &) = delete;
    GameObjectFactory &operator=(const GameObjectFactory &) & = delete;
    GameObjectFactory(GameObjectFactory&&) = delete;
    GameObjectFactory &operator=(GameObjectFactory&&) & = delete;

    template<class T>
    std::shared_ptr<T> Create();

    void SetCurrentScene(std::shared_ptr<Scene> scene) {
        currentScene = scene;
    }

private:
    static int last_id;

    // current scene, to which all new objects should be added
    std::weak_ptr<Scene> currentScene;
};
