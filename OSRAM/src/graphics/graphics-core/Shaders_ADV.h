#pragma once

#include <gl\glew.h>
#include <gl\gl.h>

#include "Window.h"

#include "..\..\utils\fileutils.h"

#include <vector>
#include <map>

namespace OSRAM
{
	namespace GRAPHICS
	{
		class Shaders_ADV
		{
		private:
			struct ProgDATA
			{
				GLuint _program;
				GLuint _vertexShaders;
				GLuint _fragmentShader;
				
				std::string _vsPath;
				std::string _fsPath;
			};

			 std::map<std::string, ProgDATA> m_Progs;
			 Window *win;
		public:
			Shaders_ADV(Window *win);
			~Shaders_ADV();

			void AddProgram(std::string name, std::string VSpath, std::string FSpath);
			void Remove(std::string name);
			void BindProgram(std::string name);
		};
	}
}