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
    virtual WindowManager* createWindowManager() const = 0;
    virtual Renderer* createRenderer() const = 0;
    virtual PhysicsManager* createPhysicsManager() const = 0;
    virtual ScriptManager* createScriptManager() const = 0;
    virtual Factory* createFactory() const = 0;
    virtual SceneManager* createSceneManager() const = 0;
    virtual InputManager* createInputManager() const = 0;
};
