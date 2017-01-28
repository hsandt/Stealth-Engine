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
    /// Remove game object from the scene (caution: this does not delete the game object)
    void removeGameObject(GameObject* go);

private:
    Scene(const Scene &) = delete;
    Scene &operator=(const Scene &) & = delete;
    Scene(Scene&&) = delete;
    Scene &operator=(Scene&&) & = delete;

    std::map<int, GameObject*> gameObjects;

};

