//
// Created by L Nguyen Huu on 06/03/15 ap. J.-C..
// Copyright (c) 2015 L Nguyen Huu. All rights reserved.
//


#pragma once

#include "geometry/Vec3.h"

struct Intention {
    // move intention, 2D vector with magnitude between 0 and 1
    Vector3 move;
    Intention() : move({0, 0, 0}) {}  // required if no explicit member initialization
};


