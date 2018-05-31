#pragma once
#include <GL\glew.h>
#include "Renderable2D.h"
#include "..\utils\stbi_image.h"

namespace OSRAM {
	namespace GRAPHICS {
		class Sprite2DTex : Renderable2D 
		{
		private:
			GLuint m_TextureID;
			GLuint m_DataBuff;
			GLuint m_IndicesBuff;
			GLuint m_VertexArray;

			float *m_Buffer;
			GLubyte ind[6] = { 0,1,2, 2, 1, 3 };

			DATA_Tex _TexSpec;

			void init();
		public:
			Sprite2DTex(DATA_Tex data);
			~Sprite2DTex();

			virtual void LegacyDraw() override;
		};
	}
}