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

			void Uniform1f(const char*, float val);
			void Uniform1i(const char*, int val);
			void Uniform2f(const char*, float val1, float val2);
			void Uniform2i(const char*, int val1, int val2);
			void Uniform3f(const char*, float val1, float val2, float val3);
			void Uniform3i(const char*, int val1, int val2, int val3);
			void Uniform4f(const char*, float val1, float val2, float val3, float val4);
			void Uniform4i(const char*, int val1, int val2, int val3, int val4);
			void UnifromMat4(const char*, glm::mat4 val, bool transpose);
			void UnifromMat3(const char*, glm::mat4 val, bool transpose);

		};
	}

}