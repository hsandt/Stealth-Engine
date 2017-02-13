//
//  ApplicationContainer.h
//  Stealth
//
//  Created by L Nguyen Huu on 04/02/27 H.
//  Copyright (c) 27 Heisei L Nguyen Huu. All rights reserved.
//

#pragma once

// Include GLEW. Always include it before gl.h and glfw.h, since it's a bit magic.
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#define APPTITLE "OpenGL Template Program"

class GameApplication;

class ApplicationContainer
{

public:

    ApplicationContainer();
    virtual ~ApplicationContainer();

    ApplicationContainer(const ApplicationContainer &) = delete;
    ApplicationContainer &operator=(const ApplicationContainer &) & = delete;
    ApplicationContainer(ApplicationContainer&&) = delete;
    ApplicationContainer &operator=(ApplicationContainer&&) & = delete;

    // Application state (just convenience instead of 0, 1, ...).
    enum RESULT
    {
        FAILURE = 0,
        SUCCESS = 1
    };

    // Initialize application, called by run(), don't call manually.
    int init(int width, int height);

    /// Run the game at given FPS
    void runGame(int fps);

private:

    // Destroy application, called by destructor, don't call manually.
    void destroy();
    
    // Called to process SDL event.
    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    
    // Called to render content into buffer.
    void Render();
    
    // Whether the application is in event loop.
    bool _running;
    GLFWwindow * window = nullptr;

    /// Contained game application
    GameApplication* game = nullptr;

};

void error_callback(int error, const char* description);
