//
// Created by wing on 15/10/13.
//

#pragma once

#include "Component.h"

class Actor;
class Renderer;

class ActorComponent : public Component {
public:
	ActorComponent();
	virtual ~ActorComponent() {};

	/// Return the actor this component is attached to
	Actor* getActor() const { return actor; }

	virtual void init() override;

protected:
	/// Actor this component is attached to (weak pointer)
	/// equivalent to dynamic_cast<Actor>(this->gameObject)
	Actor* actor = nullptr;

};

