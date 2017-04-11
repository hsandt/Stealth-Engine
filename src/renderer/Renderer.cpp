//
// Created by acro_ on 2016/06/21.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <iostream>
#include <renderer/ShaderUtils.h>

#include "debug/Logger.h"
#include "renderer/Renderer.h"
#include "service/Locator.h"
#include "component/RenderComponent.h"

using namespace std;

// REFACTOR: split in 2 classes: Renderer for the Rendering layer above OpenGL and RenderManager to register
// Render component and iterate on them

/* future RenderManager */

Renderer::Renderer(GLFWwindow *window) : window(window)
{
}

Renderer::~Renderer()
{
	LOG("[RENDERER] Renderer destroyed");
}

void Renderer::init()
{
	// Create and compile our GLSL program from the shaders

	// Shader Program 0: Simple Vertex / Simple Fragment
	shaderProgramIDs[0] = loadShaders( "resources/shaders/SimpleVertexShader.glsl", "resources/shaders/SimpleFragmentShader.glsl" );
}

void Renderer::registerRenderComponent(RenderComponent* renderComponent) {
	renderComponents.push_back(renderComponent);  // shared to weak pointer conversion
}

void Renderer::unregisterRenderComponent(RenderComponent* renderComponent) {
	auto it = find(renderComponents.begin(), renderComponents.end(), renderComponent);

	// REFACTOR: make a util function to remove element when present in container
	if (it != renderComponents.end())
	{
		// here, component == *it
		renderComponents.erase(it);
	}
	else
	{
		cout << "renderComponent not found in Renderer renderComponents" << endl;
	}
}

/* future Renderer */

void Renderer::clear() const {
	glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render() {
	for (auto renderComponent : renderComponents) {
		renderComponent->render(this);
	}
}

void Renderer::drawSquare(float x, float y, float w, float h) {

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);  // use framebuffer size for pixel size (2x if high-dpi)

	float normalizedX1 = x / screenWidth * 2 - 1;
	float normalizedY1 = y / screenHeight * 2 - 1;
	float normalizedX2 = (x + w) / screenWidth * 2 - 1;
	float normalizedY2 = (y + h) / screenHeight * 2 - 1;

	// An array of 6 vectors which represents 6 vertices
	GLfloat g_vertex_buffer_data[] = {
			normalizedX1, normalizedY1, 0.0f,
			normalizedX2, normalizedY1, 0.0f,
			normalizedX1, normalizedY2, 0.0f,
			normalizedX2, normalizedY2, 0.0f,
			normalizedX1, normalizedY2, 0.0f,
			normalizedX2, normalizedY1, 0.0f
	};

	// This will identify our vertex buffer
	GLuint vertexbuffer;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	// REFACTOR: the part above should be done ONCE for static sprites/meshes
	// use the same technique as Minecraft chunks to efficiently redraw sprite later (even multiple times if fixed positions)

	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(0);
//	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
	);

	// Use our shader (simple)
	// TODO: use material shader
	glUseProgram(shaderProgramIDs[0]);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 6); // Starting from vertex 0; 6 vertices total -> 2 triangle
	glDisableVertexAttribArray(0);
}
