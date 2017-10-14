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

void ActorComponent::setGameObject(GameObject* go)
{
	Component::setGameObject(go);

	// also store pointer for actor version
	actor = dynamic_cast<Actor*>(gameObject);
	// REFACTOR: use setActor for exclusively attaching actor component to actor
	// this will also avoid having static casts (you can also use ClassID for actors to
	// check hierarchy stuff and make your own no-RTTI dynamic cast)
	if (!actor)
		LOGERR("ActorComponent::setGameObject called with non actor game object");
}
