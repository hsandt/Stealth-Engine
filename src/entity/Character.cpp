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

using namespace std;

Character::Character(const int id, std::string const &name) :
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

    float w = 20, h = 20;

    float x = getPosition().x();
    float y = getPosition().y();
    renderer->drawSquare(x - w / 2, y - h / 2, w, h);

}
