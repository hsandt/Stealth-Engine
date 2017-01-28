//
// Created by wing on 17/01/14.
// Base class for all objects (GameObject, Components)
//

#pragma once

class Object {
public:
	int ID() const;

	// REFACTOR: set ID here?
	virtual void init() {}

protected:
	/// Object unique ID
//	const int id;  // cannot be constant if defined later
	int id = -1;

	// Let Factory set Object ID
//	friend class Factory;
	friend class GameObjectCreator;
	friend class ComponentCreator;
};

