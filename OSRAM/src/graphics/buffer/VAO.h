#pragma once
#include <GL\glew.h>

#include "VBO.h"

namespace OSRAM {
	namespace GRAPHICS {
		namespace BUFFER {
			class VAO
			{
			public:
				struct buffer_vertices_layout_type {
					int TYPE_FLOAT = 0x1406;
					int TYPE_INT = 0x1404;

				};
				struct buffer_color_layout_type {
					int TYPE_FLOAT = 0x1406;
					int TYPE_INT = 0x1404;
				};
				struct buffer_layout 
				{
					buffer_vertices_layout_type _vertices_layout;
					buffer_color_layout_type _color_layout;
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