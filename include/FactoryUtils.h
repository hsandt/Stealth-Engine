//
// Created by wing on 15/09/07.
//

#pragma once

#include <iostream>
#include <memory>
#include "Locator.h"
#include "Factory.h"
// Locator uses class forward declaration, safer to include
#include "GameApplication.h"

// REFACTOR: prefer direct access to Locator, or use namespace for better static method calls

template<class T>
std::shared_ptr<T> CreateGameObject() {
    Factory* factory = Locator::getFactory();
    // even if not used, RETURN game object! else UB
    return factory->CreateGameObject<T>();
}

template<class T>
std::shared_ptr<T> CreateComponent() {
	Factory* factory = Locator::getFactory();
    // even if not used, RETURN game object! else UB
    return factory->CreateComponent<T>();
}