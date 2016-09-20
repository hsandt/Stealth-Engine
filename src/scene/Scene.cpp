//
//  Scene.cpp
//  Stealth
//
//  Created by L Nguyen Huu on 04/02/27 H.
//  Copyright (c) 27 Heisei L Nguyen Huu. All rights reserved.
//

#include <algorithm>
#include <iostream>
#include <memory>
//#include <boost/format.hpp>
//#include <boost/log/trivial.hpp>
//#include <boost/chrono/floor.hpp>

#include "Scene.h"

using namespace std;
//using namespace boost::log;

Scene::Scene()
{
}

Scene::~Scene()
{
    std::cout << "[SCENE] Scene destroyed" << std::endl;
}

std::map<int, std::shared_ptr<GameObject>> Scene::getGameObjects() const {
    return gameObjects;
}

void Scene::addGameObject(unique_ptr<GameObject> go) {

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

void Scene::addGameObject(std::shared_ptr<GameObject> go) {
    auto emplacePair = gameObjects.emplace(go->ID(), go);
    if (emplacePair.second) {
        cout << "[SCENE] Added game object #" << go->ID() << " " << go->getName() << endl;
    }
    else {
        cout << "Could not add game object with id: " << go->ID() << ": game object with same ID already exists in the scene." << endl;
    }
}

void Scene::removeGameObject(weak_ptr<GameObject> &weakGo) {
    shared_ptr<GameObject> go {weakGo.lock()};
    if (go) {
        int nbErased = (int) gameObjects.erase(go->ID());
        if (nbErased == 0) {
//            BOOST_LOG_TRIVIAL(warning) << boost::format("Could not remove game object with id %d: no game objects with this ID in the scene.") % go -> ID();
        }
    }
}
