#pragma once
#include <GL\glew.h>
#include "Renderers\Renderable2D.h"
#include "..\graphics-core\Window.h"

namespace OSRAM {
	namespace GRAPHICS {
		class Sprite2DTex : public RENDERERS::Renderable2D
		{
		private:
			GLuint m_TextureID;
			GLuint m_DataBuff;
			GLuint m_IndicesBuff;
			GLuint m_VertexArray;

			GLubyte ind[6] = { 0, 1, 3, 1, 2, 3 };

			DATA_Tex _TexSpec;

			void init();

			// Texture Info
			int t_Width;
			int t_Hieght;
			int t_nrChannels;
			unsigned char *t_data;

			Window* win;
		public:
			Sprite2DTex(DATA_Tex data, Window *win);
			~Sprite2DTex();

			virtual void LegacyDraw() override;
		};
	}
}