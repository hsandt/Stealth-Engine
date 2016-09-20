//
// Created by wing on 15/09/06.
//

#include <memory>

#include "Scene.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "UnitTest++/UnitTest++.h"

using namespace std;

SUITE(GameObjectFactory) {
    class SceneFixture {
    public:
        shared_ptr<Scene> s = make_shared<Scene>();
        GameObjectFactory f;

//        void RegisterCurrent

    };

    TEST_FIXTURE(SceneFixture, CreateNewObject) {
        f.SetCurrentScene(s);
        auto go = f.Create<GameObject>();
        CHECK_EQUAL(0, go->ID());
        CHECK_EQUAL(0, s->getGameObjects().at(0)->ID());
    }
}

int main(int argc, char* argv[])
{
    return UnitTest::RunAllTests();
}