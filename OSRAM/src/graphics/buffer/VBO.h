#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace OSRAM
{
	namespace GRAPHICS 
	{
		namespace BUFFER
		{
			class VBO
			{
			public:
				VBO(GLfloat *vertices, int count);
				~VBO();

				void Bind();
				void unBind();

				void LegacyDraw();
			private:
				GLuint m_VBOid;
				int m_verticesCount;
				GLfloat *m_Vertices;
			};
		}
	}
}