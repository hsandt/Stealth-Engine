//
// Created by wing on 15/10/12.
//

#pragma once

#include "entity/GameObject.h"

class Transform;

/**  GameObject present in a scene.
 *
 */
class Actor : public GameObject {

public:
    Actor();
    virtual ~Actor();
    Actor(const Actor &) = delete;
    Actor &operator=(const Actor &) & = delete;

    Transform* transform = nullptr;

	/// Add a new component of type T to this actor.
	template<class T>
	T* addComponent() {
		// Actor accepts both non-actor and actor components,
		// so we redefine a new addComponent, hiding effectively
		// the base version which is also templated and therefore cannot be virtual
		return addComponent_Internal<T>();
	}

protected:
	/// Return the default name of a new instance of this game object
	virtual std::string getDefaultName() const override { return "Actor"; }

};
