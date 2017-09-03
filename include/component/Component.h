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

	// void init() override is not added here because there is no specific behavior added
	// but note that you should override init() and not fill the constructor for things that require the gameObject

	/// Set the game object this component is attached to (can be done only once)
	virtual void setGameObject(GameObject* go);

	/// Method called after the component has been added to a game object.
	/// Typically: initializes value that could not be in the constructor because they required game object reference,
	/// register the component to the appropriate manager.
	virtual void onAddedToGameObject() {};

	/// Method called just before the component is removed from its game object.
	/// This allows us to still access the game object a last time for cleanup.
	/// Typically: unregister the component from the appropriate manager.
	virtual void onRemovedFromGameObject() {};

	/// Return the game object this component is attached to
	GameObject* getGameObject() const { return gameObject; }

protected:
    GameObject* gameObject = nullptr;

};
