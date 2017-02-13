//
// Created by wing on 15/10/13.
//

#include <iostream>

#include "component/RenderComponent.h"
#include "component/Transform.h"
#include "entity/Actor.h"
#include "renderer/Renderer.h"

#include "component/SquareRenderComponent.h"

using namespace std;

SquareRenderComponent::SquareRenderComponent() : RenderComponent() {}

void SquareRenderComponent::render(Renderer *renderer) {
    if (actor != nullptr)
    {
	    const float w = 20, h = 20;

	    float x = actor->transform->position.x();
	    float y = actor->transform->position.y();
	    renderer->drawSquare(x - w / 2, y - h / 2, w, h);

	    cout << "[SquareRenderComponent] " << x << " " << y << endl;
    }
    else
    {
	    cout << "[SquareRenderComponent] no game object" << endl;
    }

}

