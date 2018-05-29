#pragma once
#include "Sprite2D.h"

namespace OSRAM {
	namespace GRAPHICS {
#define BASIC_RENDER2D_SPRITE_ARRAY 1000
		class Render2D
		{
		protected:
			// For Basic Renderer
			Renderable2D* m_ObjArray[BASIC_RENDER2D_SPRITE_ARRAY];
			int m_Counter = 0;
			// End Of Basic Renderer
		public:
			virtual void submit(Renderable2D* obj) = 0;
			virtual void flush(glm::mat4 proj, glm::mat4 view, glm::mat4 model = glm::mat4(1.0f)) = 0;
		};
	}
}