//
// Created by wing on 15/10/13.
//

#pragma once

#include <memory>

#include "RenderComponent.h"

class SquareRenderComponent : public RenderComponent {
public:
//    SquareRenderComponent(std::weak_ptr<GameObject> gameObject);
    SquareRenderComponent();

private:
    virtual void render(Renderer *renderer) override;
};
