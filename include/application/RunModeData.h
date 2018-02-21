//
// Created by L Nguyen Huu on 14/10/2017 ap. J.-C..
//

#pragma once

#include <stdexcept>

#include "RunMode.h"

struct RunModeData
{
    bool inputActive;
    bool renderingActive;
    bool isTest;
    double duration;
};

class RunModeDataSet
{
    RunModeData playModeData = {
            .inputActive = true,
            .renderingActive = true,
            .isTest = false,
            .duration = 0.
    };
    RunModeData simulationModeData = {
            .inputActive = false,
            .renderingActive = true,
            .isTest = false,
            .duration = 0.
    };
    RunModeData testModeData = {
            .inputActive = false,
            .renderingActive = false,
            .isTest = true,
            .duration = 0.
    };
    RunModeData testWithInputModeData = {
            .inputActive = true,
            .renderingActive = false,
            .isTest = true,
            .duration = 0.
    };
    RunModeData testWithRenderingModeData = {
            .inputActive = false,
            .renderingActive = true,
            .isTest = true,
            .duration = 0.
    };

private:
    RunModeDataSet () = default;

    inline static const RunModeDataSet& getInstance ()
    {
        static RunModeDataSet instance;
        return instance;
    }

public:
    inline const RunModeData& getPlayModeData() const
    {
        return playModeData;
    }

    inline const RunModeData& getSimulationModeData() const
    {
        return simulationModeData;
    }

    inline const RunModeData& getTestModeData() const
    {
        return testModeData;
    }

    inline const RunModeData& getTestWithInputModeData() const
    {
        return testWithInputModeData;
    }

    inline const RunModeData& getTestWithRenderingModeData() const
    {
        return testWithRenderingModeData;
    }

    static const RunModeData& getRunModeData(RunMode runMode)
    {
        switch (runMode)
        {
            case RunMode::Play:
                return getInstance().getPlayModeData();
            case RunMode::Simulation:
                return getInstance().getSimulationModeData();
            case RunMode::Test:
                return getInstance().getTestModeData();
            case RunMode::TestWithInput:
                return getInstance().getTestWithInputModeData();
            case RunMode::TestWithRendering:
                return getInstance().getTestWithRenderingModeData();
            default:
                throw std::invalid_argument("[RunModeData] Cannot getRunModeData for RunMode::None");
        }
    }
};
