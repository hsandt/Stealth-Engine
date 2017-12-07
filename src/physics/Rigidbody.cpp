//
// Created by wing on 17/09/03.
//

// REFACTOR: maybe use a proxy class for Box2D physics, although we are sure to use this library only
#include <Box2D/Box2D.h>

#include "include/component/Transform.h"
#include "include/entity/Actor.h"
#include "include/core/EngineCore.h"
#include "include/physics/PhysicsManager.h"
#include "include/physics/Rigidbody.h"

Rigidbody::Rigidbody()
{

}

Rigidbody::~Rigidbody()
{
	// body is supposed to be destroyed in onRemovedFromGameObject,
	// just check if it was the case as a safety
	if (body)
		destroyBody();
}

void Rigidbody::onAddedToGameObject()
{
	ActorComponent::onAddedToGameObject();

	EngineCore::getPhysicsManager()->registerRigidbody(this);

    // TODO: allow dynamic parameter to set body type
    // OPTIMIZE: since it would be costly to recreate the body each time the type changes
    // (in the editor or before running the game), only start the World
    // simulation when the game starts
//	body = EngineCore::getPhysicsManager()->createBody(actor);
	body = EngineCore::getPhysicsManager()->createDynamicBody(actor);
}

void Rigidbody::onRemovedFromGameObject()
{
	ActorComponent::onRemovedFromGameObject();

	EngineCore::getPhysicsManager()->unregisterRigidbody(this);
}

void Rigidbody::destroyBody()
{
	PhysicsManager* physicsManager = EngineCore::getPhysicsManager();
	if (physicsManager)
	{
		physicsManager->destroyBody(body);
	}
	else
	{
		const string name = gameObject ? gameObject->name : "destroyed object";
		LOGERRF("Rigidbody::destroyBody (%s): PhysicsManager is already destroyed, check destruction order in EngineCore::~", name.c_str());
	}
}


void Rigidbody::addBoxShape(const Vector2& halfSize, const Vector2& offset, float angle, float density)
{
	b2PolygonShape groundBox;
	groundBox.SetAsBox(halfSize.x(), halfSize.y(), (b2Vec2) offset, angle);
	// TODO: add density parameter (0 is ok for static objects, but need 1 or so for dynamic)
	body->CreateFixture(&groundBox, density);  // support dynamic
    // if you also need friction
//    b2FixtureDef fixtureDef;
//    fixtureDef.shape = &dynamicBox;
//    fixtureDef.density = 1.0f;
//    fixtureDef.friction = 0.3f;
//    body->CreateFixture(&fixtureDef);
}

void Rigidbody::removeAllShapes()
{
	// GetFixtureList() returns the head of a chained list, not a container!
	// so we need either a while or a for; see b2Body.cpp for examples
	// https://stackoverflow.com/questions/23163728/box2d-cant-destroy-multiple-fixtures
	for (b2Fixture* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
	{
		body->DestroyFixture(fixture);
	}

	// Note that this requires a bit more computation than what b2World::DestroyBody does to destroy
	// all the fixtures, since DestroyFixture moves the list head pointer to the next fixture each time.
	// It also doesn't call SayGoodbye, but probably fine.

	// Below is the version copied from b2World::DestroyBody, but not usable due to private fields being used
	// Delete the attached fixtures. This destroys broad-phase proxies.
	/*
	b2Fixture* f = b->m_fixtureList;
	while (f)
	{
		b2Fixture* f0 = f;
		f = f->m_next;

		if (m_destructionListener)
		{
			m_destructionListener->SayGoodbye(f0);
		}

		f0->DestroyProxies(&m_contactManager.m_broadPhase);
		f0->Destroy(&m_blockAllocator);
		f0->~b2Fixture();
		m_blockAllocator.Free(f0, sizeof(b2Fixture));

		b->m_fixtureList = f;
		b->m_fixtureCount -= 1;
	}
	b->m_fixtureList = nullptr;
	b->m_fixtureCount = 0;
	*/
}

void Rigidbody::start()
{
    ActorComponent::start();

    // set initial position from game object
    // (for now, rely on onAddedToGameObject > createDynamicBody initial position to check if it works,
    // uncomment this later)
//    Vector2 actorPosition = actor->transform->position;
//    body->SetTransform((b2Vec2) actorPosition, body->GetAngle());
}

void Rigidbody::update(float dt)
{
	ActorComponent::update(dt);

    // set actor position to body's position (update must be called after physics step)
    actor->transform->setPosition(body->GetPosition());
}

void Rigidbody::setPosition(const Vector2 &position)
{
    body->SetTransform((b2Vec2) position, body->GetAngle());
}

void Rigidbody::setVelocity(const Vector2 & velocity)
{
	body->SetLinearVelocity((b2Vec2) velocity);
}

