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

#include "debug/Logger.h"
#include "entity/GameObject.h"
#include "factory/Factory.h"
#include "scene/Scene.h"
#include "core/EngineCore.h"

using namespace std;
//using namespace boost::log;

Scene::Scene()
{
}

Scene::~Scene()
{
    // destroy all game objects in the scene
    for (auto goPair : gameObjects) {
        delete goPair.second;
    }

    LOG("[SCENE] Scene destroyed");
}

map<int, GameObject*> Scene::getGameObjects() const {
    return gameObjects;
}

/*
void Scene::addGameObject(unique_ptr<GameObject>&& go) {

	// COMPILE ERROR: shared_ptr doesn't have a constructor unique_ptr<GameObject>&& ??
    shared_ptr<GameObject> shGo{move(go)};

    //cout << "Adding object at " << sGo -> GetPosition().x() << " from unique_ptr &go" << endl;

    auto emplacePair = gameObjects.emplace(shGo->ID(), shGo);
    if (emplacePair.second) {
        cout << "[SCENE] Added game object #" << shGo->ID() << " " << shGo->getName() << endl;
    }
    else {
        cout << "Could not add game object with id: " << shGo->ID() << ": game object with same ID already exists in the scene." << endl;
//        BOOST_LOG_VERSION_NAMESPACE;
//        BOOST_LOG_TRIVIAL(warning) << boost::format("Could not add game object with id %d: game object with same ID already exists in the scene.") % go -> ID();
//        BOOST_CHRONO_STATIC;
    }
}
 */

// REFACTOR: just use a vector to store all objects...
// sice hard for us to set ID inside game object creation, we do it in the factory
/// Add a game object to this scene. You need to set the ID
/// *before* calling this method (as we currently use ID-based mapping)
void Scene::addGameObject(GameObject* go) {
    auto emplacePair = gameObjects.emplace(go->ID(), go);
    if (emplacePair.second) {
        LOGF("[SCENE] Added game object #%d %s", go->ID(), go->name.c_str());
	    go->onAddedToScene(this);
    }
    else {
        LOGF("Could not add game object with id: %d: game object with same ID already exists in the scene.",  go->ID());
    }
}

void Scene::removeGameObject(GameObject* go) {
    if (go != nullptr) {
        int nbErased = (int) gameObjects.erase(go->ID());
        if (nbErased == 0) {
//            BOOST_LOG_TRIVIAL(warning) << boost::format("Could not remove game object with id %d: no game objects with this ID in the scene.") % go -> ID();
        }
    }
}

void Scene::init() {
    EngineCore::getFactory()->ChangeCurrentScene(this);
    // T* &&arg did not work well, so to ensure I don't keep a ref of the GO I use only unique_ptr
//	addGameObject(unique_ptr<GameObject> {new Guard("Guard", {100, 50, 0})});  // use rhs or move only
//	addGameObject(unique_ptr<GameObject> {new Spy("Spy", {50, 50, 0})});
}
