#include "MVP.h"

OSRAM::GRAPHICS::MVP::MVP(Shaders * shader)
{
	m_Shader = shader;
}

OSRAM::GRAPHICS::MVP::~MVP()
{
}

void OSRAM::GRAPHICS::MVP::SetModelMatrix(glm::mat4 mat)
{
	m_Shader->UnifromMat4(m_Shader->GetBasicProgram(), "m_M", mat, false);
}

void OSRAM::GRAPHICS::MVP::SetViewMatrix(glm::mat4 view)
{
	m_Shader->UnifromMat4(m_Shader->GetBasicProgram(), "m_V", view, false);
}

void OSRAM::GRAPHICS::MVP::SetProjectionMatrix(glm::mat4 proj)
{
	m_Shader->UnifromMat4(m_Shader->GetBasicProgram(), "m_P", proj, false);
}