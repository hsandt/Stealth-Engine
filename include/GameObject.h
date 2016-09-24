//
//  GameObject.h
//  Stealth
//
//  Created by L Nguyen Huu on 04/02/27 H.
//  Copyright (c) 27 Heisei L Nguyen Huu. All rights reserved.
//

#pragma once

#include <memory>
#include <string>
#include <vector>
#include "Renderer.h"

#include "geometry/Vec3.h"

class Component;

class GameObject
{

public:
    GameObject(const int id, const std::string &name);
    virtual ~GameObject();
    GameObject(const GameObject &) = delete;
    GameObject &operator=(const GameObject &) & = delete;

    // id
    int ID() const;

    // update
    virtual void update(double dt) {}

    // render (will soon be replaced by Component render)
    virtual void render(Renderer *renderer) {}


    std::string getName() const {
        return name;
    }

//    template<class T>
//    void AddComponent();

    template<class T>
    T* GetComponent();


    Vec3f getPosition() const {
        return position;
    }

    void setPosition(const Vec3f &pos) {
        GameObject::position = pos;
    }

protected:
    const int id;
    std::string name;
    std::vector<std::shared_ptr<Component>> components;
    Vec3f position = {0, 0, 0};  // must initialize, else garbage

};
