#pragma once
#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>

#include <iostream>

#include "..\..\utils\imGUI\imgui.h"
#include "..\..\utils\imGUI\imgui_impl_glfw_gl3.h"
#include "..\..\utils\Log.h"

namespace OSRAM {
	namespace GRAPHICS {

		class Window
		{
		private:
			
			int m_Width;
			int m_Height;
			std::string m_Title;
			
			GLFWwindow* m_Window;
			UTILS::Log *m_LOG;
		public:
			Window(int width, int height, std::string title);
			~Window();

			void Update();
			static void CheckError();

			GLFWwindow* getWindowHandler() { return m_Window; };
			int getWindowWidth() { return m_Width; };
			int getWindowHeight() { return m_Height; };

			UTILS::Log *getLog() { return m_LOG; };

			void RenderImGUI();
		private:
			void init();
		};
	}
}