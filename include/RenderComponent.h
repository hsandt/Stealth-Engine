//
// Created by wing on 15/10/13.
//

#pragma once

#include "Component.h"
#include "Renderer.h"

class GameObject;

class RenderComponent : public Component {
public:
    RenderComponent(std::shared_ptr<GameObject> gameObject);

    virtual void render(Renderer* renderer) = 0;

};

