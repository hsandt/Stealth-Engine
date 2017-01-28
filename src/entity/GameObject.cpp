//
//  GameObject.cpp
//  Stealth
//
//  Created by L Nguyen Huu on 04/02/27 H.
//  Copyright (c) 27 Heisei L Nguyen Huu. All rights reserved.
//

#include <algorithm>
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
	for (Component* component : components) {
		if (component != nullptr)
			delete component;
		else
			cout << "[GAMEOBJECT] GameObject #" << id << " " << name << " has null component" << endl;
	}
    cout << "[GAMEOBJECT] GameObject #" << id << " " << name << " destroyed" << endl;
}



void GameObject::onAddedToScene(Scene* newScene) {
	scene = newScene;
}

void GameObject::removeComponent(Component *component) {
	auto it = find(components.begin(), components.end(), component);
	if (it != components.end()) {
		// detach component
		component->detachFromGameObject();
		// delete component (don't let it live alone)
		delete component;
		// clear pointer to it by completely removing the entry in the components vector
		components.erase(it);
	}
}
