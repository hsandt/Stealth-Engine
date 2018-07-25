//
// Created by acro_ on 2016/06/24.
//

#include "catch.hpp"

#include "world/SceneManager.h"
#include "world/Scene.h"

TEST_CASE("SceneManager", "[world]")
{
	SceneManager sm;

	SECTION("init should always add 'main' scene to scenes list")
	{
		sm.init();
		// implementation: private sm.sceneNames should contain "main"

		SECTION("queryLoadScene with a valid scene should set next scene to load")
		{
			sm.queryLoadScene("main");
			REQUIRE(sm.shouldLoadScene());
			// implementation: sm.nextSceneName should be "main"

			SECTION("loadNextScene should load the valid next scene")
			{
				sm.loadNextScene();
				REQUIRE(sm.getCurrentScene() != nullptr);
				CHECK(sm.getCurrentScene()->getName() == "main");
				// implementation: sm.loadScene should be called exactly once with "main"
			}
		}
	}
}