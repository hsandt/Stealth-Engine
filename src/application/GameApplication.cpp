//
//  GameApplication.cpp
//  Stealth
//
//  Created by L Nguyen Huu on 04/02/27 H.
//  Copyright (c) 27 Heisei L Nguyen Huu. All rights reserved.
//

#include <iostream>
#include <memory>
#include <vector>
#include <boost/log/trivial.hpp>

// SDL
#include <SDL2/SDL.h>
#include <GameObjectFactory.h>
#include <FactoryUtils.h>

// Engine
#include "Locator.h"
#include "Scene.h"

// Game  // move to game!
#include "Guard.h"
#include "Spy.h"
#include "engine/include/GameObject.h"

#include "GameApplication.h"

using namespace std;

GameApplication::GameApplication(SDL_Window *win, SDL_Renderer *renderer, int fps) :
        win(win), renderer(renderer), isRunning(false), fps(fps)
{
    msecPerUpdate = (Uint32) floor(1000. / fps);
    secPerUpdate = 1. / fps;  // fixed deltaTime
}

GameApplication::~GameApplication()
{
    destroy();
}

void GameApplication::run() {
    
    init();
    
    Uint32 currentTime;
//    Uint32 elapsed;
    Uint32 endTime = SDL_GetTicks();
    int lag = 0;
    int sleep;
    
    isRunning = true;

    // update loop
    while (isRunning) {
        // SDL GetTicks() returns real time; need application
        // time to debug without adding delay!
        currentTime = SDL_GetTicks();
        lag += currentTime - endTime;

        processInput();

        while (lag >= msecPerUpdate) {
            // TODO: add limit for number of iterations to catch back
            update(secPerUpdate);
            // TODO: compute complete lag decrease at once, after the loop
            lag -= msecPerUpdate;
        }
        
        render();

        endTime = SDL_GetTicks();
        lag += endTime - currentTime;
        
        sleep = msecPerUpdate - lag;
        if (sleep > 0) {
            // we are in advance, wait
            SDL_Delay(sleep);
        } else {
            // rendering required more than the end of the frame, not time to sleep!
            cout << "No time to sleep!" << endl;
        }

    }

}

void GameApplication::stop() {
    isRunning = false;
}

void GameApplication::init() {
    // register Service Providers to Service Locators
    Locator::gameApplication = weak_ptr<GameApplication>(shared_from_this());
    inputManager = make_shared<InputManager>();
    Locator::inputManager = inputManager;
    gameObjectFactory = make_shared<GameObjectFactory>();
    Locator::gameObjectFactory = gameObjectFactory;

    currentScene = make_shared<Scene>();
    // set as current scene for game object factory
    gameObjectFactory->SetCurrentScene(currentScene);

    // T* &&arg did not work well, so to ensure I don't keep a ref of the GO I use only unique_ptr
//    currentScene->addGameObject(unique_ptr<GameObject> {new Guard(0, "Guard", {0, 20, 0})});  // use rhs or move only
//    currentScene->addGameObject(unique_ptr<GameObject> {new Spy(0, "Spy", {50., 50., 0.})});

    CreateGameObject<Guard>();
    cout << "currentScene count: " << currentScene.use_count() << endl;
    cout << "init end" << endl;
};

void GameApplication::destroy() {
    // nothing for now
    std::cout << "[GAME APPLICATION] GameApplication destroyed" << std::endl;
}

void GameApplication::processInput() {
    inputManager->processInputs();
    if (inputManager->getButtonState(Button::QUIT) == ButtonState::PRESSED ||
            inputManager->getButtonState(Button::QUIT) == ButtonState::RELEASED_PRESSED) {
        stop();
    }
    //SDL_Event event;
    //while (SDL_PollEvent(&event)) {
    //    switch (event.type)
    //    {
    //        case SDL_QUIT:
    //            isRunning = false;
    //            break;
    //
    //        case SDL_KEYDOWN:
    //        {
    //            if (event.key.keysym.sym == SDLK_ESCAPE)
    //            {
    //                isRunning = false;
    //            }
    //        }
    //    }
    //}
}

void GameApplication::update(double dt) {
    map<int, std::shared_ptr<GameObject>> gameObjects {currentScene->getGameObjects()};
    for (auto goIt (gameObjects.begin()); goIt != gameObjects.end(); ++goIt)
    {
        shared_ptr<GameObject> go {goIt->second};
        go -> update(dt);
        // go -> SetPosition(go -> GetPosition() + Point3d {23, 2, 0});
    }
    // DEBUG
    
}

void GameApplication::render() {
    
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0, 0xff);
    SDL_RenderClear(renderer);

    std::map<int, std::shared_ptr<GameObject>> gameObjects {currentScene->getGameObjects()};
    // add check that scene exists for debug?
    for (auto goIt (gameObjects.begin()); goIt != gameObjects.end(); ++goIt)
    {
        // do not use GameObject& which would be invalid if all shared_ptr
        // to the game object disappeared in the meanwhile (~raw pointer issue)
        shared_ptr<GameObject> go {goIt->second};
        go->render(renderer);
    }
    SDL_RenderPresent(renderer);
}


