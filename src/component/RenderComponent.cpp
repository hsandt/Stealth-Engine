//
// Created by wing on 15/10/13.
//

#include "component/ActorComponent.h"
#include "renderer/Renderer.h"
#include "core/EngineCore.h"

#include "component/RenderComponent.h"

using namespace std;

RenderComponent::RenderComponent() : ActorComponent()
{

}

void RenderComponent::onAddedToGameObject() {
	// register render component to Renderer (use static cast,
	// dynamic only works if polymorphic base class i.e. a true virtual method)
	EngineCore::getRenderer()->registerRenderComponent(this);
}

void RenderComponent::onRemovedFromGameObject()
{
	EngineCore::getRenderer()->unregisterRenderComponent(this);
}
