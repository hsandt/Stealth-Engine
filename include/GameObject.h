//
//  GameObject.h
//  Stealth
//
//  Created by L Nguyen Huu on 04/02/27 H.
//  Copyright (c) 27 Heisei L Nguyen Huu. All rights reserved.
//

#pragma once

#include <string>

#include "Renderer.h"

#include "geometry/Vec3.h"

class GameObject
{
    
public:
    static int last_id;

    GameObject(const std::string &name, Vec3f const &pos = {0, 0, 0});
    virtual ~GameObject();
    GameObject(const GameObject &) = delete;
    GameObject &operator=(const GameObject &) & = delete;
    GameObject(GameObject&&) = delete;
    GameObject &operator=(GameObject&&) & = delete;

    // id
    int ID() const;

    // update
    virtual void update(double dt) {}

    // render
    virtual void render(Renderer *renderer) {}


    std::string getName() const {
        return name;
    }


    Vec3f getPosition() const {
        return position;
    }

    void setPosition(const Vec3f &pos) {
        GameObject::position = pos;
    }

protected:
    int id;
    std::string name;
    Vec3f position = {0, 0, 0};  // must initialize, else garbage

};
