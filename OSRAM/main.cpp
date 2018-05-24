#include "src/graphics/Window.h"
#include "src/input/Input.h"
#include "src/graphics/Shaders.h"
#include "src/graphics/buffer/VBO.h"
#include "src/graphics/buffer/IBO.h"
#include "src/graphics/buffer/VAO.h"
#include "src/graphics/Sprite2D.h"
#include "src/graphics/MVP.h"
#include "src/graphics/BasicRenderer2D.h"

#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/mat4x4.hpp>
#include <iostream>

void draw_vbo()
{
	GLuint vbo, ibo;
	GLfloat vert[8] = {
		0.0f, 0.0f,
		0.5f, 0.0f,
		0.0f, 0.5f,
		0.5f, 0.5f
	};
	GLubyte ind[6] = { 0,1,2, 3,1,2 };

	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), vert, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 8 * sizeof(GLubyte), ind,
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
	GLfloat vert[8] = {
		0.0f, 0.0f,
		0.5f, 0.0f,
		0.0f, 0.5f,
		0.5f, 0.5f
	};
	GLubyte ind[6] = { 0,1,2, 3,1,2 };

	OSRAM::GRAPHICS::Window window(460, 460, "Default Title");
	OSRAM::INPUT::Input input(window.getWindowHandler(), GLFW_CURSOR_NORMAL);
	OSRAM::GRAPHICS::Shaders shader;
	OSRAM::GRAPHICS::MVP mvp(&shader);
	//OSRAM::GRAPHICS::BUFFER::VBO vbo(vert, 8, 2);
	//OSRAM::GRAPHICS::BUFFER::IBO ibo(ind, 6);
	
	glm::mat4 proj(1.0f);
	glm::mat4 model(1.0f);
	glm::mat4 view(1.0f);
	//view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.4f, 0.3f));
	view = glm::rotate(glm::mat4(1.0f), glm::radians(25.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	proj = glm::ortho(0.0f, 230.0f, 0.0f, 230.0f, -1.0f, 1.0f);

	OSRAM::GRAPHICS::Sprite2D::DATA data;
	data._center = glm::vec2(50.0f, 50.0f);
	data._size = glm::vec2(10.0f, 10.0f);
	data._color[0] = glm::vec4(1.0f, 0.0f, 0.0f, 0.5f);
	data._color[1] = glm::vec4(0.0f, 1.0f, 0.0f, 0.5f);
	data._color[2] = glm::vec4(0.0f, 0.0f, 1.0f, 0.5f);
	data._color[3] = glm::vec4(0.5f, 0.5f, 0.0f, 0.5f);
	OSRAM::GRAPHICS::Sprite2D sprite(data, &shader);

	OSRAM::GRAPHICS::Sprite2D::DATA data2;
	data2._center = glm::vec2(60.4f, 50.4f);
	data2._size = glm::vec2(5.0f, 5.2f);
	data2._color[0] = glm::vec4(1.0f, 0.0f, 0.0f, 0.5f);
	data2._color[1] = glm::vec4(0.0f, 1.0f, 0.0f, 0.5f);
	data2._color[2] = glm::vec4(0.0f, 0.0f, 1.0f, 0.5f);
	data2._color[3] = glm::vec4(0.5f, 0.5f, 0.0f, 0.5f);
	OSRAM::GRAPHICS::Sprite2D sprite2(data2, &shader);

	OSRAM::GRAPHICS::BasicRenderer2D basic_renderer2d;

	shader.UseBasicProgram();
	mvp.SetModelMatrix(sprite.GetModelMatrix());
	mvp.SetProjectionMatrix(proj);
	//mvp.SetViewMatrix(view);

	//shader.Uniform4f(shader.GetBasicProgram(),"m_Color", 0.2f, 0.3f, 0.5f, 1.0f);
	//glClearColor(0.03f, 0.0f, 0.0f, 1.0f);

	sprite.EnableProgressiveAcc(true, 0.5f);
	sprite.SetAccelerationSpeedPos(0.5f);
	sprite.SetAccelerationSpeedNeg(-0.5f);
	while (!glfwWindowShouldClose(window.getWindowHandler()))
	{
		window.Update();

		if (input.isKeyPressed(GLFW_KEY_W) == true)
			sprite.accelerateY(true);
		else if (input.isKeyPressed(GLFW_KEY_W) == false && input.isKeyPressed(GLFW_KEY_S) == false 
			&& input.isKeyPressed(GLFW_KEY_D) == false && input.isKeyPressed(GLFW_KEY_A) == false)
		{	
			sprite.ResetSpeedPos();
		}
		if (input.isKeyPressed(GLFW_KEY_S) == true)
				sprite.accelerateNegY(true);
		else if (input.isKeyPressed(GLFW_KEY_S) == false && input.isKeyPressed(GLFW_KEY_W) == false 
			&& input.isKeyPressed(GLFW_KEY_D) == false && input.isKeyPressed(GLFW_KEY_A) == false)
		{
			sprite.ResetSpeedNeg();
		}
		if (input.isKeyPressed(GLFW_KEY_D) == true)
			sprite.accelerateX(true);
		else if (input.isKeyPressed(GLFW_KEY_D) == false && input.isKeyPressed(GLFW_KEY_A) == false
			&& input.isKeyPressed(GLFW_KEY_W) == false && input.isKeyPressed(GLFW_KEY_S) == false)
		{
			sprite.ResetSpeedPos();
		}
		if (input.isKeyPressed(GLFW_KEY_A) == true)
			sprite.accelerateNegX(true);
		else if (input.isKeyPressed(GLFW_KEY_A) == false && input.isKeyPressed(GLFW_KEY_D) == false 
			&& input.isKeyPressed(GLFW_KEY_W) == false && input.isKeyPressed(GLFW_KEY_S) == false)
		{
			sprite.ResetSpeedNeg();
		}

		basic_renderer2d.submit(&sprite);
		basic_renderer2d.submit(&sprite2);
		mvp.SetModelMatrix(sprite.GetModelMatrix());
		//sprite.LegacyDraw();
		basic_renderer2d.flush();

		window.RenderImGUI();
	}
	return 0;
}