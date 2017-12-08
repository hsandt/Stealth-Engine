//
// Created by Long Nguyen Huu on 2016/07/11.
//

#pragma once

#include <vector>

class ScriptComponent;

// REFACTOR: derive all component managers from a base class, possibly templated
class ScriptManager
{
private:
	/// All script components in the current scene (weak pointers)
	std::vector<ScriptComponent*> scripts;

public:
	ScriptManager();
	virtual ~ScriptManager();

    /// Start all scripts
    void start();

    /// Update all scripts
    void update(float dt);

    /// Register a new script component (weak pointer)
    void registerScript(ScriptComponent* script);

    /// Unregister a script component (weak pointer)
    void unregisterScript(ScriptComponent* script);
};


