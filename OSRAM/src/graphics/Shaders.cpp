#include "Shaders.h"
	
OSRAM::GRAPHICS::Shaders::Shaders()
{
	using namespace OSRAM::UTILS;


	// Basic GLSL Program Setup
	m_basicVS_Source = read_file("src\\shaders\\basic_vs.glsl");
	m_basicFS_Source = read_file("src\\shaders\\basic_fs.glsl");

	m_basicVS = glCreateShader(GL_VERTEX_SHADER);
	m_basicFS = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vsrc = m_basicVS_Source.c_str();
	const char* fsrc = m_basicFS_Source.c_str();

	glShaderSource(m_basicVS, 1, &vsrc, 0);
	glShaderSource(m_basicFS, 1, &fsrc, 0);

	glCompileShader(m_basicVS);
	GLint vertex_compiled;
	glGetShaderiv(m_basicVS, GL_COMPILE_STATUS, &vertex_compiled);
	if (vertex_compiled != GL_TRUE)
	{
		GLsizei log_lenght = 0;
		GLchar message[1024];
		glGetShaderInfoLog(m_basicVS, 1024, &log_lenght, message);

		std::cout << "[SHADER:VS] Could Not Compile, Error Message: \n" << message << std::endl;
		//return;
	}
	else
	{
		std::cout << "[SHADER:VS] Successfully Created Shader . . . " << std::endl;
	}
	glCompileShader(m_basicFS);
	GLint fragment_compiled;
	glGetShaderiv(m_basicFS, GL_COMPILE_STATUS, &fragment_compiled);
	if (fragment_compiled != GL_TRUE)
	{
		GLsizei log_lenght = 0;
		GLchar message[1024];
		glGetShaderInfoLog(m_basicFS, 1024, &log_lenght, message);

		std::cout << "[SHADER:FS] Could Not Compile, Error Message: \n" << message << std::endl;
		return;
	}
	else
	{
		std::cout << "[SHADER:FS] Successfully Created Shader . . . " << std::endl;
	}

	m_BasicProgram = glCreateProgram();
	glAttachShader(m_BasicProgram, m_basicVS);
	glAttachShader(m_BasicProgram, m_basicFS);
	glLinkProgram(m_BasicProgram);
	GLint linked;
	glGetProgramiv(m_BasicProgram, GL_LINK_STATUS, &linked);
	if (linked != GL_FALSE)
	{
		// ok
		std::cout << "[SHADERS:LINK] Successfully Linked . . . ." << std::endl;
	}
	else
	{
		GLint maxLength = 0;
		glGetProgramiv(m_BasicProgram, GL_INFO_LOG_LENGTH, &maxLength);

		GLchar message[1024];
		glGetProgramInfoLog(m_BasicProgram, maxLength, &maxLength, &message[0]);

		// We don't need the program anymore.
		glDeleteProgram(m_BasicProgram);
		// Don't leak shaders either.
		glDeleteShader(m_basicVS);
		glDeleteShader(m_basicFS);

		std::cout << "[SHADER:LINK] Failed to Link Program : " << message << std::endl;
	}

	// Texture GLSL Program
	m_texFS_Source = read_file("src//shaders//tex_fs.glsl");
	m_texVS_Source = read_file("src//shaders//tex_vs.glsl");

	vsrc = m_texVS_Source.c_str();
	fsrc = m_texFS_Source.c_str();

	m_texFS = glCreateShader(GL_FRAGMENT_SHADER);
	m_texVS = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(m_texFS, 1, &fsrc, 0);
	glShaderSource(m_texVS, 1, &vsrc, 0);

	glCompileShader(m_texFS);
	GLint tex_vertex_compiled;
	glGetShaderiv(m_texFS, GL_COMPILE_STATUS, &vertex_compiled);
	if (tex_vertex_compiled != GL_TRUE)
	{
		GLsizei log_lenght = 0;
		GLchar message[1024];
		glGetShaderInfoLog(m_texVS, 1024, &log_lenght, message);

		std::cout << "[SHADER:VS] Could Not Compile, Error Message: \n" << message << std::endl;
		//return;
	}
	else
	{
		std::cout << "[SHADER:VS] Successfully Created Shader . . . " << std::endl;
	}

	glCompileShader(m_texVS);
	GLint tex_frag_compiled;
	glGetShaderiv(m_texFS, GL_COMPILE_STATUS, &tex_frag_compiled);
	if (tex_frag_compiled != GL_TRUE)
	{
		GLsizei log_lenght = 0;
		GLchar message[1024];
		glGetShaderInfoLog(m_texVS, 1024, &log_lenght, message);

		std::cout << "[SHADER:VS] Could Not Compile, Error Message: \n" << message << std::endl;
		//return;
	}
	else
	{
		std::cout << "[SHADER:VS] Successfully Created Shader . . . " << std::endl;
	}

	m_BasicProgram = glCreateProgram();
	glAttachShader(m_BasicProgram, m_basicVS);
	glAttachShader(m_BasicProgram, m_basicFS);
	glLinkProgram(m_BasicProgram);
	GLint linked;
	glGetProgramiv(m_BasicProgram, GL_LINK_STATUS, &linked);
	if (linked != GL_FALSE)
	{
		// ok
		std::cout << "[SHADERS:LINK] Successfully Linked . . . ." << std::endl;
	}
	else
	{
		GLint maxLength = 0;
		glGetProgramiv(m_BasicProgram, GL_INFO_LOG_LENGTH, &maxLength);

		GLchar message[1024];
		glGetProgramInfoLog(m_BasicProgram, maxLength, &maxLength, &message[0]);

		// We don't need the program anymore.
		glDeleteProgram(m_BasicProgram);
		// Don't leak shaders either.
		glDeleteShader(m_basicVS);
		glDeleteShader(m_basicFS);

		std::cout << "[SHADER:LINK] Failed to Link Program : " << message << std::endl;
	}

}

OSRAM::GRAPHICS::Shaders::~Shaders()
{
	glDeleteProgram(m_BasicProgram);
	glDeleteShader(m_basicVS);
	glDeleteShader(m_basicFS);
}


void OSRAM::GRAPHICS::Shaders::UseBasicProgram()
{
	glUseProgram(m_BasicProgram);
}

void OSRAM::GRAPHICS::Shaders::UseTextureProgram()
{
	glUseProgram(m_TextureProgram);
}

void OSRAM::GRAPHICS::Shaders::Uniform1f(const char* str, float val)
{
	int location = glGetUniformLocation(m_BasicProgram, str);
	glUniform1f(location, val);
}

void OSRAM::GRAPHICS::Shaders::Uniform1i(const char* str, int val)
{
	int location = glGetUniformLocation(m_BasicProgram, str);
	glUniform1i(location, val);
}

void OSRAM::GRAPHICS::Shaders::Uniform2f(const char* str, float val1, float val2)
{
	int location = glGetUniformLocation(m_BasicProgram, str);
	glUniform2f(location, val1, val2);
}

void OSRAM::GRAPHICS::Shaders::Uniform2i(const char* str, int val1, int val2)
{
	int location = glGetUniformLocation(m_BasicProgram, str);
	glUniform2i(location, val1, val2);
}

void OSRAM::GRAPHICS::Shaders::Uniform3f(const char* str, float val1, float val2, float val3)
{
	int location = glGetUniformLocation(m_BasicProgram, str);
	glUniform3f(location, val1, val2, val3);
}

void OSRAM::GRAPHICS::Shaders::Uniform3i(const char* str, int val1, int val2, int val3)
{
	int location = glGetUniformLocation(m_BasicProgram, str);
	glUniform3i(location, val1, val2, val3);
}

void OSRAM::GRAPHICS::Shaders::Uniform4f(const char* str, float val1, float val2, float val3, float val4)
{
	int location = glGetUniformLocation(m_BasicProgram, str);
	glUniform4f(location, val1, val2, val3, val4);
}

void OSRAM::GRAPHICS::Shaders::Uniform4i(const char* str, int val1, int val2, int val3, int val4)
{
	int location = glGetUniformLocation(m_BasicProgram, str);
	glUniform4i(location, val1, val2, val3, val4);
}

void OSRAM::GRAPHICS::Shaders::UnifromMat3(const char* str, glm::mat4 val, bool transpose)
{
	int location = glGetUniformLocation(m_BasicProgram, str);
	glUniformMatrix3fv(location, 1, transpose, &val[0][0]);
}

void OSRAM::GRAPHICS::Shaders::UnifromMat4(const char* str, glm::mat4 val, bool transpose)
{
	int location = glGetUniformLocation(m_BasicProgram, str);
	glUniformMatrix4fv(location, 1, transpose, &val[0][0]);
}