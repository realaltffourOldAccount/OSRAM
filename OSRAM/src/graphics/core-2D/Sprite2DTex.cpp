#pragma once
#include "Sprite2DTex.h"

#define STB_IMAGE_IMPLEMENTATION
#include "..\..\utils\stb_image_read.h"


OSRAM::GRAPHICS::Sprite2DTex::Sprite2DTex(DATA_Tex data, Window* window)
{
	_TexSpec = data;
	win = window;
	init();
}

OSRAM::GRAPHICS::Sprite2DTex::~Sprite2DTex()
{
	glDeleteTextures(1, &m_TextureID);
	glDeleteBuffers(1, &m_DataBuff);
	glDeleteBuffers(1, &m_IndicesBuff);
	glDeleteVertexArrays(1, &m_VertexArray);
}

void OSRAM::GRAPHICS::Sprite2DTex::LegacyDraw()
{
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	glBindVertexArray(m_VertexArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndicesBuff);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
}

void OSRAM::GRAPHICS::Sprite2DTex::init()
{
	glGenVertexArrays(1, &m_VertexArray);
	glGenBuffers(1, &m_DataBuff);
	glGenBuffers(1, &m_IndicesBuff);
	glGenTextures(1, &m_TextureID);

	GLfloat buffer[8 * 4] = {
		// Vertex Data																			 // Color Data																			 // TexCord Data
		_TexSpec._center.x + (_TexSpec._size.x / 2), _TexSpec._center.y + (_TexSpec._size.y / 2), _TexSpec._color[0].x, _TexSpec._color[0].y, _TexSpec._color[0].z, _TexSpec._color[0].w, _TexSpec._texCord[0].x, _TexSpec._texCord[0].y,
		_TexSpec._center.x + (_TexSpec._size.x / 2), _TexSpec._center.y - (_TexSpec._size.y / 2), _TexSpec._color[1].x, _TexSpec._color[1].y, _TexSpec._color[1].z, _TexSpec._color[1].w, _TexSpec._texCord[1].x, _TexSpec._texCord[1].y,
		_TexSpec._center.x - (_TexSpec._size.x / 2), _TexSpec._center.y - (_TexSpec._size.y / 2), _TexSpec._color[2].x, _TexSpec._color[2].y, _TexSpec._color[2].z, _TexSpec._color[2].w, _TexSpec._texCord[2].x, _TexSpec._texCord[2].y,
		_TexSpec._center.x - (_TexSpec._size.x / 2), _TexSpec._center.y + (_TexSpec._size.y / 2), _TexSpec._color[3].x, _TexSpec._color[3].y, _TexSpec._color[3].z, _TexSpec._color[3].w, _TexSpec._texCord[3].x, _TexSpec._texCord[3].y,
	};

	m_Vertices[0] = _TexSpec._center.x - (_TexSpec._size.x / 2);
	m_Vertices[1] = _TexSpec._center.y - (_TexSpec._size.y / 2);
	m_Vertices[2] = _TexSpec._center.x + (_TexSpec._size.x / 2);
	m_Vertices[3] = _TexSpec._center.y - (_TexSpec._size.y / 2);
	m_Vertices[4] = _TexSpec._center.x - (_TexSpec._size.x / 2);
	m_Vertices[5] = _TexSpec._center.y + (_TexSpec._size.y / 2);
	m_Vertices[6] = _TexSpec._center.y + (_TexSpec._size.y / 2);

	m_Colors[0] = _TexSpec._color[0].x;
	m_Colors[1] = _TexSpec._color[0].y;
	m_Colors[2] = _TexSpec._color[0].z;
	m_Colors[3] = _TexSpec._color[0].w;

	m_Colors[4] = _TexSpec._color[1].x;
	m_Colors[5] = _TexSpec._color[1].y;
	m_Colors[6] = _TexSpec._color[1].z;
	m_Colors[7] = _TexSpec._color[1].w;


	m_Colors[8] = _TexSpec._color[2].x;
	m_Colors[9] = _TexSpec._color[2].y;
	m_Colors[10] = _TexSpec._color[2].z;
	m_Colors[11] = _TexSpec._color[2].w;

	m_Colors[12] = _TexSpec._color[3].x;
	m_Colors[13] = _TexSpec._color[3].y;
	m_Colors[14] = _TexSpec._color[3].z;
	m_Colors[15] = _TexSpec._color[3].w;

	glBindVertexArray(m_VertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, m_DataBuff);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float) * 8, (void*)0);
	glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(float) * 8, (void*)(sizeof(float) * 2));
	glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(float) * 8, (void*)(sizeof(float) * 6));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndicesBuff);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ind), &ind, GL_STATIC_DRAW);

	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	Window::CheckError();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Window::CheckError();

	// TODO: ADD file loading mechanism
	win->getLog()->LogMSG(win->getLog()->MSG_NORMAL, win->getLog()->_prefix._Sprite2DTex, "Loading File: " + _TexSpec._texturePATH + " . . . ");
	stbi_set_flip_vertically_on_load(true);
	t_data = stbi_load(_TexSpec._texturePATH.c_str(), &t_Width, &t_Hieght, &t_nrChannels, 0);
	if (t_data == NULL)
		win->getLog()->LogMSG(win->getLog()->MSG_ERROR, win->getLog()->_prefix._Sprite2DTex, "Loading File: " + _TexSpec._texturePATH + " . . . FAIL");
	else
		win->getLog()->LogMSG(win->getLog()->MSG_NORMAL, win->getLog()->_prefix._Sprite2DTex, "Loading File: " + _TexSpec._texturePATH + " . . . SUCCESS");

	float pixels[] = {
		0.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f
	};

	if (t_nrChannels == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, t_Width, t_Hieght, 0, GL_RGB, GL_UNSIGNED_BYTE, t_data);
	else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, t_Width, t_Hieght, 0, GL_RGBA, GL_UNSIGNED_BYTE, t_data);
	glGenerateMipmap(GL_TEXTURE_2D);
	Window::CheckError();
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);
	glBindTexture(GL_TEXTURE_2D, 0);
}