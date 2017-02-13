//
//  GameObject.cpp
//  Stealth
//
//  Created by L Nguyen Huu on 04/02/27 H.
//  Copyright (c) 27 Heisei L Nguyen Huu. All rights reserved.
//

#include <algorithm>
#include <iostream>

#include "component/Component.h"
#include "object/Object.h"
#include "factory/FactoryUtils.h"

#include "entity/GameObject.h"

using namespace std;

GameObject::GameObject() : Object()
{
}

GameObject::~GameObject()
{
	for (Component *component : components)
	{
		if (component != nullptr)
		{
			cout << "[GAMEOBJECT] Deleting component " << component->id << endl;
			delete component;
		}
		else
		{
			cout << "[GAMEOBJECT] GameObject #" << id << " " << name << " has null component" << endl;
		}
	}
	cout << "[GAMEOBJECT] GameObject #" << id << " " << name << " destroyed" << endl;
}


void GameObject::onAddedToScene(Scene *newScene)
{
	scene = newScene;
}

void GameObject::removeComponent(Component *component)
{
	auto it = find(components.begin(), components.end(), component);
	if (it != components.end())
	{
		// here, component == *it
		component->unregisterComponent();
		delete component;
		components.erase(it);
	}
}
