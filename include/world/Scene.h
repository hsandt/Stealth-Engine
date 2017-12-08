//
//  Scene.h
//  Stealth
//
//  Created by L Nguyen Huu on 04/02/27 H.
//  Copyright (c) 27 Heisei L Nguyen Huu. All rights reserved.
//

#pragma once

#include <map>

//#include "GameObject.h"

class GameObject;

class Scene
{
public:
    Scene();
    virtual ~Scene();
    
    // getter
    std::map<int, GameObject*> getGameObjects() const;

    void init();
//    void addGameObject(std::unique_ptr<GameObject>&& go);
    void addGameObject(GameObject* go);
//    void addGameObject(GameObject &&go);
    /// Remove and delete game object from the scene
    void removeGameObject(GameObject* go);
    /// Remove and delete all the game objects from the scene
    void clear();

private:
    Scene(const Scene &) = delete;
    Scene &operator=(const Scene &) & = delete;
    Scene(Scene&&) = delete;
    Scene &operator=(Scene&&) & = delete;

    // OPTIMIZE: usually, the best is an array of a vector of GameObject instances (not pointers)
    // for locality / cache efficiency + slot / handle mapping. For now, we support GameObject
    // subclasses (as UE4) so this is not possible due to having objects of different sizes.
    // If subclasses reveal unneeded during game development, we will switch to pure entity-components
    // (as Unity) as use an array of game objects instances indeed.
    std::map<int, GameObject*> gameObjects;

};

