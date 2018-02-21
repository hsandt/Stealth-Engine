//
// Created by acro_ on 2016/06/21.
//

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <algorithm>
#include <array>
#include <vector>

#include "Color.h"

class RenderComponent;
class GameObject;

class Renderer
{
public:
	Renderer();
	virtual ~Renderer();

	/// Initialize renderer:
	/// - load all shaders
	/// Call it after constructing the single instance
	void init();

	/// Clear screen buffer
	void clear() const;

	/// Render through all render components
	void render();

	/// Draw a square from corner (x, y) and size (w, h) toward bottom-right
	void drawSquare(float x, float y, float w, float h);

private:
	/// Array of shaders loaded
	std::array<GLuint, 16> shaderProgramIDs = {};

	/// Background color
	Color backgroundColor = {0, 0, 0.2, 1};  // dark blue

	// REFACTOR: move to future RenderManager
	/// All Render components in the current scene (weak pointers)
	std::vector<RenderComponent*> renderComponents;

public:
	/// Register a new render component (weak pointer)
	void registerRenderComponent(RenderComponent* renderComponent);

	/// Unregister a render component (weak pointer)
	void unregisterRenderComponent(RenderComponent* renderComponent);
};

