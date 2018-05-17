#pragma once
#include <GL\glew.h>
#include <iostream>
#include <string>

#include "GLM\glm.hpp"

#include "Shaders.h"
#include "buffer/VAO.h"
#include "buffer/IBO.h"

using namespace OSRAM::GRAPHICS::BUFFER;
namespace OSRAM
{
	namespace GRAPHICS
	{
		class Sprite2DTex
		{
		public:
			struct DATA
			{
				glm::vec2 _center;
				glm::vec2 _size;
				glm::vec4 _color_adj;
				std::string _texture_file = " ";
			};

			Sprite2DTex(DATA data, Shaders* shaders);
			~Sprite2DTex();

			void LegacyDraw();
		private:
			VAO *m_VAO;
			IBO *m_IBO;
			DATA m_Data;
			Shaders *m_Shader;

			GLubyte ind[6] = { 0,1,2, 3,1,2 };
			float *m_vertices;

			GLuint m_Texture;
			int m_TexWidth;
			int m_TexHieght;
			int m_nrChannels;
			unsigned char* m_TexData;
			
			void BindTexture();
			void unBindTexture();

		};
	}
}