//
// Created by acro_ on 2016/06/24.
//

#include <map>

#include "catch.hpp"

#include "world/Scene.h"

#include "core/factory/GameObjectCreator.h"
#include "world/GameObject.h"

TEST_CASE("Scene", "[world]")
{
	Scene s;

	SECTION("getGameObjects should return a map of current game objects")
	{
	    CHECK(s.getGameObjects().size() == 0);
	}

	SECTION("addGameObject should add a game object, associating it to this scene")
	{
	    // Game objects are owned by the scene which destroys them on destruction,
        //  so we need to create them with new as in GameObjectCreator
        //  (we should factorize this part to avoid setting id manually and risking to forget and override same ID go)
        // Alternatively we may *move* an object under Scene ownership completely; but that would defeat
        //  the point of a potential future GO allocator
        GameObjectCreator goCreator;
	    GameObject* go = goCreator.Create<GameObject>(0);

	    s.addGameObject(go);

	    const map<int, GameObject*>& gameObjects = s.getGameObjects();
	    CHECK(gameObjects.size() == 1);
	    auto iter = gameObjects.find(go->ID());
	    REQUIRE(iter != gameObjects.end());
	    CHECK(iter->second == go);
		// implementation: go->onAddedToScene was called once with this scene

        SECTION("removeGameObject should remove a game object by pointer from this scene")
        {
            s.removeGameObject(go);
            CHECK(gameObjects.size() == 0);
        }

        WHEN("there are multiple game objects in the scene")
        {
            GameObject* go2 = goCreator.Create<GameObject>(1);
            s.addGameObject(go2);
            CHECK(gameObjects.size() == 2);

            SECTION("clear should remove all game objects from this scene")
            {
                s.clear();
                CHECK(gameObjects.size() == 0);
            }
        }
    }
}