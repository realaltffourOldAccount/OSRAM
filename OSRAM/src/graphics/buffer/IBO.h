#pragma once
#include <GL\glew.h>

namespace OSRAM {
	namespace GRAPHICS {
		namespace BUFFER {
			class IBO
			{
			private:
				GLuint m_IBOid;
				GLubyte *m_Indices;
				int m_Count;
			public:
				IBO(GLubyte *indices, int count);
				~IBO();

				void Bind();
				void UnBind();

			};
		}
	}
}