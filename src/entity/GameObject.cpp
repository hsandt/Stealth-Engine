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
#include "debug/Logger.h"
#include "object/Object.h"
#include "factory/FactoryUtils.h"

#include "entity/GameObject.h"

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
			LOGF("[GAMEOBJECT] Deleting component %d", component->id);
			delete component;
		}
		else
		{
			LOGF("[GAMEOBJECT] GameObject #%d %s has null component", id, name.c_str());
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
		// here, component == *it
		component->onRemovedFromGameObject();
		delete component;
		components.erase(it);
	}
}
