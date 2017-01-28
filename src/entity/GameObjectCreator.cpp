//
// Created by wing on 17/01/14.
//

#include <memory>
#include <iostream>

#include "GameObjectCreator.h"

#include "GameObject.h"
#include "Scene.h"

using namespace std;

//template<class T>
//shared_ptr<T> GameObjectCreator::Create() {
//	auto go = make_shared<T>("GameObject");
//	if (shared_ptr<Scene> sp_CurrentScene = currentScene.lock()) {
//		// convert back to base GameObject shared pointer
//		sp_CurrentScene->addGameObject(static_pointer_cast<GameObject>(go));
//		cout << "Game object created and added to current scene" << endl;
//		return go;
//	} else {
//		cout << "Current scene has expired, don't create game object" << endl;
//		return nullptr;
//	}
//}

void GameObjectCreator::ChangeCurrentScene(std::shared_ptr<Scene> scene) {
	currentScene = scene;
}
