//
// Created by Long Nguyen Huu on 2016/07/11.
//

#pragma once

#include <Box2D/Box2D.h>

#include "geometry/Vector2.h"

class Physics
{
private:
	b2World* world = nullptr;

public:
	Physics(Vector2 gravity);
	virtual ~Physics();

	/// Get world gravity
	Vector2 GetGravity () const
	{
		return world->GetGravity();
	}

	/// Set world gravity
	void SetGravity(Vector2 gravity)
	{
		world->SetGravity(gravity);
	}

};


