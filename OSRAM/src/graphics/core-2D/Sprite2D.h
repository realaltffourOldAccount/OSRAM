#pragma once
#include "..\graphics-core\buffer\VAO.h"
#include "..\graphics-core\buffer\IBO.h"
#include "..\graphics-core\Window.h"
#include "..\graphics-core\Shaders.h"
#include "..\core-2D\Renderers\Renderable2D.h"

#include <GLM/glm.hpp>
#include <iostream>

using namespace OSRAM::GRAPHICS::BUFFER;
namespace OSRAM {
	namespace GRAPHICS {
		class Sprite2D : public RENDERERS::Renderable2D
		{
		public:
			Sprite2D(DATA data, Shaders *shader);
			~Sprite2D();
			
			void LegacyDraw() override;
		//	float* BufferValue() { return m_Buffer; };
		private:
			VAO *m_VAO;
			IBO *m_IBO;
			DATA m_Data;
			Shaders *m_Shader;
			
			GLubyte ind[6] = { 0,1,2, 2, 1, 3 };
		};
	}
}