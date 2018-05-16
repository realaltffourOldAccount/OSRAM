#include "Spirite2D.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../utils/stbi_image.h"

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

			if (data._texturefile != " ")
			{
				m_TexData = stbi_load(data._texturefile.c_str(), &m_TEXwidth, &m_TEXheight, &m_TEXChannels, 0);

				if (m_TexData)
				{
					std::cout << "[TEXTURE] Loaded Successfully . . . " << data._texturefile << std::endl;
					glGenTextures(1, &m_Texture);
					glBindTexture(GL_TEXTURE_2D, m_Texture);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_TEXwidth, m_TEXheight, 0, GL_RGB, GL_UNSIGNED_BYTE, m_TexData);
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, 0);
					stbi_image_free(m_TexData);
					Window::CheckError();
				}
				else
				{
					std::cout << "[TEXTURE] Could Not Load . . . " << data._texturefile << std::endl;
				}
			
			}
		}

		Spirite2D::~Spirite2D()
		{
		}

		void Spirite2D::LegacyDraw()
		{
			m_VAO->Bind();
			m_IBO->Bind();
			//if (m_Data._texturefile != "")
			//{
			//	glBindTexture(GL_TEXTURE_2D, m_Texture);
			//	glActiveTexture(GL_TEXTURE0);
			//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
			//	glEnableVertexAttribArray(2);
			//}
			m_Shader->Uniform4f("m_Color", m_Data._color.x, m_Data._color.y, m_Data._color.z, m_Data._color.w);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);
			m_IBO->UnBind();
			m_VAO->unBind();
		}
	}
}