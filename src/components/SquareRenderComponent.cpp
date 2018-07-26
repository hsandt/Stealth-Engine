//
// Created by wing on 15/10/13.
//

#include "component/SquareRenderComponent.h"

#include "component/RenderComponent.h"
#include "component/Transform.h"
#include "core/Logger.h"
#include "interfaces/renderer/Renderer.h"
#include "world/Actor.h"

SquareRenderComponent::SquareRenderComponent() : RenderComponent() {}

void SquareRenderComponent::render(Renderer *renderer) {
    if (actor != nullptr)
    {
	    const float w = 20, h = 20;

	    float x = actor->transform->getPosition().x();
	    float y = actor->transform->getPosition().y();
	    renderer->drawSquare(x - w / 2, y - h / 2, w, h);
    }
    else
    {
	    LOG("[SquareRenderComponent] no game world");
    }

}

