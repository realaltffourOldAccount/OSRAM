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
			virtual void flush() = 0;
		};
	}
}