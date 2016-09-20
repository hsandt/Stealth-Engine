//
// Created by wing on 15/09/07.
//

#pragma once

#include <iostream>
#include <memory>
#include "Locator.h"
#include "GameObjectFactory.h"
// Locator uses class forward declaration, safer to include
#include "GameApplication.h"

template<class T>
std::shared_ptr<T> CreateGameObject() {
    std::shared_ptr<GameObjectFactory> factory = Locator::getGameObjectFactory();
    // even if not used, RETURN game object! else UB
    return factory->Create<T>();
}