//
// Created by acro_ on 2016/06/21.
//

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <algorithm>
#include <memory>

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
	GLFWwindow *window = nullptr;
	Color backgroundColor = {0, 0, 0.2, 1};  // dark blue

	// REFACTOR: move references to another class if better modularization
	/// All Render components in the current scene
//	std::vector<RenderComponent*> renderComponents;
	std::vector<std::weak_ptr<RenderComponent>> renderComponents;
//	std::vector<std::shared_ptr<RenderComponent>> renderComponents;

//	void registerRenderComponent(RenderComponent* renderComponent);
	void registerRenderComponent(std::shared_ptr<RenderComponent> renderComponent);

	// incomplete class does not support this
//	friend void RenderComponent::onAddedToGameObject(std::shared_ptr<GameObject> gameObject);
	friend class RenderComponent;
};

