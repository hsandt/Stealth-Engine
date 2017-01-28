//
// Created by wing on 15/10/12.
//

#include "Actor.h"
#include "GameObject.h"

#include "Transform.h"

Actor::Actor(const std::string &name) :
    GameObject(name)
{
//    AddComponent<Transform>();
}

Actor::~Actor() {

}
