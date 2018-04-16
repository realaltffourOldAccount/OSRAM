#include "Shaders.h"
	
OSRAM::GRAPHICS::Shaders::Shaders()
{
	using namespace OSRAM::UTILS;
	m_VS_Source = read_file("src\\shaders\\basic_vs.glsl");
	m_FS_Source = read_file("src\\shaders\\basic_fs.glsl");


	m_VS = glCreateShader(GL_VERTEX_SHADER);
	m_FS = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vsrc = m_VS_Source.c_str();
	const char* fsrc = m_FS_Source.c_str();

	glShaderSource(m_VS, 1, &vsrc, 0);
	glShaderSource(m_FS, 1, &fsrc, 0);

	glCompileShader(m_VS);


	GLint vertex_compiled;
	glGetShaderiv(m_VS, GL_COMPILE_STATUS, &vertex_compiled);
	if (vertex_compiled != GL_TRUE)
	{
		GLsizei log_lenght = 0;
		GLchar message[1024];
		glGetShaderInfoLog(m_VS, 1024, &log_lenght, message);

		std::cout << "[SHADER:VS] Could Not Compile, Error Message: " << message << std::endl;
		return;
	}
	else
	{
		std::cout << "[SHADER:VS] Successfully Created Shader . . . " << std::endl;
	}
	glCompileShader(m_FS);
	glGetShaderiv(m_FS, GL_COMPILE_STATUS, &vertex_compiled);
	if (vertex_compiled != GL_TRUE)
	{
		GLsizei log_lenght = 0;
		GLchar message[1024];
		glGetShaderInfoLog(m_FS, 1024, &log_lenght, message);

		std::cout << "[SHADER:FS] Could Not Compile, Error Message: " << message << std::endl;
		return;
	}
	else
	{
		std::cout << "[SHADER:FS] Successfully Created Shader . . . " << std::endl;
	}

	m_Program = glCreateProgram();
	glAttachShader(m_Program, m_VS);
	glAttachShader(m_Program, m_FS);
	glLinkProgram(m_Program);
	GLint linked;
	glGetProgramiv(m_Program, GL_LINK_STATUS, &linked);
	if (linked != GL_FALSE)
	{
		// ok
		std::cout << "[SHADERS:LINK] Successfully Linked . . . ." << std::endl;
	}
	else
	{
		GLint maxLength = 0;
		glGetProgramiv(m_Program, GL_INFO_LOG_LENGTH, &maxLength);

		GLchar message[1024];
		glGetProgramInfoLog(m_Program, maxLength, &maxLength, &message[0]);

		// We don't need the program anymore.
		glDeleteProgram(m_Program);
		// Don't leak shaders either.
		glDeleteShader(m_VS);
		glDeleteShader(m_FS);

		std::cout << "[SHADER:LINK] Failed to Link Program : " << message << std::endl;
	}
}

OSRAM::GRAPHICS::Shaders::~Shaders()
{
	glDeleteProgram(m_Program);
	glDeleteShader(m_VS);
	glDeleteShader(m_FS);
}


void OSRAM::GRAPHICS::Shaders::UseProgram()
{
	glUseProgram(m_Program);
}

void OSRAM::GRAPHICS::Shaders::Uniform1f(const char* str, float val)
{
	int location = glGetUniformLocation(m_Program, str);
	glUniform1f(location, val);
}

void OSRAM::GRAPHICS::Shaders::Uniform1i(const char* str, int val)
{
	int location = glGetUniformLocation(m_Program, str);
	glUniform1i(location, val);
}

void OSRAM::GRAPHICS::Shaders::Uniform2f(const char* str, float val1, float val2)
{
	int location = glGetUniformLocation(m_Program, str);
	glUniform2f(location, val1, val2);
}

void OSRAM::GRAPHICS::Shaders::Uniform2i(const char* str, int val1, float val2)
{
	int location = glGetUniformLocation(m_Program, str);
	glUniform2i(location, val1, val2);
}

void OSRAM::GRAPHICS::Shaders::Uniform3f(const char* str, float val1, float val2, float val3)
{
	int location = glGetUniformLocation(m_Program, str);
	glUniform3f(location, val1, val2, val3);
}

void OSRAM::GRAPHICS::Shaders::Uniform3i(const char* str, int val1, float val2, float val3)
{
	int location = glGetUniformLocation(m_Program, str);
	glUniform3i(location, val1, val2, val3);
}

void OSRAM::GRAPHICS::Shaders::UnifromMat3(const char* str, glm::mat4 val, bool transpose)
{
	int location = glGetUniformLocation(m_Program, str);
	glUniformMatrix3fv(location, 1, transpose, &val[0][0]);
}

void OSRAM::GRAPHICS::Shaders::UnifromMat4(const char* str, glm::mat4 val, bool transpose)
{
	int location = glGetUniformLocation(m_Program, str);
	glUniformMatrix4fv(location, 1, transpose, &val[0][0]);
}