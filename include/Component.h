//
// Created by wing on 15/10/13.
//

#pragma once

#include <memory>

#include "Object.h"

class GameObject;

class Component : public Object {
public:
    Component();
    virtual ~Component();
    Component(Component const &) = delete;
    Component &operator=(Component const &) = delete;

	std::shared_ptr<GameObject> getGameObject() const;

	virtual void onAddedToGameObject(std::shared_ptr<GameObject> gameObject) {}

protected:
    std::weak_ptr<GameObject> gameObject;

	// friendship is not inherited, we can safely give access to GameObject
	friend class GameObject;
};
