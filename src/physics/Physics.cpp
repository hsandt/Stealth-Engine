//
// Created by acro_ on 2016/07/11.
//

#include "Box2D/Box2D.h"

#include "Physics.h"

Physics::Physics(b2Vec2 gravity) {
	world = new b2World(gravity);
}

Physics::~Physics() {

}



