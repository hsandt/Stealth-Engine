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

#include "entity/Guard.h"
#include "entity/Spy.h"

using namespace std;
//using namespace boost::log;

Scene::Scene()
{
}

Scene::~Scene()
{
}

std::map<int, std::shared_ptr<GameObject>> Scene::getGameObjects() const {
	return gameObjects;
}

void Scene::addGameObject(unique_ptr<GameObject> go) {
    
    shared_ptr<GameObject> shGo{move(go)};
    
    //cout << "Adding object at " << sGo -> GetPosition().x() << " from unique_ptr &go" << endl;
    
    auto emplacePair = gameObjects.emplace(shGo-> ID(), shGo);
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

void Scene::removeGameObject(weak_ptr<GameObject> &weakGo) {
    shared_ptr<GameObject> go {weakGo.lock()};
    if (go) {
        int nbErased = (int) gameObjects.erase(go->ID());
        if (nbErased == 0) {
//            BOOST_LOG_TRIVIAL(warning) << boost::format("Could not remove game object with id %d: no game objects with this ID in the scene.") % go -> ID();
        }
    }
}

void Scene::init() {
    // T* &&arg did not work well, so to ensure I don't keep a ref of the GO I use only unique_ptr
	addGameObject(unique_ptr<GameObject> {new Guard("Guard", {0, 20, 0})});  // use rhs or move only
	addGameObject(unique_ptr<GameObject> {new Spy("Spy", {50., 50., 0.})});
}

