#include "Spirite2D.h"


namespace OSRAM {
	namespace GRAPHICS {
		Spirite2D::Spirite2D(DATA data, Shaders *shader)
		{
			m_Data = data;
			m_Shader = shader;

			m_vertices = new float[8];

			float vertices[8] = {
				data._center.x - (data._size.x/2), data._center.y - (data._size.y / 2),
				data._center.x + (data._size.x/2), data._center.y - (data._size.y / 2),
				data._center.x - (data._size.x/2), data._center.y + (data._size.y / 2),
				data._center.x + (data._size.x/2), data._center.y + (data._size.y / 2)
			};
			m_vertices = vertices;
			VAO::buffer_layout layout;
			layout._type = VAO::buffer_layout_type::TYPE_FLOAT;
			layout._vertex_components = 2;

			m_VAO = new VAO(VBO(vertices, 8, 2), layout);
		
			m_IBO = new IBO(ind, 6);
		}

		Spirite2D::~Spirite2D()
		{
		}

		void Spirite2D::Draw()
		{
			m_VAO->Bind();
			m_IBO->Bind();
			m_Shader->Uniform4f("m_Color", m_Data._color.x, m_Data._color.y, m_Data._color.z, m_Data._color.w);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);
			m_IBO->UnBind();
			m_VAO->unBind();
		}
	}
}