//
//  Scene.cpp
//  Stealth
//
//  Created by L Nguyen Huu on 04/02/27 H.
//  Copyright (c) 27 Heisei L Nguyen Huu. All rights reserved.
//

#include <algorithm>
#include <iostream>
//#include <boost/format.hpp>
//#include <boost/log/trivial.hpp>
//#include <boost/chrono/floor.hpp>

#include "core/Logger.h"
#include "world/GameObject.h"
#include "core/factory/Factory.h"
#include "world/Scene.h"
#include "world/SceneData.h"
#include "core/EngineCore.h"

using namespace std;
//using namespace boost::log;

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

/*
void Scene::addGameObject(unique_ptr<GameObject>&& go) {

	// COMPILE ERROR: shared_ptr doesn't have a constructor unique_ptr<GameObject>&& ??
    shared_ptr<GameObject> shGo{move(go)};

    //cout << "Adding world at " << sGo -> GetPosition().x() << " from unique_ptr &go" << endl;

    auto emplacePair = gameObjects.emplace(shGo->ID(), shGo);
    if (emplacePair.second) {
        cout << "[SCENE] Added game world #" << shGo->ID() << " " << shGo->getName() << endl;
    }
    else {
        cout << "Could not add game world with id: " << shGo->ID() << ": game world with same ID already exists in the scene." << endl;
//        BOOST_LOG_VERSION_NAMESPACE;
//        BOOST_LOG_TRIVIAL(warning) << boost::format("Could not add game world with id %d: game world with same ID already exists in the scene.") % go -> ID();
//        BOOST_CHRONO_STATIC;
    }
}
 */

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
//            BOOST_LOG_TRIVIAL(warning) << boost::format("Could not remove game world with id %d: no game objects with this ID in the scene.") % go -> ID();
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
