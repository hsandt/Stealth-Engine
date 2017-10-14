//
// Created by wing on 15/10/13.
//

#pragma once

#include <memory>

#include "component/ActorComponent.h"
#include "geometry/Vector2.h"

class Transform : public ActorComponent {

private:
    Vector2 position;

public:
    Transform();
    virtual ~Transform();

	static std::string getStringID() { return "Transform"; }

	std::string getClassStringID() const override { return getStringID(); }

    /// Set the actor position and update the rigidbody position
	void setPosition(const Vector2& newPosition);

    Vector2 getPosition() const;
};
