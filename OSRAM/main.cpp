#include "src\graphics\graphics-core\Window.h"
#include "src\input\Input.h"
#include "src\graphics\graphics-core\Shaders.h"
#include "src\graphics\graphics-core\buffer\VBO.h"
#include "src\graphics\graphics-core\buffer\IBO.h"
#include "src\graphics\graphics-core\buffer\VAO.h"
#include "src\graphics\graphics-core\MVP.h"
#include "src\graphics\core-2D\Sprite2DTex.h"
#include "src\graphics\core-2D\renderers\VectorRenderer2D.h"

#include <GLM\gtc\matrix_transform.hpp>
#include <GLM\mat4x4.hpp>
#include <iostream>

//#define OSRAM_TEST 0
//#define OSRAM_PINGPONG 1
//#define OSRAM_PLATFORMER 2
//#define OSRAM_PLAYGROUND 3
//#define OSRAM_PLAYGROUND2 4
#define OSRAM_AUDIO_TEST 5
//#define OSRAM_LOG_TEST 6
//#define OSRAM_OPGL_INTERMIDIATE 7

#ifdef OSRAM_TEST

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

void draw_cube()
{
	glBegin(GL_QUADS); // of the color cube

					   // Top-face
	glColor3f(0.0f, 1.0f, 0.0f); // green
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	// Bottom-face
	glColor3f(1.0f, 0.5f, 0.0f); // orange
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Front-face
	glColor3f(1.0f, 0.0f, 0.0f); // red
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	// Back-face
	glColor3f(1.0f, 1.0f, 0.0f); // yellow
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	// Left-face
	glColor3f(0.0f, 0.0f, 1.0f); // blue
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	// Right-face
	glColor3f(1.0f, 0.0f, 1.0f); // magenta
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	glEnd(); // of the color cube
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

	OSRAM::GRAPHICS::Window window(760, 560, "Default Title");
	OSRAM::INPUT::Input input(&window, GLFW_CURSOR_NORMAL);
	OSRAM::GRAPHICS::Shaders shader(&window);	

	OSRAM::GRAPHICS::MVP mvp(&shader);
	//OSRAM::GRAPHICS::BUFFER::VBO vbo(vert, 8, 2);
	//OSRAM::GRAPHICS::BUFFER::IBO ibo(ind, 6);

	glm::mat4 proj(1.0f);
	glm::mat4 model(1.0f);
	glm::mat4 view(1.0f);
	//view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.4f, 0.3f));
	//view = glm::rotate(glm::mat4(1.0f), glm::radians(25.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	proj = glm::ortho(0.0f, (float)(760), 0.0f, (float)(560), -1.0f, 1.0f);
	OSRAM::GRAPHICS::RENDERERS::Renderable2D::DATA_Tex data;
	data._center.x = 760 / 2;
	data._center.y = 560 / 2;
	data._size.x = 100;
	data._size.y = 100;
	data._color[0] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	data._color[1] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	data._color[2] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	data._color[3] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	data._texCord[0] = glm::vec2(1.0f, 1.0f);
	data._texCord[1] = glm::vec2(1.0f, 0.0f);
	data._texCord[2] = glm::vec2(0.0f, 0.0f);
	data._texCord[3] = glm::vec2(0.0f, 1.0f);
	data._texturePATH = "container.jpg";
	OSRAM::GRAPHICS::Sprite2DTex tex(data, &window);


	//OSRAM::GRAPHICS::BasicRenderer2D basic_renderer2d(&mvp);
	//	OSRAM::GRAPHICS::BatchRenderer2D batch_renderer2d(proj, view, &mvp);

		//mvp.SetModelMatrix(sprite.GetModelMatrix());

		//shader.Uniform4f(shader.GetBasicProgram(),"m_Color", 0.2f, 0.3f, 0.5f, 1.0f);
		//glClearColor(0.03f, 0.0f, 0.0f, 1.0f);

	tex.SetChangerSpeedPosY(0.5f);
	tex.SetChangerSpeedNegY(-0.5f);
	tex.SetChangerSpeedPosX(0.5f);
	tex.SetChangerSpeedNegX(-0.5f);
	tex.SetSpeedPosY(0.5f);
	tex.SetSpeedPosX(0.5f);
	tex.SetSpeedNegX(-0.5f);
	tex.SetSpeedNegY(-0.5f);

	//shader.UseBasicProgram();
	shader.UseTextureProgram();
	mvp.SetTextureProjectionMatrix(proj);
	mvp.SetTextureViewMatrix(view);

	OSRAM::GRAPHICS::RENDERERS::VectorRenderer2D renderV(&mvp);
	renderV.setProjection(proj);
	renderV.add(&tex, "test");
	while (!glfwWindowShouldClose(window.getWindowHandler()))
	{
		window.Update();

		if (input.isKeyPressed(GLFW_KEY_W) == true)
		{
			tex.moveYAccelerated();
			//tex.moveY();
		}
		if (input.isKeyPressed(GLFW_KEY_S) == true)
		{
			tex.moveNegYAccelerated();
			//tex.moveNegY();
		}
		if (input.isKeyPressed(GLFW_KEY_D) == true)
		{
			tex.moveXAccelerated();
			//tex.moveX();
		}
		if (input.isKeyPressed(GLFW_KEY_A) == true)
		{
			tex.moveNegXAccelerated();
			//tex.moveNegX();
		}
		else if (input.isKeyPressed(GLFW_KEY_W) == false && input.isKeyPressed(GLFW_KEY_S) == false
			&& input.isKeyPressed(GLFW_KEY_D) == false && input.isKeyPressed(GLFW_KEY_A) == false)
		{
			tex.ResetSpeedPosX();
			tex.ResetSpeedPosY();
			tex.ResetSpeedNegX();
			tex.ResetSpeedNegY();
		}

		//basic_renderer2d.submit(&sprite);
		//glm::mat4 temp = glm::mat4(1.0f);
		//mvp.SetTextureModelMatrix(tex.GetModelMatrix());
		//tex.LegacyDraw();
	//	renderV.setModelMatrix("test", tex.GetModelMatrix());
		renderV.flush(view, proj);
		//basic_renderer2d.flush(proj, view, sprite.GetModelMatrix());


		window.RenderImGUI();
	}
	return 0;
}
#endif // OSRAM_TEST
#ifdef OSRAM_PINGPONG

#define GLEW_STATIC
#include "example\PingPong_example.h"

int main()
{
	PingPong game;
	
	game.Run();

	return 0;
}

#endif // OSRAM_PINGPONG

#ifdef OSRAM_PLATFORMER

#include "example\Platformer_example\Platformer2D.h"

int main()
{
	Platformer2D game;
	game.Run();
	return 0;
}

#endif // OSRAM_PLATFORMER


#ifdef OSRAM_PLAYGROUND 
#include "src\graphics\buffer\VBO.h"
#include "src\graphics\buffer\IBO.h"
#include "src\graphics\buffer\VAO.h"

#include "src\utils\stb_image_read.h"

int main()
{
	OSRAM::GRAPHICS::Window window(800, 600, "PLAYGROUND");
	OSRAM::GRAPHICS::Shaders shaders;
	OSRAM::GRAPHICS::MVP mvp(&shaders);
	shaders.UseTextureProgram();

	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // top left 
	};

	float vertices1[] = {
		 // positions        // texture coords
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f  // top left 
	};

	GLubyte ind[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	GLuint vao;
	OSRAM::GRAPHICS::BUFFER::VBO vbo(vertices, 8 * 4);
	OSRAM::GRAPHICS::BUFFER::IBO ibo(ind, 6);
	vbo.Bind();
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	GLuint texture;
	std::string buffer;

	glGenTextures(1, &texture);
	if (!texture)
		std::cout << "Could not create texture. . . " << std::endl;

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* image = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	//unsigned char* image = SOIL_load_image("test.png", &width, &height, (int)SOIL_LOAD_AUTO, SOIL_LOAD_RGB);
	
	if (!image)
	{
		std::cout << "Could Not read texture" << std::endl;
	}

	float pixels[] = {
		0.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f
	};

	window.CheckError();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	//glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	while (glfwWindowShouldClose(window.getWindowHandler()) == false)
	{
		window.Update();

		vbo.Bind();
		ibo.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
		window.CheckError();

		window.RenderImGUI();
	}
}

#endif // OSRAM_PLAYGROUND 2

#ifdef OSRAM_PLAYGROUND2

#include "src\graphics\Window.h"
#include "src\graphics\Shaders.h"
#include "src\graphics\MVP.h"
#include "src\graphics\Sprite2DTex.h"

int main()
{
	OSRAM::GRAPHICS::Window window(800, 600, "PLAYGROUND");
	OSRAM::GRAPHICS::Shaders shaders;
	OSRAM::GRAPHICS::MVP mvp(&shaders);

	OSRAM::GRAPHICS::Renderable2D::DATA_Tex data;
	data._center.x = 0.0f;
	data._center.y = 0.0f;
	data._size.x = 0.5f + (0.5f / 2);
	data._size.y = 0.5f + (0.5f / 2);
	data._color[0] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	data._color[1] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	data._color[2] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	data._color[3] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	data._texCord[0] = glm::vec2(1.0f, 1.0f);
	data._texCord[1] = glm::vec2(1.0f, 0.0f);
	data._texCord[2] = glm::vec2(0.0f, 0.0f);
	data._texCord[3] = glm::vec2(0.0f, 1.0f);
	data._texturePATH = "container.jpg";
	OSRAM::GRAPHICS::Sprite2DTex tex(data);

	shaders.UseTextureProgram();

	while (!glfwWindowShouldClose(window.getWindowHandler()))
	{
		window.Update();

		tex.LegacyDraw();

		window.RenderImGUI();
	}
}

#endif // OSRAM_PLAYGROUND 2

#ifdef OSRAM_AUDIO_TEST
#include <iostream>
#include "src\audio\AudioManager.h"

int main()
{
	OSRAM::AUDIO::AudioManager audio;
	OSRAM::AUDIO::AudioManager::ListenerDATA ldata;
	OSRAM::AUDIO::AudioManager::BufferObject bdata;
	OSRAM::AUDIO::AudioManager::AudioObject adata;

	bdata._PATH = "canary.wav";
	bdata._name = "test";
	bdata._loop = (ALboolean)AL_TRUE;

	adata._bindedBuffer = &bdata;
	adata._name = "test1";
	adata._looping = (ALboolean)AL_TRUE;
	adata._pitch = 1;
	adata._gain = 1;
	adata._pos = glm::vec3(0, 0, 0);
	adata._velocity = glm::vec3(0);

	ldata._ori[0] =  0.0f;
	ldata._ori[1] =  0.0f;
	ldata._ori[2] =  1.0f;
	ldata._ori[3] =  0.0f;
	ldata._ori[4] =  1.0f;
	ldata._ori[5] =  0.0f;
	ldata._pos = glm::vec3(0.0f,0.0f,1.0f);
	ldata._velocity = glm::vec3(0.0f, 0.0f, 0.0f);

	audio.SetListener(ldata);
	audio.AddBufferObject(bdata);
	audio.AddAudioObject(adata);
	audio.SetBufferOBJForAudioOBJ("test1", "test");
	audio.PlayAudioOBJ("test1");
	while (true)
	{
		audio.Update();
	}

}
#endif // OSRAM_AUDIO_TEST

#ifdef OSRAM_LOG_TEST

#include "src\utils\Log.h"

using namespace OSRAM::UTILS;

int main()
{
	Log log;

	log.LogMSG(log.MSG_NORMAL, log._prefix._WINDOW, "Hello World");

	log.FlushToFile();

	while (true);

	return 0;
}

#endif // OSRAM_LOG_TEST


#ifdef OSRAM_OPGL_INTERMIDIATE


void draw_cube()
{
	glBegin(GL_QUADS); // of the color cube

					   // Top-face
	glColor3f(0.0f, 1.0f, 0.0f); // green
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	// Bottom-face
	glColor3f(1.0f, 0.5f, 0.0f); // orange
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Front-face
	glColor3f(1.0f, 0.0f, 0.0f); // red
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	// Back-face
	glColor3f(1.0f, 1.0f, 0.0f); // yellow
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	// Left-face
	glColor3f(0.0f, 0.0f, 1.0f); // blue
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	// Right-face
	glColor3f(1.0f, 0.0f, 1.0f); // magenta
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	glEnd(); // of the color cube
}

int main()
{
	OSRAM::GRAPHICS::Window window(760, 560, "Default Title");
	OSRAM::INPUT::Input input(&window, GLFW_CURSOR_NORMAL);
	
	while (!glfwWindowShouldClose(window.getWindowHandler()))
	{
		window.Update();

		
		draw_cube();

		window.RenderImGUI();
	}
	return 0;
#endif // OSRAM_OPGL_INTERMDIATE
