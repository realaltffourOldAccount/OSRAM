#include "IBO.h"
#include "../Window.h"

OSRAM::GRAPHICS::BUFFER::IBO::IBO(GLubyte *indices, int count)
{
	m_Count = count;
	m_Indices = new GLubyte[count];

	for (int i = 0; i < count; i++)
		m_Indices[i] = indices[i];

	glGenBuffers(1, &m_IBOid);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBOid);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLubyte), m_Indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	OSRAM::GRAPHICS::Window::CheckError();
}

OSRAM::GRAPHICS::BUFFER::IBO::~IBO()
{
	glDeleteBuffers(1, &m_IBOid);
}

void OSRAM::GRAPHICS::BUFFER::IBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBOid);
}

void OSRAM::GRAPHICS::BUFFER::IBO::UnBind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}