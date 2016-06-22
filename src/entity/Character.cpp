//
//  Character.cpp
//  Stealth
//
//  Created by L Nguyen Huu on 28/01/27 H.
//  Copyright (c) 27 Heisei L Nguyen Huu. All rights reserved.
//

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Character.h"

using namespace std;

Character::Character(std::string const &name, Point3d const &pos) : GameObject(name, pos)
{
}

Character::~Character()
{
}

void Character::update(double dt) {
    // update physics
    // if controller, let controller set intention
    if (controller) {
        controller->setIntention();

        // move based on intention
        position += controller->getIntention().move * speed;
    }
    else {
        //cout << "No controller found on Character" << endl;
    }
}

void Character::render(Renderer *renderer) {
     //cout << "rendering at " << go -> GetPosition().x() << endl;
        //BOOST_LOG_TRIVIAL(warning) << "test";

//    glClear( GL_COLOR_BUFFER_BIT);
//    glColor3f(0.0, 1.0, 0.0);
//    glBegin(GL_POLYGON);
//    glVertex3f(2.0, 4.0, 0.0);
//    glVertex3f(8.0, 4.0, 0.0);
//    glVertex3f(8.0, 6.0, 0.0);
//    glVertex3f(2.0, 6.0, 0.0);
//    glEnd();
//    glFlush();

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	int w = 640, h = 480;

    float x = getPosition().x();
    float y = getPosition().y();

	float normalizedX = x / w * 2 - 1;
	float normalizedY = -(y / h * 2 - 1);
	float normalizedX2 = (x + 20) / w * 2 - 1;
	float normalizedY2 = -((y - 20) / h * 2 - 1);

	// An array of 3 vectors which represents 3 vertices
	GLfloat g_vertex_buffer_data[] = {
		normalizedX, normalizedY, 0.0f,
		normalizedX2, normalizedY, 0.0f,
		normalizedX2, normalizedY2, 0.0f
	};

    // This will identify our vertex buffer
    GLuint vertexbuffer;
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
	);
// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);

//    SDL_Rect r;
//    //int w = 640, h = 480;
//
//    r.w = 20;
//    r.h = 20;
//    r.x = getPosition().x();
//    r.y = getPosition().y();
//
//    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0, 0xff);
//    SDL_RenderDrawRect(renderer, &r);
}
