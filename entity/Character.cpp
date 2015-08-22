//
//  Character.cpp
//  Stealth
//
//  Created by L Nguyen Huu on 28/01/27 H.
//  Copyright (c) 27 Heisei L Nguyen Huu. All rights reserved.
//

#include "Character.h"

using namespace std;

Character::Character(std::string const &name, Point3d const &pos) : GameObject(name, pos)
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

void Character::render(SDL_Renderer *renderer) {
     //cout << "rendering at " << go -> GetPosition().x() << endl;
        //BOOST_LOG_TRIVIAL(warning) << "test";
    SDL_Rect r;
    //int w = 640, h = 480;

    r.w = 20;
    r.h = 20;
    r.x = getPosition().x();
    r.y = getPosition().y();

    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0, 0xff);
    SDL_RenderDrawRect(renderer, &r);
}
