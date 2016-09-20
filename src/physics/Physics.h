//
// Created by acro_ on 2016/07/11.
//

#pragma once

#include "Box2D/Box2D.h"

class Physics
{
private:
	b2World *world = nullptr;
	b2Vec2 gravity = {0.f, 0.f};

public:
	Physics(b2Vec2 gravity);
	virtual ~Physics();

	/// Set gravity
	void SetGravity(b2Vec2 gravity)
	{
		this->gravity = gravity;
	}
};


