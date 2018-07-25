//
// Created by wing on 17/04/13.
//

#include <algorithm>
#include <vector>

#include "core/Logger.h"
#include "world/Scene.h"
#include "world/SceneData.h"

#include "world/SceneManager.h"

using namespace std;

SceneManager::SceneManager()
{
	LOG("[SCENE MANAGER] SceneManager constructed");
}

SceneManager::~SceneManager()
{
	LOG("[SCENE MANAGER] SceneManager destroyed");
	delete currentScene;
}

void SceneManager::init()
{
	LOG("[SCENE MANAGER] SceneManager init");

	// TODO: check all scene asset files (game config, etc.)
	// and either dump them here directly or check the existence
	// of the corresponding scene asset files

	sceneNames.emplace_back("main");
}

void SceneManager::queryLoadScene(std::string name)
{
	auto it = find(sceneNames.begin(), sceneNames.end(), name);
	if (it != sceneNames.end())
		nextSceneName = name;
	else
		LOGERRF("[SceneManager] Scene %s is not a valid scene name.", name.c_str());
}

bool SceneManager::shouldLoadScene() const
{
	return nextSceneName != "";
}

void SceneManager::loadNextScene()
{
	loadScene(nextSceneName);
	// 6. set nextSceneName to "" (done here since technically, loadScene
	// is not aware of nextSceneName)
	nextSceneName = "";
}

void SceneManager::loadScene(std::string name)
{
	// 1. TODO: open the scene asset file corresponding to name
	// 2. TODO: parse it and create a Scene Data with the corresponding game objects
	SceneData sceneData;
	sceneData.name = name;
	// 3. TODO: set nextScene to a new Scene, initialized with said Scene Data
	nextScene = new Scene();
	nextScene->init(sceneData);
	// 4. TODO: at the last moment, delete currentScene and set it to nextScene
	delete currentScene;  // does nothing if currentScene was nullptr ie on initial scene loading
	currentScene = nextScene;
	// 5. set nextScene to nullptr
	nextScene = nullptr;

	// ASYNC: for async loading, you should even set oldScene or tempScene to currentScene
	// so that we can delete it later, progressively, to avoid frame lag
}

