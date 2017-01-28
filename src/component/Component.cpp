//
// Created by wing on 15/10/13.
//

#include <iostream>

#include "Component.h"

using namespace std;

Component::Component() {

}

Component::~Component() {

}

shared_ptr<GameObject> Component::getGameObject() const {
	if (shared_ptr<GameObject> sp_GameObject = gameObject.lock()) {
		return sp_GameObject;
	}
	else {
		cout << "Game object has expired, don't create game object" << endl;
		return nullptr;
	}
}
