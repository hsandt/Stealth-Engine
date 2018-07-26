#pragma once

class Logger;
class WindowManager;
class Renderer;
class PhysicsManager;
class ScriptManager;
class Factory;
class SceneManager;
class InputManager;

/// Factory to create concrete manager instances
class ManagerFactory {
public:
    virtual WindowManager* createWindowManager() = 0;
    virtual Renderer* createRenderer() = 0;
    virtual PhysicsManager* createPhysicsManager() = 0;
    virtual ScriptManager* createScriptManager() = 0;
    virtual Factory* createFactory() = 0;
    virtual SceneManager* createSceneManager() = 0;
    virtual InputManager* createInputManager() = 0;
};
