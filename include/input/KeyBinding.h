//
// Created by wing on 17/02/12.
//

#pragma once

#include "Key.h"
#include "KeyEvent.h"

struct KeyBinding {
	Key key;
	KeyEvent event;
	void (*callback)(void);

	KeyBinding(Key key, KeyEvent event, void (*callback)(void)) :
		key(key), event(event), callback(callback) {}

};
