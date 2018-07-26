//
// Created by wing on 17/09/03.
//

#pragma once

#include <string>

#include "component/ActorComponent.h"
#include "core/math/Vector2.h"

class Rigidbody : public ActorComponent
{
private:
	// TODO: extract interface and implement Box2DRigidbody so that all references to Box2D disappear from Rigidbody
	class b2Body* body;

public:
	Rigidbody();
	virtual ~Rigidbody();

	static std::string getStringID() { return "Rigidbody"; }
	std::string getClassStringID() const override { return getStringID(); }

	void onAddedToGameObject() override;
	void onRemovedFromGameObject() override;

    void start() override;
    void update(float dt) override;

private:
	void destroyBody();

public:
	/// Add a box shape to the rigidbody with half size and optional offset, angle and density
	void addBoxShape(const Vector2& halfSize, const Vector2 & offset = {0.f, 0.f}, float angle = 0.f, float density = 1.f);

	/// Remove all the shapes on this rigidbody (this will make it impossible to collide with)
	void removeAllShapes();

    /// Set the position of the rigidbody for the next physics update
    /// If the rigidbody is dynamic, velocity is preserved
    void setPosition(const Vector2 &position);

	/// Set the rigidbody speed for the next physics update.
    void setVelocity(const Vector2 & velocity);
};


