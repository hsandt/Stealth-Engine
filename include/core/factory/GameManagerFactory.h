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
    WindowManager* createWindowManager() const override;
    Renderer* createRenderer() const override;
    PhysicsManager* createPhysicsManager() const override;
    ScriptManager* createScriptManager() const override;
    Factory* createFactory() const override;
    SceneManager* createSceneManager() const override;
    InputManager* createInputManager() const override;
};
