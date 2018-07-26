//
// Created by acro_ on 2016/07/11.
//

#include <stdexcept>

#include "physics/Box2DPhysicsManager.h"

#include <Box2D/Box2D.h>

#include "application/GameApplication.h"
#include "component/Rigidbody.h"
#include "component/Transform.h"
#include "core/Logger.h"
#include "core/math/Vector2.h"
#include "world/Actor.h"

using namespace std;

Box2DPhysicsManager::Box2DPhysicsManager() {
	// Initialize the world with no gravity, since the PhysicsManager
	// is constructed immediately by the EngineCore and therefore we don't have
	// scene information yet, including gravity
	// TODO: delay world creation in init, or better, create a world for the current scene (except if you want to share the world)
	world = new b2World({0.f, 0.f});

    // TODO: move config in init and add setters to change them in the editor or even in runtime
    // REFACTOR/PRECISION: modify getFrameDuration to include the cast float32 with safety
    timeStep = (float32) EngineCore::requireInstance()->getFrameDuration();
	LOG("[PHYSICS MANAGER] Physics manager created");
}

Box2DPhysicsManager::~Box2DPhysicsManager() {
	LOG("[PHYSICS MANAGER] Destroying world...");
	delete world;

	LOG("[PHYSICS MANAGER] Physics manager destroyed");
}


Vector2 Box2DPhysicsManager::getGravity() const
{
    return world->GetGravity();
}


void Box2DPhysicsManager::setGravity(Vector2 gravity)
{
    world->SetGravity(gravity);
}

void Box2DPhysicsManager::destroyBody(b2Body* body)
{
    if (body == nullptr)
        throw std::invalid_argument("[PHYSICS MANAGER] Cannot destroy body: nullptr");

    world->DestroyBody(body);
}

b2Body* Box2DPhysicsManager::createBody(Actor* actor)
{
	if (actor == nullptr)
		throw invalid_argument("[PHYSICS MANAGER] Cannot create body on actor: nullptr");

	b2BodyDef bodyDef;
	Vector2 actorPosition = actor->transform->getPosition();
	bodyDef.position.Set(actorPosition.x(), actorPosition.y());

	b2Body* body = world->CreateBody(&bodyDef);
    return body;
}

b2Body *Box2DPhysicsManager::createDynamicBody(Actor *actor)
{
    if (actor == nullptr)
        throw invalid_argument("[PHYSICS MANAGER] Cannot create body on actor: nullptr");

    b2BodyDef bodyDef;
    Vector2 actorPosition = actor->transform->getPosition();
    bodyDef.position.Set(actorPosition.x(), actorPosition.y());
    bodyDef.type = b2_dynamicBody;
    b2Body* body = world->CreateBody(&bodyDef);
    return body;
}

void Box2DPhysicsManager::start()
{
    for (auto rigidbody : rigidbodies)
    {
        if (rigidbody)
            rigidbody->start();
    }
}

void Box2DPhysicsManager::update(float dt)
{
	world->Step(timeStep, velocityIterations, positionIterations);

    // update actor positions with new body positions
    for (auto rigidbody : rigidbodies)
    {
        if (rigidbody)
            rigidbody->update(dt);
    }
}

void Box2DPhysicsManager::registerRigidbody(Rigidbody* rigidbody)
{
    if (!rigidbody)
        throw invalid_argument("[PhysicsManager] Cannot register rigidbody: nullptr");

    rigidbodies.push_back(rigidbody);  // shared to weak pointer conversion
}

void Box2DPhysicsManager::unregisterRigidbody(Rigidbody* rigidbody)
{
    if (!rigidbody)
        throw invalid_argument("[PhysicsManager] Cannot unregister rigidbody: nullptr");

    auto it = find(rigidbodies.begin(), rigidbodies.end(), rigidbody);

    // REFACTOR: make a util function to remove element when present in container
    if (it != rigidbodies.end())
    {
        // here, components == *it
        rigidbodies.erase(it);
    }
    else
    {
        LOGERRF("[PhysicsManager] Rigidbody on %s not registered by PhysicsManager, could not unregister", rigidbody->getGameObject()->name.c_str());
    }
}
