//
// Created by L Nguyen Huu on 02/03/15 ap. J.-C..
// Copyright (c) 2015 L Nguyen Huu. All rights reserved.
//


#pragma once
#include <iostream>
#include "Intention.h"

class Controller {
public:
    virtual ~Controller();

    Intention getIntention() const {return intention;}
    virtual void setIntention() = 0;
//    virtual void setIntention() {std::cout << "setIntention Controller" << std::endl;}
//    Controller();  // abstract class controller protected

protected:
    Controller();  // abstract class controller protected

    Controller(const Controller &) = delete;
    Controller &operator=(const Controller &) & = delete;
    Controller(Controller &&) = default;
    Controller &operator=(Controller &&) & = default;

    Intention intention = {};
};


