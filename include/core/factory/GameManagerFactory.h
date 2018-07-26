#pragma once

#include "interfaces/core/factory/ManagerFactory.h"

class WindowManager;
class Renderer;
class PhysicsManager;
class ScriptManager;
class Factory;
class SceneManager;
class InputManager;

/// Factory to create concrete manager instances
class GameManagerFactory : public ManagerFactory {
public:
    WindowManager* createWindowManager() override;
    Renderer* createRenderer() override;
    PhysicsManager* createPhysicsManager() override;
    ScriptManager* createScriptManager() override;
    Factory* createFactory() override;
    SceneManager* createSceneManager() override;
    InputManager* createInputManager() override;
};
