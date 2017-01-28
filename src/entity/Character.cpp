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
#include "SquareRenderComponent.h"
#include "geometry/Vec3.h"

using namespace std;

Character::Character(string const &name) :
        Actor(name)
{
	// ERROR: using shared pointer of object in creation! still locked
//	components.push_back(make_shared<SquareRenderComponent>(shared_from_this()));
//	components.push_back(make_shared<SquareRenderComponent>());
}

Character::~Character()
{
	delete controller;
}

void Character::init () {
	Actor::init();

	// add components here, not in constructor,
	// since component requires a ref to the shared_ptr of the actor
	// to use shared_from_this, and we need to finish the make_shared construction first
	addComponent<SquareRenderComponent>();
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

/*
void Character::render(Renderer *renderer) {
     //cout << "rendering at " << go -> GetPosition().x() << endl;
        //BOOST_LOG_TRIVIAL(warning) << "test";
	shared_ptr<RenderComponent> renderComponent = GetComponent<RenderComponent>();
	if (renderComponent != nullptr)
		render(renderer);
	else
		cout << "No render component on character " << name << endl;
}
*/