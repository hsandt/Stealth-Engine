#include "core/factory/GameManagerFactory.h"

#include "application/GLFWWindowManager.h"
#include "renderer/Renderer.h"
#include "physics/PhysicsManager.h"
#include "gameplay/ScriptManager.h"
#include "core/factory/Factory.h"
#include "world/SceneManager.h"
#include "input/InputManager.h"

WindowManager* GameManagerFactory::createWindowManager() {
    return new GLFWWindowManager();
}

Renderer* GameManagerFactory::createRenderer() {
    return new Renderer();
}

PhysicsManager* GameManagerFactory::createPhysicsManager() {
    return new PhysicsManager();
}

ScriptManager* GameManagerFactory::createScriptManager() {
    return new ScriptManager();
}

Factory* GameManagerFactory::createFactory() {
    return new Factory();
}

SceneManager* GameManagerFactory::createSceneManager() {
    return new SceneManager();
}

InputManager* GameManagerFactory::createInputManager() {
    return new InputManager();
}
