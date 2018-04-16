#include "src/graphics/Window.h"
#include "src/input/Input.h"
#include "src/graphics/Shaders.h"
#include "src/graphics/buffer/VBO.h"
#include "src/graphics/buffer/IBO.h"

#include <iostream>

void draw_vbo()
{
	GLuint vbo, ibo;
	GLubyte ind[8] = { 0,1,2, 3,1,2 };

	glGenBuffers(1, &ibo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 8 * sizeof(GLubyte), ind,
		GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
	//glVertexPointer(3, GL_FLOAT, sizeof(GLfloat), 0);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 2, GL_FLOAT, 0, 0, 0);
	glDrawElements(GL_TRIANGLES, 8, GL_UNSIGNED_BYTE, 0);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDeleteBuffers(1, &ibo);
}

int main()
{
	GLfloat vert[8] = {
		0.0f, 0.0f,
		0.5f, 0.0f,
		0.0f, 0.5f,
		0.5f, 0.5f
	};
	GLubyte ind[6] = { 0,1,2, 3,1,2 };

	OSRAM::GRAPHICS::Window window(460, 460, "Defualt Title");
	OSRAM::INPUT::Input input(window.getWindowHandler(), GLFW_CURSOR_NORMAL);
	OSRAM::GRAPHICS::Shaders shader;
	OSRAM::GRAPHICS::BUFFER::VBO vbo(vert, 8, 2);
	OSRAM::GRAPHICS::BUFFER::IBO ibo(ind, 6);
	
	shader.UseProgram();
	while (!glfwWindowShouldClose(window.getWindowHandler()))
	{
		
		window.Update();
		//vbo.LegacyDraw();
		vbo.Bind();
		ibo.Bind();
		glEnableClientState(GL_VERTEX_ARRAY);
		//glVertexPointer(3, GL_FLOAT, sizeof(GLfloat), 0);
		//glEnableVertexAttribArray(0);
		//glVertexAttribPointer(0, 2, GL_FLOAT, 0, 0, 0);
		glDrawElements(GL_TRIANGLES, 8, GL_UNSIGNED_BYTE, 0);
		glDisableClientState(GL_VERTEX_ARRAY);
		//draw_vbo();
		vbo.unBind();
		ibo.UnBind();
	}
	return 0;
}