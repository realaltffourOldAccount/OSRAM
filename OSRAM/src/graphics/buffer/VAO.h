#pragma once
#include <GL\glew.h>

#include "VBO.h"

namespace OSRAM {
	namespace GRAPHICS {
		namespace BUFFER {
			class VAO
			{
			public:
				enum buffer_layout_type {
					TYPE_FLOAT,
					TYPE_INT
				};
				struct buffer_layout 
				{
					buffer_layout_type _type;
					int _vertex_components = 0;
				};
			public:
				VAO(BUFFER::VBO vbo, buffer_layout layout);
				~VAO();
				void LegacyDrawBuffer();

				void Bind();
				void unBind();

			private:
				OSRAM::GRAPHICS::BUFFER::VBO* m_VBO;
				buffer_layout m_Layout;

				GLuint m_VAOid;
			};
		}
	}
}