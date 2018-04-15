#include "Input.h"

OSRAM::INPUT::Input *input;
OSRAM::INPUT::Input::Input(GLFWwindow* window, int cursor)
{
	input = this;
	for (int i = 0; i < 1024; i++)
	{
		m_keys[i] = false;
	}
	for (int i = 0; i < 3; i++)
	{
		m_MOUSE_Buttons[i] = false;
	}
	m_MouseEnter = false;

	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorEnterCallback(window, cursor_enter_callback);

	inited = true;
	glfwSetInputMode(window, GLFW_CURSOR, cursor);
	std::cout << "[INPUT] Initiated Input Class . . . " << std::endl;
}

OSRAM::INPUT::Input::~Input()
{

}

void OSRAM::INPUT::Input::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
		input->m_keys[key] = true;
	else input->m_keys[key] = false;
}

void OSRAM::INPUT::Input::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	input->mouse_X = xpos;
	input->mouse_Y = ypos;
}

void OSRAM::INPUT::Input::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
		input->m_MOUSE_Buttons[button] = true;
	else input->m_MOUSE_Buttons[button] = false;
}

void OSRAM::INPUT::Input::cursor_enter_callback(GLFWwindow* window, int entered)
{
	input->m_MouseEnter = entered;
}
