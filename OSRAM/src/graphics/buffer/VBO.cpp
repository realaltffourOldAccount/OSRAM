#include "VBO.h"
#include "../Window.h"

OSRAM::GRAPHICS::BUFFER::VBO::VBO(GLfloat *vertices, int count)
{
	m_verticesCount = count;
	m_Vertices = new float[count];

	for (int i = 0; i < count; i++)
	{
		m_Vertices[i] = vertices[i];
	}

	glGenBuffers(1, &m_VBOid);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOid);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), m_Vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	
	OSRAM::GRAPHICS::Window::CheckError();
}

OSRAM::GRAPHICS::BUFFER::VBO::~VBO()
{
	glDeleteBuffers(1, &m_VBOid);
}

void OSRAM::GRAPHICS::BUFFER::VBO::LegacyDraw()	// should only be used for testing porpuses
{
	GLuint ibo;
	GLubyte ind[8] = { 0,1,2, 3,1,2 };

	glGenBuffers(1, &ibo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	this->Bind();

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

void OSRAM::GRAPHICS::BUFFER::VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOid);
}

void OSRAM::GRAPHICS::BUFFER::VBO::unBind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}