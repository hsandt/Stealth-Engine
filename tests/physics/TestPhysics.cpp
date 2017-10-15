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

using namespace std;

TEST_CASE("Physics: use rigidbody", "[physics]")
{
	// REFACTOR: see TestFactory, factorize boilerplate code
	SmokeTestRunner smokeTestRunner;
	smokeTestRunner.init();

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
                            CHECK(actor->transform->getPosition().y() < -4.9f);
                            CHECK(actor->transform->getPosition().y() > -5.1f);
                        }
                    }
                }
			}
		}
	}
}
