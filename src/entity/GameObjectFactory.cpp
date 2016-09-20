//
// Created by wing on 15/09/06.
//

#include "GameObjectFactory.h"

#include "Scene.h"
#include "GameObject.h"
#include "Character.h"

#include <memory>
#include <iostream>

using namespace std;

int GameObjectFactory::last_id = 0;

GameObjectFactory::GameObjectFactory() {

}

GameObjectFactory::~GameObjectFactory() {
    std::cout << "[FACTORY] GameObjectFactory destroyed" << std::endl;
}

template<class T>
std::shared_ptr<T> GameObjectFactory::Create() {
    // non-specialized to GameObject (any subclass) type not handled, could also throw exception
    cout << "[Warning] Calling GameObjectFactory::Create on a type that is not subclassing GameObject." << endl;
    return nullptr;
}

template<>
std::shared_ptr<GameObject> GameObjectFactory::Create<GameObject>() {
    auto go = make_shared<GameObject>(last_id, "GameObject");
    ++last_id;
    if (currentScene.expired()) {
        cout << "Current scene has expired, cannot lock" << endl;
    } else {
        shared_ptr<Scene> sp_CurrentScene = currentScene.lock();
        sp_CurrentScene->addGameObject(go);
        cout << "Game object added to current scene" << endl;
    }
    return go;
}

template<>
std::shared_ptr<Character> GameObjectFactory::Create<Character>() {
    auto go = make_shared<Character>(last_id, "Character");
    ++last_id;
    if (currentScene.expired()) {
        cout << "Current scene has expired, cannot lock" << endl;
    } else {
        shared_ptr<Scene> sp_CurrentScene = currentScene.lock();
        sp_CurrentScene->addGameObject(go);
        cout << "Game object added to current scene" << endl;
    }
    return go;
}

