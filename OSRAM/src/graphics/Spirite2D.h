#pragma once
#include "buffer/VAO.h"
#include "buffer/IBO.h"
#include "Shaders.h"
#include "Window.h"

#include <GLM/glm.hpp>
#include <iostream>

using namespace OSRAM::GRAPHICS::BUFFER;
namespace OSRAM {
	namespace GRAPHICS {
		class Spirite2D
		{
		public:
			struct DATA 
			{
				glm::vec2 _center;
				glm::vec2 _size;
				glm::vec4 _color;
				std::string _texturefile = " ";
			};
			Spirite2D(DATA data, Shaders *shader);
			~Spirite2D();
			
			void LegacyDraw();
		private:
			VAO *m_VAO;
			IBO *m_IBO;
			DATA m_Data;
			Shaders *m_Shader;
			unsigned int m_Texture;
			unsigned char* m_TexData;

			int m_TEXwidth;
			int m_TEXheight;
			int m_TEXChannels;

			GLubyte ind[6] = { 0,1,2, 3,1,2 };
			float texCoords[6] = {
				0.0f, 0.0f,  // lower-left corner  
				1.0f, 0.0f,  // lower-right corner
				0.5f, 1.0f   // top-center corner
			};
			float *m_vertices;
		};
	}
}
