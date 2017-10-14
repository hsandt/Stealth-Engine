//
// Created by wing on 15/10/13.
//

#include "component/Transform.h"
#include "entity/Actor.h"
#include "physics/Rigidbody.h"

Transform::Transform() {

}

Transform::~Transform() {

}

Vector2 Transform::getPosition() const
{
    return position;
}

void Transform::setPosition(const Vector2 &newPosition)
{
    position = newPosition;

    // if this actor has a rigidbody, update its position accordingly
    Rigidbody* rigidbody = actor->getComponent<Rigidbody>();
    if (rigidbody)
    {
        rigidbody->setPosition(newPosition);
    }
}

