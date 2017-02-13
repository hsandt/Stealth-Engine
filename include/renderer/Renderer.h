//
// Created by acro_ on 2016/06/21.
//

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <algorithm>

#include "utils/Color.h"

class RenderComponent;
class GameObject;

class Renderer
{
public:
	Renderer(GLFWwindow *window) : window(window) { }

	/// Clear screen buffer
	void clear () const;

	/// Render through all render components
	void render();

	void drawSquare(float x, float y, float w, float h);

private:
	/// Window used to render
	GLFWwindow *window = nullptr;

	/// Background color
	Color backgroundColor = {0, 0, 0.2, 1};  // dark blue

	// REFACTOR: move to future RenderManager
	/// All Render components in the current scene (weak pointers)
	std::vector<RenderComponent*> renderComponents;

	/// Register a new render component (weak pointer)
	void registerRenderComponent(RenderComponent* renderComponent);

	/// Unregister a render component (weak pointer)
	void unregisterRenderComponent(RenderComponent* renderComponent);

	// incomplete class does not support making a single method friend
//	friend void RenderComponent::onAddedToGameObject(std::shared_ptr<GameObject> gameObject);
	friend class RenderComponent;
};

