//
// Created by wing on 15/10/13.
//

#pragma once

#include "RenderComponent.h"

class SquareRenderComponent : public RenderComponent {
    virtual void render(SDL_Renderer *renderer) override;
};
