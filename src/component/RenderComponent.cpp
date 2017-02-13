//
// Created by wing on 15/10/13.
//

#include "component/ActorComponent.h"
#include "renderer/Renderer.h"
#include "service/Locator.h"

#include "component/RenderComponent.h"

using namespace std;

RenderComponent::RenderComponent() : ActorComponent()
{

}

void RenderComponent::registerComponent() {
	// register render component to Renderer (use static cast,
	// dynamic only works if polymorphic base class i.e. a true virtual method)
	Locator::getRenderer()->registerRenderComponent(this);
}

void RenderComponent::unregisterComponent()
{
	Locator::getRenderer()->unregisterRenderComponent(this);
}
