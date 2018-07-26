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

#define FALLBACK_WINDOW_WIDTH 1280
#define FALLBACK_WINDOW_HEIGHT 720

#include "interfaces/application/WindowManager.h"

#include "core/EngineCore.h"

enum class KeyStaticState;

struct GameConfig;
struct GLFWwindow;

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

    /// Initialize window manager with game config
    void init(const GameConfig & gameConfig) override;

private:
    /// Callback on GLFW event
    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

public:
	/// Callback on GLFW error
	void errorCallback(int error, const char* description);

	void pollEvents() override;
	int windowShouldClose() override;
	void swapBuffers() override;
	int getKey(int key) override;
	KeyStaticState toKeyStaticState(int glfwCode) const override;

	void getFramebufferSize(int* screenWidth, int* screenHeight) override;

};
