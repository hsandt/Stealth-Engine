#include "core/factory/GameManagerFactory.h"

#include "application/GLFWWindowManager.h"
#include "renderer/GLRenderer.h"
#include "physics/Box2DPhysicsManager.h"
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
    return new GLRenderer();
}

PhysicsManager* GameManagerFactory::createPhysicsManager() const
{
    return new Box2DPhysicsManager();
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
