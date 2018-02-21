//
// Created by wing on 15/10/13.
//

#pragma once

#include <memory>

#include "RenderComponent.h"

class SquareRenderComponent : public RenderComponent {
public:
    SquareRenderComponent();

	static std::string getStringID() { return "SquareRenderComponent"; }
	std::string getClassStringID() const override { return getStringID(); }

private:
    virtual void render(Renderer *renderer) override;
};
