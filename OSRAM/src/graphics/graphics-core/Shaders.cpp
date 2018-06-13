#include "Shaders.h"
	
OSRAM::GRAPHICS::Shaders::Shaders(Window *win)
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

		win->getLog()->LogMSG(win->getLog()->MSG_ERROR, "[SHADER:VS:BASIC]", "Could Not Compile, Error Message: \n" + std::string(message));
		//return;
	}
	else
	{
		win->getLog()->LogMSG(win->getLog()->MSG_NORMAL, "[SHADER:VS:BASIC]", "Shader Creation . . . SUCCESS");
	}
	glCompileShader(m_basicFS);
	GLint fragment_compiled;
	glGetShaderiv(m_basicFS, GL_COMPILE_STATUS, &fragment_compiled);
	if (fragment_compiled != GL_TRUE)
	{
		GLsizei log_lenght = 0;
		GLchar message[1024];
		glGetShaderInfoLog(m_basicFS, 1024, &log_lenght, message);

		win->getLog()->LogMSG(win->getLog()->MSG_ERROR, "[SHADER:FS:BASIC]", "Could Not Compile, Error Message : \n" + std::string(message));
		return;
	}
	else
	{
		win->getLog()->LogMSG(win->getLog()->MSG_NORMAL, "[SHADER:FS:BASIC]", "Shader Creation . . . SUCCESS");
	}

	m_BasicProgram = glCreateProgram();
	glAttachShader(m_BasicProgram, m_basicVS);
	glAttachShader(m_BasicProgram, m_basicFS);
	glLinkProgram(m_BasicProgram);
	GLint basiclinked;
	glGetProgramiv(m_BasicProgram, GL_LINK_STATUS, &basiclinked);
	if (basiclinked != GL_FALSE)
	{
		// ok
		win->getLog()->LogMSG(win->getLog()->MSG_NORMAL, "[SHADERS:LINK:BASIC]", "Link Status . . . SUCCESS");
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

		win->getLog()->LogMSG(win->getLog()->MSG_ERROR, "[SHADER:LINK]", "Failed to Link Program : " + std::string(message));
	}

	// Batch GLSL Program
	m_batchVS_Source = read_file("src\\shaders\\batch_vs.glsl");
	m_batchFS_Source = read_file("src\\shaders\\batch_fs.glsl");

	m_batchVS = glCreateShader(GL_VERTEX_SHADER);
	m_batchFS = glCreateShader(GL_FRAGMENT_SHADER);

	const char* batch_vsrc = m_batchVS_Source.c_str();
	const char* batch_fsrc = m_batchFS_Source.c_str();

	glShaderSource(m_batchVS, 1, &batch_vsrc, 0);
	glShaderSource(m_batchFS, 1, &batch_fsrc, 0);

	glCompileShader(m_batchVS);
	GLint batch_vertex_compiled;
	glGetShaderiv(m_batchVS, GL_COMPILE_STATUS, &batch_vertex_compiled);
	if (batch_vertex_compiled != GL_TRUE)
	{
		GLsizei log_lenght = 0;
		GLchar message[1024];
		glGetShaderInfoLog(m_batchVS, 1024, &log_lenght, message);

		win->getLog()->LogMSG(win->getLog()->MSG_ERROR, "[SHADER:VS:BATCH]", "Could Not Compile, Error Message : \n" + std::string(message));
		//return;
	}
	else
	{
		win->getLog()->LogMSG(win->getLog()->MSG_NORMAL, "[SHADER:VS:BATCH]", " Shader Creation . . . SUCCESS");
	}

	glCompileShader(m_batchFS);
	GLint batch_fragment_compiled;
	glGetShaderiv(m_batchFS, GL_COMPILE_STATUS, &batch_fragment_compiled);
	if (batch_fragment_compiled != GL_TRUE)
	{
		GLsizei log_lenght = 0;
		GLchar message[1024];
		glGetShaderInfoLog(m_batchFS, 1024, &log_lenght, message);

		win->getLog()->LogMSG(win->getLog()->MSG_ERROR, "[SHADER:FS:BATCH]", "Could Not Compile, Error Message : \n" + std::string(message));
		return;
	}
	else
	{
		win->getLog()->LogMSG(win->getLog()->MSG_NORMAL, "[SHADER:FS:BATCH]", "Shader Creation . . . SUCCESS");
	}

	m_BatchProgram = glCreateProgram();
	glAttachShader(m_BatchProgram, m_batchVS);
	glAttachShader(m_BatchProgram, m_batchFS);
	glLinkProgram(m_BatchProgram);
	GLint batchlinked;
	glGetProgramiv(m_BatchProgram, GL_LINK_STATUS, &batchlinked);
	if (batchlinked != GL_FALSE)
	{
		// ok
		win->getLog()->LogMSG(win->getLog()->MSG_NORMAL, "[SHADERS:LINK:BATCH]", "Link Status . . . SUCCESS");
	}
	else
	{
		GLint maxLength = 0;
		glGetProgramiv(m_BatchProgram, GL_INFO_LOG_LENGTH, &maxLength);

		GLchar message[1024];
		glGetProgramInfoLog(m_BatchProgram, maxLength, &maxLength, &message[0]);

		// We don't need the program anymore.
		glDeleteProgram(m_BatchProgram);
		// Don't leak shaders either.
		glDeleteShader(m_batchVS);
		glDeleteShader(m_batchFS);

		win->getLog()->LogMSG(win->getLog()->MSG_ERROR, "[SHADERS:LINK:BATCH]", "Failed to Link Program : " + std::string(message));
	}

	// Texture GLSL Program
	m_texFS_Source = read_file("src\\shaders\\tex_fs.glsl");
	m_texVS_Source = read_file("src\\shaders\\tex_vs.glsl");

	const char* tex_vsrc = m_texVS_Source.c_str();
	const char* tex_fsrc = m_texFS_Source.c_str();

	m_texFS = glCreateShader(GL_FRAGMENT_SHADER);
	m_texVS = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(m_texFS, 1, &tex_fsrc, 0);
	glShaderSource(m_texVS, 1, &tex_vsrc, 0);

	glCompileShader(m_texFS);
	GLint tex_vertex_compiled;
	glGetShaderiv(m_texFS, GL_COMPILE_STATUS, &tex_vertex_compiled);
	if (tex_vertex_compiled != GL_TRUE)
	{
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetShaderInfoLog(m_texFS, 1024, &log_length, message);

		win->getLog()->LogMSG(win->getLog()->MSG_ERROR, "[SHADERS:FS:TEX]", "Could Not Compile, Error Message: \n" + std::string(message));
		return;
	}
	else
	{
		win->getLog()->LogMSG(win->getLog()->MSG_NORMAL, "[SHADERS:FS:TEX]", "Shader Creation . . . SUCCESS");
	}

	glCompileShader(m_texVS);
	GLint tex_frag_compiled;
	glGetShaderiv(m_texFS, GL_COMPILE_STATUS, &tex_frag_compiled);
	if (tex_frag_compiled != GL_TRUE)
	{
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetShaderInfoLog(m_texVS, 1024, &log_length, message);

		win->getLog()->LogMSG(win->getLog()->MSG_ERROR, "[SHADERS:VS:TEX]", "Could Not Compile, Error Message: \n" + std::string(message));
		return;
	}
	else
	{
		win->getLog()->LogMSG(win->getLog()->MSG_NORMAL, "[SHADERS:VS:TEX]", "Shader Creation . . . SUCCESS");
	}

	m_TextureProgram = glCreateProgram();
	glAttachShader(m_TextureProgram, m_texVS);
	glAttachShader(m_TextureProgram, m_texFS);
	glLinkProgram(m_TextureProgram);
	GLint texlinked;
	glGetProgramiv(m_TextureProgram, GL_LINK_STATUS, &texlinked);
	if (texlinked != GL_FALSE)
	{
		// ok
		win->getLog()->LogMSG(win->getLog()->MSG_NORMAL, "[SHADERS:LINK:TEX]", "Link Status . . . SUCCESS");
	}
	else
	{
		GLint maxLength = 0;
		glGetProgramiv(m_TextureProgram, GL_INFO_LOG_LENGTH, &maxLength);

		GLchar message[1024];
		glGetProgramInfoLog(m_TextureProgram, maxLength, &maxLength, &message[0]);

		// We don't need the program anymore.
		glDeleteProgram(m_TextureProgram);
		// Don't leak shaders either.
		glDeleteShader(m_texVS);
		glDeleteShader(m_texFS);

		win->getLog()->LogMSG(win->getLog()->MSG_ERROR, "[SHADERS:LINK:TEX]", "Failed to Link Program : " + std::string(message));
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
	m_CurrentProgram = m_BasicProgram;
}

void OSRAM::GRAPHICS::Shaders::UseBatchProgram()
{
	glUseProgram(m_BatchProgram);
	m_CurrentProgram = m_BatchProgram;
}

void OSRAM::GRAPHICS::Shaders::UseTextureProgram()
{
	glUseProgram(m_TextureProgram);
	m_CurrentProgram = m_TextureProgram;
}

void OSRAM::GRAPHICS::Shaders::Uniform1f(unsigned int program, const char* str, float val)
{
	int location = glGetUniformLocation(program, str);
	glUniform1f(location, val);
}

void OSRAM::GRAPHICS::Shaders::Uniform1i(unsigned int program, const char* str, int val)
{
	int location = glGetUniformLocation(program, str);
	glUniform1i(location, val);
}

void OSRAM::GRAPHICS::Shaders::Uniform2f(unsigned int program, const char* str, float val1, float val2)
{
	int location = glGetUniformLocation(program, str);
	glUniform2f(location, val1, val2);
}

void OSRAM::GRAPHICS::Shaders::Uniform2i(unsigned int program, const char* str, int val1, int val2)
{
	int location = glGetUniformLocation(program, str);
	glUniform2i(location, val1, val2);
}

void OSRAM::GRAPHICS::Shaders::Uniform3f(unsigned int program, const char* str, float val1, float val2, float val3)
{
	int location = glGetUniformLocation(program, str);
	glUniform3f(location, val1, val2, val3);
}

void OSRAM::GRAPHICS::Shaders::Uniform3i(unsigned int program, const char* str, int val1, int val2, int val3)
{
	int location = glGetUniformLocation(program, str);
	glUniform3i(location, val1, val2, val3);
}

void OSRAM::GRAPHICS::Shaders::Uniform4f(unsigned int program, const char* str, float val1, float val2, float val3, float val4)
{
	int location = glGetUniformLocation(program, str);
	glUniform4f(location, val1, val2, val3, val4);
}

void OSRAM::GRAPHICS::Shaders::Uniform4i(unsigned int program, const char* str, int val1, int val2, int val3, int val4)
{
	int location = glGetUniformLocation(program, str);
	glUniform4i(location, val1, val2, val3, val4);
}

void OSRAM::GRAPHICS::Shaders::UnifromMat3(unsigned int program, const char* str, glm::mat4 val, bool transpose)
{
	int location = glGetUniformLocation(program, str);
	glUniformMatrix3fv(location, 1, transpose, &val[0][0]);
}

void OSRAM::GRAPHICS::Shaders::UnifromMat4(unsigned int program, const char* str, glm::mat4 val, bool transpose)
{
	int location = glGetUniformLocation(program, str);
	glUniformMatrix4fv(location, 1, transpose, &val[0][0]);
}