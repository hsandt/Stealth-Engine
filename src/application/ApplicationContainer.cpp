//
//  ApplicationContainer.cpp
//  Stealth
//
//  Created by L Nguyen Huu on 04/02/27 H.
//  Copyright (c) 27 Heisei L Nguyen Huu. All rights reserved.
//

#include <memory>
#include <iostream>
#include "application/GameApplication.h"

#include "application/ApplicationContainer.h"

using namespace std;

ApplicationContainer::ApplicationContainer() :
_running(false)
{
}

ApplicationContainer::~ApplicationContainer()
{
    destroy();
}

int ApplicationContainer::init(int width, int height)
{
    // Set callback for any GLFW error
    glfwSetErrorCallback(error_callback);

    // Initialise GLFW
    int initSuccess = glfwInit();
    if (!initSuccess)
    {
        cerr << "[GLFW] Could not initialize application." << endl;
        return FAILURE;
    }

    // Create window (OpenGL 4.0+, 4.5 not available yet, check your drivers)
//	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL

    window = glfwCreateWindow(width, height, APPTITLE, nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        cerr << "[GLFW] Could not create window." << endl;
        return FAILURE;
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
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

    // for now, pure OpenGL
//    glClearColor(0.0, 0.0, 0.0, 0.0);         // black background
//    glMatrixMode(GL_PROJECTION);              // setup viewing projection
//    glLoadIdentity();                           // start with identity matrix
//    glOrtho(0.0, 10.0, 0.0, 10.0, -1.0, 1.0);   // setup a 10x10x2 viewing world

    cout << glGetString(GL_VERSION) << endl;


    // VSync
    glfwSwapInterval(1);

    return SUCCESS;
}

void ApplicationContainer::destroy()
{
    if (game)
        delete game;

    if (window)
        glfwDestroyWindow(window);

    // Terminate application
    glfwTerminate();

}

void ApplicationContainer::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void ApplicationContainer::Render()
{

}

void ApplicationContainer::runGame(int fps) {
    _running = true;
    game = new GameApplication(window, 30);
    game->init();
    game->run();
}


void error_callback(int error, const char* description)
{
    cerr << "[GLFW] Error: " << description << endl;
}
