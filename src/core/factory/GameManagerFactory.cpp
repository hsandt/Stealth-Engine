#include "core/factory/GameManagerFactory.h"

#include "application/GLFWWindowManager.h"
#include "renderer/Renderer.h"
#include "physics/PhysicsManager.h"
#include "gameplay/ScriptManager.h"
#include "core/factory/Factory.h"
#include "world/SceneManager.h"
#include "input/InputManager.h"

WindowManager* GameManagerFactory::createWindowManager() const
{
    return new GLFWWindowManager();
}

Renderer* GameManagerFactory::createRenderer() const
{
    return new Renderer();
}

PhysicsManager* GameManagerFactory::createPhysicsManager() const
{
    return new PhysicsManager();
}

ScriptManager* GameManagerFactory::createScriptManager() const
{
    return new ScriptManager();
}

Factory* GameManagerFactory::createFactory() const
{
    return new Factory();
}

SceneManager* GameManagerFactory::createSceneManager() const
{
    return new SceneManager();
}

InputManager* GameManagerFactory::createInputManager() const
{
    return new InputManager();
}
