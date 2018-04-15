#include "src/graphics/Window.h"
#include "src/input/Input.h"
#include "src/graphics/Shaders.h"
#include <iostream>

void draw_vbo()
{
	GLuint vbo, ibo;
	GLfloat verts[] = {
		0.0f, 0.0f,
		0.5f, 0.0f,
		0.0f, 0.5f,
	};
	GLubyte ind[8] = { 0,1,2 };

	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), verts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(GLubyte), ind,
		GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(GLfloat), 0);
	glDrawElements(GL_TRIANGLES, 8, GL_UNSIGNED_BYTE, 0);
	glDisableClientState(GL_VERTEX_ARRAY);

	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

int main()
{
	OSRAM::GRAPHICS::Window window(460, 460, "Defualt Title");
	OSRAM::INPUT::Input input(window.getWindowHandler(), GLFW_CURSOR_NORMAL);
	OSRAM::GRAPHICS::Shaders shader;

	shader.UseProgram();

	while (!glfwWindowShouldClose(window.getWindowHandler()))
	{
		window.Update();
		draw_vbo();
	}
	return 0;
}