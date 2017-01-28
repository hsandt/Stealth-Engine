//
// Created by wing on 15/10/13.
//

#pragma once

#include "Object.h"

class GameObject;

class Component : public Object {
public:
    Component();
    virtual ~Component();
    Component(Component const &) = delete;
    Component &operator=(Component const &) = delete;

	GameObject* getGameObject() const;

	virtual void onAddedToGameObject() {}

	void detachFromGameObject();

protected:
    GameObject* gameObject;

	// friendship is not inherited, we can safely give access to GameObject
	friend class GameObject;
};
