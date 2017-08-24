//
// Created by wing on 15/10/13.
//

#pragma once

#include <memory>

#include "component/ActorComponent.h"
#include "geometry/Vector2.h"

class Transform : public ActorComponent {
public:
    Transform() : ActorComponent() {
    }
    virtual ~Transform();

    Vector2 position;

	void setPosition(const Vector2& newPosition) { position = newPosition; }
};
