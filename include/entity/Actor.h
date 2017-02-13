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

protected:
	/// Return the default name of a new instance of this game object
	virtual std::string getDefaultName() const override { return "Actor"; }

};
