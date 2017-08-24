//
// Created by wing on 15/10/13.
//

#pragma once

#include "ComponentType.h"
#include "object/Object.h"

class GameObject;

// REFACTOR: separate into base Component and NonActorComponent
class Component : public Object {
	// friendship required for addComponent
	friend class GameObject;
	friend class Actor;

public:
    Component();
    virtual ~Component() {};

	/// Return the type of this component
	/// NOTE: currently unused since we used SFINAE for GameObject::addComponent but may be useful later
	static const ComponentType getComponentType() { return ComponentType::COMPONENT; }

	/// Register the component to the appropriate manager
	virtual void registerComponent() {};

	/// Unregister the component
	virtual void unregisterComponent() {};

	/// Return the game object this component is attached to
	GameObject* getGameObject() const { return gameObject; }

protected:
    GameObject* gameObject = nullptr;

};
