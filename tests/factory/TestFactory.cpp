//
// Created by wing on 15/09/06.
//

#include <tests/catch.hpp>

#include "component/Transform.h"
#include "entity/GameObject.h"
#include "factory/Factory.h"
#include "scene/Scene.h"
#include "application/RunMode.h"

using namespace std;

TEST_CASE("Factory", "[factory]")
{
	// EngineCore binds factory and scene, so we need to initialize it via GameApplication
	// OPTIMIZE: If it is too expensive for a unit test, we'll need to add partial
	// engine (per module) initialization API
	// In particular, this will open a window for an instant, which may be unwanted
    // Otherwise, we can make it a full integration test, but in this case, initialize a fake game
	// at the beginning of ALL integration tests and terminate it at the end to be more efficient.
	// We can also test each module by order of initialization (engine init test)
	// We can only put the GameApplication in a traditional Fixture reused to each integration test
	GameApplication gameApplication;
	gameApplication.init(RunMode::Test);

	// simulate the 1st frame since we don't call run
	EngineCore::getSceneManager()->loadNextScene();

    SECTION("create first game object")
    {
        auto* go = EngineCore::getFactory()->CreateGameObject<GameObject>();
        REQUIRE(go->ID() == 0);
	    REQUIRE(EngineCore::getSceneManager()->getCurrentScene()->getGameObjects().at(0)->ID() == 0);

	    SECTION("add input component to game object")
	    {
		    InputComponent* inputComponent = go->addComponent<InputComponent>();
			REQUIRE(inputComponent != nullptr);
		    CHECK(inputComponent->getGameObject() == go);
		    // fails for now, getComponent is not implemented
		    CHECK(go->getComponent<InputComponent>() == inputComponent);
	    }
    }
}
