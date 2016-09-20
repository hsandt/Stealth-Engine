//
//  GameApplication.h
//  Stealth
//
//  Created by L Nguyen Huu on 04/02/27 H.
//  Copyright (c) 27 Heisei L Nguyen Huu. All rights reserved.
//

#pragma once

#include <memory>

// SDL
#include <SDL2/SDL.h>

#include "Scene.h"
#include "InputManager.h"
#include "GameObjectFactory.h"

class GameApplication : public std::enable_shared_from_this<GameApplication>
{

public:
    GameApplication(SDL_Window *win, SDL_Renderer *renderer, int fps = 30);
    GameApplication() = default;
    virtual ~GameApplication();

    GameApplication(const GameApplication &) = default;
    GameApplication &operator=(const GameApplication &) & = default;
    GameApplication(GameApplication&&) = default;
    GameApplication &operator=(GameApplication&&) & = default;

    // Run application
    void run();
    // Exit application
    void stop();

private:
    // Initialize game, called by run()
    void init();
    // Destroy application, called by destructor
    void destroy();
    // Called to process user input
    void processInput();
    // Called to update AI and physics
    void update(double dt);
    // Called to render the game view
    void render();

    // Pointers passed by the SDL application
    SDL_Window *win;
    SDL_Renderer *renderer;

    // Shared pointers to managers
    std::shared_ptr<InputManager> inputManager;
    std::shared_ptr<GameObjectFactory> gameObjectFactory;

    // Is the game running
    bool isRunning;
    
    // FPS and timer per update (ms)
    int fps;
    int msecPerUpdate;
    double secPerUpdate;  // avoids converting to sec every time

    // active scene (make it a unique_ptr if you are sure no one else uses it)
    std::shared_ptr<Scene> currentScene;

public:
    // debug
    std::shared_ptr<Scene> getCurrentScene() {
        return currentScene;
    }
};

