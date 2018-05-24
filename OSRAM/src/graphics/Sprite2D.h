#pragma once
#include "buffer/VAO.h"
#include "buffer/IBO.h"
#include "Shaders.h"
#include "Window.h"
#include "Renderable2D.h"

#include <GLM/glm.hpp>
#include <iostream>

using namespace OSRAM::GRAPHICS::BUFFER;
namespace OSRAM {
	namespace GRAPHICS {
		class Sprite2D : public Renderable2D
		{
		public:
			Sprite2D(DATA data, Shaders *shader);
			~Sprite2D();
			
			void LegacyDraw() override;
			float* BufferValue() { return m_Buffer; };
		private:
			VAO *m_VAO;
			IBO *m_IBO;
			DATA m_Data;
			Shaders *m_Shader;
			
			GLubyte ind[6] = { 0,1,2, 3,1,2 };
		};
	}
}