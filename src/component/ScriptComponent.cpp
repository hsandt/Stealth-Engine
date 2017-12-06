//
// Created by wing on 17/09/03.
//

#include "include/component/ScriptComponent.h"

#include "include/core/EngineCore.h"
#include "include/service/ScriptManager.h"

ScriptComponent::ScriptComponent()
{

}

ScriptComponent::~ScriptComponent()
{

}

void ScriptComponent::onAddedToGameObject()
{
	ActorComponent::onAddedToGameObject();

	EngineCore::getScriptManager()->registerScript(this);
}

void ScriptComponent::onRemovedFromGameObject()
{
	ActorComponent::onRemovedFromGameObject();

	EngineCore::getScriptManager()->unregisterScript(this);
}
