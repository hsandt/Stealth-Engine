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

Character::Character(std::string const &name, Point3f const &pos) : GameObject(name, pos)
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

//    glClear( GL_COLOR_BUFFER_BIT);
//    glColor3f(0.0, 1.0, 0.0);
//    glBegin(GL_POLYGON);
//    glVertex3f(2.0, 4.0, 0.0);
//    glVertex3f(8.0, 4.0, 0.0);
//    glVertex3f(8.0, 6.0, 0.0);
//    glVertex3f(2.0, 6.0, 0.0);
//    glEnd();
//    glFlush();

	float w = 20, h = 20;

	float x = getPosition().x();
	float y = getPosition().y();
	renderer->drawSquare(x - w / 2, y - h / 2, w, h);

}
