#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <GLM\glm.hpp>

#include "Renderable2D.h"
#include "..\MVP.h"

namespace OSRAM
{
	namespace GRAPHICS
	{
		namespace RENDERERS
		{
			class VectorRenderer2D
			{
			private:
				struct OBJ
				{
					Renderable2D *_obj;		
					std::string _name;		
				};

				std::vector<OBJ> m_Objects;

				glm::mat4 m_Projection = glm::mat4(1.0f);
				glm::mat4 m_View = glm::mat4(1.0f);

				MVP *m_MVP;
			public:
				VectorRenderer2D(MVP *mvp);
				~VectorRenderer2D();

				void flush();
				void add(Renderable2D *obj, std::string name);
				void remove(std::string name);
				void clear();

				void setProjection(glm::mat4 proj);
				void setView(glm::mat4 view);
			};
		}
	}
}