//
// Created by wing on 17/01/14.
//

#pragma once

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
	T* Create(const int id) {
		auto go = new T("GameObject");
		go->id = id;
		go->init();
		if (currentScene != nullptr) {
			// convert back to base GameObject shared pointer
			currentScene->addGameObject(go);
			std::cout << "Game object created and added to current scene" << std::endl;
			return go;
		} else {
			std::cout << "Current scene has expired, don't create game object" << std::endl;
			return nullptr;
		}
}

	void ChangeCurrentScene(Scene* scene);

private:
	// current scene, to which all new objects should be added
	Scene* currentScene;
};

