#include "Window.h"


OSRAM::GRAPHICS::Window::Window(int width, int height, std::string title)
	:m_Width(width), m_Height(height), m_Title(title), m_Window(NULL)
	, INSTANCE(this)
{
	init();
}

OSRAM::GRAPHICS::Window::~Window()
{
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
}



void OSRAM::GRAPHICS::Window::init()
{
	if (!glfwInit())
		std::cout << "[WINDOW] GLFW Init . . . FAIL" << std::endl;
	else std::cout << "[WINDOW] GLFW Init . . . SUCCESS" << std::endl;

	m_Window = glfwCreateWindow(m_Height,
								m_Width,
								m_Title.c_str(),
								NULL,NULL);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwMakeContextCurrent(m_Window);
	if (glewInit() != GLEW_OK)
		std::cout << "[WINDOW] GLEW Init . . . FAIL" << std::endl;
	else std::cout << "[WINDOW] GLEW Init . . .SUCCESS" << std::endl;

	glViewport(0, 0, m_Width, m_Height);
	glfwSwapInterval(1);
	glfwShowWindow(m_Window);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(m_Window, true);
	ImGui::StyleColorsDark();

}

void OSRAM::GRAPHICS::Window::Update() 
{
	glfwPollEvents();
	glfwSwapBuffers(m_Window);
	glClear(GL_COLOR_BUFFER_BIT);
	///this->CheckError();
	ImGui_ImplGlfwGL3_NewFrame();
}

void OSRAM::GRAPHICS::Window::RenderImGUI()
{
	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}

void OSRAM::GRAPHICS::Window::CheckError()
{
	// check OpenGL error
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cerr << "OpenGL error: " << err << std::endl;
	}
}