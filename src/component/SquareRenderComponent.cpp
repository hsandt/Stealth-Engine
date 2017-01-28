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
    if (shared_ptr<GameObject> sp_GameObject = gameObject.lock())
    {
	    float w = 20, h = 20;

	    float x = sp_GameObject->getPosition().x();
	    float y = sp_GameObject->getPosition().y();
	    renderer->drawSquare(x - w / 2, y - h / 2, w, h);
    }
    else
    {
	    cout << "no go to lock" << endl;
    }

}
