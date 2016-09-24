//
// Created by wing on 15/10/13.
//

#pragma once

#include "RenderComponent.h"

class SquareRenderComponent : public RenderComponent {
public:
    SquareRenderComponent(std::shared_ptr<GameObject> gameObject);

private:
    virtual void render(Renderer *renderer) override;
};
