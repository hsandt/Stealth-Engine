//
// Created by wing on 15/10/12.
//

#include "entity/GameObject.h"
#include "component/Transform.h"
#include "geometry/Vector2.h"

#include "entity/Actor.h"

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
