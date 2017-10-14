//
// Created by wing on 17/09/03.
//

#include <tests/catch.hpp>

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
	GameApplication gameApplication;
	gameApplication.init(RunMode::Test);

	// simulate the 1st frame since we don't call run
	EngineCore::getSceneManager()->loadNextScene();

	GIVEN("an actor")
	{
		Actor* actor = EngineCore::getFactory()->CreateGameObject<Actor>();

		WHEN("we add a Rigidbody component to actor")
		{
			Rigidbody* rigidbody = actor->addComponent<Rigidbody>();
			actor->addComponent<Rigidbody>();
			THEN("the rigidbody should be attached to the actor")
            {
                REQUIRE(rigidbody != nullptr);
                CHECK(rigidbody->getGameObject() == actor);
				// TODO: more interesting test on physics properties, possibly collision detection
				// on one frame by teleporting objects (no need to run game loop)
				// TODO: integration test, this time running the game loop for some time
                // and checking dynamic collisions

                GIVEN("a gravity of 10 toward the bottom")
                {
                    EngineCore::getPhysicsManager()->setGravity({0, -10});
				    WHEN("we skip 1s")
                    {
                        // private
//                        gameApplication.update(1.f);
                        THEN("the actor has moved")
                        {
                            // TODO
                        }
                    }
                }
			}
		}
	}
}
