//
// Created by wing on 15/09/07.
//

#pragma once

#include <iostream>
#include "core/EngineCore.h"
#include "Factory.h"
// Locator uses class forward declaration, safer to include
#include "application/GameApplication.h"

// REFACTOR: prefer direct access to Locator, or use namespace for better static method calls

template<class T>
T* CreateGameObject() {
    Factory* factory = EngineCore::getFactory();
    return factory->CreateGameObject<T>();
}

template<class T>
T* CreateComponent() {
	Factory* factory = EngineCore::getFactory();
    return factory->CreateComponent<T>();
}