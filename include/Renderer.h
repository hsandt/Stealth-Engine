//
// Created by acro_ on 2016/06/21.
//

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <utils/Color.h>

class Renderer
{
public:
	Renderer(GLFWwindow *window) : window(window) { }

	/// Clear screen buffer
	void clear () const;

	void render();

	void drawSquare(float x, float y, float w, float h);

private:
	GLFWwindow *window = nullptr;
	Color backgroundColor = {0, 0, 0.2, 1};  // dark blue
};

