//
// Created by wing on 15/10/13.
//

#include <iostream>

#include "entity/Actor.h"
#include "entity/GameObject.h"
#include "component/Component.h"

#include "component/ActorComponent.h"

using namespace std;

ActorComponent::ActorComponent() : Component()
{
}

void ActorComponent::init()
{
	Component::init();

	// store pointer to Actor
	actor = dynamic_cast<Actor*>(gameObject);
}
