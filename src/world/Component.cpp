//
// Created by wing on 15/10/13.
//

#include <iostream>

#include "world/Object.h"

#include "world/Component.h"

using namespace std;

Component::Component() : Object()
{

}

void Component::setGameObject(GameObject* go)
{
	if (gameObject)
		throw std::runtime_error("[COMPONENT] Cannot change the game world of a once attached components.");
	gameObject = go;
}
