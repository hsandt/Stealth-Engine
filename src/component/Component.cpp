//
// Created by wing on 15/10/13.
//

#include <iostream>

#include "object/Object.h"

#include "component/Component.h"

using namespace std;

Component::Component() : Object()
{

}

void Component::setGameObject(GameObject* go)
{
	if (gameObject)
		throw std::runtime_error("[COMPONENT] Cannot change the game object of a once attached component.");
	gameObject = go;
}
