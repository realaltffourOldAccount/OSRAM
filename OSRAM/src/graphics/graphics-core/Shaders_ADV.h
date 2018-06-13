#pragma once

#include <gl\glew.h>
#include <gl\gl.h>

#include "Window.h"

#include "..\..\utils\fileutils.h"

#include <vector>

namespace OSRAM
{
	namespace GRAPHICS
	{
		class Shaders_ADV
		{
		private:
			struct ProgDATA
			{
				std::string _name;

				GLuint _program;
				GLuint _vertexShaders;
				GLuint _fragmentShader;
				
				std::string _vsSource;
				std::string _fsSource;
			};

			std::vector<ProgDATA> m_Progs;

		public:
			Shaders_ADV();
			~Shaders_ADV();

			void AddProgram(std::string name, std::string VSpath, std::string FSpath);
			void Remove(std::string name);
			void BindProgram(std::string name);

		};
	}
}