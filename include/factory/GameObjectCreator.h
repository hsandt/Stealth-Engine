//
// Created by wing on 17/01/14.
//

#pragma once

#include <iostream>

#include "core/EngineCore.h"
#include "scene/SceneManager.h"
#include "scene/Scene.h"

class GameObjectCreator {
public:

	// defined in header, else include templ_impl.cpp at the end of the file
	template<class T>
	T* Create(const int id) {
		auto go = new T();
		go->id = id;
		go->setNameToDefault();
		go->init();

		Scene* currentScene = EngineCore::getSceneManager()->getCurrentScene();
		if (currentScene != nullptr) {
			// add the created game object to the current scene (shared pointer)
			currentScene->addGameObject(go);
			std::cout << "Game object created and added to current scene" << std::endl;
			return go;
		} else {
			std::cout << "Current scene has expired, don't create game object" << std::endl;
			return nullptr;
		}
	}
};

