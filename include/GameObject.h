//
//  GameObject.h
//  Stealth
//
//  Created by L Nguyen Huu on 04/02/27 H.
//  Copyright (c) 27 Heisei L Nguyen Huu. All rights reserved.
//

#pragma once

#include <string>

#include <renderer/Renderer.h>

#include "geometry/Point3.h"

class GameObject
{
    
public:
    static int last_id;

    GameObject(const std::string &name, Point3d const &pos = {0, 0, 0});
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


    Point3d getPosition() const {
        return position;
    }

    void setPosition(const Point3d &pos) {
        GameObject::position = pos;
    }

protected:
    int id;
    std::string name;
    Point3d position = {0, 0, 0};  // must initialize, else garbage

};
