//
// Created by wing on 17/09/03.
//

#pragma once


#include <include/component/ActorComponent.h>

class Rigidbody : public ActorComponent
{
private:

public:
	Rigidbody();
	virtual ~Rigidbody();

	Rigidbody(const Rigidbody &) = delete;
	Rigidbody & operator=(const Rigidbody &) = delete;
};


