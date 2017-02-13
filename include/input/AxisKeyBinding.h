//
// Created by wing on 17/02/12.
//

#pragma once

#include "Key.h"

struct AxisKeyBinding {
	Key key;
	void (*callback)(float);

	AxisKeyBinding(Key key, void (*callback)(float)) :
		key(key), callback(callback) {}

};


