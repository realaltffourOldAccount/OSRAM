#pragma once
#include "Render2D.h"
#include "Renderable2D.h"

namespace OSRAM {
	namespace GRAPHICS {
		class BasicRenderer2D : Render2D
		{
		public:
			virtual void submit(Renderable2D* obj) override;
			virtual void flush() override;
		};
	}
}