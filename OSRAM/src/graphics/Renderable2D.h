#pragma once
#include <GLM/glm.hpp>


namespace OSRAM {
	namespace GRAPHICS {
		class Renderable2D
		{
		public:
			struct DATA
			{
				glm::vec2 _center;
				glm::vec2 _size;
				glm::vec4 _color[4];
			};

			void accelerateX(bool enabled)
			{
				if (enabled)
					m_Acc_x += m_AccSpeed;
				else m_Acc_x -= m_AccSpeed;

				m_Model = glm::translate(glm::mat4(1.0f), glm::vec3(m_Acc_x, m_Acc_y,0.0f));
			};
			void accelerateY(bool enabled) 
			{
				if (enabled)
					m_Acc_y += m_AccSpeed;
				else m_Acc_y -= m_AccSpeed;

				m_Model = glm::translate(glm::mat4(1.0f), glm::vec3(m_Acc_x, m_Acc_y, 0.0f));
			};
			void accelerateNegX(bool enabled)
			{
				if (enabled)
					m_Acc_x -= m_AccSpeed;
				else m_Acc_x += m_AccSpeed;

				m_Model = glm::translate(glm::mat4(1.0f), glm::vec3(m_Acc_x, m_Acc_y, 0.0f));
			};
			void accelerateNegY(bool enabled)
			{
				if (enabled)
					m_Acc_y -= m_AccSpeed;
				else m_Acc_y += m_AccSpeed;

				m_Model = glm::translate(glm::mat4(1.0f), glm::vec3(m_Acc_x, m_Acc_y, 0.0f));
			};

			glm::mat4 GetModelMatrix() { return m_Model; };

			glm::vec2* GetVertices() { return m_Vertices; };


		protected:
			float m_Buffer[6 * 4];
			float m_AccSpeed = 0.01f;
			float m_Acc_x = 0.0f, m_Acc_y = 0.0f;
			bool m_Acc_True;

			glm::mat4 m_Model = glm::mat4(1.0f);

			glm::vec2 m_Vertices[4];
		};
	}
}