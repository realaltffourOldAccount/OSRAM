#pragma once
#include "..\utils\fileutils.h"
#include <GL\glew.h>
#include <GLM\glm.hpp>
#include <GLM\mat4x4.hpp>
#include <GLM\gtc\matrix_transform.hpp>

namespace OSRAM
{
	namespace GRAPHICS
	{
		class Shaders
		{
		private:
			unsigned int m_BasicProgram = 0, m_TextureProgram = 0, m_BatchProgram;
			unsigned int m_CurrentProgram;
			unsigned int m_basicVS, m_basicFS;
			unsigned int m_texVS, m_texFS;
			unsigned int m_batchVS, m_batchFS;
			std::string m_basicVS_Source;
			std::string m_basicFS_Source;
			std::string m_texVS_Source;
			std::string m_texFS_Source;
			std::string m_batchVS_Source;
			std::string m_batchFS_Source;
		public:
			Shaders();
			~Shaders();
			void UseBasicProgram();
			void UseBatchProgram();
			void UseTextureProgram();
			unsigned int GetBasicProgram() { return m_BasicProgram; }
			unsigned int GetBatchProgram() { return m_BatchProgram; }
			unsigned int GetTextureProgram() { return m_TextureProgram; }


			void Uniform1f(unsigned int program, const char*, float val);
			void Uniform1i(unsigned int program, const char*, int val);
			void Uniform2f(unsigned int program, const char*, float val1, float val2);
			void Uniform2i(unsigned int program, const char*, int val1, int val2);
			void Uniform3f(unsigned int program, const char*, float val1, float val2, float val3);
			void Uniform3i(unsigned int program, const char*, int val1, int val2, int val3);
			void Uniform4f(unsigned int program, const char*, float val1, float val2, float val3, float val4);
			void Uniform4i(unsigned int program, const char*, int val1, int val2, int val3, int val4);
			void UnifromMat4(unsigned int program,const char*, glm::mat4 val, bool transpose);
			void UnifromMat3(unsigned int program, const char*, glm::mat4 val, bool transpose);
		};
	}

}