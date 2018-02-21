//
//  WindowManager.h
//  Stealth
//
//  Created by L Nguyen Huu on 04/02/27 H.
//  Copyright (c) 27 Heisei L Nguyen Huu. All rights reserved.
//

#pragma once

// Include GLEW. Always include it before gl.h and glfw.h, since it's a bit magic.
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "application/ApplicationResult.h"
#include "application/GameClass.h"
#include "input/KeyStates.h"

#define FALLBACK_WINDOW_WIDTH 1280
#define FALLBACK_WINDOW_HEIGHT 720

class GameApplication;

class WindowManager
{
public:
    WindowManager();
    virtual ~WindowManager();

    WindowManager(const WindowManager &) = delete;
    WindowManager &operator=(const WindowManager &) & = delete;

    /// Initialize window manager with game config
    virtual void init(const GameConfig & gameConfig) = 0;

private:
    // Destroy application, called by destructor, don't call manually.
    void destroy();
    
    // Called to process SDL event.
    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    
    /// Contained game application
    GameApplication* game = nullptr;

public:
	virtual void errorCallback(int error, const char* description);

	/// Process all the pending events
	virtual void pollEvents() = 0;

	/// Should the window be closed? (when the close button has been clicked, etc.)
	virtual int windowShouldClose() = 0;

	/// Swap the front and back buffers
	virtual void swapBuffers() = 0;

	/// Return the state of the key for the given keycode
	virtual int getKey(int key) = 0;

	/// Return a key static state from a window-manager-specific key state code
	/// This function is not static so that it can be virtual, so at least it is made const
	virtual KeyStaticState toKeyStaticState(int keyStateCode) const = 0;

	/// Set screenWidth and screenHeight to the size of the frame buffer, in screen coordinates
	virtual void getFramebufferSize(int* screenWidth, int* screenHeight) = 0;

};
