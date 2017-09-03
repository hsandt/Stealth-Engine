//
// Created by wing on 15/10/13.
//

#pragma once

#include "component/ActorComponent.h"

class Renderer;

class RenderComponent : public ActorComponent {
public:
    RenderComponent();
	virtual ~RenderComponent() {};

	virtual void onAddedToGameObject() override;
    virtual void onRemovedFromGameObject() override;

    virtual void render(Renderer* renderer) = 0;

};

