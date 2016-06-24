//
//  GameObject.cpp
//  Stealth
//
//  Created by L Nguyen Huu on 04/02/27 H.
//  Copyright (c) 27 Heisei L Nguyen Huu. All rights reserved.
//

#include <iostream>

#include "geometry/Point3.h"

#include "GameObject.h"

int GameObject::last_id = 0;

GameObject::GameObject(const std::string &name, Point3f const &pos) :
        id(++last_id), name(name), position(pos)
{
    //id = ++last_id;
}

GameObject::~GameObject()
{
    std::cout << "[GAMEOBJECT] GameObject #" << id << " " << name << " destroyed" << std::endl;
}

int GameObject::ID() const {
    return id;
}
