#include "VAO.h"



OSRAM::GRAPHICS::BUFFER::VAO::VAO(BUFFER::VBO vbo, buffer_layout layout)
{
	m_VBO = &vbo;
	m_Layout = layout;

	glGenVertexArrays(1, &m_VAOid);

	this->Bind();
	m_VBO->Bind();
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, layout._vertex_components, layout._type, 0, 0, NULL);

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
	GLuint ibo;
	GLubyte ind[8] = { 0,1,2, 3,1,2 };

	glGenBuffers(1, &ibo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 8 * sizeof(GLubyte), ind,
		GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
	this->Bind();
	//glVertexPointer(3, GL_FLOAT, sizeof(GLfloat), 0);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 2, GL_FLOAT, 0, 0, 0);
	glDrawElements(GL_TRIANGLES, 8, GL_UNSIGNED_BYTE, 0);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDeleteBuffers(1, &ibo);
}

