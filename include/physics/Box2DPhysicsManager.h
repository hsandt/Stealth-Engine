//
// Created by Long Nguyen Huu on 2016/07/11.
//

#pragma once

#include <stdexcept>
#include <vector>

#include "interfaces/physics/PhysicsManager.h"

#include "core/math/Vector2.h"

class b2Body;
class b2World;

class Box2DPhysicsManager : public PhysicsManager
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
	Box2DPhysicsManager();
	virtual ~Box2DPhysicsManager();

	/// Get world gravity
	inline Vector2 getGravity() const override;

	/// Set world gravity
	inline void setGravity(Vector2 gravity) override;

	virtual b2Body* createBody(Actor* actor) override;
	virtual b2Body* createDynamicBody(Actor* actor) override;

	inline void destroyBody(b2Body* body) override;

    /// Start all rigidbodies
    void start() override;

    /// Apply physics time step
    void update(float dt) override;

    /// Register a new render component (weak pointer)
    void registerRigidbody(Rigidbody* rigidbody) override;

    /// Unregister a render component (weak pointer)
    void unregisterRigidbody(Rigidbody* rigidbody) override;
};


