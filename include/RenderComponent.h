//
// Created by wing on 15/10/13.
//

#pragma once

#include "Component.h"

class GameObject;
class Renderer;

class RenderComponent : public Component {
public:
    RenderComponent();
	virtual ~RenderComponent();

    virtual void onAddedToGameObject() override;

    virtual void render(Renderer* renderer) = 0;

};

