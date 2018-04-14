#include "Window.h"


OSRAM::GRAPHICS::Window::Window(int width, int height, std::string title)
	:m_Width(width), m_Height(height), m_Title(title), m_Window(NULL)
	, INSTANCE(this)
{
	init();
}

OSRAM::GRAPHICS::Window::~Window()
{
	glfwTerminate();
}


void OSRAM::GRAPHICS::Window::init()
{
	if (!glfwInit())
		std::cout << "[WINDOW] GLFW Init UnSuccessfull . . ." << std::endl;
	else std::cout << "[WINDOW] GLFW Init Successfull . . . " << std::endl;

	m_Window = glfwCreateWindow(m_Height,
								m_Width,
								m_Title.c_str(),
								NULL,NULL);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwMakeContextCurrent(m_Window);
	if (glewInit() != GLEW_OK)
		std::cout << "[WINDOW] GLEW Init UnSuccessfull . . . " << std::endl;
	else std::cout << "[WINDOW] GLEW Init Successfull . . ." << std::endl;

	glViewport(0, 0, m_Width, m_Height);
	glfwSwapInterval(0);
	glfwShowWindow(m_Window);
}

void OSRAM::GRAPHICS::Window::Update() 
{
	glfwPollEvents();
	glfwSwapBuffers(m_Window);
}