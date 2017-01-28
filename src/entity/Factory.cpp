//
// Created by wing on 15/09/06.
//

#include "Factory.h"
#include "GameObjectCreator.h"
#include "ComponentCreator.h"

#include "Scene.h"
#include "GameObject.h"
#include "Character.h"

#include <iostream>

using namespace std;

int Factory::last_id = 0;

Factory::Factory() {
    gameObjectCreator = new GameObjectCreator();
    componentCreator = new ComponentCreator();
}

Factory::~Factory() {
    delete gameObjectCreator;
    delete componentCreator;
    std::cout << "[FACTORY] Factory destroyed" << std::endl;
}

void Factory::ChangeCurrentScene(Scene* scene) {
    gameObjectCreator->ChangeCurrentScene(scene);
}

/*
template<class T>
std::shared_ptr<T> Factory::Create() {
	// try to simulate type constraint
	// compile time check, should become if(true) / if(false) at compile time
	// and getting optimized for each T
	if (std::is_base_of<GameObject, T>::value) {
		shared_ptr<T> newGameObject = gameObjectCreator->Create();
		newGameObject->id = last_id;
		++last_id;
		return newGameObject;
	} else if (std::is_base_of<Component, T>::value) {
		shared_ptr<T> newComponent = componentCreator->Create();
		newComponent->id = last_id;
		++last_id;
		return newComponent;
	} else {
		cout << "[Warning] Calling Factory::Create on a type that is not subclassing GameObject." << endl;
	    return nullptr;
	}
}
 */

// moved to header to avoid undefined reference on non-specialized template

//template<class T>
//std::shared_ptr<T> Factory::CreateGameObject() {
//	shared_ptr<T> newGameObject = gameObjectCreator->Create<T>();
//	newGameObject->id = last_id;
//	++last_id;
//	return newGameObject;
//}
//
//template<class T>
//std::shared_ptr<T> Factory::CreateComponent() {
//	shared_ptr<T> newComponent = componentCreator->Create<T>();
//	newComponent->id = last_id;
//	++last_id;
//	return newComponent;
//}

