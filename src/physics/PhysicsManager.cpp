//
// Created by acro_ on 2016/07/11.
//

#include <stdexcept>

#include <Box2D/Box2D.h>

#include "geometry/Vector2.h"

#include "physics/PhysicsManager.h"

using namespace std;

PhysicsManager::PhysicsManager() {
	// Initialize the world with no gravity, since the PhysicsManager
	// is constructed immediately by the EngineCore and therefore we don't have
	// scene information yet, including gravity
	world = new b2World({0.f, 0.f});

	LOG("[PHYSICS MANAGER] Physics manager created");
}

PhysicsManager::~PhysicsManager() {
	LOG("[PHYSICS MANAGER] Destroying world...");
	delete world;

	LOG("[PHYSICS MANAGER] Physics manager destroyed");
}

b2Body* PhysicsManager::createBody(Actor* actor)
{
	if (actor == nullptr)
		throw invalid_argument("[PHYSICS MANAGER] Cannot create body on actor: nullptr");

	b2BodyDef groundBodyDef;
	Vector2 actorPosition = actor->transform->position;
	groundBodyDef.position.Set(actorPosition.x(), actorPosition.y());

	b2Body* groundBody = world->CreateBody(&groundBodyDef);
	return groundBody;
}



