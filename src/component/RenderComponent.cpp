//
// Created by wing on 15/10/13.
//

#include <memory>
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

void RenderComponent::onAddedToGameObject(std::shared_ptr<GameObject> gameObject) {
	Component::onAddedToGameObject(gameObject);  // does nothing

	// SIGSEGV error (not bad weak pointer), maybe because shared_from_this from base class
	// returns an Object? it worked with Character creation so why not component,
	// not sure, but may be fixed by using the base/child shared_from_this pattern
	// to get directly the RenderComponent shared pointer (and we are sure we have
	// at least one shared pointer to that). That said, we actually have a shared pointer to a Component...
	auto sp_ThisRenderComponent = static_pointer_cast<RenderComponent>(shared_from_this());

	// register render component to Renderer (use static cast,
	// dynamic only works if polymorphic base class i.e. a true virtual method)
	Locator::getRenderer()->registerRenderComponent(
			sp_ThisRenderComponent
//			this
	);
}

