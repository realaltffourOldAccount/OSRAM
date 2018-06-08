#pragma once
#include <GL\glew.h>

#include "VBO.h"

namespace OSRAM {
	namespace GRAPHICS {
		namespace BUFFER {
			class VAO
			{
			public:
				#define TYPE_FLOAT  0x1406;
				#define TYPE_INT  0x1404;

				 struct buffer_vertices_data_info {
					GLenum		  _type;			// type of the values
					const GLvoid* _offset;			// offset for the first value
					GLsizei		  _stride;			// byte offset of consecutive generic values attributes
					GLint		  _components;		// number of components per generic vertix attribute
				};
				 struct buffer_color_data_info {
					GLenum		  _type;			// type of the values
					const GLvoid* _offset;			// offset for the first value
					GLsizei		  _stride;			// byte offset of consecutive generic values attributes
					GLint		  _components;		// number of components per generic vertix attribute
				};
				struct buffer_texCord_data_info {
					GLenum		  _type;			// type of the values
					const GLvoid* _offset;			// offset for the first value
					GLsizei		  _stride;			// byte offset of consecutive generic values attributes
					GLint		  _components;		// number of components per generic vertix attribute
				};
				struct buffer_layout 
				{
					buffer_vertices_data_info* _vertices_layout;
					buffer_color_data_info* _color_layout;
					buffer_texCord_data_info* _texCord_layout;
				};
			public:
				VAO(OSRAM::GRAPHICS::BUFFER::VBO vbo, buffer_layout *layout, bool texture);
				~VAO();
				void LegacyDrawBuffer();

				void Bind();
				void unBind();

			private:
				OSRAM::GRAPHICS::BUFFER::VBO* m_VBO;
				buffer_layout m_Layout;
				bool m_TextureEnabled;
				GLuint m_VAOid;
			};
		}
	}
}