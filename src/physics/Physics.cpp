//
// Created by acro_ on 2016/07/11.
//

#include "Box2D/Box2D.h"

#include "geometry/Vector2.h"

#include "physics/Physics.h"

using namespace std;

Physics::Physics(Vector2 gravity) {
	world = new b2World(gravity);
}

Physics::~Physics() {
	delete world;
}



