#pragma once

#include <GL\glew.h>
#include <GLM\glm.hpp>
#include <GLM\mat4x4.hpp>
#include <GLM\gtc\matrix_transform.hpp>

#include "Window.h"

namespace OSRAM {
	namespace GRAPHICS {
		class MVP /// MUST BE CREATED ONCE EVERY SHADER CLASS INSTANCE, passed by pionter
		{
		public:
			MVP();
			~MVP();

		private:

		};

	}
}
