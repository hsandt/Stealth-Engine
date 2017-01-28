//
// Created by wing on 15/10/12.
//

#pragma once

#include "GameObject.h"

/**  GameObject present in a scene.
 *
 */
class Actor : public GameObject {

public:
    Actor(const std::string &name);
    virtual ~Actor();
    Actor(const Actor &) = delete;
    Actor &operator=(const Actor &) & = delete;

    virtual void init() override {
        GameObject::init();
        // TODO: add transform component
    }

    // render
    virtual void render(Renderer* renderer) {}

protected:
    Vector3 position = {0, 0, 0};  // must initialize, else garbage

};
