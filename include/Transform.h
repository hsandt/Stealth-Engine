//
// Created by wing on 15/10/13.
//

#pragma once

#include <memory>

#include "Component.h"
#include "GameObject.h"

class Transform : public Component {
public:
    Transform(std::shared_ptr<GameObject> gameObject) : Component(gameObject) {}
    virtual ~Transform();

    Vec3f position;
};
