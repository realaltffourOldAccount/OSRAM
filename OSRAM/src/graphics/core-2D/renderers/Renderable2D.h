#pragma once
#include <GLM\glm.hpp>
#include "..\..\graphics-core\Window.h"

namespace OSRAM {
	namespace GRAPHICS {
		namespace RENDERERS {
			class Renderable2D
			{
			public:
				// FOR BASIC SPRITE2D
				struct DATA
				{
					glm::vec2 _center;
					glm::vec2 _size;
					glm::vec4 _color[4];
				};

				// Sprite2DTex
				struct DATA_Tex
				{
					glm::vec2 _center;
					glm::vec2 _size;
					glm::vec4 _color[4];
					glm::vec2 _texCord[4];
					std::string _texturePATH;
					bool _mixWithColor;
				};
				void SetSpeedPosX(float speed) { m_AccSpeedPosX = speed; };
				void SetSpeedPosY(float speed) { m_AccSpeedPosY = speed; };
				void SetSpeedNegX(float speed) { m_AccSpeedNegX = speed; };
				void SetSpeedNegY(float speed) { m_AccSpeedNegY = speed; };

				void SetChangerSpeedPosX(float speed) { m_AccSpeedChangerPosX = speed; };
				void SetChangerSpeedPosY(float speed) { m_AccSpeedChangerPosY = speed; };
				void SetChangerSpeedNegX(float speed) { m_AccSpeedChangerNegX = speed; };
				void SetChangerSpeedNegY(float speed) { m_AccSpeedChangerNegY = speed; };

				void ResetSpeedPosX() { m_AccSpeedPosX = 0.0f; }
				void ResetSpeedPosY() { m_AccSpeedPosY = 0.0f; }
				void ResetSpeedNegX() { m_AccSpeedNegX = 0.0f; }
				void ResetSpeedNegY() { m_AccSpeedNegY = 0.0f; }

				void moveXAccelerated()
				{
					m_AccSpeedPosX += m_AccSpeedChangerPosX;
					m_Acc_x += m_AccSpeedPosX;
					m_Model = glm::translate(glm::mat4(1.0f), glm::vec3(m_Acc_x, m_Acc_y, 0.0f));
				};
				void moveX()
				{
					m_Acc_x += m_AccSpeedPosX;
					m_Model = glm::translate(glm::mat4(1.0f), glm::vec3(m_Acc_x, m_Acc_y, 0.0f));
				};

				void moveYAccelerated()
				{
					m_AccSpeedPosY += m_AccSpeedChangerPosY;
					m_Acc_y += m_AccSpeedPosY;
					m_Model = glm::translate(glm::mat4(1.0f), glm::vec3(m_Acc_x, m_Acc_y, 0.0f));
				};
				void moveY()
				{
					m_Acc_y += m_AccSpeedPosY;
					m_Model = glm::translate(glm::mat4(1.0f), glm::vec3(m_Acc_x, m_Acc_y, 0.0f));
				};

				void moveNegXAccelerated()
				{
					m_AccSpeedNegX -= m_AccSpeedChangerNegX;
					m_Acc_x -= m_AccSpeedNegX;
					m_Model = glm::translate(glm::mat4(1.0f), glm::vec3(m_Acc_x, m_Acc_y, 0.0f));
				};
				void moveNegX()
				{
					m_Acc_x += m_AccSpeedNegX;
					m_Model = glm::translate(glm::mat4(1.0f), glm::vec3(m_Acc_x, m_Acc_y, 0.0f));
				};
				void moveNegYAccelerated()
				{
					m_AccSpeedNegY += m_AccSpeedChangerNegY;
					m_Acc_y += m_AccSpeedNegY;
					m_Model = glm::translate(glm::mat4(1.0f), glm::vec3(m_Acc_x, m_Acc_y, 0.0f));
				};
				void moveNegY()
				{
					m_Acc_y += m_AccSpeedNegY;
					m_Model = glm::translate(glm::mat4(1.0f), glm::vec3(m_Acc_x, m_Acc_y, 0.0f));
				};

				glm::mat4 GetModelMatrix() { return m_Model; };

				float* GetVertices() { return m_Vertices; };
				float* GetColors() { return m_Colors; }
				float* GetTexCord() { return m_TexCoord; }
				//float* GetBuffer() { return m_Buffer; }

				virtual void LegacyDraw() = 0;
			protected:
				//float *m_Buffer;
				float m_AccSpeedPosX = 0.000f;
				float m_AccSpeedPosY = -0.000f;
				float m_AccSpeedNegX = 0.000f;
				float m_AccSpeedNegY = -0.000f;

				float m_AccSpeedChangerPosX = 0.0f;
				float m_AccSpeedChangerNegX = 0.0f;
				float m_AccSpeedChangerPosY = 0.0f;
				float m_AccSpeedChangerNegY = 0.0f;

				float m_Acc_x = 0.0f, m_Acc_y = 0.0f;

				glm::mat4 m_Model = glm::mat4(1.0f);

				float m_Vertices[4 * 2];
				float m_Colors[4 * 4];
				float m_TexCoord[4 * 2];
			};
		}
	}
}