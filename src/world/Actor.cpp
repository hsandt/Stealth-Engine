//
// Created by wing on 15/10/12.
//

#include "world/GameObject.h"
#include "component/Transform.h"
#include "core/math/Vector2.h"

#include "world/Actor.h"

class Transform;

Actor::Actor() : GameObject()
{
//	transform = addComponent<Transform>();
}

Actor::~Actor() {

}

void Actor::init()
{
	GameObject::init();

	// TEST: safer after construction?
	transform = addComponent<Transform>();

}
