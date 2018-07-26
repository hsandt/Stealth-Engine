//
//  Scene.cpp
//  Stealth
//
//  Created by L Nguyen Huu on 04/02/27 H.
//  Copyright (c) 27 Heisei L Nguyen Huu. All rights reserved.
//

#include <algorithm>
#include <iostream>

#include "core/Logger.h"
#include "world/GameObject.h"
#include "core/factory/Factory.h"
#include "world/Scene.h"
#include "world/SceneData.h"
#include "core/EngineCore.h"

using namespace std;

Scene::Scene()
{
}

Scene::~Scene()
{
	// destroy all game objects in the scene
	// (variant of clear without clearing map, since we don't care anymore)
	for (auto goPair : gameObjects) {
		delete goPair.second;
	}

    LOG("[SCENE] Scene destroyed");
}

const map<int, GameObject*>& Scene::getGameObjects() const {
    return gameObjects;
}


void Scene::init(const SceneData &data) {
    name = data.name;

    // TODO: initialize scene with data

    LOGF("[Scene] Scene %s is initialized", "scene name");  // TODO: give a name to all objects!
}

// REFACTOR: just use a vector to store all objects...
// sice hard for us to set ID inside game world creation, we do it in the factory
/// Add a game object to this scene. You need to set the ID
/// *before* calling this method (as we currently use ID-based mapping)
void Scene::addGameObject(GameObject* go) {
    auto emplacePair = gameObjects.emplace(go->ID(), go);
    if (emplacePair.second) {
        LOGF("[SCENE] Added game world #%d %s", go->ID(), go->name.c_str());
	    go->onAddedToScene(this);
    }
    else {
        LOGF("Could not add game world with id: %d: game world with same ID already exists in the scene.",  go->ID());
    }
}

void Scene::removeGameObject(GameObject* go) {
    if (go != nullptr) {
        int nbErased = (int) gameObjects.erase(go->ID());
        if (nbErased == 0) {
            LOGWARNF("Could not remove game world with id %d: no game objects with this ID in the scene.", go->ID());
        }
        delete go;
    }
}

void Scene::clear()
{
    // destroy all game objects in the scene
    for (auto goPair : gameObjects) {
        delete goPair.second;
    }
	gameObjects.clear();
}
