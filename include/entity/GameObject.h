//
//  GameObject.h
//  Stealth
//
//  Created by L Nguyen Huu on 04/02/27 H.
//  Copyright (c) 27 Heisei L Nguyen Huu. All rights reserved.
//

#pragma once

#include <string>
#include <vector>

#include "object/Object.h"

class Component;
class ActorComponent;
class Scene;

// REFACTOR: separate into base GameObject and NonActorGameObject
/* Generic game object, abstract or inside a scene */
class GameObject : public Object
{

public:
    GameObject();
    virtual ~GameObject();
    GameObject(const GameObject &) = delete;
    GameObject &operator=(const GameObject &) & = delete;

	/// Method called when this game object is added to a new scene
	void onAddedToScene(Scene* newScene);

	/* Component methods */

	template<class T>
	typename std::enable_if<std::is_base_of<Component, T>::value, T>::type*
	getComponent();

	/// Add a component to this game object
	template<class T>
	typename std::enable_if<!std::is_base_of<ActorComponent, T>::value, T>::type*
	addComponent();

	/// Remove a component from this game object
	void removeComponent(Component *component);

	/* Update */

    /// The game object's own update, besides the component updates (equivalent of UE4's AActor::Tick)
    virtual void update(float dt) {}

	/* Setters */

	void setNameToDefault() { name = getDefaultName(); }

	/* State vars */

	/// Readable name
	std::string name;

protected:
	/* Pointers */

	/// Scene containing this game object (weak pointer)
	Scene* scene;

	/// Components attached to this game object (shared pointer)
	std::vector<Component*> components;

	/// Return the default name of a new instance of this game object
	virtual std::string getDefaultName() const { return "GameObject"; }

	/// Add a component to this game object (internal)
	template<class T>
	T* addComponent_Internal();
};


#include "GameObject_TImpl.cpp"