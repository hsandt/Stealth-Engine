//
// Created by wing on 15/10/13.
//

#pragma once

#include <memory>

#include "Component.h"

class GameObject;
class Renderer;

class RenderComponent : public Component {
public:
    RenderComponent();
	virtual ~RenderComponent();

    virtual void onAddedToGameObject(std::shared_ptr<GameObject> gameObject) override;

    virtual void render(Renderer* renderer) = 0;

};

