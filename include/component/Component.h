//
// Created by wing on 15/10/13.
//

#pragma once

#include "object/Object.h"

class GameObject;

class Component : public Object {
	// friendship is not inherited, we can safely give access to GameObject
	friend class GameObject;

public:
    Component();
    virtual ~Component() {};

	/// Register the component to the appropriate manager
	virtual void registerComponent() {};

	/// Unregister the component
	virtual void unregisterComponent() {};

	/// Return the game object this component is attached to
	GameObject* getGameObject() const { return gameObject; }

protected:
    GameObject* gameObject = nullptr;

};
