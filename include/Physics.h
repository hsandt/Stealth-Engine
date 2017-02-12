//
// Created by Long Nguyen Huu on 2016/07/11.
//

#pragma once

#include <memory>
#include "Box2D/Box2D.h"

#include "geometry/Vector2.h"

class Physics
{
private:
	std::unique_ptr<b2World> world = nullptr;

public:
	Physics(Vec2f gravity);
	virtual ~Physics();

	/// Get world gravity
	Vec2f GetGravity () const
	{
		return world->GetGravity();
	}

	/// Set world gravity
	void SetGravity(Vec2f gravity)
	{
		world->SetGravity(gravity);
	}

};


