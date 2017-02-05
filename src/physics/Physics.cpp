//
// Created by acro_ on 2016/07/11.
//

#include <memory>
#include "Box2D/Box2D.h"

#include "geometry/Vec2.h"

#include "Physics.h"

using namespace std;

Physics::Physics(Vec2f gravity) {
	world = make_unique<b2World>(gravity);
}

Physics::~Physics() {

}



