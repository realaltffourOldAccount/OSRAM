#pragma once
#include <vector>

#include "..\graphics-core\Window.h"
#include "..\graphics-core\MVP.h"
#include "..\core-2D\renderers\Renderable2D.h"

#include "..\core-2D\renderers\Render2D.h"

namespace OSRAM {
	namespace GRAPHICS {
		namespace LAYERS {
			class Layer2D
			{
			private:
				bool m_Format;
				
				glm::mat4 m_Projection;
				glm::mat4 m_View;

				std::vector<RENDERERS::Renderable2D> m_Objects;
				RENDERERS::Render2D *m_Render2D;
			public:
				Layer2D(RENDERERS::Render2D *renderer);
				~Layer2D();

				void SetProjection(glm::mat4 proj);
				void SetView(glm::mat4 view);

				void Render();
			};
		}
	}
}