//
// Created by wing on 15/10/13.
//

#pragma once

#include <memory>

#include "Component.h"
#include "GameObject.h"

class Transform : public Component {
public:
    Transform() : Component() {}
    virtual ~Transform();

    Vector3 position;
};
