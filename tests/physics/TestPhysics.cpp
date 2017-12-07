//
// Created by wing on 17/09/03.
//

#include <tests/catch.hpp>
#include <include/test/SmokeTestRunner.h>

// REFACTOR: make a generic header that contains itself headers
// for the most common engine classes
#include "application/RunMode.h"
#include "entity/Actor.h"
#include "factory/Factory.h"
#include "physics/PhysicsManager.h"
#include "physics/Rigidbody.h"
#include "scene/Scene.h"
#include "scene/SceneManager.h"

using namespace std;

TEST_CASE("Physics: use rigidbody", "[physics]")
{
	// REFACTOR: see TestFactory, factorize boilerplate code
	SmokeTestRunner smokeTestRunner;
	smokeTestRunner.init();
//	smokeTestRunner.init(RunMode::TestWithRendering);  // useless, since we skip time
	// REFACTOR: allow TestWithRendering. Either use assert objects and let run without skip,
	// or replace make skip has the effect of "wait until... running the loop" to allow rendering

	GIVEN("an actor")
	{
		Actor* actor = EngineCore::getFactory()->CreateGameObject<Actor>();

		WHEN("we add a Rigidbody component to actor")
		{
			// optional since 0, 0 is the default value, but clearer to understand the test
			actor->transform->setPosition({0.f, 0.f});
			Rigidbody* rigidbody = actor->addComponent<Rigidbody>();
			THEN("the rigidbody should be attached to the actor")
			{
				REQUIRE(rigidbody != nullptr);
				REQUIRE(rigidbody->getGameObject() == actor);

				GIVEN("a gravity of 10 toward the bottom")
				{
					EngineCore::getPhysicsManager()->setGravity({0, -10});
					WHEN("we skip 1s")
					{
						smokeTestRunner.skip(1.0);
						THEN("the actor has moved")
						{
							// 1/2 * g * t^2 = 1/2 * g = 5
							// IMPROVE: create "almost" float comparison functions
							// We tolerate a small error of 0.1f since we run at 60 FPS
							CHECK(actor->transform->getPosition().x() == 0.f);
							CHECK(actor->transform->getPosition().y() > -5.1f);
							CHECK(actor->transform->getPosition().y() < -4.9f);
						}
					}
				}
			}
		}
	}

	EngineCore::getSceneManager()->getCurrentScene()->clear();

	GIVEN("2 actors with Rigidbodies close to each other [collider box half-size 5, distance 50]")
	{
		Actor* actor1 = EngineCore::getFactory()->CreateGameObject<Actor>();
		Actor* actor2 = EngineCore::getFactory()->CreateGameObject<Actor>();
		actor1->transform->setPosition({0.f, 0.f});
		actor2->transform->setPosition({50.f, 0.f});
		Rigidbody* rigidbody1 = actor1->addComponent<Rigidbody>();
		rigidbody1->addBoxShape({5.f, 5.f});
		// idea: try a very heavy actor1 to reduce pushing
//		rigidbody1->addBoxShape({5.f, 5.f}, {0.f, 0.f}, 0.f, 100.f);
		Rigidbody* rigidbody2 = actor2->addComponent<Rigidbody>();
		rigidbody2->addBoxShape({5.f, 5.f});

		WHEN("actor 2 moves toward actor 1 [speed 10, duration 4s]")
		{
			rigidbody2->setVelocity({-10.f, 0.f});
			smokeTestRunner.skip(4.0);

			// actually, inertia matters if actor1 is not forced to velocity 0 like PlayerDynamicMotor... be careful
			THEN("actor 2 is blocked by actor 1, and stops [center distance around 10]")
			{
				// with inertia, may push a little (you can also check actor1 position)
				CHECK(actor2->transform->getPosition().x() > 9.9f);
				CHECK(actor2->transform->getPosition().x() < 10.1f);
				CHECK(actor2->transform->getPosition().y() > -0.1f);
				CHECK(actor2->transform->getPosition().y() < 0.1f);
			}
		}
	}
}
