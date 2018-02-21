//
//  GLFWWindowManager.h
//  Stealth
//
//  Created by L Nguyen Huu on 04/02/27 H.
//  Copyright (c) 27 Heisei L Nguyen Huu. All rights reserved.
//

#pragma once

// On OSX, integrated graphics only support OpenGL up to 3.3 (this may cause incompatibility issues with the shader language)
#if __APPLE__
	#define OPEN_GL_VERSION_MAJOR 3
	#define OPEN_GL_VERSION_MINOR 3
#else
	#define OPEN_GL_VERSION_MAJOR 4
	#define OPEN_GL_VERSION_MINOR 5
#endif

// Include GLEW. Always include it before gl.h and glfw.h, since it's a bit magic.
#include <input/KeyStates.h>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "application/GameConfig.h"

#include "application/WindowManager.h"
#include "core/EngineCore.h"

class GameApplication;

class GLFWWindowManager : public WindowManager
{
private:
	GLFWwindow * window = nullptr;

	/* State vars */

	/// Last GLFW error that occured
	int glfwError = 0;

public:
    GLFWWindowManager();
    virtual ~GLFWWindowManager();

    GLFWWindowManager(const GLFWWindowManager &) = delete;
    GLFWWindowManager &operator=(const GLFWWindowManager &) & = delete;
//    GLFWWindowManager (GLFWWindowManager &&) = default;
//    GLFWWindowManager &operator=(GLFWWindowManager &&) & = default;

    /// Initialize window manager with game config
    void init(const GameConfig & gameConfig) override;

private:
    /// Callback on GLFW event
    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

public:
	/// Callback on GLFW error
	virtual void errorCallback(int error, const char* description) override;

	virtual void pollEvents() override;
	virtual int windowShouldClose() override;
	virtual void swapBuffers() override;
	virtual int getKey(int key) override;
	virtual KeyStaticState toKeyStaticState(int glfwCode) const override
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

	void getFramebufferSize(int* screenWidth, int* screenHeight) override;

};
