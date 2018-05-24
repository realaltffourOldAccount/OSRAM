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

			void EnableProgressiveAcc(bool state, float changer) { m_Acc_True = state; m_AccSpeedChanger = changer; };
			void SetAccelerationSpeedPos(float speed) { m_AccSpeedPos = speed; };
			void SetAccelerationSpeedNeg(float speed) { m_AccSpeedNeg = speed; };
			void ResetSpeedPos() { m_AccSpeedPos = 0.0f; }
			void ResetSpeedNeg() { m_AccSpeedNeg = 0.0f; }

			void accelerateX(bool enabled)
			{
				if (enabled)
				{
					if (m_Acc_True)
						m_AccSpeedPos += m_AccSpeedChanger;
					m_Acc_x += m_AccSpeedPos;
				}
				else {
					if (m_Acc_True)
						m_AccSpeedNeg -= m_AccSpeedChanger;
					m_Acc_x -= m_AccSpeedNeg;
				}
				m_Model = glm::translate(glm::mat4(1.0f), glm::vec3(m_Acc_x, m_Acc_y, 0.0f));
			};
			void accelerateY(bool enabled) 
			{
				if (enabled)
				{
					if (m_Acc_True)
						m_AccSpeedPos += m_AccSpeedChanger;
					m_Acc_y += m_AccSpeedPos;
				}
				else {
					if (m_Acc_True)
						m_AccSpeedNeg -= m_AccSpeedChanger;
					m_Acc_y -= m_AccSpeedNeg;
				}
				m_Model = glm::translate(glm::mat4(1.0f), glm::vec3(m_Acc_x, m_Acc_y, 0.0f));
			};
			void accelerateNegX(bool enabled)
			{
				if (enabled)
				{
					if (m_Acc_True)
						m_AccSpeedNeg -= m_AccSpeedChanger;
					m_Acc_x += m_AccSpeedNeg;
				}
				else {
					if (m_Acc_True)
						m_AccSpeedPos += m_AccSpeedChanger;
					m_Acc_x -= m_AccSpeedPos;
				}
				m_Model = glm::translate(glm::mat4(1.0f), glm::vec3(m_Acc_x, m_Acc_y, 0.0f));
			};
			void accelerateNegY(bool enabled)
			{
				if (enabled)
				{
					if (m_Acc_True)
						m_AccSpeedNeg -= m_AccSpeedChanger;
					m_Acc_y += m_AccSpeedNeg;
				}
				else {
					if (m_Acc_True)
						m_AccSpeedPos += m_AccSpeedChanger;
					m_Acc_y -= m_AccSpeedPos;
				}
				m_Model = glm::translate(glm::mat4(1.0f), glm::vec3(m_Acc_x, m_Acc_y, 0.0f));
			};

			glm::mat4 GetModelMatrix() { return m_Model; };

			glm::vec2* GetVertices() { return m_Vertices; };

			virtual void LegacyDraw() = 0;
		protected:
			float m_Buffer[6 * 4];
			float m_AccSpeedPos = 0.000f;
			float m_AccSpeedNeg = -0.000f;
			float m_AccSpeedChanger = 0.0f;
			float m_Acc_x = 0.0f, m_Acc_y = 0.0f;
			bool m_Acc_True = false;

			glm::mat4 m_Model = glm::mat4(1.0f);

			glm::vec2 m_Vertices[4];
		};
	}
}