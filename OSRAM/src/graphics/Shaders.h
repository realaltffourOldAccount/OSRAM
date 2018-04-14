#pragma once
#include "..\utils\fileutils.h"
#include <GL\glew.h>
#include <GLM\glm.hpp>

namespace OSRAM
{
	namespace GRAPHICS
	{
		class Shaders
		{
		private:
			unsigned int m_Program;
			unsigned int m_VS, m_FS;
			std::string m_VS_Source;
			std::string m_FS_Source;
		public:
			Shaders();
			~Shaders();
			void UseProgram();
		};
	}

}