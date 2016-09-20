//
//  GameObject.cpp
//  Stealth
//
//  Created by L Nguyen Huu on 04/02/27 H.
//  Copyright (c) 27 Heisei L Nguyen Huu. All rights reserved.
//

#include <iostream>
#include "Component.h"
#include "RenderComponent.h"
#include "geometry/Vec3.h"

#include "GameObject.h"


GameObject::GameObject(const int id, const std::string &name) :
        id(id), name(name) // opt. since init in header
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

template<class T>
void GameObject::AddComponent() {
    cout << "AddComponent<T>" << endl;
}

template<>
void GameObject::AddComponent<Component>() {
    cout << "AddComponent<Component>" << endl;
    // TODO
}

template<class T>
T GameObject::GetComponent() {
    cout << "GetComponent<T>" << endl;
    return nullptr;
}

template<>
Component GameObject::GetComponent<Component>() {
    cout << "GetComponent<Component>" << endl;
    return nullptr;
}

template<>
RenderComponent GameObject::GetComponent<RenderComponent>() {
    cout << "GetComponent<RenderComponent>" << endl;
    return nullptr;
}
