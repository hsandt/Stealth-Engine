//
// Created by wing on 15/10/12.
//

#include "Actor.h"

#include "Transform.h"

Actor::Actor(const int id, const std::string &name) :
    GameObject(id, name)
{
    AddComponent<Transform>();
}

Actor::~Actor() {

}
