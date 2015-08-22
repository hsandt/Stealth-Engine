//
// Created by L Nguyen Huu on 01/04/15 ap. J.-C..
// Copyright (c) 2015 L Nguyen Huu. All rights reserved.
//


#pragma once

#include "Controller.h"

class AIController : public Controller {
public:
    AIController();
    virtual ~AIController();

    AIController(const AIController &) = delete;
    AIController &operator=(const AIController &) & = delete;
    AIController(AIController &&) = default;
    AIController &operator=(AIController &&) & = default;

    virtual void setIntention() override;

private:

};


