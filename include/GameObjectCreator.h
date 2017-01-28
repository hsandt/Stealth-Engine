//
// Created by wing on 17/01/14.
//

#pragma once

#include <memory>

#include "Creator.h"

//class Scene;
#include "Scene.h"
// required if defining template in header

class GameObjectCreator : public Creator {
public:
//	template<class T>
//	std::shared_ptr<T> Create();

	// defined in header, else include templ_impl.cpp at the end of the file
	template<class T>
	std::shared_ptr<T> Create(const int id) {
		auto go = std::make_shared<T>("GameObject");
		go->id = id;
		go->init();
		if (std::shared_ptr<Scene> sp_CurrentScene = currentScene.lock()) {
			// convert back to base GameObject shared pointer
			sp_CurrentScene->addGameObject(std::static_pointer_cast<GameObject>(go));
			std::cout << "Game object created and added to current scene" << std::endl;
			return go;
		} else {
			std::cout << "Current scene has expired, don't create game object" << std::endl;
			return nullptr;
		}
}

	void ChangeCurrentScene(std::shared_ptr<Scene> scene);

private:
	// current scene, to which all new objects should be added
	std::weak_ptr<Scene> currentScene;
};

