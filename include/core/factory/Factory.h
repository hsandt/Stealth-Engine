//
// Created by wing on 15/09/06.
//

#pragma once

#include <memory>

// required if defining template here; else include templ_impl.cpp at the end of the file
#include "GameObjectCreator.h"
#include "ComponentCreator.h"
#include "core/EngineCore.h"
#include "world/SceneManager.h"
#include "world/Scene.h"

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
		bool addedToScene = AddGameObjectToCurrentScene(newGameObject);
		if (!addedToScene)
		{
			delete newGameObject;
			return nullptr;
		}

		++last_id;
		return newGameObject;
	}

	// TODO: add CreateActor, a variant for Actors that takes initial position parameter

	// REFACTOR: prevent that except when adding to existing world
	/// Create a new component
	template<class T>
	T* CreateComponent() {
		T* newComponent = componentCreator->Create<T>(last_id);
		++last_id;
		return newComponent;
	}

private:

    bool AddGameObjectToCurrentScene(GameObject* go) {
        Scene* currentScene = EngineCore::getSceneManager()->getCurrentScene();
        if (currentScene != nullptr)
        {
            // add the created game world to the current scene (shared pointer)
            currentScene->addGameObject(go);
            std::cout << "Game world created and added to current scene" << std::endl;
            return true;
        }
        else
        {
            std::cout << "Current scene has expired, don't create game world" << std::endl;
            return false;
        }
    }

    static int last_id;

	GameObjectCreator* gameObjectCreator;
	ComponentCreator* componentCreator;

};
