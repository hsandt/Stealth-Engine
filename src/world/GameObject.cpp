//
//  GameObject.cpp
//  Stealth
//
//  Created by L Nguyen Huu on 04/02/27 H.
//  Copyright (c) 27 Heisei L Nguyen Huu. All rights reserved.
//

#include <algorithm>
#include <iostream>

#include "world/Component.h"
#include "core/Logger.h"
#include "world/Object.h"
#include "core/factory/FactoryUtils.h"

#include "world/GameObject.h"

using namespace std;

GameObject::GameObject() : Object()
{
	LOG("[TEST] construct go");

	// TEST: force components initialization (normally not needed,
	// but may fix garbage vector bug)
	components.resize(0);
	components.reserve(16);
}

GameObject::~GameObject()
{
	for (Component *component : components)
	{
		if (component != nullptr)
		{
			LOGF("[GAMEOBJECT] Deleting components %d", component->id);
			delete component;
		}
		else
		{
			LOGF("[GAMEOBJECT] GameObject #%d %s has null components", id, name.c_str());
		}
	}
	LOGF("[GAMEOBJECT] GameObject #%d %s destroyed", id, name.c_str());
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
		// here, components == *it
		component->onRemovedFromGameObject();
		delete component;
		components.erase(it);
	}
}
