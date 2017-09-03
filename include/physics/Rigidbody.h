//
// Created by wing on 17/09/03.
//

#pragma once

#include <include/component/ActorComponent.h>
#include <include/geometry/Vector2.h>

class Rigidbody : public ActorComponent
{
private:
	class b2Body* body;

public:
	Rigidbody();
	virtual ~Rigidbody();

	Rigidbody(const Rigidbody &) = delete;
	Rigidbody & operator=(const Rigidbody &) = delete;

	void onAddedToGameObject() override;
	void onRemovedFromGameObject() override;

	/// Add a box shape to the rigidbody with width, height and optional offset and angle
	void addBoxShape(float width, float height, const Vector2 & offset = {0.f, 0.f}, float angle = 0.f);

	/// Remove all the shapes on this rigidbody (this will make it impossible to collide with)
	void removeAllShapes();
};


