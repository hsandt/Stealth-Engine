//
// Created by wing on 17/02/12.
//

#pragma once

#include <vector>

#include "component/Component.h"
#include "input/AxisKeyBinding.h"
#include "input/Key.h"
#include "input/KeyEvent.h"
#include "input/KeyBinding.h"

class InputManager;

class InputComponent : public Component {
public:
	InputComponent();
	virtual ~InputComponent();

	void init() override;

	void registerComponent() override;

	void unregisterComponent() override;

	// REFACTOR: pass "this" UserClass instance and use delegates (void* + cast, etc.) to be able
	// to store any method of any object for later

	/// Bind a callback function to a key event
//	template<class UserClass>
//	void bindKey(Key key, KeyEvent event, void (UserClass::*actionCallback)(void));

	/// Bind a callback function to a key axis value (0.0 or 1.0) to call each frame
//	template<class UserClass>
//	void bindAxisKey(Key key, void (UserClass::*axisCallback)(float));

//	template<class UserClass>
//	void bindAxisKey(Key key, void (UserClass::*axisCallback)(float))
//	{
//		axisKeyBindings.emplace_back(key, axisCallback);
//	}

	// REFACTOR: friend method/class from GameApplication
	/// Check all key events bound to a callback and call it if applicable
	void applyKeyBindings();

	/// Check all key events bound to a callback and call it if applicable
	void applyAxisKeyBindings();

private:
	InputManager* inputManager;

	std::vector<KeyBinding> keyBindings;
	std::vector<AxisKeyBinding> axisKeyBindings;

};
