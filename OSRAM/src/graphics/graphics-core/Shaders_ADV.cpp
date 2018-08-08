#include "Shaders_ADV.h"

OSRAM::GRAPHICS::Shaders_ADV::Shaders_ADV(Window * _win)
{
	win = _win;
}

OSRAM::GRAPHICS::Shaders_ADV::~Shaders_ADV()
{

}

void OSRAM::GRAPHICS::Shaders_ADV::AddProgram(std::string name, std::string VSpath, std::string FSpath)
{
	ProgDATA data;
	data._vsPath = VSpath;
	data._fsPath = FSpath;
	
	std::string src_vs = UTILS::read_file(VSpath);
	std::string src_fs = UTILS::read_file(FSpath);

	data._vertexShaders = glCreateShader(GL_VERTEX_SHADER);
	data._fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vsrc = src_vs.c_str();
	const char* fsrc = src_fs.c_str();

	glShaderSource(data._vertexShaders, 1, &vsrc, 0);
	glShaderSource(data._fragmentShader, 1, &fsrc, 0);

	glCompileShader(data._vertexShaders);
	GLint vertex_compiled;
	glGetShaderiv(data._vertexShaders, GL_COMPILE_STATUS, &vertex_compiled);
	if (vertex_compiled != GL_TRUE)
	{
		GLsizei log_lenght = 0;
		GLchar message[1024];
		glGetShaderInfoLog(data._vertexShaders, 1024, &log_lenght, message);

		win->getLog()->LogMSG(win->getLog()->MSG_ERROR, "[SHADER_ADV:VS:BASIC]", "Could Not Compile, Error Message: \n" + std::string(message));
		//return;
	}
	else
	{
		win->getLog()->LogMSG(win->getLog()->MSG_NORMAL, "[SHADER_ADV:VS:BASIC]", "Shader Creation . . . SUCCESS");
	}

	glCompileShader(data._fragmentShader);
	GLint fragment_compiled;
	glGetShaderiv(data._fragmentShader, GL_COMPILE_STATUS, &fragment_compiled);
	if (fragment_compiled != GL_TRUE)
	{
		GLsizei log_lenght = 0;
		GLchar message[1024];
		glGetShaderInfoLog(data._fragmentShader, 1024, &log_lenght, message);

		win->getLog()->LogMSG(win->getLog()->MSG_ERROR, "[SHADER:FS:BASIC]", "Could Not Compile, Error Message : \n" + std::string(message));
		return;
	}
	else
	{
		win->getLog()->LogMSG(win->getLog()->MSG_NORMAL, "[SHADER:FS:BASIC]", "Shader Creation . . . SUCCESS");
	}

	data._program = glCreateProgram();
	glAttachShader(data._program, data._vertexShaders);
	glAttachShader(data._program, data._fragmentShader);
	glLinkProgram(data._program);

	GLint basiclinked;
	glGetProgramiv(data._program, GL_LINK_STATUS, &basiclinked);
	if (basiclinked != GL_FALSE)
	{
		// ok
		win->getLog()->LogMSG(win->getLog()->MSG_NORMAL, "[SHADERS:LINK:BASIC]", "Link Status . . . SUCCESS");
	}
	else
	{
		GLint maxLength = 0;
		glGetProgramiv(data._program, GL_INFO_LOG_LENGTH, &maxLength);

		GLchar message[1024];
		glGetProgramInfoLog(data._program, maxLength, &maxLength, &message[0]);

		// We don't need the program anymore.
		glDeleteProgram(data._program);
		// Don't leak shaders either.
		glDeleteShader(data._vertexShaders);
		glDeleteShader(data._fragmentShader);

		win->getLog()->LogMSG(win->getLog()->MSG_ERROR, "[SHADER:LINK]", "Failed to Link Program : " + std::string(message));
	}

	m_Progs.insert(std::make_pair(name, data));
}

void OSRAM::GRAPHICS::Shaders_ADV::Remove(std::string name)
{

}

void OSRAM::GRAPHICS::Shaders_ADV::BindProgram(std::string name)
{

}