//
// Created by wing on 15/09/06.
//

#pragma once

#include <memory>
#include <Locator.h>
#include <iostream>

class Scene;
//class GameObjectCreator;
//class ComponentCreator;

// required if defining template here; else include templ_impl.cpp at the end of the file
#include "GameObjectCreator.h"
#include "ComponentCreator.h"

class Factory {
public:
    Factory();
    virtual ~Factory();

    Factory(const Factory &) = delete;
    Factory &operator=(const Factory &) & = delete;
    Factory(Factory&&) = delete;
    Factory &operator=(Factory&&) & = delete;

    /// Template method to create any Object, T being the Object type
//    template<class T>
//    std::shared_ptr<T> Create();
//	template<class T>
//	std::shared_ptr<T> CreateGameObject();
//	template<class T>
//	std::shared_ptr<T> CreateComponent();

	// definition in header to avoid undefined reference on non-specialized template

	template<class T>
	T* CreateGameObject() {
		T* newGameObject = gameObjectCreator->Create<T>(last_id);
//		newGameObject->id = last_id;
		++last_id;
		return newGameObject;
	}

	template<class T>
	T* CreateComponent() {
		T* newComponent = componentCreator->Create<T>(last_id);
//		newComponent->id = last_id;
		++last_id;
		return newComponent;
	}


	void ChangeCurrentScene(Scene* scene);

private:
    static int last_id;

	GameObjectCreator* gameObjectCreator;
	ComponentCreator* componentCreator;

};
