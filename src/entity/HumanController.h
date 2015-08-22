//
// Created by L Nguyen Huu on 02/03/15 ap. J.-C..
// Copyright (c) 2015 L Nguyen Huu. All rights reserved.
//


#pragma once

#include "Controller.h"

class HumanController : public Controller {
public:
    HumanController();
    virtual ~HumanController();

    HumanController(const HumanController &) = delete;
    HumanController &operator=(const HumanController &) & = delete;
    HumanController(HumanController &&) = default;
    HumanController &operator=(HumanController &&) & = default;

    virtual void setIntention() override;

private:

};


