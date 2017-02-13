//
// Created by wing on 15/10/13.
//

#pragma once

#include <memory>

#include "component/Component.h"
#include "geometry/Vector2.h"

class Transform : public Component {
public:
    Transform() : Component() {
    }
    virtual ~Transform();

    Vector2 position;

	void setPosition(const Vector2& newPosition) { position = newPosition; }
};
