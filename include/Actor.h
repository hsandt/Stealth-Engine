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
    Actor(const int id, const std::string &name);
    virtual ~Actor();
    Actor(const Actor &) = delete;
    Actor &operator=(const Actor &) & = delete;

    // render
    virtual void render(SDL_Renderer* renderer) {}

protected:
    Point3d position = {0, 0, 0};  // must initialize, else garbage

};
