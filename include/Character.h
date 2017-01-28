//
//  Character.h
//  Stealth
//
//  Created by L Nguyen Huu on 28/01/27 H.
//  Copyright (c) 27 Heisei L Nguyen Huu. All rights reserved.
//

#pragma once

#include "GameObject.h"
#include "Actor.h"
#include "Controller.h"
#include "HumanController.h"

class Character : public Actor
{
public:
    Character(std::string const &name);
    virtual ~Character();
    Character(const Character &) = delete;
    Character &operator=(const Character &) & = delete;
    Character(Character&&) = delete;
    Character &operator=(Character&&) & = delete;

	virtual void init() override;

	virtual void update(double dt) override;

//    virtual void render(Renderer *renderer) override;

    /*
    Point3d getPosition() const {
        return position;
    }

    void setPosition(const Point3d &pos) {
        position = pos;
    }*/

protected:
    Controller* controller = nullptr;
    float speed = 5.0;
};

