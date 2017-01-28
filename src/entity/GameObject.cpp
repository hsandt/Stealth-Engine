//
//  GameObject.cpp
//  Stealth
//
//  Created by L Nguyen Huu on 04/02/27 H.
//  Copyright (c) 27 Heisei L Nguyen Huu. All rights reserved.
//

#include <iostream>
#include "FactoryUtils.h"
#include "Component.h"

#include "GameObject.h"


using namespace std;

GameObject::GameObject(const std::string &name) :
	name(name) // opt. since init in header
{
}

GameObject::~GameObject()
{
    std::cout << "[GAMEOBJECT] GameObject #" << id << " " << name << " destroyed" << std::endl;
}



void GameObject::onAddedToScene(std::shared_ptr<Scene> newScene) {
	scene = newScene;
}
