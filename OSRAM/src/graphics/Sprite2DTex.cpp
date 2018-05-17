#include "Sprite2DTex.h"

#define STB_IMAGE_IMPLENATATION
#include "../utils/stbi_image.h"

OSRAM::GRAPHICS::Sprite2DTex::Sprite2DTex(DATA data, Shaders * shaders)
{
	m_Data = data;
	m_vertices = new float[4*3];
	
	float vertices[] = {
			// Vertice																	// Tex-Cord
			data._center.x - (data._size.x / 2), data._center.y - (data._size.y / 2),	1.0f, 1.0f,	// top right
			data._center.x + (data._size.x / 2), data._center.y - (data._size.y / 2),	1.0f, 0.0f,	// bottom right
			data._center.x - (data._size.x / 2), data._center.y + (data._size.y / 2),	0.0f, 0.0f,	// bottom left
			data._center.x + (data._size.x / 2), data._center.y + (data._size.y / 2),	0.0f, 1.0f	// top left
	};
	m_vertices = vertices;

	VAO::buffer_layout layout;
	layout._type = VAO::buffer_layout_type::TYPE_FLOAT;
	layout._vertex_components = 2;
	m_VAO = new VAO(VBO(m_vertices, (4 * 3), 2), layout);
	m_VAO->Bind();
	m_IBO = new IBO(ind, 6);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(3 * sizeof(float)));

	m_TexData = stbi_load(data._texture_file.c_str(), &m_TexWidth, &m_TexHieght, &m_nrChannels, 0);

	if (m_TexData)
	{
		std::cout << "[SPRITE:TEXTURE] Loaded Texture...SUCCESS"  << std::endl;
	}
	else
	{
		std::cout << "[SPRITE:TEXTURE] Loaded Texture...FAIL" << std::endl;
	}

	glGenTextures(1, &m_Texture);

	glBindTexture(GL_TEXTURE_2D, m_Texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_TexWidth, m_TexHieght, 0, GL_RGB, GL_UNSIGNED_BYTE, m_TexData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(m_TexData);
}

OSRAM::GRAPHICS::Sprite2DTex::~Sprite2DTex()
{
	glDeleteTextures(1, &m_Texture);
}

void OSRAM::GRAPHICS::Sprite2DTex::LegacyDraw()
{
	m_VAO->Bind();
	m_IBO->Bind();
	BindTexture();
//	m_Shader->Uniform4f(m_Shader->GetTextureProgram(),"m_Color", m_Data._color_adj.x, m_Data._color_adj.y, m_Data._color_adj.z, m_Data._color_adj.w);
	m_VAO->LegacyDrawBuffer();
	unBindTexture();
	m_VAO->unBind();
	m_IBO->unBind();
}

void OSRAM::GRAPHICS::Sprite2DTex::BindTexture()
{
	glBindTexture(GL_TEXTURE_2D, m_Texture);
}

void OSRAM::GRAPHICS::Sprite2DTex::unBindTexture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
