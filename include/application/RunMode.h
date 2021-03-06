//
// Created by L Nguyen Huu on 14/10/2017 ap. J.-C..
//

#pragma once

enum class RunMode
{
    None,
    Play,
    Simulation,
    Test,  // Smoke test
    TestWithInput,  // Smoke test with input only to debug InputManager (simulated input, etc.)
    TestWithRendering
};