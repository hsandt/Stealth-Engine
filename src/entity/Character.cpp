//
//  Character.cpp
//  Stealth
//
//  Created by L Nguyen Huu on 28/01/27 H.
//  Copyright (c) 27 Heisei L Nguyen Huu. All rights reserved.
//

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Character.h"

#include "Renderer.h"
#include "RenderComponent.h"
#include "geometry/Vec3.h"

using namespace std;

Character::Character(const int id, string const &name) :
        Actor(id, name)
{
}

Character::~Character()
{
}

void Character::update(double dt) {
    // update physics
    // if controller, let controller set intention
    if (controller) {
        controller->setIntention();

        // move based on intention
        position += controller->getIntention().move * speed;
    }
    else {
        //cout << "No controller found on Character" << endl;
    }
}

void Character::render(Renderer *renderer) {
     //cout << "rendering at " << go -> GetPosition().x() << endl;
        //BOOST_LOG_TRIVIAL(warning) << "test";
    GetComponent<RenderComponent>()->render(renderer);
}
