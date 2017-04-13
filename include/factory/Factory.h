//
// Created by wing on 15/09/06.
//

#pragma once

#include <memory>

// required if defining template here; else include templ_impl.cpp at the end of the file
#include "factory/GameObjectCreator.h"
#include "factory/ComponentCreator.h"

class Scene;

class Factory {
public:
    Factory();
    virtual ~Factory();

    Factory(const Factory &) = delete;
    Factory &operator=(const Factory &) & = delete;
    Factory(Factory&&) = delete;
    Factory &operator=(Factory&&) & = delete;

	// definitions in header to avoid undefined reference on non-specialized template

	/// Create a new game object in the current scene
	template<class T>
	T* CreateGameObject() {
		T* newGameObject = gameObjectCreator->Create<T>(last_id);
		++last_id;
		return newGameObject;
	}

	// REFACTOR: prevent that except when adding to existing object
	/// Create a new component
	template<class T>
	T* CreateComponent() {
		T* newComponent = componentCreator->Create<T>(last_id);
		++last_id;
		return newComponent;
	}

private:
    static int last_id;

	GameObjectCreator* gameObjectCreator;
	ComponentCreator* componentCreator;

};
