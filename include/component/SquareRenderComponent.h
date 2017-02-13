//
// Created by wing on 15/10/13.
//

#pragma once

#include <memory>

#include "RenderComponent.h"

class SquareRenderComponent : public RenderComponent {
public:
    SquareRenderComponent();

private:
    virtual void render(Renderer *renderer) override;
};
