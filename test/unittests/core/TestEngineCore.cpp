//
// Created by wing on 15/09/06.
//

#include "catch.hpp"

#include "core/EngineCore.h"

#include "application/RunMode.h"
#include "application/RunModeData.h"
#include "core/factory/GameManagerFactory.h"

#include "core/Logger.h"

using namespace std;

TEST_CASE("EngineCore", "[core]")
{
    EngineCore& engineCore = *EngineCore::getNewInstance();

    WHEN("init")
    {
        const RunModeData& playModeData = RunModeDataSet::getRunModeData(RunMode::Play);
        engineCore.init(&playModeData, GameConfig(), GameManagerFactory());

        THEN("logger is created")
        {
            CHECK(engineCore.getLogger() != nullptr);
        }

        THEN("physics manager is created")
        {
            CHECK(engineCore.getPhysicsManager() != nullptr);
        }

        THEN("script manager is created")
        {
            CHECK(engineCore.getScriptManager() != nullptr);
        }

        THEN("factory is created")
        {
            CHECK(engineCore.getFactory() != nullptr);
        }

        THEN("scene manager is created")
        {
            CHECK(engineCore.getSceneManager() != nullptr);
        }
    }

    GIVEN("game config with fps=30")
    {
        const RunModeData& playModeData = RunModeDataSet::getRunModeData(RunMode::Play);
        GameConfig gameConfig;
        gameConfig.fps = 30;

        WHEN("init with game config")
        {
            engineCore.init(&playModeData, gameConfig, GameManagerFactory());

            THEN("frame duration is 1/30")
            {
                CHECK(engineCore.getFrameDuration() == 1./30.);
            }
        }
    }

    GIVEN("run mode data with rendering active")
    {
        RunModeData runModeData{};
        runModeData.renderingActive = true;

        WHEN("init with run mode data")
        {
            engineCore.init(&runModeData, GameConfig(), GameManagerFactory());

            THEN("window manager is created")
            {
                CHECK(engineCore.getWindowManager() != nullptr);
            }

            THEN("renderer is created")
            {
                CHECK(engineCore.getWindowManager() != nullptr);
            }
        }
    }

    GIVEN("run mode data with rendering inactive")
    {
        RunModeData runModeData{};
        runModeData.renderingActive = false;

        WHEN("init with run mode data")
        {
            engineCore.init(&runModeData, GameConfig(), GameManagerFactory());

            THEN("window manager is not created")
            {
                CHECK(engineCore.getWindowManager() == nullptr);
            }

            THEN("renderer is not created")
            {
                CHECK(engineCore.getWindowManager() == nullptr);
            }
        }
    }

    GIVEN("run mode data with input active")
    {
        RunModeData runModeData{};
        runModeData.inputActive = true;

        WHEN("init with run mode data")
        {
            engineCore.init(&runModeData, GameConfig(), GameManagerFactory());

            THEN("input manager is created")
            {
                CHECK(engineCore.getInputManager() != nullptr);
            }
        }
    }

    GIVEN("run mode data with input inactive")
    {
        RunModeData runModeData{};
        runModeData.inputActive = false;

        WHEN("init with run mode data")
        {
            engineCore.init(&runModeData, GameConfig(), GameManagerFactory());

            THEN("input manager is not created")
            {
                CHECK(engineCore.getInputManager() == nullptr);
            }
        }
    }
}
