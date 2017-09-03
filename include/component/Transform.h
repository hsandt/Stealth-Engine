//
// Created by wing on 15/10/13.
//

#pragma once

#include <memory>

#include "component/ActorComponent.h"
#include "geometry/Vector2.h"

class Transform : public ActorComponent {
public:
    Transform();
    virtual ~Transform();

	static std::string getStringID() { return "Transform"; }

	std::string getClassStringID() const override { return getStringID(); }

	Vector2 position;

	void setPosition(const Vector2& newPosition) { position = newPosition; }
};
