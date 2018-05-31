#include "Sprite2D.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../utils/stbi_image.h"

namespace OSRAM {
	namespace GRAPHICS {
		Sprite2D::Sprite2D(DATA data, Shaders *shader)
		{
			m_Data = data;
			m_Shader = shader;
		
			GLfloat vertices[6*4] = {// Positions											// Color				
				data._center.x - (data._size.x / 2), data._center.y - (data._size.y / 2),	data._color[0].x, data._color[0].y, data._color[0].z, data._color[0].w,
				data._center.x + (data._size.x / 2), data._center.y - (data._size.y / 2),	data._color[1].x, data._color[1].y, data._color[1].z, data._color[1].w,
				data._center.x - (data._size.x / 2), data._center.y + (data._size.y / 2),	data._color[2].x, data._color[2].y, data._color[2].z, data._color[2].w,
				data._center.x + (data._size.x / 2), data._center.y + (data._size.y / 2),	data._color[3].x, data._color[3].y, data._color[3].z, data._color[3].w
			};
			m_Vertices[0] = data._center.x - (data._size.x / 2);
			m_Vertices[1] = data._center.y - (data._size.y / 2);
			m_Vertices[2] = data._center.x + (data._size.x / 2);
			m_Vertices[3] = data._center.y - (data._size.y / 2);
			m_Vertices[4] = data._center.x - (data._size.x / 2);
			m_Vertices[5] = data._center.y + (data._size.y / 2);
			m_Vertices[6] = data._center.x + (data._size.x / 2);
			m_Vertices[7] = data._center.y + (data._size.y / 2);
			
			m_Colors[0] = data._color[0].x;
			m_Colors[1] = data._color[0].y;
			m_Colors[2] = data._color[0].z;
			m_Colors[3] = data._color[0].w;

			m_Colors[4] = data._color[1].x;
			m_Colors[5] = data._color[1].y;
			m_Colors[6] = data._color[1].z;
			m_Colors[7] = data._color[1].w;

			m_Colors[8] = data._color[2].x;
			m_Colors[9] = data._color[2].y;
			m_Colors[10] = data._color[2].z;
			m_Colors[11] = data._color[2].w;
						
			m_Colors[12] = data._color[3].x;
			m_Colors[13] = data._color[3].y;
			m_Colors[14] = data._color[3].z;
			m_Colors[15] = data._color[3].w;

		//	memcpy(&m_Buffer, &vertices, sizeof(vertices));

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

		Sprite2D::~Sprite2D()
		{
		}

		void Sprite2D::LegacyDraw()
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