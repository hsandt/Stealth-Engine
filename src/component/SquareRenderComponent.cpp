//
// Created by wing on 15/10/13.
//

#include <iostream>
#include "Renderer.h"
#include "RenderComponent.h"

#include "SquareRenderComponent.h"

#include "GameObject.h"

using namespace std;

SquareRenderComponent::SquareRenderComponent() : RenderComponent() {}

void SquareRenderComponent::render(Renderer *renderer) {
    if (gameObject != nullptr)
    {
	    float w = 20, h = 20;

	    float x = gameObject->getPosition().x();
	    float y = gameObject->getPosition().y();
	    renderer->drawSquare(x - w / 2, y - h / 2, w, h);
    }
    else
    {
	    cout << "no go to lock" << endl;
    }

}
