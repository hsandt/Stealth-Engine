//
// Created by wing on 17/09/03.
//

#pragma once

#include <string>

#include "component/ActorComponent.h"

// REFACTOR: non-actor game objects may need scripts too
// so make a ScriptComponent : Component and an ActorScript : ScriptComponent
// if you want to avoid two parallel class inheritance families (this one and ActorComponent : Component)
// doing the same thing, add some "interface" (a simple base class) IHasActor which simply adds the
// game object to actor conversion on construction and getActor method
class ScriptComponent : public ActorComponent
{
private:

public:
	ScriptComponent();
	virtual ~ScriptComponent();

	static std::string getStringID() { return "ScriptComponent"; }
	std::string getClassStringID() const override { return getStringID(); }

	void onAddedToGameObject() override;
	void onRemovedFromGameObject() override;
};


