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

			void Uniform1f(std::string str, float val);
			void Uniform1i(std::string str, int val);
			void Uniform2f(std::string str, float val1, float val2);
			void Uniform2i(std::string str, int val1, float val2);
			void Uniform3f(std::string str, float val1, float val2, float val3);
			void Uniform3i(std::string str, int val1, float val2, float val3);
			void UnifromMat4(std::string str, glm::mat4 val);
			void UnifromMat3(std::string str, glm::mat4 val);

		};
	}

}