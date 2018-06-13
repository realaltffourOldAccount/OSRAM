#include "VAO.h"

#include "../Window.h"

OSRAM::GRAPHICS::BUFFER::VAO::VAO(BUFFER::VBO vbo, buffer_layout *layout, bool texture)
{
	m_VBO = &vbo;
	m_Layout = *layout;
	m_TextureEnabled = texture;

	glGenVertexArrays(1, &m_VAOid);
	Window::CheckError();
	this->Bind();
	Window::CheckError();
	m_VBO->Bind();
	Window::CheckError();
	glEnableVertexAttribArray(0);
	Window::CheckError();
	glVertexAttribPointer(0, m_Layout._vertices_layout->_components
		, m_Layout._vertices_layout->_type
		, GL_FALSE
		, m_Layout._vertices_layout->_stride
		, m_Layout._vertices_layout->_offset);Window::CheckError();

	glEnableVertexAttribArray(1);Window::CheckError();
	glVertexAttribPointer(1, m_Layout._color_layout->_components
		, m_Layout._color_layout->_type
		, GL_FALSE
		, m_Layout._color_layout->_stride
		, m_Layout._color_layout->_offset);Window::CheckError();

	if (m_TextureEnabled == true)
	{
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, m_Layout._texCord_layout->_components
			, m_Layout._texCord_layout->_type
			, GL_FALSE
			, m_Layout._texCord_layout->_stride
			, m_Layout._texCord_layout->_offset);
	}

	this->unBind();
	m_VBO->unBind();
}

void OSRAM::GRAPHICS::BUFFER::VAO::Bind()
{
	glBindVertexArray(m_VAOid);
}

void OSRAM::GRAPHICS::BUFFER::VAO::unBind()
{
	glBindVertexArray(0);
}

OSRAM::GRAPHICS::BUFFER::VAO::~VAO()
{
	glDeleteVertexArrays(1, &m_VAOid);
}

void OSRAM::GRAPHICS::BUFFER::VAO::LegacyDrawBuffer()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	this->Bind();
	//glVertexPointer(3, GL_FLOAT, sizeof(GLfloat), 0);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 2, GL_FLOAT, 0, 0, 0);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
	glDisableClientState(GL_VERTEX_ARRAY);
}

