#pragma once
#include "..\graphics\graphics-core\Window.h"

namespace OSRAM
{
	namespace INPUT
	{
		class Input
		{
		public:
			bool m_keys[1024]; // 1 kb
			bool m_MOUSE_Buttons[3];
			bool m_MouseEnter;
			double mouse_X;
			double mouse_Y;

			bool inited = false;
		public:
			Input(OSRAM::GRAPHICS::Window* window, int cursor_mode);
			~Input();

			bool isKeyPressed(int key) { return m_keys[key]; }
			bool isKeyReleased(int key) { return !m_keys[key]; }

			bool isMouseButtonPressed(int button) { return m_MOUSE_Buttons[button]; }
			bool isMouseButtonReleased(int button) { return !m_MOUSE_Buttons[button]; }

			double getMouseXPos() { return mouse_X; }
			double getMouseYPos() { return mouse_Y; }

			bool isMouseEntered() { return m_MouseEnter; }
			bool isMouseReleased() { return !m_MouseEnter; }

			bool isInited() { return inited; }
		private:
			static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
			static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
			static void cursor_enter_callback(GLFWwindow* window, int entered);
		};
	}
}