//==============================================================================
// Button.h
// Copyright 27 Heisei L Nguyen Huu. All rights reserved.
//==============================================================================

#pragma once

#include <array>

enum class Button
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    QUIT,
    COUNTER  // only used to count values; must start at value 0
};

// weird, but works
constexpr std::array<Button, static_cast<int>(Button::COUNTER)> allButtons = {
    Button::UP,
    Button::DOWN,
    Button::LEFT,
    Button::RIGHT,
    Button::QUIT
};