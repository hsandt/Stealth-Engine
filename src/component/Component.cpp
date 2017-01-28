//
// Created by wing on 15/10/13.
//

#include <iostream>

#include "Component.h"

using namespace std;

Component::Component() {

}

Component::~Component() {
	if (gameObject != nullptr) {
		cout << "Component destroyed (as part of game object)" << endl;
	} else {
		cout << "Component destroyed (first removed)" << endl;
	}
}

GameObject* Component::getGameObject() const {
	if (gameObject != nullptr) {
		return gameObject;
	}
	else {
		cout << "Game object has expired, don't create game object" << endl;
		return nullptr;
	}
}

void Component::detachFromGameObject() {
	gameObject = nullptr;
}
