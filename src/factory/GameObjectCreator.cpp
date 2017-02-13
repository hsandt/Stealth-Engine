//
// Created by wing on 17/01/14.
//

#include <iostream>

#include "factory/GameObjectCreator.h"

using namespace std;

void GameObjectCreator::ChangeCurrentScene(Scene* scene) {
	currentScene = scene;
}
