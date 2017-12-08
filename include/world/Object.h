//
// Created by wing on 17/01/14.
// Base class for all objects (GameObject, Components)
//

#pragma once

class Object {
	friend class GameObjectCreator;
	friend class ComponentCreator;

public:
	Object() {}
	virtual ~Object() {};  // we need to define some destructor even for abstract classes -> not really pure virtual

	/// Initialization method, called right after the construction by a creator
	virtual void init() {}

	int ID() const { return id; }

protected:
	/// Object unique ID (default value to detect invalid initialization)
	int id = -1;

};

