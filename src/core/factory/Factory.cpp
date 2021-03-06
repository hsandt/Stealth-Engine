//
// Created by wing on 15/09/06.
//

#include "core/factory/Factory.h"
#include "core/factory/GameObjectCreator.h"
#include "core/factory/ComponentCreator.h"

#include "core/Logger.h"
#include "world/GameObject.h"
#include "world/Scene.h"


using namespace std;

int Factory::last_id = 0;

Factory::Factory() {
    gameObjectCreator = new GameObjectCreator();
    componentCreator = new ComponentCreator();
}

Factory::~Factory() {
    delete gameObjectCreator;
    delete componentCreator;
    LOG("[FACTORY] Factory destroyed");
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
