//
// Created by wing on 15/10/13.
//

#pragma once

#include <SDL2/SDL.h>
#include "Component.h"

class GameObject;

class RenderComponent : public Component {
public:
    RenderComponent(std::shared_ptr<GameObject> gameObject);

    virtual void render(SDL_Renderer* renderer) = 0;

};

