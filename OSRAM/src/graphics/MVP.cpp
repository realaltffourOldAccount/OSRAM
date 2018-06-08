#include "MVP.h"

OSRAM::GRAPHICS::MVP::MVP(Shaders * shader)
{
	m_Shader = shader;
}

OSRAM::GRAPHICS::MVP::~MVP()
{
}

void OSRAM::GRAPHICS::MVP::SetBasicModelMatrix(glm::mat4 mat)
{
	m_Shader->UnifromMat4(m_Shader->GetBasicProgram(), "m_M", mat, false);
}

void OSRAM::GRAPHICS::MVP::SetBasicViewMatrix(glm::mat4 view)
{
	m_Shader->UnifromMat4(m_Shader->GetBasicProgram(), "m_V", view, false);
}

void OSRAM::GRAPHICS::MVP::SetBasicProjectionMatrix(glm::mat4 proj)
{
	m_Shader->UnifromMat4(m_Shader->GetBasicProgram(), "m_P", proj, false);
}

void OSRAM::GRAPHICS::MVP::SetBatchModelMatrix(glm::mat4 mat)
{
	m_Shader->UnifromMat4(m_Shader->GetBatchProgram(), "m_M", mat, false);
}

void OSRAM::GRAPHICS::MVP::SetBatchViewMatrix(glm::mat4 view)
{
	m_Shader->UnifromMat4(m_Shader->GetBatchProgram(), "m_V", view, false);
}

void OSRAM::GRAPHICS::MVP::SetBatchProjectionMatrix(glm::mat4 proj)
{
	m_Shader->UnifromMat4(m_Shader->GetBatchProgram(), "m_P", proj, false);
}

void OSRAM::GRAPHICS::MVP::SetTextureModelMatrix(glm::mat4 model)
{
	m_Shader->UnifromMat4(m_Shader->GetTextureProgram(), "m_M", model, false);
}

void OSRAM::GRAPHICS::MVP::SetTextureViewMatrix(glm::mat4 view)
{
	m_Shader->UnifromMat4(m_Shader->GetTextureProgram(), "m_V", view, false);
}

void OSRAM::GRAPHICS::MVP::SetTextureProjectionMatrix(glm::mat4 proj)
{
	m_Shader->UnifromMat4(m_Shader->GetTextureProgram(), "m_P", proj, false);
}
