#pragma once

#include <GL\glew.h>
#include <GLM\glm.hpp>
#include <GLM\mat4x4.hpp>
#include <GLM\gtc\matrix_transform.hpp>

#include "Shaders.h"

namespace OSRAM {
	namespace GRAPHICS {
		class MVP /// MUST BE CREATED ONCE EVERY SHADER CLASS INSTANCE, passed by pionter
		{
		public:
			MVP(Shaders *shader);
			~MVP();

			void SetBasicModelMatrix(glm::mat4 mat);
			void SetBasicViewMatrix(glm::mat4 view);
			void SetBasicProjectionMatrix(glm::mat4 proj);

			void SetBatchModelMatrix(glm::mat4 mat);
			void SetBatchViewMatrix(glm::mat4 view);
			void SetBatchProjectionMatrix(glm::mat4 proj);

		private:
			Shaders *m_Shader;
		};
	}
}
