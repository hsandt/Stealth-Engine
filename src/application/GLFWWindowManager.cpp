//
//  GLFWWindowManager.cpp
//  Stealth
//
//  Created by L Nguyen Huu on 04/02/27 H.
//  Copyright (c) 27 Heisei L Nguyen Huu. All rights reserved.
//

#include <iostream>
#include <memory>
#include <stdexcept>

// Include GLEW. Always include it before gl.h and glfw.h, since it's a bit magic.
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "application/GLFWWindowManager.h"

#include "application/GameConfig.h"
#include "core/Logger.h"
#include "input/KeyStates.h"

using namespace std;

GLFWWindowManager::GLFWWindowManager() : WindowManager()
{
}

GLFWWindowManager::~GLFWWindowManager()
{
	// Destroy existing window
	if (window)
		glfwDestroyWindow(window);

	// Terminate application
	glfwTerminate();
}

void GLFWWindowManager::init(const GameConfig & gameConfig)
{
    // Set callback for any GLFW error, using the singleton (context-less, global access) + lambda technique
	glfwSetErrorCallback([](int error, const char* description){EngineCore::getWindowManager()->errorCallback(error, description);});

	// Initialise GLFW
    int initSuccess = glfwInit();
    if (!initSuccess)
    {
        throw runtime_error("[GLFW] Could not initialize application.");
    }

    // Create window (OpenGL 4.5+ now supported by Nvidia drivers for Ubuntu, but OSX integrated graphics support 3.3 only;
	// may cause issues with shader language)

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPEN_GL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPEN_GL_VERSION_MINOR);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL, but this can cause some issues
//	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing

	// On OSX, we may need to set the Stencil bits if issues arise. For now, using OpenGL 3.3 works, even with integrated graphics.
	// Discrete graphics may work with 4.5 too.
	// https://stackoverflow.com/questions/27365099/nsgl-failed-to-create-opengl-pixel-format
//	glfwWindowHint(GLFW_STENCIL_BITS, 8);

	int width, height;
    if (gameConfig.initialWindowWidth > 0 && gameConfig.initialWindowHeight > 0)
    {
		width = gameConfig.initialWindowWidth;
		height = gameConfig.initialWindowHeight;
    }
	else
    {
        // use half full screen resolution
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	    if (mode != nullptr)
	    {
		    width = mode->width / 2;
		    height = mode->height / 2;
	    }
	    else
	    {
		    if (glfwError == GLFW_PLATFORM_ERROR)
		    {
				LOGERR("[GLFW] Platform-specific error");
		    }
		    LOGERR( "[GLFW] Could not find monitor size, using " STR(FALLBACK_WINDOW_WIDTH) "x" STR(FALLBACK_WINDOW_HEIGHT));
		    width = FALLBACK_WINDOW_WIDTH;
		    height = FALLBACK_WINDOW_HEIGHT;
	    }
    }

    window = glfwCreateWindow(width, height, gameConfig.title.c_str(), nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        throw runtime_error("[GLFW] Could not create window.");
    }

    // may be useful for critical key events
    glfwSetKeyCallback(window, keyCallback);

    // in case player quickly presses and releases key between 2 frames, set to sticky mode not to miss that quick press
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

    // Use this window as OpenGL context
    glfwMakeContextCurrent(window);

    // GLEW loader here
	glewExperimental=true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		throw runtime_error("Failed to initialize GLEW");
	}

    // for now, pure OpenGL
//    glClearColor(0.0, 0.0, 0.0, 0.0);         // black background
//    glMatrixMode(GL_PROJECTION);              // setup viewing projection
//    glLoadIdentity();                           // start with identity matrix
//    glOrtho(0.0, 10.0, 0.0, 10.0, -1.0, 1.0);   // setup a 10x10x2 viewing world

    cout << glGetString(GL_VERSION) << endl;

    // VSync
    glfwSwapInterval(1);
}

void GLFWWindowManager::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void GLFWWindowManager::errorCallback(int error, const char* description)
{
	// store error number and log error immediately
    LOGERR("[GLFWWindowManager] Error: ", description);
	glfwError = error;
}

void GLFWWindowManager::pollEvents()
{
	glfwPollEvents();
}

int GLFWWindowManager::windowShouldClose()
{
	return glfwWindowShouldClose(window);
}

void GLFWWindowManager::swapBuffers()
{
	return glfwSwapBuffers(window);
}

int GLFWWindowManager::getKey(int key)
{
	return glfwGetKey(window, key);
}

KeyStaticState GLFWWindowManager::toKeyStaticState(int glfwCode) const
{
	switch (glfwCode)
	{
		case GLFW_RELEASE:
			return KeyStaticState::UP;
		case GLFW_PRESS:
			return KeyStaticState::DOWN;
		default:
			return KeyStaticState::NONE;
	}
}

void GLFWWindowManager::getFramebufferSize(int* screenWidth, int* screenHeight)
{
	glfwGetFramebufferSize(window, screenWidth, screenHeight);
}
