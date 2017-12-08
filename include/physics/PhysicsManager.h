//
// Created by Long Nguyen Huu on 2016/07/11.
//

#pragma once

#include <stdexcept>

#include <Box2D/Box2D.h>

#include "component/Transform.h"
#include "world/Actor.h"
#include "core/math/Vector2.h"

class Rigidbody;

class PhysicsManager
{
private:
	/// Physics world
	b2World* world = nullptr;

	// Physics parameters
    float32 timeStep;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

	/// All Render components in the current scene (weak pointers)
	std::vector<Rigidbody*> rigidbodies;

public:
	PhysicsManager();
	virtual ~PhysicsManager();

	/// Get world gravity
	inline Vector2 getGravity() const
	{
		return world->GetGravity();
	}

	/// Set world gravity
	inline void setGravity(Vector2 gravity)
	{
		world->SetGravity(gravity);
	}

	b2Body* createBody(Actor* actor);
	b2Body* createDynamicBody(Actor* actor);

	inline void destroyBody(b2Body* body)
	{
		if (body == nullptr)
			throw invalid_argument("[PHYSICS MANAGER] Cannot destroy body: nullptr");

		world->DestroyBody(body);
	}

    /// Start all rigidbodies
    void start();

    /// Apply physics time step
    void update(float dt);

    /// Register a new render component (weak pointer)
    void registerRigidbody(Rigidbody* rigidbody);

    /// Unregister a render component (weak pointer)
    void unregisterRigidbody(Rigidbody* rigidbody);
};


