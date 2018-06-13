#pragma once
#include "Render2D.h"
#include "Renderable2D.h"
#include "..\..\graphics-core\MVP.h"

namespace OSRAM {
	namespace GRAPHICS {
		namespace RENDERERS {
			class BasicRenderer2D : Render2D
			{
			private:
				OSRAM::GRAPHICS::MVP *m_MVP;
			public:
				BasicRenderer2D(OSRAM::GRAPHICS::MVP *mvp);
				virtual void submit(Renderable2D* obj) override;
				virtual void flush(glm::mat4 proj, glm::mat4 view, glm::mat4 model = glm::mat4(1.0f));
			};
		}
	}
}