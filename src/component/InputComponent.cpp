//
// Created by wing on 17/02/12.
//

#include "component/Component.h"
#include "service/Locator.h"
#include "service/InputManager.h"

#include "component/InputComponent.h"

using namespace std;

InputComponent::InputComponent() : Component()
{

}

InputComponent::~InputComponent() {

}


void InputComponent::init()
{
	inputManager = Locator::getInputManager();
}

void InputComponent::registerComponent()
{
	inputManager->registerInputComponent(this);
}

void InputComponent::unregisterComponent()
{
	inputManager->unregisterInputComponent(this);
}

//template<class UserClass>
//void InputComponent::bindKey(Key key, KeyEvent event, void (UserClass::*actionCallback)(void)) {
//	keyBindings.emplace_back(key, event, actionCallback);
//}

//template<class UserClass>
//void InputComponent::bindAxisKey(Key key, void (UserClass::*axisCallback)(float))
//{
//	axisKeyBindings.emplace_back(key, axisCallback);
//}

void InputComponent::applyKeyBindings() {
	for (const auto& keyBinding : keyBindings)
	{
		if (keyBinding.event == KeyEvent::PRESS && inputManager->isKeyPressed(keyBinding.key) ||
			keyBinding.event == KeyEvent::RELEASE && inputManager->isKeyReleased(keyBinding.key))
		{
			keyBinding.callback();
		}
	}
}

void InputComponent::applyAxisKeyBindings() {
	for (const auto& axisKeyBinding : axisKeyBindings)
	{
		// an axis key binding is applied each frame, and reset if the key is released
		axisKeyBinding.callback(inputManager->getAxisKeyValue(axisKeyBinding.key));
	}

}

