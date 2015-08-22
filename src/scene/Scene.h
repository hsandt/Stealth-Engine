//
//  Scene.h
//  Stealth
//
//  Created by L Nguyen Huu on 04/02/27 H.
//  Copyright (c) 27 Heisei L Nguyen Huu. All rights reserved.
//

#pragma once

#include <memory>
#include <map>

#include "entity/GameObject.h"

class Scene
{
public:
    Scene();
    virtual ~Scene();
    
    // getter
    std::map<int, std::shared_ptr<GameObject>> getGameObjects() const;

    void addGameObject(std::unique_ptr<GameObject> go);
    void addGameObject(GameObject &&go);
    void removeGameObject(std::weak_ptr<GameObject> &go);

private:
    Scene(const Scene &) = delete;
    Scene &operator=(const Scene &) & = delete;
    Scene(Scene&&) = delete;
    Scene &operator=(Scene&&) & = delete;

    std::map<int, std::shared_ptr<GameObject>> gameObjects;

};

