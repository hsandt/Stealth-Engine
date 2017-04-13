//
// Created by wing on 17/04/11.
//

#pragma once

#include <string>

struct GameConfig
{
	/// Game application title
	std::string title = "My Game";

	/// Initial window width
	int initialWindowWidth = 0;

	/// Initial window height
	int initialWindowHeight = 0;

	/// Target frames per second, used to compute the loop iteration period
	int fps = 30;

	/// Name of the initial scene to load
	char initialSceneName[40] = "main";
};