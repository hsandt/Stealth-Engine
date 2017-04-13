//
// Created by wing on 17/04/13.
//

#include <algorithm>
#include <vector>

#include "debug/Logger.h"
#include "scene/Scene.h"

#include "scene/SceneManager.h"

using namespace std;

SceneManager::SceneManager()
{
	LOG("[SceneManager] SceneManager constructed");
}

SceneManager::~SceneManager()
{
	LOG("[SceneManager] SceneManager destroyed");
}

void SceneManager::init()
{
	LOG("[SceneManager] SceneManager init");

	// TODO: check all scene asset files (game config, etc.)
	// and either dump them here directly or check the existence
	// of the corresponding scene asset files

	sceneNames.push_back("main");
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
	// 2. TODO: parse it and create a new Scene with the corresponding game objects
	// 3. TODO: set nextScene pointer to that new scene
	nextScene = new Scene();
	// 4. TODO: at the last moment, delete currentScene and set it to nextScene
	delete currentScene;  // does nothing if currentScene was nullptr ie on initial scene loading
	currentScene = nextScene;
	// 5. set nextScene to nullptr
	nextScene = nullptr;

	// ASYNC: for async loading, you should even set oldScene or tempScene to currentScene
	// so that we can delete it later, progressively, to avoid frame lag
}

