#include "src/graphics/Window.h"
#include "src/input/Input.h"
#include "src/graphics/Shaders.h"
#include <iostream>

int main()
{
	OSRAM::GRAPHICS::Window window(460, 460, "Defualt Title");
	OSRAM::INPUT::Input input(window.getWindowHandler());
	OSRAM::GRAPHICS::Shaders shader;
	
	float vertices[] = {
		0.5f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.5f
	};
	unsigned int indices[] = {
		0,1,2,
		2,3,1
	};

	GLuint vbo, vao, ibo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vbo), &vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	shader.UseProgram();

	while (!glfwWindowShouldClose(window.getWindowHandler()))
	{
		window.Update();
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glDrawBuffer(GL_TRIANGLES);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

	}
	return 0;
}