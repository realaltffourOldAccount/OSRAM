#pragma once
#include "Sprite2DTex.h"

#define STB_IMAGE_IMPLENATATION
#include "../utils/stbi_image.h"

OSRAM::GRAPHICS::Sprite2DTex::Sprite2DTex(DATA * data, Shaders * shaders)
{
	m_TexData = stbi_load(data->_texture_file.c_str(), &m_TexWidth, &m_TexHieght, &m_nrChannels, 0);

	glGenTextures(1, &m_Texture);

	glBindTexture(GL_TEXTURE_2D, m_Texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_TexWidth, m_TexHieght, 0, GL_RGB, GL_UNSIGNED_BYTE, m_TexData);

}

OSRAM::GRAPHICS::Sprite2DTex::~Sprite2DTex()
{

}

void OSRAM::GRAPHICS::Sprite2DTex::LegacyDraw()
{

}
