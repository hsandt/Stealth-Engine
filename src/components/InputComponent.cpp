//
// Created by wing on 17/02/12.
//

#include "include/world/Component.h"
#include "core/EngineCore.h"
#include "include/input/InputManager.h"

#include "component/InputComponent.h"

using namespace std;

InputComponent::InputComponent() : Component()
{

}

InputComponent::~InputComponent() {

}


void InputComponent::init()
{
	inputManager = EngineCore::getInputManager();
}

void InputComponent::onAddedToGameObject()
{
	if (!inputManager)
		throw runtime_error("[InputComponent] InputManager is nullptr");

	inputManager->registerInputComponent(this);
}

void InputComponent::onRemovedFromGameObject()
{
	if (!inputManager)
		throw runtime_error("[InputComponent] InputManager is nullptr");

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

