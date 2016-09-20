//
// Created by wing on 15/10/13.
//

#pragma once

#include <memory>

class GameObject;

class Component {
public:
    Component(std::shared_ptr<GameObject> gameObject);
    virtual ~Component() = 0;
    Component(Component const &) = delete;
    Component &operator=(Component const &) = delete;

protected:
    std::weak_ptr<GameObject> gameObject;
};
