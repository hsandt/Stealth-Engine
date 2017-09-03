//
// Created by Long Nguyen Huu on 2016/07/11.
//

#pragma once

#include <stdexcept>

#include <Box2D/Box2D.h>

#include "component/Transform.h"
#include "entity/Actor.h"
#include "geometry/Vector2.h"

class PhysicsManager
{
private:
	b2World* world = nullptr;

public:
	PhysicsManager();
	virtual ~PhysicsManager();

	/// Get world gravity
	inline Vector2 getGravity () const
	{
		return world->GetGravity();
	}

	/// Set world gravity
	inline void setGravity(Vector2 gravity)
	{
		world->SetGravity(gravity);
	}

	b2Body* createBody(Actor* actor);

	inline void destroyBody(b2Body* body)
	{
		if (body == nullptr)
			throw invalid_argument("[PHYSICS MANAGER] Cannot destroy body: nullptr");

		world->DestroyBody(body);
	}

};


