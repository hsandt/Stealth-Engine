//
// Created by wing on 15/10/13.
//

#pragma once

#include <string>

#include "ComponentType.h"
#include "object/Object.h"

class GameObject;

/// Abstract base class for all components
/// Note that concrete subclasses should implement static std::string getStringID()
// REFACTOR: separate into base Component and NonActorComponent
// this will also allow us to set getComponentType = 0 to make the class abstract
// and prevent AddComponent<Component>
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

	virtual std::string getClassStringID() const = 0;

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

	/// Game start callback: called on game start if this component is on an active object in the scene,
	/// or has just been added during play
	virtual void start() {}

	/// Update callback: called during play if this component is on an active object
	virtual void update() {}

protected:
    GameObject* gameObject = nullptr;

};
