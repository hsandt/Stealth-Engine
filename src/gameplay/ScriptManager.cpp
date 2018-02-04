//
// Created by acro_ on 2016/07/11.
//

#include <stdexcept>

#include "gameplay/ScriptManager.h"

#include "component/ScriptComponent.h"
#include "core/Logger.h"
#include "world/GameObject.h"

using namespace std;

ScriptManager::ScriptManager() {
	LOG("[ScriptManager] Script manager created");
}

ScriptManager::~ScriptManager() {
	LOG("[ScriptManager] Script manager destroyed");
}

void ScriptManager::start()
{
    for (auto script : scripts)
    {
        if (script)
	        script->start();
    }
}

void ScriptManager::update(float dt)
{
    for (auto script : scripts)
    {
        if (script)
	        script->update(dt);
    }
}

void ScriptManager::registerScript(ScriptComponent *script)
{
    if (!script)
        throw invalid_argument("[ScriptManager] Cannot register script: nullptr");

    scripts.push_back(script);  // shared to weak pointer conversion
}

void ScriptManager::unregisterScript(ScriptComponent *script)
{
    if (!script)
        throw invalid_argument("[ScriptManager] Cannot unregister script: nullptr");

    auto it = find(scripts.begin(), scripts.end(), script);

    // REFACTOR: make a util function to remove element when present in container
    if (it != scripts.end())
    {
        // here, components == *it
        scripts.erase(it);
    }
    else
    {
        LOGERRF("[ScriptManager] Script on %s not registered by ScriptManager, could not unregister", script->getGameObject()->name.c_str());
    }
}
