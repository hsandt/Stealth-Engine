#pragma once

#include "core/math/Vector2.h"

class Actor;
class b2Body;
class Rigidbody;

class PhysicsManager
{
public:
	/// Get world gravity
	virtual Vector2 getGravity() const = 0;
    virtual void setGravity(Vector2 gravity) = 0;
    // TODO: remove all references to Box2D
    virtual b2Body* createBody(Actor* actor) = 0;
    virtual b2Body* createDynamicBody(Actor* actor) = 0;
    virtual void destroyBody(b2Body* body) = 0;

    /// Start all rigidbodies
    virtual void start() = 0;

    /// Apply physics time step
    virtual void update(float dt) = 0;

    /// Register a new render component (weak pointer)
    virtual void registerRigidbody(Rigidbody* rigidbody) = 0;

    /// Unregister a render component (weak pointer)
    virtual void unregisterRigidbody(Rigidbody* rigidbody) = 0;
};

