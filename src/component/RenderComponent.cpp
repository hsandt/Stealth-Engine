//
// Created by wing on 15/10/13.
//

#include "Locator.h"
#include "Component.h"

#include "RenderComponent.h"

#include "Renderer.h"

using namespace std;

RenderComponent::RenderComponent() : Component()
{

}

RenderComponent::~RenderComponent() {

}

void RenderComponent::onAddedToGameObject() {
	Component::onAddedToGameObject();  // does nothing

	// register render component to Renderer (use static cast,
	// dynamic only works if polymorphic base class i.e. a true virtual method)
	Locator::getRenderer()->registerRenderComponent(this);
}

