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
			unsigned int m_BasicProgram, m_TextureProgram;
			unsigned int m_CurrentProgram;
			unsigned int m_basicVS, m_basicFS;
			unsigned int m_texVS, m_texFS;
			std::string m_basicVS_Source;
			std::string m_basicFS_Source;
			std::string m_texVS_Source;
			std::string m_texFS_Source;
		public:
			Shaders();
			~Shaders();
			void UseBasicProgram();
			void UseTextureProgram();
			bool GetCurrentProgram() { return m_CurrentProgram; };

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