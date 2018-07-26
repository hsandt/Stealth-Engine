//
// Created by wing on 15/10/13.
//

#pragma once

#include "world/Component.h"

class Actor;

/// Abstract base class for all actor components
class ActorComponent : public Component {
public:
	ActorComponent();
	virtual ~ActorComponent() {};

	/// Return the type of this component (hiding base static method)
	static const ComponentType getComponentType() { return ComponentType::ACTOR_COMPONENT; }

	/// Return the actor this component is attached to
	Actor* getActor() const { return actor; }

	void setGameObject(GameObject* go) override;

protected:
	/// Actor this component is attached to (weak pointer)
	/// equivalent to dynamic_cast<Actor>(this->gameObject)
	Actor* actor = nullptr;

};

