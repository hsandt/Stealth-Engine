//
// Created by wing on 17/04/13.
//

#pragma once

#include <vector>
#include <string>

class Scene;
class SceneData;

class SceneManager
{
private:
	/* Data */

	/// Vector of names of all available scenes
	std::vector<std::string> sceneNames;


	/* State vars */

	/// Current scene
	Scene* currentScene = nullptr;

	/// Next scene to load. nullptr when scene should not change.
	Scene* nextScene = nullptr;

	/// Name of the next scene to load. Empty string when scene should not change.
	std::string nextSceneName = "";

public:
	SceneManager();
	virtual ~SceneManager();

	SceneManager(const SceneManager &) = delete;
	SceneManager & operator=(const SceneManager &) & = delete;

	/// Initialize: store names of all available scenes
	void init();

	/// Return the current scene
	Scene* getCurrentScene() const { return currentScene; }

	/// Query the loading of a new scene on next game loop iteration
	void queryLoadScene(std::string name);

	/// Should a new scene be loaded, or the current scene be reloaded?
	bool shouldLoadScene() const;

	/// Load the next scene synchronously
	void loadNextScene();

private:
	/// Load a scene by name, parsing scene asset file
	void loadScene(std::string name);

};
