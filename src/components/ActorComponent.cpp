//
// Created by wing on 15/10/13.
//

#include <iostream>

#include "include/world/Actor.h"
#include "include/world/GameObject.h"
#include "include/world/Component.h"

#include "component/ActorComponent.h"

using namespace std;

ActorComponent::ActorComponent() : Component()
{
}

void ActorComponent::setGameObject(GameObject* go)
{
	Component::setGameObject(go);

	// also store pointer for actor version
	actor = dynamic_cast<Actor*>(gameObject);
	// REFACTOR: use setActor for exclusively attaching actor components to actor
	// this will also avoid having static casts (you can also use ClassID for actors to
	// check hierarchy stuff and make your own no-RTTI dynamic cast)
	if (!actor)
		LOGERR("ActorComponent::setGameObject called with non actor game world");
}
