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
	transform = addComponent<Transform>();

	// SIGSEGV
	// DEBUG
	if (transform == nullptr) {
		cout << "null transform" << endl;
	}
	transform -> position.x() = 0.0f;
//	transform -> position.y() = 0.0f;
	transform->setPosition(Vector2(1,2));
}

Actor::~Actor() {

}

//Transform* GameObject::addComponent<Transform>();