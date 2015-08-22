//
//  ButtonState.h
//  Stealth
//
//  Created by L Nguyen Huu on 04/02/27 H.
//  Copyright (c) 27 Heisei L Nguyen Huu. All rights reserved.
//

#pragma once

enum class ButtonState
{
    PRESSED,
    DOWN,
    RELEASED,
    UP,
    PRESSED_RELEASED,  // press and release in 1 frame
    RELEASED_PRESSED   // release and press in 1 frame
};
