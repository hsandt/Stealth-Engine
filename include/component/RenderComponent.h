//
// Created by wing on 15/10/13.
//

#pragma once

#include "component/ActorComponent.h"

class RenderComponent : public ActorComponent {
public:
    RenderComponent();
	virtual ~RenderComponent() {};

	static std::string getStringID() { return "RenderComponent"; }
	std::string getClassStringID() const override { return getStringID(); }

	virtual void onAddedToGameObject() override;
    virtual void onRemovedFromGameObject() override;

    virtual void render(Renderer* renderer) = 0;

};

