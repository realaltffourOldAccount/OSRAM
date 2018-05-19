#include "Spirite2D.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../utils/stbi_image.h"

namespace OSRAM {
	namespace GRAPHICS {
		Spirite2D::Spirite2D(DATA data, Shaders *shader)
		{
			m_Data = data;
			m_Shader = shader;
		
			GLfloat vertices[6*4] = {// Positions											// Color				
				data._center.x - (data._size.x / 2), data._center.y - (data._size.y / 2),	data._color[0].x, data._color[0].y, data._color[0].z, data._color[0].w,
				data._center.x + (data._size.x / 2), data._center.y - (data._size.y / 2),	data._color[1].x, data._color[1].y, data._color[1].z, data._color[1].w,
				data._center.x - (data._size.x / 2), data._center.y + (data._size.y / 2),	data._color[2].x, data._color[2].y, data._color[2].z, data._color[2].w,
				data._center.x + (data._size.x / 2), data._center.y + (data._size.y / 2),	data._color[3].x, data._color[3].y, data._color[3].z, data._color[3].w
			};

			VAO::buffer_layout layout;
			layout._vertices_layout = new VAO::buffer_vertices_data_info;
			layout._color_layout = new VAO::buffer_color_data_info;
			// Vertices
			layout._vertices_layout->_type = GL_FLOAT;
			layout._vertices_layout->_components = 2;
			layout._vertices_layout->_offset = 0;
			layout._vertices_layout->_stride = sizeof(GLfloat) * 6;
			
			//std::cout << sizeof(GLfloat) * 2 << "/" << sizeof(data._center.x - (data._size.x / 2)) * 2  << std::endl;

			// Colors
			layout._color_layout->_type = GL_FLOAT;
			layout._color_layout->_components = 4;
			layout._color_layout->_offset = (void*)(sizeof(GLfloat) * 2);
			layout._color_layout->_stride = sizeof(GLfloat) * 6;

			m_VAO = new VAO(VBO(vertices, 6*4), &layout, false);
			m_IBO = new IBO(ind, 6);
			
		}

		Spirite2D::~Spirite2D()
		{
		}

		void Spirite2D::LegacyDraw()
		{
			m_VAO->Bind();
			m_IBO->Bind();
			//	m_Shader->Uniform4f(m_Shader->GetBasicProgram()
			//	,"m_Color", m_Data._color.x, m_Data._color.y, m_Data._color.z, m_Data._color.w);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);
			m_IBO->unBind();
			m_VAO->unBind();
		}
	}
}