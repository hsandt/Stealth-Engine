//
// Created by wing on 17/09/03.
//

#include <tests/catch.hpp>

// REFACTOR: make a generic header that contains itself headers
// for the most common engine classes
#include "entity/Actor.h"
#include "factory/Factory.h"
#include "physics/Rigidbody.h"
#include "scene/Scene.h"

using namespace std;

TEST_CASE("Physics", "[physics]")
{
	// REFACTOR: see TestFactory, factorize boilerplate code
	GameApplication gameApplication;
	gameApplication.init();

	// simulate the 1st frame since we don't call run
	EngineCore::getSceneManager()->loadNextScene();

	SECTION("create an actor")
	{
		auto* go = EngineCore::getFactory()->CreateGameObject<Actor>();

		SECTION("add a Rigidbody component to game object")
		{
			Rigidbody* rigidbody = go->addComponent<Rigidbody>();
			REQUIRE(rigidbody != nullptr);
			CHECK(rigidbody->getGameObject() == go);
			// TODO: more interesting test on physics properties, possibly collision detection
			// on one frame by teleporting objects (no need to run game loop)
			// TODO: integration test, this time running the game loop and checking dynamic collisions
		}
	}
}
