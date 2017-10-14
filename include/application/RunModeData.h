//
// Created by L Nguyen Huu on 14/10/2017 ap. J.-C..
//

#pragma once

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
    RunModeData testWithRenderingModeData = {
            .inputActive = false,
            .renderingActive = true,
            .isTest = true,
            .duration = 0.
    };

public:
    const RunModeData* getPlayModeData() const
    {
        return &playModeData;
    }

    const RunModeData* getSimulationModeData() const
    {
        return &simulationModeData;
    }

    const RunModeData* getTestModeData() const
    {
        return &testModeData;
    }

    const RunModeData* getTestWithRenderingModeData() const
    {
        return &testWithRenderingModeData;
    }
};

extern RunModeDataSet g_RunModeDataSet;
